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
// Player.cpp: CPlayer �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Player.h"
#include "Taku.h"
#include "Command.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable:4786)

const UINT OMPlayer::ieTable[][4] = {
    { 0, 1, 2, 3},
    { 3, 0, 1, 2},
    { 2, 3, 0, 1},
    { 1, 2, 3, 0},
};


//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

OMPlayer::OMPlayer()
{
    m_iId = 0;
    m_bIsComp = FALSE;
    m_pFunc = NULL;
    m_pInst = NULL;
    m_strName = _T("");
    m_iPrivateId = 0;

}

OMPlayer::~OMPlayer()
{

}

void OMPlayer::parseXML(OMDomNode pElem)
{
    OMDomNode pNode;
    OMString pStr;

    pNode = OMGetElement(pElem,_T(TAG_ID));

    OMToNum(pNode,m_iId);

    pNode = OMGetElement(pElem,_T(TAG_NAME));

    if(!OMIsNull(pNode)){
        OMGetText(pNode,pStr);
        m_strName = OMString(pStr);
    }

    pNode = OMGetElement(pElem,_T(TAG_PRIVATEID));
    OMToNum(pNode,m_iPrivateId);
}

void OMPlayer::toXML(OMDomDocument pDoc,OMDomElement pParent)
{
    OMDomElement pElemPlayer,pElemID,pElemName;
    OMString str;
    OMDomNode pTxtNode;

    pElemPlayer = OMCreateElement(pDoc,_T(TAG_PLAYER));

    pElemID = OMCreateElement(pDoc,_T(TAG_ID));
    str.Format(_T("%d"),m_iId);
    pTxtNode = OMCreateTextNode(pDoc,str);
    OMAppendChild(pElemID,pTxtNode);
    OMAppendChild(pElemPlayer,pElemID);

    pElemName = OMCreateElement(pDoc,_T(TAG_NAME));
    pTxtNode = OMCreateTextNode(pDoc,m_strName);
    OMAppendChild(pElemName,pTxtNode);
    OMAppendChild(pElemPlayer,pElemName);

    pElemID = OMCreateElement(pDoc,_T(TAG_PRIVATEID));
    str.Format(_T("%d"),m_iPrivateId);
    pTxtNode = OMCreateTextNode(pDoc,str);
    OMAppendChild(pElemID,pTxtNode);
    OMAppendChild(pElemPlayer,pElemID);

    OMAppendChild(pParent,pElemPlayer);

}

/* �R���s���[�^�̃A�N�V�������v�Z */
UINT OMPlayer::onPlayerAction(OMTaku *pTaku, OMPlayerActionParam &param)
{
    UINT ret = 0;
    int i;
    int ind = pTaku->getMemberIndex(this);
    bool bAction = false;
    int kaze3;
    LONG pointdiff[4] = { 0 };
    int ieparam;

    switch(param.m_iType){
    case TYPE_TII:
    case TYPE_PON:
    case TYPE_RON:
    case TYPE_DAIMINKAN:
        /* ����̂���A�N�V���� */
        kaze3 = pTaku->m_members[pTaku->m_event.m_command.m_mentsu.m_iAite].m_gamestate.m_iZikaze - 1;
        ieparam = (ieTable[param.m_iKaze1][kaze3] << 16) | ieTable[param.m_iKaze1][param.m_iKaze2];
        break;
    default:
        /* ����̂Ȃ��A�N�V���� */
        ieparam = ieTable[param.m_iKaze1][param.m_iKaze2];
        break;
    }


    switch(param.m_iType){
    case TYPE_KOUHAI:
        m_pFunc(m_pInst,MJPI_ENDKYOKU,MJEK_RYUKYOKU,(UINT)pointdiff);
        break;
    case TYPE_START:
        m_pFunc(m_pInst,MJPI_STARTKYOKU,pTaku->m_iKyokuCount,pTaku->m_members[ind].m_gamestate.m_iZikaze - 1);
        break;
    case TYPE_DAHAI:
        bAction = true;
        ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_SUTEHAI | (UINT)pTaku->m_event.m_command.m_pai);
        break;
    case TYPE_TII:
        switch(pTaku->m_event.m_command.m_mentsu.getNakiPos()){
        case 0:
            ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_CHII1 | (UINT)pTaku->m_event.m_command.m_pai);
            break;
        case 1:
            ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_CHII2 | (UINT)pTaku->m_event.m_command.m_pai);
            break;
        case 2:
            ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_CHII3 | (UINT)pTaku->m_event.m_command.m_pai);
        default:
            break;
        }

        break;
    case TYPE_PON:
        ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_PON | (UINT)pTaku->m_event.m_command.m_pai);
        break;
    case TYPE_RON:
        ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_RON | (UINT)pTaku->m_event.m_command.m_pai);
        pointdiff[ieTable[param.m_iKaze1][kaze3]] = -(pTaku->m_event.m_result.m_iScore + pTaku->m_iTsumibou * 300);
        pointdiff[ieTable[param.m_iKaze1][param.m_iKaze2]] = (pTaku->m_event.m_result.m_iScore + pTaku->m_iTsumibou * 300 + pTaku->m_iRiichibou * 1000);
        m_pFunc(m_pInst,MJPI_ENDKYOKU,MJEK_AGARI,(UINT)pointdiff);
        break;
    case TYPE_TSUMO:
        ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_TSUMO | (UINT)pTaku->m_event.m_command.m_pai);
        if(param.m_iKaze2 == 0){
            /* �e�̃c���A�K�� */
            for(i=0;i<4;i++){
                if(i==(int)ieparam){
                    pointdiff[i] = (pTaku->m_event.m_result.m_iKoScore + pTaku->m_iTsumibou * 100) * 3 + pTaku->m_iRiichibou * 1000;
                }else{
                    pointdiff[i] = -(pTaku->m_event.m_result.m_iKoScore + pTaku->m_iTsumibou * 100);
                }
            }
        }else{
            /* �q�̃c���A�K�� */
            for(i=0;i<4;i++){
                if(i==(int)ieparam){
                    pointdiff[i] = (pTaku->m_event.m_result.m_iKoScore + pTaku->m_iTsumibou * 100) * 2 + (pTaku->m_event.m_result.m_iOyaScore + pTaku->m_iTsumibou * 100) + pTaku->m_iRiichibou * 1000;
                }else if((param.m_iKaze1 + i) % 4 == 0){
                    pointdiff[i] = -(pTaku->m_event.m_result.m_iOyaScore + pTaku->m_iTsumibou * 100);
                }else{
                    pointdiff[i] = -(pTaku->m_event.m_result.m_iKoScore + pTaku->m_iTsumibou * 100);
                }
            }
        }
        m_pFunc(m_pInst,MJPI_ENDKYOKU,MJEK_AGARI,(UINT)pointdiff);
        break;
    case TYPE_RIICHI:
        bAction = true;
        ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_REACH | (UINT)pTaku->m_event.m_command.m_pai);
        break;
    case TYPE_ANKAN:
        ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_ANKAN | (UINT)pTaku->m_event.m_command.m_pai);
        break;
    case TYPE_KUWAEKAN:
        ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_MINKAN | (UINT)pTaku->m_event.m_command.m_pai);
        break;
    case TYPE_DAIMINKAN:
        ret = m_pFunc(m_pInst,MJPI_ONACTION,ieparam,MJPIR_MINKAN | (UINT)pTaku->m_event.m_command.m_pai);
        break;
    default:
        break;
    }


    return ret;

}

void OMPlayer::setCommand(UINT id,OMTaku *pTaku, OMCommand &command)
{
    int i;
    int ind = pTaku->getMemberIndex(this);
    switch(id & 0xFFFFFF00){
    case MJPIR_CHII1:
        for(i=0;i<pTaku->m_members[ind].m_aCommandList.size();i++){
            if(pTaku->m_members[ind].m_aCommandList[i].m_mentsu.getNakiPos() == 0){
                command.m_iId = pTaku->m_members[ind].m_aCommandList[i].m_iId;
                break;
            }
        }
        break;
    case MJPIR_CHII2:
        for(i=0;i<pTaku->m_members[ind].m_aCommandList.size();i++){
            if(pTaku->m_members[ind].m_aCommandList[i].m_mentsu.getNakiPos() == 2){
                command.m_iId = pTaku->m_members[ind].m_aCommandList[i].m_iId;
                break;
            }
        }
        break;
    case MJPIR_CHII3:
        for(i=0;i<pTaku->m_members[ind].m_aCommandList.size();i++){
            if(pTaku->m_members[ind].m_aCommandList[i].m_mentsu.getNakiPos() == 1){
                command.m_iId = pTaku->m_members[ind].m_aCommandList[i].m_iId;
                break;
            }
        }
        break;
    case MJPIR_PON:
        command.m_iId = ID_PON;
        break;
    case MJPIR_KAN:
        command.m_iId = ID_DAIMINKAN;
        break;
    case MJPIR_RON:
        command.m_iId = ID_RON;
        break;
    default:
        command.m_iId = ID_PASS;
        break;
    }
}

UINT OMPlayer::onSutehai(OMTaku *pTaku, OMCommand &command)
{
    UINT ret = 0;
    int ind = pTaku->getMemberIndex(this);
    UINT paiID;
    int i;
    if(pTaku->m_members[ind].m_gamestate.m_bTsumo){
        paiID = pTaku->m_members[ind].m_aTehai[pTaku->m_members[ind].m_aTehai.size()-1];
    }else{
        paiID = 63;
    }

    ret = m_pFunc(m_pInst,MJPI_SUTEHAI,(UINT)paiID,0);
    switch(ret & 0xFFFFFF00){
    case MJPIR_SUTEHAI:
            if((ret & 0xFF) == 13){
                    command.m_iId = ID_DAHAI + pTaku->m_members[pTaku->m_iTurn].m_aTehai.size() -1;
            }else{
                    command.m_iId = ID_DAHAI + (ret & 0xFF);
            }
            break;
    case MJPIR_REACH:
            command.m_iId = ID_RIICHI + (ret & 0xFF);
            if(!pTaku->m_members[ind].isExecutableCommand(command)){
                    command.m_iId = ID_DAHAI + (ret & 0xFF);
            }
            break;
    case MJPIR_TSUMO:
            command.m_iId = ID_TSUMO;
            if(!pTaku->m_members[ind].isExecutableCommand(command)){
                    AfxDebugBreak();
                    command.m_iId = ID_DAHAI + pTaku->m_members[pTaku->m_iTurn].m_aTehai.size() -1;
            }
            break;
    case MJPIR_NAGASHI:
            command.m_iId = ID_TOUHAI;
            if(!pTaku->m_members[ind].isExecutableCommand(command)){
                    AfxDebugBreak();
                    command.m_iId = ID_DAHAI + pTaku->m_members[pTaku->m_iTurn].m_aTehai.size() -1;
            }
            break;
    case MJPIR_KAN:
            command.m_iId = ID_DAHAI + pTaku->m_members[pTaku->m_iTurn].m_aTehai.size() -1;
            if((ret & 0xFF) < pTaku->m_members[ind].m_aTehai.size()){
                    OMPai pai = pTaku->m_members[ind].m_aTehai[ret & 0xFF];
                    for(i=0;i<pTaku->m_members[ind].m_aCommandList.size();i++){
                            if(((UINT)pTaku->m_members[ind].m_aCommandList[i].m_pai & 63) == ((UINT)pai & 63) && (pTaku->m_members[ind].m_aCommandList[i].m_iType == TYPE_ANKAN || pTaku->m_members[ind].m_aCommandList[i].m_iType == TYPE_KUWAEKAN)){
                                    command.m_iId = pTaku->m_members[ind].m_aCommandList[i].m_iId;
                            }
                    }
            }

            break;
    default:
            command.m_iId = ID_DAHAI + pTaku->m_members[pTaku->m_iTurn].m_aTehai.size() -1;
            break;
    }

    return ret;
}
