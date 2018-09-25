
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


int _detokenize_(QString root, QString outfile, QStringList& infiles)
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

 return ec;
}

int sdetokenize(QString outfile, QString infile)
{
 QStringList infiles{infile};
 return _detokenize_(UDPIPE_DATA_ROOT, outfile, infiles);
}

int detokenize_multi(quint64 args_ptr)
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

 return _detokenize_(root, outfile, infiles);
}

// //  "UNDER CONSTRUCTION" ...
#ifdef HIDE
QString parse_to_outfile(DygRed_Runtime_Environment* dre, QString outfile)
{
 DygRed_Corpus& dgc = dre->dgc();
 QStringList infiles = dgc.expand_files();

 QString outf = dgc.expand_external_file(outfile);

 int result = main_parse(dre->model_file(),
   infiles, outf);
 if(result != 0)
 {
  qDebug() << "Error code: " << result;
 }
 return outfile;
}

void set_model_file(DygRed_Runtime_Environment* dre, QString mf)
{
 qDebug() << "mf: " << mf;
 dre->set_model_file(mf);
}


DygRed_Corpus* get_corpus(DygRed_Runtime_Environment* dre)
{
 DygRed_Corpus* result = &dre->dgc();
 return result;
}

#endif

int detokenize(DygRed_Corpus* dgc, QString outfile)
{
 int result = dgc->detokenize(outfile);
 qDebug() << "Detokenizer result: " << result;
 return result;
}

void add_files(DygRed_Corpus* dgc, quint64 args_ptr)
{
 QVector<quint64>& args = *(QVector<quint64>*)(args_ptr);

 QStringList qsl;
 for(quint64 qui: args)
 {
  QString** qs = (QString**) qui;
  qsl << **qs;
 }
 dgc->add_files(qsl);
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

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "sdetokenize", 700, &sdetokenize);

  g1.clear_all();
 }

// //  these functions not published in current repo ...
// {
//  g1.add_sigma_carrier({kcm.get_kcm_type_by_type_name(
//   "DygRed_Runtime_Environment*" ), nullptr}, QString() );

//  g1.add_lambda_carrier(
//    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
//     QString()
//    );

//  table.init_phaon_function(g1, "set-model-file", 710, &set_model_file);

//  g1.clear_all();
// }

// {
//  g1.add_sigma_carrier(
//    {
//     kcm.get_kcm_type_by_type_name( "DygRed_Runtime_Environment*" ), nullptr
//      //kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr
//     },
//     QString()
//    );

//  g1.add_result_carrier(
//    {kcm.get_kcm_type_by_type_name( "DygRed_Corpus*" ), nullptr},
//     QString()
//    );

//  table.init_phaon_function(g1, "get-corpus", 710, &get_corpus);

//  g1.clear_all();
// }

 {
  g1.add_sigma_carrier(
    {
     kcm.get_kcm_type_by_type_name( "DygRed_Corpus*" ), nullptr
     },
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

  table.init_phaon_function(g1, "detokenize", 710, &detokenize);

  g1.clear_all();
 }

// //  these functions not published in current repo ...
// {
//  g1.add_sigma_carrier(
//    {
//     kcm.get_kcm_type_by_type_name( "DygRed_Runtime_Environment*" ), nullptr
//     },
//     QString()
//    );

//  g1.add_lambda_carrier(
//    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
//     QString()
//    );

//  g1.add_result_carrier(
//    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__str() ), nullptr},
//     QString()
//    );

//  table.init_phaon_function(g1, "parse-to-outfile", 610, &parse_to_outfile);

//  g1.clear_all();
// }

 {
  g1.add_sigma_carrier(
    {
     kcm.get_kcm_type_by_type_name( "DygRed_Corpus*" ), nullptr
     },
     QString()
    );

  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "add-files", 710, &add_files);

  g1.clear_all();
 }

 {
  g1.add_lambda_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__argument_vector() ), nullptr},
     QString()
    );

  g1.add_result_carrier(
    {kcm.get_kcm_type_by_kauvir_type_object( &type_system->type_object__u32() ), nullptr},
     QString()
    );

  table.init_phaon_function(g1, "detokenize-multi", 700, &detokenize_multi);

  g1.clear_all();
 }

}

_KANS(Dynamo)

