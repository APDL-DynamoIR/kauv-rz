
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-channel.h"

#include "kcm-report-syntax.h"

#include "kans.h"

USING_KANS(KCM)


KCM_Channel::KCM_Channel()
  : kind_(Kinds::N_A)
{

}

QString KCM_Channel::kind_to_string(KCM_Report_Syntax& kcrs)
{
 return kcrs.get_channel_kind_code(kind_);
}

void KCM_Channel::report(QTextStream& qts,
  Kauvir_Code_Model& kcm, KCM_Report_Syntax& kcrs, Code_Environments cenv)
{
 if( (cenv == Code_Environments::Statement) &&
  kcrs.flags.arrow_before_result_channel && kind_ == Kinds::Result)
 {
  qts << " -> ";
 }
 if(carriers_.isEmpty())
 {
  if(kcrs.flags.write_empty_lambda_channel && kind_ == Kinds::Lambda)
  {
   qts << " () ";
  }
  if( (cenv == Code_Environments::Statement) &&
   kcrs.flags.write_empty_result_channel && kind_ == Kinds::Result)
  {
   qts << " () ";
  }
  return;
 }

 if(kcrs.flags.merge_fuxe_and_lambda && kind_ == Kinds::Lambda)
 {

 }
 else if(kind_ == Kinds::Fuxe && cenv == Code_Environments::Expression)
 {
  if(kcrs.flags.merge_fuxe_and_lambda)
  {
   qts << '(';
  }
 }
 else if(kind_ == Kinds::Array)
 {
  if(kcrs.flags.expand_array_indicators)
  {
   qts << "(arr ";
  }
  else
  {
   qts << '[';
  }
 }
 else
 {
  qts << '(';
 }

 if(kcrs.flags.identify_channel_names)
 {
  qts << '[' << kind_to_string(kcrs) << "] ";
 }

 int count = 0;
 int max = carriers_.size();
 for(const KCM_Carrier& kcc : carriers_)
 {
  ++count;
  kcc.report(qts, kcm, kcrs);
  if(count < max)
  {
   if(kcrs.flags.comma_separate_channel_carriers)
   {
    qts << ", ";
   }
   else
   {
    qts << ' ';
   }
  }
 }

 if(kcrs.flags.merge_fuxe_and_lambda && kind_ == Kinds::Fuxe)
 {
  qts << ' ';
 }
 else if(kind_ == Kinds::Fuxe && cenv == Code_Environments::Expression)
 {

 }
 else if(kind_ == Kinds::Array)
 {
  if(kcrs.flags.expand_array_indicators)
  {
   qts << ')';
  }
  else
  {
   qts << ']';
  }
 }
 else
 {
  qts << ')';
 }

}


void KCM_Channel::copy_from(const KCM_Channel& kch)
{
 for(const KCM_Carrier& kcc : kch.carriers())
 {
  carriers_.push_back(kcc.branch_copy());
 }
 kind_ = kch.kind();
}


KCM_Carrier* KCM_Channel::get_carrier_at_position(int position)
{
 if(position < carriers_.size())
 {
  KCM_Carrier& kcc = carriers_[position];
  return &kcc;
 }
 return nullptr;
}

void KCM_Channel::get_carrier_at_position(int position, KCM_Carrier& result)
{
 if(position < carriers_.size())
 {
  result = carriers_.value(position);
 }
}

const KCM_Type_Object* KCM_Channel::type_object_at_position(int position)
{
 if(position < carriers_.size())
 {
  return carriers_.value(position).type_object();
 }
 return nullptr;
}

void KCM_Channel::add_carrier(QPair<const KCM_Type_Object*, const KCM_Type_Object*> tos,
  KCM_Carrier::Effect_Protocols ep, QString symbol, KCM_Runtime_Scope* scope)
{
 carriers_.push_back(KCM_Carrier(tos.first, ep, symbol, tos.second, scope));
}
