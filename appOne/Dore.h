#pragma once
#include "Actor.h"
#include <functional>

class Dore : public Actor
{
public:
	Dore(class Game* game);
	int SetUp();
	void UpdateActor();
	bool OpenDore();
	bool CloseDore();
	void Open() { mBeginOpenFlag = true; }
	void Close() { mBeginCloseFlag = true; }
	void SetIsRotate(bool flag) { mIsRotate = flag; }
	bool GetCloseComplete() { return mCloseComplete; }
	bool GetOpenComplete() { return mOpenComplete; }
	bool GetBeginOpen() { return mBeginOpenFlag; }
	class TreeMeshComponent* GetMesh() { return mTc; }
	bool Closing() { return mClosing; }
	bool Opening() { return mOpening; }
	void SetCloseEvent(std::function<void()>func) { mOnClose = func; }

private:
	bool mBeginOpenFlag;
	bool mBeginCloseFlag;
	bool mOpenComplete;
	bool mCloseComplete;
	bool mIsRotate;
	bool mClosing;
	bool mOpening;
	class TreeMeshComponent* mTc;
	std::function<void()> mOnClose;

};

