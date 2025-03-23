//
// Copyright 2020 Fellipe Augusto Ugliara
//
// Use of this source code is governed by an ISC license that can be found
// in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
//
#include "compiler/home.h"
#include "compiler/post.h"
#include "toolbelt.h"

const char info_help[] =
    "Usage: staticgen [FOLDER|--help|--license]\n"
    "Static Weblog Generator makes the Html files of a weblog \n"
    "site from files written with a markup language.\n"
    "\n"
    "Compile weblog in the FOLDER path.\n"
    "\n"
    "  --help     display this help and exit\n"
    "  --license  output license and exit\n";

const char info_license[] =
    "ISC License\n"
    "\n"
    "Copyright 2020 Fellipe Augusto Ugliara\n"
    "\n"
    "Permission to use, copy, modify, and/or distribute this software for any\n"
    "purpose with or without fee is hereby granted, provided that the above\n"
    "copyright notice and this permission notice appear in all copies.\n"
    "\n"
    "THE SOFTWARE IS PROVIDED \"AS IS\" AND THE AUTHOR DISCLAIMS ALL "
    "WARRANTIES\n"
    "WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF\n"
    "MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR\n"
    "ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES\n"
    "WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN\n"
    "ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF\n"
    "OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.\n";

int main(int argc, char **argv) {
  if (argc < 2) {
    term_error("no imput folder\n");
    return EXIT_FAILURE;
  }

  if (argc > 2) {
    term_error("only one argument is expected\n");
    return EXIT_FAILURE;
  }

  if (strcmp(argv[1], "--help") == 0) {
    printf(info_help);
    return EXIT_SUCCESS;
  }

  if (strcmp(argv[1], "--license") == 0) {
    printf(info_license);
    return EXIT_SUCCESS;
  }

  home_t *home = alloc(home_t);
  printf("Weblog Staticgen\n\n");
  post_t *post = alloc(post_t);

  home_compile(home, argv[1]);

  list_for(home->cards, index, home_card_t, item, {
    if (text_compare(item->type, "post") && !text_compare(item->path, "")) {
      post_compile(post, home, item);
    }
  });

  printf("Done\n");

  dealloc(post);
  dealloc(home);
}
