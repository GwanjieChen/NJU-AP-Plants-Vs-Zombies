/**
 *Copyright (c) 2020 LZ.All Right Reserved
 *Author : LZ
 *Date: 2020.2.18
 *Email: 2117610943@qq.com
 */

#pragma once
#include "Bullet.h"

class Pea :public Bullet
{
public:
	/**
	 *�����Ƿ�ȼ��
	 */
	virtual void setIsFire(const bool isFire);

	/**
	 *����ȼ�մ���
	 */
	virtual void setPeaFireNumbers(const int fireNumbers);

	/**
	 *�����ӵ�ȼ�մ���
	 */
	virtual void addPeaFireNumbers();

	/**
	 *���û����׮���
	 */
	virtual void setTorchwoodTag(const int torchwoodTag);

	/**
	 *��ȡ�Ƿ�ȼ��
	 */
	virtual bool getIsFire() const;

	/**
	 *��ȡȼ�մ���
	 */
	virtual int getPeaFireNumbers() const;

	/**
	 *��ȡ�����׮���
	 */
	virtual int getTorchwoodTag() const;

protected:
	/**
	 *�����㶹
	 */
	virtual void createBullet() override;

	/**
	 *�㶹�뽩ʬ��ײ�ͼ��
	 */
	virtual void bulletAndZombiesCollision() override;

	/**
	 *�����㶹��ը����
	 */
	virtual void  createPeaExplode();

	/**
	 *�ӵ���ʼ��
	 */
	virtual void bulletInit() override;

	/**
	 *�����ӵ�Ӱ��
	 */
	virtual void createShadow() override;

	/**
	 *�ӵ�������ʬ
	 */
	virtual void bulletAttackZombies();

	/**
	 *���ӵ�������ʬ
	 */
	virtual void fireBulletAttackZombies();

CC_CONSTRUCTOR_ACCESS:
	Pea(Node* node = nullptr);
	~Pea();

private:
	void attackZombies();
	float getZombieInExplodeRange(Zombies* zombie);

protected:
	bool _isFire;                         // �Ƿ�ȼ�� 
	int _fireNumbers;                     // ȼ�մ���
	int _torchwoodTag;                    // �����׮���
	string _peaAnimationName;             // �㶹��������
};
