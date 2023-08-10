#pragma once
#include "UIScreen.h"
#include <vector>

class UILog :
	public UIScreen
{
public:
	UILog(class Game* game);
	~UILog();
	void Draw()override;
	void AddText(std::string text);
	void RemoveText(int num);

	struct DATA
	{
		float mWidth = 0.0f;
		float mHeight = 0.0f;
		float mTextSize = 0.0f;
		VECTOR2 mPos;
		COLOR mLogWindowColor;
		COLOR mLogTextColor;
	};
private:
	DATA Data;
private:
	std::vector<std::string>mTexts;
};

