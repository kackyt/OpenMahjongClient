#if !defined(AFX_RULEDIALOG_H__6DB009DA_AF31_42B9_8AE7_73FE09EABFFC__INCLUDED_)
#define AFX_RULEDIALOG_H__6DB009DA_AF31_42B9_8AE7_73FE09EABFFC__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// RuleDialog.h : �w�b�_�[ �t�@�C��
//
#include "Rule.h"

/////////////////////////////////////////////////////////////////////////////
// CRuleDialog �_�C�A���O

class CRuleDialog : public CDialog
{
// �R���X�g���N�V����
public:
	BOOL m_bWritable;
	CRule m_rule;
	void getRule(CRule&);
	void setRule(CRule&);
	void setAccessMode(BOOL);
	CRuleDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CRuleDialog)
	enum { IDD = IDD_RULE };
	CComboBox	m_cmbHaipai;
	CComboBox	m_cmbAotenjo;
	CComboBox	m_cmbAka;
	CComboBox	m_cmbKuitan;
	CComboBox	m_cmbGlasshai;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CRuleDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CRuleDialog)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_RULEDIALOG_H__6DB009DA_AF31_42B9_8AE7_73FE09EABFFC__INCLUDED_)
