/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.1.28
 *Email: 2117610943@qq.com
 */

#pragma once
#include <random>

#include "Zombies/Zombies.h"
#include "Based/GlobalVariable.h"

 /* ��ʬ���ֲ������� */
class ZombiesAppearControl
{
public:
	/**
	 *���ڽ����Ĳ�ͬ����������ͬ������ʬ
	 */
	int getZombiesNumbersForAppearFrequency(const unsigned int& ZombiesAppearFrequency);

	/**
	 *��ȡ��ʬ����
	 */
	int getZombiesAppearFrequency() const;

	/**
	 *��ȡ��һ����ʬ�Ƿ��Ѿ�����
	 */
	bool getLastFrequencyZombiesWasDeath() const;

	/**
	 *��ȡ��ʱ�Ƿ�ʼ
	 */
	bool getIsBegin() const;

	/**
	 *��ȡ�Ƿ���ʾ����
	 */
	bool getIsShowWords() const;

	/**
	 *��ȡʱ��
	 */
	double getTime() const;

	/**
	 *ʹÿһ�еĽ�ʬ�ȸ��ʳ���
	 */
	int getEqualProbabilityForRow();

	/**
	 *���ý�ʬ���ֲ���
	 * 1.���ݲ�������
	 */
	void setZombiesAppearFrequency(const unsigned int zombiesAppearFrequency);

	/**
	 *���ý�ʬ���ֲ���
	 * 2.������һ
	 */
	void setZombiesAppearFrequency();

	/**
	 *������һ����ʬ�Ƿ�����
	 */
	void setLastFrequencyZombiesWasDeath(bool lastFrequencyZombiesWasDeath);

	/**
	 *����ʱ������
	 */
	void setTimeClear();

	/**
	 *����ʱ������
	 */
	void setTimeAdd();
	void setTimeAdd(const double t);

	/**
	 *�����Ƿ�ʼ
	 */
	void setIsBegin(const bool isBegin);

	/**
	 *�����Ƿ���ʾ����
	 */
	void setIsShowWords(const bool isShowWords);

	/**
	 *������ͬ����Ľ�ʬ
	 */
	ZombiesType createDifferentTypeZombies(const unsigned int& ZombiesAppearFrequency);

	/**
	 *������ͬ����Ľ�ʬ
	 */
	ZombiesType createDifferentTypeZombies();

CC_CONSTRUCTOR_ACCESS:
	ZombiesAppearControl();
	~ZombiesAppearControl();

private:
	int _zombiesAppearFrequency;               // ��ʬ���ֲ���
	bool _lastFrequencyZombiesWasDeath;        // ��һ����ʬ������ 
	bool _isBegin;                             // ��ʱ�Ƿ�ʼ
	bool _isShowWords;                         // �Ƿ���ʾ����
	double _time;                              // ��ʱ
	OpenLevelData* _openLevelData;
	default_random_engine _random;             // ���������
	set<int> _judgeZombieRow;                  // �жϽ�ʬ������
	unsigned int _zombiesPosition[5] =         // ��ʬλ��
	{
		130,268,406,544,682
	};
};