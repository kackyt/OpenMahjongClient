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
#include <math.h>
#include "MahjongScoreAI.h"
#include "AILib.h"

// ��v�𕔕��I�ɕ]������
static double eval_Tehai_sub(MahjongAIState &param,int sthai,int atama_flag)
{
	int p=0,sc_max=0,sc,kazu,chk;
	char c;
	UINT tmp;

	for(p=0;p<34;p++) if (param.te_cnt[p]) break;
	if (p==34) return 0;
	c = param.te_cnt[p];

	// ���q�̕]��
	if (c>=3) {
		param.te_cnt[p]-=3;
		sc_max = eval_Tehai_sub(param,sthai,atama_flag)+18;
		param.te_cnt[p]+=3;
	}

	// �Ύq�̕]��
	if (c>=2) {
		param.te_cnt[p]-=2;
		tmp = MahjongScoreAI::MJSendMessage(MJMI_GETVISIBLEHAIS,p,0);
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("GETVISIBLEHAIS %u\n"),tmp);
#endif
		sc = eval_Tehai_sub(param,sthai,1)+6*(!param.anpai[p][0] || !atama_flag)+!atama_flag*12-tmp;
		if (sc>sc_max) sc_max = sc;
		param.te_cnt[p]+=2;
	}

	// ���v�̕]��
	if (p<27){
		kazu = p%9;
		if (kazu<7){
			if (param.te_cnt[p+2]){
				param.te_cnt[p]--; param.te_cnt[p+2]--;

				// �J���`�����̕]��
				if (!param.anpai[p+1][0] && sthai!=p+1){
					tmp = MahjongScoreAI::MJSendMessage(MJMI_GETVISIBLEHAIS,p+1,0);
#ifdef AIDUMP_COMMAND
					fprintf(fp,TEXT("GETVISIBLEHAIS %u\n"),tmp);
#endif
					sc = eval_Tehai_sub(param,sthai,atama_flag)+8-tmp;
					if (sc>sc_max) sc_max = sc;
					if (kazu<5) if (param.te_cnt[p+4]) if (!param.anpai[p+3][0] && sthai!=p+3){
						param.te_cnt[p+4]--;
						sc = eval_Tehai_sub(param,sthai,atama_flag)+12;
						if (sc>sc_max) sc_max = sc;
						param.te_cnt[p+4]++;
					}
				}

				// ���q�̕]��
				if (param.te_cnt[p+1]){
					param.te_cnt[p+1]--;
					sc = eval_Tehai_sub(param,sthai,atama_flag)+18;
					if (sc>sc_max) sc_max = sc;
					param.te_cnt[p+1]++;
				}
				param.te_cnt[p]++; param.te_cnt[p+2]++;
			}
		}

		// ���ʑ҂��A�y���`�����̕]��
		if (kazu<8){
			if (param.te_cnt[p+1]){
				chk = 0;
				if (kazu>0) if (param.anpai[p-1][0] || sthai==p-1) chk = 1;
				if (kazu<7) if (param.anpai[p+2][0] || sthai==p+2) chk = 1;
				if (!chk){
					param.te_cnt[p]--; param.te_cnt[p+1]--;
					sc = eval_Tehai_sub(param,sthai,atama_flag)+8+(kazu>0 && kazu<7)*4;
					if (sc>sc_max) sc_max = sc;
					param.te_cnt[p]++; param.te_cnt[p+1]++;
				}
			}
		}
	}

	// �v����������Ԃł̕]���_���o���Ă݂�
	param.te_cnt[p]--;
	sc = eval_Tehai_sub(param,sthai,atama_flag);
	if (sc>sc_max) sc_max = sc;
	param.te_cnt[p]++;
	return sc_max;
}

// �v��]�����ĕ]���l��Ԃ�
static double eval_hai(MahjongAIState &param,int hai,UINT *dora,int doras)
{
	double ret = 1.0;
	int j;
	double tmp;

	if (hai<27){
		if((hai % 9) == 0 || (hai % 9) == 8){
			ret += SCORE_SUPAI_19;
		}else if((hai % 9) == 1 || (hai % 9) == 7){
			ret += SCORE_SUPAI_28;
		}else{
			ret += SCORE_SUPAI_34567;
		}
	}else {
		tmp = param.nokori[hai];
	
		if (hai>30 || hai==param.cha+27 || hai==param.kaze+27){
			if(param.te_cnt[hai] >= 3){
				ret += SCORE_HANPAI_TRIPLE_BIAS;
			}
			if (tmp>1.0 && param.te_cnt[hai] == 2)
				ret+= SCORE_HANPAI_DOUBLE_BIAS;
			if (tmp>2.0 && param.te_cnt[hai] == 1)
				ret+= SCORE_HANPAI_BIAS;
		}
	}


	for(j=0;j<doras;j++)
		if (hai==(int)dora[j]) ret+=SCORE_DORA_BIAS;
	return ret;
}

// ��v��]�����ĕ]���l��Ԃ�
double MahjongAIType3::evalSutehaiSub(MahjongAIState &param,int hai)
{
	int i,j;
	double ret1,ret2;
	int shanten;
	TENPAI_LIST list;
	int doras;
	UINT dora[6];
	ret1 = 0.0;

	doras = MJSendMessage(MJMI_GETDORA,(UINT)dora,0);

	/* �V�����e�����𐔂��� */
	for(i=0;i<34;i++){
		if (param.te_cnt[i]){
			ret1 += eval_hai(param,i,dora,doras);
		}
	}
	shanten = search_tenpai((int*)param.tehai.tehai,param.tehai.tehai_max,NULL,&list,1,6);

	ret2 = eval_Tehai_sub(param,hai,0);

	return (ret1 + ret2) * pow(0.8,shanten);
}
