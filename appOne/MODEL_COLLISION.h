#pragma once
#include "Map.h"
#include <string>

class MODEL_COLLISION
{
public:
    MODEL_COLLISION(class Map* map, int numTriangles, int numVertices, int* indices, VECTOR* vertices, const char* name = "name");
    void allocateMemory();
    virtual ~MODEL_COLLISION();
    class Map* GetMap() { return mMap; }
    void SetNormals(VECTOR* normals) { mONormals = normals; }
    void SetIndices(int* indices) { mIndices = indices; }
    void SetVertices(VECTOR* position) { mOPositions = position; }
    void SetNumTriangles(int num) { mNumTriangles = num; }
    void SetNumVertices(int num) { mNumVertices = num; }
    void SetName(const char* Name) { mName = Name; }
    const char* GetName() { return mName.c_str(); }
    VECTOR* GetOPosition() { return mOPositions; }
    int* GetIndices() { return mIndices; }
    int GetNumVertices() { return mNumVertices; }
    int GetNumIndices() { return mNumIndices; }
    int GetNumTriangles() { return mNumTriangles; }
private:
    class Map* mMap;
protected:
    bool mAddFlag = true;
    int mNumVertices = 0;
    int mNumTriangles = 0;
    int mNumIndices = 0;

    //計算前のOriginalデータ
    VECTOR* mOPositions = nullptr;
    VECTOR mTmpPosition;
    VECTOR* mONormals = nullptr;
    //頂点を選択するインデックス配列
    int* mIndices = nullptr;
    std::string mName = "name";
};