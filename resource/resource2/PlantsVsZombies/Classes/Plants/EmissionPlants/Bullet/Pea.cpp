/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.2.18
 *Email: 2117610943@qq.com
 */

#include "Pea.h"
#include "../PeaShooter.h"

#include "Zombies/Zombies.h"
#include "Scenes/GameScene/GSData.h"

Pea::Pea(Node* node) :
	_isFire(false)
,   _torchwoodTag(0)
,   _fireNumbers(0)
,   _peaAnimationName("normal")
{
	_node = node;
	_attack = 20;
	_bulletType = BulletType::Pea;
}

Pea::~Pea()
{
}

void Pea::createBullet()
{
	bulletInit();
	createShadow();
}

void Pea::bulletInit()
{
	_bulletAnimation = SkeletonAnimation::createWithData(_global->userInformation->getAnimationData().find("FirePea")->second);
	_bulletAnimation->setAnimation(0, _peaAnimationName, true);
	_bulletAnimation->setPosition(_position + Vec2(70, 85));
	_bulletAnimation->setScale(0.5f);
	_bulletAnimation->setName(_bulletName);
	_bulletAnimation->setLocalZOrder(getZOrder(_position.y));
	_node->addChild(_bulletAnimation);
	_bulletAnimation->runAction(Sequence::create(MoveBy::create(3.0f, Vec2(2000, 0)),
		CallFunc::create([this]()
			{
				_bulletAnimation->setVisible(false);
			}), nullptr));
}

void Pea::createShadow()
{
	/* ����Ӱ�� */
	auto shadow = Sprite::createWithSpriteFrameName("plantshadow.png");
	shadow->setScale(1.7f);
	shadow->setName("shadow");
	shadow->setPosition(Vec2(0, -155));
	shadow->setOpacity(200);
	shadow->setLocalZOrder(_bulletAnimation->getLocalZOrder());
	_bulletAnimation->addChild(shadow, -1);
}

void Pea::bulletAndZombiesCollision()
{
	_isFire ? fireBulletAttackZombies() : bulletAttackZombies();
}

void Pea::bulletAttackZombies()
{
	for (auto zombie : ZombiesGroup)
	{
		if (!_isUsed && getBulletIsSameLineWithZombie(zombie) &&  /* �㶹û�б�ʹ�� && �㶹�뽩ʬ��ͬһ�� */
			getBulletIsEncounterWithZombie(zombie) &&             /* �㶹�뽩ʬ��ײ */
			zombie->getZombieIsSurvive() && zombie->getZombieIsEnterMap()) /* ��ʬû������ && ��ʬ�����ͼ�� */
		{
			selectSoundEffect(zombie->getZombieBodyAttackSoundEffect(),
				zombie->getZombieHeadAttackSoundEffect());  /* ����ָ������ */

			setBulletOpacity();                /* �ӵ���ʧ */
			bulletAttackHurtZombies(zombie);   /* ��ʬ��������ֵ */

			zombie->setZombieHurtBlink();

			createPeaExplode(); /* �����㶹��ը���� */
			setBulletAttack(0);
			setBulletIsUsed(true);

			break; /* һ���㶹ֻ�ܻ���һ����ʬ */
		}
	}
}

void Pea::fireBulletAttackZombies()
{
	for (auto zombie : ZombiesGroup)
	{
		if (!_isUsed && getBulletIsSameLineWithZombie(zombie) &&           /* �㶹û�б�ʹ�� && �㶹�뽩ʬ��ͬһ�� */
			getBulletIsEncounterWithZombie(zombie) &&                      /* �㶹�뽩ʬ��ײ */
			zombie->getZombieIsSurvive() && zombie->getZombieIsEnterMap()) /* ��ʬû������ && ��ʬ�����ͼ�� */
		{
			playSoundEffect(SoundEffectType::firepea); /* ����ָ������ */

			setBulletOpacity();                /* �ӵ���ʧ */
			attackZombies();                   /* ������ʬ */
			createPeaExplode();                /* �����㶹��ը���� */
			setBulletAttack(0);
			setBulletIsUsed(true);

			break;
		}
	}
}

void Pea::attackZombies()
{
	for (auto zombie : ZombiesGroup)
	{
		if (getBulletIsSameLineWithZombie(zombie) &&
			zombie->getZombieIsSurvive() &&
			zombie->getZombieIsEnterMap())
		{
			auto attack = static_cast<int>(getZombieInExplodeRange(zombie) / 50 * 20);
			_attack = 40;

			if (attack > 0) _attack -= attack;
			if (_attack <= 0) continue;
			bulletAttackHurtZombies(zombie);
			zombie->setZombieHurtBlink();
		}
	}
}

float Pea::getZombieInExplodeRange(Zombies* zombie)
{
	/* ��ʬ�Ƿ��ڱ�ը��Χ�ж� */
	return fabs(zombie->getZombieAnimation()->getPositionX() - _bulletAnimation->getPositionX());
}

void Pea::createPeaExplode()
{
	static string Skin[] = { {"skin"},{"skin1"},{"skin2"},{"skin3"} };// !!!not use
	static string Animation[] = { {"Explode"},{"Explode1"},{"Explode2"},{"Explode3"},{"Explode4"} };

	auto peaExplode = SkeletonAnimation::createWithData(_global->userInformation->getAnimationData().find("PeaExplode")->second);
	peaExplode->setPosition(getBulletPosition());
	peaExplode->setAnimation(0, Animation[!_isFire ? 4 : 3], false);
	peaExplode->setScale(!_isFire ? 1.0f : 1.4f);
	peaExplode->setLocalZOrder(_bulletAnimation->getLocalZOrder());
	if (!_isFire)
	{
		peaExplode->setColor(Color3B(102, 206, 26));
	}
	_node->addChild(peaExplode);

	peaExplode->runAction(Sequence::create(DelayTime::create(0.8f), CallFunc::create([peaExplode]()
		{
			peaExplode->removeFromParent();
		}), nullptr));
}

bool Pea::getIsFire() const
{
	return _isFire;
}

int Pea::getPeaFireNumbers() const
{
	return _fireNumbers;
}

int Pea::getTorchwoodTag() const
{
	return _torchwoodTag;
}

void Pea::setIsFire(const bool isFire)
{
	_isFire = isFire;
}

void Pea::setPeaFireNumbers(const int fireNumbers)
{
	_fireNumbers = fireNumbers;
}

void Pea::addPeaFireNumbers()
{
	++_fireNumbers;
}

void Pea::setTorchwoodTag(const int torchwoodTag)
{
	_torchwoodTag = torchwoodTag;
}
