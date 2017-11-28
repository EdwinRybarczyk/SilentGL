#include "objLoader.h"
#include <stdlib.h>
#include <stdio.h>
objData loadModelOBJ(char* path)
{
    FILE* f = fopen(path,"r");
    if(f==NULL)
    {
        printf("file %s could not be opened\n", path);
        return;
    }

    char* line = NULL;
    size_t size;

    while(getline(&line,&size,f) != -1)
    {
        
        if(line[0] == 'v')
        {
            
        }

    }

}