ACLOCAL_AMFLAGS = -I m4
AM_CPPFLAGS     =

AM_CPPFLAGS += -I"@HASHPIPE_INCDIR@"
# AM_CPPFLAGS += -I"@XGPU_INCDIR@"

# AM_CFLAGS is used for all C compiles
AM_CFLAGS = -ggdb -fPIC -O3 -Wall -Werror -fno-strict-aliasing -mavx

# Convenience variables to group source files
hello_world_databuf = hello_world_databuf.h \
	        hello_world_databuf.c

hello_world = hello_world_thread.c

# This is the paper_gpu plugin itself
lib_LTLIBRARIES = hello_world.la
hello_world_la_SOURCES = $(hello_world) $(hello_world_databuf)
hello_world_la_LIBADD   = -lrt
hello_world_la_LDFLAGS  = -avoid-version -module -shared -export-dynamic
# hello_world_la_LDFLAGS += -L"@XGPU_LIBDIR@" -Wl,-rpath,"@XGPU_LIBDIR@"
hello_world_la_LDFLAGS += -L"@HASHPIPE_LIBDIR@" -Wl,-rpath,"@HASHPIPE_LIBDIR@"

# Installed scripts
# dist_bin_SCRIPTS = hello_world_init.sh

# Non-installed test programs
# noinst_PROGRAMS = paper_fluff_test
# paper_fluff_test_SOURCES = paper_fluff_test.c $(paper_fluff)
# The paper_fluff_test_CFLAGS is an autotools workaround.
# http://www.gnu.org/software/automake/manual/html_node/Objects-created-both-with-libtool-and-without.html
# paper_fluff_test_CFLAGS = $(AM_CFLAGS)
# paper_fluff_test_LDADD = -lrt

# vi: set ts=8 noet :
