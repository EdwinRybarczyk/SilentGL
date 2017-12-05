#include "objLoader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

//Vertice loader
void loadVert(objData* objData, char* data, int dataSize)
{
    //Number buffer
    char* buffer = malloc(100);
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
                i+=1;
                //Increase character count
                count+=1;
            }
            //Allocate space for the value and terminator
            value = malloc(count+1);
            //Copy the value from the buffer
            memcpy(value,buffer,count);
            //Null terminate the string
            value[count] = '\0';
            //Reallocate the memory    
            
            if(objData->vCount % 500 == 0)
            {
                //void* temp = realloc(objData->vertices, sizeof(float)*500 +
                //    objData->vCount*sizeof(float));  
            
                //if(temp == NULL)
                //{
                 //   exit(0);
                //}
                //objData->vertices = temp;
                objData->vertices = realloc(objData->vertices, sizeof(float)*500 +
                    objData->vCount*sizeof(float));
            }
            //Append the float value   
            objData->vertices[objData->vCount] = atof(value);
            //printf("%f \n",objData->vertices[*bufferSize]);
            objData->vCount+=1;
            numCount+=1;
        }
    }
}

//Texture coordinate loader
void loadTex(objData* objData, char* data, int dataSize)
{
    //Number buffer
    char* buffer = malloc(100);
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
            
            if(objData->tCount % 500 == 0)
            {
                //void* temp = realloc(objData->textureCoords, sizeof(float)*500 +
                //    objData->tCount*sizeof(float));  
            
                //if(temp == NULL)
                //{
                //    exit(0);
                //}
                objData->textureCoords = realloc(objData->textureCoords, sizeof(float)*500 +
                    objData->tCount*sizeof(float)); 
            }
            //Append the float value   
            objData->textureCoords[objData->tCount] = atof(value);
            //printf("%f \n",objData->textureCoords[*bufferSize]);
            objData->tCount+=1;
            numCount+=1;
        }
    }
}

//Normals loader
void loadNorm(objData* objData, char* data, int dataSize)
{
    //Number buffer
    char* buffer = malloc(100);
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
            
            if(objData->nCount % 500 == 0)
            {
                //void* temp = realloc(objData->normals, sizeof(float)*500 +
                //    objData->nCount *sizeof(float));  
            
                //if(temp == NULL)
                //{
                //    exit(0);
                //}
                objData->normals = realloc(objData->normals, sizeof(float)*500 +
                    objData->nCount *sizeof(float));
            }
            //Append the float value   
            objData->normals[objData->nCount] = atof(value);
            //printf("%f \n",objData->normals[*bufferSize]);
            objData->nCount+=1;
            numCount+=1;
        }
    }
}

//Indice loader
void loadFace(int* line, int *c, char* data, int dataSize)
{
    //Number buffer
    char* buffer = malloc(1000);
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
            //printf("%i\n",count);
            //Allocate space for the value and terminator
            value = malloc(count+1);
            //Copy the value from the buffer
            memcpy(value,buffer,count);
            //Null terminate the string
            value[count] = '\0';
            //Reallocate the memory    
            
            //if(*c % 500 == 0)
            //{
            //    line = realloc(line, sizeof(float)*500 +
            //        (*c)*sizeof(float));
            //}
            //Append the float value   
            line[*c] = (atoi(value))-1;
            *c += 1;
            numCount+=1;
        }
    }
    free(buffer);
}

objData* loadModelOBJ(char* path)
{
    //char* locale = setlocale(LC_ALL,"en_UK.utf8");
    objData *data = malloc(sizeof(objData));
    data->vertices = malloc(501*sizeof(float));
    data->vCount = 0;
    data->textureCoords = malloc(501*sizeof(float));
    data->tCount = 0;
    data->indices = malloc(501*sizeof(int));
    data->iCount = 0;
    data->normals = malloc(501*sizeof(float));
    data->nCount = 0;
    data->success = 1;
    int* faces = malloc(50100*sizeof(int));
    int fCount = 0;

    FILE* f;
    f = fopen(path,"r");
    if(f==NULL)
    {
        data->success = 0;
        printf("file %s could not be opened\n", path);
        //return *data;
    }

    char* line;
    size_t s = 0;
    int size = 0;
    size = getline(&line,&s,f);

    //Load data
    while(size != -1)
    {
        if(line[0] == 'v' && isspace(line[1]))
        {
            loadVert(data, line, size);
        }
        
        if(line[0] == 'v' && line[1] == 't')
        {
            loadTex(data, line, size);
        }

        if(line[0] == 'v' && line[1] == 'n')
        {
            loadNorm(data, line, size);
        }

        if(line[0] == 'f' && isspace(line[1]))
        {
            loadFace(faces,&fCount,line, size);
        }
        
        size = getline(&line,&s,f);
    }
    //Reallocate to size and fix indices
    float* temp;

    data->vertices = realloc(data->vertices, data->vCount*sizeof(float));

    //generate indices
    data->iCount = fCount/3;
    data->indices = malloc(data->iCount*sizeof(int));
    for(int i = 0; i < data->iCount; i++)
    {
        data->indices[i] = faces[i*3];
    }

    /*
    //Reallocate texture coordinates
    //temp = realloc(data.textureCoords, data.tCount*sizeof(float)); 
    temp = malloc(data->tCount*sizeof(float));
    memcpy(temp,data->textureCoords,data->tCount*sizeof(float));

    data->textureCoords = malloc(data->tCount*sizeof(float));
    for(int i = 0; i < fCount/3; i++)
    {
        //int v = faces[i*3];
        //int t = faces[i*3+1];
        //fix this
        /*
        memcpy(
            &data->textureCoords[v],
            &temp[faces[t]],
            2*sizeof(float)
        );
        //printf("t1 %f t2 %f\n",temp[faces[i*3+1]*2],temp[faces[i*3+1]*2+1]);
        data->textureCoords[faces[i*3]] = temp[faces[i*3+1]*2];
        data->textureCoords[faces[i*3]+1] = temp[faces[i*3+1]*2+1];
    }
    //free(temp);
    //Reallocate normals
    //temp = realloc(data.normals, data.nCount*sizeof(float));  
    temp = malloc(data->nCount*sizeof(float));
    /*
    if(temp == NULL)
    {
        data->success = 0;
        return *data;
    }*/
    /*
    memcpy(temp,data->normals,data->nCount*sizeof(float));
    data->normals = malloc(data->nCount*sizeof(float));
    for(int i = 0; i < fCount/3; i++)
    {
        int v = faces[i*3];
        int t = faces[i*3+2];
        //memcpy(
        //    &data->normals[v],
        //    &temp[faces[t]],
        //    3*sizeof(float)
        //);
        data->textureCoords[faces[i*3]] = temp[faces[i*3+1]*3];
        data->textureCoords[faces[i*3]+1] = temp[faces[i*3+1]*3+1];
        data->textureCoords[faces[i*3]+2] = temp[faces[i*3+1]*3+2];
       
    }
    //free(temp);*/

    //for(int i = 0; i < data->vCount;i++)
    //{
    //    printf("v %f\n",data->vertices[i]);
    //}

    printf("icount:%i\n",data->iCount);

/*
    for(int i = 0; i < data->tCount;i++)
    {
        printf("vt%f\n",data->textureCoords[i]);
    }

    for(int i = 0; i < data->nCount;i++)
    {
        printf("vn%f\n",data->textureCoords[i]);
    }*/

    return data;
}