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
	if((UINT)m_nakihai == m_aPaiList[0]){
		return 0;
	}else if((UINT)m_nakihai == m_aPaiList[1]){
		return 1;
	}else{
		return 2;
	}

}
