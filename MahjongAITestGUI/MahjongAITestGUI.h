// MahjongAITestGUI.h : MAHJONAITESTGUI �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_MAHJONAITESTGUI_H__7C4A5ADA_4FC3_47E0_A25C_7366AC9C59D4__INCLUDED_)
#define AFX_MAHJONAITESTGUI_H__7C4A5ADA_4FC3_47E0_A25C_7366AC9C59D4__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// CMahjongAITestGUIApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� MahjongAITestGUI.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class CMahjongAITestGUIApp : public CWinApp
{
public:
	CMahjongAITestGUIApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMahjongAITestGUIApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(CMahjongAITestGUIApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MAHJONAITESTGUI_H__7C4A5ADA_4FC3_47E0_A25C_7366AC9C59D4__INCLUDED_)
