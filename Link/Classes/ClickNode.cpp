#include "ClickNode.h"

ClickNode::ClickNode()
{
	x = 0;
	y = 0;
	pClickPic =NULL;
}
ClickNode::~ClickNode()
{
	if (NULL != pClickPic)
	{
		pClickPic->release();
	}
}