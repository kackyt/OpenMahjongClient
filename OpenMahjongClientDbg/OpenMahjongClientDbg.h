// OpenMahjongClientDbg.h : OPENMAHJONGCLIENTDBG �A�v���P�[�V�����̃��C�� �w�b�_�[ �t�@�C���ł��B
//

#if !defined(AFX_OPENMAHJONGCLIENTDBG_H__4881DFF9_D3CA_4AE8_902E_6E3A58653CBA__INCLUDED_)
#define AFX_OPENMAHJONGCLIENTDBG_H__4881DFF9_D3CA_4AE8_902E_6E3A58653CBA__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#ifndef __AFXWIN_H__
	#error include 'stdafx.h' before including this file for PCH
#endif

#include "resource.h"		// ���C�� �V���{��

/////////////////////////////////////////////////////////////////////////////
// COpenMahjongClientDbgApp:
// ���̃N���X�̓���̒�`�Ɋւ��Ă� OpenMahjongClientDbg.cpp �t�@�C�����Q�Ƃ��Ă��������B
//

class COpenMahjongClientDbgApp : public CWinApp
{
public:
	COpenMahjongClientDbgApp();

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(COpenMahjongClientDbgApp)
	public:
	virtual BOOL InitInstance();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����

	//{{AFX_MSG(COpenMahjongClientDbgApp)
		// ���� - ClassWizard �͂��̈ʒu�Ƀ����o�֐���ǉ��܂��͍폜���܂��B
		//        ���̈ʒu�ɐ��������R�[�h��ҏW���Ȃ��ł��������B
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
};


/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_OPENMAHJONGCLIENTDBG_H__4881DFF9_D3CA_4AE8_902E_6E3A58653CBA__INCLUDED_)
