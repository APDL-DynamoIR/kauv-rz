
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_RUNNER__H
#define PHAON_RUNNER__H


#include "kans.h"

#include "phaon-function.h"

#include <QString>


KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)

USING_KANS(KCM)

KANS_(PhaonLib)

class Phaon_Symbol_Scope;
class Phaon_Function_Vector;


class Phaon_Runner
{

public:

 void run_by_name(Phaon_Symbol_Scope& pss, QString name);
 void run_by_vector(Phaon_Function_Vector& pfv);
 KCM_Channel_Group* run_by_function(Phaon_Function phf);

};


_KANS(PhaonLib)


#endif //PHAON_RUNNER__H
