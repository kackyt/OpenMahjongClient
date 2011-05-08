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
#include <windows.h>
#include <stdio.h>
#include <math.h>
#include <float.h>
#include <time.h>
#include "MIPIface.h"
#include "AILib.h"

//#define AIDUMP
#ifdef AIDUMP
//#define AIDUMP_1
//#define AIDUMP_2
//#define AIDUMP_3
//#define AIDUMP_STAT
//#define AIDUMP_POINT
#define AIDUMP_PARAM
#endif
#define DEBUG_MESSAGE

#define SIMULATECOUNT      (2000)

#define SCORE_KOUKEI_BIAS        (1.0)
#define SCORE_MENTSU_BIAS        (1.0)
#define SCORE_ANPAI              2 * (16)
#define SCORE_KIKENHAI           2 * (100)
#define SCORE_SUZI19             2 * (29)
#define SCORE_SUZI28             2 * (48)
#define SCORE_SUZI37             2 * (55)
#define SCORE_ZIHAI              2 * (34)
#define SCORE_19                 2 * (63)
#define SCORE_28                 2 * (70)
#define SCORE_37                 2 * (71)
#define SCORE_456                2 * (123)

#define SCORE_RIICHI_BIAS        (100.0) 
#define SCORE_IPPATSU_BIAS       (1000.0) 
#define SCORE_SUPAI_19           (0.079)
#define SCORE_SUPAI_28            (0.084)
#define SCORE_SUPAI_34567         (0.1)
#define SCORE_HANPAI_TRIPLE_BIAS (0.02)
#define SCORE_HANPAI_DOUBLE_BIAS (0.01)
#define SCORE_HANPAI_BIAS       (0.001)
#define SCORE_DORA_BIAS          (0.05)

typedef struct {
	double sc;
	double sc1;
	double sc2;
	double scc;
	int no;
} HAIPOINT;

static const int param_size[] = {
	9,
};

typedef enum {
	AI_DECISION_AGARI1,
	AI_DECISION_AGARI2,
	AI_DECISION_ORI,
} AI_DECISION;


class MahjongAI {
public :
	UINT InterfaceFunc(UINT message,UINT param1,UINT param2);
	MJITehai tehai;

#ifdef AIDUMP
	FILE *fp;
#endif
protected :
	int machi[34];
	char reach_flag[4];
	char ippatsu_flag[4];
	int te_cnt[34];
	int menzen;
	int nakiok_flag;
	int sthai;
	int doranum;
	double tehai_score;
	double nokori[34];
	double kikenhai[34];
	char anpai[34][4];
	int cha;
	int tenpai_flag;
	static int kyoku,kaze;
	int jun;
	int kyokustate;
	HAIPOINT hp[14];
	int *resultBuf;
	int current_p;
	int size_p;
	AI_DECISION decision;

	int tehai2Array(int *p);
	void initParam(void);
	void destroyParam(void);
	int getParam(int index);
	void printResult(int result);
	int search(int obj,int start,int mask);
	void set_machi(void);
	void set_Tehai(void);
	void select_Score(double sc_max,double scc_max);
	UINT sutehai_sub(int tsumohai);
	double eval_Tehai_sub(int atama_flag);
	double eval_Tehai(double max_val);
	double eval_Tehai2(void);
	double eval_hai(int hai);
	double eval_sutehai(int hai);
	int calc_sutehai(void);
	int calc_sutehai_easy(void);
	int nakability(int hai,int chii_flag);
	UINT koe_req(int no,int hai);
	UINT on_start_kyoku(int k,int c);
	UINT on_end_kyoku(UINT reason,LONG* inc_sc);
	UINT on_action(int player,int taishou,UINT action);
	UINT on_start_game(void);
	UINT on_end_game(int rank,LONG score);
	UINT on_exchange(UINT state,UINT option);
	void sendComment(int index);
};
enum {
	AI_KYOKUSTS_TSUMO,
	AI_KYOKUSTS_RON,
	AI_KYOKUSTS_TEKIAGARI,
	AI_KYOKUSTS_FURIKOMI,
	AI_KYOKUSTS_NORMAL,
};

enum {
	AI_MESSAGE_TSUMOLITTLE = 0,
	AI_MESSAGE_TSUMOMIDDLE,
	AI_MESSAGE_TSUMOBIG,
	AI_MESSAGE_RONLITTLE,
	AI_MESSAGE_RONMIDDLE,
	AI_MESSAGE_RONBIG,
	AI_MESSAGE_TEKIAGARILITTLE,
	AI_MESSAGE_TEKIAGARIMIDDLE,
	AI_MESSAGE_TEKIAGARIBIG,
	AI_MESSAGE_FURIKOMILITTLE,
	AI_MESSAGE_FURIKOMIMIDDLE,
	AI_MESSAGE_FURIKOMIBIG,
	AI_MESSAGE_TII,
	AI_MESSAGE_PON,
	AI_MESSAGE_RIICHI,
	AI_MESSAGE_TSUYOGARI,
};


static const TCHAR *message_table[] = {
	TEXT("�݂Ă��낱��ȃP�`�Ȃ��̂ł͂Ȃ��I"),
	TEXT("���l�����������悤�ȃZ���t�͂͂�����I�I�I"),
	TEXT("�͂��������`��������ɂȂ������̂�"),
	TEXT("���{�ڂɎ��ʂ̂��ȁc"),
	TEXT("���܂��Ȃǂ���̓G�ł͂Ȃ���I"),
	TEXT("��l���j���I�I�I"),
	TEXT("�t�b�c�����������͂͂₭�Ȃ����悤����"),
	TEXT("���c�������ɂ����܂̎��O�������I�Ȃ�΂��̎��O�̌��������Ă�낤"),
	TEXT("��c��͂�̂̃P���V���E�ł͂Ȃ��ȁB�Ȃ��c"),
	TEXT("���܂��Ƃ���ɂ͒v���I�ȈႢ�����邻��͗~�]�c���O���I�I"),
	TEXT("���I�I�o�A�o�J��"),
	TEXT("�c����̖��́c���Ƃǂꂭ�炢��"),
	TEXT("�Ȃ����c���܂�ď��߂Ă���͂Ȃ���"),
	TEXT("�Ȃ����c���܂�ď��߂Ă���͂Ȃ���"),
	TEXT("���{�ڂɎ��ʂ̂��ȁc"),
	TEXT("����͂������������Ĕ��������̂��D���Ȃ񂾁I"),
};

static const TCHAR * num_table[] ={
	TEXT("��"),
	TEXT("��"),
	TEXT("�O"),
	TEXT("�l"),
	TEXT("��"),
	TEXT("�Z"),
	TEXT("��"),
	TEXT("��"),
	TEXT("��"),
};

static const TCHAR * type_table[] ={
	TEXT("��"),
	TEXT("��"),
	TEXT("��"),
	TEXT("��"),
	TEXT("��"),
	TEXT("��"),
	TEXT("�k"),
	TEXT("��"),
	TEXT("��"),
	TEXT("��"),
};


static void sethaitext(TCHAR *p,int no)
{
	if(no < 27){
		sprintf(p,"%s%s",num_table[no%9],type_table[no/9]);
	}else{
		sprintf(p,"%s",type_table[no-27+3]);
	}
}

static int compare_hp(const HAIPOINT *a, const HAIPOINT *b)
{
    double res = a->sc - b->sc;
	if(res < 0){
		return 1;
	}else if(res > 0){
		return -1;
	}else{
		return 0;
	}
}

int MahjongAI::kyoku,MahjongAI::kaze;

TCHAR player_name[] = TEXT("�j�h�m�f");

UINT (WINAPI *MJSendMessage)(MahjongAI*,UINT,UINT,UINT);

static int debug_count = 0;

static int compare_int(const int *a, const int *b)
{
    return *a - *b;
}

#define PARAM_MAX (sizeof(param_size)/sizeof(int))

void MahjongAI::initParam(void)
{
	int siz = 1,i;

	for(i=0;i<PARAM_MAX;i++){
		siz *= param_size[i];
	}

	resultBuf = (int*)malloc(siz*sizeof(int));
	memset(resultBuf,0x00,siz*sizeof(int));
	current_p = 0;
	size_p = siz;
}

void MahjongAI::destroyParam(void)
{
	if(resultBuf) free(resultBuf);
}

int MahjongAI::getParam(int index)
{
	int i,p = current_p;

	for(i=0;i<index;i++){
		p /= param_size[i];
	}
	
	return p % param_size[index];
}

void MahjongAI::printResult(int result)
{
	int i;
	resultBuf[current_p] += 3 - result;
#ifdef AIDUMP_PARAM
	fclose(fp);
	fp = fopen(TEXT("./AIDUMP_COMMAND.csv"),TEXT("w"));
	for(i=0;i<size_p;i++){
		fprintf(fp,"%d,",resultBuf[i]);
	}
	fprintf(fp,"\n");
#endif
	current_p++;
	if(current_p == size_p) current_p = 0;

}

void MahjongAI::sendComment(int index)
{
	time_t tim = time(NULL);

	if((tim % 3) == 0){
		MJSendMessage(this,MJMI_FUKIDASHI,(UINT)message_table[index],0);
	}
}


// ��v�̒�����C�ӂ̔v�������A���̈ʒu��Ԃ�
int MahjongAI::search(int obj,int start,int mask)
{
	while(start<(int)tehai.tehai_max){
		if (!(mask&(1<<start)) && (int)tehai.tehai[start]==obj) break;
		start++;
	}
	return start<(int)tehai.tehai_max ? start : -1;
}

// ������v�𒲂ׁA�z��machi�ɓ����B
// �܂������Ă��邩�ǂ������ׂ�tenpai_flag���Z�b�g����B
void MahjongAI::set_machi(void)
{
	int i,j,cnt;
	(*MJSendMessage)(this,MJMI_GETMACHI,0,(UINT)machi);
	tenpai_flag = 0;
	for(i=0;i<34;i++){
		if (machi[i]) {
			cnt = 0;
			for(j=0;j<(int)tehai.tehai_max;j++) if ((int)tehai.tehai[j]==i) cnt++;
			if (cnt+(*MJSendMessage)(this,MJMI_GETVISIBLEHAIS,i,0)<4){
				tenpai_flag = 1;
				return;
			}
			tenpai_flag = -1;
		}
	}
}

#include "MJ0.h"


// ��v�̕ϐ�tehai��te_cnt���Z�b�g����
void MahjongAI::set_Tehai(void)
{
	int i;
	MJ0PARAM param[4];
	MJITehai mjtehai[4];
	MJIKawahai kawahai[4][20];
	UINT dora[8];
	double mentsu1[27+34];
	double mentsu2[27+34];
	double mentsu3[27+34];
	int doralen;

	param[0].pTehai = (MJITehai1 *)&mjtehai[0];
	param[1].pTehai = (MJITehai1 *)&mjtehai[1];
	param[2].pTehai = (MJITehai1 *)&mjtehai[2];
	param[3].pTehai = (MJITehai1 *)&mjtehai[3];
	(*MJSendMessage)(this,MJMI_GETTEHAI,0,(UINT)&mjtehai[0]);
	(*MJSendMessage)(this,MJMI_GETTEHAI,1,(UINT)&mjtehai[1]);
	(*MJSendMessage)(this,MJMI_GETTEHAI,2,(UINT)&mjtehai[2]);
	(*MJSendMessage)(this,MJMI_GETTEHAI,3,(UINT)&mjtehai[3]);
	param[0].pKawahai = &kawahai[0][0];
	param[1].pKawahai = &kawahai[1][0];
	param[2].pKawahai = &kawahai[2][0];
	param[3].pKawahai = &kawahai[3][0];
	param[0].kawalength = (*MJSendMessage)(this,MJMI_GETKAWAEX,(20 << 16) + 0,(UINT)&kawahai[0][0]);
	param[1].kawalength = (*MJSendMessage)(this,MJMI_GETKAWAEX,(20 << 16) + 1,(UINT)&kawahai[1][0]);
	param[2].kawalength = (*MJSendMessage)(this,MJMI_GETKAWAEX,(20 << 16) + 2,(UINT)&kawahai[2][0]);
	param[3].kawalength = (*MJSendMessage)(this,MJMI_GETKAWAEX,(20 << 16) + 3,(UINT)&kawahai[3][0]);

	doralen = (*MJSendMessage)(this,MJMI_GETDORA,(UINT)dora,0);

	MJ0(&param[0],(int*)dora,doralen,nokori,kikenhai,mentsu1,mentsu2,mentsu3);

#ifdef AIDUMP_1
	fprintf(fp,TEXT("<NOKORI>"));

	for(i=0;i<34;i++){
		fprintf(fp,TEXT("[%.1f]"),nokori[i]);
	}

	fprintf(fp,TEXT("</NOKORI>"));
#endif

	(*MJSendMessage)(this,MJMI_GETTEHAI,0,(UINT)&tehai);
#ifdef AIDUMP_COMMAND
	fprintf(fp,TEXT("GET TEHAI\n"));
#endif
	for(i=0;i<34;i++) te_cnt[i] = 0;
	for(i=0;i<(int)tehai.tehai_max;i++) te_cnt[tehai.tehai[i]]++;

	doranum = 0;
	for(i=0;i<doralen;i++){
		doranum += te_cnt[dora[i]];
	}
}


// �̂Ĕv���̏���
// tsumohai : �������Ă����v
UINT MahjongAI::sutehai_sub(int tsumohai)
{
	int mc[34];
	UINT kawa[30];
	int mcount,mpoint;
	UINT rchk=MJPIR_SUTEHAI;
	int i,j,hai,del_hai,hai_remain,tmp,furiten,kazu;
	int mhai,hais;
	MJITehai tmphai;

	// ���� srand���s��(�f�o�b�O���₷�����邽��)
#if 0
	srand(0xDEADBEEA);
#else
	srand((unsigned int)time(NULL));
#endif
	debug_count = 0;

	// ���݂̎�v�̏�Ԃ��Z�b�g����
	set_Tehai();
	
	// ���݂̑҂��v���擾����
	set_machi();

	// �c�������ꍇ�́u�c���v��
	if (tsumohai>=0 && tsumohai<34) if (machi[tsumohai]) return MJPIR_TSUMO;

	// ���[�`�������Ă���ꍇ�́u�c���؂�v
	if (reach_flag[0]) return MJPIR_SUTEHAI | 13;

	// ����v�ŗ�����ꍇ�͗���
	tmp = (*MJSendMessage)(this,MJMI_KKHAIABILITY,0,0);

#ifdef AIDUMP_COMMAND
	fprintf(fp,TEXT("KKHAIABILITY %u\n"),tmp);
#endif

	if (tmp) return MJPIR_NAGASHI;
	
	// �����c�����Ă����v������Ȃ�A���̔v������
	if (tsumohai>=0 && tsumohai<34) te_cnt[tsumohai]++;
	
	// �̂Ă�v�����߂�
	hai = calc_sutehai();
	if (hai<(int)tehai.tehai_max) del_hai = tehai.tehai[hai]; else del_hai = tsumohai;

#ifdef AIDUMP_POINT
	fprintf(fp,"\n");
#endif
	
	if (machi[hai]){
	}
	// ��O�ŁA�e���p�����ꍇ�̓��[�`�������悤���Ȃ��H
	if (menzen){
		mcount = 0;
		mpoint = 0;
		furiten = 0;
		hais = 0;

		memcpy(&tmphai,&tehai,sizeof(tmphai));
		te_cnt[del_hai]--;
		tmphai.tehai_max = 0;
		for(i=0;i<34;i++){
			for(j=0;j<te_cnt[i];j++){
				tmphai.tehai[tmphai.tehai_max++] = i;
			}
		}
		te_cnt[del_hai]++;

		hai_remain = (*MJSendMessage)(this,MJMI_GETHAIREMAIN,0,0);
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("GETHAIREMAIN %u\n"),hai_remain);
#endif
		tenpai_flag = (*MJSendMessage)(this,MJMI_GETMACHI,(UINT)&tmphai,(UINT)mc);
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("GETMACHI %u\n"),tenpai_flag);
#endif
		for(i=0;i<34;i++){
			if (mc[i]){
				mcount++;
				tmp = (*MJSendMessage)(this,MJMI_GETVISIBLEHAIS,i,0);
#ifdef AIDUMP_COMMAND
				fprintf(fp,TEXT("GETVISIBLEHAIS %u\n"),tmp);
#endif
				if (te_cnt[i]+tmp<4 && hai_remain>60){ rchk = MJPIR_REACH; break;}
				hais += 4 - (te_cnt[i] + tmp);
				mpoint += (*MJSendMessage)(this,MJMI_GETAGARITEN,(UINT)&tmphai,i);
				mhai = i;
				if(!furiten){
					kazu = (*MJSendMessage)(this,MJMI_GETKAWA,(30 << 16),(UINT)kawa);

					for(j=0;j<kazu;j++){
						if(mc[kawa[j]]){
							furiten = 1;
							break;
						}
					}
				}

			}
		}

		TCHAR comment[256];
		if(mcount > 0) mpoint /= mcount;

		if(furiten){
			if(mpoint > 2000 && hais > 4){
				rchk = MJPIR_REACH;
			}
		}else{
			if(((mpoint > 1300 && mhai >= 27 && mhai <=30 && mhai != 27 + kaze && mhai != 27 + kyoku/4 ) || hais > getParam(0))){
				rchk = MJPIR_REACH;
			}

			if(mpoint > 2000 && hais > 2){
				rchk = MJPIR_REACH;
			}
		}

		sprintf(comment,"mpoint %d,mcount %d,hais %d",mpoint,mcount,hais);
		
		MJSendMessage(this,MJMI_FUKIDASHI,(UINT)comment,0);	}

	// �e��t���O�̃Z�b�g
	if (rchk==MJPIR_REACH){
#ifdef AIDUMP_2
		TCHAR haitext[10];
		TCHAR haitext2[10];
		TCHAR haitext3[10];
		int j;
		fprintf(fp,"<TEHAI>");
		for(i=0;i<34;i++){
			for(j=0;j<te_cnt[i];j++){
				fprintf(fp,"%d ",i);
			}
		}
		fprintf(fp,"</TEHAI>");
		
		for(i=0;i<14;i++){
			sethaitext(haitext,hp[i].no);

			fprintf(fp,"<SCORE>%s:%.1f,%.1f,%.1f</SCORE>\n",
				haitext,hp[i].sc1,hp[i].sc2,hp[i].scc);
		}

#endif
		reach_flag[0] = 1;
	}
	return hai|rchk;
}


// ��v��]�����ĕ]���l��Ԃ�
double MahjongAI::eval_Tehai2(void)
{
	int i;
	double ret;

	ret = eval_Tehai_sub(0) * 10;
	for(i=0;i<34;i++){
		if (!te_cnt[i]) continue;
		ret *= eval_hai(i) + log10(te_cnt[i]);
	}

	return ret;
}

static int getPoint(AGARI_LIST *pList,void *ptr)
{
	MJITehai resulthai;
	int val,i,j;
	int isChiitoi = 1;
	MahjongAI *obj=(MahjongAI*)ptr;
	double coef = 4.0;
	int remain = (*MJSendMessage)(obj,MJMI_GETHAIREMAIN,0,0)/4;

	memcpy(&resulthai,&obj->tehai,sizeof(resulthai));
	for(i=0;i<pList->tehai_max;i++){
		if(pList->tehai[i] >> 8) coef *= 0.8;
		//for(j=0;j<(pList->tehai[i] >> 8);j++) coef *= 0.95635;
		if(--remain > 0) coef *= 1.2;
		pList->tehai[i] = pList->tehai[i] & 0xFF;
	}
	memcpy(&resulthai.tehai,pList->tehai,sizeof(int)*pList->tehai_max);
	resulthai.tehai_max = pList->tehai_max-1;
	qsort(&resulthai.tehai,pList->tehai_max,sizeof(int),(int (*)(const void*, const void*))compare_int);
	val = (*MJSendMessage)(obj,MJMI_GETAGARITEN,(UINT)&resulthai,(UINT)resulthai.tehai[pList->tehai_max-1]);

	/* ���Ύq�␳ */
	if(pList->tehai_max == 14){
		for(i=0;i<7;i++){
			if(resulthai.tehai[2*i] != resulthai.tehai[2*i+1]){
				isChiitoi = 0;
				break;
			}
		}
	}else{
		isChiitoi = 0;
	}


#ifdef AIDUMP_POINT
	fprintf(obj->fp,"%d,",val);
#endif
	debug_count++;

#if 1
	if(isChiitoi){
		return 180 * log(val * coef);
	}else{
		return 3000 * log(val * coef);
	}
#else
	if(isChiitoi){
		return val * coef / 16;
	}else{
		return val * coef;
	}
#endif
}


// ��v��]�����ĕ]���l��Ԃ�
double MahjongAI::eval_Tehai(double max_val)
{
	int simtehai[34];
	int remain = (*MJSendMessage)(this,MJMI_GETHAIREMAIN,0,0);
	int i,j,k,res,painum,maxpts,pts,debug = 0;
	double tmp,ret,index;
	AGARI_LIST list;
	MJITehai resulthai;
	int paicount;
	double nokorihais;
	double nokoribuf[34];

	memcpy(&resulthai,&tehai,sizeof(resulthai));

	double value = 0;

	if(remain/4 == 0){
		paicount = 1;
	}else{
		/* 10���ȏ�̓c����Ȃ� */
		paicount = remain/4 > 10 ? 10 : remain/4;
	}
	for(i=0;i<SIMULATECOUNT;i++){
		/* �ʓ|�����ǁA�܂���v�̔z��ɖ߂� (�b��) */
		painum = 0;
		for(j=0;j<34;j++){
			for(k=0;k<te_cnt[j];k++){
				simtehai[painum++] = (j << 8);
			}
		}
		tmp=0.0;
		for(j=0;j<34;j++){
			tmp+=nokori[j];
		}
		nokorihais = tmp;
		memcpy(nokoribuf,nokori,sizeof(nokoribuf));

		for(j=0;j<paicount;j++){
			index = (nokorihais + 1.0) * (double)rand() / (double)(1.0 + RAND_MAX);
			tmp=0.0;
			for(k=0;k<34;k++){
				tmp+=nokoribuf[k];
				if(index < tmp){
					simtehai[tehai.tehai_max+j]=(k << 8) + 1;
					nokoribuf[k]-=1.0;
					nokorihais -= 1.0;
					break;
				}
			}
		}

		/* �\�[�g���� */
		qsort(simtehai,tehai.tehai_max+paicount,sizeof(int),(int (*)(const void*, const void*))compare_int);

		for(k=0;k<tehai.tehai_max+paicount;k++){
			simtehai[k] = (simtehai[k] >> 8) | ((simtehai[k] & 0xFF) << 8);
		}

		maxpts = search_agari(simtehai,tehai.tehai_max+paicount,&list,tehai.tehai_max+1,this,getPoint);
#ifdef AIDUMP_3
		if(maxpts == 0){
			fprintf(fp,"rem(%02d)",remain);
			for(k=0;k<tehai.tehai_max+paicount;k++){
				fprintf(fp,"%02d ",simtehai[k]);
			}
			fprintf(fp,"\n");
		}
#endif
		value += (double)maxpts/SIMULATECOUNT;
#ifdef AIDUMP_STAT
		fprintf(fp,"%d,",maxpts);
#endif
		if(maxpts > 0){
			if(list.tehai[0] == 0 && list.tehai[1] == 1 && list.tehai[2] == 2){
				debug++;
			}
		}

		/* �������̂��߂̍H�v */
		//if(i>SIMULATECOUNT/10 && 10.0 * value * SIMULATECOUNT / i < max_val) break;

	}
	//fprintf(fp,"%d",debug);
#ifdef AIDUMP_STAT
	fprintf(fp,"\n");
#endif
	return value;
}

// ��v�𕔕��I�ɕ]������
double MahjongAI::eval_Tehai_sub(int atama_flag)
{
	int p=0,sc_max=0,sc,kazu,chk;
	char c;
	UINT tmp;

	for(p=0;p<34;p++) if (te_cnt[p]) break;
	if (p==34) return 0;
	c = te_cnt[p];

	// ���q�̕]��
	if (c>=3) {
		te_cnt[p]-=3;
		sc_max = eval_Tehai_sub(atama_flag)+18;
		te_cnt[p]+=3;
	}

	// �Ύq�̕]��
	if (c>=2) {
		te_cnt[p]-=2;
		tmp = (*MJSendMessage)(this,MJMI_GETVISIBLEHAIS,p,0);
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("GETVISIBLEHAIS %u\n"),tmp);
#endif
		sc = eval_Tehai_sub(1)+6*(!anpai[p][0] || !atama_flag)+!atama_flag*12-tmp;
		if (sc>sc_max) sc_max = sc;
		te_cnt[p]+=2;
	}

	// ���v�̕]��
	if (p<27){
		kazu = p%9;
		if (kazu<7){
			if (te_cnt[p+2]){
				te_cnt[p]--; te_cnt[p+2]--;

				// �J���`�����̕]��
				if (!anpai[p+1][0] && sthai!=p+1){
					tmp = (*MJSendMessage)(this,MJMI_GETVISIBLEHAIS,p+1,0);
#ifdef AIDUMP_COMMAND
					fprintf(fp,TEXT("GETVISIBLEHAIS %u\n"),tmp);
#endif
					sc = eval_Tehai_sub(atama_flag)+8-tmp;
					if (sc>sc_max) sc_max = sc;
					if (kazu<5) if (te_cnt[p+4]) if (!anpai[p+3][0] && sthai!=p+3){
						te_cnt[p+4]--;
						sc = eval_Tehai_sub(atama_flag)+12;
						if (sc>sc_max) sc_max = sc;
						te_cnt[p+4]++;
					}
				}

				// ���q�̕]��
				if (te_cnt[p+1]){
					te_cnt[p+1]--;
					sc = eval_Tehai_sub(atama_flag)+18;
					if (sc>sc_max) sc_max = sc;
					te_cnt[p+1]++;
				}
				te_cnt[p]++; te_cnt[p+2]++;
			}
		}

		// ���ʑ҂��A�y���`�����̕]��
		if (kazu<8){
			if (te_cnt[p+1]){
				chk = 0;
				if (kazu>0) if (anpai[p-1][0] || sthai==p-1) chk = 1;
				if (kazu<7) if (anpai[p+2][0] || sthai==p+2) chk = 1;
				if (!chk){
					te_cnt[p]--; te_cnt[p+1]--;
					sc = eval_Tehai_sub(atama_flag)+8+(kazu>0 && kazu<7)*4;
					if (sc>sc_max) sc_max = sc;
					te_cnt[p]++; te_cnt[p+1]++;
				}
			}
		}
	}

	// �v����������Ԃł̕]���_���o���Ă݂�
	te_cnt[p]--;
	sc = eval_Tehai_sub(atama_flag);
	if (sc>sc_max) sc_max = sc;
	te_cnt[p]++;
	return sc_max;
}

// �v��]�����ĕ]���l��Ԃ�
double MahjongAI::eval_hai(int hai)
{
	double ret = 1.0;
	int j,doras;
	UINT dora[6];
	UINT tmp;

	if (hai<27){
		if((hai % 9) == 0 || (hai % 9) == 8){
			ret += SCORE_SUPAI_19;
		}else if((hai % 9) == 1 || (hai % 9) == 7){
			ret += SCORE_SUPAI_28;
		}else{
			ret += SCORE_SUPAI_34567;
		}
	}else {
		tmp = (*MJSendMessage)(this,MJMI_GETVISIBLEHAIS,hai,0);
	
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("GETVISIBLEHAIS %u\n"),tmp);
#endif
		if (hai>30 || hai==cha+27 || hai==kaze+27){
			if(te_cnt[hai] >= 3){
				ret += SCORE_HANPAI_TRIPLE_BIAS;
			}
			if (tmp<2 && te_cnt[hai] == 2)
				ret+= SCORE_HANPAI_DOUBLE_BIAS;
			if (tmp<3 && te_cnt[hai] == 1)
				ret+= SCORE_HANPAI_BIAS;
		}
	}

	doras = (*MJSendMessage)(this,MJMI_GETDORA,(UINT)dora,0);

#ifdef AIDUMP_COMMAND
	fprintf(fp,TEXT("GETDORA %u\n"),doras);
#endif
	for(j=0;j<doras;j++)
		if (hai==(int)dora[j]) ret+=SCORE_DORA_BIAS;
	return ret;
}

// �̂Ĕv��]�����ĕ]���l��Ԃ�
double MahjongAI::eval_sutehai(int hai)
{
	int i;
	double ret = 0;
	double minus = 0;
	double plus = 0,tmp;

	minus += SCORE_KIKENHAI * kikenhai[hai];
	for(i=1;i<4;i++){
		tmp = 0.0;
		if (anpai[hai][i]){
		}else if (hai<27){
			int kazu = hai%9,fl=1;
			if (kazu>2) if (!anpai[hai-3][i]) fl = 0;
			if (fl) if (kazu<6) if (!anpai[hai+3][i]) fl = 0;
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
		if(ippatsu_flag[i]){
			tmp *= SCORE_IPPATSU_BIAS;
			minus *= SCORE_IPPATSU_BIAS;
		}else if (reach_flag[i]){
			tmp *= SCORE_RIICHI_BIAS;
			minus *= SCORE_RIICHI_BIAS;
		}

		plus += tmp;
	}
	return plus - minus;
}

void MahjongAI::select_Score(double sc_max,double scc_max)
{
	int i;
#if 0
	for(i=0;i<14;i++){
		hp[i].sc = hp[i].sc1;
	}
#else
	int rnum = 0;
	int shanten = 0;
	TENPAI_LIST list;

	/* �V�����e�����𐔂��� */
	shanten = search_tenpai((int*)tehai.tehai,tehai.tehai_max,NULL,&list,1,6);

	if(shanten != 0){
		shanten = list.shanten;
	}else{
		shanten = 4;
	}



	/* �I���邩�U�߂邩�̔��f */
	for(i=1;i<4;i++){
		if(reach_flag[i]) rnum++;
	}


	if(rnum > 0 && rnum + shanten > 2){
		decision = AI_DECISION_ORI;
		for(i=0;i<14;i++){
			hp[i].sc = hp[i].scc;
		}
	}else{
		if(sc_max < 1500){
			decision = AI_DECISION_AGARI2;
			for(i=0;i<14;i++){
				hp[i].sc = hp[i].sc2;
			}
		}else{
			decision = AI_DECISION_AGARI1;
			for(i=0;i<14;i++){
				hp[i].sc = hp[i].sc1;
			}
		}
	}

#endif

}

// �̂Ă�v�����߂�
int MahjongAI::calc_sutehai(void)
{
	int i,ret;

	// �̂Ă�v���������Ă݂āA�����Ƃ��]���l�̍������̂��Ƃ�
	double sc_max = -DBL_MAX;
	int sh;
	double sc,scc,scc_max=-DBL_MAX;
	int index = 0;
	TCHAR haitext[10];
	TCHAR haitext2[10];
	TCHAR haitext3[10];
	TCHAR comment[512];

	memset(hp,0,sizeof(hp));

#ifdef AIDUMP_1
	int j;
	fprintf(fp,"<CALC><TEHAI>");
	for(i=0;i<34;i++){
		for(j=0;j<te_cnt[i];j++){
			fprintf(fp,"%d ",i);
		}
	}
	fprintf(fp,"</TEHAI>");

#endif

	for(i=0;i<34;i++){
		if (!te_cnt[i]) continue;
#ifdef AIDUMP_1
		fprintf(fp,"<SUTEHAI><NUM>%d</NUM>",i);
#endif
		te_cnt[i]--;
		sthai = i;
#ifdef AIDUMP_1
	fprintf(fp,"<EVAL>");
#endif
		//fprintf(fp,"%d,",i);
		sc = eval_Tehai(sc_max);
		hp[index].sc1 = sc;
		hp[index].sc2 = eval_Tehai2();
		hp[index].no = i;
#ifdef AIDUMP_1
	fprintf(fp,"</EVAL>");
#endif
		scc = eval_sutehai(i);
#ifdef AIDUMP_1
		fprintf(fp,"<TOTAL>%.3f</TOTAL>",sc);
		fprintf(fp,"<SUTEHAI_VAL>%.3f</SUTEHAI_VAL>",scc);
		fprintf(fp,"</SUTEHAI>");
#endif

		hp[index].scc = scc;

		if(sc > sc_max){
			sc_max = sc;
		}

		if (scc>scc_max){
			scc_max = scc;  sh = i;
		}
		te_cnt[i]++;
		index++;
	}

	select_Score(sc_max,scc_max);

	qsort(hp,index,sizeof(HAIPOINT),(int (*)(const void*, const void*))compare_hp);
	
#ifdef DEBUG_MESSAGE
	sethaitext(haitext,hp[0].no);
	sethaitext(haitext2,hp[1].no);
	sethaitext(haitext3,hp[2].no);

	sprintf(comment,"%s:%.1f,%.1f,%.1f\n%s:%.1f,%.1f,%.1f\n%s:%.1f,%.1f,%.1f",
		haitext,hp[0].sc1,hp[0].sc2,hp[0].scc,
		haitext2,hp[1].sc1,hp[1].sc2,hp[1].scc,
		haitext3,hp[2].sc1,hp[2].sc2,hp[2].scc);

	MJSendMessage(this,MJMI_FUKIDASHI,(UINT)comment,0);
#endif	

	tehai_score = hp[0].sc;
	ret = search(hp[0].no,0,0);
#ifdef AIDUMP_1
		fprintf(fp,"</CALC>");
		fprintf(fp,"<MAX>%d</MAX>",hp[0].no);
		fprintf(fp,"<RET>%d</RET>",ret);
#endif

	return ret>=0 ? ret : 13;
}

// �̂Ă�v�����߂�
int MahjongAI::calc_sutehai_easy(void)
{
	int i,sh;

	// �̂Ă�v���������Ă݂āA�����Ƃ��]���l�̍������̂��Ƃ�
	double scc,scc_max=-DBL_MAX;

	for(i=0;i<34;i++){
		if (!te_cnt[i]) continue;
		te_cnt[i]--;
		scc = eval_Tehai2();

		if (scc>scc_max){
			scc_max = scc;  sh = i;
		}
		te_cnt[i]++;
	}

	return sh;
}


// �����Ƃ��ł��邩�ǂ������ׂ�
// hai : �Ώۂ̔v
// chii_flag : �`�[�ɂ��Ă��`�F�b�N���邩�ǂ���
// return : �ȉ��̒l�̘_���a
//		 1 : �|���ł���
//		 2 : �J���ł���
//		 4 : �`�[�P�i���j�ł���
//		 8 : �`�[�Q�i�E�j�ł���
//		16 : �`�[�R�i���j�ł���
//		32 : �����ł���
int MahjongAI::nakability(int hai,int chii_flag)
{
	int x,i,ret=0,kazu,furiten;
	UINT kawa[30];

	if (machi[hai]){
		kazu = (*MJSendMessage)(this,MJMI_GETKAWA,(30 << 16),(UINT)kawa);
		furiten = 0;

		for(i=0;i<kazu;i++){
			if(machi[kawa[i]]){
				furiten = 1;
				break;
			}
		}

		if(furiten){
#ifdef DEBUG_MESSAGE
			(*MJSendMessage)(this,MJMI_FUKIDASHI,(UINT)TEXT("�t���e��"),0);
#endif
		}else{
			ret |= 32;
		}
	}
	if (reach_flag[0]) return ret;
	if ((*MJSendMessage)(this,MJMI_GETHAIREMAIN,0,0)==0) return ret;
	if ((x=search(hai,0,0))>=0){
		if (x<(int)tehai.tehai_max-1){
			if ((int)tehai.tehai[x+1]==hai){
				ret |= 1;
				if (x<(int)tehai.tehai_max-2){
					if ((int)tehai.tehai[x+2]==hai) ret |= 2;
				}
			}
		}
	}
	if (chii_flag){
		if (hai<27){
			kazu = hai%9;
			if (kazu>1){
				if (te_cnt[hai-2]>0 && te_cnt[hai-1]>0) ret |= 8;
			}
			if (kazu<7){
				if (te_cnt[hai+2]>0 && te_cnt[hai+1]>0) ret |= 4;
			}
			if (kazu>0 && kazu<8){
				if (te_cnt[hai-1]>0 && te_cnt[hai+1]>0) ret |= 16;
			}
		}
	}
	return ret;
}

int MahjongAI::tehai2Array(int *p)
{
	int size = 0;
	int i,j;

	for(i=0;i<34;i++){
		for(j=0;j<te_cnt[i];j++){
			p[size++] = i;
		}
	}

	return size;
}

// ���Ƃ̎̂Ĕv�ɑ΂���A�N�V���������߂�
// no : ���ꂪ�̂Ă���
// hai : �����̂Ă���
// return : �A�N�V����
UINT MahjongAI::koe_req(int no,int hai)
{
	int chii_flag;
	int naki_ok;
	int hanpai;
	UINT tmp;
	UINT dora[8];
	int doralen;
	int doraflag;
	int i;
	int tmptehai[14];
	int tehaisize;
	int prevshanten;
	int nextshanten;
	TENPAI_LIST list;
	int sthai;

	doralen = (*MJSendMessage)(this,MJMI_GETDORA,(UINT)dora,0);
	set_Tehai();
	set_machi();
	chii_flag = (no == 3);
	naki_ok = nakability(hai,chii_flag);
	if (!naki_ok) return 0;
	if (naki_ok&32){
		tmp = (*MJSendMessage)(this,MJMI_GETAGARITEN,0,hai);
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("GETAGARITEN %u\n"),tmp);
#endif
		if (tmp>0) {
			return MJPIR_RON;
		}
	}

	/* �e���p�C�܂��̓I���Ă���΂����͖��Ȃ� */
	if (tenpai_flag==1 || decision == AI_DECISION_ORI) return 0;
	sthai = -1;

	hanpai = 0;
	for(i=27;i<34;i++){
		if ((te_cnt[i] >= 3)&&(i>=31 || i-27==cha || i-27==kaze)){
			hanpai++;
		}
	}

	tehaisize = tehai2Array(tmptehai);
	/* �V�����e�����𐔂��� */
	prevshanten = search_tenpai(tmptehai,tehaisize,NULL,&list,1,6);

	if(prevshanten != 0){
		prevshanten = list.shanten;
	}else{
		prevshanten = 6;
	}

	if (naki_ok&1){
		if(menzen == 0){
			if (te_cnt[hai]==2){
				te_cnt[hai]-=2;
				sthai = calc_sutehai_easy();
				te_cnt[sthai]--;
				tehaisize = tehai2Array(tmptehai);
				te_cnt[sthai]++;
				te_cnt[hai]+=2;
				/* �V�����e�����𐔂��� */
				nextshanten = search_tenpai(tmptehai,tehaisize,NULL,&list,1,6);
				
				if(nextshanten != 0){
					nextshanten = list.shanten;
				}else{
					nextshanten = 6;
				}

				if(nextshanten < prevshanten) return MJPIR_PON;
			}

		}
		if (hai>=27){

			if (te_cnt[hai]==2){
				if ((doranum >= 2)&&(hai>=31 || hai-27==cha || hai-27==kaze)){
					return MJPIR_PON;
				}
			}
		} else {
			doraflag = 0;

			for(i=0;i<doralen;i++){
				if(dora[i] == hai){
					doraflag = 1;
					break;
				}
			}

			if(hanpai > 0 && doraflag >= 0){
				return MJPIR_PON;
			}

		}
	}

	if(naki_ok & 4){
		te_cnt[hai+1]--;
		te_cnt[hai+2]--;
		sthai = calc_sutehai_easy();
		te_cnt[sthai]--;
		tehaisize = tehai2Array(tmptehai);
		te_cnt[sthai]++;
		te_cnt[hai+1]++;
		te_cnt[hai+2]++;
		/* �V�����e�����𐔂��� */
		nextshanten = search_tenpai(tmptehai,tehaisize,NULL,&list,1,6);
		
		if(nextshanten != 0){
			nextshanten = list.shanten;
		}else{
			nextshanten = 6;
		}
		
		if(nextshanten < prevshanten && (menzen == 0 || hanpai)) return MJPIR_CHII1;
	}
	if(naki_ok & 8){
		te_cnt[hai-1]--;
		te_cnt[hai-2]--;
		sthai = calc_sutehai_easy();
		te_cnt[sthai]--;
		tehaisize = tehai2Array(tmptehai);
		te_cnt[sthai]++;
		te_cnt[hai-1]++;
		te_cnt[hai-2]++;
		/* �V�����e�����𐔂��� */
		nextshanten = search_tenpai(tmptehai,tehaisize,NULL,&list,1,6);
		
		if(nextshanten != 0){
			nextshanten = list.shanten;
		}else{
			nextshanten = 6;
		}
		
		if(nextshanten < prevshanten && (menzen == 0 || hanpai)) return MJPIR_CHII2;
	}
	if(naki_ok & 16){
		te_cnt[hai+1]--;
		te_cnt[hai-1]--;
		sthai = calc_sutehai_easy();
		te_cnt[sthai]--;
		tehaisize = tehai2Array(tmptehai);
		te_cnt[sthai]++;
		te_cnt[hai+1]++;
		te_cnt[hai-1]++;
		/* �V�����e�����𐔂��� */
		nextshanten = search_tenpai(tmptehai,tehaisize,NULL,&list,1,6);
		
		if(nextshanten != 0){
			nextshanten = list.shanten;
		}else{
			nextshanten = 6;
		}
		
		if(nextshanten < prevshanten && (menzen == 0 || hanpai)) return MJPIR_CHII3;
	}
	return 0;
}

// �ǊJ�n���̏���
// k : ��
// c : ��
UINT MahjongAI::on_start_kyoku(int k,int c)
{
	int i,j,sc_max = 0,mysc;
	kyokustate = AI_KYOKUSTS_NORMAL;
	decision = AI_DECISION_AGARI1;
	set_Tehai();
	for(i=0;i<34;i++) {
		for (j=0;j<4;j++) anpai[i][j] = 0;
	}
	kyoku = k;
	kaze = kyoku/4;
	cha = c;
	menzen = 1;
	nakiok_flag = 0;
	jun = 0;
	sthai = -1;
	for(i=0;i<4;i++){
		reach_flag[i] = 0;
		ippatsu_flag[i] = 0;
	}
	tehai_score = eval_Tehai(0);
	set_machi();

	mysc = (*MJSendMessage)(this,MJMI_GETSCORE,0,0);

	for(i=1;i<4;i++){
		j = (*MJSendMessage)(this,MJMI_GETSCORE,i,0);
		if(j > sc_max) sc_max = j;
	}

	if(k > 4 && sc_max - mysc > 20000){
		sendComment(AI_MESSAGE_TSUYOGARI);
	}

	return 0;
}

// �ǏI�����̏���
// reason : �I���������R
// inc_sc : �_���̕ω�
UINT MahjongAI::on_end_kyoku(UINT reason,LONG* inc_sc)
{
	int sc = *inc_sc;

	switch(kyokustate){
	case AI_KYOKUSTS_TSUMO:
		if(sc < 4000){
			sendComment(AI_MESSAGE_TSUMOLITTLE);
		}else if(sc < 16000){
			sendComment(AI_MESSAGE_TSUMOMIDDLE);
		}else{
			sendComment(AI_MESSAGE_TSUMOBIG);
		}
		break;
	case AI_KYOKUSTS_RON:
		if(sc < 4000){
			sendComment(AI_MESSAGE_RONLITTLE);
		}else if(sc < 16000){
			sendComment(AI_MESSAGE_RONMIDDLE);
		}else{
			sendComment(AI_MESSAGE_RONBIG);
		}
		break;
	case AI_KYOKUSTS_TEKIAGARI:
		if(sc > -2000){
			sendComment(AI_MESSAGE_TEKIAGARILITTLE);
		}else if(sc > -6000){
			sendComment(AI_MESSAGE_TEKIAGARIMIDDLE);
		}else{
			sendComment(AI_MESSAGE_TEKIAGARIBIG);
		}
		break;
	case AI_KYOKUSTS_FURIKOMI:
		if(sc > -4000){
			sendComment(AI_MESSAGE_FURIKOMILITTLE);
		}else if(sc > -16000){
			sendComment(AI_MESSAGE_FURIKOMIMIDDLE);
		}else{
			sendComment(AI_MESSAGE_FURIKOMIBIG);
		}
		break;
	default:
		break;
	}

	return 0;
}

// �A�N�V�����ɑ΂��鉞��������
UINT MahjongAI::on_action(int player,int taishou,UINT action)
{
	int hai = action&63;

	if (action & MJPIR_REACH){
		reach_flag[player] = 1;
		ippatsu_flag[player] = 1;
		if(player == 0){
			sendComment(AI_MESSAGE_RIICHI);
		}
	}else{
		ippatsu_flag[player] = 0;
	}

	if(action & MJPIR_TSUMO){
		if(player == 0){
			kyokustate = AI_KYOKUSTS_TSUMO;
		}else{
			kyokustate = AI_KYOKUSTS_TEKIAGARI;
		}
	}
	if (action & (MJPIR_SUTEHAI | MJPIR_REACH)){
		anpai[hai][player] = 1;
		for(int i=0;i<4;i++) if (reach_flag[i]) anpai[hai][i] = 1;
		if (player==0) return 0;
		return koe_req(player,hai);
	}
	if (action & MJPIR_RON){
		if(player == 0){
			kyokustate = AI_KYOKUSTS_RON;
		}else if(taishou == 0){
#ifdef AIDUMP_1
			fprintf(fp,"<FURIKOMI/>");
#endif
			kyokustate = AI_KYOKUSTS_FURIKOMI;
		}else{
			kyokustate = AI_KYOKUSTS_TEKIAGARI;
		}
	}
	if ((action & MJPIR_PON) && player==0){
		nakiok_flag = 1;
		menzen = 0;
		sendComment(AI_MESSAGE_PON);
	}
	if ((action & MJPIR_CHII1) && player==0){
		menzen = 0;
		sendComment(AI_MESSAGE_TII);
	}
	if ((action & MJPIR_CHII2) && player==0){
		menzen = 0;
		sendComment(AI_MESSAGE_TII);
	}
	if ((action & MJPIR_CHII3) && player==0){
		menzen = 0;
		sendComment(AI_MESSAGE_TII);
	}
	if ((action & MJPIR_MINKAN) && player==0){
		menzen = 0;
		sendComment(AI_MESSAGE_PON);
	}
	return 0;
}

// �����J�n���̏���
UINT MahjongAI::on_start_game(void)
{
	return 0;
}

// �����I�����̏���
// rank : ����
// score : �_��
UINT MahjongAI::on_end_game(int rank,LONG score)
{
	/*char str[40];
	sprintf(str,"%d�_�A%d�ʂ��c",score,rank+1);
	(*MJSendMessage)(this,MJMI_FUKIDASHI,(UINT)str,0);*/
	return 0;
}

// �r���Q�����̏���
// state : ���̂Ƃ��̏��
// option : ��ԂɊ֘A���đ�������
UINT MahjongAI::on_exchange(UINT state,UINT option)
{
	if (state==MJST_INKYOKU){
		int i,j,k;
		set_Tehai();
		for(i=0;i<34;i++) {
			for (j=0;j<4;j++) anpai[i][j] = 0;
		}
		for(i=0;i<4;i++){
			reach_flag[i] = 0;
			ippatsu_flag[i] = 0;
		}

		MJIKawahai kawa[30];
		for(i=0;i<4;i++){
			k = (*MJSendMessage)(this,MJMI_GETKAWAEX,MAKELPARAM(i,30),(UINT)kawa);
			reach_flag[i] = 0;
			for(j=0;j<k;j++){
				anpai[kawa[j].hai&63][i] = 1;
				if (kawa[j].state&MJKS_REACH) reach_flag[i] = 1;
			}
		}

		kyoku = LOWORD(option);
		kaze = kyoku/4;
		cha = HIWORD(option);
		menzen = tehai.minshun_max+tehai.minkan_max+tehai.minkou_max==0;
		nakiok_flag = !menzen;
		sthai = -1;
		tehai_score = eval_Tehai(0);
		set_machi();
	}
	return 0;
}

// �C���X�^���X�p�̃C���^�[�t�F�[�X�֐�
UINT MahjongAI::InterfaceFunc(UINT message,UINT param1,UINT param2)
{
	UINT ret = MJR_NOTCARED;
#ifdef AIDUMP
	fp = fopen(TEXT("./AIDUMP_COMMAND.xml"),TEXT("a"));
#endif

	switch(message){
	case MJPI_SUTEHAI :
		jun++;
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("SUTEHAI %u\n"),param1);
#endif
		ret = sutehai_sub(LOWORD(param1));
		break;
	case MJPI_ONACTION :
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("ONACTION %u %u\n"),param1,param2);
#endif
		ret = on_action(LOWORD(param1),HIWORD(param1),param2);
		break;
	case MJPI_STARTKYOKU :
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("STARTKYOKU %u %u\n"),param1,param2);
#endif
		ret = on_start_kyoku(LOWORD(param1),LOWORD(param2));
		break;
	case MJPI_ENDKYOKU :
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("ENDKYOKU %u %u\n"),param1,param2);
#endif
		ret = on_end_kyoku(param1,(LONG*)param2);
		break;
	case MJPI_STARTGAME :
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("STARTGAME\n"));
#endif
		ret = on_start_game();
		break;
	case MJPI_ENDGAME :
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("ENDGAME %u %u\n"),param1,param2);
#endif
		ret = on_end_game(LOWORD(param1),(LONG)param2);
		printResult(LOWORD(param1));
		break;
	case MJPI_ONEXCHANGE :
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("ONEXCHANGE %u %u\n"),param1,param2);
#endif
		ret = on_exchange(LOWORD(param1),param2);
		break;
	case MJPI_CREATEINSTANCE :
		ret = sizeof(MahjongAI);
		break;
	case MJPI_INITIALIZE :
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("INITIALIZE\n"));
#endif
		MJSendMessage = (UINT (WINAPI *)(MahjongAI*,UINT,UINT,UINT))param2;
		initParam();
		ret = 0;
		break;
	case MJPI_YOURNAME :
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("YOUENAME\n"));
#endif
		ret = (UINT)player_name;
		break;
	case MJPI_DESTROY :
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("DESTROY\n"));
#endif
		destroyParam();
		ret = 0;
		break;
	case MJPI_ISEXCHANGEABLE :
#ifdef AIDUMP_COMMAND
		fprintf(fp,TEXT("ISEXCHANGEABLE\n"));
#endif
		ret = 0; // �r���Q���ɑΉ�����B�Ή��������Ȃ��ꍇ��0�ȊO�ɂ���B
		break;
	}

#ifdef AIDUMP
	fclose(fp);
#endif
	return ret;
}

extern "C" {
	// �C���^�[�t�F�[�X�֐�
	UINT WINAPI MJPInterfaceFunc(MahjongAI* inst,UINT message,UINT param1,UINT param2)
	{
		if (inst) return inst->InterfaceFunc(message,param1,param2);
		switch(message){
		case MJPI_CREATEINSTANCE :
			return sizeof(MahjongAI);
		case MJPI_INITIALIZE :
			MJSendMessage = (UINT (WINAPI *)(MahjongAI*,UINT,UINT,UINT))param2;
			return 0;
		case MJPI_YOURNAME :
			return (UINT)player_name;
		case MJPI_DESTROY :
			return 0;
		case MJPI_ISEXCHANGEABLE :
			return 0; // �r���Q���ɑΉ�����B�Ή��������Ȃ��ꍇ��0�ȊO�ɂ���B
		}
		return MJR_NOTCARED;
	}
};