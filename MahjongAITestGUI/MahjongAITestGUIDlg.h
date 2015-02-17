// MahjongAITestGUIDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_MAHJONAITESTGUIDLG_H__E7DE8816_5E35_4B81_BA91_A75705A66AD5__INCLUDED_)
#define AFX_MAHJONAITESTGUIDLG_H__E7DE8816_5E35_4B81_BA91_A75705A66AD5__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "MessageEdit.h"
#include "TestView.h"
#include "MIPIface.h"
#include "afxwin.h"

typedef enum {
	MJCOM_PREV,
		MJCOM_NEXT,
		MJCOM_AUTO,
		MJCOM_NONE,
} MJCOMMAND;
typedef enum {
	MJSTATE_INIT,
		MJSTATE_KYOKU,
		MJSTATE_AGARI,
} MJSTATE;
/////////////////////////////////////////////////////////////////////////////
// CMahjongAITestGUIDlg �_�C�A���O

class CMahjongAITestGUIDlg : public CDialog
{
// �\�z
public:
	CMahjongAITestGUIDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^
	int m_iWait;
	MJCOMMAND m_command;
	MJSTATE m_state;
	void nextPai();
	void prevPai();
	void newKyoku(bool reset = true);
	void aiInit();

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CMahjongAITestGUIDlg)
	enum { IDD = IDD_MAHJONAITESTGUI_DIALOG };
	CButton	m_btnNext;
	CButton	m_btnPrev;
	CTestView	m_view;
	CString	m_strKyoku;
	CString	m_strWait;
	CString	m_strHoura2;
	CString	m_strHoura;
	CString	m_strTenpai;
	CString	m_strHouraR;
	CString	m_strHouraR2;
	CString	m_strTenpaiR;
	CString	m_strSeek;
	CString	m_strDebug;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMahjongAITestGUIDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;
	char m_aPai[136];
	int m_iIndex;
	MJPIFunc m_func;
	void * m_inst;
	int m_iKyoku;
	int m_iTenpai;
	int m_iHoura;
	int m_iHoura2;
	LRESULT OnRefresh(WPARAM,LPARAM);
	HMODULE m_comp;
	CString m_strDumpFile;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CMahjongAITestGUIDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnnext();
	afx_msg void OnBtnprev();
	afx_msg void OnBtnauto();
	afx_msg void OnDestroy();
	afx_msg void OnTimer(UINT nIDEvent);
	afx_msg void OnBtnwait();
	afx_msg void OnAi();
	afx_msg void OnBtnseek();
	afx_msg void OnBtnrddump();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
public:
	CMessageEdit m_ctrlMessage;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MAHJONAITESTGUIDLG_H__E7DE8816_5E35_4B81_BA91_A75705A66AD5__INCLUDED_)
