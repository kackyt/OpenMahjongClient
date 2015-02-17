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
// Taku.cpp: CTaku �N���X�̃C���v�������e�[�V����
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "Taku.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

#define GLASS_DEBUG (0)

//////////////////////////////////////////////////////////////////////
// �\�z/����
//////////////////////////////////////////////////////////////////////

OMTaku::OMTaku()
{

}

OMTaku::~OMTaku()
{

}

void OMTaku::parseXML(QDomNode pElem)
{
        QDomNode pNode;
        QDomNodeList pNodeList;
	int i;

	/* �X�J���[�f�[�^�̊i�[ */

        pNode = OM_GETELEMENT(pElem,_T(TAG_YAMA "/" TAG_COUNT));

        OM_TOLONG(pElem,m_iYama);

        pNode = OM_GETELEMENT(pElem,_T(TAG_BAKAZE));

        OM_TOLONG(pElem,m_iBakaze);

        pNode = OM_GETELEMENT(pElem,_T(TAG_KYOKUCOUNT));

        OM_TOLONG(pElem,m_iKyokuCount);

        pNode = OM_GETELEMENT(pElem,_T(TAG_RIICHIBOU));

        OM_TOLONG(pElem,m_iRiichibou);

        pNode = OM_GETELEMENT(pElem,_T(TAG_TSUMIBOU));

        OM_TOLONG(pElem,m_iTsumibou);

        pNode = OM_GETELEMENT(pElem,_T(TAG_TURN));

        OM_TOLONG(pElem,m_iTurn);

        pNode = OM_GETELEMENT(pElem,_T(TAG_EVENT));

        if(!OM_ISNULL(pNode)){
		m_event.parseXML(pNode);
	}

	/* �h���v�̊i�[ */
        m_aDora.clear();
        pNodeList = OM_GETELEMENTLIST(pElem,_T(TAG_YAKU));

        if(!OM_ISEMPTY(pNodeList)){
            for(i=0;i<OM_LISTLENGTH(pNodeList);i++){
                        OMPai pai;
                        pNode = OM_LISTITEM(pNodeList,i);
			pai.parseXML(pNode);
                        m_aDora.append(pai);
		}
	}

        m_aUradora.clear();

        pNodeList = OM_GETELEMENTLIST(pElem,_T(TAG_YAKU));

        if(!OM_ISEMPTY(pNodeList)){
            for(i=0;i<OM_LISTLENGTH(pNodeList);i++){
                        OMPai pai;
                        pNode = OM_LISTITEM(pNodeList,i);
			pai.parseXML(pNode);
                        m_aUradora.append(pai);
		}
	}

        pNodeList = OM_GETELEMENTLIST(pElem,_T(TAG_YAKU));

        if(!OM_ISEMPTY(pNodeList)){
            for(i=0;i<OM_LISTLENGTH(pNodeList);i++){
                        pNode = OM_LISTITEM(pNodeList,i);
			m_members[i].parseXML(pNode);
		}
	}


}

int OMTaku::getMemberIndex(OMPlayer *player)
{
	int i;
	if(player == NULL) return -1;

	for(i=0;i<4;i++){
		if(m_members[i].m_player.m_iId == player->m_iId){
			return i;
		}
	}

	return -1;
}
void OMTaku::getMJITehai(int index,MJITehai1 *pTehai,OMRule& rule)
{
        OMMember& member = m_members[index];
	int i,j,k;

        memset(pTehai,0,sizeof(MJITehai1));

	/* ���̂Ƃ���ԃE�[�͍l�����Ȃ� */

        if(member.m_aTehai.size() == 0){
		pTehai->tehai_max = 0;
	}else{
		if(member.m_gamestate.m_bTsumo){
                        pTehai->tehai_max = member.m_aTehai.size() - 1;
		}else{
                        pTehai->tehai_max = member.m_aTehai.size();
		}
		
		for(i=0;i<(int)pTehai->tehai_max;i++){
			pTehai->tehai[i] = member.m_aTehai[i];
			if(member.m_aTehai[i].isAka(rule)) pTehai->tehai[i] += 64;
		}
	}

	pTehai->minshun_max = 0;
	pTehai->minkou_max = 0;
	pTehai->minkan_max = 0;
	pTehai->ankan_max = 0;

        for(i=0;i<member.m_gamestate.m_aNakiList.size();i++){
                OMNakiMentsu& mentsu = member.m_gamestate.m_aNakiList[i];
		switch(mentsu.m_iCategory){
		case MENTSU_SYUNTSU:
			pTehai->minshun[pTehai->minshun_max] = mentsu.m_aPaiList[0];
			pTehai->minshun_hai[0][pTehai->minshun_max] = mentsu.m_nakihai;

			k = 1;
                        for(j=0;j<mentsu.m_aPaiList.size();j++){
				if(j != (int)mentsu.getNakiPos()){
					pTehai->minshun_hai[k++][pTehai->minshun_max] = mentsu.m_aPaiList[j];
					if(mentsu.m_aPaiList[j].isAka(rule)) pTehai->minshun_hai[k++][pTehai->minshun_max] += 64;
				}
			}
			pTehai->minshun_max++;
			break;
		case MENTSU_KOUTSU:
			pTehai->minkou[pTehai->minkou_max] = mentsu.m_aPaiList[0];
                        for(j=0;j<mentsu.m_aPaiList.size();j++){
				pTehai->minkou_hai[j][pTehai->minkou_max] = mentsu.m_aPaiList[j];
				if(mentsu.m_aPaiList[j].isAka(rule)) pTehai->minkou_hai[j][pTehai->minkou_max] += 64;
			}
			pTehai->minkou_max++;
			break;
		case MENTSU_MINKAN:
			pTehai->minkan[pTehai->minkan_max] = mentsu.m_aPaiList[0];
                        for(j=0;j<mentsu.m_aPaiList.size();j++){
				pTehai->minkan_hai[j][pTehai->minkan_max] = mentsu.m_aPaiList[j];
				if(mentsu.m_aPaiList[j].isAka(rule)) pTehai->minkan_hai[j][pTehai->minkan_max] += 64;
			}
			pTehai->minkan_max++;
			break;
		case MENTSU_ANKAN:
			pTehai->ankan[pTehai->ankan_max] = mentsu.m_aPaiList[0];
                        for(j=0;j<mentsu.m_aPaiList.size();j++){
				pTehai->ankan_hai[j][pTehai->ankan_max] = mentsu.m_aPaiList[j];
				if(mentsu.m_aPaiList[j].isAka(rule)) pTehai->ankan_hai[j][pTehai->ankan_max] += 64;
			}
			pTehai->ankan_max++;
			break;
		default:
			break;
		}

	}

}

void OMTaku::getMJITehai(int index,MJITehai *pTehai)
{
        OMMember& member = m_members[index];
	int i;

        memset(pTehai,0,sizeof(MJITehai));

	/* ���̂Ƃ���ԃE�[�͍l�����Ȃ� */

        if(member.m_aTehai.size() == 0){
		pTehai->tehai_max = 0;
	}else{
		if(member.m_gamestate.m_bTsumo){
                        pTehai->tehai_max = member.m_aTehai.size() - 1;
		}else{
                        pTehai->tehai_max = member.m_aTehai.size();
		}
		
		for(i=0;i<(int)pTehai->tehai_max;i++){
			pTehai->tehai[i] = member.m_aTehai[i];
		}
	}

	pTehai->minshun_max = 0;
	pTehai->minkou_max = 0;
	pTehai->minkan_max = 0;
	pTehai->ankan_max = 0;

        for(i=0;i<member.m_gamestate.m_aNakiList.size();i++){
                OMNakiMentsu& mentsu = member.m_gamestate.m_aNakiList[i];
		switch(mentsu.m_iCategory){
		case MENTSU_SYUNTSU:
			pTehai->minshun[pTehai->minshun_max] = mentsu.m_aPaiList[0];
			pTehai->minshun_max++;
			break;
		case MENTSU_KOUTSU:
			pTehai->minkou[pTehai->minkou_max] = mentsu.m_aPaiList[0];
			pTehai->minkou_max++;
			break;
		case MENTSU_MINKAN:
			pTehai->minkan[pTehai->minkan_max] = mentsu.m_aPaiList[0];
			pTehai->minkan_max++;
			break;
		case MENTSU_ANKAN:
			pTehai->ankan[pTehai->ankan_max] = mentsu.m_aPaiList[0];
			pTehai->ankan_max++;
			break;
		default:
			break;
		}

	}

}

int OMTaku::getKawahai(int index,UINT *pBuf)
{
        OMMember& member = m_members[index];
	int i;

        for(i=0;i<member.m_aDahai.size();i++){
		*pBuf = member.m_aDahai[i];
		*pBuf++;
	}

        return member.m_aDahai.size();

}

int OMTaku::getVisibleHais(UINT num,int iPlayerIndex)
{
	int i,j,k,count;
	count = 0;

	for(i=0;i<4;i++){
                for(j=0;j<m_members[i].m_aDahai.size();j++){
			if(num == m_members[i].m_aDahai[j]){
				count++;				
			}
		}
		if(i != iPlayerIndex){
                        for(j=0;j<m_members[i].m_aTehai.size();j++){
				if(num == m_members[i].m_aTehai[j]){
					count++;				
				}
			}
		}
                for(j=0;j<m_members[i].m_gamestate.m_aNakiList.size();j++){
                        for(k=0;k<m_members[i].m_gamestate.m_aNakiList[j].m_aPaiList.size();k++){
				if(num == m_members[i].m_gamestate.m_aNakiList[j].m_aPaiList[k]){
					count++;
				}
			}
		}
	}

        for(i=0;i<m_aDora.size();i++){
		if(num == m_aDora[i]){
			count++;				
		}
	}
	return count;

}

void OMTaku::printState(int index,QString& text)
{
	const TCHAR *kyokuTable[] = { _T("�����"),_T("�����"),_T("���O��"),_T("���l��"),_T("����"),_T("����"),_T("��O��"),_T("��l��") };
	const TCHAR *ieTable[] = {_T("����"),_T("���"),_T("����"),_T("�k��")};
	const TCHAR *eventTable[] = { _T("�Ŕv"),_T("�`�["),_T("�|��"),_T("�J��"),_T("�J��"),_T("�J��"),_T("����"),
		_T("�c��"),_T("���[�`"),_T("�p�X"),_T("����v�|�v"),_T("�l���q�A��"),
		_T("�l�l���[�`"),_T("�r�v"),_T("�l�J���c����"),_T("�O�Ƙa"),_T("�����I��"),_T("�ǊJ�n") };
        QString str;
	int i,j;

	if(m_event.m_command.m_iType >= 100){
		str.Format(_T("event : %s\r\n"),eventTable[m_event.m_command.m_iType - 100]);
		text += str;
	}

	if(m_event.m_result.m_bActive){
                for(i=0;i<m_event.m_result.m_aYaku.size();i++){
			text += m_event.m_result.m_aYaku[i];
			text += _T(" ");
		}

		text += _T("\r\n");

		str.Format(_T("%d�| %d�� %d�_\r\n"),m_event.m_result.m_iHan,m_event.m_result.m_iFu,m_event.m_result.m_iScore);

		text += str;		
	}

	str.Format(_T("%s �c�� : %d\r\n"),kyokuTable[m_iKyokuCount],m_iYama);

	text += str;

	text += _T("�h�� ");

        for(i=0;i<m_aDora.size();i++){
                OMPai pai;
		m_aDora[i].getDora(pai);
		pai.getName(str);
		text += str;
		text += _T(" ");
	}

	text += _T("\r\n");

	text += _T("���C�o��\r\n");
	for(i=0;i<4;i++){
		if(i != index){
			text += m_members[i].m_player.m_strName;
			text += _T(" ");
			text += ieTable[m_members[i].m_gamestate.m_iZikaze - 1];
			text += _T("\r\n");
			str.Format(_T("�_�� : %d"),m_members[i].m_iPoint);
			text += str;
			if(m_members[i].m_gamestate.m_bRiichi){
				text += _T("** ���[�` **");
			}
			text += _T("\r\n");

			text += _T("�Ŕv ");
                        for(j=0;j<m_members[i].m_aDahai.size();j++){
				str.Format(_T("[%d]"),j);
				text += str;
				m_members[i].m_aDahai[j].getName(str);
				text += str;
				text += _T(" ");
			}

			text += _T("\r\n");
		}
	}

	text += _T("�v���[��\r\n");
	text += m_members[index].m_player.m_strName;
	text += _T(" ");
	text += ieTable[m_members[index].m_gamestate.m_iZikaze - 1];
	text += _T("\r\n");
	str.Format(_T("�_�� : %d"),m_members[index].m_iPoint);
	text += str;
	if(m_members[index].m_gamestate.m_bRiichi){
		text += _T("** ���[�` **");
	}
	text += _T("\r\n");
	text += _T("�Ŕv ");
        for(j=0;j<m_members[index].m_aDahai.size();j++){
		str.Format(_T("[%d]"),j);
		text += str;
		m_members[index].m_aDahai[j].getName(str);
		text += str;
		text += _T(" ");
	}

	text += _T("\r\n");

	text += _T("��v ");
        for(j=0;j<m_members[index].m_aTehai.size();j++){
		str.Format(_T("[%d]"),j);
		text += str;
		m_members[index].m_aTehai[j].getName(str);
		text += str;
		text += _T(" ");
	}

	text += _T("\r\n");

	text += _T("�R�}���h");

        for(i=0;i<m_members[index].m_aCommandList.size();i++){
		int id = m_members[index].m_aCommandList[i].m_iId;
                OMPai *pPai;
		pPai = &m_members[index].m_aCommandList[i].m_pai;
		if(id >= ID_RIICHI && id <= ID_RIICHI + 13){
			str.Format(_T("[%d] ���[�` "),id);
			text += str;
			pPai->getName(str);
			text += str;
		}else if(id == ID_TSUMO){
			str.Format(_T("[%d] �c�� "),id);
			text += str;
		}else if(id == ID_START){
			str.Format(_T("[%d] ���̋ǂ� "),id);
			text += str;
		}else if(id == ID_PASS){
			str.Format(_T("[%d] ���Ȃ� "),id);
			text += str;
		}else if(id >= ID_TII && id < ID_PON){
			str.Format(_T("[%d] �`�[ "),id);
			text += str;
                        for(j=0;j<m_members[index].m_aCommandList[i].m_mentsu.m_aPaiList.size();j++){
				pPai = &m_members[index].m_aCommandList[i].m_mentsu.m_aPaiList[j];
				pPai->getName(str);
				text += str;
				text += _T(" ");
			}
		}else if(id >= ID_PON && id < ID_DAIMINKAN){
			str.Format(_T("[%d] �|�� "),id);
			text += str;
			pPai->getName(str);
			text += str;
		}else if(id == ID_DAIMINKAN){
			str.Format(_T("[%d] �J�� "),id);
			text += str;
			pPai->getName(str);
			text += str;
		}else if(id == ID_RON){
			str.Format(_T("[%d] ���� "),id);
			text += str;
			pPai->getName(str);
			text += str;
		}else if(id >= ID_KAN && id < ID_RIICHI){
			str.Format(_T("[%d] �J�� "),id);
			text += str;
			pPai->getName(str);
			text += str;
		}
	}

	text += _T("\r\n");
}

OMTaku& OMTaku::operator =(OMTaku& value)
{
	int i;
        OM_COPYARRAY(m_aDora,value.m_aDora);
        OM_COPYARRAY(m_aUradora,value.m_aUradora);
	m_event = value.m_event;
	m_iBakaze = value.m_iBakaze;
	m_iKyokuCount = value.m_iKyokuCount;
	m_iRiichibou = value.m_iRiichibou;
	m_iTsumibou = value.m_iTsumibou;
	m_iTurn = value.m_iTurn;
	m_iYama = value.m_iYama;

	for(i=0;i<4;i++){
		m_members[i] = value.m_members[i];
	}

	return *this;

}

void OMTaku::update(OMTaku& value)
{
	int i,j,num;
	int ind;
	int prevSeq;
        OMPai pai;
	BOOL bInserted,bDeleted,bTsumo = TRUE;

	m_iTurn = value.m_iTurn;
	m_iYama = value.m_iYama;

	for(i=0;i<4;i++){
                for(j=0;j<m_members[i].m_aDahai.size();j++){
			m_members[i].m_aDahai[j].m_bLast = FALSE;
		}
	}

	// �C�x���g����������
	if(value.m_event.m_bActive){
		if(m_event.m_iSeq != value.m_event.m_iSeq){
			prevSeq = m_event.m_iSeq;
			m_event = value.m_event;
			switch(value.m_event.m_command.m_iType){
			case TYPE_DAHAI:
				ind = getMemberIndex(&value.m_event.m_command.m_player);
                                m_members[ind].m_aDahai.append(value.m_event.m_command.m_pai);
                                m_members[ind].m_aDahai[m_members[ind].m_aDahai.size()-1].m_bLast = TRUE;
                                bDeleted = m_members[ind].m_aTehai.size() == 0 ? TRUE : FALSE;
				
                                for(i=0;i<m_members[ind].m_aTehai.size();i++){
					if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_pai)){
                                                m_members[ind].m_aTehai.remove(i);
						bDeleted = TRUE;
						break;
					}
				}
				
				if(!bDeleted){
                                        for(i=0;i<m_members[ind].m_aTehai.size();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
                                                        m_members[ind].m_aTehai.remove(i);
							bDeleted = TRUE;
							break;
						}
					}
					
					if(!bDeleted){
						AfxDebugBreak();
					}
				}
				
				// ��v����ג���
                                if(m_members[ind].m_aTehai.size() > 0){
                                        pai = m_members[ind].m_aTehai[m_members[ind].m_aTehai.size()-1];
                                        m_members[ind].m_aTehai.remove(m_members[ind].m_aTehai.size()-1);
					bInserted = FALSE;
					
                                        for(i=m_members[ind].m_aTehai.size()-1;i>=0;i--){
						if(pai >= m_members[ind].m_aTehai[i]){
                                                        m_members[ind].m_aTehai.insert(i+1,pai);
							bInserted = TRUE;
							break;
						}
					}
					
					if(!bInserted){
                                                m_members[ind].m_aTehai.insert(0,pai);
					}
				}
				
				break;
			case TYPE_TII:
				ind = getMemberIndex(&value.m_event.m_command.m_player);
                                m_members[ind].m_gamestate.m_aNakiList.append(value.m_event.m_command.m_mentsu);
                                for(i=0;i<m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai.size();i++){
					if(m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].match(value.m_event.m_command.m_pai)){
						m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].m_bNaki = TRUE;
						break;
					}
				}
				num = 0;
                                for(i=0;i<m_members[ind].m_aTehai.size();i++){
                                        for(j=0;j<value.m_event.m_command.m_mentsu.m_aPaiList.size();j++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_mentsu.m_aPaiList[j])){
                                                        m_members[ind].m_aTehai.remove(i);
							i--;
							num++;
							break;
						}
					}
				}

				if(num < 2){
                                        for(i=0;i<m_members[ind].m_aTehai.size();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
                                                        m_members[ind].m_aTehai.remove(i);
							i--;
							num++;
							if(num >= 2) break;
						}
					}
				}

#if GLASS_DEBUG
				if(num < 2){
					AfxDebugBreak();
				}
#endif

				bTsumo = FALSE;
				break;
			case TYPE_PON:
				ind = getMemberIndex(&value.m_event.m_command.m_player);
                                m_members[ind].m_gamestate.m_aNakiList.append(value.m_event.m_command.m_mentsu);
                                for(i=0;i<m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai.size();i++){
					if(m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].match(value.m_event.m_command.m_pai)){
						m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].m_bNaki = TRUE;
						break;
					}
				}

				num = 0;
                                for(i=0;i<m_members[ind].m_aTehai.size();i++){
                                        for(j=0;j<value.m_event.m_command.m_mentsu.m_aPaiList.size();j++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_mentsu.m_aPaiList[j])){
                                                        m_members[ind].m_aTehai.remove(i);
							i--;
							num++;
							break;
						}
					}
				}

				if(num < 2){
                                        for(i=0;i<m_members[ind].m_aTehai.size();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
                                                        m_members[ind].m_aTehai.remove(i);
							i--;
							num++;
							if(num >= 2) break;
						}
					}
				}
#if GLASS_DEBUG
				if(num < 2){
					AfxDebugBreak();
				}
#endif

				bTsumo = FALSE;
				break;
			case TYPE_DAIMINKAN:
				ind = getMemberIndex(&value.m_event.m_command.m_player);
                                m_members[ind].m_gamestate.m_aNakiList.append(value.m_event.m_command.m_mentsu);
                                for(i=0;i<m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai.size();i++){
					if(m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].match(value.m_event.m_command.m_pai)){
						m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].m_bNaki = TRUE;
						break;
					}
				}
				
				num = 0;
                                for(i=0;i<m_members[ind].m_aTehai.size();i++){
                                        for(j=0;j<value.m_event.m_command.m_mentsu.m_aPaiList.size();j++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_mentsu.m_aPaiList[j])){
                                                        m_members[ind].m_aTehai.remove(i);
							i--;
							num++;
							break;
						}
					}
				}
				if(num < 3){
                                        for(i=0;i<m_members[ind].m_aTehai.size();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
                                                        m_members[ind].m_aTehai.remove(i);
							i--;
							num++;
							if(num >= 3) break;
						}
					}
				}
#if GLASS_DEBUG

				if(num < 3){
					AfxDebugBreak();
				}
#endif

				break;
			case TYPE_KUWAEKAN:
				ind = getMemberIndex(&value.m_event.m_command.m_player);
                                for(i=0;i<m_members[ind].m_gamestate.m_aNakiList.size();i++){
					if((UINT)m_members[ind].m_gamestate.m_aNakiList[i].m_nakihai == (UINT)value.m_event.m_command.m_pai){
                                                m_members[ind].m_gamestate.m_aNakiList.remove(i);
						break;
					}
				}
                                m_members[ind].m_gamestate.m_aNakiList.append(value.m_event.m_command.m_mentsu);
				num = 0;
                                for(i=0;i<m_members[ind].m_aTehai.size();i++){
                                        for(j=0;j<value.m_event.m_command.m_mentsu.m_aPaiList.size();j++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_mentsu.m_aPaiList[j])){
                                                        m_members[ind].m_aTehai.remove(i);
							i--;
							num++;
							break;
						}
					}
				}
				if(num < 1){
                                        for(i=0;i<m_members[ind].m_aTehai.size();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
                                                        m_members[ind].m_aTehai.remove(i);
							i--;
							num++;
							if(num >= 1) break;
						}
					}
				}

#if GLASS_DEBUG
				if(num < 1){
					AfxDebugBreak();
				}
#endif
				break;
			case TYPE_ANKAN:
				ind = getMemberIndex(&value.m_event.m_command.m_player);
                                m_members[ind].m_gamestate.m_aNakiList.append(value.m_event.m_command.m_mentsu);
				num = 0;
                                for(i=0;i<m_members[ind].m_aTehai.size();i++){
                                        for(j=0;j<value.m_event.m_command.m_mentsu.m_aPaiList.size();j++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_mentsu.m_aPaiList[j])){
                                                        m_members[ind].m_aTehai.remove(i);
							i--;
							num++;
							break;
						}
					}
				}
				if(num < 4){
                                        for(i=0;i<m_members[ind].m_aTehai.size();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
                                                        m_members[ind].m_aTehai.remove(i);
							i--;
							num++;
							if(num >= 4) break;
						}
					}
				}

#if GLASS_DEBUG
				if(num < 4){
					AfxDebugBreak();
				}
#endif
				// ��v����ג���
                                if(m_members[ind].m_aTehai.size() > 0){
                                        pai = m_members[ind].m_aTehai[m_members[ind].m_aTehai.size() - 1];
                                        m_members[ind].m_aTehai.remove(m_members[ind].m_aTehai.size() - 1);
					bInserted = FALSE;
					
                                        for(i=m_members[ind].m_aTehai.size() - 1;i>=0;i--){
						if(pai >= m_members[ind].m_aTehai[i]){
                                                        m_members[ind].m_aTehai.insert(i+1,pai);
							bInserted = TRUE;
							break;
						}
					}
					
					if(!bInserted){
                                                m_members[ind].m_aTehai.insert(0,pai);
					}
				}

				break;
			case TYPE_RIICHI:
				ind = getMemberIndex(&value.m_event.m_command.m_player);
                                m_members[ind].m_aDahai.append(value.m_event.m_command.m_pai);
                                m_members[ind].m_aDahai[m_members[ind].m_aDahai.size() - 1].m_bLast = TRUE;
                                bDeleted = m_members[ind].m_aTehai.size() == 0 ? TRUE : FALSE;
				
                                for(i=0;i<m_members[ind].m_aTehai.size();i++){
					if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_pai)){
                                                m_members[ind].m_aTehai.remove(i);
						bDeleted = TRUE;
						break;
					}
				}
				
				if(!bDeleted){
                                        for(i=0;i<m_members[ind].m_aTehai.size();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
                                                        m_members[ind].m_aTehai.remove(i);
							bDeleted = TRUE;
							break;
						}
					}
					
					if(!bDeleted){
						AfxDebugBreak();
					}
				}
				
				// ��v����ג���
                                if(m_members[ind].m_aTehai.size() > 0){
                                        pai = m_members[ind].m_aTehai[m_members[ind].m_aTehai.size() - 1];
                                        m_members[ind].m_aTehai.remove(m_members[ind].m_aTehai.size() - 1);
					bInserted = FALSE;
					
                                        for(i=m_members[ind].m_aTehai.size() - 1;i>=0;i--){
						if(pai >= m_members[ind].m_aTehai[i]){
                                                        m_members[ind].m_aTehai.insert(i+1,pai);
							bInserted = TRUE;
							break;
						}
					}
					
					if(!bInserted){
                                                m_members[ind].m_aTehai.insert(0,pai);
					}
				}
				m_members[ind].m_gamestate.m_bRiichi = TRUE;
				break;
			case TYPE_KOUHAI:
				if(value.m_event.m_command.m_pai != PAI_NIL){
					ind = getMemberIndex(&value.m_event.m_command.m_player);
                                        m_members[ind].m_aDahai.append(value.m_event.m_command.m_pai);
                                        bDeleted = m_members[ind].m_aTehai.size() == 0 ? TRUE : FALSE;
					
                                        for(i=0;i<m_members[ind].m_aTehai.size();i++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_pai)){
                                                        m_members[ind].m_aTehai.remove(i);
							bDeleted = TRUE;
							break;
						}
					}
					
					if(!bDeleted){
                                                for(i=0;i<m_members[ind].m_aTehai.size();i++){
							if(m_members[ind].m_aTehai[i] == PAI_NIL){
                                                                m_members[ind].m_aTehai.remove(i);
								bDeleted = TRUE;
								break;
							}
						}
						
						if(!bDeleted){
							AfxDebugBreak();
						}
					}
					
					// ��v����ג���
                                        if(m_members[ind].m_aTehai.size() > 0){
                                                pai = m_members[ind].m_aTehai[m_members[ind].m_aTehai.size() - 1];
                                                m_members[ind].m_aTehai.remove(m_members[ind].m_aTehai.size() - 1);
						bInserted = FALSE;
						
                                                for(i=m_members[ind].m_aTehai.size() - 1;i>=0;i--){
							if(pai >= m_members[ind].m_aTehai[i]){
                                                                m_members[ind].m_aTehai.insert(i+1,pai);
								bInserted = TRUE;
								break;
							}
						}
						
						if(!bInserted){
                                                        m_members[ind].m_aTehai.insert(0,pai);
						}
					}
				}
				
				break;
			default:
				break;
			}

                        if(m_aDora.size() < value.m_aDora.size()){
                                OM_COPYARRAY(m_aDora,value.m_aDora);
			}
			
                        if(m_aUradora.size() < value.m_aUradora.size()){
                                OM_COPYARRAY(m_aUradora,value.m_aUradora);
			}
			// �c���v�̓R�}���h���X�g����擾����
			for(i=0;i<4;i++){
                                m_members[i].m_aCommandList.clear();
				m_members[i].m_gamestate.m_bTsumo = value.m_members[i].m_gamestate.m_bTsumo;
				
				if(m_members[i].m_gamestate.m_bTsumo && value.m_members[i].m_tsumohai != PAI_NOTINIT){
                                        m_members[i].m_aTehai.append(value.m_members[i].m_tsumohai);
                                        if(m_members[i].m_aTehai.size() > 14){
						AfxDebugBreak();
					}
				}
				
                                for(j=0;j<value.m_members[i].m_aCommandList.size();j++){
                                        //CCommand *pCom = &value.m_members[i].m_aCommandList[j];
                                        m_members[i].m_aCommandList.append(value.m_members[i].m_aCommandList[j]);
				}
				
                                if(value.m_members[i].m_aTehai.size() > 0){
                                        m_members[i].m_aTehai.clear();
                                        OM_COPYARRAY(m_members[i].m_aTehai,value.m_members[i].m_aTehai);
				}
				
                                m_members[i].m_aResultList.clear();
                                for(j=0;j<value.m_members[i].m_aResultList.size();j++){
                                        m_members[i].m_aResultList.append(value.m_members[i].m_aResultList[j]);
				}
			}
		}
	}
}


int OMTaku::getKawahaiEx(int index,MJIKawahai *pKawa)
{
        OMMember& member = m_members[index];
	int i;

        for(i=0;i<member.m_aDahai.size();i++){
		pKawa->hai = member.m_aDahai[i];
		pKawa->state = 0;
		if(member.m_aDahai[i].m_bNaki) pKawa->state |= MJKS_NAKI;
		if(member.m_aDahai[i].m_bRiichi) pKawa->state |= MJKS_REACH;
		pKawa++;
	}

        return member.m_aDahai.size();

}
