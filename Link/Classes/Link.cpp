#include "Link.h"
#include "Other.h"

#include <string>
#include "tinyxml.h"
#include "tinystr.h"
#include <ctime>
#include <cstdlib>


const string XML_FILE ="Setting.xml";


using namespace cocos2d;

CCScene* Link::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::node();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		Link *layer = Link::node();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool Link::init()
{
	bool bRet = false;
	do 
	{
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////

		CC_BREAK_IF(! CCLayer::init());

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		this->setIsTouchEnabled(true);
		/*CCDirector::sharedDirector()->to->getTouchDispatcher()->addTargetedDelegate(this, 0, true);*/


		//添加背景
		CCSprite* pBg = CCSprite::spriteWithFile("backgroud.png");
		pBg->setPosition(ccp(size.width/2,size.height/2));
		pBg->setScaleX(size.width/pBg->getContentSize().width);
		pBg->setScaleY(size.height/pBg->getContentSize().height);
		addChild(pBg,-1);


		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::itemFromNormalImage(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(Link::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);

		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::menuWithItems(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);

		// Add the menu to Link layer as a child layer.
		this->addChild(pMenu, 1);

		// 2. Add a label shows "Hello World".

		// Create a label and initialize with string "Hello World".
		// 		CCLabelTTF* pLabel = CCLabelTTF::labelWithString(" ", "Thonburi", 64);
		// 		CC_BREAK_IF(! pLabel);
		// 
		// 		// Get window size and place the label upper. 
		// 		pLabel->setPosition(ccp(size.width / 2, size.height - 20));
		// 
		// 		// Add the label to Link layer as a child layer.
		// 		this->addChild(pLabel, 1);

		// 3. Add add a splash screen, show the cocos2d splash image.
		//         CCSprite* pSprite = CCSprite::spriteWithFile("q0.png");
		//         CC_BREAK_IF(! pSprite);
		// 
		//         // Place the sprite on the center of the screen
		//         pSprite->setPosition(ccp(size.width/2, size.height/2));
		// 
		//         // Add the sprite to Link layer as a child layer.
		//         this->addChild(pSprite, 0);

		bRet = true;
	} while (0);

	return bRet;
}

void Link::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	CCDirector::sharedDirector()->end();
}



//***********************************
// 生成二维
// CCSprite Link::GetMArray(int i, int j)
// {
// 	return m_pAllPic(i*j + j);
// }
//生成随机数组
bool Link::RanArr()
{
	if ((m_nPicNum*m_nReNum)%m_nHorNum != 0)
	{
		CCLOG("Error m_nHorNum");
		return false;
	}
	int nVer = (m_nPicNum*m_nReNum)/m_nHorNum; 
	ppRanArr = new int* [nVer+2];
	for (int i=0;i<nVer+2;i++)
	{
		ppRanArr[i] = new int [m_nHorNum+2];
	}

	//最外圈填充上15
	for (int j=0;j<nVer+2;j++)
	{
		ppRanArr[j][0] = 15;
		ppRanArr[j][m_nHorNum+1] = 15;
	}
	for (int j=0;j<m_nHorNum+2;j++)
	{
		ppRanArr[0][j] = 15;
		ppRanArr[nVer + 1][j] = 15;
	}
	//15表示空
	//从1-
	//随机到一个由
	//进行随机分配从0-m_nPicNum

	int NeedRanNum;
	int* NumTim;
	if (m_nPicNum > 14)
	{
		//此处大于14时随机数从0<=x<14
		//需注意每个数字只能出现
		//每张图片出现的次数
		NumTim = new int[14];
		for (int k=0;k<14;k++)
		{
			NumTim[k] = 0;
		}
		NeedRanNum = 14;
	}else
	{
		NumTim = new int[m_nPicNum];
		for (int k=0;k<m_nPicNum;k++)
		{
			NumTim[k] = 0;
		}
		NeedRanNum = m_nPicNum;
	}

	srand(unsigned(time(0)));
	for (int j=1;j<nVer+1;j++)
	{
		for (int k=1;k<m_nHorNum+1;k++)
		{
			int RandNum = int(RanDom(0,NeedRanNum));
			while(NumTim[RandNum] >= 4)
			{
				RandNum = int(RanDom(0,NeedRanNum));
			}
			ppRanArr[j][k] = RandNum;
			NumTim[RandNum]++;
		}
	}
	return true;
}



//读取Xml文件
void Link::GetXmlVal()
{

	TiXmlDocument *pDoc = new TiXmlDocument(XML_FILE);
	pDoc->LoadFile();
	TiXmlElement *Root = pDoc->RootElement();  //根，<Rank>
	TiXmlElement *pFirE = Root->FirstChildElement(); //叶子节点
	while(NULL != pFirE)
	{
		if (pFirE->ValueStr().compare("PicSize") == 0)
		{
			m_nPicSize = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("PicNum") == 0)
		{
			m_nPicNum = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("HorNum") == 0)
		{
			m_nHorNum = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("PerSco") == 0)
		{
			m_nPerSco = atoi(pFirE->FirstChild()->Value());
		}else if (pFirE->ValueStr().compare("ReNum") == 0)
		{
			m_nReNum = atoi(pFirE->FirstChild()->Value());
		}else
		{
			CCLOG("Error Input xml.");
		}
		pFirE = pFirE->NextSiblingElement();		
	}
}


//得到m_nPicNum张图片到m_pAllPic中
void Link::GetAllPic()
{
	//用于存储已经排列好的精灵
	CCMutableArray<CCSprite*>* FulSprite = new CCMutableArray<CCSprite*> (m_nPicNum*m_nReNum);
	FulSprite->autorelease();
	CCSize size = CCDirector::sharedDirector()->getWinSize();

	//循环加载到图片序列
	char *pTrName = new char[40];

	for (int i=0;i<m_nPicNum;i++)
	{
		sprintf(pTrName,"q%d.png",i);
		for (int j=0;j<m_nReNum;j++)
		{
			CCSprite* pPic = CCSprite::spriteWithFile(pTrName);
			/*addChild(pPic);*/
			CC_BREAK_IF(! pPic);
			m_pAllPic->push_back(pPic);
			pPic->setPosition(ccp(size.width/2,size.height/2));

		}
		// 		m_pAllPic->getObjectAtIndex(i)->setPosition(ccp(100+i*30,200));
		// 		addChild(m_pAllPic->getLastObject());

	}

	int *IsRe = new int [m_nPicNum];
	/*IsReNum = new int [m_nPicNum*m_nReNum];*/
	int nVer = (m_nPicNum*m_nReNum)/m_nHorNum; 
	//设置居中
	float ForMidleIntW = (size.width - ((m_nHorNum+1)*m_nPicSize))/2;
	float ForMidleIntH = (size.height - ((nVer+1)*m_nPicSize))/2;
	for (int i=0;i<m_nPicNum;i++)
	{
		IsRe[i] = 0;
	}
	CCSprite* pPicUsed = NULL;
	for (int i=0;i<nVer;i++)
	{
		for (int j=0;j<m_nHorNum;j++)
		{
			pPicUsed = m_pAllPic->at(ppRanArr[i+1][j+1]*m_nReNum+IsRe[ppRanArr[i+1][j+1]]);
			FulSprite->addObject(m_pAllPic->at(ppRanArr[i+1][j+1]*m_nReNum+IsRe[ppRanArr[i+1][j+1]]));
			/*IsReNum[i*j+j] = IsRe[ppRanArr[i+1][j+1]];*/
			IsRe[ppRanArr[i+1][j+1]]++;
			if(NULL == pPicUsed)
			{
				int a = 0;
			}
			float PicScale = float(m_nPicSize)/128.0f;
			pPicUsed->setScale(PicScale);
			pPicUsed->setPosition(ccp(ForMidleIntW+m_nPicSize*(j+1),ForMidleIntH+m_nPicSize*(i+1)));
			
			//pPic->release();
		}
	}
	//将m_pAllPic重建为排列好的精灵
	m_pAllPic->clear();
	for (int i=0;i<nVer;i++)
	{
		for (int j=0;j<m_nHorNum;j++)
		{
			m_pAllPic->push_back(FulSprite->getObjectAtIndex(i*m_nHorNum+j));
		}
	}

	//为调试改变
	//显示放到这里
	for (int i=0;i<nVer;i++)
	{
		for (int j=0;j<m_nHorNum;j++)
		{
			pPicUsed = m_pAllPic->at(i*m_nHorNum + j);
// 			CCActionInterval* action;
// 			action = CCFadeOut::actionWithDuration(0.2);
// 			CCActionInterval* action_back = action->reverse();
// 			CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions( action, action_back, NULL ));
// 			/*CurSprite = m_pAllPic->at(12);*/
// 			pPicUsed->runAction( CCRepeat::actionWithAction(seq,1) );
			this->addChild(pPicUsed);

// 			//*************************调试**显示坐标
// 
// 			char* tmpts = new char[40];
// 			sprintf(tmpts,"%d",j);
// 			CCLabelTTF* pLabel = CCLabelTTF::labelWithString(tmpts, "Thonburi", 15);
// 			CC_BREAK_IF(! pLabel);
// 			pLabel->setPosition(ccp(ForMidleIntW+m_nPicSize*(j+1)+7,ForMidleIntH+m_nPicSize*(i+1)));
// 			this->addChild(pLabel,1);
// 
// 			char* tmpts1 = new char[40];
// 			sprintf(tmpts1,"%d",i);
// 			CCLabelTTF* pLabe2 = CCLabelTTF::labelWithString(tmpts1, "Thonburi", 15);
// 			CC_BREAK_IF(! pLabe2);
// 			pLabe2->setPosition(ccp(ForMidleIntW+m_nPicSize*(j+1)-7,ForMidleIntH+m_nPicSize*(i+1)));
// 			this->addChild(pLabe2,1);

		}
	}

}

Link::Link()
{
	GetXY.x = 0.0;
	GetXY.y = 0.0;
	pScoSprite = new std::vector<cocos2d::CCSprite*>;
	m_pAllPic = new std::vector<cocos2d::CCSprite*>;
	m_x = 0;
	m_y = 0;
	m_x1 = 0;
	m_y1 = 0;
	IsFirGo = 1;

	GetXmlVal();
	RanArr();
	GetAllPic();
	ShowSco(0);
	scheduleUpdate();
	/*FliSpri(1,5);*/
	/*	GetInterfaceWL();*/
	/*	UpDate();*/
	// 	CCSize size = CCDirector::sharedDirector()->getWinSize();
	// 
	// 	// 3. Add add a splash screen, show the cocos2d splash image.
	// 	CCSprite* pSprit = CCSprite::spriteWithFile("backgroud.png");
	// /*	CC_BREAK_IF(! pSprit);*/
	// 
	// 	// Place the sprite on the center of the screen
	// 	pSprit->setPosition(ccp(size.width/2, size.height/2));
	// 
	// 	// Add the sprite to Link layer as a child layer.
	// 	this->addChild(pSprit, 0);
}


//右上角显示的分数
void Link::ShowSco(int Sco)
{
	if (!pScoSprite->empty())
	{
		for (int i=0;i<pScoSprite->size();i++)
		{
			// 		if (pScoSprite->at(i) == "out_of_range")
			// 		{
			// 			int a =5;
			// 		}
			this->removeChild(pScoSprite->at(i),true);
		}
		pScoSprite->clear();
	}

	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCTexture2D *pScoTexture = CCTextureCache::sharedTextureCache()->addImage("fps_images.png");
	CCSpriteFrame *pAidSco =CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*2,25*0,18,25));
	// 	pSco0 = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*2,25*0,18,25));
	// 	pSco1 = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*3,25*0,18,25));
	// 	pSco2 = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*4,25*0,18,25));
	// 	pSco3 = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*5,25*0,18,25));
	// 	pSco4 = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*6,25*0,18,25));
	// 	pSco5 = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*7,25*0,18,25));
	// 	pSco6 = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*8,25*0,18,25));
	// 	pSco7 = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*9,25*0,18,25));
	// 	pSco8 = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*10,25*0,18,25));
	// 	pSco9 = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*11,25*0,18,25));

	// 	CCMutableArray<CCSpriteFrame *> *pScoArray = new CCMutableArray<CCSpriteFrame *>(10);
	// 	pScoArray->addObject(pSco0);
	// 	pScoArray->addObject(pSco1);
	// 	pScoArray->addObject(pSco2);
	// 	pScoArray->addObject(pSco3);
	// 	pScoArray->addObject(pSco4);
	// 	pScoArray->addObject(pSco5);
	// 	pScoArray->addObject(pSco6);
	// 	pScoArray->addObject(pSco7);
	// 	pScoArray->addObject(pSco8);
	// 	pScoArray->addObject(pSco9);
	/*CCSprite *pScoSprite = NULL;*/
	CCSprite* pAidSpr;
	if (Sco == 0)
	{
		pAidSpr = CCSprite::spriteWithSpriteFrame(pAidSco);
		pScoSprite->push_back(pAidSpr);
		pAidSpr->setPosition(ccp(size.width -25,size.height-25));
		addChild(pAidSpr);
	}else
	{
		int nCur = Sco%10; //当前获得的数值
		Sco/=10;
		for (int i=0;!(Sco<=0&&nCur<=0);nCur=Sco%10,Sco/=10,i++)
		{
			switch(nCur)
			{
			case 0:pAidSco = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16*2,25*0,18,25));break;
			case 1:pAidSco = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(15.5*3,25*0,18,25));break;
			case 2:pAidSco = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(15.5*4,25*0,18,25));break;
			case 3:pAidSco = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(15.5*5,25*0,18,25));break;
			case 4:pAidSco = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(15.7*6,25*0,18,25));break;
			case 5:pAidSco = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16*7,25*0,18,25));break;
			case 6:pAidSco = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*8,25*0,18,25));break;
			case 7:pAidSco = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*9,25*0,18,25));break;
			case 8:pAidSco = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*10,25*0,18,25));break;
			case 9:pAidSco = CCSpriteFrame::frameWithTexture(pScoTexture,cocos2d::CCRect(16.2*11,25*0,18,25));break;
			default:
				break;
			}
			pAidSpr = CCSprite::spriteWithSpriteFrame(pAidSco);
			pScoSprite->push_back(pAidSpr);
			pAidSpr->setPosition(ccp(size.width -(25+16.2*i),size.height-25));
			addChild(pAidSpr);
		}
	}

}
//得到全体图片围成的区域
CCRect Link::rect()
{
	//整个连连看图片的区域。
	int nVal = m_nReNum*m_nPicNum/m_nHorNum;
	return CCRectMake(-m_nHorNum*m_nPicSize / 2, -nVal*m_nPicSize / 2, m_nHorNum*m_nPicSize, nVal*m_nPicSize);
}
// 判断是否在全体图片区域内
bool Link::containsTouchLocation(CCTouch* touch)
{
	return CCRect::CCRectContainsPoint(rect(), convertTouchToNodeSpaceAR(touch));
}

//虚拟触摸
void Link::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	/*if ( !containsTouchLocation(touch) ) return false;*/
	CCSetIterator it = pTouches->begin();
	CCTouch* pTouch = (CCTouch*)(*it);

	CCPoint touchLocation = pTouch->locationInView(pTouch->view());
	touchLocation = CCDirector::sharedDirector()->convertToGL(touchLocation);
	GetXY = touchLocation;
}

// bool Link::ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event)
// {
// 	return true;
// }

//获得用户点击屏幕图片的对应二维坐标
void Link::GetTouchXY(int &nTouchX,int &nTouchY)
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	//边距
	int nVer = (m_nPicNum*m_nReNum)/m_nHorNum; 
	float ForMidleIntW = (size.width - ((m_nHorNum+1)*m_nPicSize))/2;
	float ForMidleIntH = (size.height - ((nVer+1)*m_nPicSize))/2;
	if ((GetXY.x <ForMidleIntW) || (GetXY.x > (size.width - ForMidleIntW)) || (GetXY.y < ForMidleIntH) || (GetXY.y > (size.height - ForMidleIntH)))
	{
		nTouchX = 0;
		nTouchY = 0;
	}else
	{
		nTouchX =(GetXY.x - ForMidleIntW + m_nPicSize/2) / m_nPicSize;
		nTouchY = (GetXY.y - ForMidleIntH + m_nPicSize/2) / m_nPicSize;
	}

}

//每帧更新
void Link::update(ccTime dt)
{

	GetTouchXY(m_x,m_y);
	ShowSco(m_x);
	/*FliSpri(x,y);*/
	if ((m_x1 != m_x||m_y1 != m_y)&&ppRanArr[m_y][m_x]!=15)
	{
		if (!(m_x<=0||m_x>m_nHorNum||m_y<=0||(m_y>(m_nPicNum*m_nReNum)/m_nHorNum)))
		{
			if (IsFirGo ==1)
			{
				GetClick(m_x,m_y,IsFirGo);
				m_x1 = m_x;
				m_y1 = m_y;
				IsFirGo = 0;
			}
			else
			{
				if (!(m_x1 == m_x&&m_y1 == m_y))
				{
					m_x1 = m_x;
					m_y1 = m_y;
					GetClick(m_x,m_y,IsFirGo);
					//得到第二个有效点击
					if (ppRanArr[m_FirClick.y][m_FirClick.x] == ppRanArr[m_SecClick.y][m_SecClick.x])
					{
						if (IsSamePic())
						{
							ppRanArr[m_FirClick.y][m_FirClick.x] = 15;
							ppRanArr[m_SecClick.y][m_SecClick.x] = 15;
							this->removeChild(m_FirClick.pClickPic,true);
							this->removeChild(m_SecClick.pClickPic,true);
							m_FirClick.pClickPic = NULL;
							m_FirClick.x = 0;
							m_FirClick.y = 0;
							m_SecClick.pClickPic = NULL;
							m_SecClick.x = 0;
							m_SecClick.y = 0;
						}
					}
					if (NULL != m_SecClick.pClickPic)
					{
						m_FirClick.pClickPic->stopAllActions();
						m_SecClick.pClickPic->stopAllActions();
						m_FirClick.pClickPic->setOpacity(255);
						/*m_FirClick.pClickPic->setIsVisible(false);*/
						/*seq->release();*/
					}
					IsFirGo = 1;
				}
				else
				{
					m_FirClick.pClickPic->stopAllActions();
					m_SecClick.pClickPic->stopAllActions();
					m_FirClick.pClickPic->setOpacity(255);
					/*seq->release();*/

					IsFirGo = 1;
				}
			}
		}
	}
	

// 	int x2=x,y2=y;
// 	while((x2 == x)&&(y2 == y))
// 	{
// 		GetTouchXY(x2,y2);
// 	}
// 	if ((x2 == 0)&&(y2 == 0))
// 	{
// 		FliSpri(x,y,1);
// 		m_FirClick.x = 0;
// 		m_FirClick.y = 0;
// 		m_FirClick.pClickPic = NULL;
// 	}else
// 	{
// 		m_SecClick.x = x2;
// 		m_SecClick.y = y2;
// 		m_SecClick.pClickPic = m_pAllPic->at((y2-1)*m_nHorNum+(x2-1));
// 	}
}

void Link::touchDelegateRetain()
{
	this->retain();
}

void Link::touchDelegateRelease()
{
	this->release();
}

//闪动二维坐标为x,y的精灵
//IsStop =1停止，0，开始
void Link::FliSpri(const int x,const int y)
{

	if (!(x<=0||x>m_nHorNum||y<=0||(y>(m_nPicNum*m_nReNum)/m_nHorNum)))
	{
		CCActionInterval* action;
		action = CCFadeOut::actionWithDuration(0.5);
		CCActionInterval* action_back = action->reverse();
		CCActionInterval* seq = (CCActionInterval*)(CCSequence::actions( action, action_back, NULL ));
		CCSprite* CurSprite;
		CurSprite = m_pAllPic->at((y-1)*m_nHorNum+(x-1));
		/*CurSprite = m_pAllPic->at(12);*/
		CurSprite->runAction( CCRepeatForever::actionWithAction(seq) );
	}
}

//获得点击的第一个与第二个的坐标
//IsFir为1为第一点 为0为第二点
void Link::GetClick(const int x,const int y,int IsFir)
{
	if (IsFir == 1)
	{
		m_FirClick.x = 0;
		m_FirClick.y = 0;
		m_FirClick.pClickPic = NULL;
		m_SecClick.x = 0;
		m_SecClick.y = 0;
		m_SecClick.pClickPic = NULL;

		if (!(x<=0||x>m_nHorNum||y<=0||(y>(m_nPicNum*m_nReNum)/m_nHorNum)))
		{
			m_FirClick.x = x;
			m_FirClick.y = y;
			m_FirClick.pClickPic = m_pAllPic->at((y-1)*m_nHorNum+(x-1));
			FliSpri(x,y);
		}
	}
	else
	{
		m_SecClick.x = 0;
		m_SecClick.y = 0;
		m_SecClick.pClickPic = NULL;

		if (!(x<=0||x>m_nHorNum||y<=0||(y>(m_nPicNum*m_nReNum)/m_nHorNum)))
		{
			m_SecClick.x = x;
			m_SecClick.y = y;
			m_SecClick.pClickPic = m_pAllPic->at((y-1)*m_nHorNum+(x-1));
			FliSpri(x,y);
		}
	}
}


//根据两坐标判断是否可以进行消除
bool Link::IsSamePic()const
{
	//判断是否已经得到了第二个点击的精灵

	//判断有以下几种情况：
	//1.x、y轴水平可消
	//2.通过(x1,y2)或(x2,y1)一点可以分别相连可消
	//3.通过((z,y1)与(z,y2)）或((x1,z)与(x2,z))两点作为转点相连可消
	//********第一种与第二种皆为第三种的特殊情况*********
	if (m_SecClick.x !=0)
	{
		int x1 = m_FirClick.x,
			y1 = m_FirClick.y,
			x2 = m_SecClick.x,
			y2 = m_SecClick.y,
			z = 0;
		//处理特殊情况
		//两个中只要有一个四周都有不是自己的，直接false
		int nFir = ppRanArr[m_FirClick.y][m_FirClick.x];
		int nUp = ppRanArr[m_FirClick.y+1][m_FirClick.x];
		int nDown = ppRanArr[m_FirClick.y-1][m_FirClick.x];
		int nLeft = ppRanArr[m_FirClick.y][m_FirClick.x-1];
		int nRight = ppRanArr[m_FirClick.y][m_FirClick.x+1];
		if (nUp!=nFir&&nUp!=15&&nDown!=nFir&&nDown!=15)
		{
			if (nLeft!=nFir&&nLeft!=15&&nRight!=nFir&&nRight!=15)
			{
				return false;
			}
		}
		int nSec = ppRanArr[m_SecClick.y][m_SecClick.x];
		nUp = ppRanArr[m_SecClick.y+1][m_SecClick.x];
		nDown = ppRanArr[m_SecClick.y-1][m_SecClick.x];
		nLeft = ppRanArr[m_SecClick.y][m_SecClick.x-1];
		nRight = ppRanArr[m_SecClick.y][m_SecClick.x+1];
		if (nUp!=nSec&&nUp!=15&&nDown!=nSec&&nDown!=15)
		{
			if (nLeft!=nSec&&nLeft!=15&&nRight!=nSec&&nRight!=15)
			{
				return false;
			}
		}
		//第一种特殊情况
		if ((x1 == x2&&IsEmptyLine(y1,y2,x1,1))||(y1 == y2&&IsEmptyLine(x1,x2,y1,0)))
		{
			return true;
		}
		//第二种情况
		if (IsEmptyLine(x1,x2,y2,0)&&IsEmptyLine(y1,y2,x1,1))
		{
			//折点必须为空
			if (ppRanArr[y2][x1] == 15)
			{
				return true;
			}
		}
		if (IsEmptyLine(x1,x2,y1,0)&&IsEmptyLine(y1,y2,x2,1))
		{
			//折点必须为空
			if (ppRanArr[x2][y1] == 15)
			{
				return true;
			}
		}
		//第三种情况
		for (int i=0;i<=m_nHorNum+1;i++)
		{
			if (i == x2||i == x1||y1 == y2)
			{
				continue;
			}
			if (IsEmptyLine(i,x2,y2,0,1)&&IsEmptyLine(y1,y2,i,1,1)&&IsEmptyLine(i,x1,y1,0,1))
			{
				if (ppRanArr[y2][i] == 15&&ppRanArr[y1][i] == 15)
				{
					return true;
				}
			}
		}
		for (int i=0;i<=(m_nPicNum*m_nReNum)/m_nHorNum+1;i++)
		{
			if (i == y1||i == y2 || x1 == x2)
			{
				continue;
			}
			if (IsEmptyLine(i,y1,x1,1,1)&&IsEmptyLine(x1,x2,i,0,1)&&IsEmptyLine(i,y2,x2,1,1))
			{
				if (ppRanArr[i][x1] == 15|| ppRanArr[i][x2] == 15)
				{
					return true;
				}
			}
		}
	}
	return false;
}

// int min(const int a,const int b)
// {
// 	return a:b?a<b;
// }
//判断一条通x或通y的直线上是否在范围(a,b)之间所有都为15或a==b或相差1
//RgtXY =0为x轴范围.RgtXY =1为y轴范围
bool Link::IsEmptyLine(const int a,const int b,const int FixXY,const int RgtXY,const int Rgt)const
{
	if ((a == b||a == b+1 || b == a+1)&&Rgt == 0)
	{
		return true;
	}
	int Min = a<b?a:b;
	int Max = a>b?a:b;
	for (int i = Min+1;i < Max;i++)
	{
		if (RgtXY == 0&&ppRanArr[FixXY][i] != 15)
		{
			return false;
		}
		if (RgtXY == 1&&ppRanArr[i][FixXY] != 15)
		{
			return false;
		}
	}
	return true;
		
}