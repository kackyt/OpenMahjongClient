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

#include <string.h>
#include <stdlib.h>
#include "AILib.h"

#ifdef __cplusplus
extern "C" {
#endif


static int isYaotyu(int pai)
{
    return pai >= 27 || (pai % 9) == 0 || (pai % 9) == 8;
}

static int isMenzen(GAMESTATE *gamestate, RESULT_ITEM *item){
	return item->menzen ? AI_TRUE : AI_FALSE;
}


static int isDaburii(GAMESTATE *gamestate, RESULT_ITEM *item);

/* 1�ʖ� */
/* �c�� */
static int isTsumo(GAMESTATE *gamestate, RESULT_ITEM *item)
{
	if (gamestate->tsumo && isMenzen(gamestate, item))
        return 1;
    return 0;
}


/* ���[�` */
static int isRiichi(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    if (isDaburii(gamestate, item))
        return 0;
    if (gamestate->riichi)
        return 1;
    return 0;
}

/* �ꔭ */
static int isIppatsu(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    if ((gamestate->riichi) && (gamestate->riichicount == 1))
        return 1;
    return 0;
}

static int numHanpai(GAMESTATE *gamestate, int no){
    int n = 0;
    if(no > 30) n++;
    if(no - 27 == gamestate->bakaze) n++;
    if(no - 27 == gamestate->zikaze) n++;
    return n;
}


/* �s���t */
static int isPinfu(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;
    
    if (!isMenzen(gamestate,item))
        return 0;
    if (item->machi != AI_MACHI_RYANMEN)
        return 0;
    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category != AI_SYUNTSU){
            return 0;
        }
	}

    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].category == AI_KOUTSU) return 0;
        if(item->mentsulist[i].category == AI_TOITSU && numHanpai(gamestate,item->mentsulist[i].pailist[0]) > 0) return 0;
    }
    return 1;
}

/* �^�����I */
static int isTanyao(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;
    
    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category == AI_SYUNTSU && (((gamestate->nakilist[i].pailist[0] % 9) == 0) ||
                                                                 ((gamestate->nakilist[i].pailist[0] % 9) == 6))){
            return 0;
        }
        if(gamestate->nakilist[i].category != AI_SYUNTSU && (((gamestate->nakilist[i].pailist[0] % 9) == 0) ||
                                                                 ((gamestate->nakilist[i].pailist[0] % 9) == 8) ||
                                                                 (gamestate->nakilist[i].pailist[0] >= 27))){
            return 0;
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].category == AI_SYUNTSU && (((item->mentsulist[i].pailist[0] % 9) == 0) ||
                                                                 ((item->mentsulist[i].pailist[0] % 9) == 6))){
            return 0;
        }
        if(item->mentsulist[i].category != AI_SYUNTSU && (((item->mentsulist[i].pailist[0] % 9) == 0) ||
                                                                 ((item->mentsulist[i].pailist[0] % 9) == 8) ||
                                                                 (item->mentsulist[i].pailist[0] >= 27))){
            return 0;
        }
    }
    return 1;
}

/* ��u���A��u�� */
static int isIipeikou(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i,prev = -1;
    int count = 0;

    if(!isMenzen(gamestate,item))
        return 0;
    
    for(i=0;i<item->mentsusize;i++){
        
        if(item->mentsulist[i].category == AI_SYUNTSU){
            if(item->mentsulist[i].pailist[0] == prev){
                prev = -1;
                count++;
            }else{
                prev = item->mentsulist[i].pailist[0];
            }
            
        }
    }
    
	if(count == 2){
		return 3;
	}else if(count == 1){
		return 1;
	}else{
		return 0;
	}
}


static int isHanpai(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i,n=0;
    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category != AI_SYUNTSU){
            n += numHanpai(gamestate,gamestate->nakilist[i].pailist[0]);
        }
    }

    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].category == AI_KOUTSU){
            n += numHanpai(gamestate,item->mentsulist[i].pailist[0]);
        }
    }
    return n;
}

/* �n�C�e�C */
static int isHaitei(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    if (gamestate->endpai)
        return 1;
    return 0;
}

/* ���J�� */
static int isRinsyan(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    if ((gamestate->kan) && (gamestate->tsumo))
        return 1;
    return 0;
}

/* ����     */
static int isCyankan(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    if ((gamestate->kan) && (!gamestate->tsumo))
        return 1;
    return 0;
}


/* 2�ʖ� */
/* �_�u���[ */
static int isDaburii(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    if ((gamestate->riichi) && 
        (gamestate->riichicount == gamestate->count))
        return 2;
    return 0;
}

/* ���Ύq */
static int isTiitoitsu(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    
    if (item->mentsusize == 7)
        return 2;
    return 0;
}

/* �`�����^�E���`���� */
static int isTyanta(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;
	int routou = 0;
	int jihai = 0;
	int syuntsu = 0;

    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category == AI_SYUNTSU){
			if(((gamestate->nakilist[i].pailist[0] % 9) == 0) ||
                ((gamestate->nakilist[i].pailist[0] % 9) == 6)){
				syuntsu++;
				routou++;
			}else{
				return 0;
			}
        }

        if(gamestate->nakilist[i].category != AI_SYUNTSU){
			if(gamestate->nakilist[i].pailist[0] >= 27){
				jihai++;
			}else if(((gamestate->nakilist[i].pailist[0] % 9) == 0) ||
                      ((gamestate->nakilist[i].pailist[0] % 9) == 8)){
				routou++;
			}else{
	            return 0;
			}
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].category == AI_SYUNTSU){
			if(((item->mentsulist[i].pailist[0] % 9) == 0) ||
                ((item->mentsulist[i].pailist[0] % 9) == 6)){
				syuntsu++;
				routou++;
			}else{
				return 0;
			}
        }
        if(item->mentsulist[i].category != AI_SYUNTSU){
			if(item->mentsulist[i].pailist[0] >= 27){
				jihai++;
			}else if(((item->mentsulist[i].pailist[0] % 9) == 0) ||
                      ((item->mentsulist[i].pailist[0] % 9) == 8)){
				routou++;
			}else{
	            return 0;
			}
        }
    }
    
	if(routou == 5 && syuntsu){
	    return isMenzen(gamestate,item) ? 3 : 2;
	}else if(routou + jihai == 5 && syuntsu){
		return isMenzen(gamestate,item) ? 2 : 1;
	}else{
		return 0;
	}
}

/* ��C�ʊ� */
static int isIttsu(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int flagtable[3][3] = { 0 };
    int i;

    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category == AI_SYUNTSU && ((gamestate->nakilist[i].pailist[0] % 9) == 0)){
            flagtable[gamestate->nakilist[i].pailist[0]/9][0]++;
        }
        if(gamestate->nakilist[i].category == AI_SYUNTSU && ((gamestate->nakilist[i].pailist[0] % 9) == 3)){
            flagtable[gamestate->nakilist[i].pailist[0]/9][1]++;
        }
        if(gamestate->nakilist[i].category == AI_SYUNTSU && ((gamestate->nakilist[i].pailist[0] % 9) == 6)){
            flagtable[gamestate->nakilist[i].pailist[0]/9][2]++;
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].category == AI_SYUNTSU && ((item->mentsulist[i].pailist[0] % 9) == 0)){
            flagtable[item->mentsulist[i].pailist[0]/9][0]++;
        }
        if(item->mentsulist[i].category == AI_SYUNTSU && ((item->mentsulist[i].pailist[0] % 9) == 3)){
            flagtable[item->mentsulist[i].pailist[0]/9][1]++;
        }
        if(item->mentsulist[i].category == AI_SYUNTSU && ((item->mentsulist[i].pailist[0] % 9) == 6)){
            flagtable[item->mentsulist[i].pailist[0]/9][2]++;
        }
    }

    for(i=0;i<3;i++){
        if(flagtable[i][0] >= 1 && flagtable[i][1] >= 1 && flagtable[i][2] >= 1) return isMenzen(gamestate,item) ? 2 : 1;
    }
    
    return 0;
}

/* �O�F���� */
static int isSansyoku(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int notable[4][9] = {0};    /* SYUNTSU_START�̂Ƃ���̐� */
    int i;
    
    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category == AI_SYUNTSU){
            notable[gamestate->nakilist[i].pailist[0]/9][gamestate->nakilist[i].pailist[0]%9]++;
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].category == AI_SYUNTSU){
            notable[item->mentsulist[i].pailist[0]/9][item->mentsulist[i].pailist[0]%9]++;
        }
    }

    for(i=0;i<9;i++){
        if(notable[0][i] >= 1 && notable[1][i] >= 1 && notable[2][i] >= 1) return isMenzen(gamestate,item) ? 2 : 1;
    }

    return 0;
}

/* �O�F���� */
static int isSandou(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int notable[4][9] = {0};    /* SYUNTSU_START�̂Ƃ���̐� */
    int i;
    
    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category == AI_KOUTSU || gamestate->nakilist[i].category == AI_ANKAN ||
           gamestate->nakilist[i].category == AI_MINKAN){
            notable[gamestate->nakilist[i].pailist[0]/9][gamestate->nakilist[i].pailist[0]%9]++;
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].category == AI_KOUTSU){
            notable[item->mentsulist[i].pailist[0]/9][item->mentsulist[i].pailist[0]%9]++;
        }
    }

    for(i=0;i<9;i++){
        if(notable[0][i] >= 1 && notable[1][i] >= 1 && notable[2][i] >= 1) return 2;
    }

    return 0;
}

/* �g�C�g�C */
static int isToitoi(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;
	int count = 0;
    
    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category == AI_KOUTSU || gamestate->nakilist[i].category == AI_ANKAN ||
           gamestate->nakilist[i].category == AI_MINKAN){
            count++;
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].category == AI_KOUTSU){
			count++;
        }
    }

    return count == 4 ? 2 : 0;
}

/* �O�Í��A�l�Í�   */
static int isSananko(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;
    int count = 0;
    
    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category == AI_ANKAN){
            count++;
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if((gamestate->tsumo || i != item->machipos) && item->mentsulist[i].category == AI_KOUTSU){
            count++;
        }
    }

	if(count == 4){
		return 13;
	}else if(count == 3){
		return 2;
	}else{
		return 0;
	}

}

/* �O�Ȏq�A�l�Ȏq   */
static int isSankantsu(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;
    int count = 0;
    
    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category == AI_ANKAN || gamestate->nakilist[i].category == AI_MINKAN){
            count++;
        }
    }

	if(count == 4){
		return 13;
	}else if(count == 3){
		return 2;
	}else{
		return 0;
	}
    
}

/* 3�ʖ� */

/* ����F�A����F */
static int isHonitsu(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int category[4] = {0};
    int i;

    
    for(i=0;i<gamestate->naki;i++){
        if(category[gamestate->nakilist[i].pailist[0]/9] == 0)
            category[gamestate->nakilist[i].pailist[0]/9] = 1;
    }
    
    for(i=0;i<item->mentsusize;i++){
        if(category[item->mentsulist[i].pailist[0]/9] == 0)
            category[item->mentsulist[i].pailist[0]/9] = 1;
    }

    if(category[0] + category[1] + category[2] == 1){
		if(category[3]){
	        return isMenzen(gamestate,item) ? 3 : 2;
		}else{
	        return isMenzen(gamestate,item) ? 6 : 5;
		}
    }else{
        return 0;
    }
}


/* 4�ʖ� */
/* ���O���A��O�� */
static int isSyousangen(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;
    int count = 0;
    int atama = 0;

    for(i=0;i<gamestate->naki;i++){
        if((gamestate->nakilist[i].category == AI_KOUTSU || gamestate->nakilist[i].category == AI_ANKAN ||
            gamestate->nakilist[i].category == AI_MINKAN) && gamestate->nakilist[i].pailist[0] >= 31){
            count++;
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if((item->mentsulist[i].category == AI_KOUTSU || item->mentsulist[i].category == AI_ANKAN ||
            item->mentsulist[i].category == AI_MINKAN) && item->mentsulist[i].pailist[0] >= 31){
            count++;
        }else if((item->mentsulist[i].category == AI_TOITSU) && item->mentsulist[i].pailist[0] >= 31){
            atama = 1;
        }
    }
    
	if(count == 3){
		return 13;
	}else if(count == 2 && atama){
		return 2;
	}else{
		return 0;
	}

}

/* ���V���A���V�� */
static int isHonroutou(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;
    int count = 0;
    int jihai = 0;

    for(i=0;i<gamestate->naki;i++){
        if((gamestate->nakilist[i].category == AI_KOUTSU || gamestate->nakilist[i].category == AI_ANKAN ||
            gamestate->nakilist[i].category == AI_MINKAN) && gamestate->nakilist[i].pailist[0] >= 27){
            jihai++;
        }else if((gamestate->nakilist[i].category == AI_KOUTSU || gamestate->nakilist[i].category == AI_ANKAN ||
            gamestate->nakilist[i].category == AI_MINKAN) &&
                 ((gamestate->nakilist[i].pailist[0] % 9) == 0 ||
                  (gamestate->nakilist[i].pailist[0] % 9) == 8)){
            count++;
		} else {
			return 0;
		}
    }
    
    for(i=0;i<item->mentsusize;i++){
        if((item->mentsulist[i].category == AI_KOUTSU || item->mentsulist[i].category == AI_ANKAN ||
            item->mentsulist[i].category == AI_MINKAN) && item->mentsulist[i].pailist[0] >= 27){
            jihai++;
        }else if((item->mentsulist[i].category == AI_TOITSU) && item->mentsulist[i].pailist[0] >= 27){
            jihai++;
        }else if((item->mentsulist[i].category == AI_KOUTSU || item->mentsulist[i].category == AI_ANKAN ||
            item->mentsulist[i].category == AI_MINKAN) &&
                 ((item->mentsulist[i].pailist[0] % 9) == 0 ||
                  (item->mentsulist[i].pailist[0] % 9) == 8)){
            count++;
        }else if((item->mentsulist[i].category == AI_TOITSU) &&
                 ((item->mentsulist[i].pailist[0] % 9) == 0 ||
                  (item->mentsulist[i].pailist[0] % 9) == 8)){
            count++;
		} else {
			return 0;
		}
    }

	if(count == 5 && jihai == 0){
		return 13;
	}else if(count + jihai == gamestate->naki + item->mentsusize){
		return 2;
	}else{
		return 0;
	}
    
}

/* �l�a */
static int isRenhou(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    if ((gamestate->count == 0) && 
        (!gamestate->oya) &&
        (!gamestate->membernaki) &&
        (gamestate->tsumo == 0))
        return 13;
    return 0;
}

/* �� */

/* ���m���o */
static int isKokushi(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    
    return 0;
}

/* �V�a */
/* �n�a */
static int isTenhou(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    if ((gamestate->count == 0) && 
        (!gamestate->membernaki) &&
        (gamestate->tsumo))
        return 13;
    return 0;
}

static int isSyousushi(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;
    int count = 0;
    int atama = 0;

    for(i=0;i<gamestate->naki;i++){
        if((gamestate->nakilist[i].category == AI_KOUTSU || gamestate->nakilist[i].category == AI_ANKAN ||
            gamestate->nakilist[i].category == AI_MINKAN) && gamestate->nakilist[i].pailist[0] >= 27 && gamestate->nakilist[i].pailist[0] <= 30){
            count++;
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if((item->mentsulist[i].category == AI_KOUTSU || item->mentsulist[i].category == AI_ANKAN ||
            item->mentsulist[i].category == AI_MINKAN) && item->mentsulist[i].pailist[0] >= 27 &&
           item->mentsulist[i].pailist[0] <= 30){
            count++;
        }else if((item->mentsulist[i].category == AI_TOITSU) && item->mentsulist[i].pailist[0] >= 27 &&
           item->mentsulist[i].pailist[0] <= 30){
            atama = 1;
        }
    }
    
    if(count == 3 && atama) return 13;
    if(count == 4) return 26;

    return 0;
}

/* ����F */
static int isTsuuiisou(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;
    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].pailist[0] < 27){
            return 0;
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].pailist[0] < 27){
            return 0;
        }
    }

    return 13;
}


/* �Έ�F */
static int isRiuiisou(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int i;

    for(i=0;i<gamestate->naki;i++){
        if((gamestate->nakilist[i].category == AI_KOUTSU || gamestate->nakilist[i].category == AI_ANKAN ||
            gamestate->nakilist[i].category == AI_MINKAN)){
            if(!(gamestate->nakilist[i].pailist[0] == 19 ||
               gamestate->nakilist[i].pailist[0] == 20 ||
               gamestate->nakilist[i].pailist[0] == 21 ||
               gamestate->nakilist[i].pailist[0] == 23 ||
               gamestate->nakilist[i].pailist[0] == 25 ||
               gamestate->nakilist[i].pailist[0] == 32)
               ){
                return 0;
            }
        }

        if((gamestate->nakilist[i].category == AI_SYUNTSU) &&
           gamestate->nakilist[i].pailist[0] != 19
           ){
            return 0;
        }
    }
    
    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].category == AI_KOUTSU || item->mentsulist[i].category == AI_TOITSU){
            if(!(item->mentsulist[i].pailist[0] == 19 ||
               item->mentsulist[i].pailist[0] == 20 ||
               item->mentsulist[i].pailist[0] == 21 ||
               item->mentsulist[i].pailist[0] == 23 ||
               item->mentsulist[i].pailist[0] == 25 ||
               item->mentsulist[i].pailist[0] == 32)
               ){
                return 0;
            }
        }

        if((item->mentsulist[i].category == AI_SYUNTSU) &&
           item->mentsulist[i].pailist[0] != 19
           ){
            return 0;
        }
    }
    
    return 13;
}

/* ��A�� */
static int isTyuren(GAMESTATE *gamestate, RESULT_ITEM *item)
{
    int table[9] = {0};
    const int table2[] = {3,1,1,1,1,1,1,1,3};
    int i,tmp=0;

    
    for(i=0;i<item->mentsusize;i++){
        if(item->mentsulist[i].pailist[0] >= 27) return 0;
        switch(item->mentsulist[i].category){
          case AI_KOUTSU:
            table[item->mentsulist[i].pailist[0] % 9]+=3;
            break;
          case AI_SYUNTSU:
            table[item->mentsulist[i].pailist[0] % 9]++;
            table[item->mentsulist[i].pailist[1] % 9]++;
            table[item->mentsulist[i].pailist[2] % 9]++;
            break;
          case AI_TOITSU:
            table[item->mentsulist[i].pailist[0] % 9]+=2;
            break;
          default:
            break;
        }
    }
    
    for(i=0;i<9;i++){
        if(table[i] == table2[i] + 1){
            if(tmp == 0){
                tmp = 1;
            }else{
                return 0;
            }
        }else if(table[i] != table2[i]){
            return 0;
        }
    }
    return 13;
}

static int (*funcs[])(GAMESTATE *, RESULT_ITEM *) = {
    isTsumo,
    isRiichi,
    isIppatsu,
    isPinfu,
    isTanyao,
    isIipeikou,
    isHanpai,
    isHaitei,
    isRinsyan,
    isCyankan,
    isDaburii,
    isTiitoitsu,
    isTyanta,
    isIttsu,
    isSansyoku,
    isSandou,
    isToitoi,
    isSananko,
    isSankantsu,
    isHonitsu,
    isSyousangen,
    isHonroutou,
    isRenhou,
    isKokushi,
    isTenhou,
    isSyousushi,
    isTsuuiisou,
    isRiuiisou,
    isTyuren,
};

static int(*funcs_chiitoi[])(GAMESTATE *, RESULT_ITEM *) = {
	isTsumo,
	isRiichi,
	isIppatsu,
	isTanyao,
	isHaitei,
	isCyankan,
	isDaburii,
	isTiitoitsu,
	isTyanta,
	isHonitsu,
	isHonroutou,
	isRenhou,
	isTenhou,
	isTsuuiisou,
};



static int compare_int(const int *a, const int *b)
{
    return *a - *b;
}


/* resultitem��resultlist����1������Đݒ� */
void make_resultitem(int *paiarray, int *mentsu, int length,RESULT_ITEM *item,GAMESTATE *gamestate,int agarihai,int machi)
{
    int mentsu_save[14];
    t_mentsu machi_mentsu;
    int pos=0,mpos = 0;
    int i,j;

    memset(item,0,sizeof(RESULT_ITEM));
    memset(&machi_mentsu,0,sizeof(machi_mentsu));

    memcpy(mentsu_save,mentsu,sizeof(int)*length);

    item->machi = machi;
    item->machihai = agarihai;
	item->machipos = -1;
    item->menzen = AI_TRUE;

    for(i=0;i<gamestate->naki;i++){
        if(gamestate->nakilist[i].category != AI_ANKAN){
			item->menzen =  AI_FALSE;
		}
    }

    switch(machi){
      case AI_MACHI_KANCHAN:
      case AI_MACHI_PENCHAN:
      case AI_MACHI_RYANMEN:
        machi_mentsu.category = AI_SYUNTSU;
        break;
      case AI_MACHI_TANKI:
        machi_mentsu.category = AI_TOITSU;
        break;
      default:
        machi_mentsu.category = AI_KOUTSU;
        break;
    }

    pos = 0;
    while(pos < length){
        switch(mentsu_save[pos]){
          case AI_UKIHAI:
            machi_mentsu.pailist[mpos++] = paiarray[pos];
			if(item->machipos < 0){
				item->machipos = item->mentsusize;
				item->mentsusize++;
			}
            mentsu_save[pos] = -1;
            pos++;
            break;
          case AI_KOUTSU:
            mentsu_save[pos] = -1;
            item->mentsulist[item->mentsusize].pailist[0] = paiarray[pos];
            mentsu_save[pos+1] = -1;
            item->mentsulist[item->mentsusize].pailist[1] = paiarray[pos+1];
            mentsu_save[pos+2] = -1;
            item->mentsulist[item->mentsusize].pailist[2] = paiarray[pos+2];
            item->mentsulist[item->mentsusize].category = AI_KOUTSU;
            item->mentsusize++;
            pos+=3;
            break;
          case AI_ATAMA:
            mentsu_save[pos] = -1;
            item->mentsulist[item->mentsusize].pailist[0] = paiarray[pos];
            mentsu_save[pos+1] = -1;
            item->mentsulist[item->mentsusize].pailist[1] = paiarray[pos+1];
            item->mentsulist[item->mentsusize].category = AI_TOITSU;
            item->mentsusize++;
            pos+=2;
			break;
          case AI_SYUNTSU_START:
            mentsu_save[pos] = -1;
            item->mentsulist[item->mentsusize].pailist[0] = paiarray[pos];

            for(i=pos+1;i<length;i++){
                if(mentsu_save[i] == AI_SYUNTSU_MIDDLE && paiarray[i] == paiarray[pos] + 1){
                    mentsu_save[i] = -1;
                    item->mentsulist[item->mentsusize].pailist[1] = paiarray[i];
                    break;
                }
            }

            for(j=i+1;j<length;j++){
                if(mentsu_save[j] == AI_SYUNTSU_END && paiarray[j] == paiarray[pos] + 2){
                    mentsu_save[j] = -1;
                    item->mentsulist[item->mentsusize].pailist[2] = paiarray[j];
                    break;
                }
            }

            item->mentsulist[item->mentsusize].category = AI_SYUNTSU;
            item->mentsusize++;
            break;
          default:
            pos++;
            break;
        }
    }

	if(machi_mentsu.category == AI_KOUTSU && (agarihai & 0x3F) != machi_mentsu.pailist[0]){
		/* �V�����|���҂� */
		for(i=0;i<item->mentsusize;i++){
			if(item->mentsulist[i].category == AI_TOITSU && item->mentsulist[i].pailist[0] == (agarihai & 0x3F)){
				pos = i;
				item->mentsulist[i].category = AI_KOUTSU;
				item->mentsulist[i].pailist[2] = agarihai & 0xFF;
				machi_mentsu.category = AI_TOITSU;
			}
		}
	}else{
		pos = item->machipos;
		machi_mentsu.pailist[mpos++] = agarihai;
		qsort(&machi_mentsu.pailist,mpos,sizeof(int),(int (*)(const void*, const void*))compare_int);
	}

	/* �オ��̔��� */
	switch(machi_mentsu.category){
	case AI_SYUNTSU:
		if(machi_mentsu.pailist[0] + 1 != machi_mentsu.pailist[1] ||
			machi_mentsu.pailist[0] + 2 != machi_mentsu.pailist[2]){
			return;
		}
		break;
	case AI_TOITSU:
		if(machi_mentsu.pailist[0] != machi_mentsu.pailist[1]){
			return;
		}
		break;
	case AI_KOUTSU:
	default:
		if(machi_mentsu.pailist[0] != machi_mentsu.pailist[1] ||
			machi_mentsu.pailist[0] != machi_mentsu.pailist[2]){
			return;
		}
		break;
	}

    memcpy(&item->mentsulist[item->machipos],&machi_mentsu,sizeof(t_mentsu));

	item->machipos = pos;

    make_resultitem_bh(item,gamestate);
}

void make_resultitem_bh(RESULT_ITEM *item,GAMESTATE *gamestate)
{
	int han[35] = { 0 };
    int i,j;
    int pts,rpts;
	int pinfu = 0;
    
	if (item->mentsusize == 7)
	{
		/* ���Ύq */
		item->fu = 25; // ���Ύq��25��

		/* ���̌v�Z */
		for (i = 0; i<sizeof(funcs_chiitoi) / sizeof(void*); i++) {
			han[i] = funcs_chiitoi[i](gamestate, item);
			item->han += han[i];
			if (i == 0 && han[i]) pinfu = 1;
		}
		/* �h�� */
		for (i = 0; i < gamestate->dorasize; i++) {
			for (j = 0; j < item->mentsusize; j++) {
				if (gamestate->dorapai[i] == (item->mentsulist[j].pailist[0] & 0x3F)) {
					item->han += 2;
				}
			}
		}
	} else {
		/* ���̌v�Z */
		for (i = 0; i<sizeof(funcs) / sizeof(void*); i++) {
			han[i] = funcs[i](gamestate, item);
			item->han += han[i];
			if (i == 0 && han[i]) pinfu = 1;
		}

		if (item->han < 1) {
			item->score = item->coscore = item->oyascore = 0;
			return;
		}

		item->fu = 20;

		if (isMenzen(gamestate, item) && !gamestate->tsumo) {
			item->fu += 10; // �ʑO������10���ǉ�
		}
		if (gamestate->tsumo && !pinfu) {
			item->fu += 2;
		}

		switch (item->machi) {
		case AI_MACHI_KANCHAN:
		case AI_MACHI_PENCHAN:
		case AI_MACHI_TANKI:
			item->fu += 2;
			break;
		default:
			break;
		}
		for (i = 0; i<gamestate->naki; i++) {
			switch (gamestate->nakilist[i].category) {
			case AI_ANKAN:
				item->fu += isYaotyu(gamestate->nakilist[i].pailist[0]) ? 32 : 16;
				break;
			case AI_MINKAN:
				item->fu += isYaotyu(gamestate->nakilist[i].pailist[0]) ? 16 : 8;
				break;
			case AI_KOUTSU:
				item->fu += isYaotyu(gamestate->nakilist[i].pailist[0]) ? 4 : 2;
				break;
			default:
				break;
			}
		}

		for (i = 0; i<item->mentsusize; i++) {
			switch (item->mentsulist[i].category) {
			case AI_TOITSU:
				item->fu += numHanpai(gamestate, item->mentsulist[i].pailist[0]) * 2;
				break;
			case AI_KOUTSU:
				if (i == item->machipos && !gamestate->tsumo) {
					item->fu += isYaotyu(item->mentsulist[i].pailist[0]) ? 4 : 2;
				}
				else {
					item->fu += isYaotyu(item->mentsulist[i].pailist[0]) ? 8 : 4;
				}
				break;
			default:
				break;
			}
		}
		/* 10�������͐؂�グ */
		pts = item->fu % 10;
		item->fu = item->fu - pts + (pts ? 10 : 0);
		/* �h�� */
		for (i = 0; i < gamestate->dorasize; i++) {
			for (j = 0; j < item->mentsusize; j++) {
				switch (item->mentsulist[j].category) {
				case AI_ANKAN:
				case AI_MINKAN:
					if (gamestate->dorapai[i] == (item->mentsulist[j].pailist[0] & 0x3F)) {
						item->han += 4;
					}
					break;
				case AI_TOITSU:
					if (gamestate->dorapai[i] == (item->mentsulist[j].pailist[0] & 0x3F)) {
						item->han += 2;
					}
					break;
				case AI_KOUTSU:
					if (gamestate->dorapai[i] == (item->mentsulist[j].pailist[0] & 0x3F)) {
						item->han += 3;
					}
					break;
				case AI_SYUNTSU:
					if (gamestate->dorapai[i] == (item->mentsulist[j].pailist[0] & 0x3F)) {
						item->han++;
					}
					if (gamestate->dorapai[i] == (item->mentsulist[j].pailist[1] & 0x3F)) {
						item->han++;
					}
					if (gamestate->dorapai[i] == (item->mentsulist[j].pailist[2] & 0x3F)) {
						item->han++;
					}
					break;
				}
			}

			for (j = 0; j < gamestate->naki; j++) {
				switch (gamestate->nakilist[j].category) {
				case AI_ANKAN:
				case AI_MINKAN:
					if (gamestate->dorapai[i] == (gamestate->nakilist[j].pailist[0] & 0x3F)) {
						item->han += 4;
					}
					break;
				case AI_KOUTSU:
					if (gamestate->dorapai[i] == (gamestate->nakilist[j].pailist[0] & 0x3F)) {
						item->han += 3;
					}
					break;
				case AI_SYUNTSU:
					if (gamestate->dorapai[i] == (gamestate->nakilist[j].pailist[0] & 0x3F)) {
						item->han++;
					}
					if (gamestate->dorapai[i] == (gamestate->nakilist[j].pailist[1] & 0x3F)) {
						item->han++;
					}
					if (gamestate->dorapai[i] == (gamestate->nakilist[j].pailist[2] & 0x3F)) {
						item->han++;
					}
					break;

				}

			}
		}
	}


    if(item->han >= 13){
        /* �𖞈ȏ� */
        if(gamestate->oya){
            item->score = 48000 * (item->han / 13);
            item->coscore = item->score / 3;
        }else{
            item->score = 32000 * (item->han / 13);
            item->oyascore = item->score / 2;
            item->coscore = item->score / 4;
        }
    }else if(item->han >= 11){
        /* �O�{�� */
        if(gamestate->oya){
            item->score = 36000;
            item->coscore = 12000;
        }else{
            item->score = 24000;
            item->oyascore = 12000;
            item->coscore = 6000;
        }
    }else if(item->han >= 8){
        /* �{�� */
        if(gamestate->oya){
            item->score = 24000;
            item->coscore = 8000;
        }else{
            item->score = 16000;
            item->oyascore = 8000;
            item->coscore = 4000;
        }
    }else if(item->han >= 6){
        /* ���� */
        if(gamestate->oya){
            item->score = 18000;
            item->coscore = 6000;
        }else{
            item->score = 12000;
            item->oyascore = 6000;
            item->coscore = 3000;
        }
    }else{
        pts = (item->fu * (gamestate->oya ? 6 : 4)) << (item->han+2);
		/* �؂�グ���� */
		if((item->fu == 30 && item->han == 4) || (item->fu == 60 && item->han == 3)){
			if(gamestate->oya){
				pts = 12000;
			}else{
				pts = 8000;
			}
		}
        /* ���� */
        if(gamestate->oya){
            if(pts >= 12000){
                item->score = 12000;
                item->coscore = 4000;
            }else{
                rpts = pts % 100;
                item->score = pts - rpts + (rpts ? 100 : 0);
                rpts = (pts / 3) % 100;
                item->coscore = pts/3 - rpts + (rpts ? 100 : 0);
            }
        }else{
            if(pts >= 8000){
                item->score = 8000;
                item->oyascore = 4000;
                item->coscore = 2000;
            }else{
                rpts = pts % 100;
                item->score = pts - rpts + (rpts ? 100 : 0);
                rpts = (pts / 2) % 100;
                item->oyascore = pts/2 - rpts + (rpts ? 100 : 0);
                rpts = (pts / 4) % 100;
                item->coscore = pts/4 - rpts + (rpts ? 100 : 0);
            }
        }   
    }
}


#ifdef __cplusplus
}
#endif