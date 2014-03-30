bin_PROGRAMS = mkdarts darts

mkdarts_SOURCES = mkdarts.cc
darts_SOURCES = darts.cc

include_HEADERS = ${top_srcdir}/include/darts.h

EXTRA_HEADERS = \
	timer.h \
	lexicon.h \
	mersenne-twister.h \
	mkdarts-config.h \
	darts-config.h \
	benchmark-config.h

EXTRA_DIST = ${EXTRA_HEADERS}
