
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#include "phaon-runner.h"

#include "phaon-symbol-scope.h"
#include "phaon-function-vector.h"

USING_KANS(PhaonLib)

void Phaon_Runner::run_by_name(Phaon_Symbol_Scope& pss, QString name)
{
 auto it = pss.find(name);
 if(it != pss.end())
 {
  Phaon_Function_Vector& pfv = it.value();
  run_by_vector(pfv);
 }
}

void Phaon_Runner::run_by_vector(Phaon_Function_Vector& pfv)
{
 for(Phaon_Function phf : pfv)
 {
  KCM_Channel_Group* kcg = run_by_function(phf);
 }
}


KCM_Channel_Group* Phaon_Runner::run_by_function(Phaon_Function phf)
{
 KCM_Channel_Group* result;
 void* fn = phf.de_augment<KCM_Channel_Group>(result);
 if(result)
 {
  ((void (*)(QString, QString)) fn) ("t1", "t2");
 }
 return result;
}




