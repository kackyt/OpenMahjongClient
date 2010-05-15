#if !defined(AFX_CONNECTDLG_H__CF340994_31A2_45F7_9DFF_4A4F8CEE4ECA__INCLUDED_)
#define AFX_CONNECTDLG_H__CF340994_31A2_45F7_9DFF_4A4F8CEE4ECA__INCLUDED_

#include "RuleDialog.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// ConnectDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CConnectDlg �_�C�A���O

class CConnectDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CRuleDialog m_ruleDlg;
	CString m_strComp3;
	CString m_strComp2;
	CString m_strComp1;
	LPVOID m_pTopObj;
	CConnectDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CConnectDlg)
	enum { IDD = IDD_CONNECT };
	CComboBox	m_cmbComp3;
	CComboBox	m_cmbComp2;
	CComboBox	m_cmbComp1;
	CString	m_playerName;
	int		m_iSession;
	CString	m_strDst;
	int		m_iNewSess;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CConnectDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CConnectDlg)
	virtual BOOL OnInitDialog();
	virtual void OnOK();
	afx_msg void OnBtnrule();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_CONNECTDLG_H__CF340994_31A2_45F7_9DFF_4A4F8CEE4ECA__INCLUDED_)
