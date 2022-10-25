#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include "functions.h"

int copy_files(char* filename, char* in_path, char* out_path);

int main(int argc, char** argv)
{
    char cwd[PATH_MAX], in_path[PATH_MAX], out_path[PATH_MAX], mode[11];
    struct dirent *de;
    DIR *dr = opendir(".");

    memset(in_path,0x00,sizeof(in_path));
    memset(out_path,0x00,sizeof(out_path));
    
    printf("Reading parameters...\n");
    
    if(argc != 4) {
        printf("Wrong format:\n\timage in_path out_path oper\n\toperation: copy, histo, mono, gauss\n\n");
        return -1;
    }
    
    validate_parameters(argv);

    // prueba - borrar si se quiere trabajar con otros directorios
    if(getcwd(cwd, sizeof(cwd)) != NULL) {
        strcpy(in_path, cwd);
        strcpy(out_path, cwd);
        printf("Input path: %s\n", in_path);
        printf("Output path: %s\n", out_path);
    } else {
        perror("getcwd() error");
        return -1;
    }
    
    // prueba - descomentar esto si se borro lo anterior
    /*strcpy(in_path, argv[1]);
    strcpy(out_path, argv[2]);
    printf("Input path: %s\n", in_path);
    printf("Output path: %s\n", out_path);*/
    
    // tipo de operacion
    strcpy(mode, argv[3]);
    
    if(check_operation(mode) == -1) return -1;
    
    if (dr == NULL)  // abrir directorio
    {
        printf("Could not open current directory" );
        return -1;
    }
    
    // busca los archivos BMP
    while ((de = readdir(dr)) != NULL){
        if(is_bmp(de->d_name))
        {
            //printf("File: %s\n", de->d_name);
            //sprintf(full_filename, "%s\\%s", in_path, de->d_name);
            //printf("Full filename: %s\n", full_filename);
            
            if(strcmp(mode, "copy") == 0){
                if(copy_files(de->d_name, in_path, out_path) != 0){
                    printf("Could not copy %s to %s\n", de->d_name, out_path);
                    return -1;
                }
            }
            if(strcmp(mode, "histo") == 0){
                printf("Create histogram\n");
            }
            if(strcmp(mode, "mono") == 0){
                printf("Generate mono file\n");
            }
            if(strcmp(mode, "gauss") == 0){
                printf("Apply Gaussian smoothing\n");
            }
            
        }
    }
    
    closedir(dr);

    printf("End of program\n");
    return 0;
}
