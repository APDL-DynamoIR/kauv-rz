
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-dynamo-basic-functions.h"


#include "kauvir-code-model/kauvir-code-model.h"

#include "kauvir-code-model/kcm-channel-group.h"

#include "kauvir-type-system/kauvir-type-system.h"

#include "kauvir-code-model/kcm-callable-value.h"

#include "fn-doc/fn-doc.h"

#include "kauvir-runtime/kcm-command-runtime/kcm-command-runtime-table.h"

#include "kauvir-runtime/kcm-command-runtime/kcm-command-runtime-router.h"

#include "kcm-lisp-bridge/kcm-lisp-eval.h"

#include <QTextStream>

#include <QDebug>

#include <QEventLoop>


USING_KANS(KCL)

KANS_(Dynamo)


void test_call(KCM_Callable_Value* kcv)
{
 KCM_Command_Runtime_Router* kcrr = kcv->kcrr();
 kcrr->run_callable_value(kcv);
}

void test_void()
{
 qDebug() << "OK";
}

void test_dfr_call(quint64 qclo, KCM_Callable_Value* kcv)
{
 quint64 result;
 KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "fixnum");
 qDebug() << result;

 KCM_Command_Runtime_Router* kcrr = kcv->kcrr();
 kcrr->run_callable_value(kcv);
}


void lr(quint64 qclo)
{
 quint64 result = 0;
 KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "nil");
 qDebug() << result;
}

void test_int_call(int num, KCM_Callable_Value* kcv)
{
 qDebug() << num;

 KCM_Command_Runtime_Router* kcrr = kcv->kcrr();
 kcrr->run_callable_value(kcv);
}



void test_dfr(quint64 qclo, quint64 qclo1)
{
 quint64 x = (quint64) qclo;
 quint64 y = (quint64) qclo1;

 void* vx = (void*) x;
 void* vy = (void*) y;

 QPair<KCM_Scope_System*, QPair<int, quint64>>* pr2 =
   (QPair<KCM_Scope_System*, QPair<int, quint64>>*) qclo;

 QPair<KCM_Scope_System*, QPair<int, quint64>>* pr3 =
   (QPair<KCM_Scope_System*, QPair<int, quint64>>*) qclo1;

 quint64 result;
 KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "fixnum");
 qDebug() << result;

 KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo1, result, "fixnum");
 qDebug() << result;
}


int test_find(QString outstr, QString instr)
{
 return outstr.indexOf(instr);
}

void test_calls(KCM_Callable_Value* kcv, KCM_Callable_Value* kcv1)
{
 KCM_Command_Runtime_Router* kcrr = kcv->kcrr();
 kcrr->run_callable_value(kcv);

 KCM_Command_Runtime_Router* kcrr1 = kcv1->kcrr();
 kcrr1->run_callable_value(kcv1);
}


void test_arg_vec_calls(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 for(quint64 qui: args)
 {
  KCM_Callable_Value** kcv = (KCM_Callable_Value**) qui;
  KCM_Command_Runtime_Router* kcrr = (*kcv)->kcrr();
  kcrr->run_callable_value(*kcv);
 }
}

void test_arg_vec_dfr_call(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 int i = 0;
 for(quint64 qui: args)
 {
  if(i % 2)
  {
   KCM_Callable_Value** kcv = (KCM_Callable_Value**) qui;
   KCM_Command_Runtime_Router* kcrr = (*kcv)->kcrr();
   kcrr->run_callable_value(*kcv);
  }
  else
  {
   quint64 qclo = *((quint64*)qui);

   quint64 result;
   KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "fixnum");
   qDebug() << result;
  }
  ++i;
 }
}

void test_arg_vec_str(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 for(quint64 qui: args)
 {
  QString** qs = (QString**) qui;
  qDebug() << **qs;
 }
}

void test_if_then_else(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 int i = 0;
 bool test = false;
 for(quint64 qui: args)
 {
  if(i % 2)
  {
   if(test)
   {
    KCM_Callable_Value** kcv = (KCM_Callable_Value**) qui;
    KCM_Command_Runtime_Router* kcrr = (*kcv)->kcrr();
    kcrr->run_callable_value(*kcv);
    return;
   }
  }
  else
  {
   quint64 qclo = *((quint64*)qui);

   quint64 result;
   KCM_Lisp_Eval::eval_lisp_callable_deferred_value(qclo, result, "bool");
   qDebug() << result;
   test = (bool) result;
  }
  ++i;
 }
}

void if_t_e(quint64 args_ptr)
{
 test_if_then_else(args_ptr);
}

QString fndoc_test_summary(Fn_Doc* fnd)
{
 QString summ = fnd->test_summary();
 return summ;
}

void* envv(void* kind)
{
 if(kind)
 {
  qDebug() << "Kind: " << *(QString*)kind;
  return insert_envv(kind, nullptr);
 }
 else
 {
  qDebug() << "In envv: Return kind could not be determined.";
  return nullptr;
 }
}

void* insert_envv(void* kind, void* test)
{
 static QMap<QString, void*> hold;
 QString* k = reinterpret_cast<QString*>(kind);
 if(test)
 {
  hold[*k] = test;
 }
 return hold.value(*k);
}

void prs(QString str)
{
 qDebug() << str;
}

void test_prss(QString str1, QString str2)
{
 qDebug() << str1;
 qDebug() << str2;
}


void prn(int num)
{
 qDebug() << num;
}


void pr_two_n(int num, int n1)
{
 qDebug() << num << ", " << n1;
}

void prdn(quint64 num, quint64 n1)
{
 qDebug() << num << ", " << n1;
}

int let_num(int num)
{
 return num;
}

QString let_str(QString str)
{
 return str;
}


void fndoc_read(Fn_Doc* fnd, QString fn)
{
 qDebug() << "Reading " << fn << " ...";
 fnd->read(fn);
}



void init_basic_functions_kci(Kauvir_Code_Model& kcm)
{
 init_test_functions_kci(kcm);

 Kauvir_Type_System* type_system = kcm.type_system();

 KCM_Command_Runtime_Table& table = *kcm.table();

 KCM_Channel_Group g1(kcm.channel_names());
 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("prs", g1);
  table.add_s0_declared_function("prs", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&prs));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("test_prss", g1);
  table.add_s0_declared_function("test_prss", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_prss));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-find", g1);
  table.add_s0_declared_function("test-find", kcg, reinterpret_cast<s0_fn1_p_p_type>
                              (&test_find));
  g1.clear_all();
 }

 {
  g1.add_sigma_carrier(
    {kcm.get_kcm_type_by_type_name( "Fn_Doc*" ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s10_declared_function("read", g1);
  table.add_s10_declared_function("read", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&fndoc_read));
  g1.clear_all();
 }


 {
  g1.add_sigma_carrier(
    {kcm.get_kcm_type_by_type_name( "Fn_Doc*" ), nullptr},
     QString()
    );

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s10_declared_function("test-summary", g1);
  table.add_s10_declared_function("test-summary", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&fndoc_test_summary));
  table.note_s10_string_return("test_summary");
  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-arg-vec-calls", g1);
  table.add_s0_declared_function("test-arg-vec-calls", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_arg_vec_calls));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-arg-vec-str", g1);
  table.add_s0_declared_function("test-arg-vec-str", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_arg_vec_str));
  g1.clear_all();
 }

 {
  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-void", g1);
  table.add_s0_declared_function("test-void", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_void));
  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-arg-vec-dfr-call", g1);
  table.add_s0_declared_function("test-arg-vec-dfr-call", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_arg_vec_dfr_call));
  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-if-then-else", g1);
  table.add_s0_declared_function("test-if-then-else", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_if_then_else));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("if-t-e", g1);
  table.add_s0_declared_function("if-t-e", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&if_t_e));
  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("prn", g1);
  table.add_s0_declared_function("prn", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&prn));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("pr-two-n", g1);
  table.add_s0_declared_function("pr-two-n", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&pr_two_n));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ), nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("prdn", g1);
  table.add_s0_declared_function("prdn", kcg, reinterpret_cast<_s0_fn1_p_type>
                              (&prdn));
  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-call", g1);
  table.add_s0_declared_function("test-call", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_call));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ),
     nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ),
     nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-dfr", g1);
  table.add_s0_declared_function("test-dfr", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_dfr));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ),
     nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s0_declared_function("lr", g1);
  table.add_s0_declared_function("lr", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&lr));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-calls", g1);
  table.add_s0_declared_function("test-calls", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_calls));
  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u64() ),
     nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-dfr-call", g1);
  table.add_s0_declared_function("test-dfr-call", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_dfr_call));
  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ),
     nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-int-call", g1);
  table.add_s0_declared_function("test-int-call", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_int_call));
  g1.clear_all();
 }



 {
  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("let_num", g1);
  table.add_s0_declared_function("let_num", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&let_num));
  g1.clear_all();
 }

 {
  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("let_str", g1);
  table.add_s0_declared_function("let_str", kcg, reinterpret_cast<s0_fn1_p__s_type>
                              (&let_str));
  table.note_s0_string_return("let_str");
  g1.clear_all();

 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );
  const KCM_Type_Object* kto = kcm.get_kcm_type_by_type_name("u64");
  g1.add_result_carrier({kto, nullptr},QString());
  KCM_Channel_Group* kcg = table.add_s0_declared_function("envv", g1);
  table.add_s0_declared_function("envv", kcg, reinterpret_cast<s0_fn1_p_type>
                               (&envv));
  g1.clear_all();
 }


}

_KANS(Dynamo)

