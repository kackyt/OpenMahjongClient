// Mentsu.cpp: CMentsu �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "Mentsu.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CMentsu::CMentsu()
{

}

CMentsu::~CMentsu()
{

}

void CMentsu::parseXML(IXMLDOMNodePtr pElem)
{
	IXMLDOMNodePtr pNode;
	IXMLDOMNodeListPtr pNodeList;
	CString text;
	BSTR pStr;
	int i;

	/* �X�J���[�f�[�^�̊i�[ */

	pNode = pElem->selectSingleNode(_T(TAG_CATEGORY));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iCategory = _tcstol((const TCHAR*)text,NULL,0);
	}

	/* �v�̊i�[ */
	m_aPaiList.RemoveAll();
	pNodeList = pElem->selectNodes(_T(TAG_PAI));

	if(pNodeList != NULL){
		for(i=0;i<pNodeList->Getlength();i++){
			CPai pai;
			pNode = pNodeList->Getitem(i);
			pai.parseXML(pNode);
			m_aPaiList.Add(pai);
		}
	}

}

CMentsu& CMentsu::operator=(CMentsu& value)
{
	m_iCategory = value.m_iCategory;
	m_aPaiList.Copy(value.m_aPaiList);

	return *this;
}

