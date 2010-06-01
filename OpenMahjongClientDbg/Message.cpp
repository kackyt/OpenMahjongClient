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
// Message.cpp: CMessage �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "Message.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable:4786)

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CMessage::CMessage()
{

}

CMessage::~CMessage()
{

}

void CMessage::parseXML(IXMLDOMNodePtr pElem)
{
	IXMLDOMNodePtr pNode;
	IXMLDOMNodeListPtr pNodeList;
	CString text;
	BSTR pStr;
	int i;

	pNode = pElem->selectSingleNode(_T(TAG_TEXT));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		m_strText = pStr;
	}

	pNode = pElem->selectSingleNode(_T(TAG_FROM "/" TAG_PLAYER));

	if(pNode != NULL){
		m_playerFrom.parseXML(pNode);
	}

	pNodeList = pElem->selectNodes(_T(TAG_TO "/" TAG_PLAYER));

	if(pNodeList != NULL){
		for(i=0;i<pNodeList->Getlength();i++){
			CPlayer player;
			pNode = pNodeList->Getitem(i);
			player.parseXML(pNode);
			m_aPlayerTo.Add(player);
		}
	}
}

void CMessage::toXML(IXMLDOMDocumentPtr pDoc,IXMLDOMElementPtr pParent)
{
	IXMLDOMElementPtr pElemMes,pElemTo,pElemFrom,pElemText;
	int i;

	pElemMes = pDoc->createElement(_T(TAG_MESSAGE));

	pElemTo = pDoc->createElement(_T(TAG_TO));

	for(i=0;i<m_aPlayerTo.GetSize();i++){
		m_aPlayerTo[i].toXML(pDoc,pElemTo);
	}

	pElemMes->appendChild(pElemTo);


	pElemFrom = pDoc->createElement(_T(TAG_FROM));
	m_playerFrom.toXML(pDoc,pElemFrom);
	pElemMes->appendChild(pElemFrom);

	pElemText = pDoc->createElement(_T(TAG_TEXT));
	pElemText->appendChild(pDoc->createTextNode((LPCTSTR)m_strText));
	pElemMes->appendChild(pElemText);

	pParent->appendChild(pElemMes);

}

CMessage& CMessage::operator =(CMessage& value)
{
	m_aPlayerTo.Copy(value.m_aPlayerTo);

	m_playerFrom = value.m_playerFrom;

	m_strText = value.m_strText;

	return *this;
}


