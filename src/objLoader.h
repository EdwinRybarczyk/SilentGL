//Data stored for loaded model
typedef struct objData
{
    float* vertices;
    int vCount;
    int* indices;
    int iCount;
    float* textureCoords;
    int tCount;
    float* normals;
    int nCount;
    char success;
}objData;

//Return model data
objData* loadModelOBJ(char* path);