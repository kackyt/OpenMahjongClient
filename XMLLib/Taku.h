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
// Taku.h: CTaku �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_TAKU_H__D62DB02C_B097_4C6E_AFB0_BD812D314DA0__INCLUDED_)
#define AFX_TAKU_H__D62DB02C_B097_4C6E_AFB0_BD812D314DA0__INCLUDED_

#include "OMXMLCommon.h"
#include "Pai.h"
#include "Member.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "TakuEvent.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "MIPIface.h"
#include "Rule.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class OMTaku
{
public:
	int getKawahaiEx(int,MJIKawahai*);
        void getMJITehai(int,MJITehai1 *,OMRule&);
        void update(OMTaku&);
        OMTaku& operator=(OMTaku&);
        void printState(int,QString&);
	int getVisibleHais(UINT,int);
	int getKawahai(int,UINT*);
	void getMJITehai(int,MJITehai*);
        int getMemberIndex(OMPlayer*);
        OMTakuEvent m_event;
        OMMember m_members[4];
        void parseXML(QDomNode);
	int m_iYama;
	int m_iTsumibou;
	int m_iRiichibou;
	int m_iKyokuCount;
	int m_iBakaze;
        OM_DEFARRAY(OMPai,m_aUradora);
        OM_DEFARRAY(OMPai,m_aDora);
	int m_iTurn;
        OMTaku();
        virtual ~OMTaku();

};

#endif // !defined(AFX_TAKU_H__D62DB02C_B097_4C6E_AFB0_BD812D314DA0__INCLUDED_)
