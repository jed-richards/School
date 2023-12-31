#include <errno.h>
#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "structs.h"


/*
 * void write_file_to_archive(
 *     int archive_fd,
 *     const char* dir_name,
 *     struct dirent* dir_entity)
 *
 * Description:
 * Opens and writes file to archive file. This is done by creating a
 * File object to hold meta-data for file to be archived. Then, writes
 * the File meta-data followed by the contents of the file. Meaning the
 * archive file will have structure like so:
 *
 * Let:
 *   MD_n : meta-data for file n
 *   C_n  : contents for file n
 *
 * |------|-------------|------|-------------|
 * | MD_1 | ... C_2 ... | MD_2 | ... C_2 ... |
 * |------|-------------|------|-------------|
 *
 * Input Parameters:
 *   int archive_fd: a file descriptor to the archive file.
 *   const char* dir_name: the directory name containing the file to write.
 *   struct dirent* dir_entity: a pointer to the dirent object representing
 *     the file to be written.
 *
 */
void write_file_to_archive(int archive_fd, const char* dir_name, struct dirent *dir_entity) {
    // create File struct with filename: dirname/filename
    File f;
    strcpy(f.filename, dir_name);
    strcat(f.filename, dir_entity->d_name);

    // open file for reading
    int fd = open(f.filename, O_RDONLY);
    if (fd < 0) {
        printf("Error: %s", strerror(errno));
        exit(1);
    }

    // get size of file contents
    f.length = lseek(fd, 0, SEEK_END);

    // set cursor to beginning of file
    lseek(fd, 0, SEEK_SET);

    // create a buffer to store file contents and a null byte
    char buf[f.length+1];
    int bytes_read = read(fd, buf, f.length);
    buf[f.length] = '\0';

    // write file struct and contents to archive file
    write(archive_fd, (void *) &f, sizeof(f));
    write(archive_fd, buf, f.length+1);
    close(fd);
}


/*
 * int is_file(struct dirent* dir_entity)
 *
 * Description:
 * Returns whether a dir_entity is a file or not.
 *
 * Input Parameters:
 * struct dirent* dir_entity: a dirent entry
 *
 * Output:
 *   int
 *     0: not a file
 *     1: is a file
 */
int is_file(struct dirent *dir_entity) {
    if (strcmp(dir_entity->d_name, "..") == 0 || strcmp(dir_entity->d_name, ".") == 0) {
        return 0;
    }
    return 1;
}


/*
 * int count_files(DIR *directory)
 *
 * Description:
 * Returns the count of the number of files within a DIR. Then rewinds
 * the DIR object, i.e., resets to the top of the file list.
 *
 * Input Parameters:
 * DIR *directory: an open DIR object
 *
 * Output:
 *   int count: number of files in directory
 */
int count_files(DIR *directory) {
    int count = 0;
    struct dirent *dir_entity;
    while( (dir_entity = readdir(directory)) != NULL ) {
        if (is_file(dir_entity)) {
            count++;
        }
    }
    rewinddir(directory);

    return count;
}


int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Error: invalid arguments.\n");
        printf("Usage: [%s DIRECTORY archive.file]\n", argv[0]);
        return 0;
    }

    char *dir_name = argv[1];
    char *archive_file = argv[2];

    // append a '/' if dir_name doesn't have one
    if (strcmp(&dir_name[strlen(dir_name)-1], "/") != 0) {
        strcat(dir_name, "/");
    }

    // open archive file
    int archive_file_fd = open(archive_file, O_CREAT | O_RDWR | O_EXCL, 0644);
    if (archive_file_fd < 0) {
        printf("Error: %s", strerror(errno));
        return -1;
    }

    // open directory as a DIR object (dirent.h)
    DIR *directory = opendir(dir_name);
    if (!directory) {
        printf("Failed to open %s\n", dir_name);
        return 1;
    }

    // initialize and write meta-data struct to archive file
    MetaData meta_data;
    strcpy(meta_data.dir_name, dir_name);
    meta_data.num_files = count_files(directory);
    write(archive_file_fd, (void *) &meta_data, sizeof(MetaData));

    // write all files to archive file
    struct dirent *dir_entity;
    while ( (dir_entity = readdir(directory)) != NULL ) {
        if (is_file(dir_entity)) {
            write_file_to_archive(archive_file_fd, meta_data.dir_name, dir_entity);
        }
    }

    // close DIR object and archive file
    closedir(directory);
    close(archive_file_fd);

    return 0;
}
