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
#if !defined(AFX_DEBUGDIALOG_H__0BC4D97F_FB57_4DCA_B2D9_BADECBA4CE04__INCLUDED_)
#define AFX_DEBUGDIALOG_H__0BC4D97F_FB57_4DCA_B2D9_BADECBA4CE04__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// DebugDialog.h : �w�b�_�[ �t�@�C��
//
enum {
	WM_SETTIME = (WM_USER + 100),
	WM_SETSTATUSCODE,
};

/////////////////////////////////////////////////////////////////////////////
// CDebugDialog �_�C�A���O

class CDebugDialog : public CDialog
{
// �R���X�g���N�V����
public:
	LRESULT OnSetStatusCode(WPARAM,LPARAM);
	LRESULT OnSetTime(WPARAM,LPARAM);
	void setStatusCode(int);
	void setTime(int);
	CDebugDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CDebugDialog)
	enum { IDD = IDD_DEBUG };
	CString	m_strRescodc1;
	CString	m_strRescodc2;
	CString	m_strRescodc3;
	CString	m_strRescodc4;
	CString	m_strRescodc5;
	CString	m_strRescodc6;
	CString	m_strRescodr1;
	CString	m_strRescodr2;
	CString	m_strRescodr3;
	CString	m_strRescodr4;
	CString	m_strRescodr5;
	CString	m_strRescodr6;
	CString	m_strRestimc1;
	CString	m_strRestimc2;
	CString	m_strRestimc3;
	CString	m_strRestimc4;
	CString	m_strRestimr1;
	CString	m_strRestimr2;
	CString	m_strRestimr3;
	CString	m_strRestimr4;
	CString	m_strCUI;
	CString	m_strRestimc5;
	CString	m_strRestimc6;
	CString	m_strRestimr5;
	CString	m_strRestimr6;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CDebugDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CDebugDialog)
	virtual BOOL OnInitDialog();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	int m_aTimCount[6];
	int m_iTimTotal;
	int m_aCodCount[6];
	int m_iCodTotal;
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_DEBUGDIALOG_H__0BC4D97F_FB57_4DCA_B2D9_BADECBA4CE04__INCLUDED_)
