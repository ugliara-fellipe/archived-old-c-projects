//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#include "extend/prototype.h"
#include "extend/inspect.h"

static object_t object_init(object_t self, object_t prototype_header) {
  header_t *header = self;
  memcpy(header, prototype_header, sizeof(header_t));
  header->_context_ = NULL;
  header->_referrers_ = NULL;
  return (cast(object_t, header) + sizeof(header_t));
}

object_t object_alloc(size_t type_size, header_t *header, ...) {
  object_t self = object_init(calloc(1, sizeof(header_t) + type_size), header);
  va_list arguments;
  va_start(arguments, header);
  header->_alloc_(self, arguments);
  va_end(arguments);
  return self;
}

static header_t *get_header(object_t self) {
  return ((header_t *)(cast(object_t, self) - sizeof(header_t)));
}

void dealloc(object_t self) {
  get_header(self)->_free_(self);
  ref_t *node = get_header(self)->_referrers_;
  while (node != NULL) {
    ref_t *temp = node->next;
    *(node->address) = NULL;
    free(node);
    node = temp;
  }
  free(get_header(self));
}

static size_t object_sizeof(object_t self) {
  return get_header(self)->_size_();
}

object_t copy(object_t self) {
  object_t result = object_init(
      calloc(1, sizeof(header_t) + object_sizeof(self)), get_header(self));
  get_header(self)->_copy_(self, result);
  return result;
}

object_t clone(object_t self, ...) {
  va_list arguments;
  va_start(arguments, self);
  object_t result = object_init(
      calloc(1, sizeof(header_t) + object_sizeof(self)), get_header(self));
  get_header(self)->_alloc_(result, arguments);
  va_end(arguments);
  return result;
}

void attach(object_t self, void **address) {
  ref_t *ref = calloc(1, sizeof(ref_t));
  ref->address = address;
  ref->next = NULL;
  ref_t *node = get_header(self)->_referrers_;
  if (node != NULL) {
    ref->next = node;
  }
  get_header(self)->_referrers_ = ref;
  *(address) = self;
}

void detach(object_t self, void **address) {
  ref_t *node = get_header(self)->_referrers_;
  if (node->next == NULL) {
    if (node->address == address) {
      get_header(self)->_referrers_ = NULL;
      free(node);
      *(address) = NULL;
      return;
    }
  }
  ref_t *previous = node;
  do {
    if (node->address == address) {
      if (node == previous) {
        get_header(self)->_referrers_ = node->next;
      } else {
        previous->next = node->next;
      }
      free(node);
      *(address) = NULL;
      return;
    }
    previous = node;
    node = node->next;
  } while (node != NULL);
}

void context_set(object_t self, const char *context) {
  get_header(self)->_context_ = context;
}

const char *context_get(object_t self) { return get_header(self)->_context_; }

const char *object_type(object_t self) { return get_header(self)->_type_(); }

bool type_equal(object_t self, const char *str) {
  return (strcmp(get_header(self)->_type_(), str) ? false : true);
}

bool object_type_equal(object_t self, object_t object) {
  return (strcmp(get_header(self)->_type_(), get_header(object)->_type_())
              ? false
              : true);
}

bool equal(object_t self, object_t object) {
  if (object_type_equal(self, object)) {
    return get_header(self)->_equal_(self, object);
  }
  return false;
}

void object_inspect(object_t self, void *inspect) {
  get_header(self)->_inspect_(self, inspect);
}

void inspect(object_t self, const char *snapshot) {
  inspect_t *inspect = inspect_alloc();
  object_inspect(self, inspect);
  inspect_perform(inspect, snapshot);
  inspect_dealloc(inspect);
}

size_t ref_size(object_t self) {
  size_t result = 0;
  ref_t *ref = get_header(self)->_referrers_;
  if (ref != NULL) {
    result++;
    while (ref->next != NULL) {
      result++;
      ref = ref->next;
    }
  }
  return result;
}

ref_t *ref_head(object_t self) { return get_header(self)->_referrers_; }

void prototype_test() {}
