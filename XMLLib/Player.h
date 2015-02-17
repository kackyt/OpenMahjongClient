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
// Player.h: CPlayer �N���X�̃C���^�[�t�F�C�X
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_PLAYER_H__521B1B37_B5BC_4B85_A9EC_F41883A29BE7__INCLUDED_)
#define AFX_PLAYER_H__521B1B37_B5BC_4B85_A9EC_F41883A29BE7__INCLUDED_
#include "OMXMLCommon.h"
#include "MIPIface.h"

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class OMTaku;
class OMCommand;

typedef struct
{
    int m_iType;
    int m_iIndex1;
    int m_iIndex2;
    int m_iKaze1;
    int m_iKaze2;
} OMPlayerActionParam;


class OMPlayer
{
public:
    static const UINT ieTable[][4];
    int m_iPrivateId;
    void toXML(OMDomDocument,OMDomElement);
    void parseXML(OMDomNode);
    UINT onPlayerAction(OMTaku *,OMPlayerActionParam&);
    UINT onSutehai(OMTaku *,OMCommand&);

    void setCommand(UINT,OMTaku *,OMCommand&);

    MJPIFunc m_pFunc;
    void* m_pInst;
    BOOL m_bIsComp;
    OMString m_strName;
    int m_iId;
    int m_iStructMode;
    OMPlayer();
    virtual ~OMPlayer();

};

#endif // !defined(AFX_PLAYER_H__521B1B37_B5BC_4B85_A9EC_F41883A29BE7__INCLUDED_)
