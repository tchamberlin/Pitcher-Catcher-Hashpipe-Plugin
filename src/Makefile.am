AM_CPPFLAGS = -I"@HASHPIPE_INCDIR@"

# AM_CFLAGS is used for all C compiles
AM_CFLAGS = -ggdb -fPIC -O3 -Wall -Werror -fno-strict-aliasing

# Convenience variables to group source files
pitcher_output_databuf = pitcher_output_databuf.h \
			  pitcher_output_databuf.c

pitcher_catcher = pitcher_thread.c \
		  catcher_thread.c

# This is the paper_gpu plugin itself
lib_LTLIBRARIES = pitcher_catcher.la
pitcher_catcher_la_SOURCES = $(pitcher_catcher) $(pitcher_output_databuf)
pitcher_catcher_la_LIBADD   = -lrt
pitcher_catcher_la_LDFLAGS  = -avoid-version -module -shared -export-dynamic
# pitcher_output_la_LDFLAGS += -L"@XGPU_LIBDIR@" -Wl,-rpath,"@XGPU_LIBDIR@"
pitcher_catcher_la_LDFLAGS += -L"@HASHPIPE_LIBDIR@" -Wl,-rpath,"@HASHPIPE_LIBDIR@"