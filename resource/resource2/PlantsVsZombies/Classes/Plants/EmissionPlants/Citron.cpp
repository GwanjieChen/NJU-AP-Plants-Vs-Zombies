/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.2.27
 *Email: 2117610943@qq.com
 */

#include "Citron.h"
#include "Bullet/CitronBullet.h"

#include "Zombies/Zombies.h"
#include "Scenes/GameScene/GSData.h"

Citron::Citron(Node* node):
	_attackInterval(0)
,   _animationId(0)
,   _isBaginReady(true)
,   _readyFinished(false)
{
	_node = node;
	_plantImage = nullptr;

	_healthPoint = 300;
	_combatEffecttiveness = 0;
	_plantsType = PlantsType::Citron;
	srand(time(nullptr));
}

Citron::~Citron()
{
}

Citron* Citron::create(Node* node)
{
	Citron* citron = new (std::nothrow) Citron(node);
	if (citron && citron->init())
	{
		citron->autorelease();
		return citron;
	}
	CC_SAFE_DELETE(citron);
	return nullptr;
}

Sprite* Citron::createPlantImage()
{
	imageInit("Citron", INIT);
	_plantImage->setScale(1.3f);
	return _plantImage;
}

void Citron::createPlantAnimation()
{
	_plantAnimation = plantInit("Citron", "normal");
	_plantAnimation->setAnchorPoint(Vec2::ANCHOR_MIDDLE);
	_plantAnimation->setScale(1.0f);
	_plantAnimation->setTimeScale(0.6f);
	_node->addChild(_plantAnimation);

	// Ӱ��
	setPlantShadow(1.9f);
	_plantAnimation->getChildByName("plantshadow")->setPosition(Vec2(0, 15));

	// �����ɽ�����
	setPlantSoilSplashAnimation(0.8f);

	createListener();
}

void Citron::determineRelativePositionPlantsAndZombies()
{
	for (auto zombie : ZombiesGroup)
	{
		zombieEatPlant(zombie);      /* ��ʬ��ֲ�� */

		plantAttack(zombie);         /* ֲ�﹥�� */

		zombieRecoveryMove(zombie);  /* ��ʬ�ָ��ƶ� */
	}
}

void Citron::plantAttack(Zombies* zombie)
{
	if (getPlantIsSurvive() && zombie->getZombieIsSurvive() && zombie->getZombieIsEnterMap() &&     /* ֲ���� && ��ʬû������ && ��ʬ�����ͼ */
		getZombieIsTheFrontOfPlant(zombie) && getZombieIsSameLineWithPlant(zombie))                 /* ��ʬ��ֲ����ͬһ�� && ��ʬ��ֲ���ǰ�� */
	{
		plantEmission();
	}
}

void Citron::plantEmission()
{
	if (_readyFinished)
	{
		if (!_isChanged)     /* �ж϶����Ƿ��Ѿ��ı� */
		{
			_plantAnimation->addAnimation(0, calculateGreatEvocationProbability() ? "shoot1" : "shoot", true);
			_isChanged = true;
		}

		_plantAnimation->setEventListener([&](spTrackEntry* entry, spEvent* event)
			{
				if (strcmp(event->data->name, "shoot") == 0)
				{
					rand() % 2 == 0 ? Bullet::playSoundEffect("throw") : Bullet::playSoundEffect("throw2");
					createBullet();
					plantRecovery("normal");
				}
			});
	}
}

void Citron::plantRecovery(const string& plantAnimation)
{
	if (_isChanged)
	{
		_plantAnimation->addAnimation(0, plantAnimation, true);
		_isBaginReady = true; /* ��ʼ׼�� */
		_readyFinished = false;
		_attackInterval = 0;

		_isChanged = false;
	}
}

void Citron::createListener()
{
	_plantAnimation->runAction(RepeatForever::create(Sequence::create(DelayTime::create(0.5f), 
		CallFunc::create([&]() 
			{
				++_attackInterval;
				if (_attackInterval >= 16 && _isBaginReady)
				{
					_readyFinished = true;
					_isBaginReady = false;
				}
			}), nullptr)));
}

int Citron::calculateGreatEvocationProbability()
{
	int number = rand() % 100;
	if (number < 5)
		_animationId = 1;
	else
		_animationId = 0;
	return _animationId;
}

void Citron::createBullet()
{
	_bulletAnimation = new CitronBullet(_node, _animationId);
	_bulletAnimation->setBulletPosition(_position);
	_bulletAnimation->createBullet();

	BulletGroup.push_back(_bulletAnimation);
}
