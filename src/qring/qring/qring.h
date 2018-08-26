
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)

#ifndef QRING__H
#define QRING__H

#include "kans.h"

#include "accessors.h"

#include "kauvir-type-system/kauvir-universal-class.h"


#include <QVector>
#include <QObject>

KANS_(QRing)
_KANS(QRing)

class QRing :  public QObject, public Kauvir_Universal_Class
{
 Q_OBJECT

 QStringList names_;

public:

 QRing();

 QRing(const QRing& rhs);

 ~QRing();


 ACCESSORS__RGET(QStringList ,names)

};

Q_DECLARE_METATYPE(QRing)
Q_DECLARE_METATYPE(QRing*)

//_KANS(QRing)


#endif //QRING__H

