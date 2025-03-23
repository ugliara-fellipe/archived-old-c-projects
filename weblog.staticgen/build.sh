#
# Copyright 2020 Fellipe Augusto Ugliara
#
# Use of this source code is governed by an ISC license that can be found 
# in the LICENSE file at https://github.com/ugliara-fellipe/weblog.staticgen
#
# --------------------
#
# Run this script to deploy staticgen cli and tests
# It require clang; to install use the command:
#
#   $ sudo apt install clang
#
rm -rf ./deploy
mkdir deploy
mkdir deploy/object

TOOLBELT="../library.toolbelt/deploy"
TOOLBELT_INC="-I $TOOLBELT/include"
TOOLBELT_OBJS="$TOOLBELT/object/*.o"

LANGUAGE="../library.language/deploy"
LANGUAGE_INC="-I $LANGUAGE/include"
LANGUAGE_OBJS="$LANGUAGE/object/*.o"

clang compiler/home.c -c -I . $TOOLBELT_INC $LANGUAGE_INC -o deploy/object/home.o
clang compiler/post.c -c -I . $TOOLBELT_INC $LANGUAGE_INC -o deploy/object/post.o

clang cli.c deploy/object/*.o -I . $TOOLBELT_INC $TOOLBELT_OBJS $LANGUAGE_INC $LANGUAGE_OBJS -o deploy/staticgen
