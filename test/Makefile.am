AM_CXXFLAGS = -Wall -Weffc++ -I${top_srcdir}/include

TESTS = \
	test-darts \
	test-compat \
	test-tools.sh

noinst_PROGRAMS = test-darts test-compat

test_darts_SOURCES = test-darts.cc

test_compat_SOURCES = test-compat.cc

dist_noinst_DATA = test-tools.sh

EXTRA_DIST = \
	correct-dic \
	correct-result \
	test-lexicon \
	test-text
