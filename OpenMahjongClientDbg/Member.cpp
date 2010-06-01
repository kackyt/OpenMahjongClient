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
// Member.cpp: CMember �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "Member.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CMember::CMember()
{

}

CMember::~CMember()
{

}

void CMember::parseXML(IXMLDOMNodePtr pElem)
{
	IXMLDOMNodePtr pNode;
	IXMLDOMNodeListPtr pNodeList;
	CString text;
	BSTR pStr;
	int i;

	/* �X�J���[�f�[�^�̊i�[ */

	pNode = pElem->selectSingleNode(_T(TAG_MSTATE));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iState = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_POINT));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iPoint = _tcstol((const TCHAR*)text,NULL,0);
	}

	/* �Ŕv�̊i�[ */
	m_aDahai.RemoveAll();
	pNodeList = pElem->selectNodes(_T(TAG_DAHAI "/ "  TAG_PAI));

	if(pNodeList != NULL){
		for(i=0;i<pNodeList->Getlength();i++){
			CPai pai;
			pNode = pNodeList->Getitem(i);
			pai.parseXML(pNode);
			m_aDahai.Add(pai);
		}
	}

	/* ��v�̊i�[ */
	m_aTehai.RemoveAll();
	pNodeList = pElem->selectNodes(_T(TAG_TEHAI "/" TAG_PAI));

	if(pNodeList != NULL){
		for(i=0;i<pNodeList->Getlength();i++){
			CPai pai;
			pNode = pNodeList->Getitem(i);
			pai.parseXML(pNode);
			m_aTehai.Add(pai);
		}
	}

	/* �R�}���h���X�g�̊i�[ */
	m_aCommandList.RemoveAll();
	pNodeList = pElem->selectNodes(_T(TAG_COMMANDLIST "/" TAG_COMMAND));

	if(pNodeList != NULL){
		for(i=0;i<pNodeList->Getlength();i++){
			CCommand com;
			pNode = pNodeList->Getitem(i);
			com.parseXML(pNode);
			m_aCommandList.Add(com);
		}
	}

	/* �c���v�̊i�[ */
	pNode = pElem->selectSingleNode(_T(TAG_TSUMOHAI));

	if(pNode != NULL){
		m_gamestate.m_bTsumo = TRUE;
		pNode = pElem->selectSingleNode(_T(TAG_TSUMOHAI "/" TAG_PAI));
		if(pNode != NULL){
			m_tsumohai.parseXML(pNode);
		}
	}else{
		m_gamestate.m_bTsumo = FALSE;
	}


	/* �v���[���[�̊i�[ */

	pNode = pElem->selectSingleNode(_T(TAG_PLAYER));

	if(pNode != NULL){
		m_player.parseXML(pNode);
	}

	/* �Q�[����Ԃ̊i�[ */
	pNode = pElem->selectSingleNode(_T(TAG_GAMESTATE));

	if(pNode != NULL){
		m_gamestate.parseXML(pNode);
	}

	/* ������̊i�[ */
	m_aResultList.RemoveAll();
	pNodeList = pElem->selectNodes(_T(TAG_RESULTLIST "/" TAG_RESULT));

	if(pNodeList != NULL){
		for(i=0;i<pNodeList->Getlength();i++){
			CResult res;
			pNode = pNodeList->Getitem(i);
			res.parseXML(pNode);
			m_aResultList.Add(res);
		}
	}

}

BOOL CMember::isExecutableCommand(CCommand& command)
{
	int i;

	for(i=0;i<m_aCommandList.GetSize();i++){
		if(m_aCommandList[i].m_iId == command.m_iId){
			return TRUE;
		}
	}

	return FALSE;
}

CMember& CMember::operator =(CMember& value)
{
	int i;
	m_aCommandList.RemoveAll();
	for(i=0;i<value.m_aCommandList.GetSize();i++){
		m_aCommandList.Add(value.m_aCommandList[i]);
	}
	m_aDahai.Copy(value.m_aDahai);
	m_aResultList.RemoveAll();
	for(i=0;i<value.m_aResultList.GetSize();i++){
		m_aResultList.Add(value.m_aResultList[i]);
	}
	m_aTehai.Copy(value.m_aTehai);
	m_gamestate = value.m_gamestate;
	m_iPoint = value.m_iPoint;
	m_iState = value.m_iState;
	m_player = value.m_player;

	return *this;
}
