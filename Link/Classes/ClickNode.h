#include "cocos2d.h"

class ClickNode
{
public:
	ClickNode();
	~ClickNode();
	/*ClickNode& operator=(const)*/
public:
	//�����ͼƬ������x��y
	int x;
	int y;
	cocos2d::CCSprite* pClickPic;
};