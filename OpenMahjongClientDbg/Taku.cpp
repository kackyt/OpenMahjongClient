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
#include "OpenMahjongClientDbg.h"
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

CTaku::CTaku()
{

}

CTaku::~CTaku()
{

}

void CTaku::parseXML(IXMLDOMNodePtr pElem)
{
	IXMLDOMNodePtr pNode;
	IXMLDOMNodeListPtr pNodeList;
	CString text;
	BSTR pStr;
	int i;

	/* �X�J���[�f�[�^�̊i�[ */

	pNode = pElem->selectSingleNode(_T(TAG_YAMA "/" TAG_COUNT));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iYama = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_BAKAZE));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iBakaze = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_KYOKUCOUNT));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iKyokuCount = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_RIICHIBOU));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iRiichibou = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_TSUMIBOU));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iTsumibou = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_TURN));

	if(pNode != NULL){
		pNode->get_text(&pStr);
		text = pStr;
		m_iTurn = _tcstol((const TCHAR*)text,NULL,0);
	}

	pNode = pElem->selectSingleNode(_T(TAG_EVENT));

	if(pNode != NULL){
		m_event.parseXML(pNode);
	}

	/* �h���v�̊i�[ */
	m_aDora.RemoveAll();
	pNodeList = pElem->selectNodes(_T(TAG_DORA "/" TAG_PAI));

	if(pNodeList != NULL){
		for(i=0;i<pNodeList->Getlength();i++){
			CPai pai;
			pNode = pNodeList->Getitem(i);
			pai.parseXML(pNode);
			m_aDora.Add(pai);
		}
	}

	m_aUradora.RemoveAll();

	pNodeList = pElem->selectNodes(_T(TAG_URADORA "/" TAG_PAI));

	if(pNodeList != NULL){
		for(i=0;i<pNodeList->Getlength();i++){
			CPai pai;
			pNode = pNodeList->Getitem(i);
			pai.parseXML(pNode);
			m_aUradora.Add(pai);
		}
	}

	pNodeList = pElem->selectNodes(_T(TAG_MEMBER));

	if(pNodeList != NULL){
		for(i=0;i<pNodeList->Getlength();i++){
			pNode = pNodeList->Getitem(i);
			m_members[i].parseXML(pNode);
		}
	}


}

int CTaku::getMemberIndex(CPlayer *player)
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
void CTaku::getMJITehai(int index,MJITehai1 *pTehai,CRule& rule)
{
	CMember& member = m_members[index];
	int i,j,k;

	ZeroMemory(pTehai,sizeof(MJITehai1));

	/* ���̂Ƃ���ԃE�[�͍l�����Ȃ� */

	if(member.m_aTehai.GetSize() == 0){
		pTehai->tehai_max = 0;
	}else{
		if(member.m_gamestate.m_bTsumo){
			pTehai->tehai_max = member.m_aTehai.GetSize() - 1;
		}else{
			pTehai->tehai_max = member.m_aTehai.GetSize();
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

	for(i=0;i<member.m_gamestate.m_aNakiList.GetSize();i++){
		CNakiMentsu& mentsu = member.m_gamestate.m_aNakiList[i];
		switch(mentsu.m_iCategory){
		case MENTSU_SYUNTSU:
			pTehai->minshun[pTehai->minshun_max] = mentsu.m_aPaiList[0];
			pTehai->minshun_hai[0][pTehai->minshun_max] = mentsu.m_nakihai;

			k = 1;
			for(j=0;j<mentsu.m_aPaiList.GetSize();j++){
				if(j != (int)mentsu.getNakiPos()){
					pTehai->minshun_hai[k++][pTehai->minshun_max] = mentsu.m_aPaiList[j];
					if(mentsu.m_aPaiList[j].isAka(rule)) pTehai->minshun_hai[k++][pTehai->minshun_max] += 64;
				}
			}
			pTehai->minshun_max++;
			break;
		case MENTSU_KOUTSU:
			pTehai->minkou[pTehai->minkou_max] = mentsu.m_aPaiList[0];
			for(j=0;j<mentsu.m_aPaiList.GetSize();j++){
				pTehai->minkou_hai[j][pTehai->minkou_max] = mentsu.m_aPaiList[j];
				if(mentsu.m_aPaiList[j].isAka(rule)) pTehai->minkou_hai[j][pTehai->minkou_max] += 64;
			}
			pTehai->minkou_max++;
			break;
		case MENTSU_MINKAN:
			pTehai->minkan[pTehai->minkan_max] = mentsu.m_aPaiList[0];
			for(j=0;j<mentsu.m_aPaiList.GetSize();j++){
				pTehai->minkan_hai[j][pTehai->minkan_max] = mentsu.m_aPaiList[j];
				if(mentsu.m_aPaiList[j].isAka(rule)) pTehai->minkan_hai[j][pTehai->minkan_max] += 64;
			}
			pTehai->minkan_max++;
			break;
		case MENTSU_ANKAN:
			pTehai->ankan[pTehai->ankan_max] = mentsu.m_aPaiList[0];
			for(j=0;j<mentsu.m_aPaiList.GetSize();j++){
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

void CTaku::getMJITehai(int index,MJITehai *pTehai)
{
	CMember& member = m_members[index];
	int i;

	ZeroMemory(pTehai,sizeof(MJITehai));

	/* ���̂Ƃ���ԃE�[�͍l�����Ȃ� */

	if(member.m_aTehai.GetSize() == 0){
		pTehai->tehai_max = 0;
	}else{
		if(member.m_gamestate.m_bTsumo){
			pTehai->tehai_max = member.m_aTehai.GetSize() - 1;
		}else{
			pTehai->tehai_max = member.m_aTehai.GetSize();
		}
		
		for(i=0;i<(int)pTehai->tehai_max;i++){
			pTehai->tehai[i] = member.m_aTehai[i];
		}
	}

	pTehai->minshun_max = 0;
	pTehai->minkou_max = 0;
	pTehai->minkan_max = 0;
	pTehai->ankan_max = 0;

	for(i=0;i<member.m_gamestate.m_aNakiList.GetSize();i++){
		CNakiMentsu& mentsu = member.m_gamestate.m_aNakiList[i];
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

int CTaku::getKawahai(int index,UINT *pBuf)
{
	CMember& member = m_members[index];
	int i;

	for(i=0;i<member.m_aDahai.GetSize();i++){
		*pBuf = member.m_aDahai[i];
		*pBuf++;
	}

	return member.m_aDahai.GetSize();

}

int CTaku::getVisibleHais(UINT num,int iPlayerIndex)
{
	int i,j,k,count;
	count = 0;

	for(i=0;i<4;i++){
		for(j=0;j<m_members[i].m_aDahai.GetSize();j++){
			if(num == m_members[i].m_aDahai[j]){
				count++;				
			}
		}
		if(i != iPlayerIndex){
			for(j=0;j<m_members[i].m_aTehai.GetSize();j++){
				if(num == m_members[i].m_aTehai[j]){
					count++;				
				}
			}
		}
		for(j=0;j<m_members[i].m_gamestate.m_aNakiList.GetSize();j++){
			for(k=0;k<m_members[i].m_gamestate.m_aNakiList[j].m_aPaiList.GetSize();k++){
				if(num == m_members[i].m_gamestate.m_aNakiList[j].m_aPaiList[k]){
					count++;
				}
			}
		}
	}

	for(i=0;i<m_aDora.GetSize();i++){
		if(num == m_aDora[i]){
			count++;				
		}
	}
	return count;

}

void CTaku::printState(int index,CString& text)
{
	const TCHAR *kyokuTable[] = { _T("�����"),_T("�����"),_T("���O��"),_T("���l��"),_T("����"),_T("����"),_T("��O��"),_T("��l��") };
	const TCHAR *ieTable[] = {_T("����"),_T("���"),_T("����"),_T("�k��")};
	const TCHAR *eventTable[] = { _T("�Ŕv"),_T("�`�["),_T("�|��"),_T("�J��"),_T("�J��"),_T("�J��"),_T("����"),
		_T("�c��"),_T("���[�`"),_T("�p�X"),_T("����v�|�v"),_T("�l���q�A��"),
		_T("�l�l���[�`"),_T("�r�v"),_T("�l�J���c����"),_T("�O�Ƙa"),_T("�����I��"),_T("�ǊJ�n") };
	CString str;
	int i,j;

	if(m_event.m_command.m_iType >= 100){
		str.Format(_T("event : %s\r\n"),eventTable[m_event.m_command.m_iType - 100]);
		text += str;
	}

	if(m_event.m_result.m_bActive){
		for(i=0;i<m_event.m_result.m_aYaku.GetSize();i++){
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

	for(i=0;i<m_aDora.GetSize();i++){
		CPai pai;
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
			for(j=0;j<m_members[i].m_aDahai.GetSize();j++){
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
	for(j=0;j<m_members[index].m_aDahai.GetSize();j++){
		str.Format(_T("[%d]"),j);
		text += str;
		m_members[index].m_aDahai[j].getName(str);
		text += str;
		text += _T(" ");
	}

	text += _T("\r\n");

	text += _T("��v ");
	for(j=0;j<m_members[index].m_aTehai.GetSize();j++){
		str.Format(_T("[%d]"),j);
		text += str;
		m_members[index].m_aTehai[j].getName(str);
		text += str;
		text += _T(" ");
	}

	text += _T("\r\n");

	text += _T("�R�}���h");

	for(i=0;i<m_members[index].m_aCommandList.GetSize();i++){
		int id = m_members[index].m_aCommandList[i].m_iId;
		CPai *pPai;
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
			for(j=0;j<m_members[index].m_aCommandList[i].m_mentsu.m_aPaiList.GetSize();j++){
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

CTaku& CTaku::operator =(CTaku& value)
{
	int i;
	m_aDora.Copy(value.m_aDora);
	m_aUradora.Copy(value.m_aUradora);
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

void CTaku::update(CTaku& value)
{
	int i,j,num;
	int ind;
	int prevSeq;
	CPai pai;
	BOOL bInserted,bDeleted,bTsumo = TRUE;

	m_iTurn = value.m_iTurn;
	m_iYama = value.m_iYama;

	for(i=0;i<4;i++){
		for(j=0;j<m_members[i].m_aDahai.GetSize();j++){
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
				m_members[ind].m_aDahai.Add(value.m_event.m_command.m_pai);
				m_members[ind].m_aDahai[m_members[ind].m_aDahai.GetUpperBound()].m_bLast = TRUE;
				bDeleted = m_members[ind].m_aTehai.GetSize() == 0 ? TRUE : FALSE;
				
				for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
					if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_pai)){
						m_members[ind].m_aTehai.RemoveAt(i);
						bDeleted = TRUE;
						break;
					}
				}
				
				if(!bDeleted){
					for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
							m_members[ind].m_aTehai.RemoveAt(i);
							bDeleted = TRUE;
							break;
						}
					}
					
					if(!bDeleted){
						AfxDebugBreak();
					}
				}
				
				// ��v����ג���
				if(m_members[ind].m_aTehai.GetSize() > 0){
					pai = m_members[ind].m_aTehai[m_members[ind].m_aTehai.GetUpperBound()];
					m_members[ind].m_aTehai.RemoveAt(m_members[ind].m_aTehai.GetUpperBound());
					bInserted = FALSE;
					
					for(i=m_members[ind].m_aTehai.GetUpperBound();i>=0;i--){
						if(pai >= m_members[ind].m_aTehai[i]){
							m_members[ind].m_aTehai.InsertAt(i+1,pai);
							bInserted = TRUE;
							break;
						}
					}
					
					if(!bInserted){
						m_members[ind].m_aTehai.InsertAt(0,pai);
					}
				}
				
				break;
			case TYPE_TII:
				ind = getMemberIndex(&value.m_event.m_command.m_player);
				m_members[ind].m_gamestate.m_aNakiList.Add(value.m_event.m_command.m_mentsu);
				for(i=0;i<m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai.GetSize();i++){
					if(m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].match(value.m_event.m_command.m_pai)){
						m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].m_bNaki = TRUE;
						break;
					}
				}
				num = 0;
				for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
					for(j=0;j<value.m_event.m_command.m_mentsu.m_aPaiList.GetSize();j++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_mentsu.m_aPaiList[j])){
							m_members[ind].m_aTehai.RemoveAt(i);
							i--;
							num++;
							break;
						}
					}
				}

				if(num < 2){
					for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
							m_members[ind].m_aTehai.RemoveAt(i);
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
				m_members[ind].m_gamestate.m_aNakiList.Add(value.m_event.m_command.m_mentsu);
				for(i=0;i<m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai.GetSize();i++){
					if(m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].match(value.m_event.m_command.m_pai)){
						m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].m_bNaki = TRUE;
						break;
					}
				}

				num = 0;
				for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
					for(j=0;j<value.m_event.m_command.m_mentsu.m_aPaiList.GetSize();j++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_mentsu.m_aPaiList[j])){
							m_members[ind].m_aTehai.RemoveAt(i);
							i--;
							num++;
							break;
						}
					}
				}

				if(num < 2){
					for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
							m_members[ind].m_aTehai.RemoveAt(i);
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
				m_members[ind].m_gamestate.m_aNakiList.Add(value.m_event.m_command.m_mentsu);
				for(i=0;i<m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai.GetSize();i++){
					if(m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].match(value.m_event.m_command.m_pai)){
						m_members[value.m_event.m_command.m_mentsu.m_iAite].m_aDahai[i].m_bNaki = TRUE;
						break;
					}
				}
				
				num = 0;
				for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
					for(j=0;j<value.m_event.m_command.m_mentsu.m_aPaiList.GetSize();j++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_mentsu.m_aPaiList[j])){
							m_members[ind].m_aTehai.RemoveAt(i);
							i--;
							num++;
							break;
						}
					}
				}
				if(num < 3){
					for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
							m_members[ind].m_aTehai.RemoveAt(i);
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
				for(i=0;i<m_members[ind].m_gamestate.m_aNakiList.GetSize();i++){
					if((UINT)m_members[ind].m_gamestate.m_aNakiList[i].m_nakihai == (UINT)value.m_event.m_command.m_pai){
						m_members[ind].m_gamestate.m_aNakiList.RemoveAt(i);
						break;
					}
				}
				m_members[ind].m_gamestate.m_aNakiList.Add(value.m_event.m_command.m_mentsu);
				num = 0;
				for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
					for(j=0;j<value.m_event.m_command.m_mentsu.m_aPaiList.GetSize();j++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_mentsu.m_aPaiList[j])){
							m_members[ind].m_aTehai.RemoveAt(i);
							i--;
							num++;
							break;
						}
					}
				}
				if(num < 1){
					for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
							m_members[ind].m_aTehai.RemoveAt(i);
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
				m_members[ind].m_gamestate.m_aNakiList.Add(value.m_event.m_command.m_mentsu);
				num = 0;
				for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
					for(j=0;j<value.m_event.m_command.m_mentsu.m_aPaiList.GetSize();j++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_mentsu.m_aPaiList[j])){
							m_members[ind].m_aTehai.RemoveAt(i);
							i--;
							num++;
							break;
						}
					}
				}
				if(num < 4){
					for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
							m_members[ind].m_aTehai.RemoveAt(i);
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
				if(m_members[ind].m_aTehai.GetSize() > 0){
					pai = m_members[ind].m_aTehai[m_members[ind].m_aTehai.GetUpperBound()];
					m_members[ind].m_aTehai.RemoveAt(m_members[ind].m_aTehai.GetUpperBound());
					bInserted = FALSE;
					
					for(i=m_members[ind].m_aTehai.GetUpperBound();i>=0;i--){
						if(pai >= m_members[ind].m_aTehai[i]){
							m_members[ind].m_aTehai.InsertAt(i+1,pai);
							bInserted = TRUE;
							break;
						}
					}
					
					if(!bInserted){
						m_members[ind].m_aTehai.InsertAt(0,pai);
					}
				}

				break;
			case TYPE_RIICHI:
				ind = getMemberIndex(&value.m_event.m_command.m_player);
				m_members[ind].m_aDahai.Add(value.m_event.m_command.m_pai);
				m_members[ind].m_aDahai[m_members[ind].m_aDahai.GetUpperBound()].m_bLast = TRUE;
				bDeleted = m_members[ind].m_aTehai.GetSize() == 0 ? TRUE : FALSE;
				
				for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
					if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_pai)){
						m_members[ind].m_aTehai.RemoveAt(i);
						bDeleted = TRUE;
						break;
					}
				}
				
				if(!bDeleted){
					for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
						if(m_members[ind].m_aTehai[i] == PAI_NIL){
							m_members[ind].m_aTehai.RemoveAt(i);
							bDeleted = TRUE;
							break;
						}
					}
					
					if(!bDeleted){
						AfxDebugBreak();
					}
				}
				
				// ��v����ג���
				if(m_members[ind].m_aTehai.GetSize() > 0){
					pai = m_members[ind].m_aTehai[m_members[ind].m_aTehai.GetUpperBound()];
					m_members[ind].m_aTehai.RemoveAt(m_members[ind].m_aTehai.GetUpperBound());
					bInserted = FALSE;
					
					for(i=m_members[ind].m_aTehai.GetUpperBound();i>=0;i--){
						if(pai >= m_members[ind].m_aTehai[i]){
							m_members[ind].m_aTehai.InsertAt(i+1,pai);
							bInserted = TRUE;
							break;
						}
					}
					
					if(!bInserted){
						m_members[ind].m_aTehai.Add(pai);
					}
				}
				m_members[ind].m_gamestate.m_bRiichi = TRUE;
				break;
			case TYPE_KOUHAI:
				if(value.m_event.m_command.m_pai != PAI_NIL){
					ind = getMemberIndex(&value.m_event.m_command.m_player);
					m_members[ind].m_aDahai.Add(value.m_event.m_command.m_pai);
					bDeleted = m_members[ind].m_aTehai.GetSize() == 0 ? TRUE : FALSE;
					
					for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
						if(m_members[ind].m_aTehai[i].match(value.m_event.m_command.m_pai)){
							m_members[ind].m_aTehai.RemoveAt(i);
							bDeleted = TRUE;
							break;
						}
					}
					
					if(!bDeleted){
						for(i=0;i<m_members[ind].m_aTehai.GetSize();i++){
							if(m_members[ind].m_aTehai[i] == PAI_NIL){
								m_members[ind].m_aTehai.RemoveAt(i);
								bDeleted = TRUE;
								break;
							}
						}
						
						if(!bDeleted){
							AfxDebugBreak();
						}
					}
					
					// ��v����ג���
					if(m_members[ind].m_aTehai.GetSize() > 0){
						pai = m_members[ind].m_aTehai[m_members[ind].m_aTehai.GetUpperBound()];
						m_members[ind].m_aTehai.RemoveAt(m_members[ind].m_aTehai.GetUpperBound());
						bInserted = FALSE;
						
						for(i=m_members[ind].m_aTehai.GetUpperBound();i>=0;i--){
							if(pai >= m_members[ind].m_aTehai[i]){
								m_members[ind].m_aTehai.InsertAt(i+1,pai);
								bInserted = TRUE;
								break;
							}
						}
						
						if(!bInserted){
							m_members[ind].m_aTehai.Add(pai);
						}
					}
				}
				
				break;
			default:
				break;
			}
		}
	}
	
	if(m_aDora.GetSize() < value.m_aDora.GetSize()){
		m_aDora.Copy(value.m_aDora);
	}
	
	if(m_aUradora.GetSize() < value.m_aUradora.GetSize()){
		m_aUradora.Copy(value.m_aUradora);
	}
	
	// �c���v�̓R�}���h���X�g����擾����
	for(i=0;i<4;i++){
		m_members[i].m_aCommandList.RemoveAll();
		m_members[i].m_gamestate.m_bTsumo = value.m_members[i].m_gamestate.m_bTsumo;
		
		if(m_members[i].m_gamestate.m_bTsumo && value.m_members[i].m_tsumohai != PAI_NOTINIT){
			m_members[i].m_aTehai.Add(value.m_members[i].m_tsumohai);
			if(m_members[i].m_aTehai.GetSize() > 14){
				AfxDebugBreak();
			}
		}
		
		for(j=0;j<value.m_members[i].m_aCommandList.GetSize();j++){
			CCommand *pCom = &value.m_members[i].m_aCommandList[j];
			m_members[i].m_aCommandList.Add(value.m_members[i].m_aCommandList[j]);
		}
		
		if(value.m_members[i].m_aTehai.GetSize() > 0){
			m_members[i].m_aTehai.RemoveAll();
			m_members[i].m_aTehai.Copy(value.m_members[i].m_aTehai);
		}
		
		m_members[i].m_aResultList.RemoveAll();
		for(j=0;j<value.m_members[i].m_aResultList.GetSize();j++){
			m_members[i].m_aResultList.Add(value.m_members[i].m_aResultList[j]);
		}
	}
	
}


int CTaku::getKawahaiEx(int index,MJIKawahai *pKawa)
{
	CMember& member = m_members[index];
	int i;

	for(i=0;i<member.m_aDahai.GetSize();i++){
		pKawa->hai = member.m_aDahai[i];
		pKawa->state = 0;
		if(member.m_aDahai[i].m_bNaki) pKawa->state |= MJKS_NAKI;
		if(member.m_aDahai[i].m_bRiichi) pKawa->state |= MJKS_REACH;
		pKawa++;
	}

	return member.m_aDahai.GetSize();

}
