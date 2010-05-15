// OpenMahjongClientDbgDlg.h : �w�b�_�[ �t�@�C��
//

#if !defined(AFX_OPENMAHJONGCLIENTDBGDLG_H__F00E9E9C_E252_4199_B645_8A686A31936A__INCLUDED_)
#define AFX_OPENMAHJONGCLIENTDBGDLG_H__F00E9E9C_E252_4199_B645_8A686A31936A__INCLUDED_

#include "AgariDialog.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include <afxmt.h>
#include "Taku.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "ConnectDlg.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "Player.h"
#include "MIPIface.h"
#include "MahjongStatic.h"
#include "MahjongBtn.h"
#include "MyButton.h"
#include "Library.h"
#include "Message.h"
#include "DebugDialog.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "MessageEdit.h"
#include "WavePlayer.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "WavePlayMatrix.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "WaveFilePlayMethod.h"	// ClassView �ɂ���Ēǉ�����܂����B
#include "Rule.h"	// ClassView �ɂ���Ēǉ�����܂����B

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#define COMP_MAX (256)

/////////////////////////////////////////////////////////////////////////////
// COpenMahjongClientDbgDlg �_�C�A���O

class COpenMahjongClientDbgDlg : public CDialog
{
// �\�z
public:
	CRule m_rule;
	CWaveFilePlayMethod m_fileNormal;
	CWaveFilePlayMethod m_fileCommand;
	CWavePlayMatrix m_matrix;
	CWavePlayer m_player;
	BOOL m_bFirst;
	void sendCommand(CArray<CCommand,CCommand&>&,CString&);
	void queueMessage(CMessage&);
	CWinThread * m_pWorkThread;
	int m_iCurState;
	void resetPlayer();
	int m_iAgari;
	CAgariDialog m_agariDlg;
	CDebugDialog m_debugDlg;
	CMutex m_queMutex;
	CArray<CMessage,CMessage&> m_aMessageQueue;
	void appendMessageText(CString&);
	int m_iPlayerIndex;
	int m_iSelType;
	void sendLibrary(CLibrary&);
	int m_iSyncTick;
	void sendString(CString&,CString&);
	BOOL m_bBusy;
	LRESULT OnSndCommand(WPARAM,LPARAM);
	LRESULT OnRefresh(WPARAM,LPARAM);
	int m_iLogicNum;
	int m_iSession;
	int sendCommand(CCommand&,CString&);
	CPlayer * m_pCurPlayer;
	BOOL searchComp(CString&);
	void gameSync();
	CTaku *m_pCurTaku;
	CTaku m_aTakuAll[4];
	CConnectDlg m_connDlg;
	CString m_strHostURL;
	int m_iCompNum;
	int m_iPlayerNum;
	HMODULE hComp[COMP_MAX];
	MJPIFunc pFunc[COMP_MAX];
	CString compName[COMP_MAX];
	LPVOID pInst[4];
	int structMode[4];
	CPlayer m_players[4];
	COpenMahjongClientDbgDlg(CWnd* pParent = NULL);	// �W���̃R���X�g���N�^

// �_�C�A���O �f�[�^
	//{{AFX_DATA(COpenMahjongClientDbgDlg)
	enum { IDD = IDD_OPENMAHJONGCLIENTDBG_DIALOG };
	CButton	m_btnSndMes;
	CEdit	m_ctlSendText;
	CButton	m_btnConnect;
	CMessageEdit	m_messageEdit;
	CButton	m_btnSndTo3;
	CButton	m_btnSndTo2;
	CButton	m_btnSndTo1;
	CButton	m_btnTsumo;
	CButton	m_btnTouhai;
	CButton	m_btnRon;
	CButton	m_btnRiichi;
	CButton	m_btnPon;
	CButton	m_btnPass;
	CButton	m_btnKan;
	CButton	m_btnDecide;
	CButton	m_btnTii;
	CMahjongBtn	m_btnMahjong;
	CButton	m_btnSync;
	CString	m_strCUIMessage;
	int		m_iComID;
	CString	m_strTakunum;
	CString	m_strSyncTick;
	CString	m_strSendText;
	//}}AFX_DATA

	// ClassWizard �͉��z�֐��̃I�[�o�[���C�h�𐶐����܂��B
	//{{AFX_VIRTUAL(COpenMahjongClientDbgDlg)
	public:
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV �̃T�|�[�g
	//}}AFX_VIRTUAL

// �C���v�������e�[�V����
protected:
	HICON m_hIcon;

	// �������ꂽ���b�Z�[�W �}�b�v�֐�
	//{{AFX_MSG(COpenMahjongClientDbgDlg)
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	afx_msg void OnBtnconnect();
	afx_msg void OnCmdsnd();
	afx_msg void OnBtnsync();
	afx_msg void OnBtnsyncapl();
	afx_msg void OnBtndecide();
	afx_msg void OnBtnkan();
	afx_msg void OnBtnpass();
	afx_msg void OnBtnpon();
	afx_msg void OnBtnriichi();
	afx_msg void OnBtnron();
	afx_msg void OnBtntii();
	afx_msg void OnBtntouhai();
	afx_msg void OnBtntsumo();
	afx_msg void OnSndmes();
	afx_msg void OnSndtoall();
	afx_msg void OnDestroy();
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnAbort();
	afx_msg void OnBtnrule();
	//}}AFX_MSG
	DECLARE_MESSAGE_MAP()
private:
	void resetBtnState();
};

//{{AFX_INSERT_LOCATION}}
// Microsoft Visual C++ �͑O�s�̒��O�ɒǉ��̐錾��}�����܂��B

#endif // !defined(AFX_OPENMAHJONGCLIENTDBGDLG_H__F00E9E9C_E252_4199_B645_8A686A31936A__INCLUDED_)