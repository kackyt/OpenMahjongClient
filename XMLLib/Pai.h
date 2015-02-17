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
// Pai.h: CPai �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PAI_H__16AB8A35_5601_46CB_89F4_1F11DA494FA4__INCLUDED_)
#define AFX_PAI_H__16AB8A35_5601_46CB_89F4_1F11DA494FA4__INCLUDED_

#include "OMXMLCommon.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define PAI_NIL     (34)
#define PAI_NOTINIT (63)
#include "Rule.h"

class OMPai
{
public:
        int operator >=(OMPai&);
        bool operator ==(OMPai &);
	BOOL m_bLast;
        BOOL isAka(OMRule&);
	BOOL m_bNaki;
        BOOL match(OMPai&);
        void set(UINT id);
	BOOL m_bRiichi;
        void getDora(OMPai&);
        void getName(OMString&);
	operator UINT();
        void parseXML(OMDomNode);
	BOOL m_bTsumogiri;
	int m_iId;
	int m_iNo;
	int m_iCategory;
    void toPaiString(OMString &str,OMRule &rule);
    OMPai();
        virtual ~OMPai();

};

#endif // !defined(AFX_PAI_H__16AB8A35_5601_46CB_89F4_1F11DA494FA4__INCLUDED_)
