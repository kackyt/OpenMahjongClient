/****************************************************************************************
 * Copyright (c) 2010-2012, Takaya Kakizaki(kacky)
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
#include "MahjongScoreAI.h"
UINT (WINAPI *MahjongScoreAI::pMJSendMessage)(void*,UINT,UINT,UINT);
void *MahjongScoreAI::pObj;


double MahjongAIKikenhai::evalSutehaiSub(MahjongAIState &param,int hai)
{
	int i;
	double ret = 0;
	double minus = 0;
	double plus = 0,tmp;

	minus += SCORE_KIKENHAI * param.myself._kikenhai[hai];
	for(i=0;i<3;i++){
		tmp = 0.0;
		if (param.players[i]._anpai[hai]){
		}else if (hai<27){
			int kazu = hai%9,fl=1;
			if (kazu>2) if (!param.players[i]._anpai[hai-3]) fl = 0;
			if (fl) if (kazu<6) if (!param.players[i]._anpai[hai+3]) fl = 0;
			if (fl){
				if(kazu == 0 || kazu == 8){
					tmp -= SCORE_SUZI19;
				}else if(kazu == 1 || kazu == 7){
					tmp -= SCORE_SUZI28;
				}else{
					tmp -= SCORE_SUZI37;
				}
			}else{
				if(kazu == 0 || kazu == 8){
					tmp -= SCORE_19;
				}else if(kazu == 1 || kazu == 7){
					tmp -= SCORE_28;
				}else if(kazu == 1 || kazu == 7){
					tmp -= SCORE_37;
				}else{
					tmp -= SCORE_456;
				}
			}
			tmp -= SCORE_ANPAI;
		}else{
			tmp -= SCORE_ZIHAI + SCORE_ANPAI;
		}
		if(param.players[i]._is_ippatsu){
			tmp *= SCORE_IPPATSU_BIAS;
			minus *= SCORE_IPPATSU_BIAS;
		}else if (param.players[i]._is_riichi){
			tmp *= SCORE_RIICHI_BIAS;
			minus *= SCORE_RIICHI_BIAS;
		}

		plus += tmp;
	}

	return plus - minus;
}