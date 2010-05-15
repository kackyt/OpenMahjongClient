// ConnectDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "ConnectDlg.h"
#include "OpenMahjongClientDbgDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg �_�C�A���O


CConnectDlg::CConnectDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CConnectDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CConnectDlg)
	m_playerName = _T("");
	m_iSession = 0;
	m_strDst = _T("");
	m_iNewSess = 0;
	//}}AFX_DATA_INIT
}


void CConnectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CConnectDlg)
	DDX_Control(pDX, IDC_CMBCOMP3, m_cmbComp3);
	DDX_Control(pDX, IDC_CMBCOMP2, m_cmbComp2);
	DDX_Control(pDX, IDC_CMBCOMP1, m_cmbComp1);
	DDX_Text(pDX, IDC_PNAME, m_playerName);
	DDX_Text(pDX, IDC_SESSION, m_iSession);
	DDX_CBString(pDX, IDC_CONNECTDST, m_strDst);
	DDX_Radio(pDX, IDC_RADIONEW, m_iNewSess);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CConnectDlg, CDialog)
	//{{AFX_MSG_MAP(CConnectDlg)
	ON_BN_CLICKED(IDC_BTNRULE, OnBtnrule)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg ���b�Z�[�W �n���h��

BOOL CConnectDlg::PreTranslateMessage(MSG* pMsg) 
{
	// �L�[�������ꂽ�Ƃ�
	if( pMsg->message == WM_KEYDOWN ){
		// �����Ɛ���
		switch(pMsg->wParam){
			case VK_RETURN:
			case VK_ESCAPE:
				return TRUE;
			default:
				break;
		}
	}
	
	return CDialog::PreTranslateMessage(pMsg);
}

BOOL CConnectDlg::OnInitDialog() 
{
	COpenMahjongClientDbgDlg *pObj = (COpenMahjongClientDbgDlg *)m_pTopObj;
	int i;
	CDialog::OnInitDialog();
	m_iNewSess = 0;

	m_cmbComp1.AddString(_T("�Ȃ�"));
	m_cmbComp1.SetCurSel(0);
	m_cmbComp2.AddString(_T("�Ȃ�"));
	m_cmbComp2.SetCurSel(0);
	m_cmbComp3.AddString(_T("�Ȃ�"));
	m_cmbComp3.SetCurSel(0);
	for(i=0;i<pObj->m_iLogicNum;i++){
		m_cmbComp1.AddString(pObj->compName[i]);
		m_cmbComp2.AddString(pObj->compName[i]);
		m_cmbComp3.AddString(pObj->compName[i]);
	}


	UpdateData(FALSE);
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CConnectDlg::OnOK() 
{
	UpdateData(TRUE);

	if(m_strDst == _T("")){
		MessageBox(_T("�ڑ�������Ă�������"));
		return;
	}

	if(m_iNewSess < 2 && m_playerName == _T("")){
		MessageBox(_T("�v���[���[�������Ă�������"));
		return;
	}

	m_cmbComp1.GetLBText(m_cmbComp1.GetCurSel(),m_strComp1);
		
	m_cmbComp2.GetLBText(m_cmbComp2.GetCurSel(),m_strComp2);

	m_cmbComp3.GetLBText(m_cmbComp3.GetCurSel(),m_strComp3);
	
	CDialog::OnOK();
}

void CConnectDlg::OnBtnrule() 
{
	// TODO: ���̈ʒu�ɃR���g���[���ʒm�n���h���p�̃R�[�h��ǉ����Ă�������
	m_ruleDlg.setAccessMode(TRUE);
	m_ruleDlg.DoModal();
	
}
