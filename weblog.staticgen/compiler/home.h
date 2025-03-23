//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#ifndef HOME_H
#define HOME_H

#include "language.h"
#include "toolbelt.h"

typedef struct {
  text_t *type;
  text_t *size;
  text_t *date;
  text_t *show;
  text_t *group;
  text_t *link;
  text_t *path;
  text_t *title;
  text_t *text;
} home_card_t;

def_prototype_header(home_card_t);

typedef struct {
  recognizer_t *recognizer;
  walker_t *generator;

  text_t *path;

  text_t *group;
  home_card_t *card;
  text_t *value;

  text_t *weblog_title;
  text_t *weblog_brief;
  text_t *weblog_tags;

  text_t *copyright_year;
  text_t *copyright_owner;

  text_t *license_link;
  text_t *license_type;
  text_t *license_file;

  text_t *content_link;
  text_t *content_site;
  text_t *content_type;
  text_t *content_name;
  text_t *content_file;

  list_t *cards;

  text_t *page;
} home_t;

def_prototype_header(home_t);

void home_compile(home_t *self, const char *home_path);

void home_test();

#endif
