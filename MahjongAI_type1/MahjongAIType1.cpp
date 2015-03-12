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
#include <stdlib.h>
#include "MahjongScoreAI.h"
#include "AILib.h"

/* �v�������̊��Ғl�̕␳�W�� */
static double dist_coef[] = {
    0.88,
    0.90,
    0.99,
    0.98,
    0.94,
    0.97,
    0.93,
    0.93,
    0.93,
    0.93
};

/* �v�̎�ނ��Ƃ̊��Ғl�̕␳�W�� */
static double kind_coef[] = {
    0.97,
    0.98,
    0.99,
    0.96,
    0.95
};

static double getKindCoef(MahjongAIState *state, unsigned num){
    num &= 0x3F;

    if (num >= 31){
        return kind_coef[3];
    }
    else if (num >= 27){
        if (state->cha == num - 27 || state->kaze == num - 27){
            return kind_coef[3];
        }
        else{
            return kind_coef[4];
        }
    }
    else{
        switch (num % 9) {
        case 0:
        case 8:
            return kind_coef[0];
        case 1:
        case 7:
            return kind_coef[1];
        default:
            return kind_coef[2];
        }
    }
}



static int compare_hai(const void *a, const void *b){
	return (*(int*)a & 0xFF) - (*(int*)b & 0xFF);
}


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
            coef *= getKindCoef(obj,pList->tehai[i]);
        }
		pList->tehai[i] = pList->tehai[i] & 0xFF;
	}
	memcpy(&resulthai.tehai,pList->tehai,sizeof(int)*pList->tehai_max);
	resulthai.tehai_max = pList->tehai_max-1;
	//qsort(&resulthai.tehai,pList->tehai_max,sizeof(int),(int (*)(const void*, const void*))compare_int);
	val = MahjongScoreAI::MJSendMessage(MJMI_GETAGARITEN,(UINT)&resulthai,(UINT)resulthai.tehai[pList->tehai_max-1]);

    return val * coef;

}

#endif

typedef struct {
    MahjongAIState *pState;
    int hai;
    int remain;
    double ret;
	int count;
} THREAD_PARAM;



// ��v��]�����ĕ]���l��Ԃ�
static DWORD WINAPI evalSutehaiSubSub(LPVOID param)
{
    THREAD_PARAM *prm = (THREAD_PARAM *)param;
    int simtehai;
    int remain = prm->remain;
    int i, j, k, l;
    double tmp, tmp2, ret, index,coef;
    int paicount;
    double nokorihais;
    double nokoribuf[34];
	MahjongAIType2 subai;
	MahjongAIState copystate;
	HAIPOINT hp[14];
	int hpsize;
	int score;

    double value = 0;

    if (remain / 4 == 0){
        paicount = 1;
    }
    else{
        /* 8���ȏ�̓c����Ȃ� */
        paicount = remain / 4;
    }


    for (i = 0; i<prm->count; i++){
		/* ��Ԃ������� */
		memcpy(&copystate, prm->pState, sizeof(MahjongAIState));
        tmp = 0.0;
        for (j = 0; j<34; j++){
            tmp += prm->pState->nokori[j];
        }
        nokorihais = tmp;
        memcpy(nokoribuf, prm->pState->nokori, sizeof(nokoribuf));
		coef = 1.0;

        for (j = 0; j<paicount; j++){
            index = (nokorihais + 1.0) * (double)rand() / (double)(1.0 + RAND_MAX);
            tmp = 0.0;
            for (k = 0; k<34; k++){
                tmp += nokoribuf[k];
                if (index < tmp){
                    simtehai = k;
                    tmp2 = nokoribuf[k] > 1.0 ? 1.0 : nokoribuf[k];
                    nokoribuf[k] -= tmp2;
                    nokorihais -= tmp2;
                    break;
                }
            }

			score = MahjongScoreAI::MJSendMessage(MJMI_GETAGARITEN, (UINT)&copystate.tehai, simtehai);

			if (score > 0){
				/* �a���� */
				value += coef * score;
				break;
			}
			else{
				/* SubAI�ɑł����� */
				copystate.te_cnt[simtehai]++;
				tmp = subai.evalSutehai(copystate, hp, hpsize);
				for (k = 0; k < hpsize; k++){
					if (hp[k].sc == tmp){
						/* �̂Ĕv */
						copystate.te_cnt[hp[k].no]--;
						for (l = 0; l < copystate.tehai.tehai_max; l++){
							if (copystate.tehai.tehai[l] == hp[k].no){
								copystate.tehai.tehai[l] = simtehai;
								break;
							}
						}
						break;
					}
				}

				qsort(&copystate.tehai.tehai, copystate.tehai.tehai_max, sizeof(int), compare_hai);
			}

			coef *= 0.8;


        }

    }

    prm->ret = value;

    return 0;
}



#define THREADNUM (4)

double MahjongAIType1::evalSutehaiSub(MahjongAIState &param, int hai)
{
    double sum = 0.0;
    DWORD dwID;
    THREAD_PARAM tparam[THREADNUM];
    HANDLE hThread[THREADNUM];
    int i;
    int remain = MJSendMessage(MJMI_GETHAIREMAIN, 0, 0);
    memset(hThread, 0, sizeof(hThread));

    for (i = 0; i<THREADNUM; i++){
        tparam[i].pState = &param;
        tparam[i].hai = hai;
        tparam[i].ret = 0.0;
        tparam[i].remain = remain;
		tparam[i].count = SIMULATECOUNT / THREADNUM;
        hThread[i] = (HANDLE)CreateThread(NULL, 0, evalSutehaiSubSub, &tparam[i], 0, &dwID);
    }

    WaitForMultipleObjects(THREADNUM, hThread, TRUE, INFINITE);

    for (i = 0; i<THREADNUM; i++){
        sum += tparam[i].ret;
    }


    return sum;

}



