// RuleDialog.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "RuleDialog.h"
#include "Rule.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CRuleDialog �_�C�A���O


CRuleDialog::CRuleDialog(CWnd* pParent /*=NULL*/)
	: CDialog(CRuleDialog::IDD, pParent)
{
	//{{AFX_DATA_INIT(CRuleDialog)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ}�b�s���O�p�̃}�N����ǉ��܂��͍폜���܂��B
	//}}AFX_DATA_INIT
}


void CRuleDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CRuleDialog)
	DDX_Control(pDX, IDC_CMBKUITAN, m_cmbKuitan);
	DDX_Control(pDX, IDC_CMBGLASSHAI, m_cmbGlasshai);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CRuleDialog, CDialog)
	//{{AFX_MSG_MAP(CRuleDialog)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CRuleDialog ���b�Z�[�W �n���h��

void CRuleDialog::setAccessMode(BOOL isWritable)
{
	m_bWritable = isWritable;

}

void CRuleDialog::setRule(CRule& rule)
{
	m_rule = rule;
	m_rule.m_bActive = TRUE;
}

void CRuleDialog::getRule(CRule& rule)
{
	rule = m_rule;
	rule.m_bActive = TRUE;
}

BOOL CRuleDialog::OnInitDialog() 
{
	CDialog::OnInitDialog();

	if(m_bWritable){
		m_cmbGlasshai.EnableWindow(TRUE);
		m_cmbKuitan.EnableWindow(TRUE);
	}else{
		m_cmbGlasshai.EnableWindow(FALSE);
		m_cmbKuitan.EnableWindow(FALSE);
	}

	if(m_rule.m_bActive){
		m_cmbGlasshai.SetCurSel(m_rule.m_iGlasshai);
		m_cmbKuitan.SetCurSel(m_rule.m_iKuitan);
	}else{
		m_cmbGlasshai.SetCurSel(0);
		m_cmbKuitan.SetCurSel(0);
	}
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CRuleDialog::OnOK() 
{
	UpdateData(TRUE);

	m_rule.m_bActive = TRUE;
	m_rule.m_iGlasshai = m_cmbGlasshai.GetCurSel();
	m_rule.m_iKuitan = m_cmbKuitan.GetCurSel();
	
	CDialog::OnOK();
}
