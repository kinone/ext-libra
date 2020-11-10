dnl config.m4 for extension libra

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary.

dnl If your extension references something external, use with:

dnl PHP_ARG_WITH(libra, for libra support,
dnl Make sure that the comment is aligned:
dnl [  --with-libra             Include libra support])

dnl Otherwise use enable:

PHP_ARG_ENABLE(libra, whether to enable libra support,
dnl Make sure that the comment is aligned:
[  --enable-libra          Enable libra support], no)

if test "$PHP_LIBRA" != "no"; then
  dnl Write more examples of tests here...

  dnl # get library opencv build options from pkg-config output
  AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  AC_MSG_CHECKING(for opencv)
  if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists opencv; then
    if $PKG_CONFIG opencv --atleast-version 3.4.12; then
      LIBOPENCV_CFLAGS=`$PKG_CONFIG opencv --cflags`
      LIBOPENCV_LIBDIR=`$PKG_CONFIG opencv --libs`
      LIBOPENCV_VERSON=`$PKG_CONFIG opencv --modversion`
      AC_MSG_RESULT(from pkgconfig: version $LIBOPENCV_VERSON)
    else
      AC_MSG_ERROR(system opencv is too old: version 3.4.12 required)
    fi
  else
    AC_MSG_ERROR(pkg-config not found)
  fi
  PHP_EVAL_LIBLINE($LIBOPENCV_LIBDIR, LIBRA_SHARED_LIBADD)
  PHP_EVAL_INCLINE($LIBOPENCV_CFLAGS)

  dnl # get library libwebp build options from pkg-config output
  AC_PATH_PROG(PKG_CONFIG, pkg-config, no)
  AC_MSG_CHECKING(for libwebp)
  if test -x "$PKG_CONFIG" && $PKG_CONFIG --exists libwebp; then
    if $PKG_CONFIG libwebp --atleast-version 1.1.0; then
      LIBWEBP_CFLAGS=`$PKG_CONFIG libwebp --cflags`
      LIBWEBP_LIBDIR=`$PKG_CONFIG libwebpmux --libs`
      LIBWEBP_VERSON=`$PKG_CONFIG libwebp --modversion`
      AC_MSG_RESULT(from pkgconfig: version $LIBWEBP_VERSON)
    else
      AC_MSG_ERROR(system libwep is too old: version 1.1.0 required)
    fi
  else
    AC_MSG_ERROR(pkg-config not found)
  fi
  PHP_EVAL_LIBLINE($LIBWEBP_LIBDIR, LIBRA_SHARED_LIBADD)
  PHP_EVAL_INCLINE($LIBWEBP_CFLAGS)

  dnl # --with-libra -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/libra.h"  # you most likely want to change this
  dnl if test -r $PHP_LIBRA/$SEARCH_FOR; then # path given as parameter
  dnl   LIBRA_DIR=$PHP_LIBRA
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for libra files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       LIBRA_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$LIBRA_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the libra distribution])
  dnl fi

  dnl # --with-libra -> add include path
  dnl PHP_ADD_INCLUDE($LIBRA_DIR/include)

  dnl # --with-libra -> check for lib and symbol presence
  dnl LIBNAME=LIBRA # you may want to change this
  dnl LIBSYMBOL=LIBRA # you most likely want to change this

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $LIBRA_DIR/$PHP_LIBDIR, LIBRA_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_LIBRALIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong libra lib version or lib not found])
  dnl ],[
  dnl   -L$LIBRA_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl

  PHP_SUBST(LIBRA_SHARED_LIBADD)

  dnl # In case of no dependencies
  AC_DEFINE(HAVE_LIBRA, 1, [ Have libra support ])

  PHP_REQUIRE_CXX()
  PHP_ADD_LIBRARY(stdc++, 1, XMLSCHEMA_SHARED_LIBADD)

  PHP_NEW_EXTENSION(libra, libra.cpp                 \
   libra_kaleido.cpp                                 \
   libra_image.cpp                                   \
   src/*.cpp,
   $ext_shared)
fi
