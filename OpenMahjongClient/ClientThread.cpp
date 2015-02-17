#include <QThreadPool>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include "ClientThread.h"
#include "common/IllegalStateException.h"
#include "common/ConnectionException.h"

OMClientThread::OMClientThread(QObject *parent) :
    QThread(parent),
    m_clientState(OM_CLIENT_STATE_STOP)
{
}

/* Client Thread */
void OMClientThread::run()
{
    QNetworkAccessManager manager;
    QNetworkRequest request;
    request.setUrl(m_dstUrl);

    m_pReply = manager.post(request,m_sendString.toLocal8Bit());

    /* ��M�X���b�g�̓o�^ */
    QObject::connect(m_pReply,SIGNAL(readyRead()),SLOT(readProgress()),Qt::DirectConnection);
    QObject::connect(m_pReply,SIGNAL(error(QNetworkReply::NetworkError)),SLOT(error(QNetworkReply::NetworkError)),Qt::DirectConnection);
    QObject::connect(m_pReply,SIGNAL(finished()),SLOT(finish()),Qt::DirectConnection);
    //QObject::connect(this,SIGNAL(finished()),SLOT(deleteLater()));

    /* �C�x���g���[�v�ɓ��� */
    exec();
}

void OMClientThread::sendString(QUrl &dst, QString &sendString, QString &recvString)
{
    bool enableSend;
    bool sendCondition;
    QString errMessage;

    m_mutex.lock();
    if(m_clientState != OM_CLIENT_STATE_STARTED){
        m_clientState = OM_CLIENT_STATE_STARTED;
        enableSend = true;
    }else{
        enableSend = false;
    }
    m_mutex.unlock();

    if(!enableSend){
        /* 2�ȏ�̃��N�G�X�g�𑗂邱�Ƃ͂ł��Ȃ����ߗ�O�𔭐� */
        errMessage = QString("Client cannot send multiple request.");
        throw OMIllegalStateException(errMessage);
    }


    m_sendString = sendString;
    m_dstUrl = dst;

    start();

    /* ���M������҂� */
    m_mutex.lock();
    m_wait.wait(&m_mutex);
    if(m_clientState == OM_CLIENT_STATE_ERROR){
        sendCondition = false;
    }else{
        sendCondition = true;
    }
    m_clientState = OM_CLIENT_STATE_STOP;
    m_mutex.unlock();

    if(!sendCondition){
        /* �G���[�̔��� */
        errMessage = QString("Connection error occured.");
        throw OMConnectionException(errMessage);
    }

    recvString = QString::fromLocal8Bit(m_recvBuf.constData());

    m_recvBuf.clear();

}

void OMClientThread::readProgress()
{
    m_recvBuf += m_pReply->readAll();
}

void OMClientThread::error(QNetworkReply::NetworkError errCode)
{
    if(errCode != QNetworkReply::NoError){
        m_clientState = OM_CLIENT_STATE_ERROR;
    }
}

void OMClientThread::finish()
{
    m_wait.wakeAll();
    /* �X���b�h�̏I�� */
    quit();
}
