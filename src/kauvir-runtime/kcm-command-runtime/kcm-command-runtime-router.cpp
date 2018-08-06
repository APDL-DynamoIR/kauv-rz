
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-command-runtime-router.h"

#include "kcm-command-runtime-router-qob.h"

#include "kcm-command-package/kcm-command-package.h"
#include "kcm-command-runtime-argument.h"

#include "kauvir-kcm/kauvir-type-system/kauvir-universal-class.h"

#include "kcm-command-runtime-table.h"
#include "kauvir-kcm/kauvir-code-model/kcm-type-object.h"

#include "kcm-runtime-eval/kcm-scopes/kcm-scope-system.h"

#include "kauvir-code-model/kcm-callable-value.h"

#include "kauvir-code-model/kcm-proxy-scope.h"

#include "kauvir-code-model/kcm-expression.h"

#include "kauvir-code-model/kcm-channel-bridge.h"

#include "kcm-lisp-bridge/kcm-lisp-bridge.h"

#include "kcm-lisp-bridge/kcm-lisp-eval.h"

#include <QDebug>

USING_KANS(KCL)


USING_KANS(CMD)


KCM_Command_Runtime_Router::KCM_Command_Runtime_Router(KCM_Command_Runtime_Table& table,
  KCM_Scope_System* scopes, KCM_Proxy_Scope* proxy_scope,
  QString& string_result)
  :  sigma_argument_(nullptr), kcm_expression_(nullptr),
     result_type_object_(nullptr), string_result_(string_result),
     table_(table), scopes_(scopes), proxy_scope_(proxy_scope), call_result_(0),
     reflection_convention_(Reflection_Conventions::N_A),
     string_result_code_(0)
{

}

QString KCM_Command_Runtime_Router::return_type_name_strip_namespace()
{
 int li = return_type_name().lastIndexOf("::");
 if(li != -1)
 {
  return return_type_name().mid(li + 2);
 }
 else
 {
  return return_type_name();
 }
}

QObject* KCM_Command_Runtime_Router::this_object()
{
 return static_cast<QObject*>(argument_info_[0].void_argument);
}

KCM_Command_Runtime_Argument* KCM_Command_Runtime_Router::parse_carrier_to_argument(KCM_Carrier& kcc, int pos)
{
 KCM_Command_Runtime_Argument* result;
 QString sym = kcc.symbol();
 const KCM_Type_Object* kto = kcc.type_object();
 if(kto)
 {
  result = new KCM_Command_Runtime_Argument;
  const Kauvir_Type_Object* kvto =  kto->kauvir_type_object();
  result->set_type_name(kvto->name());

  result->set_qmo(kvto->qmo());
  result->set_pqmo(kvto->pqmo());

  void* k = kcc.symbol_as_pointer();
  QString* qs = reinterpret_cast<QString*>(k);

  if(kcc.flags.string_rep)
  {
   result->set_raw_value(kcc.symbol_as_pointer());
   result->set_value_classification(KCM_Command_Runtime_Argument::Value_Classification::Generic_Ptr);
  }
  else
  {
   result->set_bind_code(sym);
   result->set_raw_value(kcc.symbol_as_pointer());
   result->set_value_classification(KCM_Command_Runtime_Argument::Value_Classification::Generic_Ptr);
  }

 }
 else if(kcc.flags.string_rep)
 {
  result = new KCM_Command_Runtime_Argument;
  result->set_type_name("QString");

  void* k = kcc.symbol_as_pointer();
  QString* qs = reinterpret_cast<QString*>(k);

  result->set_raw_value(kcc.symbol_as_pointer());
  result->set_value_classification(KCM_Command_Runtime_Argument::Value_Classification::Generic_Ptr);
 }
 else if(kcc.declaration_scope())
 {
  // // currently declaration_scope is only used
   // as a signal that kcc is scoped ...
  result = new KCM_Command_Runtime_Argument;
  const KCM_Type_Object* rkto;

  quint64 qv =  KCM_Lisp_Bridge::get_value_of_symbol(kcc.symbol(), scopes_, &rkto);

  if(rkto)
  {
   result->set_type_name(rkto->kauvir_type_object()->name());
  }

  result->set_raw_value( (void*) qv);
  result->set_value_classification(KCM_Command_Runtime_Argument::Value_Classification::QObject_Ptr);
 }
 else
 {
  result = new KCM_Command_Runtime_Argument;
  QString qs = kcc.symbol();
  result->set_bind_code(qs);
 }
 return result;
}

QString KCM_Command_Runtime_Router::return_type_name()
{
 if(result_type_object_)
  return result_type_object_->kauvir_type_object()->name();
 return QString();
}


void KCM_Command_Runtime_Router::parse_command_package(KCM_Command_Package* cpkg)
{
 kcm_expression_ = cpkg->kcm_expression();

 KCM_Channel& sigma = cpkg->sigma();
 if(!sigma.carriers().isEmpty())
 {
  KCM_Carrier s1;
  sigma.get_carrier_at_position(0, s1);
  KCM_Command_Runtime_Argument* s1a = new KCM_Command_Runtime_Argument;
  if(s1.flags.string_rep)
  {
   s1a->set_raw_value(s1.symbol_as_pointer());
   s1a->set_value_classification(KCM_Command_Runtime_Argument::Value_Classification::Generic_Ptr);
  }
  else
  {
   s1a->set_bind_code(s1.symbol());
  }
  sigma_argument_ = s1a;
 }
 KCM_Channel& fuxe = cpkg->fuxe();
 if(fuxe.carriers().isEmpty())
 {
  // no function name!
  return;
 }
 KCM_Channel& result = cpkg->result();
 if(!result.carriers().isEmpty())
 {
  KCM_Carrier r1;
  result.get_carrier_at_position(0, r1);
  result_type_object_ = r1.type_object();
 }

 KCM_Carrier kcc;
 fuxe.get_carrier_at_position(0, kcc);
 fuxe_name_ = kcc.symbol();


 KCM_Channel& lambda = cpkg->lambda();

 int size = lambda.carriers().size();
 for(int i = 0; i < size; ++i)
 {
  KCM_Carrier* kcc = lambda.get_carrier_at_position(i);
  KCM_Command_Runtime_Argument* la = parse_carrier_to_argument(*kcc, i);
  lambda_arguments_.push_back(la);
 }
}

void KCM_Command_Runtime_Router::proceed()
{
 if(sigma_argument_)
 {
  proceed_s1();
 }
 else
 {
  proceed_s0();
 }
}

KCM_Channel_Group* KCM_Command_Runtime_Router::get_channel_group()
{
 if(kcm_expression_)
 {
  return kcm_expression_->channel_group();
 }
}

void KCM_Command_Runtime_Router::proceed_s0()
{
 void* result;
 switch(lambda_arguments_.size())
 {
 case 0:
  proceed_s0_0();
  break;
 case 1:
  proceed_s0_1(&result);
  break;
 case 2:
  proceed_s0_2();
  break;
 default:
  break;
 }
 if(result)
 {
  call_result_ = (quint64) result;
 }
}

void KCM_Command_Runtime_Router::proceed_s1()
{
 void* result = nullptr;
 QString code = sigma_argument_->bind_code();
 const KCM_Type_Object* kto = nullptr;
 const KCM_Type_Object* ckto = nullptr;
 QString encoded_value;
 void* raw_value = scopes_->find_raw_value_from_current_scope(code, kcm_expression_, kto, ckto, encoded_value);

 switch(lambda_arguments_.size())
 {
 case 0:
  proceed_s1_0(&result, raw_value);
  break;
 case 1:
  proceed_s1_1(&result, raw_value);
  break;
 case 2:
  proceed_s1_2(&result, raw_value);
  break;
 default:
  break;
 }
 if(result)
 {
  call_result_ = (quint64) result;
 }
 else
 {

 }
}

void KCM_Command_Runtime_Router::proceed_s1_2(void** pResult, void* raw_value)
{
 void* result = nullptr;
 s1_fng_type fn = table_.find_s1_declared_function_0(fuxe_name_, nullptr, &result_type_object_);
 if(fn)
 {
  // raw_value is quint64* standing for void** ...
  Kauvir_Universal_Class* uo = (Kauvir_Universal_Class*) (* (void**)raw_value) ;
  void* la0 = nullptr;
  quint64 mem = 0;
  QString qs_mem;
  QString* pqs_mem = &qs_mem;

  void* la1 = nullptr;
  quint64 mem1 = 0;
  QString qs_mem1;
  QString* pqs_mem1 = &qs_mem1;

  FN_Codes fnc = result_type_object_? FN_Codes::RET_CC:FN_Codes::NOR_CC;

  int ptr_depth1;
  int ptr_depth2;
  FN_Codes fnc1 = check_init_raw_value(lambda_arguments_[0], fnc, mem, pqs_mem, la0, ptr_depth1);
  FN_Codes fnc2 = check_init_raw_value(lambda_arguments_[1], fnc1, mem1, pqs_mem1, la1, ptr_depth2);

  if(result_type_object_)
  {
   fn2_pp_wrtn_type pfn = (fn2_pp_wrtn_type) fn;
   result = (uo->*pfn)( (void*) *((quint64*) la0),  (void*) *((quint64*) la1));
  }
  else
  {
   fn2_pp_type pfn = (fn2_pp_type) fn;
   (uo->*pfn)( (void*) *((quint64*) la0),  (void*) *((quint64*) la1));
  }

  // // here?

  if(pResult)
  {
   *pResult = result;
  }
 }
 else
 {
  reflection_convention_ = Reflection_Conventions::Qt_Meta_Object;
  do_invoke_method(lambda_arguments_);
 }
}

void KCM_Command_Runtime_Router::run_callable_value(KCM_Callable_Value* kcv)
{
 KCM_Lisp_Eval::run_source_function(*this, (quint64) kcv->as_pVoid() );
}


KCM_Command_Runtime_Router::FN_Codes KCM_Command_Runtime_Router::check_init_raw_value(KCM_Command_Runtime_Argument* kcra,
  FN_Codes fnc, quint64& mem, QString* qs_mem, void*& result, int& ptr_depth)
{
 const KCM_Type_Object* kto;
 if(kcra->bind_code().isEmpty())
 {
  QString* qs = (QString*) kcra->raw_value();
  if(kcra->type_name() == "str")
  {
   *qs_mem = *qs;
   result = &qs_mem;
   ptr_depth = 2;
   return add_string_cast_to_fn_code(fnc);
  }
  else
  {
   // // assume always a string rep to number?
   mem = qs->toLongLong();
   result = &mem;
   ptr_depth = 1;
   return add_ptr_cast_to_fn_code(fnc);
  }
 }
 else if(quint64 temp = scopes_->find_temporary_bridge_value(kcra->bind_code(), kto))
 {
  // // actually need to check of kto is anon fdef ...
  KCM_Callable_Value* kcv = (KCM_Callable_Value*) temp;
  kcv->set_kcrr(this);
  mem = (quint64) kcv;
  result = &mem;
 }
 else
 {
  const KCM_Type_Object* kto;
  const KCM_Type_Object* ckto;
  QString encoded_value;

  const KCM_Type_Object* xkto;
  QString proxy_coords_code = proxy_scope_->find_proxy_coords_for_symbol_name(kcra->bind_code(), xkto);

  if(proxy_coords_code.isEmpty())
  {
   quint64* rv = scopes_->find_raw_value_from_current_scope(kcra->bind_code(), kcm_expression_, kto, ckto, encoded_value);

   if(rv == (quint64*) &encoded_value)
   {
    if(!kto)
    {
     // // means nested_expression_store could not find the pair ...
    }

    else if(kto->is_lisp_list_like())
    {
     QString key = encoded_value; //? ".1.";
     quint64 lisp_val = scopes_->find_held_lisp_list_from_current_scope(key);
     KCM_Lisp_Eval::run_held_lisp_list(lisp_val, mem);
     result = &mem;
     //mem = lisp_val;
    }
    // need to parse the encoded ...
    else if(kto->is_string_like())
    {
     // // is this OK given the QString** stuff?
     *qs_mem = encoded_value;
     result = qs_mem;
    }
    else
    {
     // // probably have to deal with multiple types ...
     mem = encoded_value.toInt();
     result = &mem;
    }
   }
   else if(rv)
   {
    // what about str? ...
    mem = *rv;
    result = &mem;
   }
   else
   {
    result = nullptr;
   }
   return add_ptr_cast_to_fn_code(fnc);
  }
  else
  {
   KCM_Channel_Bridge* bridge = proxy_scope_->kcm_channel_bridge();
   KCM_Carrier* kcr = bridge->get_carrier_by_proxy_coords_code(proxy_coords_code);

   const KCM_Type_Object* kto = kcr->type_object();

   // // any issue of checking between kto and xkto?
    //   ... xkto;

   if(kto->is_string_like())
   {
    //    Again the QString** stuff: this only gets to QString* ...
    //    QString encoded_value = kcr->symbol();
    //    qs_mem = encoded_value;
    //    result = &qs_mem;

    QString* pqs = kcr->symbol_as_pointer();
    mem = (quint64) pqs;
    result = &mem;
   }
   else
   {
    // // now this only works for ints ...
    QString encoded_value = kcr->symbol();
    mem = encoded_value.toInt();
    result = &mem;
   }
  }

 }
}

KCM_Command_Runtime_Router::FN_Codes KCM_Command_Runtime_Router::add_string_cast_to_fn_code(FN_Codes fnc)
{
 static QMap<FN_Codes,FN_Codes> static_map {{
#define TEMP_MACRO(X, Y) {FN_Codes::NOR_##X, FN_Codes::NOR_##Y}, {FN_Codes::RET_##X, FN_Codes::RET_##Y},
   TEMP_MACRO(C,S)
   TEMP_MACRO(CC,SC)
   TEMP_MACRO(PC,PS)
   TEMP_MACRO(RC,RS)
   TEMP_MACRO(SC,SS)
#undef TEMP_MACRO
   }};
 return static_map.value(fnc, FN_Codes::N_A);
}

KCM_Command_Runtime_Router::FN_Codes KCM_Command_Runtime_Router::add_ptr_cast_to_fn_code(FN_Codes fnc)
{
 static QMap<FN_Codes,FN_Codes> static_map {{
#define TEMP_MACRO(X, Y) {FN_Codes::NOR_##X, FN_Codes::NOR_##Y}, {FN_Codes::RET_##X, FN_Codes::RET_##Y},
   TEMP_MACRO(C,P)
   TEMP_MACRO(CC,SP)
   TEMP_MACRO(PC,PP)
   TEMP_MACRO(RC,RP)
   TEMP_MACRO(SC,SP)
#undef TEMP_MACRO
   }};
 return static_map.value(fnc, FN_Codes::N_A);
}


void KCM_Command_Runtime_Router::proceed_s1_1(void** pResult, void* raw_value)
{
 void* result = nullptr;
 s1_fng_type fn = table_.find_s1_declared_function_0(fuxe_name_, nullptr, &result_type_object_);
 if(fn)
 {
  // raw_value is quint64* standing for void** ...
  Kauvir_Universal_Class* uo = (Kauvir_Universal_Class*) (* (void**)raw_value) ;
  void* la0 = nullptr;
  quint64 mem = 0;
  QString qs_mem;
  QString* pqs_mem = &qs_mem;

  FN_Codes fnc = result_type_object_? FN_Codes::RET_C:FN_Codes::NOR_C;

  int ptr_depth = 0;
  FN_Codes fnc1 = check_init_raw_value(lambda_arguments_[0], fnc, mem, pqs_mem, la0, ptr_depth);

  switch(fnc1)
  {
  case FN_Codes::RET_P:
   {
    fn1_p_wrtn_type pfn = (fn1_p_wrtn_type) fn;
    result = (uo->*pfn)((void*) la0);
   }
   break;
  case FN_Codes::NOR_P:
   {
    s1_fn1_p_type pfn = (s1_fn1_p_type) fn;
    (uo->*pfn)( (void*) *((quint64*) la0) );
   }
   break;

  case FN_Codes::RET_S:
   {
    fn1_s_wrtn_type pfn = (fn1_s_wrtn_type) fn;
    result = (uo->*pfn)(qs_mem);
   }
   break;
  case FN_Codes::NOR_S:
   {
    fn1_s_type pfn = (fn1_s_type) fn;
    (uo->*pfn)(qs_mem);
   }
   break;

  default: break;
  }

  // // does this go here?
  if(pResult)
  {
   *pResult = result;
  }

 }
 else
 {
  reflection_convention_ = Reflection_Conventions::Qt_Meta_Object;
  do_invoke_method(lambda_arguments_);
 }


}

void KCM_Command_Runtime_Router::proceed_s1_0(void** pResult, void* raw_value)
{
 void* result = nullptr;
 s1_fng_type fn = table_.find_s1_declared_function_0(fuxe_name_, nullptr, &result_type_object_);
 if(fn)
 {
  // raw_value is quint64* standing for void** ...
  Kauvir_Universal_Class* uo = (Kauvir_Universal_Class*) (* (void**)raw_value) ;
  if(result_type_object_)
  {
   result = (uo->*fn)();
  }
  else
  {
   (uo->*fn)();
  }
 }
 if(pResult)
 {
  *pResult = result;
 }
 else
 {
  reflection_convention_ = Reflection_Conventions::Qt_Meta_Object;
  do_invoke_method(lambda_arguments_);
 }
}


//?
void KCM_Command_Runtime_Router::proceed_s0_0()
{

}

void KCM_Command_Runtime_Router::proceed_s0_2()
{

}

void KCM_Command_Runtime_Router::proceed_s0_1(void** pResult)
{
 void* result = nullptr;
 s0_fn1_p_type fn = table_.find_s0_declared_function_1(fuxe_name_, nullptr, &result_type_object_);
 bool sr = table_.s0_string_return(fuxe_name_);
 if(fn)
 {
   // raw_value is quint64* standing for void** ...
  void* la0 = nullptr;
  quint64 mem = 0;
  QString qs_mem;
  QString* pqs_mem = &qs_mem;

  FN_Codes fnc = result_type_object_? FN_Codes::RET_CC:FN_Codes::NOR_CC;

  int ptr_depth = 0;
  FN_Codes fnc1 = check_init_raw_value(lambda_arguments_[0], fnc, mem, pqs_mem, la0, ptr_depth);

  // for review ...
  QString** qs = reinterpret_cast<QString**>(la0);


  QString xx = "ok";
  void* arg = (void*) *((quint64*) la0);

  if(result_type_object_)
  {
   if(sr)
   {
    s0_fn1_p__s_type sfn = (s0_fn1_p__s_type) fn;
    QString str_result = sfn( (void*) *((quint64*) la0) );
    hold_string_result(str_result);
   }
   else
   {
    result = fn( (void*) *((quint64*) la0) );
   }
  }
  else
  {
   fn( (void*) *((quint64*) la0) );
  }
 }
 if(pResult)
 {
  *pResult = result;
 }
}

void KCM_Command_Runtime_Router::do_invoke_method(QVector<KCM_Command_Runtime_Argument*>& args)
{
 if(reflection_convention_ == Reflection_Conventions::Qt_Meta_Object)
 {
  argument_info_.resize(args.size() + 1);
  argument_info_[0].qmo = sigma_argument_->qmo();
  argument_info_[0].qmt = sigma_argument_->qmt();
 }
 else
 {
  argument_info_.resize(args.size());
 }
 QVector<quint64> store;
 init_argument_info(args, store);

 QString rtn = return_type_name();

 if(rtn.isEmpty())
 {
  return_type_code_ = Arg_Type_Codes::No_Return;
 }
 else
 {
  return_type_code_ = parse_return_type_code(rtn);
 }


#define MAX_UC_ARG_COUNT 2

 switch(args.size())
 {
//?
 case 0: Do_Invoke_Method_<0, 0 <= MAX_UC_ARG_COUNT>::run(this, args); break;
//?
 case 1: Do_Invoke_Method_<1, 1 <= MAX_UC_ARG_COUNT>::run(this, args); break;
 case 2: Do_Invoke_Method_<2, 2 <= MAX_UC_ARG_COUNT>::run(this, args); break;
 }

 // for return...
 switch(return_type_code_)
 {
 case Arg_Type_Codes::No_Return:
  break;
 case Arg_Type_Codes::Int:
  break;
 default:
  break;
 }

}

void KCM_Command_Runtime_Router::init_argument_info(QVector<KCM_Command_Runtime_Argument*>& args,
  QVector<quint64>& store)
{
 store.resize(args.size());
 switch(reflection_convention_)
 {
 case Reflection_Conventions::Qt_Meta_Object:
  init_argument_info_qob(args, store);
  break;
 case Reflection_Conventions::Universal_Class:
  init_argument_info_uc(args, store);
  break;
 default:
  break;
 }
}


KCM_Command_Runtime_Router::QOB_Argument_Conventions KCM_Command_Runtime_Router::qob_argument_convention_from_type_name(QString tn)
{
 static QMap<QString, KCM_Command_Runtime_Router::QOB_Argument_Conventions> static_map {{
   {"u32", KCM_Command_Runtime_Router::QOB_Argument_Conventions::Value_From_QString},
   {"str", KCM_Command_Runtime_Router::QOB_Argument_Conventions::QString_Direct},
  }};

 return static_map.value(tn, KCM_Command_Runtime_Router::QOB_Argument_Conventions::N_A);
}

void KCM_Command_Runtime_Router::init_argument_info_qob(QVector<KCM_Command_Runtime_Argument*>& args,
  QVector<quint64>& store)
{
 for(int i = 0; i < args.size(); ++i)
 {
  KCM_Command_Runtime_Argument* arg = args[i];
  //int i = j + 1;
  //QString internal_type_string = arg->qob_reflection_type_name();

  QString tn = arg->type_name();
  QOB_Argument_Conventions ac;

  if(tn.isEmpty())
  {
   // //  others?
   if(arg->value_classification() == KCM_Command_Runtime_Argument::Value_Classification::QObject_Ptr)
   {
    ac = QOB_Argument_Conventions::QObject_Direct;
   }
  }
  else
  {
   ac = qob_argument_convention_from_type_name(tn);
  }
  if(ac == QOB_Argument_Conventions::N_A)
  {
   if(arg->value_classification() == KCM_Command_Runtime_Argument::Value_Classification::QObject_Ptr)
   {
    ac = QOB_Argument_Conventions::QObject_Direct;
   }
  }

  QString abc = arg->bind_code();
  if(!abc.isEmpty())
  {
   const KCM_Type_Object* kto;
   const KCM_Type_Object* ckto;
   QString encoded_value;
   quint64* rv = scopes_->find_raw_value_from_current_scope(abc, kcm_expression_, kto, ckto, encoded_value);
   store[i] = *rv;
   argument_info_[i + 1].qob_convention = ac;
   argument_info_[i + 1].void_argument = &store[i];
   continue;
  }

  switch(ac)
  {
  case QOB_Argument_Conventions::Value_From_QString:
   {
    QString* qs = (QString*) arg->raw_value();
    int qsi = qs->toInt();
    store[i] = qsi;
    argument_info_[i + 1].qob_convention = ac;
    argument_info_[i + 1].void_argument = &store[i];
   }
   break;

  case QOB_Argument_Conventions::QString_Direct:
   {
    QString* qs = (QString*) arg->raw_value();
    store[i] = (quint64) qs;
    argument_info_[i + 1].qob_convention = ac;
    argument_info_[i + 1].void_argument = (void*) store[i];
   }
   break;

  case QOB_Argument_Conventions::QObject_Direct:
   {
    void* pv = arg->raw_value();
    store[i] = (quint64) pv;
    argument_info_[i + 1].qob_convention = ac;
    argument_info_[i + 1].void_argument = (void*) store[i];
   }
   break;

  }
 }

 QString bc = sigma_argument_->bind_code();
 if(bc.isEmpty())
 {
  argument_info_[0].void_argument = sigma_argument_->raw_value();
 }
 else
 {
  const KCM_Type_Object* kto;
  const KCM_Type_Object* ckto;
  QString encoded_value;
  quint64* rv = scopes_->find_raw_value_from_current_scope(bc, kcm_expression_, kto, ckto, encoded_value);
  argument_info_[0].void_argument = (void*) *rv;
 }
}

void KCM_Command_Runtime_Router::init_argument_info_uc(QVector<KCM_Command_Runtime_Argument*>& args,
  QVector<quint64>& store)
{
}


template<int Arg_Count>
void KCM_Command_Runtime_Router::Do_Invoke_Method<Arg_Count>
 ::run(KCM_Command_Runtime_Router* this_, QVector<KCM_Command_Runtime_Argument*>& args)
{
  switch(this_->reflection_convention_)
  {//?
//  case Reflection_Conventions::Universal_Class:
//   Do_Invoke_Method__Cast_Schedule__UC__Cast_<Arg_Count>
//     ::Type::template run<QObject*, typename Type_List__All_Cast_Needed<Arg_Count>::Type,
//     typename FN_Type_Arg_Count<Arg_Count>::Type
//     >
//      (this_->function_name(),
//      this_->this_object(), 0, *this_,
//      this_->argument_info(), args);
//   break;

  case Reflection_Conventions::Qt_Meta_Object:
   Do_Invoke_Method__Cast_Schedule__QOB__Cast_<Arg_Count>
     ::Type::template run<QObject*, typename Type_List__All_Cast_Needed<Arg_Count>::Type //,
     >
      (this_->fuxe_name(),
      this_->this_object(), 0, *this_,
      this_->argument_info(), args);
   break;
  }
}
