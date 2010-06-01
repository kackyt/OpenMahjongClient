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
#include "StdAfx.h"
#include "WavePlayMatrix.h"

CWavePlayMatrixHook::CWavePlayMatrixHook(void)
{
}

CWavePlayMatrixHook::~CWavePlayMatrixHook(void)
{
}


CWavePlayMatrix::CWavePlayMatrix(void)
: m_channels(0)
, m_pWaveBuf(NULL)
, m_pHook(NULL)
{
	m_handleCounter = 1;

	m_matrix.InitHashTable(20); // �e�L�g�[�Ƀn�b�V���e�[�u��������������
}

CWavePlayMatrix::~CWavePlayMatrix(void)
{
	if(m_pWaveBuf) delete[] m_pWaveBuf;
}

CWavePlayMatrix::WPMHANDLE CWavePlayMatrix::appendChannel(CWavePlayMethod * pMethod, WPMCHMAP uMap, double volume)
{
	CWavePlayMatrixParam param;
	int i;

	param.pMethod = pMethod;
	param.uMap = uMap;
	param.volume = volume;
	param.channels = 0;

	for(i=0;i<32;i++){
		if(param.uMap & (1 << i)){
			param.channels++;
		}
	}

	m_matrix.SetAt(m_handleCounter,param);

	return m_handleCounter++;
}

BOOL CWavePlayMatrix::removeChannel(WPMHANDLE handle)
{
	return m_matrix.RemoveKey(handle);
}

sint16 * CWavePlayMatrix::getNextWaveFix16(int length)
{
	// 16bit �Œ菬���_�̓T�|�[�g�O
	return NULL;
}

f64 * CWavePlayMatrix::getNextWaveFloat64(int length)
{
	POSITION pos;
	WPMHANDLE handle;
	CWavePlayMatrixParam param;
	f64 *pBuf;
	int mCh,ch,i,samples;

	if(m_channels == 0) return NULL;

	if(!m_pWaveBuf){
		m_pWaveBuf = new f64[length];
	}

	samples = length / m_channels;

	/* Map�̒���S���Ȃ߂� */
	pos = m_matrix.GetStartPosition();

	ZeroMemory(m_pWaveBuf,sizeof(f64)*length);

	if(m_pHook){
		/* �t�b�N���[�`�����Ăяo�� */
		m_pHook->matrixStart(this);
	}

	while(pos != NULL){
		m_matrix.GetNextAssoc(pos,handle,param);
		pBuf = param.pMethod->getNextWaveFloat64(param.channels*samples);
		if(pBuf != NULL){
			ch = 0;
			for(mCh=0;mCh<m_channels;mCh++){
				if(param.uMap & (1 << mCh)){
					for(i=0;i<samples;i++){
						m_pWaveBuf[i*m_channels + mCh] += pBuf[i*param.channels + ch] * param.volume;
					}
					ch++;
				}
			}
		}
	}

	if(m_pHook){
		/* �t�b�N���[�`�����Ăяo�� */
		m_pHook->matrixEnd(this,m_pWaveBuf,length);
	}

	return m_pWaveBuf;
}

void CWavePlayMatrix::setMaxChannels(int channels)
{
	f64 * pBuf = m_pWaveBuf;
	m_channels = channels;
	if(pBuf){
		m_pWaveBuf = NULL;
		delete[] pBuf;
	}
}

CWavePlayMethod * CWavePlayMatrix::getPlayData(WPMHANDLE handle)
{
	CWavePlayMatrixParam methodParam;
	BOOL success;

	success = m_matrix.Lookup(handle,methodParam);

	return success ? methodParam.pMethod : NULL; 
}

int CWavePlayMatrix::getPosition(CWavePlayMethod * pMethod)
{
	POSITION pos;
	WPMHANDLE handle;
	CWavePlayMatrixParam param;
	int ret = 0;
	/* Map�̒���S���Ȃ߂� */
	pos = m_matrix.GetStartPosition();

	while(pos != NULL){
		m_matrix.GetNextAssoc(pos,handle,param);
		if(param.pMethod == pMethod){
			return ret;
		}
		ret++;		
	}
	return -1;
}

int CWavePlayMatrix::getUpperBoundChannel(void)
{
	POSITION pos;
	WPMHANDLE handle;
	CWavePlayMatrixParam param;
	int max = -1,mCh;

	/* Map�̒���S���Ȃ߂āA��ԏ�̃`�����l���ԍ���Ԃ� */
	pos = m_matrix.GetStartPosition();

	while(pos != NULL){
		m_matrix.GetNextAssoc(pos,handle,param);
		for(mCh=max;mCh<32;mCh++){
			if(param.uMap & (1 << mCh)){
				max = mCh;
			}
		}
	}

	return max;
}

void CWavePlayMatrix::setVolume(WPMHANDLE handle, double volume)
{
	CWavePlayMatrixParam methodParam;
	BOOL success;

	success = m_matrix.Lookup(handle,methodParam);

	if(success){
		methodParam.volume = volume;
		m_matrix.SetAt(handle,methodParam);
	}
}

void CWavePlayMatrix::setChannelMap(WPMHANDLE handle, WPMCHMAP uNewMap)
{
	CWavePlayMatrixParam methodParam;
	BOOL success;

	success = m_matrix.Lookup(handle,methodParam);

	if(success){
		methodParam.uMap = uNewMap;
		m_matrix.SetAt(handle,methodParam);
	}
}

BOOL CWavePlayMatrix::getChannelMap(WPMHANDLE handle,WPMCHMAP &uMap)
{
	CWavePlayMatrixParam methodParam;
	BOOL success;

	success = m_matrix.Lookup(handle,methodParam);

	if(success){
		uMap = methodParam.uMap;
	}

	return success;
}

BOOL CWavePlayMatrix::getVolume(WPMHANDLE handle, double & volume)
{
	CWavePlayMatrixParam methodParam;
	BOOL success;

	success = m_matrix.Lookup(handle,methodParam);

	if(success){
		volume = methodParam.volume;
	}

	return success;
}

void CWavePlayMatrix::setHook(CWavePlayMatrixHook * pHook)
{
	m_pHook = pHook;
}
