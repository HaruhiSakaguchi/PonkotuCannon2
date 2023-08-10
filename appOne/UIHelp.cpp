#include "UIHelp.h"
#include "Game.h"

UIHelp::UIHelp(class Game* game)
	: UIHelpBase(game)
{
	mImgs.emplace_back(Data.mHelp1Img);
	mImgs.emplace_back(Data.mHelp2Img);
	mImgs.emplace_back(Data.mHelp3Img);
	mImgs.emplace_back(Data.mHelp4Img);
	mImgs.emplace_back(Data.mHelp5Img);
}
