
//           Copyright Nathaniel Christen 2018.
//  Distributed under the Boost Software License, Version 1.0.
//     (See accompanying file LICENSE_1_0.txt or copy at
//           http://www.boost.org/LICENSE_1_0.txt)


#ifndef DYGRED_SENTENCE__H
#define DYGRED_SENTENCE__H


#include "udpipe.h"


class DygRed_Sentence
{
 sentence* udp_sentence_;

public:

 explicit DygRed_Sentence(sentence* udp_sentence = nullptr);


};


#endif
