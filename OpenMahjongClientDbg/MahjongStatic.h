#if !defined(AFX_MAHJONGSTATIC_H__A8FD3147_9799_4CC5_AD2C_F0DFA9D62659__INCLUDED_)
#define AFX_MAHJONGSTATIC_H__A8FD3147_9799_4CC5_AD2C_F0DFA9D62659__INCLUDED_


#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MahjongStatic.h : �w�b�_�[ �t�@�C��
//
#include "Result.h"	// ClassView �ɂ���Ēǉ�����܂����B

/////////////////////////////////////////////////////////////////////////////
// CMahjongStatic �E�B���h�E

class CMahjongStatic : public CStatic
{
// �R���X�g���N�V����
public:
	CMahjongStatic();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMahjongStatic)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	int m_iType;
	CResult m_result;
	virtual ~CMahjongStatic();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CMahjongStatic)
	afx_msg void OnPaint();
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MAHJONGSTATIC_H__A8FD3147_9799_4CC5_AD2C_F0DFA9D62659__INCLUDED_)
