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
#include "afxmt.h"
#include "waveplaymethod.h"

class CWavePlayer :
	public CWavePlayMethod
{
	friend void CALLBACK waveOutCallback(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance,DWORD dwParam1,DWORD dwParam2);
private:
	CWavePlayMethod *m_pMethod;
public:
	CWavePlayer(void);
	CWavePlayer(CWavePlayMethod *pPlayMethod,int uBufNum,int uBufSize);
public:
	~CWavePlayer(void);
public:
	// WaveOut �f�o�C�X���J��
	BOOL openDevice(UINT uDevID);

private:
	HANDLE m_hHeap;
private:
	int m_uBufSize;
private:
	int m_uBufNum;
private:
	LPWAVEHDR m_pWaveHdr;
private:
	void **m_ppWaveBuf;
private:
	HWAVEOUT m_hWaveout;
private:
	WAVEFORMATEX m_wfxWaveForm;
public:
	// �Đ����J�n����
	BOOL play(void);
public:
	sint16 * CWavePlayer::getNextWaveFix16(int length);
	double * CWavePlayer::getNextWaveFloat64(int length);
	// �Đ�����PCM�t�H�[�}�b�g��ݒ肷��
	BOOL setPlayFormat(WAVEFORMATEX * pFormat);
	void setWaveData(LPWAVEHDR pHeader);
public:
	BOOL closeDevice(void);
public:
	BOOL stop(void);

private:
	long m_lPrepPage;
public:
	int getBufferSize(void);
public:
	long getReadyBlocks(void);
public:
	int getPlayedSamples(void);
public:
	void create(int uBufNum, int uBufSize);
public:
	void setMethod(CWavePlayMethod * pPlayMethod);
public:
	void destroy(void);
public:
	int getBufferedSamples(void);
public:
	void getPlayFormat(WAVEFORMATEX * pFormat);
	CEvent m_evCallback;
};
