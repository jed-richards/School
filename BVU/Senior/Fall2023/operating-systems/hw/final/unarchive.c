#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>

#include "structs.h"

int main(int argc, char* argv[]) {
    if (argc != 2) {
        printf("Error: invalid arguments.\n");
        printf("Usage: [%s archive.file]\n", argv[0]);
        return 0;
    }

    char *archive_file = argv[1];

    // try to open archive file
    int archive_file_fd = open(archive_file, O_RDONLY);
    if (archive_file_fd < 0) {
        printf("Error: %s", strerror(errno));
        return -1;
    }

    // read meta-data into MetaData struct
    MetaData meta_data;
    read(archive_file_fd, (void *) &meta_data, sizeof(MetaData));

    // Create an array of File objects to hold file meta-data
    File files[meta_data.num_files];

    // try to create directory
    if (mkdir(meta_data.dir_name, S_IRWXU) != 0) {
        printf("Error: %s", strerror(errno));
        return -1;
    };

    // create and write each file into the directory
    for (int i=0; i<meta_data.num_files; i++) {
        read(archive_file_fd, (void *) &files[i], sizeof(File));
        char buf[files[i].length + 1];
        read(archive_file_fd, (void *) buf, files[i].length + 1);
        int fd = open(files[i].filename, O_CREAT | O_RDWR | O_EXCL, 0644);
        write(fd, (void *) buf, files[i].length);
        close(fd);
    }

    return 0;
}
