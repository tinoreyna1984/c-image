#include <stdio.h>
#include <string.h>

/* Generales */

bool validate_parameters(char** argv)
{

    printf("Method: %s\n", argv[3]);

    return true;
}

bool is_bmp(const char* filename)
{

    char* ret;
    char bmp[5];

    strcpy(bmp, ".bmp");
    ret = strstr(filename, ".bmp");

    if(ret == NULL || strcmp(ret, bmp) != 0)
        return false;

    return true;
}

int check_operation(char* mode)
{
    printf("Operation: %s\n", mode);

    if(strcmp(mode, "copy") != 0 && strcmp(mode, "histo") != 0 && strcmp(mode, "mono") != 0 &&
        strcmp(mode, "gauss") != 0) {
        printf("Unexpected operation:%s\n\timage in_path out_path oper\n\toperation: copy, histo, mono, gauss\n", mode);
        return -1;
    }

    return 0;
}
