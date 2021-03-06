dnl Init
AC_INIT([efighter], [0.0.1], [root@epiar.net])
AC_PREREQ(2.50)

dnl Detect the canonical host and target build environment
AC_CANONICAL_HOST
AC_CANONICAL_TARGET 

AM_INIT_AUTOMAKE(efighter, 0.0.1)
AM_CONFIG_HEADER(config.h)

AC_PROG_CPP
AC_PROG_CXX
AC_PROG_CC
AC_PROG_RANLIB
AC_LANG(C++)

dnl Check for a C++ compiler
if test "$ac_cv_prog_cxx_g" == no
then
	AC_MSG_ERROR([Cannot find a working C++ compiler])
fi

dnl Check for libxml2
case "$target" in
	*-*-linux* | *-*-cygwin* | *-*-mingw32* | *-*-freebsd* | *-apple-darwin*)
	PKG_CHECK_MODULES([libxml2], [libxml-2.0 >= 2.7.6])
	CFLAGS="$CFLAGS $libxml2_CFLAGS"
	LIBS="$LIBS $libxml2_LIBS"
esac

dnl Check for SDL
SDL_VERSION=1.2.12

case "$target" in
	*-*-linux* | *-*-cygwin* | *-*-mingw32* | *-*-freebsd*)
		AM_PATH_SDL($SDL_VERSION, :, AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))
		CFLAGS="$CFLAGS $SDL_CFLAGS -DCOMP_GCC"
		LIBS="$LIBS $SDL_LIBS"
esac
case "$target" in
	*-apple-darwin*)
	CFLAGS="$CFLAGS -DCOMP_GCC -I/Developer/Library/Frameworks/SDL.Framework/Headers -I/System/Library/Frameworks/OpenGL.framework/Headers"
	LIBS="$LIBS -framework SDL -framework OpenGL -framework Cocoa SDLMain.m"
esac

dnl Check for SDL_image
case "$target" in
	*-*-linux* | *-*-cygwin* | *-*-mingw32* | *-*-freebsd*)
	PKG_CHECK_MODULES([SDL_image], [SDL_image >= 1.2.10])
	CFLAGS="$CFLAGS $SDL_image_CFLAGS"
	LIBS="$LIBS $SDL_image_LIBS"
esac
case "$target" in
	*-apple-darwin*)
	CFLAGS="$CFLAGS -I/Developer/Library/Frameworks/SDL_image.Framework/Headers"
	LIBS="$LIBS -framework SDL_image"
esac

dnl Check for SDL_mixer
case "$target" in
	*-*-linux* | *-*-cygwin* | *-*-mingw32* | *-*-freebsd*)
	PKG_CHECK_MODULES([SDL_mixer], [SDL_mixer >= 1.2.11])
	CFLAGS="$CFLAGS $SDL_mixer_CFLAGS"
	LIBS="$LIBS $SDL_mixer_LIBS"
esac
case "$target" in
	*-apple-darwin*)
	CFLAGS="$CFLAGS -I/Library/Frameworks/SDL_mixer.Framework/Headers"
	LIBS="$LIBS -framework SDL_mixer"
esac

dnl Set MS Windows specific options - For afont and ntohl (Win32 provides this through Winsock)
case "$target" in
	*-*-cygwin* | *-*-mingw32*)
		LIBS="$LIBS -lwsock32 -lz"
		;;
esac

dnl Set MinGW-specific options
case "$target" in
	*-*-mingw32*)
		LIBS="$LIBS -lopengl32"
		;;
esac

dnl Set Unix specific options
case "$target" in
	*-*-linux* | *-*-freebsd*)
		CFLAGS="$CFLAGS -DUNIX -I/usr/include/GL"
		LIBS="$LIBS -lGL -lGLU -lz"
		;;
esac

dnl Set OS X specific options
case "$target" in
	*-apple-darwin*)
		CFLAGS="$CFLAGS -DDARWIN"
		LIBS="$LIBS"
		;;
esac

CFLAGS="$CFLAGS -Wall"
CXXFLAGS="$CFLAGS"

AC_OUTPUT([Makefile])
