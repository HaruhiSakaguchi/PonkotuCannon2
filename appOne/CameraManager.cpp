#include "CameraManager.h"
#include "Camera.h"
#include "NormalCamera.h"
#include "Game.h"
#include "PlayerHome.h"
#include "LookFieldCenterCamera.h"
#include "LookPHomeCamera.h"
#include "FILE_BUFFER.h"
#include "NAME.h"

CameraManager::CameraManager(Game* game)
	: Manager(game)
	, mCurCamera(nullptr)
	, mPos(0.0f, 0.0f, 0.0f)
	, mSensitivityX(0.0f)
	, mSensitivityY(0.0f)

{
	SetUp();
	mGame->SetCameraManager(this);
}

CameraManager::~CameraManager()
{
	while (!mCameras.empty())
	{
		delete mCameras.back();
	}

	mGame->SetCameraManager(nullptr);

	SaveText(mSaveFileName);
}

int CameraManager::SetUp()
{
	LoadText(mSaveFileName);
	return 0;
}

void CameraManager::Update()
{
	if (mCurCamera)
	{
		VECTOR prePos = mCurCamera->GetPosition();

		mPos.x = prePos.x + (mPos.x - prePos.x) * mGame->GetAllData()->cameraData.mChangePosSpeed;
		mPos.y = prePos.y + (mPos.y - prePos.y) * mGame->GetAllData()->cameraData.mChangePosSpeed;
		mPos.z = prePos.z + (mPos.z - prePos.z) * mGame->GetAllData()->cameraData.mChangePosSpeed;

		MATRIX view;
		view.camera(mPos, mCurCamera->GetLookatPos(), mGame->GetAllData()->cameraData.mUpVec);
		mGame->GetRenderer()->SetView(view);
	}
}

void CameraManager::AddCamera(class Camera* camera)
{
	mCameras.emplace_back(camera);
}

void CameraManager::RemoveCamera(class Camera* camera)
{
	//このactorがmActorsにあるか探す
	auto iter = std::find(mCameras.begin(), mCameras.end(), camera);
	if (iter != mCameras.end())
	{
		//このActorとケツのActorを入れ替える(消去後コピー処理を避けるため)
		std::iter_swap(iter, mCameras.end() - 1);
		mCameras.pop_back();
	}

	auto iter2 = mCameraMap.find(camera->GetCamName());
	mCameraMap.erase(iter2);
}

void CameraManager::RegisterCamera(class Camera* camera)
{
	mCameraMap.emplace(camera->GetCamName(), camera);
}

void CameraManager::ChangeCamera(const char* name)
{
	auto iter = mCameraMap.find(name);
	if (iter != mCameraMap.end())
	{
		mCurCamera = iter->second;
	}
	else
	{
		mCurCamera = nullptr;
	}
}

void CameraManager::LoadText(const char* fileName)
{
	FILE_BUFFER fb(fileName);
	NAME name;

	fb.readString();
	while (!fb.end()) {
		if (fb == "X")
		{
			mSensitivityX = fb.readFloat();
			fb.readString();
		}
		if (fb == "Y")
		{
			mSensitivityY = fb.readFloat();
		}

		fb.readString();
	}
}

void CameraManager::SaveText(const char* fileName)
{
	FILE* fp = NULL;
	fopen_s(&fp, fileName, "w");
	if (fp != NULL)
	{
		fprintf_s(fp, "%s %f\n", "X ", mSensitivityX);
		fprintf_s(fp, "%s %f\n", "Y ", mSensitivityY);
	}
	fclose(fp);
}
