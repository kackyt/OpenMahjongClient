#if !defined(AFX_MYBUTTON_H__DEDDE70F_638F_4F43_AF30_069D7CBFED01__INCLUDED_)
#define AFX_MYBUTTON_H__DEDDE70F_638F_4F43_AF30_069D7CBFED01__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MyButton.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMyButton �E�B���h�E

class CMyButton : public CButton
{
// �R���X�g���N�V����
public:
	CMyButton();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMyButton)
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	CFont m_pushedFont;
	CBrush m_pushedBrush;
	CFont m_defFont;
	virtual ~CMyButton();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CMyButton)
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MYBUTTON_H__DEDDE70F_638F_4F43_AF30_069D7CBFED01__INCLUDED_)
