ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS     =

AM_CPPFLAGS += -I"@HASHPIPE_INCDIR@"
# AM_CPPFLAGS += -I"@XGPU_INCDIR@"

# AM_CFLAGS is used for all C compiles
AM_CFLAGS = -ggdb -fPIC -O3 -Wall -Werror -fno-strict-aliasing -mavx

# Convenience variables to group source files
example_databuf = example_databuf.h \
	        example_databuf.c

example = pitcher_thread.c \
	  catcher_thread.c

# This is the paper_gpu plugin itself
lib_LTLIBRARIES = example.la
example_la_SOURCES = $(example) $(example_databuf)
example_la_LIBADD   = -lrt
example_la_LDFLAGS  = -avoid-version -module -shared -export-dynamic
# example_la_LDFLAGS += -L"@XGPU_LIBDIR@" -Wl,-rpath,"@XGPU_LIBDIR@"
example_la_LDFLAGS += -L"@HASHPIPE_LIBDIR@" -Wl,-rpath,"@HASHPIPE_LIBDIR@"

# Installed scripts
# dist_bin_SCRIPTS = example_init.sh

# Non-installed test programs
# noinst_PROGRAMS = paper_fluff_test
# paper_fluff_test_SOURCES = paper_fluff_test.c $(paper_fluff)
# The paper_fluff_test_CFLAGS is an autotools workaround.
# http://www.gnu.org/software/automake/manual/html_node/Objects-created-both-with-libtool-and-without.html
# paper_fluff_test_CFLAGS = $(AM_CFLAGS)
# paper_fluff_test_LDADD = -lrt

# vi: set ts=8 noet :
