//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "datatype/function.h"
#include "extend/inspect.h"

static void _alloc_(function_t *self, args_t arguments) {
  object_t value = next_arg(arguments, object_t);
  self->value = value;
}

static void _free_(function_t *self) {}

static void _copy_(function_t *self, function_t *object) {
  object->value = self->value;
}

static bool _equal_(function_t *self, function_t *object) {
  if (self->value == object->value) {
    return true;
  }
  return false;
}

static void _inspect_(function_t *self, inspect_t *inspect) {
  inspect_value_node(inspect, self, "");
}

def_prototype_source(function_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

static int func_test(int a, int b) { return a + b; }

void function_test() {
  function_t *func = alloc(function_t, func_test);
  assert(type_equal(func, "function_t") == true);
  assert(call(int, func, (int, int))(2, 3) == 5);
  dealloc(func);
}
