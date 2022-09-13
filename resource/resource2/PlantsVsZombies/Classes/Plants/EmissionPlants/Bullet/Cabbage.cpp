/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.2.18
 *Email: 2117610943@qq.com
 */

#include "Cabbage.h"
#include "../PeaShooter.h"

#include "Zombies/Zombies.h"
#include "Scenes/GameScene/GSData.h"

Cabbage::Cabbage(Node* node) :
  _zombiePosition(Vec2::ZERO)
, _zombieSpeed(0)
, _isFileData(false)
{
	_node = node;
	_attack = 60;
	_bulletType = BulletType::Cabbage;
}

void Cabbage::createBullet()
{
	bulletInit();
	createShadow();
}

void Cabbage::bulletAndZombiesCollision()
{
	for (auto zombie : ZombiesGroup)
	{
		if (!_isUsed && zombie->getZombieIsSurvive() &&                                           /* ���Ĳ�û��ʹ�� && ��ʬû������ */
			getBulletIsSameLineWithZombie(zombie) && getBulletIsEncounterWithZombie(zombie))      /* �ӵ��뽩ʬͬһ�� && �ӵ��뽩ʬ��ײ */
		{
			selectSoundEffect(zombie->getZombieHeadAttackSoundEffect());
			_bulletAnimation->setOpacity(0);
			bulletAttackHurtZombies(zombie);   /* ��ʬ��������ֵ */

			zombie->setZombieHurtBlink();

			createCabbageExplode();

			_isUsed = true;
			break; /* һ��ֻ�ܻ���һ����ʬ */
		}
	}
}

void Cabbage::bulletInit()
{
	float height = 300, time = 1.0f;
	Vec2 endPosition = calculateZombiePosition();
	Vec2 initPosition = _position + Vec2(70, 150);
	
	if (_isFileData)
	{
		_isFileData = false;
		auto position = _position + Vec2(70, 150); //���Ĳ�������ʼλ��

		auto distance = _zombiePosition.x - position.x; // ��ʬ����Ĳ˳�ʼ����
		if (_currentPosition.x <= _zombiePosition.x - distance / 2) // ��ǰλ�����������ϰ벿��
			height = 300 - (_currentPosition.y - position.y);
		else
			height = 0;
		time = (distance - (_currentPosition.x - _position.x)) / distance; //����ʣ���˶�ʱ��
		if (time < 0)time = 0;
		if (time > 1)time = 1;

		initPosition = _currentPosition;
		endPosition = _zombiePosition - Vec2(0, 20);
	}

	_bulletAnimation = SkeletonAnimation::createWithData(_global->userInformation->getAnimationData().find("CabbageBullet")->second);
	_bulletAnimation->setAnimation(0, "Cabbage_Rotate", true);
	_bulletAnimation->setScale(0.8f);
	_bulletAnimation->setLocalZOrder(getZOrder(_position.y));
	_bulletAnimation->setPosition(initPosition);
	_bulletAnimation->setAnchorPoint(Vec2(0, 0));
	_node->addChild(_bulletAnimation);

	auto jto = JumpTo::create(time, endPosition, height, 1);

	_bulletAnimation->runAction(Sequence::create(jto,
		CallFunc::create([this]()
			{
				if (_bulletAnimation->getOpacity()) /* ���û������˵��û�л��н�ʬ */
				{
					playSoundEffect(SoundEffectType::kernelpult);
				}
				_bulletAnimation->setAnimation(0, "Cabbage_Crush", false);
			}), DelayTime::create(1.4f),
		CallFunc::create([this]()
			{
				_bulletAnimation->runAction(Sequence::create(FadeOut::create(0.2f),
					CallFunc::create([this]()
						{
							_bulletAnimation->setVisible(false);
						}), nullptr));
			}), nullptr));
}

Vec2 Cabbage::calculateZombiePosition()
{
	if (fabs(_position.x + 70 - _zombiePosition.x) >= 662)
		return _zombiePosition + Vec2(_zombieSpeed + 10, 20);
	else if (fabs(_position.x + 70 - _zombiePosition.x) >= 300)
		return _zombiePosition + Vec2(_zombieSpeed / 2.f, 20);
	else 
		return _zombiePosition + Vec2(-_zombieSpeed, 20);
}

void Cabbage::createShadow()
{
	/* ����Ӱ�� */
	auto shadow = Sprite::createWithSpriteFrameName("plantshadow.png");
	shadow->setPosition(_position + Vec2(70, 10));
	shadow->setLocalZOrder(getZOrder(_position.y));
	shadow->setOpacity(200);
	_node->addChild(shadow);
	shadow->runAction(RepeatForever::create(Sequence::create(
		CallFunc::create([=]()
			{
				shadow->setPositionX(_bulletAnimation->getPositionX());
			}), DelayTime::create(0.01f),
		CallFunc::create([=]() 
			{
				if (!_bulletAnimation->getOpacity())
				{
					shadow->removeFromParent();
				}
			}), nullptr)));
	shadow->runAction(Sequence::create(DelayTime::create(1.0f),
		CallFunc::create([shadow]()
			{
				shadow->removeFromParent();
			}), nullptr));
}

void Cabbage::createCabbageExplode()
{
	auto cabbageExplode = SkeletonAnimation::createWithData(_global->userInformation->getAnimationData().find("CabbageBullet")->second);
	cabbageExplode->setAnimation(0, "Cabbage_Crush", false);
	cabbageExplode->setScale(0.6f);
	cabbageExplode->setLocalZOrder(_bulletAnimation->getLocalZOrder());
	cabbageExplode->setPosition(_bulletAnimation->getPosition());
	cabbageExplode->setAnchorPoint(Vec2(0, 0));
	cabbageExplode->runAction(Sequence::create(DelayTime::create(1.4f),
		CallFunc::create([cabbageExplode]()
			{
				cabbageExplode->runAction(Sequence::create(FadeOut::create(0.2f),
					CallFunc::create([cabbageExplode]()
						{
							cabbageExplode->removeFromParent();
						}), nullptr));
			}), nullptr));
	_node->addChild(cabbageExplode);
}

void Cabbage::setZombiePosition(const Vec2& position)
{
	_zombiePosition = position; /* ��¼��ʬλ��*/
}

void Cabbage::setZombieSpeed(const float speed)
{
	_zombieSpeed = speed;
}

void Cabbage::setIsFileData(const bool isFileData)
{
	_isFileData = isFileData;
}

float Cabbage::getZombieSpeed() const
{
	return _zombieSpeed;
}

void Cabbage::setCabbageCurrentPosition(const Vec2& position)
{
	_currentPosition = position;
}

Vec2 Cabbage::getCabbageInitialPosition()
{
	return _position;
}

bool Cabbage::getBulletIsSameLineWithZombie(Zombies* zombie)
{
	return (fabs(zombie->getZombieAnimation()->getPositionY() - _position.y) <= 10 &&
		fabs(zombie->getZombieAnimation()->getPositionY() - _bulletAnimation->getPositionY()) <= 170) ? true : false;
}

bool Cabbage::getBulletIsEncounterWithZombie(Zombies* zombie)
{
	return fabs(zombie->getZombieAnimation()->getPositionX() - _bulletAnimation->getPositionX()) <= 60 ? true : false;
}

void Cabbage::bulletAttackHurtZombies(Zombies* zombie)
{
	if (zombie->getZombieCurrentHeadShieldVolume() < _attack) /* �����ǰͷ������Ѫ��С�ڹ����˺� */
	{
		if (zombie->getZombieCurrentHeadShieldVolume() + zombie->getZombieCurrentBloodVolume() <= _attack) /* �����ʬ����Ѫ��С���˺�����ʬ������ */
		{
			/* ��ʬ���� */
			zombie->setZombieCurrentBloodVolume(0);
			zombie->setZombieCurrentHeadShieldVolume(0);
		}
		else
		{
			/* ���㽩ʬ����Ѫ�� */
			zombie->setZombieCurrentBloodVolume(zombie->getZombieCurrentHeadShieldVolume() + zombie->getZombieCurrentBloodVolume() - _attack);
			zombie->setZombieCurrentHeadShieldVolume(0);
		}
	}
	else
	{
		/* ���㽩ʬ����ʣ��Ѫ�� */
		zombie->setZombieCurrentHeadShieldVolume(zombie->getZombieCurrentHeadShieldVolume() - _attack);
	}
}
