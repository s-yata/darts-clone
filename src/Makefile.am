AM_CXXFLAGS = -Wall -Weffc++ -I$(top_srcdir)/include

bin_PROGRAMS = mkdarts darts darts-benchmark

mkdarts_SOURCES = mkdarts.cc
darts_SOURCES = darts.cc
darts_benchmark_SOURCES = darts-benchmark.cc

EXTRA_HEADERS = \
	timer.h \
	lexicon.h \
	mersenne-twister.h \
	mkdarts-config.h \
	darts-config.h \
	benchmark-config.h

EXTRA_DIST = ${EXTRA_HEADERS}
