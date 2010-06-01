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
