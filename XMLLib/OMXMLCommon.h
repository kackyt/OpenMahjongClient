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

#ifndef WITHQT
/* XSXML�̏ꍇ�|�C���^�ɂ��A�N�Z�X�̂��߁A�ԐڎQ�Ɖ��Z�q���g�� */
#define QDomNode  IXMLDOMNodePtr
#define QDomElement IXMLDOMElementPtr
#define QDomDocument IXMLDOMDocumentPtr
#define QDomNodeList IXMLDOMNodeListPtr
#define QString CString
#define OM_DEFARRAY(type) CArray<type,type&>
#define OM_CREATEDOCUMENT(inst) (inst).CreateInstance(CLSID_DOMDocument)
#define OM_LOADXML(inst,str) (inst)->loadXML((LPCTSTR)str)
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
#define OM_SLEEP(tim) Sleep(tim)
#define OM_TOXML(inst,str)  { \
    BSTR bstr;\
    (inst)->get_xml(&bstr);\
    str = _T("<?xml version=\"1.0\" encoding=\"Shift_JIS\" ?>");\
    str += bstr;\
    }

static inline void OM_GETATTRIBUTE(QDomNode inst,LPCTSTR name,QString &text){
    QDomNode pNode = inst->Getattributes()->getNamedItem(name);
    if(OM_ISNULL(pNode)){
        text = pNode->GetnodeValue().bstrVal;
    }
}

#else
#include <QtXml>
#include <QVector>
typedef QDomNode OMDomNode;
typedef QDomElement OMDomElement;
typedef QDomDocument OMDomDocument;
#define XMLOBJ_ISPOINTER (0)

class OMDomNodeList {
public:
    OMDomNodeList(){}
    virtual ~OMDomNodeList(){}
    OMDomNode	at ( int index ) const{
        return m_list[index];
    }
    int	count () const{
        return m_list.count();
    }
    bool	isEmpty () const{
        return m_list.isEmpty();
    }
    QDomNode	item ( int index ) const{
        return m_list[index];
    }

    int	length () const{
        return m_list.length();
    }
    int	size () const{
        return m_list.length();
    }

    OMDomNodeList &	operator= ( const OMDomNodeList & n ){
        m_list = n.m_list;
        return *this;
    }

    bool	operator== ( const OMDomNodeList & n ) const{
        return m_list == n.m_list;
    }


    void	append ( const OMDomNode & value ){
        m_list.append(value);
    }

    void	append ( const OMDomNodeList & value ){
        m_list.append(value.m_list);
    }

private:
    QList<OMDomNode> m_list;
};


class OMString : public QString {
public:
    OMString() {}
    OMString(const char *str) : QString(str) {}
    OMString(const OMString &inst) : QString(inst) {}
    OMString(const QString &inst) : QString(inst) {}

    void Format(const char *format,...)
    {
        va_list ap;
        va_start(ap,format);
        this->vsprintf(format,ap);
        va_end(ap);
    }

};

template <typename T> class OMArray{
private:
    QVector<T> inst;

public:
    int size() {
        return inst.size();
    }
    void clear() {
        inst.clear();
    }
    void remove(int index) {
        inst.remove(index);
    }
    T & operator[](int index){
        return inst[index];
    }
    void insert(int index,const T& value){
        inst.insert(index,value);
    }

    void append(const T&value){
        inst.append(value);
    }

    void copy(OMArray<T> &src){
        *this = src;
    }
};

#ifndef TRUE
#define TRUE (1)
#endif
#ifndef FALSE
#define FALSE (0)
#endif
#define TCHAR char
typedef int BOOL;
typedef uint UINT;
typedef long LONG;
typedef ushort USHORT;
typedef void* LPVOID;
#ifndef LOWORD
#define LOWORD(val) ((val) & 0xFFFF)
#endif
#ifndef HIWORD
#define HIWORD(val) (((val) >> 16) & 0xFFFF)
#endif
#define WINAPI __stdcall
#define _T(str) (str)
#define AfxDebugBreak()


#if 0

#define OM_DEFARRAY(type) QVector<type>
#define OM_EVAL(inst,func)  (inst).func
#define OM_CREATEDOCUMENT(inst)
#define OM_LOADXML(inst,str) (inst).setContent(str)
#define OM_LISTLENGTH(inst) (inst).size()
#define OM_LISTITEM(inst,index) (inst).item(index)
static inline QDomElement OM_GETELEMENT(QDomNode inst,QString name) {
    QStringList list = name.split("/");
    QDomElement node;
    bool isFirst = true;
    while(!list.isEmpty()){
        QString nm = list.takeFirst();
        if(isFirst){
            node = inst.firstChildElement(nm);
            isFirst = false;
        }else{
            node = node.firstChildElement(nm);
        }
        if(node.isNull()) break;
    }
    return node;
}

static inline QDomNodeList OM_GETELEMENTLIST(QDomNode inst,QString name) {
    QStringList list = name.split("/");
    QDomElement node;
    QDomNodeList nodelist;
    QString nm;
    bool isFirst = true;

    while(list.size() > 1){
        nm = list.takeFirst();
        if(isFirst){
            node = inst.firstChildElement(nm);
            isFirst = false;
        }else{
            node = node.firstChildElement(nm);
        }
        if(node.isNull()) break;
    }

    if(isFirst){
        node = inst.toElement();
    }

    if(!node.isNull()){
        nm = list.takeFirst();
        nodelist = node.elementsByTagName(nm);
    }

    return nodelist;
}

#define OM_GETTEXT(inst,str) (str = (inst).firstChild().nodeValue())
#define OM_CREATETEXT(inst,str) OM_EVAL(inst,createTextNode(str))
#define OM_STRTOL(str) ((str).toLong())
#define OM_NUMTOSTR(str,val) ((str) = (str).sprintf(_T("%d"),val))
#define OM_ISNULL(inst) ((inst).isNull())
#define OM_ISEMPTY(inst) ((inst).isEmpty())
#define OM_COPYARRAY(dst,src) ((dst) = (src))
#define OM_TOXML(inst,str) (str = (inst).toString(-1))
#define OM_GETATTRIBUTE(inst,name,text) (text = inst.attribute(name))

static inline void OM_TOLONG(QDomNode inst,int &val)
{
    if(!OM_ISNULL(inst)){
        QString text;
        text = inst.firstChild().nodeValue();
        val = OM_STRTOL(text);
    }
}

#if 0
#define OM_TOLONG(inst,val) \
    if(!OM_ISNULL(inst)){\
        BSTR pStr;\
        QString text;\
        OM_GETTEXT(inst,pStr);\
        text = QString(pStr);\
        val = OM_STRTOL(text);\
    }
#endif

#define OM_TOBOOL(inst,val) \
    if(!OM_ISNULL(inst)){\
        BSTR pStr;\
        QString text;\
        OM_GETTEXT(inst,pStr);\
        text = QString(pStr);\
        val = (text == _T("true")) ? TRUE : FALSE;\
    }


#define Format sprintf
//#define TRUE (1)
//#define FALSE (0)
#define OM_SLEEP(tim) { \
    QMutex mutex;\
    QWaitCondition wc;\
    mutex.lock();\
    wc.wait(&mutex,(tim));\
    mutex.unlock();\
    }

#endif
#endif

extern long OMStrtol(OMString val);
extern void OMNumToStr(OMString &str,int val);

#if XMLOBJ_ISPOINTER == 1
extern void OMCreateDocument(OMDomDocument inst);
extern void OMLoadXML(OMDomDocument inst,OMString &str);
extern OMDomElement OMGetElement(OMDomNode node,OMString name);
extern OMDomNodeList OMGetElementList(OMDomNode node,OMString name);
extern void OMToXML(OMDomDocument inst,OMString &str);
extern int OMListLength(OMDomNodeList list);
extern OMDomNode OMListItem(OMDomNodeList list,int index);
extern void OMGetAttribute(OMDomElement inst,OMString name,OMString &str);
extern bool OMIsNull(OMDomNode inst);
extern OMDomNode OMCreateTextNode(OMDomDocument doc,OMString str);
extern void OMGetText(OMDomNode inst,OMString &str);
extern void OMToNum(OMDomNode inst,int &val);
extern void OMToBool(OMDomNode inst,BOOL &val);
extern OMDomElement OMCreateElement(OMDomDocument doc,OMString name);
extern void OMAppendChild(OMDomNode parent,OMDomNode child);
extern void OMSetAttribute(OMDomElement inst,OMString name,OMString val);
extern bool OMIsEmpty(OMDomNodeList list);
#else
extern void OMCreateDocument(OMDomDocument &inst);
extern void OMLoadXML(OMDomDocument &inst,OMString &str);
extern OMDomElement OMGetElement(OMDomNode &node,OMString name);
extern OMDomNodeList OMGetElementList(OMDomNode &node,OMString name);
extern void OMToXML(OMDomDocument &inst,OMString &str);
extern int OMListLength(OMDomNodeList &list);
extern OMDomNode OMListItem(OMDomNodeList &list,int index);
extern void OMGetAttribute(OMDomElement &inst,OMString name,OMString &str);
extern bool OMIsNull(OMDomNode &inst);
extern OMDomNode OMCreateTextNode(OMDomDocument &doc,OMString str);
extern void OMNumToStr(OMString &str,int val);
extern void OMGetText(OMDomNode &inst,OMString &str);
extern void OMToNum(OMDomNode &inst,int &val);
extern void OMToBool(OMDomNode &inst,BOOL &val);
extern OMDomElement OMCreateElement(OMDomDocument &doc,OMString name);
extern void OMAppendChild(OMDomNode &parent,OMDomNode &child);
extern void OMSetAttribute(OMDomElement &inst,OMString name,OMString val);
extern bool OMIsEmpty(OMDomNodeList &list);
#endif

