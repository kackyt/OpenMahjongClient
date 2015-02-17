﻿/****************************************************************************************
 * Copyright (c) 2010, Takaya Kakizaki(kacky)
 * All rights reserved.

  ソースコード形式かバイナリ形式か、変更するかしないかを問わず、以下の条件を満たす場合に限り、再頒布および使用が許可されます。 

  ・ソースコードを再頒布する場合、上記の著作権表示、本条件一覧、および下記免責条項を含めること。 

  ・バイナリ形式で再頒布する場合、頒布物に付属のドキュメント等の資料に、上記の著作権表示、本条件一覧、および下記免責条項を含めること。 

  ・書面による特別の許可なしに、本ソフトウェアから派生した製品の宣伝または販売促進に、オープン麻雀の名前またはコントリビューターの名前を使用してはならない。


  本ソフトウェアは、著作権者およびコントリビューターによって「現状のまま」提供されており、明示黙示を問わず、
  商業的な使用可能性、および特定の目的に対する適合性に関する暗黙の保証も含め、またそれに限定されない、いかなる保証もありません。
  著作権者もコントリビューターも、事由のいかんを問わず、 損害発生の原因いかんを問わず、かつ責任の根拠が契約であるか厳格責任であるか
  （過失その他の）不法行為であるかを問わず、仮にそのような損害が発生する可能性を知らされていたとしても、本ソフトウェアの使用によって発生した
  （代替品または代用サービスの調達、使用の喪失、データの喪失、利益の喪失、業務の中断も含め、またそれに限定されない）
  直接損害、間接損害、偶発的な損害、特別損害、懲罰的損害、または結果損害について、一切責任を負わないものとします。 

****************************************************************************************/
// Library.h: CLibrary クラスのインターフェイス
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_LIBRARY_H__823E5C0D_EA91_4E97_964F_6B612FCDB742__INCLUDED_)
#define AFX_LIBRARY_H__823E5C0D_EA91_4E97_964F_6B612FCDB742__INCLUDED_

#include "OMXMLCommon.h"
#include "Member.h"	// ClassView によって追加されました。
#include "Pai.h"	// ClassView によって追加されました。
#include "Result.h"
#include "GameState.h"	// ClassView によって追加されました。
#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

class OMLibrary
{
public:
        OMGameState m_gamestate;
        void setMember(int id,OMMember& member,MJITehai* pTehai,int agarihai);
        OMArray<OMResult> m_aResultList;
        OMArray<OMPai> m_aTehai;
        OMPai m_agarihai;
	int m_iId;
        OMPlayer m_player;
        OMLibrary();
        virtual ~OMLibrary();

};

#endif // !defined(AFX_LIBRARY_H__823E5C0D_EA91_4E97_964F_6B612FCDB742__INCLUDED_)
