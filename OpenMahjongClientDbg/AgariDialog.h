#if !defined(AFX_AGARIDIALOG_H__A3811369_9311_40D3_B697_BD9D3AA454F9__INCLUDED_)
#define AFX_AGARIDIALOG_H__A3811369_9311_40D3_B697_BD9D3AA454F9__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// AgariDialog.h : �w�b�_�[ �t�@�C��
//

#include "MahjongStatic.h"

/////////////////////////////////////////////////////////////////////////////
// CAgariDialog �_�C�A���O

class CAgariDialog : public CDialog
{
// �R���X�g���N�V����
public:
	CAgariDialog(CWnd* pParent = NULL);   // �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(CAgariDialog)
	enum { IDD = IDD_AGARI };
	CMahjongStatic	m_staAgariyaku;
	//}}AFX_DATA


// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CAgariDialog)
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(CAgariDialog)
		// ����: ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ����܂��B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_AGARIDIALOG_H__A3811369_9311_40D3_B697_BD9D3AA454F9__INCLUDED_)
