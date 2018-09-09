
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

#include "kcm-lisp-bridge/kcm-lisp-eval.h"

#include "fn-doc/fn-doc.h"

#include <QTextStream>

#include <QDebug>

#include <QEventLoop>


USING_KANS(KCL)

KANS_(Dynamo)

void test_0_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
}

void test_0_s(QString s1)
{
 qDebug() << "s1 = " << s1;
}

QString test_s_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
 qDebug() << "returning: s_ss";
 return "s_ss";
}

QString test_s_s(QString s1)
{
 qDebug() << "s1 = " << s1;
 qDebug() << "returning: s_s";
 return "s_s";
}

int test_i_ss(QString s1, QString s2)
{
 qDebug() << "s1 = " << s1 << "s2 = " << s2;
 qDebug() << "returning: 66";
 return 66;
}

int test_i_s(QString s1)
{
 qDebug() << "s1 = " << s1;
 qDebug() << "returning: 66";
 return 66;
}

void fndoc_test_0_S10_s(Fn_Doc* fnd, QString s1)
{
 qDebug() << "s1 = " << s1;
}

void fndoc_test_0_S10(Fn_Doc* fnd)
{
 qDebug() << "OK";
}

void init_test_functions_kci(Kauvir_Code_Model& kcm)
{

 Kauvir_Type_System* type_system = kcm.type_system();

 KCM_Command_Runtime_Table& table = *kcm.table();

 KCM_Channel_Group g1(kcm.channel_names());
 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-0-ss", g1);
  table.add_s0_declared_function("test-0-ss", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_0_ss));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-0-s", g1);
  table.add_s0_declared_function("test-0-s", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_0_s));
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
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-s-ss", g1);
  table.add_s0_declared_function("test-s-ss", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_s_ss));
  table.note_s0_string_return("test_s_ss");
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-s-s", g1);
  table.add_s0_declared_function("test-s-s", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_s_s));
  table.note_s0_string_return("test_s_s");
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

  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-i-ss", g1);
  table.add_s0_declared_function("test-i-ss", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_i_ss));
  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
     QString()
    );

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );

  KCM_Channel_Group* kcg = table.add_s0_declared_function("test-i-s", g1);
  table.add_s0_declared_function("test-i-s", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&test_i_s));
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

  KCM_Channel_Group* kcg = table.add_s10_declared_function("test-0-S10-s", g1);
  table.add_s10_declared_function("test-0-S10-s", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&fndoc_test_0_S10_s));
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

  KCM_Channel_Group* kcg = table.add_s10_declared_function("test-0-S10", g1);
  table.add_s10_declared_function("test-0-S10", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&fndoc_test_0_S10));
  g1.clear_all();
 }
}

_KANS(Dynamo)

