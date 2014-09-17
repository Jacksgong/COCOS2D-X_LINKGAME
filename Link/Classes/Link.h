#ifndef __LINK_H__
#define __LINK_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CCMutableArray.h"
#include <vector>
#include "ClickNode.h"
//自定义界面长宽
const float DIYW = 700;
const float DIYH = 600;
/*extern float DIYW,DIYH;*/
//获得图片q0.png-q14.png并进行从0-13编号
//保存连连看图片的二维数组
//单张图片长宽(PicLen、PicWid)、连连看中图片半数(PicNum)(1<x<28)、消除一对所得分数(PerSco)等具体数值保存在根目录下的Setting.xml,并受其影响.
//如果大于14将重复加载从0开始。
//需要函数：
//1.初始化布置场景
// 1.1 随机场景
//  1.1.1 随机二维数组中的值（0-PicNum)
//  1.1.2 根据随机出来的二维数组的值布置图片布局
// 1.2 从Setting.xml中比对数据得到对应数值
//2.判断是否消除
// 2.1 获得用户点击的两张图片对应的编号，返回判断的值
//  2.1.1 获得用户点击图片的坐标以此从排列中得到对应序号
//   2.1.1.1 判断是否是在图片区域点击
//3.得分每消除一个得到对应分数
// 3.1加载数字图片，并显示于屏幕右上角，默认是0，没消除一个累加PerSco分数
//  3.1.1加载图片，并由数组分配图片域
//4.加载声音
// 4.1消除时，播放对应声音connect_effect.mp3
//  4.1.1事先对声音文件进行预加载，并随时调用播放
//5.左下角显示重新再来与退出游戏
// 5.1点击重新再来，从1开始，并进行内存清楚
// 5.2点击退出游戏，关闭Layer
//6.成功画面
// 6.1显示“恭喜您本次游戏得分：xxx”

class Link : public cocos2d::CCLayer,public cocos2d::CCTargetedTouchDelegate
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  

    // there's no 'id' in cpp, so we recommand to return the exactly class pointer
    static cocos2d::CCScene* scene();
    
    // a selector callback
    virtual void menuCloseCallback(CCObject* pSender);

    // implement the "static node()" method manually
    LAYER_NODE_FUNC(Link);

	//获得xml中的数值到Link
	void GetXmlVal();
	//随机得到二维数组
	bool RanArr();
	//每帧更新
	void update(cocos2d::ccTime dt); 
	//得到m_nPicNum张图片到m_pAllPic中
	void GetAllPic();
	Link();
	//用作CCMutableArray的二维
	//返回界面长宽
	/*void GetInterfaceWL();*/
	//重载AppDelegate的initInstance();来设置界面大小
	/*virtual bool initInstance();*/
	//右上角显示的分数
	void ShowSco(int Sco);
	//获得用户点击屏幕图片的对应二维坐标
	void GetTouchXY(int &nTouchX,int &nTouchY);

	//触摸
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	/*virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);*/
	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();
	// 判断是否在全体图片区域内
	bool containsTouchLocation(cocos2d::CCTouch* touch);
	//得到全体图片围成的区域
	cocos2d::CCRect rect();
// 	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
// 	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
// 	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
// 	virtual void ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent);
	//闪动二维坐标为x,y的精灵
	void FliSpri(const int x,const int y);
	//获得点击的第一个与第二个的坐标
	void GetClick(const int x,const int y,int IsFir);
	//根据两坐标判断是否可以进行消除
	bool IsSamePic()const;
	//判断一条通x或通y的直线上是否在范围(a,b)之间所有都为15或a==b或相差1
	//FixXY为另一个固定轴
	//RgtXY =0为x轴范围.RgtXY =1为y轴范围
	//Rgt用于处理bug（第三种情况)
	bool IsEmptyLine(const int a,const int b,const int FixXY,const int RgtXY = 0,const int Rgt = 0)const;
private:
	//单张图片长宽
	int m_nPicSize;
	//需加载图片数
	int m_nPicNum;
	//排列横向个数(m_nHorNum = m_nPicNum*m_nReNum / int
	int m_nHorNum;
	//分数/每消一次
	int m_nPerSco;
	//重复次数（此值只为偶数)
	int m_nReNum;
	//保存所有图片对应从0-m_nPicNum
	std::vector<cocos2d::CCSprite*>* m_pAllPic;
	//保存分数精灵
	std::vector<cocos2d::CCSprite*>* pScoSprite;
	//随机二维数组
	int **ppRanArr;
	//用户触摸屏幕时候获得的XY坐标。
	cocos2d::CCPoint GetXY;
// 	//保存重复的编号数组
// 	int *IsReNum;
	//点击获得的第一个记录精灵
	ClickNode m_FirClick;
	//点击获得的第二个精灵
	ClickNode m_SecClick;
	//当前xy
	int m_x;
	int m_y;
	//前一个xy
	int m_x1;
	int m_y1;
	//是否第一个已经获得
	int IsFirGo;
};

#endif  // __LINK_H__