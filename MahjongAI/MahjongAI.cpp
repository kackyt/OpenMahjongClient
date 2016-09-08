/****************************************************************************************
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
#include <windows.h>
#include <functional>
#include <memory>
#include <mruby.h>
#include <mruby/dump.h>

#include "MIPIface.h"

#include "MahjongAI_global.h"

using namespace std;

static UINT(*MJSendMessage)(LPVOID, UINT, UINT, UINT);
extern "C" const uint8_t ai[];

class MJAIRuby {
public:
	mrb_state *_mrb;
	mrb_value _mr_value;
	UINT interfaceFunc(UINT message, UINT param1, UINT param2);
};

extern "C" mrb_value __stdcall callMessage(mrb_state *mrb, mrb_value self, mrb_value param1, mrb_value param2, mrb_value param3)
{
	return mrb_nil_value();
}


UINT MJAIRuby::interfaceFunc(UINT message, UINT param1, UINT param2)
{
	if (message == MJPI_INITIALIZE) {
		_mrb = mrb_open();
		_mr_value = mrb_load_irep(_mrb, ai);
	}

	mrb_value ret = mrb_funcall(_mrb, _mr_value, "native_interface", 3, mrb_fixnum_value(message), mrb_fixnum_value(param1), mrb_fixnum_value(param2));

	return mrb_fixnum(ret);
}


// インターフェース関数
extern "C" UINT __stdcall MJPInterfaceFunc(MJAIRuby* inst,UINT message,UINT param1,UINT param2)
{
	if (message == MJPI_YOURNAME) {
		return (UINT)"てすと";
	}
	if (inst) {
		return inst->interfaceFunc(message, param1, param2);
	}
    switch(message){
    case MJPI_SUTEHAI :
       return MJPIR_SUTEHAI | 13;
    case MJPI_ONACTION :
       return 0;
    case MJPI_STARTKYOKU :
       return 0;
    case MJPI_ENDKYOKU :
       return 0;
    case MJPI_STARTGAME :
       return 0;
    case MJPI_ENDGAME :
       return 0;
    case MJPI_CREATEINSTANCE :
       return sizeof(MJAIRuby);
    case MJPI_INITIALIZE :
       MJSendMessage = (UINT (*)(LPVOID,UINT,UINT,UINT))param2;
       return 0;
    case MJPI_YOURNAME :
       return (UINT)"てすと";
    case MJPI_DESTROY :
       return 0;
    }
    return MJR_NOTCARED;
}
