
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-channel-group.h"

#include "kcm-type-object.h"

#include "kans.h"

USING_KANS(KCM)

KCM_Channel_Group::KCM_Channel_Group()
  :  furnisher_(nullptr)
{
 set_kinds();
}

KCM_Channel_Group::KCM_Channel_Group(const KCM_Channel_Group& rhs)
  :  furnisher_(rhs.furnisher())
{
 lambda_ = rhs.lambda();
 result_ = rhs.result();
 sigma_ = rhs.sigma();

 fuxe_ = rhs.fuxe();
}


void KCM_Channel_Group::set_kinds()
{
 fuxe_.set_kind(KCM_Channel::Kinds::Fuxe);
 lambda_.set_kind(KCM_Channel::Kinds::Lambda);
 sigma_.set_kind(KCM_Channel::Kinds::Sigma);
 array_.set_kind(KCM_Channel::Kinds::Array);
 capture_.set_kind(KCM_Channel::Kinds::Capture);
 gamma_.set_kind(KCM_Channel::Kinds::Gamma);
 result_.set_kind(KCM_Channel::Kinds::Result);

 preempt_.set_kind(KCM_Channel::Kinds::Preempt_Any);

}

void KCM_Channel_Group::clear_all_but_sigma()
{
 fuxe_ = KCM_Channel();
 lambda_ = KCM_Channel();
 capture_ = KCM_Channel();
 array_ = KCM_Channel();
 gamma_ = KCM_Channel();
 result_ = KCM_Channel();
 preempt_ = KCM_Channel();
 set_kinds();
}

void KCM_Channel_Group::clear_all()
{
 fuxe_ = KCM_Channel();
 lambda_ = KCM_Channel();
 sigma_ = KCM_Channel();
 array_ = KCM_Channel();
 capture_ = KCM_Channel();
 gamma_ = KCM_Channel();
 result_ = KCM_Channel();
 preempt_ = KCM_Channel();
 set_kinds();
}

void KCM_Channel_Group::add_fuxe_carrier(const KCM_Type_Object* type_object)
{
 fuxe_.add_carrier({type_object, nullptr}, KCM_Carrier::Effect_Protocols::Run_Chief, QString());
}

void KCM_Channel_Group::add_fuxe_carrier(QString symbol_name)
{
 fuxe_.add_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Run_Chief, symbol_name);
}


void KCM_Channel_Group::add_result_carrier(kcm_type_object_pair_type tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol_name)
{
 result_.add_carrier(tos, ep, symbol_name);
}

void KCM_Channel_Group::add_preempt_carrier(kcm_type_object_pair_type tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol_name)
{
 preempt_.add_carrier(tos, ep, symbol_name);
}

void KCM_Channel_Group::add_lambda_carrier(kcm_type_object_pair_type tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol_name, KCM_Runtime_Scope* scope)
{
 lambda_.add_carrier(tos, ep, symbol_name, scope);
}

void KCM_Channel_Group::add_array_carrier(kcm_type_object_pair_type tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol_name)
{
 array_.add_carrier(tos, ep, symbol_name);
}

void KCM_Channel_Group::add_sigma_carrier(kcm_type_object_pair_type tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol_name)
{
 sigma_.add_carrier(tos, ep, symbol_name);
}

void KCM_Channel_Group::add_sigma_carrier_via_symbol_with_cast(QString value_name,
  const KCM_Type_Object* kto, const KCM_Type_Object* ckto)
{
 add_sigma_carrier({kto, ckto}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_capture_carrier(kcm_type_object_pair_type tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol_name)
{
 capture_.add_carrier(tos, ep, symbol_name);
}

void KCM_Channel_Group::add_gamma_carrier(kcm_type_object_pair_type tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol_name)
{
 gamma_.add_carrier(tos, ep, symbol_name);
}

int KCM_Channel_Group::get_lambda_byte_code()
{
 int result = 9;
 for(const KCM_Carrier& c : lambda_.carriers())
 {
  result *= 10;
  result += c.type_object()->byte_code();
 }
 return result;
}

void KCM_Channel_Group::add_lambda_carrier_from_result_channel(int level, int index)
{
 add_lambda_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted,
   QString(":##%1-%2").arg(level).arg(index));
}

void KCM_Channel_Group::add_lambda_carrier_via_symbol_with_cast(QString value_name, const KCM_Type_Object* type_object)
{
 add_lambda_carrier({nullptr, type_object}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_array_carrier_via_symbol_with_cast(QString value_name, const KCM_Type_Object* type_object)
{
 add_array_carrier({nullptr, type_object}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_literal_with_cast(QString value_name, const KCM_Type_Object* type_object)
{
 add_lambda_carrier({nullptr, type_object}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_array_carrier_via_literal_with_cast(QString value_name, const KCM_Type_Object* type_object)
{
 add_array_carrier({nullptr, type_object}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_bind_symbol(const KCM_Type_Object* kto, QString symbol_name)
{
 add_lambda_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, symbol_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_symbol(const KCM_Type_Object* kto, QString value_name)
{
 add_lambda_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_typed_scoped_symbol(const KCM_Type_Object* kto,
   QString value_name, KCM_Runtime_Scope* scope)
{
 add_lambda_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name, scope);
}

void KCM_Channel_Group::add_lambda_carrier_via_symbol(QString value_name)
{
 add_lambda_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_scoped_symbol(QString symbol_name, KCM_Runtime_Scope* scope)
{
 add_lambda_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, symbol_name, scope);
}

void KCM_Channel_Group::add_sigma_carrier_via_symbol(QString value_name)
{
 add_sigma_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}


void KCM_Channel_Group::add_array_carrier_via_symbol(QString value_name)
{
 add_array_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Unrestricted, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_typed_opaque_value(const KCM_Type_Object* kto, QString value_encoding)
{
 add_lambda_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_encoding);
}

void KCM_Channel_Group::add_lambda_carrier_via_typed_literal(const KCM_Type_Object* kto, QString value_name)
{
 add_lambda_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_sigma_carrier_via_typed_literal(const KCM_Type_Object* kto, QString value_name)
{
 add_sigma_carrier({kto, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_lambda_carrier_via_typed_literal_with_cast(const KCM_Type_Object* kto,
  QString value_name, const KCM_Type_Object* ckto)
{
 add_lambda_carrier({kto, ckto}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_sigma_carrier_via_typed_literal_with_cast(const KCM_Type_Object* kto,
  QString value_name, const KCM_Type_Object* ckto)
{
 add_sigma_carrier({kto, ckto}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}


void KCM_Channel_Group::add_lambda_carrier_via_literal(QString value_name)
{
 add_lambda_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_sigma_carrier_via_literal(QString value_name)
{
 add_sigma_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_array_carrier_via_literal(QString value_name)
{
 add_array_carrier({nullptr, nullptr}, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_lambda_carrier(kcm_type_object_pair_type tos, QString value_name)
{
 add_lambda_carrier(tos, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_array_carrier(kcm_type_object_pair_type tos, QString value_name)
{
 add_array_carrier(tos, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_sigma_carrier(kcm_type_object_pair_type tos, QString value_name)
{
 add_sigma_carrier(tos, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_capture_carrier(kcm_type_object_pair_type tos, QString value_name)
{
 add_capture_carrier(tos, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_gamma_carrier(kcm_type_object_pair_type tos, QString value_name)
{
 add_gamma_carrier(tos, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_result_carrier(kcm_type_object_pair_type tos, QString value_name)
{
 add_result_carrier(tos, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::add_preempt_carrier(kcm_type_object_pair_type tos, QString value_name)
{
 add_preempt_carrier(tos, KCM_Carrier::Effect_Protocols::Const_Literal, value_name);
}

void KCM_Channel_Group::report(QTextStream& qts, Kauvir_Code_Model& kcm,
  KCM_Report_Syntax& kcrs, KCM_Channel::Code_Environments cenv)
{
 fuxe_.report(qts, kcm, kcrs, cenv);
 if(array_.carriers().isEmpty())
 {
  lambda_.report(qts, kcm, kcrs, cenv);
 }
 else
 {
  array_.report(qts, kcm, kcrs, cenv);
 }
 sigma_.report(qts, kcm, kcrs, cenv);
 capture_.report(qts, kcm, kcrs, cenv);
 gamma_.report(qts, kcm, kcrs, cenv);
 result_.report(qts, kcm, kcrs, cenv);
 preempt_.report(qts, kcm, kcrs, cenv);

}



KCM_Channel_Group* KCM_Channel_Group::branch_copy()
{
 KCM_Channel_Group* result = new KCM_Channel_Group;
 result->fuxe_.copy_from(fuxe_);
 result->lambda_.copy_from(lambda_);
 result->sigma_.copy_from(sigma_);
 result->preempt_.copy_from(preempt_);
 result->array_.copy_from(array_);
 result->result_.copy_from(result_);
 // any others?

 return result;
}

