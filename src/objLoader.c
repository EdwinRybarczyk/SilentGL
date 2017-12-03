#include "objLoader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

//Vertice loader
void loadVert(objData* objData, char* data, int dataSize, int* bufferSize)
{
    //Number buffer
    char* buffer = malloc(25);
    //Iterate through line
    int numCount = 0;
    for(int i = 0; i < dataSize; i++)
    {
        //Check whether its digit
        if((isdigit(data[i]) || data[i] == '-')/* && numCount < 3*/)
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
            objData->vCount+=1;
            *bufferSize+=1;
            numCount+=1;
        }
    }
}

//Texture coordinate loader
void loadTex(objData* objData, char* data, int dataSize, int* bufferSize)
{
    //Number buffer
    char* buffer = malloc(25);
    //Iterate through line
    int numCount = 0;
    for(int i = 0; i < dataSize; i++)
    {
        //Check whether its digit
        if((isdigit(data[i]) || data[i] == '-')&&numCount < 2)
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
            objData->tCount+=1;
            *bufferSize+=1;
            numCount+=1;
        }
    }
}

//Normals loader
void loadNorm(objData* objData, char* data, int dataSize, int* bufferSize)
{
    //Number buffer
    char* buffer = malloc(25);
    //Iterate through line
    int numCount = 0;
    for(int i = 0; i < dataSize; i++)
    {
        //Check whether its digit
        if((isdigit(data[i]) || data[i] == '-')&&numCount<3)
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
            objData->nCount+=1;
            *bufferSize+=1;
            numCount+=1;
        }
    }
}

//Indice loader
void loadFace(char* objData, int *c, char* data, int dataSize, int* bufferSize)
{
    //Number buffer
    char* buffer = malloc(25);
    //Iterate through line
    int numCount = 0;
    for(int i = 0; i < dataSize; i++)
    {
        //Check whether its digit
        if(isdigit(data[i]) && numCount < 9)
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
                void* temp = realloc(objData, sizeof(float)*500 +
                    *(bufferSize)*sizeof(float));  
            
                if(temp == NULL)
                {
                    exit(0);
                }
                objData = temp;
            }
            //Append the float value   
            objData[*bufferSize] = (atoi(value))-1;
            *bufferSize+=1;
            *c += 1;
            numCount+=1;
        }
    }
}

objData loadModelOBJ(char* path)
{
    //char* locale = setlocale(LC_ALL,"en_UK.utf8");
    objData data;
    data.vertices = malloc(501*sizeof(float));
    data.vCount = 0;
    data.textureCoords = malloc(501*sizeof(float));
    data.tCount = 0;
    data.indices = malloc(501*sizeof(int));
    data.iCount = 0;
    data.normals = malloc(501*sizeof(float));
    data.nCount = 0;
    data.success = 1;

    char* faces = malloc(500*sizeof(int));
    int fCount = 0;

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
    int nBufferCount = 0;
    int fBufferCount = 0;

    //Load data
    while(getline(&line,&size,f) != -1)
    {
        
        if(line[0] == 'v' && isspace(line[1]))
        {
            loadVert(&data, line, size, &vBufferCount);
        }
        
        if(line[0] == 'v' && line[1] == 't')
        {
            loadTex(&data, line, size, &tBufferCount);
        }

        if(line[0] == 'v' && line[1] == 'n')
        {
            loadNorm(&data, line, size, &nBufferCount);
        }

        if(line[0] == 'f' && isspace(line[1]))
        {
            loadFace(faces,&fCount,line, size, &fBufferCount);
        }
        
    }
    //Reallocate to size and fix indices
    float* temp;
    //Realloc vertices  
    temp = realloc(data.vertices, data.vCount*sizeof(float));  
    if(temp == NULL)
    {
        data.success = 0;
        return data;
    }
    data.vertices = temp;

    //generate indices
    
    
    data.iCount = fCount/3;
    data.indices = malloc(data.iCount*sizeof(int));
    for(int i = 0; i < data.iCount; i++)
    {
        data.indices[i] = faces[i*3];
    }

    //Reallocate texture coordinates
    temp = realloc(data.textureCoords, data.tCount*sizeof(float));  
    if(temp == NULL)
    {
        data.success = 0;
        return data;
    }
    data.textureCoords = malloc(data.tCount*sizeof(float));
    for(int i = 0; i < fCount; i++)
    {
        int v = faces[i*3];
        int t = faces[i*3+1];
        memcpy(
            &data.textureCoords[v],
            &temp[faces[t]],
            2*sizeof(float)
        );
    }
    //free(temp);
    //Reallocate normals
    temp = realloc(data.normals, data.nCount*sizeof(float));  
    if(temp == NULL)
    {
        data.success = 0;
        return data;
    }
    data.normals = malloc(data.nCount*sizeof(float));
    for(int i = 0; i < fCount; i++)
    {
        int v = faces[i*3];
        int t = faces[i*3+2];
        memcpy(
            &data.normals[v],
            &temp[faces[t]],
            3*sizeof(float)
        );
    }
    

    return data;
}