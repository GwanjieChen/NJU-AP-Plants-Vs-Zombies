/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.5.08
 *Email: 2117610943@qq.com
 */

#include "SGSSurvivalControlLayer.h"
#include "../GSZombiesAppearControl.h"
#include "../GSAnimationLayer.h"
#include "../GSInformationLayer.h"
#include "../GSData.h"
#include "../GSDefine.h"
#include "../../SelectPlantsScene/SelectPlantsScene.h"

#include "Based/PlayMusic.h"

unsigned int SGSSurvivalControlLayer::_frequencyNumbers = 0;

void SGSSurvivalControlLayer::judgeLevelIsFinished()
{
	/* �ؿ����� */
	if (ZombiesGroup.size() <= 0 && _zombiesAppearControl->getZombiesAppearFrequency() >= 10)
	{
		CURSOR_VISIBLE(true);

		_director->pushScene(SelectPlantsScene::createScene());
	}
}

void SGSSurvivalControlLayer::createZombies()
{
	/* ˢ�½�ʬ */
	if (_zombiesAppearControl->getLastFrequencyZombiesWasDeath())
	{
		_zombiesAppearControl->setLastFrequencyZombiesWasDeath(false);
		_zombiesAppearControl->setTimeClear(); /* ������һ��ˢ��ʱ������ */
		if (_zombiesAppearControl->getZombiesAppearFrequency() < 10)
		{
			unsigned int zombiesNumbers = getZombiesNumbers();
			for (unsigned int i = 0; i < zombiesNumbers; ++i)
			{
				animationLayerInformation->createZombiesOnSurvival();
			}
			/* ������������һ */
			_zombiesAppearControl->setZombiesAppearFrequency();
			++_frequencyNumbers;

			/* ���������� */
			informationLayerInformation->updateProgressBar(_zombiesAppearControl->getZombiesAppearFrequency(), 10);
		}
	}
	informationLayerInformation->updateProgressBarHead();

	/* ���ƽ�ʬ��ˢ�� */
	if (controlRefurbishZombies())
	{
		_zombiesAppearControl->setLastFrequencyZombiesWasDeath(true);
		_zombiesAppearControl->setIsBegin(false);
	}
}

bool SGSSurvivalControlLayer::controlRefurbishZombies()
{
	if ((Zombies::getZombiesNumbers() <= 4 && _frequencyNumbers > 3)                    /* ������ŵĽ�ʬ��С�ڹ涨��ˢ����һ�� */

		|| (Zombies::getZombiesNumbers() <= 0 && _frequencyNumbers > 1                  /* ���û�д�ʬ������ˢ�½�ʬ */)

		|| (_zombiesAppearControl->getTime() >= 18 && _frequencyNumbers == 0)           /* ��һ��ˢ�¿��� */

		|| (_zombiesAppearControl->getTime() >= 30 + rand() % 10 &&
			(_frequencyNumbers == 1 || _frequencyNumbers == 2))                         /* �ڶ�����ˢ�¿��� */

		|| (_zombiesAppearControl->getTime() >= 40 && _frequencyNumbers > 2)            /* �������45��ˢ����һ�� */
		)
	{
		return true;
	}
	return false;
}

void SGSSurvivalControlLayer::controlRefurbishMusicAndText()
{
	/* ���ƴ󲨽�ʬ��Ϯ������������ */
	if ((_zombiesAppearControl->getTime() >= 18 && _frequencyNumbers / 10 == 0) ||
		(_zombiesAppearControl->getTime() >= 5 && _frequencyNumbers / 10 > 0) &&
		_zombiesAppearControl->getZombiesAppearFrequency() == 0)
	{
		PlayMusic::playMusic("awooga");
	}

	/* ��ʬ��������ʾ�����Ӹ��� */
	if (_zombiesAppearControl->getZombiesAppearFrequency() > 0 && 
		_zombiesAppearControl->getZombiesAppearFrequency() % 5 == 0 && !_zombiesAppearControl->getIsShowWords())
	{
		if (informationLayerInformation->updateProgressBarFlag())
		{
			_zombiesAppearControl->setIsShowWords(true);
		}
	}
	if (_zombiesAppearControl->getZombiesAppearFrequency() % 5 != 0 && _zombiesAppearControl->getIsShowWords())
	{
		_zombiesAppearControl->setIsShowWords(false);
	}
}

int SGSSurvivalControlLayer::getZombiesNumbers()
{
	auto number = static_cast<int>(pow(_frequencyNumbers + 1, 2));
	if (number > 50)number = 50;
	return number + number % number / 2;
}

void SGSSurvivalControlLayer::setZombiesAppearFrequency(const unsigned int frequency)
{
	_frequencyNumbers = frequency;
}

unsigned int SGSSurvivalControlLayer::getZombiesAppearFrequency() const
{
	return _frequencyNumbers;
}
