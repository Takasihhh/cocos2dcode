# 
值传递 or 引用传递
值传递：只需要值就用值传递
引用传递：关心引用的对象

#include "Player.h"


Player* Player::create(const std::string& filename)//重写create函数
{
	Player *sprite = new (std::nothrow) Player();
	if (sprite && sprite->initWithFile(filename))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

bool Player::initPos(float x, float y)//初始化人物位置
{

	this->setPosition(x, y);

	this->setAnchorPoint(Vec2(0, 0));
	this->setScale(70 / 96.0);


	return true;
}

void Player::playAni(PLAYERDIR dir)//人物动画的实现
{
	
	Animation *ani = Animation::create();
	//1 上  2 下 3 左 4 右
	char * frameName = "player/PlayerDown_";
	switch (dir)
	{
	case PLAYERDIR::UP:
		frameName = "player/PlayerUp_";
		break;
	case PLAYERDIR::DWON:
		"player/PlayerDown_";
		break;
	case PLAYERDIR::LEFT:
		this->setFlippedX(false);
		frameName = "player/PlayerLeft_";
		break;
	case PLAYERDIR::RIGHT:
		this->setFlippedX(true);
		frameName = "player/PlayerLeft_";
		break;
	default:
		break;
	}
	for (int i = 0; i < 4; i++){
		char szName[128] = {};
		sprintf(szName, "%s%d.png", frameName, i);
		ani->addSpriteFrameWithFileName(szName);
	}
	ani->setDelayPerUnit(0.12f);
	auto act = RepeatForever::create(Animate::create(ani));
	this->stopAllActions();	
	this->runAction(act);


}


void Player::move(PLAYERDIR dir){//人物的移动
	Point * MOVE=nullptr;
	auto moveDis = Vec2(0, 0);
	switch (dir)
	{
	case UP:
		moveDis.y = 70;
		break;
	case DWON:
		moveDis.y = -70;
		break;
	case LEFT:
		moveDis.x = -70;
		break;
	case RIGHT:
		moveDis.x = 70;
		break;
	default:
		break;
	}

		auto moveby = MoveBy::create(0.1f,moveDis);
		moveby->setTag(01);

		if (this->getActionByTag(01))
		{

		}
    else
  {
		this->playAni(dir);
		this->runAction(moveby);
   }


}


