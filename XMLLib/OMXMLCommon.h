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
#pragma once
#include "OpenMahjongDef.h"

/* Qt XML Parser�� MSXML(Visual C++)�ň������߂̃��b�p�[ */

#ifdef _MSC_VER
/* XSXML�̏ꍇ�|�C���^�ɂ��A�N�Z�X�̂��߁A�ԐڎQ�Ɖ��Z�q���g�� */
#define QDomNode  IXMLDOMNodePtr
#define QDomElement IXMLDOMElementPtr
#define QDomDocument IXMLDOMDocumentPtr
#define QDomNodeList IXMLDOMNodeListPtr
#define QString CString
#define OM_DEFARRAY(type,inst) CArray<type,type&> inst
#define clear() RemoveAll()
#define append(item) Add(item)
#define size() GetSize()
#define remove(i) RemoveAt(i)
#define insert(i,inst) InsertAt(i,inst)
#define OM_EVAL(inst,func)  (inst)->func
#define OM_GETELEMENT(inst,name) OM_EVAL(inst,selectSingleNode(name))
#define OM_GETELEMENTLIST(inst,name) OM_EVAL(inst,selectNodes(name))
#define OM_LISTLENGTH(inst) (inst)->Getlength()
#define OM_LISTITEM(inst,index) (inst)->Getitem(index)
#define OM_GETTEXT(inst,str) (inst)->get_text(&str)
#define OM_CREATETEXT(inst,str) OM_EVAL(inst,createTextNode((LPCTSTR)str))
#define OM_STRTOL(str) (_tcstol((const TCHAR*)(str),NULL,0))
#define OM_NUMTOSTR(str,val) ((str).Format(_T("%d"),val))
#define OM_ISNULL(inst) ((inst) == NULL)
#define OM_ISEMPTY(inst) ((inst) == NULL)
#define OM_COPYARRAY(dst,src) ((src).Copy(dst))


#else
#include <QtXml>
#define OM_DEFARRAY(type,inst) QVector<type> inst
#define OM_EVAL(inst,func)  (inst).func
#define OM_LISTLENGTH(inst) (inst).size()
#define OM_LISTITEM(inst,index) (inst).item(index)
#define OM_GETELEMENT(inst,name) OM_EVAL(inst,firstChildElement(name))
#define OM_GETELEMENTLIST(inst,name) OM_EVAL(inst.toElement(),elementsByTagName(name))
#define OM_GETTEXT(inst,str) (str = (inst).firstChild().nodeValue().data())
#define OM_CREATETEXT(inst,str) OM_EVAL(inst,createTextNode(str))
#define OM_STRTOL(str) ((str).toLong())
#define OM_NUMTOSTR(str,val) ((str) = (str).sprintf(_T("%d"),val))
#define OM_ISNULL(inst) ((inst).isNull())
#define OM_ISEMPTY(inst) ((inst).isEmpty())
#define OM_COPYARRAY(dst,src) ((dst) = (src))
#define _T(str) (str)
#define Format sprintf
typedef QChar *BSTR;
typedef char TCHAR;
typedef bool BOOL;
typedef uint UINT;
typedef ushort USHORT;
typedef void* LPVOID;
#define WINAPI __stdcall
#define TRUE true
#define FALSE false
#define AfxDebugBreak()

#endif

#define OM_TOLONG(inst,val) \
    if(!OM_ISNULL(inst)){\
        BSTR pStr;\
        QString text;\
        OM_GETTEXT(inst,pStr);\
        text = QString(pStr);\
        val = OM_STRTOL(text);\
    }

#define OM_TOBOOL(inst,val) \
    if(!OM_ISNULL(inst)){\
        BSTR pStr;\
        QString text;\
        OM_GETTEXT(inst,pStr);\
        text = QString(pStr);\
        val = (text == _T("true")) ? TRUE : FALSE;\
    }
