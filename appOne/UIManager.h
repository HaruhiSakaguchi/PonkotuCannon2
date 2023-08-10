#pragma once
#include <vector>
#include "Manager.h"

class UIManager
	:public Manager
{

public:
	UIManager(class Game* game);
	~UIManager();
	void Update()override;
	void ProcessInput()override;
	void PushUI(class UIScreen* uiScreen);
	void PullUI(class UIScreen* uiScreen);

	void AddUIPSide(class UIPSideCharacterStatusBase* ui);
	void RemoveUIPSide(class UIPSideCharacterStatusBase* ui);
	void UIClear();
	void UIClear(UIScreen* ui);
	const class std::vector<class UIScreen*>& GetUIStack() { return mUIStack; }
	const std::vector<class UIPSideCharacterStatusBase*>& GetUIPSideStatus() { return mUIStatus; }

private:
	std::vector<class UIScreen*>mUIStack;
	std::vector<class UIPSideCharacterStatusBase*>mUIStatus;
	bool mUpdatingUIs;
	std::vector<class UIScreen*> mPendingUIs;

};

