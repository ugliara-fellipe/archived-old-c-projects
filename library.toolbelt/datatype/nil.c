//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "datatype/nil.h"
#include "extend/inspect.h"

static void _alloc_(nil_t *self, args_t arguments) {}

static void _free_(nil_t *self) {}

static void _copy_(nil_t *self, nil_t *object) {}

static bool _equal_(nil_t *self, nil_t *object) { return true; }

static void _inspect_(nil_t *self, inspect_t *inspect) {
  inspect_value_node(inspect, self, "");
}

def_prototype_source(nil_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

void nil_test() {
  nil_t *nil = alloc(nil_t);
  assert(type_equal(nil, "nil_t") == true);
  dealloc(nil);
}
