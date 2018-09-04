
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-command-runtime-table.h"


#include "kauvir-code-model/kcm-channel-group.h"

#include "kans.h"

#include <QQueue>

USING_KANS(Kauvir)
USING_KANS(CMD)




KCM_Command_Runtime_Table::KCM_Command_Runtime_Table(Kauvir_Type_System& type_system)
  :  type_system_(type_system)
{

}



KCM_Channel_Group* KCM_Command_Runtime_Table::find_channel_group(const KCM_Channel_Group& channels)
{
 if(group_pointers_.contains(channels))
 {
  return group_pointers_.value(channels);
 }
 KCM_Channel_Group* result = new KCM_Channel_Group(channels);
 group_pointers_[channels] = result;
 return result;
}

KCM_Channel_Group* KCM_Command_Runtime_Table::add_s0_declared_function(QString name, const KCM_Channel_Group& channels)
{
 strip_hyphens(name);
 KCM_Channel_Group* result = find_channel_group(channels);
 s0_declared_functions_.insertMulti(name, result);
 return result;
}

KCM_Channel_Group* KCM_Command_Runtime_Table::add_s10_declared_function(QString name, const KCM_Channel_Group& channels)
{
 strip_hyphens(name);
 KCM_Channel_Group* result = find_channel_group(channels);
 s10_declared_functions_.insertMulti(name, result);
 return result;
}


KCM_Channel_Group* KCM_Command_Runtime_Table::add_s1_declared_function(QString name, const KCM_Channel_Group& channels)
{
 strip_hyphens(name);
 KCM_Channel_Group* result = find_channel_group(channels);
 s1_declared_functions_.insertMulti(name, result);
 return result;
}

s1_fng_type KCM_Command_Runtime_Table::find_s1_declared_function_0(QString name,
  KCM_Channel_Group* kcg, const KCM_Type_Object** pkto)
{
 for(QPair<KCM_Channel_Group*, s1_fng_type> pr : s1_declared_functions_generic_.values(name))
 {
  if(pkto)
  {
   KCM_Channel_Group* k_ = pr.first;
   KCM_Channel& result = k_->result_ch();
   if(!result.carriers().isEmpty())
   {
    KCM_Carrier r1;
    result.get_carrier_at_position(0, r1);
    *pkto = r1.type_object();
   }
   else
   {
    *pkto = nullptr;
   }
  }
  return (s1_fng_type)(pr.second);
 }
 return nullptr;
}


s0_fn1_p_p_type KCM_Command_Runtime_Table::find_s10_argvec_function(QString name, int& sl_byte_code)
{
 for(QPair<KCM_Channel_Group*, s0_fng_type> pr : s10_declared_functions_generic_.values(name))
 {
  KCM_Channel_Group* k_ = pr.first;
  int byte_code = k_->get_lambda_byte_code();
  if(byte_code == 99)
  {
   sl_byte_code = k_->get_sigma_lambda_byte_code();
   return (s0_fn1_p_p_type)(pr.second);
  }
 }
 return nullptr;
}


s0_fn1_p_type KCM_Command_Runtime_Table::find_argvec_function(QString name)
{
 for(QPair<KCM_Channel_Group*, s0_fng_type> pr : s0_declared_functions_generic_.values(name))
 {
  KCM_Channel_Group* k_ = pr.first;
  int byte_code = k_->get_lambda_byte_code();
  if(byte_code == 99)
  {
   return (s0_fn1_p_type)(pr.second);
  }
 }
 return nullptr;
}


s0_fn1_p_p_type KCM_Command_Runtime_Table::find_s10_declared_function_1(QString name,
  KCM_Channel_Group* kcg, const KCM_Type_Object** pkto, int& byte_code)
{
 for(QPair<KCM_Channel_Group*, s0_fng_type> pr : s10_declared_functions_generic_.values(name))
 {
  KCM_Channel_Group* k_ = pr.first;
  byte_code = k_->get_sigma_lambda_byte_code();
  if(pkto)
  {
   KCM_Channel& result = k_->result_ch();
   if(!result.carriers().isEmpty())
   {
    KCM_Carrier r1;
    result.get_carrier_at_position(0, r1);
    *pkto = r1.type_object();
   }
   else
   {
    *pkto = nullptr;
   }
  }
  return (s0_fn1_p_p_type)(pr.second);
 }
 return nullptr;
}




s0_fn1_p_type KCM_Command_Runtime_Table::find_s0_declared_function_1(QString name,
  KCM_Channel_Group* kcg, const KCM_Type_Object** pkto, int& byte_code)
{
 for(QPair<KCM_Channel_Group*, s0_fng_type> pr : s0_declared_functions_generic_.values(name))
 {
  KCM_Channel_Group* k_ = pr.first;
  byte_code = k_->get_lambda_byte_code();
  if(pkto)
  {
   KCM_Channel& result = k_->result_ch();
   if(!result.carriers().isEmpty())
   {
    KCM_Carrier r1;
    result.get_carrier_at_position(0, r1);
    *pkto = r1.type_object();
   }
   else
   {
    *pkto = nullptr;
   }
  }
  return (s0_fn1_p_type)(pr.second);
 }
 return nullptr;
}

