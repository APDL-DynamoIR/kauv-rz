
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "kcm-command-package.h"

#include "kauvir-kcm/kauvir-code-model/kcm-carrier.h"
#include "kauvir-kcm/kauvir-code-model/kcm-overloadable-symbol.h"

#include "kans.h"

USING_KANS(CMD)


KCM_Command_Package::KCM_Command_Package()
  :  KCM_Channel_Group(), output_symbol_(nullptr),
     kcm_expression_(nullptr), bind_kto_(nullptr), bind_qob_(nullptr)
{

}

KCM_Command_Package::KCM_Command_Package(const KCM_Channel_Group& kcg)
  :  KCM_Channel_Group(kcg), output_symbol_(nullptr),
     kcm_expression_(nullptr), bind_kto_(nullptr), bind_qob_(nullptr)
{

}

KCM_Command_Package::KCM_Command_Package(const KCM_Type_Object* kto, QString val, QObject* bind_qob)
 :  KCM_Channel_Group(), bind_kto_(kto),
    bind_val_(val), output_symbol_(nullptr),
    kcm_expression_(nullptr), bind_qob_(bind_qob)
{

}


QString KCM_Command_Package::report_sigma(Kauvir_Code_Model& kcm,
  QString sep, QString last_sep, QString on_empty) const
{
 if(sigma_.carriers().isEmpty())
   return on_empty;

 QString result = "[";
 last_sep.prepend("]");
 int max = sigma_.carriers().size() - 1;
 int i = 0;

 for(const KCM_Carrier& kcmc: sigma_.carriers())
 {
  result += kcmc.token_report(kcm);
  result += (i < max)? sep : last_sep;
  ++i;
 }
 return result;
}

QString KCM_Command_Package::report_fuxe(Kauvir_Code_Model& kcm,
  QString sep, QString last_sep, QString on_empty) const
{
 if(fuxe_.carriers().isEmpty())
   return on_empty;

 QString result = "(|";
 last_sep.prepend("|)");
 int max = fuxe_.carriers().size() - 1;
 int i = 0;


 for(const KCM_Carrier& kcmc: fuxe_.carriers())
 {
  result += kcmc.token_report(kcm);
  result += (i < max)? sep : last_sep;
  ++i;
 }
 return result;
}

QString KCM_Command_Package::output_symbol_name()
{
 if(output_symbol_)
  return output_symbol_->symbol_name();
 return QString();
}


QString KCM_Command_Package::report_lambda(Kauvir_Code_Model& kcm,
  QString sep, QString last_sep, QString on_empty) const
{
 if(lambda_.carriers().isEmpty())
   return on_empty;

 QString result;
 int max = lambda_.carriers().size() - 1;
 int i = 0;


 for(const KCM_Carrier& kcmc: lambda_.carriers())
 {
  result += kcmc.token_report(kcm);
  result += (i < max)? sep : last_sep;
  ++i;
 }
 return result;
}
