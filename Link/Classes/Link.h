#ifndef __LINK_H__
#define __LINK_H__

#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include "CCMutableArray.h"
#include <vector>
#include "ClickNode.h"
//�Զ�����泤��
const float DIYW = 700;
const float DIYH = 600;
/*extern float DIYW,DIYH;*/
//���ͼƬq0.png-q14.png�����д�0-13���
//����������ͼƬ�Ķ�ά����
//����ͼƬ����(PicLen��PicWid)����������ͼƬ����(PicNum)(1<x<28)������һ�����÷���(PerSco)�Ⱦ�����ֵ�����ڸ�Ŀ¼�µ�Setting.xml,������Ӱ��.
//�������14���ظ����ش�0��ʼ��
//��Ҫ������
//1.��ʼ�����ó���
// 1.1 �������
//  1.1.1 �����ά�����е�ֵ��0-PicNum)
//  1.1.2 ������������Ķ�ά�����ֵ����ͼƬ����
// 1.2 ��Setting.xml�бȶ����ݵõ���Ӧ��ֵ
//2.�ж��Ƿ�����
// 2.1 ����û����������ͼƬ��Ӧ�ı�ţ������жϵ�ֵ
//  2.1.1 ����û����ͼƬ�������Դ˴������еõ���Ӧ���
//   2.1.1.1 �ж��Ƿ�����ͼƬ������
//3.�÷�ÿ����һ���õ���Ӧ����
// 3.1��������ͼƬ������ʾ����Ļ���Ͻǣ�Ĭ����0��û����һ���ۼ�PerSco����
//  3.1.1����ͼƬ�������������ͼƬ��
//4.��������
// 4.1����ʱ�����Ŷ�Ӧ����connect_effect.mp3
//  4.1.1���ȶ������ļ�����Ԥ���أ�����ʱ���ò���
//5.���½���ʾ�����������˳���Ϸ
// 5.1���������������1��ʼ���������ڴ����
// 5.2����˳���Ϸ���ر�Layer
//6.�ɹ�����
// 6.1��ʾ����ϲ��������Ϸ�÷֣�xxx��

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

	//���xml�е���ֵ��Link
	void GetXmlVal();
	//����õ���ά����
	bool RanArr();
	//ÿ֡����
	void update(cocos2d::ccTime dt); 
	//�õ�m_nPicNum��ͼƬ��m_pAllPic��
	void GetAllPic();
	Link();
	//����CCMutableArray�Ķ�ά
	//���ؽ��泤��
	/*void GetInterfaceWL();*/
	//����AppDelegate��initInstance();�����ý����С
	/*virtual bool initInstance();*/
	//���Ͻ���ʾ�ķ���
	void ShowSco(int Sco);
	//����û������ĻͼƬ�Ķ�Ӧ��ά����
	void GetTouchXY(int &nTouchX,int &nTouchY);

	//����
	virtual void ccTouchesEnded(cocos2d::CCSet *pTouches, cocos2d::CCEvent *pEvent);
	/*virtual bool ccTouchBegan(cocos2d::CCTouch* touch, cocos2d::CCEvent* event);*/
	virtual void touchDelegateRetain();
	virtual void touchDelegateRelease();
	// �ж��Ƿ���ȫ��ͼƬ������
	bool containsTouchLocation(cocos2d::CCTouch* touch);
	//�õ�ȫ��ͼƬΧ�ɵ�����
	cocos2d::CCRect rect();
// 	virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);
// 	virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
// 	virtual bool ccTouchBegan(CCTouch *pTouch,CCEvent *pEvent);
// 	virtual void ccTouchEnded(CCTouch *pTouch,CCEvent *pEvent);
	//������ά����Ϊx,y�ľ���
	void FliSpri(const int x,const int y);
	//��õ���ĵ�һ����ڶ���������
	void GetClick(const int x,const int y,int IsFir);
	//�����������ж��Ƿ���Խ�������
	bool IsSamePic()const;
	//�ж�һ��ͨx��ͨy��ֱ�����Ƿ��ڷ�Χ(a,b)֮�����ж�Ϊ15��a==b�����1
	//FixXYΪ��һ���̶���
	//RgtXY =0Ϊx�᷶Χ.RgtXY =1Ϊy�᷶Χ
	//Rgt���ڴ���bug�����������)
	bool IsEmptyLine(const int a,const int b,const int FixXY,const int RgtXY = 0,const int Rgt = 0)const;
private:
	//����ͼƬ����
	int m_nPicSize;
	//�����ͼƬ��
	int m_nPicNum;
	//���к������(m_nHorNum = m_nPicNum*m_nReNum / int
	int m_nHorNum;
	//����/ÿ��һ��
	int m_nPerSco;
	//�ظ���������ֵֻΪż��)
	int m_nReNum;
	//��������ͼƬ��Ӧ��0-m_nPicNum
	std::vector<cocos2d::CCSprite*>* m_pAllPic;
	//�����������
	std::vector<cocos2d::CCSprite*>* pScoSprite;
	//�����ά����
	int **ppRanArr;
	//�û�������Ļʱ���õ�XY���ꡣ
	cocos2d::CCPoint GetXY;
// 	//�����ظ��ı������
// 	int *IsReNum;
	//�����õĵ�һ����¼����
	ClickNode m_FirClick;
	//�����õĵڶ�������
	ClickNode m_SecClick;
	//��ǰxy
	int m_x;
	int m_y;
	//ǰһ��xy
	int m_x1;
	int m_y1;
	//�Ƿ��һ���Ѿ����
	int IsFirGo;
};

#endif  // __LINK_H__