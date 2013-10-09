AC_INIT([Eudyptula], [0.1], [neil.howie@yahoo.co.uk], [eudyptula], [http://hello.example.com/])
AC_PREREQ([2.68])
AM_INIT_AUTOMAKE([1.10 no-define])
AC_CONFIG_HEADERS([config.h])
AC_PROG_CC
AC_PROG_CXX
AC_CONFIG_FILES([Makefile])

# Get FLTK library and include locations
AC_ARG_WITH([fltk-include-path],
  [AS_HELP_STRING([--with-fltk-include-path],
    [location of the FLTK headers, defaults to /usr/local/include])],
  [FLTK_CPPFLAGS="-I$withval"],
  [FLTK_CPPFLAGS='-I/usr/local/include/'])
AC_SUBST([FLTK_CPPFLAGS])

AC_ARG_WITH([fltk-lib-path],
  [AS_HELP_STRING([--with-fltk-lib-path], [location of the FLTK libraries])],
  [FLTK_LIBS="-L$withval -lfltk -ldl -lX11 -lXext"],
  [FLTK_LIBS='-lfltk -ldl -lX11 -lXext'])
AC_SUBST([FLTK_LIBS])

# Get BOOST library and include locations
AC_ARG_WITH([boost-include-path],
  [AS_HELP_STRING([--with-boost-include-path],
    [location of the BOOST headers, defaults to /usr/include])],
  [BOOST_CPPFLAGS="-I$withval"],
  [BOOST_CPPFLAGS='-I/usr/include/'])
AC_SUBST([BOOST_CPPFLAGS])

AC_ARG_WITH([boost-lib-path],
  [AS_HELP_STRING([--with-boost-lib-path], [location of the BOOST libraries])],
  [BOOST_LIBS="-L$withval -lboost_thread-mt"],
  [BOOST_LIBS='-lboost_thread-mt'])
AC_SUBST([BOOST_LIBS])

AC_CHECK_LIB(asound,snd_pcm_hw_params_get_access_mask,
  [AC_COMPILE_IFELSE([AC_LANG_PROGRAM([[#ifdef HAVE_ALSA_ASOUNDLIB_H
#include <alsa/asoundlib.h>
#elif defined(HAVE_SYS_ASOUNDLIB_H)
#include <sys/asoundlib.h>
#endif]], [[snd_pcm_hw_params_get_access_mask(NULL, NULL)]])],
  [ALSA_LIBS="-lasound"])])
AC_SUBST([ALSA_LIBS])

AC_OUTPUT

