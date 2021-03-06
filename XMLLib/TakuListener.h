﻿#ifndef TAKULISTENER_H
#define TAKULISTENER_H
#include "Taku.h"
#include "Member.h"
#include "Pai.h"
#include "NakiMentsu.h"

class OMTakuListener
{
public:
    OMTakuListener();
    virtual void tehaiAdded(OMTaku *taku,int memberIndex,OMMember *member,int paiIndex,OMPai pai,bool tsumo);
    virtual void tehaiRemoved(OMTaku *taku,int memberIndex,OMMember *member,int paiIndex,OMPai pai,bool tsumo);
    virtual void dahaiAdded(OMTaku *taku,int memberIndex,OMMember *member,int paiIndex,OMPai pai);
    virtual void dahaiNaki(OMTaku *taku,int memberIndex,OMMember *member,int paiIndex,OMPai pai);
    virtual void nakiAdded(OMTaku *taku,int memberIndex,OMMember *member,int mentsuIndex,OMNakiMentsu mentsu,bool kuwae);
    virtual void nakiRemoved(OMTaku *taku,int memberIndex,OMMember *member,int mentsuIndex,OMNakiMentsu mentsu);
};

#endif // TAKULISTENER_H
