#include "objLoader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

//Vertice loader
void loadVert(objData* objData, char* data, int dataSize, int* bufferSize)
{
    //Number buffer
    char* buffer = malloc(25);
    //Iterate through line
    for(int i = 0; i < dataSize; i++)
    {
        //Check whether its digit
        if(isdigit(data[i]))
        {
            //Prepare variable for value
            char* value;
            //Number of characters in the number
            char count = 0;
            //Check whether it's a number
            while(isdigit(data[i]) || data[i] == '.' || data[i] == '-')
            {
                //Add character to the buffer
                buffer[count] = data[i];
                //Increase iterator
                i++;
                //Increase character count
                count++;
            }
            //Allocate space for the value and terminator
            value = malloc(count+1);
            //Copy the value from the buffer
            memcpy(value,buffer,count);
            //Null terminate the string
            value[count] = '\0';
            //Reallocate the memory    
            
            if(*bufferSize % 500 == 0)
            {
                void* temp = realloc(objData->vertices, sizeof(float)*500 +
                    *(bufferSize)*sizeof(float));  
            
                if(temp == NULL)
                {
                    exit(0);
                }
                objData->vertices = temp;
            }
            //Append the float value   
            objData->vertices[*bufferSize] = atof(value);
            //printf("%f \n",objData->vertices[*bufferSize]);
            objData->vCount++;
        }
    }
}

//Texture coordinate loader
void loadTex(objData* objData, char* data, int dataSize, int* bufferSize)
{
    //Number buffer
    char* buffer = malloc(25);
    //Iterate through line
    for(int i = 0; i < dataSize; i++)
    {
        //Check whether its digit
        if(isdigit(data[i]))
        {
            //Prepare variable for value
            char* value;
            //Number of characters in the number
            char count = 0;
            //Check whether it's a number
            while(isdigit(data[i]) || data[i] == '.' || data[i] == '-')
            {
                //Add character to the buffer
                buffer[count] = data[i];
                //Increase iterator
                i++;
                //Increase character count
                count++;
            }
            //Allocate space for the value and terminator
            value = malloc(count+1);
            //Copy the value from the buffer
            memcpy(value,buffer,count);
            //Null terminate the string
            value[count] = '\0';
            //Reallocate the memory    
            
            if(*bufferSize % 500 == 0)
            {
                void* temp = realloc(objData->textureCoords, sizeof(float)*500 +
                    *(bufferSize)*sizeof(float));  
            
                if(temp == NULL)
                {
                    exit(0);
                }
                objData->textureCoords = temp;
            }
            //Append the float value   
            objData->textureCoords[*bufferSize] = atof(value);
            //printf("%f \n",objData->textureCoords[*bufferSize]);
            objData->tCount++;
        }
    }
}

//Normals loader
void loadNorm(objData* objData, char* data, int dataSize, int* bufferSize)
{
    //Number buffer
    char* buffer = malloc(25);
    //Iterate through line
    for(int i = 0; i < dataSize; i++)
    {
        //Check whether its digit
        if(isdigit(data[i]))
        {
            //Prepare variable for value
            char* value;
            //Number of characters in the number
            char count = 0;
            //Check whether it's a number
            while(isdigit(data[i]) || data[i] == '.' || data[i] == '-')
            {
                //Add character to the buffer
                buffer[count] = data[i];
                //Increase iterator
                i++;
                //Increase character count
                count++;
            }
            //Allocate space for the value and terminator
            value = malloc(count+1);
            //Copy the value from the buffer
            memcpy(value,buffer,count);
            //Null terminate the string
            value[count] = '\0';
            //Reallocate the memory    
            
            if(*bufferSize % 500 == 0)
            {
                void* temp = realloc(objData->normals, sizeof(float)*500 +
                    *(bufferSize)*sizeof(float));  
            
                if(temp == NULL)
                {
                    exit(0);
                }
                objData->normals = temp;
            }
            //Append the float value   
            objData->normals[*bufferSize] = atof(value);
            //printf("%f \n",objData->normals[*bufferSize]);
            objData->nCount++;
        }
    }
}

//Indice loader
void loadInd(objData* objData, char* data, int dataSize, int* bufferSize)
{
    //Number buffer
    char* buffer = malloc(25);
    //Iterate through line
    for(int i = 0; i < dataSize; i++)
    {
        //Check whether its digit
        if(isdigit(data[i]))
        {
            //Prepare variable for value
            char* value;
            //Number of characters in the number
            char count = 0;
            //Check whether it's a number
            while(isdigit(data[i]))
            {
                //Add character to the buffer
                buffer[count] = data[i];
                //Increase iterator
                i++;
                //Increase character count
                count++;
            }
            //Allocate space for the value and terminator
            value = malloc(count+1);
            //Copy the value from the buffer
            memcpy(value,buffer,count);
            //Null terminate the string
            value[count] = '\0';
            //Reallocate the memory    
            
            if(*bufferSize % 500 == 0)
            {
                void* temp = realloc(objData->indices, sizeof(float)*500 +
                    *(bufferSize)*sizeof(float));  
            
                if(temp == NULL)
                {
                    exit(0);
                }
                objData->indices = temp;
            }
            //Append the float value   
            objData->indices[*bufferSize] = atoi(value);
            //printf("%i \n",objData->indices[*bufferSize]);
            objData->iCount++;
        }
    }
}

objData loadModelOBJ(char* path)
{
    objData data;
    data.vertices = malloc(501*sizeof(float));
    data.vCount = 0;
    data.textureCoords = malloc(501*sizeof(float));
    data.tCount = 0;
    data.indices = malloc(501*sizeof(float));
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

    //Load data
    while(getline(&line,&size,f) != -1)
    {
        
        if(line[0] == 'v' && isspace(line[1]))
        {
            loadVert(&data, line, size, &vBufferCount);
        }

        if(line[0] == 'v' && line[1] == 't')
        {
            loadTex(&data, line, size, &iBufferCount);
        }

        if(line[0] == 'v' && line[1] == 'n')
        {
            loadNorm(&data, line, size, &iBufferCount);
        }

        if(line[0] == 'f' && isspace(line[1]))
        {
            loadInd(&data, line, size, &iBufferCount);
        }

    }
    //Reallocate to size
    //Realloc vertices
    void* temp;
    temp = realloc(data.vertices, data.vCount*sizeof(float));  
    if(temp == NULL)
    {
        data.success = 0;
        return data;
    }
    data.vertices = temp;
    //Realloc indices
    temp = realloc(data.indices, data.iCount*sizeof(int));  
    if(temp == NULL)
    {
        data.success = 0;
        return data;
    }
    data.indices = temp;
    //Reallocate texture coordinates
    temp = realloc(data.textureCoords, data.tCount*sizeof(float));  
    if(temp == NULL)
    {
        data.success = 0;
        return data;
    }
    data.textureCoords = temp;
    //Reallocate normals
    temp = realloc(data.normals, data.nCount*sizeof(float));  
    if(temp == NULL)
    {
        data.success = 0;
        return data;
    }
    data.normals = temp;

    return data;
}