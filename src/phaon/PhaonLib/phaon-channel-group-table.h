
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef PHAON_CHANNEL_GROUP_TABLE__H
#define PHAON_CHANNEL_GROUP_TABLE__H

#include <QtGlobal>


#include <functional>

#include <QMetaProperty>
#include <QVector>

#include <QSet>

#include "kans.h"
#include "accessors.h"

#include "kauvir-kcm/kauvir-type-system/kauvir-universal-class.h"
#include "kauvir-kcm/kauvir-type-system/kauvir-type-system.h"



KANS_CLASS_DECLARE(KCM ,KCM_Channel_Group)
KANS_CLASS_DECLARE(KCM ,KCM_Type_Object)

USING_KANS(KCM)
USING_KANS(Kauvir)

KANS_(PhaonLib)

class Phaon_Channel_Group_Table
{
 QMap<KCM_Channel_Group, KCM_Channel_Group*> group_pointers_;


 QMultiMap<QString, QString> declared_types_;

 Kauvir_Type_System& type_system_;


public:

 Phaon_Channel_Group_Table(Kauvir_Type_System& type_system);

 ACCESSORS__GET(Kauvir_Type_System& ,type_system)

 KCM_Channel_Group* find_channel_group(const KCM_Channel_Group& channels);

};

_KANS(PhaonLib)

#endif //PHAON_CHANNEL_GROUP_TABLE__H
