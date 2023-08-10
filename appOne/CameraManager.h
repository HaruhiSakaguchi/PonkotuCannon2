#pragma once
#include "Actor.h"
#include "Camera.h"
#include "Manager.h"
#include <unordered_map>
#include <vector>

class CameraManager
	: public Manager
{
public:
	CameraManager(class Game* game);
	~CameraManager();
	int SetUp();
	void Update();
	class Camera* GetCurCamera() { return mCurCamera; }
	void SetCurCamera(Camera* cam) { mCurCamera = cam; }
	void AddCamera(class Camera* camera);
	void RemoveCamera(class Camera* camera);
	void RegisterCamera(Camera* camera);
	void ChangeCamera(const char* name);

private:
	void LoadText(const char* fileName);
	void SaveText(const char* fileName);
private:
	std::vector<Camera*>mCameras;
	VECTOR mPos;
	class Camera* mCurCamera;
	std::unordered_map<std::string, class Camera*> mCameraMap;
private:
	//ÉJÉÅÉâä¥ìx
	float mSensitivityX;
	float mSensitivityY;
	const char* mSaveFileName = "Assets\\option\\Camera.txt";
public:
	void SetCameraSX(float sx) { mSensitivityX = sx; }
	void SetCameraSY(float sy) { mSensitivityY = sy; }
	float GetCameraSX() { return mSensitivityX; }
	float GetCameraSY() { return mSensitivityY; }
};

