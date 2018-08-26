
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qring-file-structure.h"

#include "kans.h"

//USING_KANS(QRing)


QRing_File_Structure::QRing_File_Structure(QString root_folder)
  :  root_folder_(root_folder)
{

}

void QRing_File_Structure::add_files(QStringList f)
{
 files_.append(f.toVector());
}

void QRing_File_Structure::add_folder(QString f)
{
 folders_.push_back(f);
}

void QRing_File_Structure::add_file(QString f)
{
 files_.push_back(f);
}

QString QRing_File_Structure::expand_file(QString f)
{
 if(f.startsWith('@'))
 {
  return QString("%1/%2").arg(root_folder_).arg(f.mid(1));
 }
 return f;
}

void QRing_File_Structure::expand_files(QStringList& result)
{
 for(QString s : files_)
 {
  result.push_back(expand_file(s));
 }
}
