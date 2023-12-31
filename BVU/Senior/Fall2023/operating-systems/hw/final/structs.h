struct File {
    char filename[512];
    int length;
} typedef File;

struct MetaData {
    char dir_name[256];
    int num_files;
} typedef MetaData;
