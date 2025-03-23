//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "datatype/list.h"
#include "datatype/number.h"
#include "extend/inspect.h"

static void _alloc_(list_t *self, args_t arguments) {
  self->size = 0;
  self->head = NULL;
  self->tail = NULL;
  object_t value = next_arg(arguments, object_t);
  while (value != NULL) {
    list_add(self, LIST_TAIL, value);
    value = next_arg(arguments, object_t);
  }
}

static void _free_(list_t *self) {
  if (self->size > 0) {
    node_t *node = self->head;
    do {
      node_t *next = node->next;
      dealloc(node->value);
      free(node);
      node = next;
    } while (node != NULL);
  }
}

static void _copy_(list_t *self, list_t *object) {
  object->size = 0;
  if (self->size > 0) {
    node_t *node = self->head;
    do {
      list_add(object, LIST_TAIL, copy(node->value));
      node = node->next;
    } while (node != NULL);
  } else {
    object->head = NULL;
    object->tail = NULL;
  }
}

static bool _equal_(list_t *self, list_t *object) {
  if (self->size != object->size) {
    return false;
  }
  if (self->size > 0) {
    node_t *node_self = self->head;
    node_t *node_object = object->head;
    do {
      if (!equal(node_self->value, node_object->value)) {
        return false;
      }
      node_self = node_self->next;
      node_object = node_object->next;
    } while (node_self != NULL);
  }
  return true;
}

static void _inspect_(list_t *self, inspect_t *inspect) {
  inspect_list_node(inspect, self, self);
  list_for(self, index, object_t, item, {
    char index_str[50];
    snprintf(index_str, 50, "i%zu", index);
    inspect_add_edge(inspect, self, index_str, item, NULL);
    object_inspect(item, inspect);
  });
}

def_prototype_source(list_t, _alloc_, _free_, _copy_, _equal_, _inspect_);

void list_add(list_t *self, index_t index, object_t value) {
  node_t *node = calloc(1, sizeof(node_t));
  node->value = value;
  node->next = NULL;
  if (self->size == 0) {
    if (index == LIST_HEAD || index == LIST_TAIL) {
      self->head = node;
      self->tail = node;
    }
  } else {
    if (index == LIST_HEAD) {
      node->next = self->head;
      self->head = node;
    } else if (index == LIST_TAIL || index == self->size) {
      self->tail->next = node;
      self->tail = node;
    } else {
      node_t *last = self->head;
      for (index_t i = 0; i < index - 1; i++) {
        last = last->next;
      }
      node->next = last->next;
      last->next = node;
    }
  }
  self->size++;
}

static object_t list_remove(list_t *self, index_t index, bool clean) {
  object_t result = NULL;

  if (self->size == 1) {
    if (clean) {
      dealloc(self->head->value);
    } else {
      result = self->head->value;
    }
    free(self->head);
    self->head = NULL;
    self->tail = NULL;
  } else {
    node_t *remove = NULL;
    if (index == LIST_HEAD) {
      remove = self->head;
      self->head = self->head->next;
      if (clean) {
        dealloc(remove->value);
      } else {
        result = remove->value;
      }
      free(remove);
    } else if (index == LIST_TAIL || (index == self->size - 1)) {
      remove = self->tail;
      node_t *last = self->head;
      while (last->next != remove) {
        last = last->next;
      }
      last->next = NULL;
      self->tail = last;
      if (clean) {
        dealloc(remove->value);
      } else {
        result = remove->value;
      }
      free(remove);
    } else {
      remove = self->head->next;
      node_t *last = self->head;
      for (index_t i = 1; i < index; i++) {
        last = remove;
        remove = remove->next;
      }
      last->next = remove->next;
      if (clean) {
        dealloc(remove->value);
      } else {
        result = remove->value;
      }
      free(remove);
    }
  }
  self->size--;
  return result;
}

void list_del(list_t *self, index_t index) { list_remove(self, index, true); }

object_t list_extract(list_t *self, index_t index) {
  return list_remove(self, index, false);
}

object_t list_get_object(list_t *self, index_t index) {
  if (index == LIST_HEAD) {
    return self->head->value;
  } else if (index == LIST_TAIL) {
    return self->tail->value;
  } else {
    node_t *node = self->head;
    for (index_t i = 0; i < index; i++) {
      node = node->next;
    }
    return node->value;
  }
}

void list_test() {
  list_t *list = alloc(list_t);
  number_t *n0 = alloc(number_t, 0.0);
  list_add(list, 0, n0);
  list_del(list, 0);
  assert(type_equal(list, "list_t") == true);
  dealloc(list);
  number_t *n1 = alloc(number_t, 1.0);
  number_t *n2 = alloc(number_t, 2.0);
  number_t *n3 = alloc(number_t, 3.0);
  list = alloc(list_t, n1, n2, n3);
  list_t *list2 = copy(list);
  assert(list_get(list2, number_t, 1)->value == 2);
  dealloc(list2);
  assert(list->size == 3);
  assert(list_get(list, number_t, LIST_HEAD)->value == 1);
  assert(list_get(list, number_t, 0)->value == 1);
  assert(list_get(list, number_t, 1)->value == 2);
  assert(list_get(list, number_t, 2)->value == 3);
  assert(list_get(list, number_t, LIST_TAIL)->value == 3);
  list_for(list, index, number_t, item, { assert(item->value == index + 1); });
  number_t *n4 = alloc(number_t, 4.0);
  list_add(list, 0, n4);
  assert(list_get(list, number_t, LIST_HEAD)->value == 4);
  number_t *n5 = alloc(number_t, 5.0);
  list_add(list, 2, n5);
  assert(list_get(list, number_t, 2)->value == 5);
  number_t *n6 = alloc(number_t, 6.0);
  list_add(list, LIST_TAIL, n6);
  assert(list_get(list, number_t, LIST_TAIL)->value == 6);
  list_del(list, 2);
  assert(list_get(list, number_t, 2)->value == 2);
  list_del(list, 0);
  assert(list_get(list, number_t, 0)->value == 1);
  list_del(list, LIST_TAIL);
  assert(list_get(list, number_t, LIST_TAIL)->value == 3);
  assert(type_equal(list, "list_t") == true);
  dealloc(list);
}
