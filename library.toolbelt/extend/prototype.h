//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/library.toolbelt
//
#ifndef PROTOTYPE_H
#define PROTOTYPE_H

#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef size_t index_t;
typedef void *object_t;
typedef va_list args_t;

typedef struct ref_t ref_t;

struct ref_t {
  void **address;
  ref_t *next;
};

typedef struct {
  const char *_context_;
  const char *(*_type_)(void);
  size_t (*_size_)(void);
  void (*_alloc_)(object_t, args_t);
  void (*_free_)(object_t);
  void (*_copy_)(object_t, object_t);
  bool (*_equal_)(object_t, object_t);
  void (*_inspect_)(object_t, void *);
  ref_t *_referrers_;
} header_t;

#define next_arg(args, type) va_arg(args, type)

#define cast(type, object) ((type)object)

#define def_prototype_header(type) header_t *type##_prototype_header();

#define def_prototype_source(type, _alloc_, _free_, _copy_, _equal_,           \
                             _inspect_)                                        \
  static const char *_##type##_type_() { return #type; }                       \
                                                                               \
  static size_t _##type##_size_() { return sizeof(type); }                     \
                                                                               \
  static header_t type##_header_prototype =                                    \
      (header_t){NULL,                                                         \
                 _##type##_type_,                                              \
                 _##type##_size_,                                              \
                 ((void (*)(object_t, args_t))_alloc_),                        \
                 ((void (*)(object_t))_free_),                                 \
                 ((void (*)(object_t, object_t))_copy_),                       \
                 ((bool (*)(object_t, object_t))_equal_),                      \
                 ((void (*)(object_t, void *))_inspect_),                      \
                 NULL};                                                        \
                                                                               \
  header_t *type##_prototype_header() { return &type##_header_prototype; }

object_t object_alloc(size_t type_size, header_t *header, ...);

#define alloc(type, ...)                                                       \
  object_alloc(sizeof(type), type##_prototype_header(), ##__VA_ARGS__, NULL)

void dealloc(object_t self);

object_t copy(object_t self);
object_t clone(object_t self, ...);

void attach(object_t self, void **address);
void detach(object_t self, void **address);

void context_set(object_t self, const char *context);
const char *context_get(object_t self);

const char *object_type(object_t self);
bool type_equal(object_t self, const char *str);
bool object_type_equal(object_t self, object_t object);
bool equal(object_t self, object_t object);

void object_inspect(object_t self, void *inspect);
void inspect(object_t self, const char *snapshot);

size_t ref_size(object_t self);
ref_t *ref_head(object_t self);

void prototype_test();

#endif
