// Event.cpp: CEvent �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "Event.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CEvent::CEvent()
{

}

CEvent::~CEvent()
{

}

void CEvent::parseXML(IXMLDOMNodePtr pElem)
{
	IXMLDOMNodePtr pNode;

	/* �X�J���[�f�[�^�̊i�[ */

	pNode = pElem->selectSingleNode(_T("command"));

	if(pNode != NULL){
		m_command.parseXML(pNode);
	}

	pNode = pElem->selectSingleNode(_T("result"));

	if(pNode != NULL){
		m_result.parseXML(pNode);
	}
}
