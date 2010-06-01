/*
 * MJ0.h
 * �Ƃ������k����MJ-0 �A���S���Y�����������܂�(on �܂������IF)
 * �A���S���Y���̒��쌠�͂Ƃ������k�������L���܂�
 * �܂������̒��쌠�͐Δ������������L���܂�
 * �v���O�����̒��쌠��kacky�����L���܂�
 */
#pragma once

#ifdef __cplusplus
extern "C" {
#endif

typedef unsigned int UINT;
typedef unsigned short USHORT;
#include "MIPIface.h"

#define SIMU_SIZE (5000)

typedef struct{
	MJITehai1 *pTehai;
	MJIKawahai *pKawahai;
	int kawalength;
} MJ0PARAM;

extern int MJ0(/* inputs */
		MJ0PARAM *pParam,int *pDora,int dlength,
		/* outputs */
		double *pNokoriHai,double *pKikenhai,
		double *pMentsuSimo,double *pMentsuToimen,double *pMentsuKami);

#ifdef __cplusplus
}
#endif
