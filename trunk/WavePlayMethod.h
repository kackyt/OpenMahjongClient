#pragma once
#include "libtype.h"

class CWavePlayMethod
{
public:
	CWavePlayMethod(void);
public:
	~CWavePlayMethod(void);
public:
	// ���t���鎟�̃o�b�t�@���l������(16bit�Œ菬���_) (NULL��Ԃ��Ă��悢)
	virtual sint16 * getNextWaveFix16(int length) = 0;
public:
	// ���t���鎟�̃o�b�t�@���l������(64bit���������_) (NULL��Ԃ��Ă��悢)
	virtual double * getNextWaveFloat64(int length) = 0;
};
