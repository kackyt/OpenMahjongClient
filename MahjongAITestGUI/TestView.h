#if !defined(AFX_TESTVIEW_H__2456EE92_D85A_4389_ADF3_AEF43090EC2C__INCLUDED_)
#define AFX_TESTVIEW_H__2456EE92_D85A_4389_ADF3_AEF43090EC2C__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// TestView.h : �w�b�_�[ �t�@�C��
//
#include "Komae.h"

/////////////////////////////////////////////////////////////////////////////
// CTestView �E�B���h�E

class CTestView : public CButton
{
// �R���X�g���N�V����
public:
	CTestView();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CTestView)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	virtual ~CTestView();
	CKomae m_haigaList;
	int m_aTehai[13];
	int m_iTehaiSize;
	int m_iTsumohai;
	int m_aSutehai[18];
	int m_iSutehaiSize;
	int m_iDora;
	void reset();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CTestView)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_TESTVIEW_H__2456EE92_D85A_4389_ADF3_AEF43090EC2C__INCLUDED_)
