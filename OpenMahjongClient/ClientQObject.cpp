#include <QDebug>
#include <QApplication>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QMessageBox>
#include "ClientQObject.h"
#include "ClientThread.h"
#include "FilePath.h"

static OMClientQObject *thisObj;

static UINT WINAPI MJSendMessageAPI(LPVOID inst,UINT message,UINT param1,UINT param2)
{
    return thisObj->MJSendMessage(inst,message,param1,param2);
}

static const char *keywords[] = {
    QT_TRANSLATE_NOOP("OpenMahjong", "��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�k"),
    QT_TRANSLATE_NOOP("OpenMahjong", "��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "����"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�f����"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�ʔv"),
    QT_TRANSLATE_NOOP("OpenMahjong", "��O������"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�ꔭ"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�C��̌�"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�͒ꝝ��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "���J��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "���a"),
    QT_TRANSLATE_NOOP("OpenMahjong", "����"),
    QT_TRANSLATE_NOOP("OpenMahjong", "��u��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�h��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "���Ύq"),
    QT_TRANSLATE_NOOP("OpenMahjong", "���S�ь�"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�O�F����"),
    QT_TRANSLATE_NOOP("OpenMahjong", "��C�ʊ�"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�΁X�a"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�O�Í�"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�_�u������"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�O�F����"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�O�Ȏq"),
    QT_TRANSLATE_NOOP("OpenMahjong", "���S�ь�"),
    QT_TRANSLATE_NOOP("OpenMahjong", "��u��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "���V��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "���O��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "����F"),
    QT_TRANSLATE_NOOP("OpenMahjong", "����F"),
    QT_TRANSLATE_NOOP("OpenMahjong", "���m���o"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�l�Í�"),
    QT_TRANSLATE_NOOP("OpenMahjong", "��O��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "���l��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "��l��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "����F"),
    QT_TRANSLATE_NOOP("OpenMahjong", "���V��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�Έ�F"),
    QT_TRANSLATE_NOOP("OpenMahjong", "��@��"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�l�Ȏq"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�V�a"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�n�a"),
    QT_TRANSLATE_NOOP("OpenMahjong", "�l�a")
};


OMClientQObject::OMClientQObject(QObject *parent) :
    QObject(parent),
    m_pTimer(NULL),
    m_iSyncInterval(1000),
    m_bMyTurnSync(true)
{
    QString path = getFilePath("comp");
    QDir compDir(path);
    QFileInfoList list;
    int i;

    thisObj = this;

    /* comp�f�B���N�g���ɓ����Ă���dll��QLibrary�ɓ���� */
    compDir.setFilter(QDir::Files);

    list = compDir.entryInfoList();

    for(i=0;i<list.size();i++){
        try{
            QFileInfo info = list.at(i);

            if(QLibrary::isLibrary(info.filePath())){
                QLibrary *lib = new QLibrary(info.filePath());
                MJPIFunc func = (MJPIFunc)lib->resolve("MJPInterfaceFunc");
                if(func != NULL){
                    QTextCodec *codec = QTextCodec::codecForName("Shift-JIS");
                    OMString name = codec->toUnicode((const char*)func(NULL,MJPI_YOURNAME,0,0));
                    m_playerTemplate[name] = lib;
                }
            }

        }catch(...){

        }
    }

    setClientListener(this);
    m_aTakuAll[0].setTakuListener(this);
    moveToThread(&m_thread);
    m_thread.start();
}

OMClientQObject::~OMClientQObject()
{
    m_thread.quit();
    m_thread.wait();
}

void OMClientQObject::sendString(OMString &sendMessage, OMString &recvMessage)
{
    OMClientThread *clThread = new OMClientThread();

    try {
        clThread->sendString(m_dstUrl,sendMessage,recvMessage);
    }catch(...){

    }
}

void OMClientQObject::createCompInstance(OMPlayer &player)
{
    QLibrary *lib = m_playerTemplate[player.m_strName];
    int size;
    player.m_pFunc = (MJPIFunc)lib->resolve("MJPInterfaceFunc");
    size = player.m_pFunc(NULL,MJPI_CREATEINSTANCE,0,0);
    if(size > 0)
    {
        player.m_pInst = malloc(size);
        memset(player.m_pInst,0,size);
    }

    player.m_pFunc(player.m_pInst,MJPI_INITIALIZE,0,(UINT)MJSendMessageAPI);
}

void OMClientQObject::clientStart()
{
    QMetaObject::invokeMethod(this,"clientStartImpl");
}

void OMClientQObject::clientStop()
{
    QMetaObject::invokeMethod(this,"clientStopImpl");
}

void OMClientQObject::confirmCommand()
{
    OMCommand com;
    OMString recvMessage;
    int res;
    bool bCommand;

    bCommand = m_commander.getCommand(com);

    qDebug() << "confirmCommand" << bCommand;

    if(bCommand){
        com.m_player = m_players[0];

        do{
            res = sendCommand(com,recvMessage);
            qDebug() << "res = " << res;
        }while(res < 0);

        if(res != RESPONCE_OK){
            emit sigResponceCode(res);
        }
    }

    m_pTimer->start();
}

void OMClientQObject::setDestination(QUrl &url)
{
    m_dstUrl = url;
}

void OMClientQObject::takuUpdate()
{
    OM_SYNC_STATE state;
    int i;


    state = gameSync();

    if(state == OM_SYNC_STATE_USERCOMMAND){
        m_commander.initialize(m_pCurTaku->m_members[getPlayerIndex()]);
        if(!m_bMyTurnSync){
            m_pTimer->stop();
        }
        emit sigUserTurn(m_pCurTaku);
    }else if(state == OM_SYNC_STATE_NEXTKYOKU){
        OMString text;
        m_commander.initialize(m_pCurTaku->m_members[getPlayerIndex()]);

        text = "<font size='6'><strong>";


        if(m_pCurTaku->m_event.m_command.m_iType == TYPE_KOUHAI){
            text += tr("�r�v����");
        }else{
            OMString pt;
            for(i=0;i<m_pCurTaku->m_event.m_result.m_aYaku.size();i++){
                text += QApplication::instance()->translate("OpenMahjong",m_pCurTaku->m_event.m_result.m_aYaku[i].toLocal8Bit().constData());
                text += "<br />";
            }
            text += "<br />";

            pt = tr("%1�� %2�� %3�_").arg(m_pCurTaku->m_event.m_result.m_iHan).arg(m_pCurTaku->m_event.m_result.m_iFu).arg(m_pCurTaku->m_event.m_result.m_iScore);

            text += pt;
            text += "<br />";
        }

        text += "</strong></font>";

        clientStop();
        emit sigKyokuEnd(text,m_pCurTaku);
    }else if(state == OM_SYNC_STATE_ERROR){
        clientStop();
        emit sigDisconnected();
    }
}

void OMClientQObject::setSyncInterval(int interval)
{
    m_iSyncInterval = interval;
    if(m_pTimer != NULL){
        m_pTimer->setInterval(interval);
    }
}

void OMClientQObject::setMyTurnSync(bool sync)
{
    m_bMyTurnSync = sync;
}

void OMClientQObject::tehaiAdded(OMTaku *taku,int memberIndex,OMMember *member,int paiIndex,OMPai pai,bool tsumo)
{
    emit sigTehaiAdded(taku,memberIndex,member,paiIndex,pai,tsumo);
}

void OMClientQObject::tehaiRemoved(OMTaku *taku,int memberIndex,OMMember *member,int paiIndex,OMPai pai,bool tsumo)
{
    emit sigTehaiRemoved(taku,memberIndex,member,paiIndex,pai,tsumo);
}

void OMClientQObject::dahaiAdded(OMTaku *taku,int memberIndex,OMMember *member,int paiIndex,OMPai pai)
{
    emit sigDahaiAdded(taku,memberIndex,member,paiIndex,pai);

}

void OMClientQObject::dahaiNaki(OMTaku *taku,int memberIndex,OMMember *member,int paiIndex,OMPai pai)
{
    emit sigDahaiNaki(taku,memberIndex,member,paiIndex,pai);

}

void OMClientQObject::nakiAdded(OMTaku *taku,int memberIndex,OMMember *member,int mentsuIndex,OMNakiMentsu mentsu,bool kuwae)
{
    emit sigNakiAdded(taku,memberIndex,member,mentsuIndex,mentsu,kuwae);
}

void OMClientQObject::nakiRemoved(OMTaku *taku,int memberIndex,OMMember *member,int mentsuIndex,OMNakiMentsu mentsu)
{
    emit sigNakiRemoved(taku,memberIndex,member,mentsuIndex,mentsu);
}

void OMClientQObject::onDahai()
{
    emit sigDahai();
}

void OMClientQObject::onKan()
{
    emit sigKan();
}

void OMClientQObject::onPon()
{
    emit sigPon();
}

void OMClientQObject::onStarted(int index, OMTaku *taku)
{
    emit sigStarted(index,taku);
}

void OMClientQObject::onProgressed(int index, OMTaku *taku)
{
    emit sigProgressed(index,taku);
}

void OMClientQObject::onRiichi()
{
    emit sigRiichi();
}

void OMClientQObject::onRivalRiichi()
{
    emit sigRiichi();
}

void OMClientQObject::onRon()
{
    emit sigRon();
}

void OMClientQObject::onStatusCode(int code)
{
    emit sigStatusCode(code);
}

void OMClientQObject::onTii()
{
    emit sigTii();
}

void OMClientQObject::onTsumo()
{
    emit sigTsumo();
}

void OMClientQObject::appendMessageText(OMString *)
{

}

void OMClientQObject::clientStartImpl()
{

    if(m_commander.setStart()){
        OMCommand com;
        int res,i;
        OMString recvMessage;

        m_commander.getCommand(com);

        for(i=0;i<m_iPlayerNum+m_iCompNum;i++){
            com.m_player = m_players[i];

            do{
                res = sendCommand(com,recvMessage);
                qDebug() << "res = " << res;
            }while(res < 0);
        }
    }

    /* �^�C�}�[�̃X�^�[�g */
    gameStart();
    m_pTimer = new QTimer(this);
    QObject::connect(m_pTimer,SIGNAL(timeout()),SLOT(takuUpdate()));
    m_pTimer->setSingleShot(false);
    m_pTimer->start(m_iSyncInterval);
}

void OMClientQObject::clientStopImpl()
{
    gameStop();
    m_pTimer->stop();
}

