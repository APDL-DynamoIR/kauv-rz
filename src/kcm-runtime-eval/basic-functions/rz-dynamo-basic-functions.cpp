
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "rz-dynamo-basic-functions.h"


#include "kauvir-code-model/kauvir-code-model.h"

#include "kauvir-code-model/kcm-channel-group.h"

#include "kauvir-type-system/kauvir-type-system.h"

#include "kauvir-code-model/kcm-callable-value.h"

#include "kauvir-runtime/kcm-command-runtime/kcm-command-runtime-table.h"

#include "kauvir-runtime/kcm-command-runtime/kcm-command-runtime-router.h"

#include <QTextStream>

#include <QDebug>

#include <QEventLoop>

KANS_(Dynamo)


void testcall(KCM_Callable_Value* kcv)
{
 KCM_Command_Runtime_Router* kcrr = kcv->kcrr();
 kcrr->run_callable_value(kcv);
}

void* envv(void* kind)
{
 return insert_envv(kind, nullptr);
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

void prn(int num)
{
 qDebug() << num;
}

void prfn(int num)
{
 qDebug() << num;
}


int let_num(int num)
{
 return num;
}

QString let_str(QString str)
{
 return str;
}

void init_basic_functions_kci(Kauvir_Code_Model& kcm)
{
 Kauvir_Type_System* type_system = kcm.type_system();

 KCM_Command_Runtime_Table& table = *kcm.table();

 KCM_Channel_Group g1;
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
  KCM_Channel_Group* kcg = table.add_s0_declared_function("prfn", g1);
  table.add_s0_declared_function("prfn", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&prfn));
  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__kcm_callable_value() ),
     nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("testcall", g1);
  table.add_s0_declared_function("testcall", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&testcall));
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

