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
#include "WavePlayer.h"

CWavePlayer::CWavePlayer()
: m_lPrepPage(0)
, m_hHeap(NULL)
, m_hWaveout(NULL)
{
}

CWavePlayer::CWavePlayer(CWavePlayMethod *pPlayMethod,int uBufNum,int uBufSize)
: m_lPrepPage(0)
, m_hHeap(NULL)
, m_hWaveout(NULL)
{
	create(uBufNum,uBufSize);
	setMethod(pPlayMethod);
}

CWavePlayer::~CWavePlayer(void)
{
	destroy();
}

sint16 * CWavePlayer::getNextWaveFix16(int length){
	return m_pMethod->getNextWaveFix16(length);
}

double * CWavePlayer::getNextWaveFloat64(int length){
	return m_pMethod->getNextWaveFloat64(length);
}



// WaveOut �f�o�C�X���J��
BOOL CWavePlayer::openDevice(UINT uDevID)
{
	if (m_hWaveout)
	{
		return FALSE;
	}
	MMRESULT ret = waveOutOpen(
		&m_hWaveout,
		uDevID,
		&m_wfxWaveForm,
		(DWORD)waveOutCallback,
		(DWORD)this,
		CALLBACK_FUNCTION);

	if(ret != MMSYSERR_NOERROR){
		return FALSE;
	}
	return TRUE;
}

// �Đ����J�n����
BOOL CWavePlayer::play(void)
{
	int i;
	MMRESULT ret;

	for(i=0;i<m_uBufNum;i++){
		LPWAVEHDR pHeader = &m_pWaveHdr[i];
		pHeader->lpData = (LPSTR)m_ppWaveBuf[i];
		pHeader->dwBufferLength = m_uBufSize;
		pHeader->dwUser = 0;
		pHeader->dwFlags = 0;
		pHeader->dwLoops = 0;

		setWaveData(pHeader);

		ret = waveOutPrepareHeader(m_hWaveout,pHeader,sizeof(WAVEHDR));

		if(ret != MMSYSERR_NOERROR){
			break;
		}

		ret = waveOutWrite(m_hWaveout,pHeader,sizeof(WAVEHDR));
		++m_lPrepPage;

		if(ret != MMSYSERR_NOERROR){
			break;
		}

	}

	if(ret == MMSYSERR_NOERROR) m_evCallback.SetEvent();
	return (ret == MMSYSERR_NOERROR) ? TRUE : FALSE;
}

// �Đ�����PCM�t�H�[�}�b�g��ݒ肷��
BOOL CWavePlayer::setPlayFormat(WAVEFORMATEX * pFormat)
{
	if(m_hWaveout){
		return FALSE;
	}

	m_wfxWaveForm = *pFormat;

	return TRUE;
}


void CWavePlayer::setWaveData(LPWAVEHDR pHeader)
{
	sint16 *pWaveFix16;
	double *pWaveFloat64;
	int i;

	pWaveFix16 = getNextWaveFix16(m_uBufSize>>1);
	if(pWaveFix16 != NULL){
		memcpy(pHeader->lpData,pWaveFix16,m_uBufSize);
	}else{
		pWaveFloat64 = getNextWaveFloat64(m_uBufSize>>1);
		pWaveFix16 = (sint16 *)pHeader->lpData;
		if(pWaveFloat64 != NULL){
			for(i=0;i<m_uBufSize>>1;i++){
				// �N���b�v����
				if(pWaveFloat64[i] > 1.0){
					pWaveFix16[i] = 32767;
				}else if(pWaveFloat64[i] < -1.0){
					pWaveFix16[i] = -32768;
				}else{
					pWaveFix16[i] = (sint16)(pWaveFloat64[i] * 32767.0); // 16bit�Œ菬���_�ɃL���X�g
				}
			}
		}else{
			ZeroMemory(pWaveFix16,m_uBufSize);
		}
	}
}


// �R�[���o�b�N�֐�
static void CALLBACK waveOutCallback(HWAVEOUT hwo, UINT uMsg, DWORD dwInstance,DWORD dwParam1,DWORD dwParam2)
{
	MMRESULT ret;
	CWavePlayer *pInst = (CWavePlayer *)dwInstance;
	LPWAVEHDR pHdr =(LPWAVEHDR)dwParam1;

	pInst->m_evCallback.ResetEvent();

	switch(uMsg){
		case MM_WOM_OPEN:
			break;
		case MM_WOM_CLOSE:
			break;
		case MM_WOM_DONE:
			if(pInst->m_lPrepPage == 0) break;
			if (!(pHdr->dwFlags & WHDR_DONE)) break;			// �܂����t���ł���
			if (!(pHdr->dwFlags & WHDR_PREPARED)) break;		// �������ꂽ�o�b�t�@�ł͂Ȃ�


			ret = waveOutUnprepareHeader(hwo,pHdr,sizeof(WAVEHDR));
			if(ret != MMSYSERR_NOERROR) break;
			pInst->m_lPrepPage--;
			pInst->setWaveData(pHdr);

			pHdr->dwFlags = 0;

			ret = waveOutPrepareHeader(hwo,pHdr,sizeof(WAVEHDR));

			if(ret != MMSYSERR_NOERROR) break;

			ret = waveOutWrite(hwo,pHdr,sizeof(WAVEHDR));

			if(ret != MMSYSERR_NOERROR) break;
			pInst->m_lPrepPage++;
			break;
		default:
			break;
	}

	pInst->m_evCallback.SetEvent();
}

BOOL CWavePlayer::closeDevice(void)
{
	if (! m_hWaveout)		return TRUE;

	MMRESULT ret = waveOutClose(m_hWaveout);
	m_hWaveout = NULL;

	if (ret != MMSYSERR_NOERROR)
	{
		return FALSE;
	}
	return TRUE;
}

BOOL CWavePlayer::stop(void)
{
	if (! m_hWaveout)		return TRUE;
	// �R�[���o�b�N�֐��̎��s�I����ҋ@����
	WaitForSingleObject(m_evCallback.m_hObject,INFINITE);
	m_lPrepPage = 0;

	MMRESULT ret = waveOutReset(m_hWaveout);

	if (ret != MMSYSERR_NOERROR)
	{
		return FALSE;
	}

	for (int i=0; i<m_uBufNum; i++)
	{
		LPWAVEHDR pHeader = &m_pWaveHdr[i];

		if (! (pHeader->dwFlags & WHDR_PREPARED))	continue;
		if (! (pHeader->dwFlags & WHDR_DONE))		continue;

		ret = waveOutUnprepareHeader(m_hWaveout, pHeader, sizeof(WAVEHDR));

		if (ret != MMSYSERR_NOERROR)
		{
			return FALSE;
		}
	}

	return ret == MMSYSERR_NOERROR ? TRUE:FALSE;
}

int CWavePlayer::getBufferSize(void)
{
	return m_uBufSize;
}

long CWavePlayer::getReadyBlocks(void)
{
	int i;
	long count = 0;
	LPWAVEHDR pHdr = m_pWaveHdr;

	for(i=0;i<m_uBufNum;i++){
		if(!(pHdr->dwFlags & WHDR_DONE)) count++;
		pHdr++;
	}
	return count;
}

int CWavePlayer::getPlayedSamples(void)
{
	MMTIME mmt;
	mmt.wType = TIME_SAMPLES;

	waveOutGetPosition(m_hWaveout,&mmt,sizeof(MMTIME));
	return mmt.u.sample;
}

void CWavePlayer::create(int uBufNum, int uBufSize)
{
	int i;
	m_hWaveout = NULL;
	m_uBufNum = uBufNum;
	m_uBufSize = uBufSize;
	m_hHeap = HeapCreate(0,0,0);
	m_pWaveHdr = (LPWAVEHDR)HeapAlloc(m_hHeap,HEAP_ZERO_MEMORY,sizeof(WAVEHDR)*uBufNum);
	m_ppWaveBuf = (void **)HeapAlloc(m_hHeap,HEAP_ZERO_MEMORY,sizeof(void *)*uBufNum);
	for(i=0;i<uBufNum;i++){
		m_ppWaveBuf[i] = HeapAlloc(m_hHeap,HEAP_ZERO_MEMORY,uBufSize);
	}

	m_wfxWaveForm.wFormatTag = WAVE_FORMAT_PCM;
	m_wfxWaveForm.nChannels = 1;
	m_wfxWaveForm.nSamplesPerSec = 44100;
	m_wfxWaveForm.wBitsPerSample = 16;
	m_wfxWaveForm.cbSize = 0;
	m_wfxWaveForm.nBlockAlign = m_wfxWaveForm.wBitsPerSample * m_wfxWaveForm.nChannels / 8;
	m_wfxWaveForm.nAvgBytesPerSec = m_wfxWaveForm.nSamplesPerSec * m_wfxWaveForm.nBlockAlign;
}

void CWavePlayer::setMethod(CWavePlayMethod * pPlayMethod)
{
	m_pMethod = pPlayMethod;
}

void CWavePlayer::destroy(void)
{
	if(m_hHeap) HeapDestroy(m_hHeap);
	m_hHeap = NULL;
}

int CWavePlayer::getBufferedSamples(void)
{
	return (getReadyBlocks()*getBufferSize() - (getPlayedSamples() % getBufferSize())) / sizeof(sint16);
}


void CWavePlayer::getPlayFormat(WAVEFORMATEX * pFormat)
{
	*pFormat = m_wfxWaveForm;
}
