/****************************************************************************************
 * Copyright (c) 2010, Takaya Kakizaki(kacky)
 * All rights reserved.

  �\�[�X�R�[�h�`�����o�C�i���`�����A�ύX���邩���Ȃ������킸�A�ȉ��̏����𖞂����ꍇ�Ɍ���A�ĔЕz����юg�p��������܂��B 

  �E�\�[�X�R�[�h���ĔЕz����ꍇ�A��L�̒��쌠�\���A�{�����ꗗ�A����щ��L�Ɛӏ������܂߂邱�ƁB 

  �E�o�C�i���`���ōĔЕz����ꍇ�A�Еz���ɕt���̃h�L�������g���̎����ɁA��L�̒��쌠�\���A�{�����ꗗ�A����щ��L�Ɛӏ������܂߂邱�ƁB 

  �E���ʂɂ����ʂ̋��Ȃ��ɁA�{�\�t�g�E�F�A����h���������i�̐�`�܂��͔̔����i�ɁA�I�[�v�������̖��O�܂��̓R���g���r���[�^�[�̖��O���g�p���Ă͂Ȃ�Ȃ��B


  �{�\�t�g�E�F�A�́A���쌠�҂���уR���g���r���[�^�[�ɂ���āu����̂܂܁v�񋟂���Ă���A�����َ����킸�A
  ���ƓI�Ȏg�p�\���A����ѓ���̖ړI�ɑ΂���K�����Ɋւ���Öق̕ۏ؂��܂߁A�܂�����Ɍ��肳��Ȃ��A�����Ȃ�ۏ؂�����܂���B
  ���쌠�҂��R���g���r���[�^�[���A���R�̂�������킸�A ���Q�����̌�����������킸�A���ӔC�̍������_��ł��邩���i�ӔC�ł��邩
  �i�ߎ����̑��́j�s�@�s�ׂł��邩���킸�A���ɂ��̂悤�ȑ��Q����������\����m�炳��Ă����Ƃ��Ă��A�{�\�t�g�E�F�A�̎g�p�ɂ���Ĕ�������
  �i��֕i�܂��͑�p�T�[�r�X�̒��B�A�g�p�̑r���A�f�[�^�̑r���A���v�̑r���A�Ɩ��̒��f���܂߁A�܂�����Ɍ��肳��Ȃ��j
  ���ڑ��Q�A�Ԑڑ��Q�A�����I�ȑ��Q�A���ʑ��Q�A�����I���Q�A�܂��͌��ʑ��Q�ɂ��āA��ؐӔC�𕉂�Ȃ����̂Ƃ��܂��B 

****************************************************************************************/
#pragma once
#include "waveplaymethod.h"

class CWavePlayMatrixHook;

class CWavePlayMatrix :
	public CWavePlayMethod
{
public:
	typedef int WPMHANDLE;
	typedef unsigned int WPMCHMAP;
	typedef struct {
		CWavePlayMethod *pMethod;
		WPMCHMAP        uMap;
		double          volume;
		int             channels;
	} CWavePlayMatrixParam;
	CWavePlayMatrix(void);
public:
	~CWavePlayMatrix(void);
private:
	CMap<WPMHANDLE,WPMHANDLE,CWavePlayMatrixParam,CWavePlayMatrixParam&> m_matrix;
	WPMHANDLE m_handleCounter;
public:
	WPMHANDLE appendChannel(CWavePlayMethod * pMethod, WPMCHMAP uMap, double volume = 1.0);
	BOOL removeChannel(WPMHANDLE handle);
public:
	sint16 * getNextWaveFix16(int length);
public:
	f64 * getNextWaveFloat64(int length);
public:
	void setMaxChannels(int channels);
public:
	int m_channels;
public:
	f64 *m_pWaveBuf;
public:
	CWavePlayMethod * getPlayData(WPMHANDLE handle);
public:
	int getPosition(CWavePlayMethod * pMethod);
public:
	int getUpperBoundChannel(void);
public:
	void setVolume(WPMHANDLE handle, double newVolume);
public:
	void setChannelMap(WPMHANDLE handle, WPMCHMAP uNewMap);
public:
	BOOL getChannelMap(WPMHANDLE handle,WPMCHMAP &uMap);
public:
	BOOL getVolume(WPMHANDLE handle, double & volume);
public:
	CWavePlayMatrixHook *m_pHook;
public:
	void setHook(CWavePlayMatrixHook * pHook);
};

class CWavePlayMatrixHook
{
public:
	CWavePlayMatrixHook(void);
public:
	~CWavePlayMatrixHook(void);
public:
	virtual void matrixStart(CWavePlayMatrix * pMatrix) = 0;
public:
	virtual void matrixEnd(CWavePlayMatrix * pMatrix,f64 *pWav,int length) = 0;
};
