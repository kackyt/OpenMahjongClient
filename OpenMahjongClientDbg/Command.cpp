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
// Command.cpp: CCommand �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "Command.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable:4786)

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CCommand::CCommand()
{
	m_iId = 0;
	m_iType = 0;

}

CCommand::~CCommand()
{

}

void CCommand::parseXML(IXMLDOMNodePtr pElem)
{
	IXMLDOMNodePtr pNode;
	CString text;
	BSTR pStr;

	/* �X�J���[�f�[�^�̊i�[ */

	pNode = pElem->selectSingleNode(_T(TAG_ID));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iId = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_TYPE));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iType = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_PAI));

	if(pNode != NULL){
		m_pai.parseXML(pNode);
	}

	pNode = pElem->selectSingleNode(_T(TAG_PLAYER));

	if(pNode != NULL){
		m_player.parseXML(pNode);
	}

	pNode = pElem->selectSingleNode(_T(TAG_NAKIMENTSU));

	if(pNode != NULL){
		m_mentsu.parseXML(pNode);
	}else{
		pNode= pElem->selectSingleNode(_T(TAG_MENTSU));

		if(pNode != NULL){
			m_mentsu.parseXML(pNode);
		}
	}

	pNode = pElem->selectSingleNode(_T(TAG_RULE));

	if(pNode != NULL){
		m_rule.parseXML(pNode);
	}

}

CCommand& CCommand::operator=(CCommand& value)
{
	m_iId = value.m_iId;
	m_iType = value.m_iType;
	m_mentsu = value.m_mentsu;
	m_pai = value.m_pai;
	m_player = value.m_player;

	return *this;
}

void CCommand::toXML(IXMLDOMDocumentPtr pDoc,IXMLDOMElementPtr pParent)
{
	IXMLDOMElementPtr pElemCom,pElemID;
	CString str;

	pElemCom = pDoc->createElement(_T(TAG_COMMAND));
	pParent->appendChild(pElemCom);
	pElemID = pDoc->createElement(_T(TAG_ID));
	pElemCom->appendChild(pElemID);

	str.Format(_T("%d"),m_iId);

	pElemID->appendChild(pDoc->createTextNode((LPCTSTR)str));

	m_player.toXML(pDoc,pElemCom);

	if(m_rule.m_bActive){
		m_rule.toXML(pDoc,pElemCom);
	}
}
