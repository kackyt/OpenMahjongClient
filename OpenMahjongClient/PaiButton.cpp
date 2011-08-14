#include <QPainter>
#include "PaiButton.h"

OMPaiButton::OMPaiButton(QWidget *parent) :
    QPushButton(parent)
{
    setPai(m_pai,0);
    QObject::connect(this,SIGNAL(clicked()),this,SLOT(clickPai()));
}

void OMPaiButton::toPaiString(OMPai &pai, QString &str)
{
    UINT num;
    static const char *haigaNameTbl[] = {
        "ton","nan","sha","pei","haku","hatu","tyun","ura"
    };

    num = (UINT)pai;
    if(m_rule.m_iAka == 1) {
        if(pai.m_iCategory != PAI_ZIHAI && pai.m_iNo == 5 && pai.m_iId == 4) {
            num += 35;
        }
    }else if(m_rule.m_iAka == 2) {
        if(pai.m_iCategory != PAI_ZIHAI && pai.m_iNo == 5 && pai.m_iId == 4) {
            num += 35;
        }else if(pai.m_iCategory == PAI_PINZU && pai.m_iNo == 5 && pai.m_iId == 3) {
            num += 35;
        }

    }else if(m_rule.m_iAka == 3) {
        if(pai.m_iId == 4){
            num += 35;
        }
    }

    if(num < 9) {
        str.sprintf("man%d",num + 1);
    }else if(num < 18) {
        str.sprintf("pin%d",(num % 9) + 1);
    }else if(num < 27) {
        str.sprintf("sou%d",(num % 9) + 1);
    }else if(num < 35) {
        str.sprintf("%s",haigaNameTbl[(num % 9)]);
    }else if(num < 44) {
        str.sprintf("manred%d",((num - 35) % 9) + 1);
    }else if(num < 53) {
        str.sprintf("pinred%d",((num - 35) % 9) + 1);
    }else if(num < 62) {
        str.sprintf("soured%d",((num - 35) % 9) + 1);
    }else if(num < 68) {
        str.sprintf("%sred",haigaNameTbl[(num - 35) % 9]);
    }else{
        str = "tyun";
    }


}

void OMPaiButton::setPai(OMPai &pai, int rotate)
{
    QString filepath;
    QString hainame;
    m_pai = pai;
    m_rotate = rotate;

    toPaiString(pai,hainame);

    /* 回転した画像を取得する */
    switch(rotate){
    case 0:
        filepath = QString(":/haiga/%1.gif").arg(hainame);
        resize(24,34);
        break;
    case 1:
        filepath = QString(":/haiga/y%1.gif").arg(hainame);
        resize(32,24);
        break;
    case 2:
        filepath = QString(":/haiga/t%1.gif").arg(hainame);
        resize(24,34);
        break;
    case 3:
    default:
        filepath = QString(":/haiga/ty%1.gif").arg(hainame);
        resize(32,24);
        break;
    }

    m_image = QImage(filepath);

    if(m_rule.m_iGlasshai != FALSE && (UINT)pai != PAI_NIL && pai.m_iId != 4) {
        setWindowOpacity(0.5);
    }
}

void OMPaiButton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;

    pen.setWidth(5);
    pen.setBrush(Qt::red);

    painter.drawImage(0,0,m_image);

    if(isChecked()) {
        /* チェックされていた場合は赤枠で囲む */
        painter.setPen(pen);
        painter.drawRect(0,0,width(),height());
    }
}

void OMPaiButton::clickPai()
{
    emit selectPai(m_pai);
}
