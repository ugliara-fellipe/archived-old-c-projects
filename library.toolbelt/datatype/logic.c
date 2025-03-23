//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "datatype/logic.h"
#include "extend/inspect.h"

static void _alloc_(logic_t *self, args_t arguments) {
  bool value = next_arg(arguments, int);
  self->value = value;
}

static void _free_(logic_t *self) {}

static void _copy_(logic_t *self, logic_t *object) {
  object->value = self->value;
}

static bool _equal_(logic_t *self, logic_t *object) {
  if (self->value == object->value) {
    return true;
  }
  return false;
}

static void _inspect_(logic_t *self, inspect_t *inspect) {
  if (self->value) {
    inspect_value_node(inspect, self, "true");
  } else {
    inspect_value_node(inspect, self, "false");
  }
}

def_prototype_source(logic_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

void logic_test() {
  logic_t *logic = alloc(logic_t, true);
  assert(type_equal(logic, "logic_t") == true);
  assert(logic->value == true);
  dealloc(logic);
}
