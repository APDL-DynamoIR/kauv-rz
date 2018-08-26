
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "dygred-corpus.h"


DygRed_Corpus::DygRed_Corpus(QString root_folder)
  :  QRing_File_Structure(root_folder)
{


}

int DygRed_Corpus::detokenize(QString outfile)
{
 QVector<sentence*> sv;

 QStringList infiles;
 expand_files(infiles);

 int result = main_detokenize(infiles,
   expand_file(outfile), &sv);

 for(sentence* s : sv)
 {
  push_back(DygRed_Sentence(s));
 }

 return result;
}
