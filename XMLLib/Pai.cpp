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
// Pai.cpp: CPai �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Pai.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

OMPai::OMPai()
{
	m_iCategory = -1;
	m_iNo = -1;
	m_iId = -1;
	m_bTsumogiri = FALSE;
	m_bRiichi = FALSE;
	m_bNaki = FALSE;
	m_bLast = FALSE;

}

OMPai::~OMPai()
{

}

void OMPai::parseXML(QDomNode pElem)
{
        QDomNode pNode;

        pNode = OM_GETELEMENT(pElem,_T(TAG_CATEGORY));

        OM_TOLONG(pNode,m_iCategory);

        pNode = OM_GETELEMENT(pElem,_T(TAG_NO));

        OM_TOLONG(pNode,m_iNo);

        pNode = OM_GETELEMENT(pElem,_T(TAG_ID));

        OM_TOLONG(pNode,m_iId);

        pNode = OM_GETELEMENT(pElem,_T(TAG_TSUMOGIRI));

        OM_TOBOOL(pNode,m_bTsumogiri);

        pNode = OM_GETELEMENT(pElem,_T(TAG_RIICHI));

        OM_TOBOOL(pNode,m_bRiichi);

}

OMPai::operator UINT()
{
	if(m_iCategory < 0) return PAI_NOTINIT;
	else if(m_iCategory == 0 && m_iNo == 0) return PAI_NIL;
	else return (m_iCategory - 1) * 9 + (m_iNo - 1);
}

void OMPai::getName(QString& text)
{
	const TCHAR *table[] = {_T("��"),_T("��"),_T("�O"),_T("�l"),_T("��"),_T("�Z"),_T("��"),_T("��"),_T("��")};
	const TCHAR *table2[] = {_T("��"),_T("��"),_T("��"),_T("�k"),_T("��"),_T("��"),_T("��")};
	text = _T("");

	switch(m_iCategory){
	case PAI_MANZU:
		text += table[m_iNo - 1];
		text += _T("��");
		break;
	case PAI_SOUZU:
		text += table[m_iNo - 1];
		text += _T("��");
		break;
	case PAI_PINZU:
		text += table[m_iNo - 1];
		text += _T("��");
		break;
	case PAI_ZIHAI:
		text += table2[m_iNo - 1];
		break;
	default:
		break;
	}

	if(m_bTsumogiri){
		text += _T("*");
	}
	if(m_bRiichi){
		text += _T("#");
	}

}

void OMPai::getDora(OMPai& dora)
{
	dora.m_iCategory = m_iCategory;

	if(m_iCategory == PAI_ZIHAI){
		if(m_iNo == 4){
			dora.m_iNo = 1;
		}else if(m_iNo == 7){
			dora.m_iNo = 5;
		}else{
			dora.m_iNo = m_iNo + 1;
		}
	}else{
		if(m_iNo == 9){
			dora.m_iNo = 1;
		}else{
			dora.m_iNo = m_iNo + 1;
		}
	}

}

void OMPai::set(UINT id)
{
	m_iCategory = ((id & 0x3F)/ 9) + 1;
	m_iNo = ((id & 0x3F) % 9) + 1;
}

BOOL OMPai::match(OMPai& pai)
{
	if(m_iCategory == pai.m_iCategory && m_iNo == pai.m_iNo && m_iId == pai.m_iId){
		return TRUE;
	}else{
		return FALSE;
	}
}

BOOL OMPai::isAka(OMRule& rule)
{
	if(rule.m_iAka == 1){
		if(m_iNo == 5 && m_iId == 4 && m_iCategory != PAI_ZIHAI){
			return TRUE;
		}
	}else if(rule.m_iAka == 2){
		if(m_iNo == 5 && m_iId == 4 && m_iCategory != PAI_ZIHAI){
			return TRUE;
		}

		if(m_iCategory == PAI_PINZU && m_iNo == 5 && m_iId == 3){
			return TRUE;
		}
	}

	return FALSE;

}

int OMPai::operator >=(OMPai& pai)
{
	if((UINT)pai == PAI_NIL) return FALSE;
	if((UINT)*this == PAI_NIL) return TRUE;
	if(m_iCategory > pai.m_iCategory){
		return TRUE;
	}else if(m_iCategory == pai.m_iCategory){
		if(m_iNo > pai.m_iNo){
			return TRUE;
		}else if(m_iNo == pai.m_iNo){
			if(m_iId >= pai.m_iId){
				return TRUE;
			}
		}
	}

	return FALSE;
}
