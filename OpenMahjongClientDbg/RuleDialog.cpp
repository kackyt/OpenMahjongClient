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
	DDX_Control(pDX, IDC_CMBHAIPAI, m_cmbHaipai);
	DDX_Control(pDX, IDC_CMBAOTENJO, m_cmbAotenjo);
	DDX_Control(pDX, IDC_CMBAKADORA, m_cmbAka);
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
		m_cmbAka.EnableWindow(TRUE);
		m_cmbAotenjo.EnableWindow(TRUE);
		m_cmbHaipai.EnableWindow(TRUE);
	}else{
		m_cmbGlasshai.EnableWindow(FALSE);
		m_cmbKuitan.EnableWindow(FALSE);
		m_cmbAka.EnableWindow(FALSE);
		m_cmbAotenjo.EnableWindow(FALSE);
		m_cmbHaipai.EnableWindow(FALSE);
	}

	m_cmbGlasshai.SetCurSel(m_rule.m_iGlasshai);
	m_cmbKuitan.SetCurSel(m_rule.m_iKuitan);
	m_cmbAka.SetCurSel(m_rule.m_iAka);
	m_cmbAotenjo.SetCurSel(m_rule.m_iAotenjo);
	m_cmbHaipai.SetCurSel(m_rule.m_iHaipai);
	
	return TRUE;  // �R���g���[���Ƀt�H�[�J�X��ݒ肵�Ȃ��Ƃ��A�߂�l�� TRUE �ƂȂ�܂�
	              // ��O: OCX �v���p�e�B �y�[�W�̖߂�l�� FALSE �ƂȂ�܂�
}

void CRuleDialog::OnOK() 
{
	UpdateData(TRUE);

	m_rule.m_bActive = TRUE;
	m_rule.m_iGlasshai = m_cmbGlasshai.GetCurSel();
	m_rule.m_iKuitan = m_cmbKuitan.GetCurSel();
	m_rule.m_iAka = m_cmbAka.GetCurSel();
	m_rule.m_iAotenjo = m_cmbAotenjo.GetCurSel();
	m_rule.m_iHaipai = m_cmbHaipai.GetCurSel();
	
	CDialog::OnOK();
}
