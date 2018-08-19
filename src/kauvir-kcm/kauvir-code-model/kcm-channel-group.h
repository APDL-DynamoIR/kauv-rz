
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef KCM_CHANNEL_GROUP__H
#define KCM_CHANNEL_GROUP__H


#include "kans.h"

#include "accessors.h"

#include "kcm-channel.h"

#include <QVector>
#include <QTextStream>

KANS_(KCM)


class KCM_Type_Object;
class KCM_Channel_Furnisher;

class KCM_Channel_Group
{
 KCM_Channel_Furnisher* furnisher_;

protected:
 KCM_Channel fuxe_;

 KCM_Channel lambda_;
 KCM_Channel sigma_;

 KCM_Channel array_;

 KCM_Channel capture_;
 KCM_Channel gamma_;

 KCM_Channel result_;

 KCM_Channel preempt_;

private:

 void set_kinds();

 typedef QPair<const KCM_Type_Object*, const KCM_Type_Object*> kcm_type_object_pair_type;

public:

 KCM_Channel_Group();

 KCM_Channel_Group(const KCM_Channel_Group& rhs);

 ACCESSORS(KCM_Channel_Furnisher* ,furnisher)

 int get_lambda_byte_code();

 friend bool operator<(const KCM_Channel_Group& lhs, const KCM_Channel_Group& rhs)
 {
  if(lhs.sigma() < rhs.sigma())
   return true;
  if(lhs.lambda() < rhs.lambda())
   return true;
  if(lhs.array() < rhs.array())
   return true;
  if(lhs.capture() < rhs.capture())
   return true;
  if(lhs.gamma() < rhs.gamma())
   return true;
  if(lhs.result() < rhs.result())
   return true;
  if(lhs.fuxe() < rhs.fuxe())
   return true;
  return false;
 }

 ACCESSORS__RGET(KCM_Channel ,fuxe)

 ACCESSORS__RGET(KCM_Channel ,lambda)
 ACCESSORS__RGET(KCM_Channel ,sigma)

 ACCESSORS__RGET(KCM_Channel ,array)

 ACCESSORS__RGET(KCM_Channel ,capture)
 ACCESSORS__RGET(KCM_Channel ,gamma)

 ACCESSORS__RGET(KCM_Channel ,result)

 ACCESSORS__CONST_RGET(KCM_Channel ,fuxe)

 ACCESSORS__CONST_RGET(KCM_Channel ,lambda)
 ACCESSORS__CONST_RGET(KCM_Channel ,sigma)

 ACCESSORS__CONST_RGET(KCM_Channel ,array)

 ACCESSORS__CONST_RGET(KCM_Channel ,capture)
 ACCESSORS__CONST_RGET(KCM_Channel ,gamma)

 ACCESSORS__CONST_RGET(KCM_Channel ,result)


 void add_fuxe_carrier(const KCM_Type_Object* type_object);
 void add_fuxe_carrier(QString symbol_name);


 void add_lambda_carrier_via_scoped_symbol(QString symbol_name, KCM_Runtime_Scope* scope);

 void add_lambda_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
   QString symbol_name = QString(), KCM_Runtime_Scope* scope = nullptr);

 void add_array_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
   QString symbol_name = QString());

 void add_sigma_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
                        QString symbol_name = QString());

 void add_capture_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
                          QString symbol_name = QString());

 void add_gamma_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
                        QString symbol_name = QString());

 void add_result_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
   QString symbol_name = QString());

 void add_preempt_carrier(kcm_type_object_pair_type tos,
   KCM_Carrier::Effect_Protocols ep = KCM_Carrier::Effect_Protocols::Unrestricted,
   QString symbol_name = QString());


 void add_lambda_carrier(kcm_type_object_pair_type tos, QString value_name);
 void add_sigma_carrier(kcm_type_object_pair_type tos, QString value_name);
 void add_array_carrier(kcm_type_object_pair_type tos, QString value_name);
 void add_capture_carrier(kcm_type_object_pair_type tos, QString value_name);
 void add_gamma_carrier(kcm_type_object_pair_type tos, QString value_name);
 void add_result_carrier(kcm_type_object_pair_type tos, QString value_name);
 void add_preempt_carrier(kcm_type_object_pair_type tos, QString value_name);

 void add_lambda_carrier_via_bind_symbol(const KCM_Type_Object* kto, QString symbol_name);

 void add_lambda_carrier_via_symbol(QString value_name);
 void add_lambda_carrier_via_symbol(const KCM_Type_Object* kto, QString value_name);
 void add_lambda_carrier_via_typed_scoped_symbol(const KCM_Type_Object* kto, QString value_name, KCM_Runtime_Scope* scope);

 void add_lambda_carrier_via_literal(QString value_name);

 void add_lambda_carrier_via_typed_literal(const KCM_Type_Object* kto, QString value_name);
 void add_lambda_carrier_from_result_channel(int level, int index);

 void add_lambda_carrier_via_typed_opaque_value(const KCM_Type_Object* kto, QString value_encoding);

 void add_lambda_carrier_via_typed_literal_with_cast(const KCM_Type_Object* kto,
   QString value_name, const KCM_Type_Object* ckto);

 void add_lambda_carrier_via_symbol_with_cast(QString value_name, const KCM_Type_Object* type_object);
 void add_lambda_carrier_via_literal_with_cast(QString value_name, const KCM_Type_Object* type_object);



 void add_sigma_carrier_via_symbol(QString value_name);
 void add_sigma_carrier_via_literal(QString value_name);

 void add_sigma_carrier_via_typed_literal(const KCM_Type_Object* kto, QString value_name);
 void add_sigma_carrier_via_typed_literal_with_cast(const KCM_Type_Object* kto,
   QString value_name, const KCM_Type_Object* ckto);

 void add_sigma_carrier_via_symbol_with_cast(QString value_name, const KCM_Type_Object* kto,
    const KCM_Type_Object* ckto);
 void add_sigma_carrier_via_literal_with_cast(QString value_name, const KCM_Type_Object* type_object);



 void add_array_carrier_via_symbol(QString value_name);
 void add_array_carrier_via_literal(QString value_name);
 void add_array_carrier_via_symbol_with_cast(QString value_name, const KCM_Type_Object* type_object);
 void add_array_carrier_via_literal_with_cast(QString value_name, const KCM_Type_Object* type_object);

 void clear_all();

 void clear_all_but_sigma();

 KCM_Channel_Group* branch_copy();

 void report(QTextStream& qts, Kauvir_Code_Model& kcm,
   KCM_Report_Syntax& kcrs, KCM_Channel::Code_Environments cenv);



};


_KANS(KCM)


#endif //KCM_CHANNEL_GROUP__H
