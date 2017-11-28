//Data stored for each model
typedef struct objData
{
    float* vertices;
    int* indices;
    float* textureCoords;
}objData;

//Return model data
objData loadModelOBJ(char* path);