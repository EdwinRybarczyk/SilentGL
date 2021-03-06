#include "objLoader.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

//Vertice loader
void loadVert(vector* verts, char* data, int dataSize)
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
            //Append the float value   
            float* val = malloc(sizeof(float));
            *val = atof(value);
            vectorPushBack(verts,val);
            free(val);
            numCount+=1;
        }
    }
}

//Texture coordinate loader
void loadTex(vector* textureCoordinates, char* data, int dataSize)
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
            
            //Append the float value   
            //objData->textureCoords[objData->tCount] = atof(value);
            float* val = malloc(sizeof(float));
            *val = atof(value);
            vectorPushBack(textureCoordinates, val);
            free(val);
            numCount+=1;
        }
    }
}

//Normals loader
void loadNorm(vector* normals, char* data, int dataSize)
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
            //Append the float value   
            float* val = malloc(sizeof(float));
            *val = atof(value);
            vectorPushBack(normals, val);
            free(val);
            numCount+=1;
        }
    }
}

//Indice loader
void loadFace(vector* faces, char* data, int dataSize)
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

            //Append the float value   
            float* val = malloc(sizeof(float));
            *val = atof(value);
            vectorPushBack(faces, val);
            free(val);
            numCount+=1;
        }
    }
    free(buffer);
}

objData* loadModelOBJ(char* path)
{
    //char* locale = setlocale(LC_ALL,"en_UK.utf8");
    objData *data = malloc(sizeof(objData));
    data->vertices = createVector(sizeof(float));
    data->indices = createVector(sizeof(int));
    data->textureCoords = createVector(sizeof(float));
    data->normals = createVector(sizeof(float));

    vector* faces = createVector(sizeof(int));

    FILE* f;
    f = fopen(path,"r");
    if(f==NULL)
    {
        printf("file %s could not be opened\n", path);
        exit(1);
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
            loadVert(data->vertices, line, size);
        }
        
        if(line[0] == 'v' && line[1] == 't')
        {
            loadTex(data->textureCoords, line, size);
        }

        if(line[0] == 'v' && line[1] == 'n')
        {
            loadNorm(data->normals, line, size);
        }

        if(line[0] == 'f' && isspace(line[1]))
        {
            loadFace(faces,line, size);
        }
        
        size = getline(&line,&s,f);
    }
    //Reallocate to size and fix indices
    //float* temp;

    //data->vertices = realloc(data->vertices, data->vCount*sizeof(float));

    //generate indices
    //data->iCount = fCount/3;
    //data->indices = malloc(data->iCount*sizeof(int));
    for(int i = 0; i < faces->dataCount/3; i++)
    {
        //data->indices[i] = faces[i*3];
        vectorPushBack(data->indices,faces->integers + (i*3));
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

    //printf("icount:%i\n",data->iCount);

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