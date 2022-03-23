# Cocos2d

### Cocos2d动作系统

##### 1.瞬时动作(ActionInstant)

```c++
(1)Hide 隐藏
    auto hide = Hide：：create();
(2)show 显示
    auto show =show::create();
(3)place 放置
    auto place = Place::create(vec2(0，0)); 
(4)auto toggleVisbility = ToggleVisbility::create(); 
(5)auto fipX = FlipX::create(bool x); 
(6)auto fipY = FlipY::create(bool x); 
(8)node->runaction(动作指针)
    
```

##### 2.可持续动作【间隔动作】(ActionInterval)

```c++
(1)FadeTo
1.FadeIn 淡入
auto fadein =FadeIn::create(float d);
2.FadeOut 淡出
auto fadeout =Fadeout::create(float d);
(2)ScaleTo 放大到多少倍
auto scaleto =ScaleTo::create(时间，倍数);
(3)ScaleBy 放大了多少倍
 auto scaleby =ScaleBy::create(时间，倍数);
(4)Blink
 auto blink =Blink::create(持续时间，闪烁次数);
(5)MoveTO 移动到那个点
 auto movetO =MoveTO::create(坐标);
(6)MoveBy 移动一段向量距离
 auto moveby =MoveBy::create(坐标);
```

##### 3.组合动作

```
参数表末尾要加NULL值

auto seq =S0equence ::create(...Null);


```

##### 4.回调函数

```
(7)auto callFunc = CallFunc::create(const std::function<void()>& func); 
```

### Cocos人物系统

##### 1.人物类

```c++
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



```

##### 2.碰撞检测

```c++
bool tmxLayer::crashtest(Node* obj)
//碰撞检测函数

{
	float xDis = player1->getPositionX() - obj->getPositionX();
	float yDis = player1->getPositionY() - obj->getPositionY();
	
	
	if (obj != NULL)
	{

		if (abs(xDis) < (LENGTH / 2) && abs(yDis) < (LENGTH / 2))
		{
			return true;
		}
	else
		return false;
	}
}
void tmxLayer::update(float dt)//
{
	CCLOG("time%f", dt);
	if (crashtest(treemon1))
	{
		CCLOG("撞到树怪了");

	tmxLayer::init();

	}
}

再调用schedulepdate进行每帧检测

```

