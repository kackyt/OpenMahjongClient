// MahjongStatic.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "MahjongStatic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

/////////////////////////////////////////////////////////////////////////////
// CMahjongStatic

CMahjongStatic::CMahjongStatic()
{
	m_iType = TYPE_KOUHAI;
}

CMahjongStatic::~CMahjongStatic()
{
}


BEGIN_MESSAGE_MAP(CMahjongStatic, CStatic)
	//{{AFX_MSG_MAP(CMahjongStatic)
	ON_WM_PAINT()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CMahjongStatic ���b�Z�[�W �n���h��

void CMahjongStatic::OnPaint() 
{
	CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g
	CFont agariFont,*pOldFont;
	int i;
	CString str;
	dc.SetBkMode(TRANSPARENT);
	agariFont.CreateFont(20,0,0,0,FW_BOLD,TRUE,FALSE,FALSE,
		SHIFTJIS_CHARSET,OUT_DEFAULT_PRECIS,CLIP_DEFAULT_PRECIS,DRAFT_QUALITY,DEFAULT_PITCH,_T("�l�r �S�V�b�N"));

	switch(m_iType){
	case TYPE_START:

		pOldFont = dc.SelectObject(&agariFont);				

		for(i=0;i<m_result.m_aYaku.GetSize();i++){
			dc.TextOut(0,20 + 25 * i,m_result.m_aYaku[i]);
		}

		str.Format(_T("%d�| %d�� %d�_"),m_result.m_iHan,m_result.m_iFu,m_result.m_iScore);
		dc.TextOut(0,270,str);

		dc.SelectObject(pOldFont);
		break;
	case TYPE_KOUHAI:
		pOldFont = dc.SelectObject(&agariFont);

		dc.TextOut(100,150,_T("�r�v����"));

		dc.SelectObject(pOldFont);
		break;
	}
	
	// �`��p���b�Z�[�W�Ƃ��� CStatic::OnPaint() ���Ăяo���Ă͂����܂���
}
