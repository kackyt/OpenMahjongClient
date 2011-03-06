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
	DDX_Control(pDX, IDC_BTNRULE, m_btnRule);
	DDX_Control(pDX, IDC_SESSION, m_editSess);
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
	ON_BN_CLICKED(IDC_DEBUG, OnDebug)
	ON_BN_CLICKED(IDC_RADIONEW, OnRadionew)
	ON_BN_CLICKED(IDC_RADIOAPPEND, OnRadioappend)
	ON_BN_CLICKED(IDC_RESTART, OnRestart)
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

	m_btnRule.EnableWindow(TRUE);
	m_editSess.EnableWindow(FALSE);

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
	m_ruleDlg.setAccessMode(TRUE);
	m_ruleDlg.DoModal();
}

void CConnectDlg::OnDebug() 
{
	m_btnRule.EnableWindow(FALSE);
	m_editSess.EnableWindow(TRUE);	
}

void CConnectDlg::OnRadionew() 
{
	m_btnRule.EnableWindow(TRUE);
	m_editSess.EnableWindow(FALSE);
}

void CConnectDlg::OnRadioappend() 
{
	m_btnRule.EnableWindow(FALSE);
	m_editSess.EnableWindow(TRUE);	
}

void CConnectDlg::OnRestart() 
{
	m_btnRule.EnableWindow(FALSE);
	m_editSess.EnableWindow(FALSE);	
}
