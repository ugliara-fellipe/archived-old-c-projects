//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#ifndef FUNCTION_H
#define FUNCTION_H

#include "extend/prototype.h"

typedef struct {
  object_t value;
} function_t;

def_prototype_header(function_t);

#define call(ret, self, par) cast(ret(*) par, self->value)

void function_test();

#endif
