//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#ifndef POST_H
#define POST_H

#include "compiler/home.h"
#include "language.h"
#include "toolbelt.h"

typedef struct {
  recognizer_t *recognizer;
  walker_t *generator;

  text_t *page;
  text_t *post;
} post_t;

def_prototype_header(post_t);

void post_compile(post_t *self, home_t *home, home_card_t *home_post);

void post_test();

#endif
