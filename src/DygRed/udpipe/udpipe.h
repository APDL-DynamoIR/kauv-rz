
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

// //  Adapted from udpipe.cpp, which has a separate license and copyright.

#ifndef UDPIPE__H
#define UDPIPE__H

#include <fstream>
#include <sstream>

#include "common.h"
#include "model/evaluator.h"
#include "model/model.h"
#include "model/pipeline.h"
#include "sentence/input_format.h"
#include "sentence/output_format.h"
#include "tokenizer/detokenizer.h"
#include "trainer/trainer.h"
#include "utils/getpara.h"
#include "utils/iostreams.h"
#include "utils/options.h"
#include "utils/process_args.h"
#include "version/version.h"

#include <QMap>
#include <QVector>

using namespace ufal::udpipe;

int main_with_options(int argc, char* argv[], options::map& options,
  QStringList& files, QString model_file, QVector<sentence*>* sv = nullptr);

int main_with_qmap(int argc, char* argv[], QMap<QString, QString>& qoptions,
  QStringList& files, QString model_file, QVector<sentence*>* sv = nullptr);

int main_parse(int argc, char* argv[], QString model_file,
               QStringList& infiles, QString outfile);

int main_detokenize(int argc, char* argv[],
                    QStringList& infiles, QString outfile, QVector<sentence*>* sv = nullptr);

int main_detokenize(QStringList& infiles,
  QString fn = QString(), QVector<sentence*>* sv = nullptr);

void main_detokenize(int argc, char* argv[], options::map& options,
  QStringList& files, QString fn, QVector<sentence*>* sv);

//int main_with_options(int argc, char* argv[], options::map& options,
//  QStringList& files, QString model_file, QVector<sentence*>* sv = nullptr);


#endif //UDPIPE__H
