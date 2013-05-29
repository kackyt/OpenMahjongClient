// MahjongAITestGUIDlg.cpp : �C���v�������e�[�V���� �t�@�C��
//

#include <stdlib.h>
#include "stdafx.h"
#include "MahjongAITestGUI.h"
#include "MahjongAITestGUIDlg.h"
#include "AILib.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif

#define WM_REFRESH (WM_USER + 0)

/////////////////////////////////////////////////////////////////////////////
// CMahjongAITestGUIDlg �_�C�A���O

CMahjongAITestGUIDlg::CMahjongAITestGUIDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CMahjongAITestGUIDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(CMahjongAITestGUIDlg)
	m_strKyoku = _T("0");
	m_strWait = _T("10");
	m_strHoura2 = _T("0");
	m_strHoura = _T("0");
	m_strTenpai = _T("0");
	m_strHouraR = _T("(0.0)");
	m_strHouraR2 = _T("(0.0)");
	m_strTenpaiR = _T("(0.0)");
	m_strSeek = _T("");
	m_strDebug = _T("0");
	//}}AFX_DATA_INIT
	// ����: LoadIcon �� Win32 �� DestroyIcon �̃T�u�V�[�P���X��v�����܂���B
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMahjongAITestGUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CMahjongAITestGUIDlg)
	DDX_Control(pDX, IDC_BTNNEXT, m_btnNext);
	DDX_Control(pDX, IDC_BTNPREV, m_btnPrev);
	DDX_Control(pDX, IDC_BTNMJ, m_view);
	DDX_Text(pDX, IDC_KYOKU, m_strKyoku);
	DDX_Text(pDX, IDC_EDITWAIT, m_strWait);
	DDX_Text(pDX, IDC_HOURA2, m_strHoura2);
	DDX_Text(pDX, IDC_HOURA, m_strHoura);
	DDX_Text(pDX, IDC_TENPAI, m_strTenpai);
	DDX_Text(pDX, IDC_HOURAR, m_strHouraR);
	DDX_Text(pDX, IDC_HOURAR2, m_strHouraR2);
	DDX_Text(pDX, IDC_TENPAIR, m_strTenpaiR);
	DDX_Text(pDX, IDC_EDTSEEK, m_strSeek);
	DDX_Text(pDX, IDC_DEBUGP, m_strDebug);
	//}}AFX_DATA_MAP
	DDX_Control(pDX, IDC_MESSAGE, m_ctrlMessage);
}

BEGIN_MESSAGE_MAP(CMahjongAITestGUIDlg, CDialog)
	//{{AFX_MSG_MAP(CMahjongAITestGUIDlg)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTNNEXT, OnBtnnext)
	ON_BN_CLICKED(IDC_BTNPREV, OnBtnprev)
	ON_BN_CLICKED(IDC_BTNAUTO, OnBtnauto)
	ON_WM_DESTROY()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTNWAIT, OnBtnwait)
	ON_BN_CLICKED(IDC_AI, OnAi)
	ON_MESSAGE(WM_REFRESH,OnRefresh)
	ON_BN_CLICKED(IDC_BTNSEEK, OnBtnseek)
	ON_BN_CLICKED(IDC_BTNRDDUMP, OnBtnrddump)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

static unsigned int gSeed;

static int myrand()
{
	gSeed = gSeed * 1103515245U + 12345;
	return gSeed >> 16;
}

static void mysrand(unsigned int seed)
{
	gSeed = seed;
}


extern "C" {
UINT WINAPI MJPInterfaceFunc(void* inst,UINT message,UINT param1,UINT param2);
};

static void shuffle(int arr[], int n);

typedef struct {
	GAMESTATE gamestate;
	int agarihai;
} MJ_GAMESTATE;

static UINT __cdecl workFunc(LPVOID param)
{
	CMahjongAITestGUIDlg *pDlg = (CMahjongAITestGUIDlg*)param;

	do {
		switch(pDlg->m_command){
		case MJCOM_AUTO:
		case MJCOM_NEXT:
			if(pDlg->m_state == MJSTATE_KYOKU){
				pDlg->nextPai();
			}else{
				pDlg->newKyoku();
			}
			break;
		case MJCOM_PREV:
			pDlg->prevPai();
			break;
		default:
			break;
		}

		pDlg->PostMessage(WM_REFRESH);

		Sleep(pDlg->m_iWait);
	}while(pDlg->m_command == MJCOM_AUTO);

	pDlg->m_command = MJCOM_NONE;
	pDlg->PostMessage(WM_REFRESH,1);

	return 0;
}


static int scoreCallback(int*paiarray,int*mentsu,int length,int machi,void *inf)
{
	RESULT_ITEM item;
	MJ_GAMESTATE *state = (MJ_GAMESTATE *)inf;
	make_resultitem(paiarray,mentsu,length,&item,&state->gamestate,state->agarihai,machi);

	return item.score;
	//return item.mentsusize == 7 ? item.score/300 : item.score;
}

static CMahjongAITestGUIDlg *pGObj;

UINT WINAPI MJSendMessage(LPVOID inst,UINT message,UINT param1,UINT param2)
{
	UINT ret = 0;
	int idx;
	int i;
	MJITehai tehai;
	MJITehai *pTehai;
	UINT *p;
	MJIKawahai *pKawahai;
	CMahjongAITestGUIDlg *pObj = pGObj;
	CTestView *pView = &pObj->m_view;
	TENPAI_LIST tlist;
	int num;

	switch(message){
	case MJMI_GETTEHAI:
		pTehai = (MJITehai*)param2;
		memset(pTehai,0,sizeof(MJITehai));
		if(param1 == 0){
			memcpy(pTehai->tehai,pView->m_aTehai,pView->m_iTehaiSize*sizeof(UINT));
			pTehai->tehai_max = pView->m_iTehaiSize;
		}
		ret = 1;
		break;
	case MJMI_GETMACHI:
		p = (UINT*)param2;
		for(i=0;i<34;i++){
			p[i] = 0;
		}
		ret = 0;
		if(param1 != 0){
			pTehai = (MJITehai*)param1;
		}else{
			memset(&tehai,0x0,sizeof(tehai));
			tehai.tehai_max = 13;
			memcpy(tehai.tehai,pView->m_aTehai,sizeof(int)*tehai.tehai_max);
			pTehai = &tehai;
		}
		num = search_tenpai((int *)pTehai->tehai,pTehai->tehai_max,(int *)p,&tlist,1,0);
		ret = num > 0 ? 1 : 0;
		break;
	case MJMI_GETAGARITEN:
		if(param1 != 0){
			MJ_GAMESTATE gs;
			pTehai = (MJITehai*)param1;

			memset(&gs,0,sizeof(gs));
			gs.gamestate.zikaze = 0;
			gs.gamestate.bakaze = 0;

			for(i=0;i<pTehai->ankan_max;i++){
				gs.gamestate.nakilist[gs.gamestate.naki].category = AI_ANKAN;
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[0] = pTehai->ankan[0];
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[1] = pTehai->ankan[1];
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[2] = pTehai->ankan[2];
				gs.gamestate.naki++;
			}

			for(i=0;i<pTehai->minkan_max;i++){
				gs.gamestate.nakilist[gs.gamestate.naki].category = AI_MINKAN;
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[0] = pTehai->minkan[i];
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[1] = pTehai->minkan[i];
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[2] = pTehai->minkan[i];
				gs.gamestate.naki++;
			}

			for(i=0;i<pTehai->minkou_max;i++){
				gs.gamestate.nakilist[gs.gamestate.naki].category = AI_KOUTSU;
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[0] = pTehai->minkou[i];
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[1] = pTehai->minkou[i];
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[2] = pTehai->minkou[i];
				gs.gamestate.naki++;
			}

			for(i=0;i<pTehai->minshun_max;i++){
				gs.gamestate.nakilist[gs.gamestate.naki].category = AI_SYUNTSU;
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[0] = pTehai->minshun[i];
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[1] = pTehai->minshun[i]+1;
				gs.gamestate.nakilist[gs.gamestate.naki].pailist[2] = pTehai->minshun[i]+2;
				gs.gamestate.naki++;
			}

			gs.gamestate.dorapai[0] = pView->m_iDora;


			gs.gamestate.dorasize = 1;
			gs.gamestate.count = 2;

			gs.agarihai = (int)param2;

			ret = search_score((int *)pTehai->tehai,pTehai->tehai_max,&gs,scoreCallback);
		}
		break;
	case MJMI_GETKAWA:
		idx = LOWORD(param1);
		if(idx == 0){
			memcpy((UINT*)param2,pView->m_aSutehai,sizeof(UINT)*pView->m_iSutehaiSize);
			ret = pView->m_iSutehaiSize;
		}else{
			ret = 0;
		}
		break;
	case MJMI_GETKAWAEX:
		idx = LOWORD(param1);
		pKawahai = (MJIKawahai*)param2;
		if(idx == 0){
			for(i=0;i<pView->m_iSutehaiSize;i++){
				pKawahai[i].hai = pView->m_aSutehai[i];
				pKawahai[i].state = 0;
			}
			pView->m_iSutehaiSize;
		}else{
			ret = 0;
		}
		break;
	case MJMI_GETDORA:
		p = (UINT*)param1;

		switch(pView->m_iDora){
		case 33:
			p[0] = 31;
			break;
		case 30:
			p[0] = 27;
			break;
		case 8:
			p[0] = 0;
			break;
		case 17:
			p[0] = 9;
			break;
		case 26:
			p[0] = 18;
			break;
		default:
			p[0] = pView->m_iDora + 1;
			break;
		}
		ret = 1;
		break;
	case MJMI_GETHAIREMAIN:
		ret = 70;
		ret-= pView->m_iSutehaiSize*4;
		break;
	case MJMI_GETVISIBLEHAIS:
		ret = 0;
		idx = LOWORD(param1);

		for(i=0;i<pView->m_iSutehaiSize;i++){
			if(pView->m_aSutehai[i] == idx) ret++;
		}

		if(pView->m_iDora == idx){
			ret++;
		}
		
		
		break;
	case MJMI_FUKIDASHI:
		pObj->m_ctrlMessage.appendMessage(CString((const char*)param1));
		//pObj->m_message += (const char*)param1;
		printf((const char*)param1);
		printf("\n");
		break;
	case MJMI_GETSCORE:
		ret = 25000;
		break;
	case MJMI_GETVERSION:
		ret = 12;
		break;
	case MJMI_GETKYOKU:
	case MJMI_GETHONBA:
	case MJMI_GETREACHBOU:
	case MJMI_ANKANABILITY:
	case MJMI_KKHAIABILITY:
	case MJMI_LASTTSUMOGIRI:
	case MJMI_GETRULE:
	case MJMI_SETSTRUCTTYPE:
	case MJMI_SETAUTOFUKIDASHI:
	case MJMI_GETWAREME:
	default:
		ret = 0;
		break;
	}

	return ret;

}



/////////////////////////////////////////////////////////////////////////////
// CMahjongAITestGUIDlg ���b�Z�[�W �n���h��

BOOL CMahjongAITestGUIDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ���̃_�C�A���O�p�̃A�C�R����ݒ肵�܂��B�t���[�����[�N�̓A�v���P�[�V�����̃��C��
	// �E�B���h�E���_�C�A���O�łȂ����͎����I�ɐݒ肵�܂���B
	SetIcon(m_hIcon, TRUE);			// �傫���A�C�R����ݒ�
	SetIcon(m_hIcon, FALSE);		// �������A�C�R����ݒ�
	
	// TODO: ���ʂȏ��������s�����͂��̏ꏊ�ɒǉ����Ă��������B
	mysrand((unsigned int)time(NULL));
	m_inst = NULL;
	m_comp = NULL;
#ifdef LOAD_LIBRARY
	m_comp = ::LoadLibrary("MahjongAI.dll");
	if(m_comp == NULL){
		printf("Cannot load Library.\n");
		return -1;
	}

	m_func = (MJPIFunc)::GetProcAddress(m_comp,"MJPInterfaceFunc");

	if(m_func == NULL){
		printf("Cannot load Function.\n");
		exit(1);
	}
#else
	m_func = MJPInterfaceFunc;
#endif

	aiInit();

	SetTimer(1, 1000, NULL);

	m_iWait = 10;

	pGObj = this;
	
	return TRUE;  // TRUE ��Ԃ��ƃR���g���[���ɐݒ肵���t�H�[�J�X�͎����܂���B
}

void CMahjongAITestGUIDlg::aiInit() 
{
	int dummyHai[] = { 4, 5, 6, 7};
	int size;

	if(m_inst){
		m_func(m_inst,MJPI_INITIALIZE,0,(UINT)MJSendMessage);
		free(m_inst);
	}
	m_func(NULL,MJPI_INITIALIZE,0,(UINT)MJSendMessage);
	size = m_func(NULL,MJPI_CREATEINSTANCE,0,0);
	if(size > 0){
		m_inst = malloc(size);
	}
	m_func(m_inst,MJPI_INITIALIZE,0,(UINT)MJSendMessage);

	m_func(m_inst,MJPI_STARTGAME,0,0);
	m_func(m_inst,MJPI_BASHOGIME,(UINT)dummyHai,0);

	m_state = MJSTATE_INIT;
	m_command = MJCOM_NONE;
	m_iKyoku = 0;
	m_iHoura = 0;
	m_iHoura2 = 0;
	m_iTenpai = 0;
}

// �����_�C�A���O�{�b�N�X�ɍŏ����{�^����ǉ�����Ȃ�΁A�A�C�R����`�悷��
// �R�[�h���ȉ��ɋL�q����K�v������܂��BMFC �A�v���P�[�V������ document/view
// ���f�����g���Ă���̂ŁA���̏����̓t���[�����[�N�ɂ�莩���I�ɏ�������܂��B

void CMahjongAITestGUIDlg::OnPaint() 
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �`��p�̃f�o�C�X �R���e�L�X�g

		SendMessage(WM_ICONERASEBKGND, (WPARAM) dc.GetSafeHdc(), 0);

		// �N���C�A���g�̋�`�̈���̒���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �A�C�R����`�悵�܂��B
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

// �V�X�e���́A���[�U�[���ŏ����E�B���h�E���h���b�O���Ă���ԁA
// �J�[�\����\�����邽�߂ɂ������Ăяo���܂��B
HCURSOR CMahjongAITestGUIDlg::OnQueryDragIcon()
{
	return (HCURSOR) m_hIcon;
}

void CMahjongAITestGUIDlg::OnBtnnext() 
{
	if(m_command == MJCOM_NONE){
		m_btnNext.EnableWindow(FALSE);
		m_btnPrev.EnableWindow(FALSE);
		m_command = MJCOM_NEXT;
		AfxBeginThread(workFunc,this);
	}

}

void CMahjongAITestGUIDlg::OnBtnprev() 
{
	if(m_command == MJCOM_NONE){
		m_btnNext.EnableWindow(FALSE);
		m_btnPrev.EnableWindow(FALSE);
		m_command = MJCOM_PREV;
		AfxBeginThread(workFunc,this);
	}
}

void CMahjongAITestGUIDlg::OnBtnauto() 
{
	if(m_command == MJCOM_NONE){
			m_btnNext.EnableWindow(FALSE);
			m_btnPrev.EnableWindow(FALSE);
			m_command = MJCOM_AUTO;
			AfxBeginThread(workFunc,this);
	}else{
		m_command = MJCOM_NONE;
	}
}



static void shuffle(char arr[], int n){

  int i, rnd, temp;

  for(i=0;i<n;i++){
    rnd = myrand() % n;
    temp = arr[i];
    arr[i] = arr[rnd];
    arr[rnd] = temp;
  }
}

static int compare_int(const int *a, const int *b)
{
    return *a - *b;
}

static int getPoint(AGARI_LIST *pList,void *ptr)
{
	return 1000;
}


void CMahjongAITestGUIDlg::newKyoku(bool reset)
{
	int i;
	LONG dummy[] = { 0, 0, 0, 0};
	FILE *fp;

	if(reset){
		if(m_state != MJSTATE_INIT){
			int aSim[13+18];
			AGARI_LIST list;
			m_func(m_inst,MJPI_ENDKYOKU,MJEK_RYUKYOKU,(UINT)dummy);
			m_iKyoku++;
			/* �O�̋ǂ͏オ�ꂽ���𔻒� */
			for(i=0;i<13+18;i++){
				aSim[i] = m_aPai[i+1];
			}
			qsort(aSim,13+18,sizeof(int),(int (*)(const void*, const void*))compare_int);
			
			if(search_agari(aSim,13+18,NULL,14,NULL,getPoint) != 0){
				m_iHoura2++;
			}
		}

		for(i=0;i<136;i++){
			m_aPai[i] = i/4;
		}
		
		/* �V���b�t�� */
		shuffle(m_aPai,136);
		if((fp = fopen("paidata","ab")) != NULL){
			fwrite(m_aPai,136,1,fp);
			fclose(fp);
		}
	}

	/* �z�v */
	m_view.m_iDora = m_aPai[0];
	for(i=0;i<13;i++){
		m_view.m_aTehai[i] = m_aPai[i+1];
	}
	m_view.m_iTehaiSize = 13;
	m_view.m_iTsumohai = m_aPai[14];
	m_view.m_iSutehaiSize = 0;
	m_iIndex = 15;

	qsort(m_view.m_aTehai,13,sizeof(int),(int (*)(const void*, const void*))compare_int);


	m_state = MJSTATE_KYOKU;
	m_func(m_inst,MJPI_STARTKYOKU,0,0);


	//Invalidate(FALSE);
}

void CMahjongAITestGUIDlg::nextPai()
{
	int ret,num;
	TENPAI_LIST tlist;
	int p[34];

	if(m_state != MJSTATE_AGARI){
		ret = m_func(m_inst,MJPI_SUTEHAI,m_view.m_iTsumohai,0);
		if(ret == MJPIR_TSUMO){
			//AfxDebugBreak();
			m_state = MJSTATE_AGARI;
			m_iHoura++;
		}else{
			if((ret & 63) == 13){
				m_view.m_aSutehai[m_view.m_iSutehaiSize++] = m_view.m_iTsumohai;
			}else{
				m_view.m_aSutehai[m_view.m_iSutehaiSize++] = m_view.m_aTehai[ret & 63];
				m_view.m_aTehai[ret & 63] = m_view.m_iTsumohai;
			}
			qsort(m_view.m_aTehai,13,sizeof(int),(int (*)(const void*, const void*))compare_int);
			if(m_view.m_iSutehaiSize == 18){
				m_state = MJSTATE_AGARI;
				m_view.m_iTsumohai = -1;
				num = search_tenpai((int *)m_view.m_aTehai,13,(int *)p,&tlist,1,0);
				if(num > 0){
					m_iTenpai++;
				}

			}else{
				m_view.m_iTsumohai = m_aPai[m_iIndex++];
			}
		}

	}

}

void CMahjongAITestGUIDlg::prevPai()
{
	int i;
	if(m_state != MJSTATE_AGARI && m_iIndex > 15){
		m_iIndex--;
		m_view.m_iSutehaiSize--;
		m_view.m_iTsumohai = m_aPai[m_iIndex-1];

		for(i=0;i<13;i++){
			if(m_view.m_aTehai[i] == m_view.m_iTsumohai){
				m_view.m_aTehai[i] = m_view.m_aSutehai[m_view.m_iSutehaiSize];
				break;
			}
		}
		qsort(m_view.m_aTehai,13,sizeof(int),(int (*)(const void*, const void*))compare_int);
	}

}

void CMahjongAITestGUIDlg::OnDestroy() 
{
	CDialog::OnDestroy();
	
	m_func(m_inst,MJPI_ENDGAME,0,0);
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����Ă�������
	if(m_inst) free(m_inst);
	if(m_comp) ::FreeLibrary(m_comp);
	
}

void CMahjongAITestGUIDlg::OnTimer(UINT nIDEvent) 
{
	// TODO: ���̈ʒu�Ƀ��b�Z�[�W �n���h���p�̃R�[�h��ǉ����邩�܂��̓f�t�H���g�̏������Ăяo���Ă�������
	UINT dbg;

	dbg = m_func(m_inst,MJPI_DEBUG,0,0);

	m_strDebug.Format("%u",dbg);

	UpdateData(FALSE);
	
	CDialog::OnTimer(nIDEvent);
}


LRESULT CMahjongAITestGUIDlg::OnRefresh(WPARAM wParam,LPARAM lParam)
{
	UpdateData(TRUE);

	if(wParam){
		m_btnPrev.EnableWindow(TRUE);
		m_btnNext.EnableWindow(TRUE);
	}

	m_strKyoku.Format("%d",m_iKyoku);
	m_strHoura.Format("%d",m_iHoura);
	m_strTenpai.Format("%d",m_iTenpai);
	m_strHoura2.Format("%d",m_iHoura2);
	if(m_iKyoku > 0){
		m_strTenpaiR.Format("(%02.1f%%)",(m_iTenpai + m_iHoura)* 100.0 / (double)m_iKyoku);
		m_strHouraR.Format("(%02.1f%%)",m_iHoura * 100.0 / (double)m_iKyoku);
		m_strHouraR2.Format("(%02.1f%%)",m_iHoura2 * 100.0 / (double)m_iKyoku);
	}


	Invalidate(FALSE);

	UpdateData(FALSE);

	return 0;
}

void CMahjongAITestGUIDlg::OnBtnwait() 
{
	UpdateData(TRUE);
	m_iWait = strtol((LPCTSTR)m_strWait,NULL,0);

	UpdateData(FALSE);	
}

void CMahjongAITestGUIDlg::OnAi() 
{
	CString sPathName;
	CFileDialog dlg(TRUE,
		NULL,
		"*.dll",
		OFN_FILEMUSTEXIST,
		"AI DLL | *.dll | �S�Ă�̧��(*.*) | *.*||",
		this);

	if(dlg.DoModal() != IDOK){
		return;
	}

	sPathName = dlg.GetPathName();

	if(m_comp){
		::FreeLibrary(m_comp);
	}

	m_comp = ::LoadLibrary(sPathName);
	if(m_comp == NULL){
		AfxMessageBox("Cannot load Library.");
		return;
	}

	m_func = (MJPIFunc)::GetProcAddress(m_comp,"MJPInterfaceFunc");

	if(m_func == NULL){
		AfxMessageBox("Cannot load Library.");
		return;
	}

	aiInit();

	
}

void CMahjongAITestGUIDlg::OnBtnseek() 
{
	UpdateData(TRUE);

	int seek = (int)strtol((LPCTSTR)m_strSeek,NULL,0);

	FILE *fp;
	bool failed = true;

	if((fp = fopen((LPCTSTR)m_strDumpFile,"rb")) != NULL){
		if(fseek(fp,136*seek,SEEK_SET) == 0){
			if(fread(&m_aPai,136,1,fp) > 0){
				failed = false;
				newKyoku(false);
			}
		}
	}

	if(failed){
		AfxMessageBox("�t�@�C���ǂݍ��݂Ɏ��s���܂���");
	}
	
}

void CMahjongAITestGUIDlg::OnBtnrddump() 
{
	CString sPathName;
	CFileDialog dlg(TRUE,
		NULL,
		"*.*",
		OFN_FILEMUSTEXIST,
		"�S�Ă�̧��(*.*) | *.*||",
		this);

	if(dlg.DoModal() != IDOK){
		return;
	}

	m_strDumpFile = dlg.GetPathName();
	
}