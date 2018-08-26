
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef QRING_FILE_STRUCTURE__H
#define QRING_FILE_STRUCTURE__H

#include "kans.h"

#include "accessors.h"

#include <QVector>
#include <QObject>


class QRing_File_Structure
{
public:
 typedef QVector<QString> QStringVector;

protected:

 QString root_folder_;
 QStringVector folders_;
 QStringVector files_;

 QString expand_file(QString f);
 void expand_files(QStringList& result);

public:

 QRing_File_Structure(QString root_folder);

 ACCESSORS(QString ,root_folder)
 ACCESSORS__RGET(QStringVector ,folders)
 ACCESSORS__RGET(QStringVector ,files)

 void add_files(QStringList f);
 void add_folder(QString f);
 void add_file(QString f);

};


#endif //QRING_FILE_STRUCTURE

