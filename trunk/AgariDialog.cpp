// AgariDialog.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "AgariDialog.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CAgariDialog �_�C�A���O


CAgariDialog::CAgariDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CAgariDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CAgariDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CAgariDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CAgariDialog)
	DDX_Control(pDX, IDC_AGARIYAKU, m_staAgariyaku);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CAgariDialog, CDialog)
	//{{AFX_MSG_MAP(CAgariDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CAgariDialog ���b�Z�[�W �n���h��
