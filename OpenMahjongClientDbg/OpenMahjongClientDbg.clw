; CLW ファイルは MFC ClassWizard の情報を含んでいます。

[General Info]
Version=1
LastClass=CRuleDialog
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "OpenMahjongClientDbg.h"

ClassCount=11
Class1=COpenMahjongClientDbgApp
Class2=COpenMahjongClientDbgDlg

ResourceCount=6
Resource1=IDR_MAINFRAME
Class3=CMahjongWnd
Resource2=IDD_AGARI
Class4=CConnectDlg
Class5=CMahjongStatic
Class6=CMahjongBtn
Class7=CMyButton
Resource3=IDD_OPENMAHJONGCLIENTDBG_DIALOG
Class8=CDebugDialog
Class9=CMessageEdit
Resource4=IDD_CONNECT
Class10=CAgariDialog
Resource5=IDD_DEBUG
Class11=CRuleDialog
Resource6=IDD_RULE

[CLS:COpenMahjongClientDbgApp]
Type=0
HeaderFile=OpenMahjongClientDbg.h
ImplementationFile=OpenMahjongClientDbg.cpp
Filter=N

[CLS:COpenMahjongClientDbgDlg]
Type=0
HeaderFile=OpenMahjongClientDbgDlg.h
ImplementationFile=OpenMahjongClientDbgDlg.cpp
Filter=D
LastObject=IDC_SENDTEXT
BaseClass=CDialog
VirtualFilter=dWC



[DLG:IDD_OPENMAHJONGCLIENTDBG_DIALOG]
Type=1
Class=COpenMahjongClientDbgDlg
ControlCount=32
Control1=IDC_BTNSYNC,button,1342242816
Control2=IDC_BTNCONNECT,button,1342242816
Control3=IDC_BTNTII,button,1476464643
Control4=IDC_BTNPON,button,1476464643
Control5=IDC_BTNKAN,button,1476464643
Control6=IDC_BTNRON,button,1476460544
Control7=IDC_BTNTSUMO,button,1476460544
Control8=IDC_BTNRIICHI,button,1476464643
Control9=IDC_BTNPASS,button,1476460544
Control10=IDC_BTNTOUHAI,button,1476460544
Control11=IDC_STATIC,static,1342308352
Control12=IDC_COMID,edit,1350631552
Control13=IDC_CMDSND,button,1342242816
Control14=IDC_CUI,edit,1082198144
Control15=IDC_TAKUNUM,static,1342308352
Control16=IDC_BTNMAHJONG,button,1342242816
Control17=IDC_SYNCTICK,edit,1350631552
Control18=IDC_STATIC,static,1342308352
Control19=IDC_BTNSYNCAPL,button,1342242816
Control20=IDC_BTNDECIDE,button,1476460544
Control21=IDC_MESSAGE,edit,1352730692
Control22=IDC_STATIC,static,1342308352
Control23=IDC_SENDTEXT,edit,1350631552
Control24=IDC_STATIC,static,1342308352
Control25=IDC_SNDMES,button,1342242816
Control26=IDC_SNDTO1,button,1342242819
Control27=IDC_SNDTO2,button,1342242819
Control28=IDC_SNDTO3,button,1342242819
Control29=IDC_SNDTOALL,button,1342242816
Control30=IDC_STATIC,static,1342308352
Control31=IDC_ABORT,button,1342242816
Control32=IDC_BTNRULE,button,1342242816

[CLS:CMahjongWnd]
Type=0
HeaderFile=MahjongWnd.h
ImplementationFile=MahjongWnd.cpp
BaseClass=CWnd
Filter=W
VirtualFilter=WC

[DLG:IDD_CONNECT]
Type=1
Class=CConnectDlg
ControlCount=20
Control1=IDC_CONNECTDST,combobox,1344339970
Control2=IDC_RADIONEW,button,1342308361
Control3=IDC_RADIOAPPEND,button,1342177289
Control4=IDC_DEBUG,button,1342177289
Control5=IDC_SESSION,edit,1350631552
Control6=IDC_PNAME,edit,1350631552
Control7=IDC_CMBCOMP1,combobox,1344339971
Control8=IDC_CMBCOMP2,combobox,1344339971
Control9=IDC_CMBCOMP3,combobox,1344339971
Control10=IDOK,button,1342242817
Control11=IDCANCEL,button,1342242816
Control12=IDC_STATIC,static,1342308352
Control13=IDC_STATIC,static,1342308352
Control14=IDC_STATIC,button,1342177287
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_BTNRULE,button,1342242816

[CLS:CConnectDlg]
Type=0
HeaderFile=ConnectDlg.h
ImplementationFile=ConnectDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_BTNRULE

[CLS:CMahjongStatic]
Type=0
HeaderFile=MahjongStatic.h
ImplementationFile=MahjongStatic.cpp
BaseClass=CStatic
Filter=W
VirtualFilter=WC
LastObject=CMahjongStatic

[CLS:CMahjongBtn]
Type=0
HeaderFile=MahjongBtn.h
ImplementationFile=MahjongBtn.cpp
BaseClass=CButton
Filter=W
VirtualFilter=BWC
LastObject=CMahjongBtn

[CLS:CMyButton]
Type=0
HeaderFile=MyButton.h
ImplementationFile=MyButton.cpp
BaseClass=CButton
Filter=W
LastObject=CMyButton
VirtualFilter=BWC

[DLG:IDD_DEBUG]
Type=1
Class=CDebugDialog
ControlCount=40
Control1=IDC_STATIC,static,1342308352
Control2=IDC_STATIC,static,1342308352
Control3=IDC_STATIC,static,1342308352
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_RESTIMC1,static,1342308352
Control7=IDC_RESTIMC2,static,1342308352
Control8=IDC_RESTIMC3,static,1342308352
Control9=IDC_RESTIMC4,static,1342308352
Control10=IDC_RESTIMR1,static,1342308352
Control11=IDC_RESTIMR2,static,1342308352
Control12=IDC_RESTIMR3,static,1342308352
Control13=IDC_RESTIMR4,static,1342308352
Control14=IDC_STATIC,static,1342308352
Control15=IDC_STATIC,static,1342308352
Control16=IDC_STATIC,static,1342308352
Control17=IDC_STATIC,static,1342308352
Control18=IDC_STATIC,static,1342308352
Control19=IDC_STATIC,static,1342308352
Control20=IDC_STATIC,static,1342308352
Control21=IDC_RESCODC1,static,1342308352
Control22=IDC_RESCODC2,static,1342308352
Control23=IDC_RESCODC3,static,1342308352
Control24=IDC_RESCODC4,static,1342308352
Control25=IDC_RESCODC5,static,1342308352
Control26=IDC_RESCODC6,static,1342308352
Control27=IDC_RESCODR1,static,1342308352
Control28=IDC_RESCODR2,static,1342308352
Control29=IDC_RESCODR3,static,1342308352
Control30=IDC_RESCODR4,static,1342308352
Control31=IDC_RESCODR5,static,1342308352
Control32=IDC_RESCODR6,static,1342308352
Control33=IDC_CUI,edit,1353777348
Control34=IDC_STATIC,static,1342308352
Control35=IDC_STATIC,static,1342308352
Control36=IDC_STATIC,static,1342308352
Control37=IDC_RESTIMC5,static,1342308352
Control38=IDC_RESTIMC6,static,1342308352
Control39=IDC_RESTIMR5,static,1342308352
Control40=IDC_RESTIMR6,static,1342308352

[CLS:CDebugDialog]
Type=0
HeaderFile=DebugDialog.h
ImplementationFile=DebugDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=CDebugDialog
VirtualFilter=dWC

[CLS:CMessageEdit]
Type=0
HeaderFile=MessageEdit.h
ImplementationFile=MessageEdit.cpp
BaseClass=CEdit
Filter=W

[DLG:IDD_AGARI]
Type=1
Class=CAgariDialog
ControlCount=2
Control1=IDOK,button,1342242817
Control2=IDC_AGARIYAKU,static,1342308352

[CLS:CAgariDialog]
Type=0
HeaderFile=AgariDialog.h
ImplementationFile=AgariDialog.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC
LastObject=IDC_AGARIYAKU

[DLG:IDD_RULE]
Type=1
Class=CRuleDialog
ControlCount=12
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_CMBGLASSHAI,combobox,1344339971
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,static,1342308352
Control6=IDC_CMBKUITAN,combobox,1344339971
Control7=IDC_STATIC,static,1342308352
Control8=IDC_CMBSHANYU,combobox,1344339971
Control9=IDC_STATIC,static,1342308352
Control10=IDC_CMBSUFURENDA,combobox,1344339971
Control11=IDC_STATIC,static,1342308352
Control12=IDC_CMBAKADORA,combobox,1344339971

[CLS:CRuleDialog]
Type=0
HeaderFile=RuleDialog.h
ImplementationFile=RuleDialog.cpp
BaseClass=CDialog
Filter=D
LastObject=IDOK
VirtualFilter=dWC

