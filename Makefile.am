AUTOMAKE_OPTIONS = subdir-objects

ACLOCAL_AMFLAGS = ${ACLOCAL_FLAGS}
# FIXME: eugh!!!
AM_CPPFLAGS = -Wall -g @FLTK_CPPFLAGS@ -I./stk/include -DHAVE_GETTIMEOFDAY -D__LINUX_ALSA__ -D__LINUX_ALSASEQ__ -D__LITTLE_ENDIAN__ -DRAWWAVE_PATH=\"/home/nhowie/stk-4.4.3/rawwaves/\"

bin_PROGRAMS = eudyptula
eudyptula_SOURCES = src/Audio.cc src/Audio.h src/Control.h src/KeyboardListener.h src/Main.cc src/Main.h src/MainWidget.cc src/MainWidget.h src/MyKeyMap.h src/Node.h src/Osc.h src/Reverb.h src/TickListener.h

eudyptula_LDADD = $(DEPS_LIBS) -lm -lpthread @FLTK_LIBS@ -L./stk/src -lstk @ALSA_LIBS@ @BOOST_LIBS@ -lasound # -lefence

dist_noinst_SCRIPTS = autogen.sh
