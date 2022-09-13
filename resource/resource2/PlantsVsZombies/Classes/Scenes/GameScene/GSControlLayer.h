/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.1.28
 *Email: 2117610943@qq.com
 */

#pragma once
#include <random>

#include "cocos2d.h"
#include "Based/GlobalVariable.h"

using namespace cocos2d;

class ZombiesAppearControl;
class GSGameEndLayer;
class OpenLevelData;
enum class ZombiesType;
enum class PlantsType;


/* ��Ϸ��ͼ */
struct GameMapInformation
{
	GameMapInformation();
	int plantsMap[5][9];               /* ֲ����ֲ��ͼ */
	unsigned int rowNumbers;           /* ���� */
	unsigned int columnNumbers;        /* ���� */
};

class GSControlLayer :public Layer
{
public:
	CREATE_FUNC(GSControlLayer);
	void addLayer(Node* node, const int order, const string& name) { node->addChild(this, order, name); }
	static void setPlantMapCanPlant(const unsigned int colum, const unsigned int row);
	void updateFlag();

CC_CONSTRUCTOR_ACCESS:
	GSControlLayer();
	~GSControlLayer();
	virtual bool init();

protected:
	virtual void judgeLevelIsFinished();                                                /* �жϹؿ��Ƿ���� */
	virtual void zombiesComeTiming();                                                   /* ��ʬ���ּ�ʱ */
	virtual void createZombies();                                                       /* ������ʬ */
	virtual bool controlRefurbishZombies();                                             /* ���ƽ�ʬˢ�� */
	virtual void controlRefurbishMusicAndText();                                        /* �������������ֵ�ˢ��*/

private:
	void createSchedule();                                                              /* ������ʱ�� */
	void controlCardEnabled();                                                          /* ���ƿ����Ƿ���� */
	void calculatePlantPosition();                                                      /* ����ֲ����ֲλ�� */
	void createMouseListener();                                                         /* ������� */
	void mouseMoveControl();                                                            /* ����ƶ����� */
	void mouseDownControl(EventMouse* eventmouse = nullptr);                            /* ��갴�¿��� */
	void createPlantsCardListener();                                                    /* ����ֲ�￨�Ƽ��� */
	void selectPlantsPreviewImage();                                                    /* ѡ��ֲ��Ԥ��ͼƬ */
	void createPreviewPlants();                                                         /* ����Ԥ��ֲ�� */
	bool judgeMousePositionIsInMap();                                                   /* �ж��������λ�Ƿ��ڵ�ͼ�� */
	bool judgeMousePositionIsCanPlant();                                                /* �ж��������λ�Ƿ������ֲֲ�� */
	bool judgeMousePositionHavePlant();                                                 /* �ж��������λ�Ƿ���ֲ�� */
	void removePreviewPlant();                                                          /* �Ƴ�Ԥ��ֲ�� */
	void removeShovel();                                                                /* �Ƴ����� */
	void recoveryPlantsColor();                                                         /* �ָ�ֲ����ɫ */
  	void setGameEnd();                                                                  /* ������Ϸ���� */
	
public:
	Vec2 _cur;                                           // ������� 
	Vec2 _plantsPosition;                                // ֲ����ֲ����
	PlantsType _selectPlantsTag;                         // ��ѡֲ����
	GameMapInformation* _gameMapInformation;             // ��Ϸ��ͼ��Ϣ
	ZombiesAppearControl* _zombiesAppearControl;         // ��ʬ���ּ���

protected:
	Sprite* _plantPreviewImage;                          // ֲ��Ԥ��ͼƬ
	Sprite* _plantCurImage;                              // ֲ�����ͼƬ
	Global* _global;                                     // ȫ�ֵ���
	Node* _animationLayer;                               // ��Ϸ��
	GSGameEndLayer* _gameEndShieldLayer;                 // ��Ϸ�������β�
	OpenLevelData* _openLevelData;                       // �ؿ����ݵ���
	vector<int> _levelData;                              // ��ʱ�ؿ�����
};