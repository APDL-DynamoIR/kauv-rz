
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef RZ_DYGRED_FUNCTIONS__H
#define RZ_DYGRED_FUNCTIONS__H


#include "accessors.h"

#include "kans.h"

#include <QString>
#include <QStringList>

#include <QMap>

class QTextStream;

KANS_CLASS_DECLARE(KCM ,Kauvir_Code_Model)

USING_KANS(KCM)

KANS_(Dynamo)

void init_dygred_functions(Kauvir_Code_Model& kcm);

//void* envv(void* kind);
//void* insert_envv(void* kind, void* test);

//void prs(QString str);
//void prn(int num);
//int let_num(int num);
//QString let_str(QString str);


//void prfn(int num);

_KANS(Dynamo)

#endif //RZ_DYNAMO_BASIC_FUNCTIONS__H
