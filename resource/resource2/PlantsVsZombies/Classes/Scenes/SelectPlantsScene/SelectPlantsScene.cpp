/**
 *Copyright (c) 2019 LZ.All Right Reserved
 *Author : LZ
 *Date: 2019.8.12
 *Modify: 2020.2.3
 *Email: 2117610943@qq.com
 */

#include "SPSControlLayer.h"
#include "SPSBackgroundLayer.h"
#include "SPSRequriementLayer.h"
#include "SPSSpriteLayer.h"
#include "SPSControlLayer.h"
#include "SelectPlantsScene.h"
#include "Scenes/GameScene/GameScene.h"

#include "Based/GameType.h"
#include "Based/PlayMusic.h"

SelectPlantsScene::SelectPlantsScene() :
	_controlLayer(nullptr),
	_scrollLayer(nullptr),
	_spriteLayer(nullptr),
	_scrollView(nullptr),
	_director(Director::getInstance()),
	_global(Global::getInstance())
{
	PlayMusic::changeBgMusic("mainmusic.mo3.1", true);
}

SelectPlantsScene::~SelectPlantsScene()
{
}

Scene* SelectPlantsScene::createScene()
{
	return SelectPlantsScene::create();
}

bool SelectPlantsScene::init()
{
	if (!Scene::init())return false;

	createBackgroundLayer();
	createControlLayer();
	schedule(schedule_selector(SelectPlantsScene::eventUpdate), 0.25f);
	schedule([this](float) {_global->checkAnimationInterval(); }, 1.f, "FPS");

	return true;
}

void SelectPlantsScene::createBackgroundLayer()
{
	/* ����������С */
	_scrollLayer = Layer::create();
	_scrollLayer->setContentSize(Size(2930, 1080));

	/* ���������еĶ��������飩*/
	_scrollLayer->addChild(SPSBackgroundLayer::create());
	
	//����������ͼ
	_scrollView = extension::ScrollView::create();
	_scrollView = extension::ScrollView::create(_director->getWinSize(), _scrollLayer);
	_scrollView->setPosition(Vec2(0, 0));
	_scrollView->setDirection(extension::ScrollView::Direction::HORIZONTAL);//����ֻ���������
	_scrollView->setTouchEnabled(false);//�رմ����¼�
	_scrollView->runAction(Sequence::create(DelayTime::create(1.0f),
		CallFuncN::create([&](Node* node)
			{
				_scrollView->setContentOffsetInDuration(Vec2(-1010, 0), 2.5f);
			}), nullptr));
	this->addChild(_scrollView);
}

void SelectPlantsScene::createControlLayer()
{
	_controlLayer = SPSControlLayer::create();
	this->addChild(_controlLayer, 1);
}

void SelectPlantsScene::eventUpdate(float Time)
{
	if (Time == 0.22f && _spriteLayer->_selectFinished)
	{
		unschedule(schedule_selector(SelectPlantsScene::eventUpdate));
		selectPlantsCallBack();
	}
	else if (Time == 0.25f)
	{
		if (_scrollView->getContentOffset().x <= SCROLLRIGHTFINISHED)
		{
			/* ȡ����ʱ���� */
			unschedule(schedule_selector(SelectPlantsScene::eventUpdate)); 

			runAction(Sequence::create(DelayTime::create(1.0f), CallFunc::create([&]() {controlShowRequirement(); }), nullptr));
		}
	}
	else if (Time == 0.3f)
	{
		if (_scrollView->getContentOffset().x >= SCROLLLEFTFINISHED)
		{
			/* �������� */
			PlayMusic::playMusic("readysetplant");
			/* ȡ����ʱ���� */
			this->unschedule(schedule_selector(SelectPlantsScene::eventUpdate));

			createReadyText("StartReady", 1);
		}
	}
}

void SelectPlantsScene::createSelectPlantsDialog()
{
	/* ɾ������ */
	_controlLayer->removeChildByName("username");

	_spriteLayer = SPSSpriteLayer::create();
	this->addChild(_spriteLayer);

	schedule(schedule_selector(SelectPlantsScene::eventUpdate), 0.22f);
}

void SelectPlantsScene::controlShowRequirement()
{
	/* �����Ҫ������ʾͨ��Ҫ�� */
	auto _levelData = OpenLevelData::getInstance()->readLevelData(OpenLevelData::getInstance()->getLevelNumber());
	if (_levelData->getGameType().size())
	{
		this->addChild(SPSRequriementLayer::create(), 2);
	}
	createSelectPlantsDialog();
}

void SelectPlantsScene::selectPlantsCallBack()
{
	_scrollView->setContentOffsetInDuration(Vec2(-220, 0), 2.0f);//���ù���������ʱ��
	this->schedule(schedule_selector(SelectPlantsScene::eventUpdate), 0.3f);
}

void SelectPlantsScene::createReadyText(const std::string& name, const int& id)
{
	static float time[] = { 0,0.2f,0.2f,1.5f };
	auto text = Sprite::createWithSpriteFrameName(name + ".png");
	text->setScale(15.0f);
	text->setName(name);
	text->setPosition(Director::getInstance()->getWinSize() / 2.0f);
	text->runAction(Sequence::create(ScaleTo::create(0.3f, 2.0f), DelayTime::create(time[id]), CallFuncN::create(CC_CALLBACK_1(SelectPlantsScene::readyTextCallBack, this, name, id)), nullptr));
	this->addChild(text);
}

void SelectPlantsScene::readyTextCallBack(Node* node, const std::string& name, const int& id)
{
	this->removeChildByName(name);
	switch (id)
	{
	case 1:
		createReadyText("StartSet", 2);
		break;
	case 2:
		createReadyText("StartPlant", 3);
		break;
	default:
		_scrollLayer->removeChildByName("previewBackgroundImage");

		replaceScene();
		break;
	}
}

void SelectPlantsScene::replaceScene()
{
	_global->userInformation->setUserSelectCrads(_spriteLayer->seedBankButton);
	_global->userInformation->setSunNumbers(100); //�趨��ʼ������ 

	if (_global->userInformation->getIsEaseAnimation() == ui::CheckBox::EventType::SELECTED)
		Director::getInstance()->replaceScene(TransitionFade::create(1.f, GameScene::createScene()));
	else
		Director::getInstance()->replaceScene(GameScene::createScene());
}
