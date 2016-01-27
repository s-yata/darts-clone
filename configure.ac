#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.67])
AC_INIT([darts-clone], [0.32h], [susumu.yata@gmail.com])
AC_CONFIG_SRCDIR([include/darts.h])
AM_INIT_AUTOMAKE([foreign])

# Checks for programs.
AC_PROG_CXX
AC_PROG_INSTALL

AC_CONFIG_MACRO_DIR([m4])

AM_CXXFLAGS="-Wall -Weffc++ -I\${top_srcdir}/include"

# Checks for libraries.

# Checks for C++ header files.

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

AC_CONFIG_FILES([Makefile
                 include/Makefile
                 src/Makefile
                 test/Makefile])
AC_OUTPUT

echo
echo "${PACKAGE_NAME} ${PACKAGE_VERSION} configuration:"
echo "-----------------------"
echo "  CXX:                   ${CXX}"
echo "  CXXFLAGS:              ${CXXFLAGS} ${AM_CXXFLAGS}"
echo "  LDFLAGS:               ${LDFLAGS} ${AM_LTLDFLAGS}"
echo "  LIBS:                  ${LIBS}"
echo
echo "Paths:"
echo "  Install path prefix:   ${prefix}"
echo

echo "Now type 'make' to build ${PACKAGE_NAME} ${PACKAGE_VERSION}!"
