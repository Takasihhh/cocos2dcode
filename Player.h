#ifndef _PLAYER_H_
#define _PLAYER_H_

#include"cocos2d.h"
using namespace cocos2d;

enum PLAYERDIR
{
	UP,
	DWON,
	LEFT,
    RIGHT


};


class Player :public Sprite
{

public:

	static Player* create(const std::string& filename);

	bool initPos(float x, float y);



	float x, y;

	void playAni(PLAYERDIR dir);
	void Player::move(PLAYERDIR dir);


};







#endif