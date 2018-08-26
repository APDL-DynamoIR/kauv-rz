
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#include "qring.h"

#include "kans.h"

USING_KANS(QRing)


QRing::QRing()
{

}

QRing::QRing(const QRing& rhs)
  :  names_(rhs.names_)
{

}

QRing::~QRing()
{

}
