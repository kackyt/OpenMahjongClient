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
// Library.cpp: CLibrary �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "OpenMahjongClientDbg.h"
#include "Library.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

CLibrary::CLibrary()
{

}

CLibrary::~CLibrary()
{

}

void CLibrary::setMember(int id,CMember& member,MJITehai* pTehai,int agarihai)
{
	UINT i,j;
	m_iId = id;
	m_player = member.m_player;
	m_gamestate = member.m_gamestate;
	m_gamestate.m_aNakiList.RemoveAll();

	if(pTehai != NULL){
		for(i=0;i<pTehai->tehai_max;i++){
			CPai pai;
			pai.set(pTehai->tehai[i]);
			m_aTehai.Add(pai);
		}

		for(i=0;i<pTehai->minshun_max;i++){
			CNakiMentsu nakimentsu;
			nakimentsu.m_iAite = 3;
			nakimentsu.m_iCategory = MENTSU_SYUNTSU;
			for(j=0;j<3;j++){
				CPai pai;
				pai.set(pTehai->minshun[i] + j);
				nakimentsu.m_aPaiList.Add(pai);
			}

			m_gamestate.m_aNakiList.Add(nakimentsu);
		}

		for(i=0;i<pTehai->minkou_max;i++){
			CNakiMentsu nakimentsu;
			nakimentsu.m_iAite = 3;
			nakimentsu.m_iCategory = MENTSU_KOUTSU;
			for(j=0;j<3;j++){
				CPai pai;
				pai.set(pTehai->minkou[i]);
				nakimentsu.m_aPaiList.Add(pai);
			}
			m_gamestate.m_aNakiList.Add(nakimentsu);
		}

		for(i=0;i<pTehai->minkan_max;i++){
			CNakiMentsu nakimentsu;
			nakimentsu.m_iAite = 3;
			nakimentsu.m_iCategory = MENTSU_MINKAN;
			for(j=0;j<4;j++){
				CPai pai;
				pai.set(pTehai->minkan[i]);
				nakimentsu.m_aPaiList.Add(pai);
			}
			m_gamestate.m_aNakiList.Add(nakimentsu);
		}

		for(i=0;i<pTehai->ankan_max;i++){
			CNakiMentsu nakimentsu;
			nakimentsu.m_iAite = 3;
			nakimentsu.m_iCategory = MENTSU_ANKAN;
			for(j=0;j<4;j++){
				CPai pai;
				pai.set(pTehai->ankan[i]);
				nakimentsu.m_aPaiList.Add(pai);
			}
			m_gamestate.m_aNakiList.Add(nakimentsu);
		}
	}

	if(agarihai >= 0){
		m_agarihai.set((UINT)agarihai);
	}

}

