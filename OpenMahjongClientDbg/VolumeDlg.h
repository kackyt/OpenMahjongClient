#if !defined(AFX_VOLUMEDLG_H__7C3DED2D_25D1_4DFD_AF6D_FA2558AF7409__INCLUDED_)
#define AFX_VOLUMEDLG_H__7C3DED2D_25D1_4DFD_AF6D_FA2558AF7409__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// VolumeDlg.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CVolumeDlg �_�C�A���O

class CVolumeDlg : public CDialog
{
// �R���X�g���N�V����
public:
	CVolumeDlg(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CVolumeDlg)
	enum { IDD = IDD_VOLUME };
	CSliderCtrl	m_volSE2;
	CSliderCtrl	m_volSE1;
	CSliderCtrl	m_volBGM;
	int		m_iVolBGM;
	int		m_iVolSE1;
	CString	m_strVolBGM;
	CString	m_strVolSE1;
	CString	m_strVolSE2;
	int		m_iVolSE2;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CVolumeDlg)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CVolumeDlg)
	afx_msg void OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar);
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_VOLUMEDLG_H__7C3DED2D_25D1_4DFD_AF6D_FA2558AF7409__INCLUDED_)
