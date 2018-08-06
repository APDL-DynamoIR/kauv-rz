
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_COMMAND_RUNTIME_TABLE__H
#define KCM_COMMAND_RUNTIME_TABLE__H

#include <QtGlobal>


#include <functional>

#include <QMetaProperty>
#include <QVector>

#include <QSet>

#include "kans.h"
#include "accessors.h"

#include "kauvir-kcm/kauvir-type-system/kauvir-universal-class.h"
#include "kauvir-kcm/kauvir-type-system/kauvir-type-system.h"



KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)

USING_KANS(KCM)
USING_KANS(Kauvir)

KANS_(CMD)

class KCM_Command_Runtime_Table
{
 QMultiMap<QString, KCM_Channel_Group*> s1_declared_functions_;
 QMultiMap<QString, KCM_Channel_Group*> s0_declared_functions_;

 QMap<KCM_Channel_Group, KCM_Channel_Group*> group_pointers_;
 KCM_Channel_Group* find_channel_group(const KCM_Channel_Group& channels);

 QMultiMap<QString, QPair<KCM_Channel_Group*, s1_fng_type>> s1_declared_functions_generic_;
 QMultiMap<QString, QPair<KCM_Channel_Group*, s0_fng_type>> s0_declared_functions_generic_;

 QMultiMap<QString, QPair<KCM_Channel_Group*, _s1_fng_type>> _s1_declared_functions_generic_;
 QMultiMap<QString, QPair<KCM_Channel_Group*, _s0_fng_type>> _s0_declared_functions_generic_;

 QMultiMap<QString, QString> declared_types_;

 Kauvir_Type_System& type_system_;


 QSet<QString>  s0_string_returns_;
 QSet<QString>  s1_string_returns_;

public:

 KCM_Command_Runtime_Table(Kauvir_Type_System& type_system);

 ACCESSORS__GET(Kauvir_Type_System& ,type_system)

 KCM_Channel_Group* add_s1_declared_function(QString name, const KCM_Channel_Group& channels);
 KCM_Channel_Group* add_s0_declared_function(QString name, const KCM_Channel_Group& channels);


 note_s0_string_return(QString n)
 {
  s0_string_returns_.insert(n);
 }

 note_s1_string_return(QString n)
 {
  s1_string_returns_.insert(n);
 }

 bool s0_string_return(QString n)
 {
  return s0_string_returns_.contains(n);
 }

 bool s1_string_return(QString n)
 {
  return s1_string_returns_.contains(n);
 }

 template<typename FN_type>
 void add_s1_declared_function(QString name, KCM_Channel_Group* kcg, FN_type fn)
 {
  s1_declared_functions_generic_.insert(name, {kcg, (s1_fng_type)fn});
 }

 template<typename FN_type>
 void add_s0_declared_function(QString name, KCM_Channel_Group* kcg, FN_type fn)
 {
  s0_declared_functions_generic_.insert(name, {kcg, (s0_fng_type)fn});
 }

 s0_fn1_p_type find_s0_declared_function_1(QString name,
   KCM_Channel_Group* kcg, const KCM_Type_Object** pkto);

 s1_fng_type find_s1_declared_function_0(QString name,
   KCM_Channel_Group* kcg, const KCM_Type_Object** pkto);
};

_KANS(CMD)

#endif //KCM_COMMAND_RUNTIME_TABLE__H
