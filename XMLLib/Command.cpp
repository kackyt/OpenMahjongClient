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
// Command.cpp: CCommand �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Command.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#pragma warning(disable:4786)

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

OMCommand::OMCommand()
{
	m_iId = 0;
	m_iType = 0;

}

OMCommand::~OMCommand()
{

}

void OMCommand::parseXML(OMDomNode pElem)
{
    OMDomNode pNode;

    /* �X�J���[�f�[�^�̊i�[ */

    pNode = OMGetElement(pElem,_T(TAG_ID));

    OMToNum(pNode,m_iId);

    pNode = OMGetElement(pElem,_T(TAG_TYPE));

    OMToNum(pNode,m_iType);

    pNode = OMGetElement(pElem,_T(TAG_PAI));

    if(!OMIsNull(pNode)){
        m_pai.parseXML(pNode);
    }

    pNode = OMGetElement(pElem,_T(TAG_PLAYER));

    if(!OMIsNull(pNode)){
        m_player.parseXML(pNode);
    }

    pNode = OMGetElement(pElem,_T(TAG_NAKIMENTSU));

    if(!OMIsNull(pNode)){
        m_mentsu.parseXML(pNode);
    }else{
        pNode = OMGetElement(pElem,_T(TAG_MENTSU));

        if(!OMIsNull(pNode)){
            m_mentsu.parseXML(pNode);
        }
    }

    pNode = OMGetElement(pElem,_T(TAG_RULE));

    if(!OMIsNull(pNode)){
        m_rule.parseXML(pNode);
    }

}

#ifdef _MSC_VER
OMCommand& OMCommand::operator=(OMCommand& value)
#else
OMCommand& OMCommand::operator=(const OMCommand& value)
#endif
{
    m_iId = value.m_iId;
    m_iType = value.m_iType;
    m_mentsu = value.m_mentsu;
    m_pai = value.m_pai;
    m_player = value.m_player;

    return *this;
}

void OMCommand::toXML(OMDomDocument pDoc,OMDomElement pParent)
{
    OMDomElement pElemCom,pElemID;
    OMDomNode pTxtNode;
    OMString str;

    pElemCom = OMCreateElement(pDoc,_T(TAG_COMMAND));
    OMAppendChild(pParent,pElemCom);
    pElemID = OMCreateElement(pDoc,_T(TAG_ID));
    OMAppendChild(pElemCom,pElemID);

    OMNumToStr(str,m_iId);

    pTxtNode = OMCreateTextNode(pDoc,str);
    OMAppendChild(pElemID,pTxtNode);

    m_player.toXML(pDoc,pElemCom);

    if(m_rule.m_bActive){
        m_rule.toXML(pDoc,pElemCom);
    }
}
