#include "cocos2d.h"

class ClickNode
{
public:
	ClickNode();
	~ClickNode();
	/*ClickNode& operator=(const)*/
public:
	//点击的图片的坐标x与y
	int x;
	int y;
	cocos2d::CCSprite* pClickPic;
};