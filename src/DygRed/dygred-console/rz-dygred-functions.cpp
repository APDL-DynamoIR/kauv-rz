
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "rz-dygred-functions.h"



#include "udpipe.h"

#include <QDebug>

#include "dygred-sentence/dygred-sentence.h"
#include "dygred-sentence/dygred-corpus.h"

#include "rz-graph-visit/rz-lisp-graph-visitor-dynamo.h"



#include "kauvir-code-model/kauvir-code-model.h"

#include "kauvir-code-model/kcm-channel-group.h"

#include "kauvir-type-system/kauvir-type-system.h"

#include "kauvir-code-model/kcm-callable-value.h"

#include "kauvir-runtime/kcm-command-runtime/kcm-command-runtime-table.h"

#include "kauvir-runtime/kcm-command-runtime/kcm-command-runtime-router.h"

#include "kcm-lisp-bridge/kcm-lisp-eval.h"

#include <QTextStream>

#include <QDebug>

#include <QEventLoop>


USING_KANS(KCL)

KANS_(Dynamo)


void _detokenize_(QString root, QString outfile, QStringList& infiles)
{

 qDebug() << "root: " << root;
 qDebug() << "outfile: " << outfile;
 qDebug() << "infiles: " << infiles;

 DygRed_Corpus dgc(root);

 dgc.add_files(infiles);
 int ec = dgc.detokenize(outfile);

 if(ec == 0)
 {
  qDebug() << "Detokenizer completed successfully.";
 }

 else
 {
  qDebug() << "Detokenizer reported error code " << ec;
 }
}

void detokenize(QString outfile, QString infile)
{
 QStringList infiles{infile};
 _detokenize_(UDPIPE_DATA_ROOT, outfile, infiles);
}

void detokenize_multi(quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 int i = 0;
 QString root;
 QString outfile;
 QStringList infiles;

 for(quint64 qui: args)
 {
  QString** qs = (QString**) qui;
  if(i == 0)
    root = **qs;
  else if(i == 1)
    outfile = **qs;
  else
    infiles.push_back(**qs);
  ++i;
 }

 _detokenize_(root, outfile, infiles);

}



void init_dygred_functions(Kauvir_Code_Model& kcm)
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


  KCM_Channel_Group* kcg = table.add_s0_declared_function("detokenize", g1);
  table.add_s0_declared_function("detokenize", kcg, reinterpret_cast<s0_fn1_p_p_type>
                              (&detokenize));
  g1.clear_all();
 }


 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );
  KCM_Channel_Group* kcg = table.add_s0_declared_function("detokenize-multi", g1);
  table.add_s0_declared_function("detokenize-multi", kcg, reinterpret_cast<s0_fn1_p_type>
                              (&detokenize_multi));
  g1.clear_all();
 }



}

_KANS(Dynamo)

