/*
 * MJ0.c
 * �Ƃ������k����MJ-0 �A���S���Y�����������܂�(on �܂������IF)
 * �A���S���Y���̒��쌠�͂Ƃ������k�������L���܂�
 * �܂������̒��쌠�͐Δ������������L���܂�
 * �v���O�����̒��쌠��kacky�����L���܂�
 */
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

#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "MJ0.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef struct{
	int num;
	int sum;
} MJ0_COMBI;

int MJ0(/* inputs */
		MJ0PARAM *pParam,int *pDora,int dlength,
		/* outputs */
		double *pNokorihai,double *pKikenhai,
		double *pMentsuSimo,double *pMentsuToimen,double *pMentsuKami)
{
	int i,j,k;
	int sum;
	int index;
	int mindex;
	int pai;
	int furiten;
	unsigned int r;
	int aNokorihai[34];
	int iniMentsu[3];
	int aPaikukan[4][34];
	int curMentsu[3];
	MJ0PARAM *pCurPrm;
	MJ0_COMBI aCombi[21+34];
	int aAnpai[3][34];
	int aRiichi[3];
	int aMentsu[3][5];
	int aMachi[34];
	
	iniMentsu[0] = 0;
	iniMentsu[1] = 0;
	iniMentsu[2] = 0;
	aRiichi[0] = 0;
	aRiichi[1] = 0;
	aRiichi[2] = 0;

	memset(aAnpai,0,sizeof(aAnpai));

	for(i=0;i<34;i++){
		pNokorihai[i] = 0.0;
		pKikenhai[i] = 0.0;
		aNokorihai[i] = 4;
	}

	for(i=0;i<21+34;i++){
		pMentsuSimo[i] = 0.0;
		pMentsuToimen[i] = 0.0;
		pMentsuKami[i] = 0.0;
	}

	/* �c��v�������� */
	pCurPrm = pParam;
	for(j=0;j<pCurPrm->pTehai->tehai_max;j++){
		aNokorihai[pCurPrm->pTehai->tehai[j] & 63]--;
	}
	for(i=0;i<4;i++){

		for(j=0;j<pCurPrm->pTehai->minshun_max;j++){
			aNokorihai[pCurPrm->pTehai->minshun[j] & 63]--;
			aNokorihai[(pCurPrm->pTehai->minshun[j] & 63) + 1]--;
			aNokorihai[(pCurPrm->pTehai->minshun[j] & 63) + 2]--;
		}
		if(i!=0) iniMentsu[i-1]+= pCurPrm->pTehai->minshun_max;

		for(j=0;j<pCurPrm->pTehai->minkou_max;j++){
			aNokorihai[pCurPrm->pTehai->minkou[j] & 63]-=3;
		}
		if(i!=0) iniMentsu[i-1]+= pCurPrm->pTehai->minkou_max;
		
		for(j=0;j<pCurPrm->pTehai->minkan_max;j++){
			aNokorihai[pCurPrm->pTehai->minkan[j] & 63]-=4;
		}
		if(i!=0) iniMentsu[i-1]+= pCurPrm->pTehai->minkan_max;
		
		for(j=0;j<pCurPrm->pTehai->ankan_max;j++){
			aNokorihai[pCurPrm->pTehai->ankan[j] & 63]-=4;
		}
		if(i!=0) iniMentsu[i-1]+= pCurPrm->pTehai->ankan_max;

		/* ���ꂽ�v�͊��Ɋ��肵�Ă���̂ŏ��� */
		for(j=0;j<pCurPrm->kawalength;j++){
			if(!(pCurPrm->pKawahai[j].state & MJKS_NAKI)) aNokorihai[pCurPrm->pKawahai[j].hai & 63]--;
			/* ���������v�ɂ��� */
			if(i!=0){
				aAnpai[i-1][pCurPrm->pKawahai[j].hai & 63] = 1;
			}

		}

		/* �������ɌŒ肵�Ă����ʎq������̂ł���΂���������ōs��(TODO) */

		pCurPrm++;
	}

	/* ���[�`��̎̂Ĕv�����p�C�ɂ���(�̂ď����l�����ĂȂ�����) */
	i = 0;
	j = 0;
	while(1){
		if(j >= pParam[i].kawalength) break;
		if(i!=0){
			if(pParam[i].pKawahai[j].state & MJKS_REACH){
				aRiichi[i - 1] = 1;
			}
			for(k=1;k<4;k++){
				if(aRiichi[k - 1]){
					aAnpai[k - 1][pParam[i].pKawahai[j].hai & 63] = 1;
				}
			}
		}

		i = (i + 1) & 3;
		if(i==0) j++;
	}

	for(i=0;i<dlength;i++){
		aNokorihai[pDora[i] & 63]--;
	}


	/* �w��񐔕��V�~�����[�V�������J��Ԃ� */
	for(i=0;i<SIMU_SIZE;i++){
		for(j=0;j<4;j++){
			memcpy(&aPaikukan[j][0],aNokorihai,sizeof(aNokorihai));
		}

		memset(aMentsu,0xFF,sizeof(aMentsu));
		memcpy(curMentsu,iniMentsu,sizeof(iniMentsu));

		/* �����A��F�n�Ȃǂ�ǂނ̂ł���΂����Ŕv��Ԃ�ύX���Ă����Ɨǂ�(TODO) */


		/* 4�ʎq�S�Ă̑��肪�����܂ŌJ��Ԃ� */
		while(curMentsu[0] != 4 || curMentsu[1] != 4 || curMentsu[2] != 4){
			for(j=0;j<3;j++){
				if(curMentsu[j] == 4) continue;
				/* �g�ݍ��킹���̏����� */

				/* ���q�̑g�ݍ��킹 */
				for(k=0;k<21;k++){
					pai = (k / 7) * 9 + k % 7; // �v�Z����v�ԍ��̐擪�̒l
					aCombi[k].num = aPaikukan[j][pai] * aPaikukan[j][pai+1] * aPaikukan[j][pai+2];
				}

				/* ���q�̑g�ݍ��킹 */
				for(k=0;k<34;k++){
					if(aPaikukan[j][k-21] == 4){
						aCombi[k+21].num = 4;
					}else if(aPaikukan[j][k-21] == 3){
						aCombi[k+21].num = 1;
					}else{
						aCombi[k+21].num = 0;
					}
				}

				/* �҂��ǂ݂ɂ��g�ݍ��킹���̍X�V(TODO) */

				/* ���v���v�Z */
				sum = 0;
				for(k=0;k<21+34;k++){
					aCombi[k].sum = sum;
					sum += aCombi[k].num;
				}

				/* �����ɂ��ʎq�𐶐� */
				if(sum == 0) goto failure;
				r = ((unsigned int)rand()) % sum;

				/* ����Ȃɂ�������Ȃ�����V�[�P���V�����T�[�`�� */
				for(k=0;k<21+34;k++){
					if(r < aCombi[k].sum + aCombi[k].num && aCombi[k].num != 0){
						/* ���̖ʎq�Ɍ���I */
						aMentsu[j][curMentsu[j]] = k;

						/* �ʎq���\������v��v��Ԃ��珜�� */
						if(k<21){
							if(aPaikukan[0][k] > 0)   aPaikukan[0][k]--;
							if(aPaikukan[0][k+1] > 0) aPaikukan[0][k+1]--;
							if(aPaikukan[0][k+2] > 0) aPaikukan[0][k+2]--;
							if(aPaikukan[1][k] > 0)   aPaikukan[1][k]--;
							if(aPaikukan[1][k+1] > 0) aPaikukan[1][k+1]--;
							if(aPaikukan[1][k+2] > 0) aPaikukan[1][k+2]--;
							if(aPaikukan[2][k] > 0)   aPaikukan[2][k]--;
							if(aPaikukan[2][k+1] > 0) aPaikukan[2][k+1]--;
							if(aPaikukan[2][k+2] > 0) aPaikukan[2][k+2]--;
							if(aPaikukan[3][k] > 0)   aPaikukan[3][k]--;
							if(aPaikukan[3][k+1] > 0) aPaikukan[3][k+1]--;
							if(aPaikukan[3][k+2] > 0) aPaikukan[3][k+2]--;
						}else{
							if(aPaikukan[0][k-21] >= 3) aPaikukan[0][k-21]-=3;
							if(aPaikukan[1][k-21] >= 3) aPaikukan[1][k-21]-=3;
							if(aPaikukan[2][k-21] >= 3) aPaikukan[2][k-21]-=3;
							if(aPaikukan[3][k-21] >= 3) aPaikukan[3][k-21]-=3;
						}

						if(j==0){
							pMentsuSimo[k] += 1.0;
						}else if(j==1){
							pMentsuToimen[k] += 1.0;
						}else{
							pMentsuKami[k] += 1.0;
						}

						curMentsu[j]++;
						break;
					}
				}

			}
			
		}

		/* �A�^�}�̐��� */
		for(j=0;j<3;j++){
			for(k=0;k<34;k++){
				if(aPaikukan[j][k] == 4){
					aCombi[k].num = 6;  // 4 C 2
				}else if(aPaikukan[j][k] == 3){
					aCombi[k].num = 3;  // 3 C 2
				}else if(aPaikukan[j][k] == 2){
					aCombi[k].num = 1;  // 2 C 2
				}else{
					aCombi[k].num = 0;
				}
			}
			/* �҂��ǂ݂ɂ��g�ݍ��킹���̍X�V(TODO) */

			/* ���v���v�Z */
			sum = 0;
			for(k=0;k<34;k++){
				aCombi[k].sum = sum;
				sum += aCombi[k].num;
			}

			/* �����ɂ��Ύq�𐶐� */
			if(sum == 0) goto failure;
			r = ((unsigned int)rand()) % sum;
			/* ����Ȃɂ�������Ȃ�����V�[�P���V�����T�[�`�� */
			for(k=0;k<34;k++){
				if(r < aCombi[k].sum + aCombi[k].num && aCombi[k].num != 0){
					/* ���̔v�Ɍ���I */
					aMentsu[j][4] = k;
					/* �A�^�}���\������v��v��Ԃ��珜�� */
					if(aPaikukan[0][k] >= 2) aPaikukan[0][k]-=2;
					if(aPaikukan[1][k] >= 2) aPaikukan[1][k]-=2;
					if(aPaikukan[2][k] >= 2) aPaikukan[2][k]-=2;
					if(aPaikukan[3][k] >= 2) aPaikukan[3][k]-=2;
					break;
				}
			}
		}

		

		/* ������v�����肷�� */
		for(;;){
			memset(aMachi,0,sizeof(aMachi));

			j = rand() % 3; // �N�̖ʎq�𓖂���ɂ��邩
			mindex = rand() % ((4 - iniMentsu[j]) * 3 + 2); // �ǂ̔v�𓖂���v�ɂ��邩
			if(mindex >= (4 - iniMentsu[j]) * 3){
				/* �P�R�҂� */
				aMachi[aMentsu[j][4]] = 1;

				if(aMentsu[j][4] < 27){
					/* ���גP�R */
					for(k=0;k<4;k++){
						if((aMentsu[j][k] % 7) != 6 && 
							(aMentsu[j][k] / 7)*9 + (aMentsu[j][k] % 7) + 3 == aMentsu[j][4]){
							aMachi[aMentsu[j][4] - 3] = 1;
						}
						if((aMentsu[j][k] % 7) != 0 && 
							(aMentsu[j][k] / 7)*9 + (aMentsu[j][k] % 7) - 1 == aMentsu[j][4]){
							aMachi[aMentsu[j][4] + 3] = 1;
						}
					}
				}
			}else{
				/* �ʎq�҂� */
				index = iniMentsu[j] + mindex/3;
				
				if(aMentsu[j][index] < 21){
					/* ���q */
					pai = (aMentsu[j][index] / 7) * 9 + (aMentsu[j][index] % 7);
					if((mindex % 3) == 1){
						/* �J���`���� */
						aMachi[pai] = 1;

						/* �Í��J�u�� */
						if(aMentsu[j][4] == pai + 1){
							aMachi[pai-1] = 1;
						}else if(aMentsu[j][4] == pai - 1){
							aMachi[pai+1] = 1;
						}

					}else if((mindex % 3) == 0 && (pai % 9) == 6){
						/* �y���`���� */
						aMachi[pai] = 1;
						/* �Í��J�u�� */
						if(aMentsu[j][4] == pai + 1){
							aMachi[pai+2] = 1;
						}else if(aMentsu[j][4] == pai + 2){
							aMachi[pai+1] = 1;
						}

					}else if((mindex % 3) == 2 && (pai % 9) == 0){
						/* �y���`���� */
						aMachi[pai+2] = 1;
						/* �Í��J�u�� */
						if(aMentsu[j][4] == pai){
							aMachi[pai+1] = 1;
						}else if(aMentsu[j][4] == pai + 1){
							aMachi[pai] = 1;
						}
					}else{
						/* ���� */
						if((mindex % 3) == 0){
							aMachi[pai] = 1;
							aMachi[pai+3] = 1;
							/* �Í��J�u�� */
							if(aMentsu[j][4] == pai + 1){
								aMachi[pai+2] = 1;
							}else if(aMentsu[j][4] == pai + 2){
								aMachi[pai+1] = 1;
							}

						}else{
							aMachi[pai+2] = 1;
							aMachi[pai-1] = 1;
							/* �Í��J�u�� */
							if(aMentsu[j][4] == pai){
								aMachi[pai+1] = 1;
							}else if(aMentsu[j][4] == pai + 1){
								aMachi[pai] = 1;
							}
						}

					}
				}else{
					/* ���q�̓V�����|���҂� */
					aMachi[aMentsu[j][index] - 21] = 1;
					aMachi[aMentsu[j][4]] = 1;
				}

			}

			furiten = 0;
			for(k=0;k<34;k++){
				if(aMachi[k] && aAnpai[j][k]){
					furiten = 1;
				}
			}

			if(furiten == 0){
				for(k=0;k<34;k++){
					if(aMachi[k]){
						pKikenhai[k] += 1.0;
					}
				}
			}
			break;

		}


		/* �c�����v���R�̐��Ƃ��ăJ�E���g */
		for(j=0;j<34;j++){
			pNokorihai[j] += aPaikukan[3][j];
		}
failure:
		j=0;

	}

	/* ���s�񐔂Ŋ���Z�����ĕ��ϒl�Ƃ��� */
	for(i=0;i<34;i++){
		pNokorihai[i] /= SIMU_SIZE;
		pKikenhai[i] /= SIMU_SIZE;
	}

	for(i=0;i<27+34;i++){
		pMentsuSimo[i] /= SIMU_SIZE;
		pMentsuToimen[i] /= SIMU_SIZE;
		pMentsuKami[i] /= SIMU_SIZE;
	}

	return 1;

}



#ifdef __cplusplus
}
#endif
