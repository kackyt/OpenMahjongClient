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
// Result.cpp: CResult �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Result.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

OMResult::OMResult()
{
	m_bActive = FALSE;
}

OMResult::~OMResult()
{

}

void OMResult::parseXML(OMDomNode pElem)
{
        OMDomNode pNode;
        OMDomNodeList pNodeList;
        OMString text;
        OMString pStr;
	int i;

	m_bActive = TRUE;

	/* �X�J���[�f�[�^�̊i�[ */

        pNode = OMGetElement(pElem,_T(TAG_DORAKAZU));

        OMToNum(pNode,m_iDorakazu);

        pNode = OMGetElement(pElem,_T(TAG_HAN));

        OMToNum(pNode,m_iHan);

        pNode = OMGetElement(pElem,_T(TAG_FU));

        OMToNum(pNode,m_iFu);

        pNode = OMGetElement(pElem,_T(TAG_MACHI));

        OMToNum(pNode,m_iMachi);

        pNode = OMGetElement(pElem,_T(TAG_MANGAN));

        OMToNum(pNode,m_iMangan);

        pNode = OMGetElement(pElem,_T(TAG_SCORE));

        OMToNum(pNode,m_iScore);

        pNode = OMGetElement(pElem,_T(TAG_OYASCORE));

        OMToNum(pNode,m_iOyaScore);

        pNode = OMGetElement(pElem,_T(TAG_KOSCORE));

        OMToNum(pNode,m_iKoScore);

        pNode = OMGetElement(pElem,_T(TAG_TSUMO));

        OMToBool(pNode,m_bTsumo);

        pNode = OMGetElement(pElem,_T(TAG_MACHIHAI "/" TAG_PAI));

        if(!OMIsNull(pNode)){
		m_machihai.parseXML(pNode);
	}

	/* �𖼃��X�g���i�[ */
        m_aYaku.clear();
        pNodeList = OMGetElementList(pElem,_T(TAG_YAKU));

        if(!OMIsEmpty(pNodeList)){
            for(i=0;i<OMListLength(pNodeList);i++){
                pNode = OMListItem(pNodeList,i);
                OMGetText(pNode,pStr);
                text = OMString(pStr);
                m_aYaku.append(text);
            }
	}


}

#ifdef _MSC_VER
OMResult& OMResult::operator=(OMResult& value)
#else
OMResult& OMResult::operator=(const OMResult& value)
#endif
{
	m_iDorakazu = value.m_iDorakazu;
	m_iFu = value.m_iFu;
	m_bActive = value.m_bActive;
	m_iHan = value.m_iHan;
	m_iMachi = value.m_iMachi;
	m_iMangan = value.m_iMangan;
	m_iScore = value.m_iScore;
	m_iOyaScore = value.m_iOyaScore;
	m_iKoScore = value.m_iKoScore;
	m_bTsumo = value.m_bTsumo;
	m_machihai = value.m_machihai;
        m_aYaku.copy(((OMResult&)value).m_aYaku);

	return *this;
}