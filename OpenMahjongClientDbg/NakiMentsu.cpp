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
// NakiMentsu.cpp: CNakiMentsu �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "NakiMentsu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CNakiMentsu::CNakiMentsu()
{
	m_iAite = 0;

}

CNakiMentsu::~CNakiMentsu()
{

}

void CNakiMentsu::parseXML(IXMLDOMNodePtr pElem)
{
	IXMLDOMNodePtr pNode;
	CString text;
	BSTR pStr;

	/* �X�[�p�[�N���X�̌Ăяo�� */
	pNode = pElem->selectSingleNode(_T(TAG_MENTSU));

	if(pNode != NULL){
		CMentsu::parseXML(pNode);
	}

	/* �X�J���[�f�[�^�̊i�[ */

	pNode = pElem->selectSingleNode(_T(TAG_AITE));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iAite = _tcstol((const TCHAR*)text,NULL,0);
	}

	/* �v�̊i�[ */
	pNode = pElem->selectSingleNode(_T(TAG_NAKIHAI "/" TAG_PAI));

	if(pNode != NULL){
		m_nakihai.parseXML(pNode);
	}

}

CNakiMentsu& CNakiMentsu::operator=(CNakiMentsu& value)
{
	m_iAite = value.m_iAite;
	m_nakihai = value.m_nakihai;
	m_iCategory = value.m_iCategory;
	m_aPaiList.Copy(value.m_aPaiList);

	return *this;
}

UINT CNakiMentsu::getNakiPos()
{
	if(m_aPaiList.GetSize() < 3){
		return 999;
	}
	if((UINT)m_nakihai == m_aPaiList[0] && m_nakihai.m_iId == m_aPaiList[0].m_iId){
		return 0;
	}else if((UINT)m_nakihai == m_aPaiList[1] && m_nakihai.m_iId == m_aPaiList[1].m_iId){
		return 1;
	}else if(m_aPaiList.GetSize() == 4 && (UINT)m_nakihai == m_aPaiList[3] && m_nakihai.m_iId == m_aPaiList[3].m_iId){
		return 3;
	}else{
		return 2;
	}

}
