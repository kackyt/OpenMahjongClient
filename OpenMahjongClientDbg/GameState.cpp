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
// GameState.cpp: CGameState �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "GameState.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CGameState::CGameState()
{
	m_iZikaze = 1;
	m_iCount = 1;
	m_bTsumo = FALSE;
	m_bRiichi = FALSE;
	m_bOya = FALSE;
	m_bIppatsu = FALSE;
	m_bNaki = FALSE;
}

CGameState::~CGameState()
{

}

void CGameState::parseXML(IXMLDOMNodePtr pElem)
{
	IXMLDOMNodePtr pNode;
	IXMLDOMNodeListPtr pNodeList;
	CString text;
	BSTR pStr;
	int i;

	/* �X�J���[�f�[�^�̊i�[ */

	pNode = pElem->selectSingleNode(_T(TAG_ZIKAZE));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iZikaze = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_COUNT));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iCount = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_OYA));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_bOya = text == _T("true") ? TRUE : FALSE;
	}

	pNode = pElem->selectSingleNode(_T(TAG_NAKI));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_bNaki = text == _T("true") ? TRUE : FALSE;
	}

	pNode = pElem->selectSingleNode(_T(TAG_RIICHI));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_bRiichi = text == _T("true") ? TRUE : FALSE;
	}

	pNode = pElem->selectSingleNode(_T(TAG_IPPATSU));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_bIppatsu = text == _T("true") ? TRUE : FALSE;
	}

	pNode = pElem->selectSingleNode(_T(TAG_TSUMO));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_bTsumo = text == _T("true") ? TRUE : FALSE;
	}

	/* ���ʎq�̊i�[ */
	m_aNakiList.RemoveAll();
	pNodeList = pElem->selectNodes(_T(TAG_NAKILIST "/" TAG_NAKIMENTSU));

	if(pNodeList != NULL){
		for(i=0;i<pNodeList->Getlength();i++){
			CNakiMentsu mentsu;
			pNode = pNodeList->Getitem(i);
			mentsu.parseXML(pNode);
			m_aNakiList.Add(mentsu);
		}
	}

}

CGameState& CGameState::operator =(CGameState& value)
{
	int i;
	m_aNakiList.RemoveAll();
	for(i=0;i<value.m_aNakiList.GetSize();i++){
		m_aNakiList.Add(value.m_aNakiList[i]);
	}
	m_bIppatsu = value.m_bIppatsu;
	m_bOya = value.m_bOya;
	m_bRiichi = value.m_bRiichi;
	m_bTsumo = value.m_bTsumo;
	m_iZikaze = value.m_iZikaze;

	return *this;
}
