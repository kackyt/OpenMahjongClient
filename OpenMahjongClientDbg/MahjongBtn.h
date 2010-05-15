#if !defined(AFX_MAHJONGBTN_H__969D422C_1E03_42F0_A91A_DC0023FC8094__INCLUDED_)
#define AFX_MAHJONGBTN_H__969D422C_1E03_42F0_A91A_DC0023FC8094__INCLUDED_

#include "Taku.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "Komae.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "Rule.h"	// ClassView �ɂ���Ēǉ�����܂����B
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
// MahjongBtn.h : �w�b�_�[ �t�@�C��
//

/////////////////////////////////////////////////////////////////////////////
// CMahjongBtn �E�B���h�E

class CMahjongBtn : public CButton
{
// �R���X�g���N�V����
public:
	CMahjongBtn();

// �A�g���r���[�g
public:

// �I�y���[�V����
public:

// �I�[�o�[���C�h
	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(CMahjongBtn)
	public:
	virtual void DrawItem(LPDRAWITEMSTRUCT lpDrawItemStruct);
	protected:
	virtual void PreSubclassWindow();
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
public:
	CRule m_rule;
	CKomae m_haigaListYoko180;
	CKomae m_haigaList180;
	CKomae m_haigaListYoko;
	int getSelMode();
	void setSelMode(int);
	int m_selIndex[2];
	BOOL m_bActive;
	CKomae m_haigaList;
	void refresh(int,CTaku&);
	virtual ~CMahjongBtn();

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
protected:
	//{{AFX_MSG(CMahjongBtn)
	afx_msg void OnPaint();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnRButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	//}}AFX_MSG

	DECLARE_MESSAGE_MAP()
private:
	void paintPai(CPaintDC &dc,CRect &rect,CString &str,CMember *member,int count);
	int m_iPlayerIndex;
	CTaku m_taku;
	int m_iSelMode;
};

/////////////////////////////////////////////////////////////////////////////

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_MAHJONGBTN_H__969D422C_1E03_42F0_A91A_DC0023FC8094__INCLUDED_)
