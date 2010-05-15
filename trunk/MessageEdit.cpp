// MessageEdit.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "MessageEdit.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMessageEdit

CMessageEdit::CMessageEdit()
{
	m_iLineLimit = 100;
}

CMessageEdit::~CMessageEdit()
{
}


BEGIN_MESSAGE_MAP(CMessageEdit, CEdit)
	//{{AFX_MSG_MAP(CMessageEdit)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMessageEdit ���b�Z�[�W �n���h��

BOOL CMessageEdit::appendMessage(CString& message)
{
	CString str;
	int lines;
	BOOL erased = FALSE;

	GetWindowText(str);

	str += message;

	SetWindowText(str);

	lines = GetLineCount();

	if(lines > m_iLineLimit){
		// �폜���镶������Z���N�g
		str = str.Mid(LineIndex(lines - m_iLineLimit));
		SetWindowText(str);

		lines = m_iLineLimit;
		erased = TRUE;
	}


	// �ǉ������s�܂ŃX�N���[������
	LineScroll(m_iLineLimit + 10);

	return erased;
}
