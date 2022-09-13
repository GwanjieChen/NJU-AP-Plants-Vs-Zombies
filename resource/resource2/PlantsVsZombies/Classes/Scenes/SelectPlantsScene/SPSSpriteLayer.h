/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2019.8.12
 *Modify: 2020.2.3
 *Email: 2117610943@qq.com
 */

#pragma once
#include "cocos2d.h"
#include "Based/GlobalVariable.h"
#include "spine/spine-cocos2dx.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace spine;

class SPSSpriteLayer : public Layer
{
public:
	CREATE_FUNC(SPSSpriteLayer);
	Text* showPlantsInformation(Button* button, const unsigned int id) const;

private:
	void createSelectPlantsDialog();
	void alreadySelectPlantsDialog();
	void alreadyHavePlantsDialog();
	void createScrollview();
	void scrollViewUpdate(float Time);
	void createMouseListener();
	void createPlantsCards();
	void showRandPlantsInformation();
	Button* createButtons(const Vec2& vec2, const unsigned int& ID);
	void preLoadText();
	void createPlantsImage(Button* button, const std::string& resource, const float& scale = 0.8f) const;
	void createMoveButton(Button* button, const Vec2& vec2, const unsigned int& id);
	void createAnimationAndText(const unsigned int& id);
	void createPlantsAnimation(const std::string& filepath, const std::string& AnimationName, const std::string& skin, Vec2& vec2, const float& scale = 1.0f);
	void createPlantsText(const unsigned int& ID, const std::string& name, const Vec2& vec2, const float& fontsize, Color3B color = Color3B::WHITE, bool AnchorPoint = true);
	void sortPlantsCard(const unsigned int& id);
	void removePlantsCardCallBack(Node* node, const unsigned int& ID, Button* button);
	void createBeginButton();
	void controlPlantCanSelect(Button* button, const unsigned int id);
	void createProhibit(Button* button);
	void selectPlantsCallBack(Node* node) { _selectFinished = true; }

CC_CONSTRUCTOR_ACCESS:
	SPSSpriteLayer();
	~SPSSpriteLayer();
	virtual bool init();

public:
	bool _selectFinished;                      /* �Ƿ�ѡ����� */
	vector<UserSelectCard> seedBankButton;

private:
	Global* _global;
	Sprite* _seedChooser;
	Text* _animationText[15];                  /* ����˵�� */
	SkeletonAnimation* _plantsAnimation;       /* ֲ�ﶯ�� */
	ui::ScrollView* _plantCardScrollView;      /* ֲ�￨�ƹ�����ͼ */
	ui::ScrollView* _plantCardTextScrollView;  /* ֲ�￨�ƹ�����ͼ */
	float _plantCardScrollViewPercent;         /* ֲ�￨�ƹ�����ͼ�������� */
	float _plantCardRollingDistance;           /* �������������� */
	unsigned int _plantsNumber;                /* ֲ������ */
	bool _isPlantIsCanSelect[13];              /* �Ƿ����ѡ���ֲ�� */
};

