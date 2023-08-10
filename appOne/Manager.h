#pragma once
class Manager
{
public:
	Manager(class Game* game);
	virtual ~Manager();
	virtual void Update() {};
	virtual void ProcessInput() {};
protected:
	class Game* mGame;
};

