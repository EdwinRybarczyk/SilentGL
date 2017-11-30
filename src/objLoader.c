#include "objLoader.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

void loadVert(char* data, int dataSize, int* bufferSize)
{

}

objData loadModelOBJ(char* path)
{
    objData data;
    data.vCount = 0;
    data.iCount = 0;
    data.success = 1;
    FILE* f = fopen(path,"r");
    if(f==NULL)
    {
        data.success = 0;
        printf("file %s could not be opened\n", path);
        return data;
    }

    char* line = NULL;
    size_t size;

    int vBufferCount = 0;
    int iBufferCount = 0;
    int tBufferCount = 0;

    while(getline(&line,&size,f) != -1)
    {
        
        if(line[0] == 'v' && isspace(line[1]))
        {
            loadVert(line, size, &vBufferCount);
        }

    }

}