/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.1.28
 *Email: 2117610943@qq.com
 */

#include "GSPauseQuitLayer.h"
#include "GameScene.h"
#include "GSData.h"

#include "../SelectPlantsScene/SelectPlantsScene.h"
#include "../SelectPlantsScene/MirrorSelectPlantsScene.h"
#include "../WorldScene/World_1.h"
#include "../WorldScene/MirrorWorld_1.h"

#include "spine/spine-cocos2dx.h"
#include "Based/UserData.h"
#include "Based/PlayMusic.h"

using namespace spine;

string GSPauseQuitLayer::_layerName[] = 
{ 
	"backgroundLayer","buttonLayer","animationLayer",
	"controlLayer","informationLayer","sunLayer" 
};

int GSPauseQuitLayer::_pauseNumbers = 0;

GSPauseQuitLayer::GSPauseQuitLayer() :
  _promptLayer(nullptr)
, _levelName(_global->userInformation->getCurrentCaveFileLevelWorldName())
{
}

GSPauseQuitLayer::~GSPauseQuitLayer()
{
	_pauseNumbers = 0;
}

Layer* GSPauseQuitLayer::addLayer()
{
	return GSPauseQuitLayer::create();
}

void GSPauseQuitLayer::pauseLayer()
{
	auto director = Director::getInstance()->getRunningScene();
	for (auto name : _layerName)
	{
		if (director->getChildByName(name))
			director->getChildByName(name)->onExit();
		else
			return;
	}
	PlayMusic::stopMusic();
	++_pauseNumbers;
}

void GSPauseQuitLayer::resumeLayer()
{
	if (!--_pauseNumbers)
	{
		auto director = Director::getInstance()->getRunningScene();
		for (auto name : _layerName)
		{
			if (director->getChildByName(name))
				director->getChildByName(name)->onEnter();
			else
				return;
		}
		PlayMusic::resumeMusic();
	}
}

int GSPauseQuitLayer::getPauseNumbers()
{
	return _pauseNumbers;
}

bool GSPauseQuitLayer::init()
{
	if (!LayerColor::initWithColor(Color4B(0, 0, 0, 180)))return false;

	createDialog();

	return true;
}

void GSPauseQuitLayer::createDialog()
{
	_option = Sprite::createWithSpriteFrameName("LevelObjiectivesBg.png");
	_option->setPosition(_director->getWinSize() / 2);
	_option->setScale(0.9f);
	this->addChild(_option);

	auto PauseAnimation= SkeletonAnimation::createWithData(
		_global->userInformation->getAnimationData().find("PauseAnimation")->second);
	PauseAnimation->setAnimation(0, "animation", true);
	PauseAnimation->setPosition(Vec2(530, 650));
	_option->addChild(PauseAnimation);

	/* �����ƶ����� */
	_touchListener = createTouchtListener(_option);

	/* ���������� */
	auto musicslider = createSlider(Vec2(600, 520), Vec2(150, 520), 
		_global->userInformation->getGameText().find("����")->second, OptionScene_Slider::����,
		Sprite::createWithSpriteFrameName("bgFile.png"),
		Sprite::createWithSpriteFrameName("progressFile.png"),
		Sprite::createWithSpriteFrameName("thumbFile.png"),
		nullptr,
		true);
	auto SoundEffectslider = createSlider(Vec2(600, 450), Vec2(150, 450), 
		_global->userInformation->getGameText().find("��Ч")->second, OptionScene_Slider::��Ч,
		Sprite::createWithSpriteFrameName("bgFile.png"),
		Sprite::createWithSpriteFrameName("progressFile.png"),
		Sprite::createWithSpriteFrameName("thumbFile.png"),
		nullptr,
		true);

	musicslider->setScale(1.2f);
	SoundEffectslider->setScale(1.2f);

	/* ������ѡ�� */
	auto check    = createCheckBox(Vec2(350, 380), Vec2(150, 380), _global->userInformation->getGameText().find("��Ϣ")->second, OptionScene_CheckBox::��ʾ��Ϣ, "CheckBox2", "CheckBox", true);
	auto check1   = createCheckBox(Vec2(800, 380), Vec2(600, 380), _global->userInformation->getGameText().find("ȫ��")->second, OptionScene_CheckBox::ȫ��, "CheckBox2", "CheckBox", true);
	auto check2   = createCheckBox(Vec2(350, 310), Vec2(150, 310), _global->userInformation->getGameText().find("��֡��")->second, OptionScene_CheckBox::��֡��, "CheckBox2", "CheckBox", true);
	auto check3   = createCheckBox(Vec2(800, 310), Vec2(600, 310), _global->userInformation->getGameText().find("�����ʾ")->second, OptionScene_CheckBox::�������, "CheckBox2", "CheckBox", true);
	auto check4   = createCheckBox(Vec2(350, 240), Vec2(150, 240), _global->userInformation->getGameText().find("������ʾ")->second, OptionScene_CheckBox::������ʾ, "CheckBox2", "CheckBox", true);
	auto check5   = createCheckBox(Vec2(800, 240), Vec2(600, 240), _global->userInformation->getGameText().find("��ֱͬ��")->second, OptionScene_CheckBox::��ֱͬ��, "CheckBox2", "CheckBox", true);

	check->setScale(0.6f);
	check1->setScale(0.6f);
	check2->setScale(0.6f);
	check3->setScale(0.6f);
	check4->setScale(0.6f);
	check5->setScale(0.6f);

	/* ������ť */
	createButton(Vec2(210, 170), _global->userInformation->getGameText().find("�鿴ͼ��")->second, PauseQuitLayer_Button::�鿴ͼ��);
	createButton(Vec2(520, 170), _global->userInformation->getGameText().find("���¿�ʼ")->second, PauseQuitLayer_Button::���¿�ʼ);
	createButton(Vec2(830, 170), _global->userInformation->getGameText().find("������Ϸ")->second, PauseQuitLayer_Button::������Ϸ);
	createButton(Vec2(365, 70), _global->userInformation->getGameText().find("����˵��")->second, PauseQuitLayer_Button::����˵��);
	createButton(Vec2(665, 70), _global->userInformation->getGameText().find("�˳���Ϸ")->second, PauseQuitLayer_Button::�˳���Ϸ);
}

void GSPauseQuitLayer::createButton(const Vec2& vec2, const std::string name, PauseQuitLayer_Button button_type)
{
	/* �����������˵���ť */
	auto button = ui::Button::create("ButtonNew2.png", "ButtonNew.png", "", TextureResType::PLIST);
	auto label = Label::createWithTTF(name, GAME_FONT_NAME_1, 35);
	label->enableShadow(Color4B(0, 0, 0, 200));//������Ӱ
	label->setScale(2.0f);
	button->setTitleLabel(label);
	button->setTitleColor(Color3B::WHITE);
	button->setPosition(vec2);
	button->setScale(0.5f);
	_option->addChild(button);

	button->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				PlayMusic::playMusic("gravebutton");
				break;
			case ui::Widget::TouchEventType::ENDED:
				switch (button_type)
				{
				case PauseQuitLayer_Button::�鿴ͼ��: openHandBook();   break;
				case PauseQuitLayer_Button::���¿�ʼ: setRestart();     break;
				case PauseQuitLayer_Button::�˳���Ϸ: setQuitGame();    break;
				case PauseQuitLayer_Button::����˵��: keyDescription(); break;
				case PauseQuitLayer_Button::������Ϸ: returnGame();     break;
				default: break;
				}
			}
		});
}

void GSPauseQuitLayer::showPrompt()
{
	_promptLayer = LayerColor::create(Color4B(0, 0, 0, 180));
	createShieldLayer(_promptLayer);
	this->addChild(_promptLayer);

	auto prompt = Sprite::createWithSpriteFrameName("Prompt.png");
	prompt->setPosition(_director->getWinSize() / 2.0f);
	prompt->setOpacity(200);
	_promptLayer->addChild(prompt);

	auto Close = ui::Button::create("CloseDown.png", "Close.png", "", TextureResType::PLIST);
	Close->setPosition(Vec2(1510, 422));
	Close->setScale(0.6f);
	Close->setScaleY(0.58f);
	prompt->addChild(Close);

	Close->addTouchEventListener([=](Ref* sender, ui::Widget::TouchEventType type)
		{
			switch (type)
			{
			case ui::Widget::TouchEventType::BEGAN:
				PlayMusic::playMusic("tap");
				break;
			case ui::Widget::TouchEventType::ENDED:
				_promptLayer->removeFromParent();
				break;
			}
		});
}

void GSPauseQuitLayer::openHandBook()
{
	Application::getInstance()->openURL("https://lzpvz.rthe.net");
}

void GSPauseQuitLayer::setRestart()
{
	_director->getScheduler()->setTimeScale(1.0f);
	UserData::getInstance()->caveUserData("BREAKTHROUGH", ++_global->userInformation->getBreakThroughNumbers());
	
	_director->replaceScene(TransitionFade::create(1.0f, SelectPlantsScene::createScene()));

	UserData::getInstance()->createNewLevelDataDocument();
	UserData::getInstance()->removeLevelData(_levelName);
}

void GSPauseQuitLayer::setQuitGame()
{
	_director->getScheduler()->setTimeScale(1.0f);
	UserData::getInstance()->caveUserData("BREAKTHROUGH", ++_global->userInformation->getBreakThroughNumbers());

	UserData::getInstance()->createNewLevelDataDocument();
	UserData::getInstance()->caveLevelData(_levelName);

	popSceneAnimation();
}

void GSPauseQuitLayer::keyDescription()
{
	showPrompt();
}

void GSPauseQuitLayer::returnGame()
{
	resumeLayer();
	this->removeFromParent();
}

void GSPauseQuitLayer::popSceneAnimation()
{
	auto layer = LayerColor::create(Color4B(0, 0, 0, 0));
	this->addChild(layer);
	layer->runAction(Sequence::create(FadeIn::create(0.5f),
		CallFunc::create([=]()
			{
				World_1::setPopEnter(true);
				layer->removeFromParent();
				_director->popScene();
			}), nullptr));
}