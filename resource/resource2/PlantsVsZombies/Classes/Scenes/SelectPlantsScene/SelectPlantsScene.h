/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2019.8.12
 *Modify: 2020.2.3
 *Email: 2117610943@qq.com
 */

#pragma once
#include "cocos2d.h"
#include "cocos-ext.h"

#include "Based/GlobalVariable.h" 

#define SCROLLRIGHTFINISHED -1010
#define SCROLLLEFTFINISHED  -220

using namespace cocos2d;
using namespace cocos2d::extension;

class SPSSpriteLayer;
class SPSControlLayer;

class SelectPlantsScene :public Scene
{
public:
	static Scene* createScene(); 
	CREATE_FUNC(SelectPlantsScene);

CC_CONSTRUCTOR_ACCESS:
	SelectPlantsScene();
	~SelectPlantsScene();
	virtual bool init();

protected:
	/**
	 *��������
	 */
	virtual void createReadyText(const std::string& name, const int& id);

	/**
	 *���ֻص�
	 */
	virtual void readyTextCallBack(Node* node, const std::string& name, const int& id);

	/**
	 *�л�����
	 */
	virtual void replaceScene();

	/**
	 *����������
	 */
	virtual void createBackgroundLayer();

	/**
	 *�������Ʋ�
	 */
	virtual void createControlLayer();

	/**
	 *�¼�����
	 */
	virtual void eventUpdate(float Time);

	/**
	 *����ֲ��ѡ��Ի���
	 */
	virtual void createSelectPlantsDialog();

	/**
	 *������ʾҪ��
	 */
	virtual void controlShowRequirement();

	/**
	 *ֲ��ѡ��ص�����
	 */
	virtual void selectPlantsCallBack();

protected:
	Layer* _scrollLayer;
	Director* _director;
	Global* _global;
	SPSControlLayer* _controlLayer;
	SPSSpriteLayer* _spriteLayer;
	extension::ScrollView* _scrollView;
};