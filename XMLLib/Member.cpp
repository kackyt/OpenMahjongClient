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
// Member.cpp: CMember �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Member.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

OMMember::OMMember()
{

}

OMMember::~OMMember()
{

}

void OMMember::parseXML(OMDomNode pElem)
{
        OMDomNode pNode;
        OMDomNodeList pNodeList;
	int i;

	/* �X�J���[�f�[�^�̊i�[ */

        pNode = OMGetElement(pElem,_T(TAG_MSTATE));

        OMToNum(pNode,m_iState);

        pNode = OMGetElement(pElem,_T(TAG_POINT));

        OMToNum(pNode,m_iPoint);

	/* �Ŕv�̊i�[ */
        m_aDahai.clear();
        pNodeList = OMGetElementList(pElem,_T(TAG_DAHAI "/"  TAG_PAI));

        if(!OMIsEmpty(pNodeList)){
            for(i=0;i<OMListLength(pNodeList);i++){
                        OMPai pai;
                        pNode = OMListItem(pNodeList,i);
                        pai.parseXML(pNode);
                        m_aDahai.append(pai);
		}
	}

	/* ��v�̊i�[ */
        m_aTehai.clear();
        pNodeList = OMGetElementList(pElem,_T(TAG_TEHAI "/" TAG_PAI));

        if(!OMIsEmpty(pNodeList)){
            for(i=0;i<OMListLength(pNodeList);i++){
                        OMPai pai;
                        pNode = OMListItem(pNodeList,i);
                        pai.parseXML(pNode);
                        m_aTehai.append(pai);
		}
	}

	/* �R�}���h���X�g�̊i�[ */
        m_aCommandList.clear();
        pNodeList = OMGetElementList(pElem,_T(TAG_COMMANDLIST "/" TAG_COMMAND));

        if(!OMIsEmpty(pNodeList)){
            for(i=0;i<OMListLength(pNodeList);i++){
                        OMCommand com;
                        pNode = OMListItem(pNodeList,i);
                        com.parseXML(pNode);
                        m_aCommandList.append(com);
		}
	}

	/* �c���v�̊i�[ */
        pNode = OMGetElement(pElem,_T(TAG_TSUMOHAI));

        if(!OMIsNull(pNode)){
		m_gamestate.m_bTsumo = TRUE;
                pNode = OMGetElement(pElem,_T(TAG_TSUMOHAI "/" TAG_PAI));
                if(!OMIsNull(pNode)){
			m_tsumohai.parseXML(pNode);
		}
	}else{
		m_gamestate.m_bTsumo = FALSE;
	}


	/* �v���[���[�̊i�[ */

        pNode = OMGetElement(pElem,_T(TAG_PLAYER));

        if(!OMIsNull(pNode)){
		m_player.parseXML(pNode);
	}

	/* �Q�[����Ԃ̊i�[ */
        pNode = OMGetElement(pElem,_T(TAG_GAMESTATE));

        if(!OMIsNull(pNode)){
		m_gamestate.parseXML(pNode);
	}

	/* ������̊i�[ */
        m_aResultList.clear();
        pNodeList = OMGetElementList(pElem,_T(TAG_RESULTLIST "/" TAG_RESULT));

        if(!OMIsEmpty(pNodeList)){
            for(i=0;i<OMListLength(pNodeList);i++){
                        OMResult res;
                        pNode = OMListItem(pNodeList,i);
                        res.parseXML(pNode);
                        m_aResultList.append(res);
		}
	}

}

BOOL OMMember::isExecutableCommand(OMCommand& command)
{
	int i;

        for(i=0;i<m_aCommandList.size();i++){
		if(m_aCommandList[i].m_iId == command.m_iId){
			return TRUE;
		}
	}

	return FALSE;
}

OMMember& OMMember::operator =(OMMember& value)
{
	int i;
        m_aCommandList.clear();
        for(i=0;i<value.m_aCommandList.size();i++){
                m_aCommandList.append(value.m_aCommandList[i]);
	}
        m_aDahai.copy(value.m_aDahai);
        m_aResultList.clear();
        for(i=0;i<value.m_aResultList.size();i++){
                m_aResultList.append(value.m_aResultList[i]);
	}
        m_aTehai.copy(value.m_aTehai);
	m_gamestate = value.m_gamestate;
	m_iPoint = value.m_iPoint;
	m_iState = value.m_iState;
	m_player = value.m_player;

	return *this;
}

/* ���ꂼ��̉Ƃ̋�����Ԃ�
  0 - ���g
  1 - ����
  2 - �Ζ�
  3 - ���
  */
int OMMember::getChaDistance(int x, int y)
{
    return (y - x + 4) % 4;
}

int OMMember::getDahaiRealPos(OMPai &pai)
{
    int pos = 0;
    int i;
    bool matched = false;

    for(i=0;i<m_aDahai.size();i++){
        if(m_aDahai[i].match(pai)){
            matched = true;
            break;
        }else if(!m_aDahai[i].m_bNaki){
            pos++;
        }
    }

    return matched ? pos : -1;
}
