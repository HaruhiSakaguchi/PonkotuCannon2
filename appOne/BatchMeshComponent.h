#pragma once
#include "MeshComponent.h"
class BatchMeshComponent :
    public MeshComponent
{
public:
    BatchMeshComponent(class Actor* owner, bool isDraw = true);
    ~BatchMeshComponent();
    void SetBatch(const char* name);
    void Draw()override;
private:
    class BATCH* mBatch;
};

