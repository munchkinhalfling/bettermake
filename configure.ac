#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([bettermake], [1.0], [munchkinhalfling@pm.me])
AM_INIT_AUTOMAKE
AC_CONFIG_SRCDIR([src/header.cpp])
AC_CONFIG_HEADERS([config.h])

# Checks for programs.
AC_PROG_CXX

# Checks for libraries.
# libcyaml
LDFLAGS="$LDFLAGS -L/usr/local/lib"
AC_CHECK_LIB([cyaml], [cyaml_load_file])

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile])
AC_OUTPUT
