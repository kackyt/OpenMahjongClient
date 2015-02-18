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

/* �v�������̊��Ғl�̕␳�W�� */
static double dist_coef[] = {
    0.1,
    1.0,
    0.8,
    0.6,
    0.2,
    0.4,
    0.3,
    0.3,
    0.3,
    0.3
};


#if 0
static int getPoint(AGARI_LIST *pList,void *ptr)
{
	return 0;
}
#else
static int getPoint(AGARI_LIST *pList,void *ptr)
{
	MJITehai resulthai;
	int val,i,j;
	int isChiitoi = 1;
	MahjongAIState *obj=(MahjongAIState*)ptr;
	double coef = 1.0;
	int remain = MahjongScoreAI::MJSendMessage(MJMI_GETHAIREMAIN,0,0)/4;

	memcpy(&resulthai,&obj->tehai,sizeof(resulthai));
	
	for(i=0;i<pList->tehai_max;i++){
		//if(remain < pList->tehai[i] >> 8) return 0;
        if (pList->tehai[i] >> 8){
            int dist = paidistance(obj->tehai.tehai, pList->tehai[i]);
            coef *= dist_coef[dist + 1];
        }
		//for(j=0;j<(pList->tehai[i] >> 8);j++) coef *= 0.95635;
		pList->tehai[i] = pList->tehai[i] & 0xFF;
	}
	memcpy(&resulthai.tehai,pList->tehai,sizeof(int)*pList->tehai_max);
	resulthai.tehai_max = pList->tehai_max-1;
	//qsort(&resulthai.tehai,pList->tehai_max,sizeof(int),(int (*)(const void*, const void*))compare_int);
	val = MahjongScoreAI::MJSendMessage(MJMI_GETAGARITEN,(UINT)&resulthai,(UINT)resulthai.tehai[pList->tehai_max-1]);

    return val * coef;

}

#endif

// ��v��]�����ĕ]���l��Ԃ�
double MahjongAIType1::evalSutehaiSub(MahjongAIState &param,int hai)
{
	int simtehai[34];
	int remain = MJSendMessage(MJMI_GETHAIREMAIN,0,0);
	int i,j,k,res,painum,maxpts,pts,debug = 0;
	double tmp,tmp2,ret,index;
	AGARI_LIST list;
	MJITehai resulthai;
	int paicount;
	double nokorihais;
	double nokoribuf[34];
	int tmp_tecnt[34];

	memcpy(&resulthai,&param.tehai,sizeof(resulthai));

	double value = 0;

	if(remain/4 == 0){
		paicount = 1;
	}else{
		/* 10���ȏ�̓c����Ȃ� */
		paicount = remain/4 > 10 ? 10 : remain/4;
	}

	//if(paicount < 5){
		paicount = 5;
	//}

	for(i=0;i<SIMULATECOUNT;i++){
		tmp=0.0;
		for(j=0;j<34;j++){
			tmp+=param.nokori[j];
		}
		nokorihais = tmp;
		memcpy(nokoribuf,param.nokori,sizeof(nokoribuf));
		memcpy(tmp_tecnt,param.te_cnt,sizeof(tmp_tecnt));
		
		for(j=0;j<paicount;j++){
			index = (nokorihais + 1.0) * (double)rand() / (double)(1.0 + RAND_MAX);
			tmp=0.0;
			for(k=0;k<34;k++){
				tmp+=nokoribuf[k];
				if(index < tmp){
					tmp_tecnt[k]++;
					tmp2 = nokoribuf[k] > 1.0 ? 1.0 : nokoribuf[k];
					nokoribuf[k]-=tmp2;
					nokorihais -= tmp2;
					break;
				}
			}
		}

		/* �ʓ|�����ǁA�܂���v�̔z��ɖ߂� (�b��) */
		painum = 0;
		for(j=0;j<34;j++){
			for(k=0;k<tmp_tecnt[j];k++){
				simtehai[painum++] = (j << 8);
			}
		}

		for(k=0;k<param.tehai.tehai_max+paicount;k++){
			simtehai[k] = (simtehai[k] >> 8) | ((simtehai[k] & 0xFF) << 8);
		}

		maxpts = search_agari(simtehai,param.tehai.tehai_max+paicount,&list,param.tehai.tehai_max+1,&param,getPoint);
		value += (double)maxpts/SIMULATECOUNT;
		if(maxpts > 0){
			if(list.tehai[0] == 0 && list.tehai[1] == 1 && list.tehai[2] == 2){
				debug++;
			}
		}

		/* �������̂��߂̍H�v */
		//if(i>SIMULATECOUNT/10 && 10.0 * value * SIMULATECOUNT / i < max_val) break;

	}
	//fprintf(fp,"%d",debug);
	return value;
}
