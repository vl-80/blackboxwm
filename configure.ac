#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.71])
AC_INIT([blackbox],[0.77],[http://github.com/bbidulock/blackboxwm],[blackbox],[http://github.com/bbidulock/blackboxwm/issues])
AC_REVISION([0.77])

# set better defaults
AC_PREFIX_DEFAULT([/usr])
if test "$prefix" = /usr -o "$prefix" = NONE; then
	test "$sysconfdir" = '${prefix}/etc' && sysconfdir=/etc
	test "$sharedstatedir" = '${prefix}/com' && sharedstatedir=/var
	test "$localstatedir" = '${prefix}/var' && localstatedir=/var
fi

AC_CONFIG_SRCDIR([src/blackbox.cc])
AC_CONFIG_HEADERS([config.h])
AC_CONFIG_MACRO_DIR([m4])
AC_CONFIG_AUX_DIR([scripts])
AC_USE_SYSTEM_EXTENSIONS
AC_CANONICAL_TARGET

DATE='2021-05-11'
AC_SUBST([DATE])

MDOCDATE='May 11, 2021'
AC_SUBST([MDOCDATE])

BRANCH='0.77'
AC_SUBST([BRANCH])

# Initialize Automake
AM_INIT_AUTOMAKE([gnits 1.16 dist-lzip no-dist-gzip std-options -Wall color-tests silent-rules tar-pax])
AM_MAINTAINER_MODE
AM_SILENT_RULES([yes])

# Checks for programs.
AC_PROG_SED
AC_PROG_AWK
AC_PROG_EGREP
AC_PROG_CC
AC_PROG_CPP
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AM_PROG_AR
AC_PROG_MKDIR_P
AC_ARG_VAR([LD], [Linker loader command])

AC_ARG_VAR([MARKDOWN],[markdown command. @<:@default=markdown@:>@])
AC_CHECK_PROGS([MARKDOWN],[markdown],[${am_missing_run}markdown],[$PATH])

AC_ARG_VAR([ASCIIDOC],[asciidoc command. @<:@default=asciidoctor@:>@])
AC_CHECK_PROGS([ASCIIDOC],[asciidoc asciidoctor],[${am_missing_run}asciidoc],[$PATH])

AC_ARG_VAR([ASCIIDOC_BACKEND],[asciidoc backend @<:@default=NONE@:>@])
if test -z "$ASCIIDOC_BACKEND"; then
	case "$ASCIIDOC" in
		asciidoc) ASCIIDOC_BACKEND="--backend=html4" ;;
		asciidoctor) ASCIIDOC_BACKEND="--backend=html5" ;;
		*) AC_MSG_WARN([ASCIIDOC $ASCIIDOC is not supported.]) ;;
	esac
fi

AC_ARG_VAR([ASCIIMAN],[asciidoc to manpage converter. @<:@default=a2x@:>@])
AC_CHECK_PROGS([ASCIIMAN],[a2x asciidoctor],[${am_missing_run}a2x],[$PATH])

AC_ARG_VAR([ASCIIMAN_FORMAT],[asciidoc manpage option @<:@default=NONE@:>@])
if test -z "$ASCIIMAN_FORMAT"; then
	case "$ASCIIMAN" in
		a2x) ASCIIMAN_FORMAT="--format=manpage" ;;
		asciidoctor) ASCIIMAN_FORMAT="--backend=manpage" ;;
		*) AC_MSG_WARN([ASCIIMAN $ASCIIMAN is not supported.]) ;;
	esac
fi

AC_ARG_VAR([LINKS],[links command. @<:@default=lynx@:>@])
AC_CHECK_PROGS([LINKS],[lynx links],[${am_missing_run}lynx],[$PATH])
if test "$LINKS" = "links"; then
	LINKS="links -codepage utf-8"
fi

dnl libbt shouldn't be shared by default (yet)
AC_DISABLE_SHARED
LT_PATH_LD
LT_PREREQ([2.4.2])
LT_INIT([])
LT_LANG([C++])
AC_SUBST([LIBTOOL_DEPS])

AM_GNU_GETTEXT_VERSION([0.21])
AM_GNU_GETTEXT([external])

AC_LANG([C++])

PKG_PROG_PKG_CONFIG([0.14.0])

# Checks for header files.
AS_BOX([Header Files])
AC_CHECK_INCLUDES_DEFAULT

AC_PATH_X
AC_PATH_XTRA
AC_CHECK_HEADERS([fcntl.h langinfo.h limits.h locale.h string.h sys/time.h unistd.h libintl.h])

# Checks for typedefs, structures, and compiler characteristics.
AS_BOX([Typedefs, Structures, Compiler])
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_MODE_T
AC_TYPE_SIZE_T

# Checks for library functions.
AS_BOX([Library Functions])
AC_FUNC_FORK
AC_FUNC_MALLOC
AC_FUNC_STRNLEN
AC_CHECK_FUNCS([gethostname gettimeofday memmove memset mkdir nl_langinfo putenv select setlocale sqrt strcasecmp strncasecmp strtol strtoul])

AS_BOX([X11 Extension Libraries])

PKG_CHECK_MODULES([X11],[x11])
PKG_CHECK_MODULES([XEXT],[xext], [],
	[enable_shape=no
	 enable_mitshm=no])

AC_ARG_ENABLE([shape],
    AS_HELP_STRING([--disable-shape],[Disable use of SHAPE extension @<:@default=auto@:>@]))
if test x$enable_shape != xno ; then
    AC_CHECK_LIB([Xext],[XShapeCombineShape],
	[AC_DEFINE([SHAPE],[1],[Define to enable SHAPE extension.])],
	[enable_shape=no])
fi

AC_ARG_ENABLE([mitshm],
    AS_HELP_STRING([--disable-mitshm],[Disable use of the MIT-SHM extension @<:@default=auto@:>@]))
if test x$enable_mitshm != xno ; then
    AC_CHECK_LIB([Xext],[XShmPutImage],
	[AC_DEFINE([MITSHM],[1],[Define to enable MIT-SHM extension.])],
	[enable_mitshm=no])
fi

AC_ARG_ENABLE([xft],
    AS_HELP_STRING([--disable-xft],[Disable use of XFT library @<:@default=auto@:>@]))
if test x$enable_xft != xno ; then
    PKG_CHECK_MODULES([XFT],[xft >= 2.0.0],
	[AC_DEFINE([XFT],[1],[Define to enable XFT library.])
	 XFT_PKGCONFIG='xft >= 2.0.0'],
	[enable_xft=no
	 XFT_PKGCONFIG=''])
fi
AC_SUBST([XFT_PKGCONFIG])

AC_ARG_ENABLE([debug],
    AS_HELP_STRING([--enable-debug],[Enable use of verbose debugging code @<:@default=no@:>@]))
if test x$enable_debug = xyes ; then
    AC_DEFINE([DEBUG],[1],[Define to enable debugging code.])
fi

AC_ARG_ENABLE([debug-colorcache],
    AS_HELP_STRING([--enable-debug-colorcache],[Enable color cache debugging code @<:@default=no@:>@]))
if test x$enable_debug_colorcache = xyes ; then
    AC_DEFINE([COLORCACHE_DEBUG],[1],[Define to debug color cache code.])
fi

AC_ARG_ENABLE([debug-colortable],
    AS_HELP_STRING([--enable-debug-colortable],[Enable color table debugging code @<:@default=no@:>@]))
if test x$enable_debug_colortable = xyes ; then
    AC_DEFINE([COLORCACHE_DEBUG],[1],[Define to debug color table code.])
fi

AC_ARG_ENABLE([debug-focus],
    AS_HELP_STRING([--enable-debug-focus],[Enable focus debugging code @<:@default=no@:>@]))
if test x$enable_debug_focus = xyes ; then
    AC_DEFINE([FOCUS_DEBUG],[1],[Define to debug focus code.])
fi

AC_ARG_ENABLE([debug-fontcache],
    AS_HELP_STRING([--enable-debug-fontcache],[Enable font cache debugging code @<:@default=no@:>@]))
if test x$enable_debug_fontcache = xyes ; then
    AC_DEFINE([FONTCACHE_DEBUG],[1],[Define to debug font cache code.])
fi

AC_ARG_ENABLE([debug-mitshm],
    AS_HELP_STRING([--enable-debug-mitshm],[Enable MIT-SHM debugging code @<:@default=no@:>@]))
if test x$enable_debug_mitshm = xyes ; then
    AC_DEFINE([MITSHM_DEBUG],[1],[Define to debug MIT-SHM code.])
fi

AC_ARG_ENABLE([debug-pixmapcache],
    AS_HELP_STRING([--enable-debug-pixmapcache],[Enable pixmap cache debugging code @<:@default=no@:>@]))
if test x$enable_debug_pixmapcache = xyes ; then
    AC_DEFINE([FONTCACHE_DEBUG],[1],[Define to debug pixmap cache code.])
fi

AC_ARG_ENABLE([print-sizes],
    AS_HELP_STRING([--enable-print-sizes],[Enable printing of structure sizes on startup. @<:@default=no@:>@]))
if test x$enable_print_sizes = xyes ; then
    AC_DEFINE([PRINT_SIZES],[1],[Define to print structure sizes on startup.])
fi

AC_ARG_ENABLE([fullscreen],
    AS_HELP_STRING([--disable-fullscreen],[Disable fullscreen item in window menu. @<:@default=enabled@:>@]))
if test x$enable_fullscreen != xno ; then
    AC_DEFINE([WITH_FULLSCREEN],[1],[Define to add fullscreen item to window menu.])
fi

AM_CONDITIONAL([USE_NLS],[test x$enable_nls != xno])

test "x$prefix" = xNONE && prefix="$ac_default_prefix"
LOCDIR="$localedir"
eval "LOCDIR=\"$LOCDIR\""
eval "LOCDIR=\"$LOCDIR\""
eval "LOCDIR=\"$LOCDIR\""
AC_SUBST([LOCDIR])

AC_CONFIG_FILES([version.h
		 Makefile
		 po/Makefile.in
		 data/Makefile
		 data/styles/Makefile
		 doc/Makefile
		 doc/fr_FR/Makefile
		 doc/ja_JP/Makefile
		 doc/nl_NL/Makefile
		 doc/sl_SI/Makefile
		 lib/Makefile
		 lib/libbt.pc
		 src/Makefile
		 util/Makefile])
AC_OUTPUT

# vim: set ft=config:
