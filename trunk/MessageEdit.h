#if !defined(AFX_MESSAGEEDIT_H__847A5FF7_3EAD_4B57_9492_B10A11E14633__INCLUDED_)
#define AFX_MESSAGEEDIT_H__847A5FF7_3EAD_4B57_9492_B10A11E14633__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MessageEdit.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMessageEdit �E�B���h�E

class CMessageEdit : public CEdit
{
// �R���X�g���N�V����
public:
	CMessageEdit();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMessageEdit)
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	int m_iLineLimit;
	BOOL appendMessage(CString&);
	virtual ~CMessageEdit();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CMessageEdit)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MESSAGEEDIT_H__847A5FF7_3EAD_4B57_9492_B10A11E14633__INCLUDED_)
