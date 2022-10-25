#include <stdio.h>    
#include <stdlib.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>

int copy_files(char* filename, char* in_path, char* out_path)
{
    char source_filename[PATH_MAX], target_filename[PATH_MAX];
    int src_fd, dst_fd, n, err;
    unsigned char buffer[4096];

    // origen y destino
    sprintf(source_filename, "%s\\%s", in_path, filename);
    sprintf(target_filename, "%s\\copy_%s", out_path, filename);
    src_fd = open(source_filename, O_RDONLY);
    dst_fd = open(target_filename, O_CREAT | O_WRONLY);
    
    // copia contenido masivo del BMP
    while (1) {
        err = read(src_fd, buffer, 4096);
        if (err == -1) {
            printf("Error reading file.\n");
            exit(1);
        }
        n = err;

        if (n == 0) break;

        err = write(dst_fd, buffer, n);
        if (err == -1) {
            printf("Error writing to file.\n");
            exit(1);
        }
    }
    
    printf("Copy %s to %s: DONE\n", filename, out_path);

    // cierra punteros
    close(src_fd);
    close(dst_fd);

    return 0;
}