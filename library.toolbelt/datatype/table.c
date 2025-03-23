//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "datatype/table.h"
#include "extend/inspect.h"

static void _alloc_(table_t *self, args_t arguments) {
  self->values = alloc(list_t);
}

static void _free_(table_t *self) { dealloc(self->values); }

static void _copy_(table_t *self, table_t *object) {
  object->values = copy(self->values);
}

static bool _equal_(table_t *self, table_t *object) {
  return equal(self->values, object->values);
}

static void _inspect_(table_t *self, inspect_t *inspect) {
  inspect_list_node(inspect, self, self->values);
  list_for(self->values, index, object_t, item, {
    char index_str[50];
    snprintf(index_str, 50, "i%zu", index);
    inspect_add_edge(inspect, self, index_str, item, NULL);
    object_inspect(item, inspect);
  });
}

def_prototype_source(table_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

void table_add(table_t *self, const char *key, object_t value) {
  pair_t *pair = alloc(pair_t, key, value);
  list_add(self->values, LIST_TAIL, pair);
}

void table_del(table_t *self, const char *key) {
  index_t index_to_del = LIST_INVALID_INDEX;
  list_for(self->values, index, pair_t, pair, {
    if (text_compare(pair->key, key)) {
      index_to_del = index;
      break;
    }
  });
  if (index_to_del != LIST_INVALID_INDEX) {
    list_del(self->values, index_to_del);
  }
}

pair_t *table_get_pair(table_t *self, const char *key) {
  list_for(self->values, index, pair_t, pair, {
    if (text_compare(pair->key, key)) {
      return pair;
    }
  });
  return NULL;
}

void table_test() {
  table_t *table = alloc(table_t);
  assert(type_equal(table, "table_t") == true);
  text_t *t1 = alloc(text_t, "value1");
  table_add(table, "key1", t1);
  text_t *t2 = alloc(text_t, "value2");
  table_add(table, "key2", t2);
  text_t *t3 = alloc(text_t, "value3");
  table_add(table, "key3", t3);
  // Uncomment inspect, after run dot to create the graph
  // dot -T svg graph.gv -o img.svg
  // inspect(table,"graph");
  table_del(table, "key2");
  pair_t *pair = table_get_pair(table, "key3");
  assert(text_compare(pair->key, "key3") == true);
  assert(text_compare(pair->value, "value3") == true);
  assert(text_compare(table_get(table, text_t, "key3"), "value3") == true);
  table_for(table, index, text_t, key, value,
            { assert(type_equal(value, "text_t") == true); });
  dealloc(table);
}
