// Modified by Adrian Gierakowski, 2014

// ORIGINAL COPYRIGHT NOTICE
//==============================================================================
// Name        : TripleBuffer.hxx
// Author      : André Pacheco Neves
// Version     : 1.0 (27/01/13)
// Copyright   : Copyright (c) 2013, André Pacheco Neves
//               All rights reserved.

/*

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
- Redistributions of source code must retain the above copyright
notice, this list of conditions and the following disclaimer.
- Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the following disclaimer in the
documentation and/or other materials provided with the distribution.
- Neither the name of the <organization> nor the
names of its contributors may be used to endorse or promote products
derived from this software without specific prior written permission.
THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

// Description :
//    Template class for a TripleBuffer as a concurrency mechanism,
//    using atomic operations
// Credits :
//    http://remis-thoughts.blogspot.pt/2012/01/triple-buffering-as-concurrency_30.html
//==============================================================================

#include <gtest/gtest.h>
#include <lockless_tripplebuffer/TripleBuffer.h>

TEST(tripplebuffer, test1) {
  TripleBuffer<int> buffer(0);

  buffer.write(3);
  buffer.flipWriter();

  buffer.newSnap();

  ASSERT_EQ(3, buffer.snap());
}

TEST(tripplebuffer, test2) {
  TripleBuffer<int> buffer(0);

  buffer.write(4);
  buffer.flipWriter();
  buffer.write(5);
  buffer.flipWriter();
  buffer.write(6);
  buffer.flipWriter();

  buffer.newSnap();

  buffer.write(7);
  buffer.flipWriter();
  buffer.write(8);
  buffer.flipWriter();

  ASSERT_EQ(6 , buffer.snap());
}

TEST(tripplebuffer, test3) {
  TripleBuffer<int> buffer(0);

  buffer.write(7);
  buffer.flipWriter();

  buffer.write(8);
  buffer.flipWriter();

  buffer.newSnap();
  ASSERT_EQ(8 , buffer.snap());

  buffer.newSnap();
  ASSERT_EQ(8 , buffer.snap());
}
