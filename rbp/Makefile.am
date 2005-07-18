AUTOMAKE_OPTIONS        = foreign
SUBDIRS =

INCLUDES = -I$(top_srcdir) $(all_includes)

lib_LTLIBRARIES =  librbp.la

rbpincludedir = $(includedir)/r
rbpinclude_HEADERS = rbp.h rchromobp.h rchromobp.hh \
					rfirstfitdesheuristic.h rfirstfitdesheuristic.hh rgroupbp.h \
					rgroupbp.hh rinstbp.h rinstbp.hh robjbp.h \
					rfchromobp.h rfinstbp.h rdatabpfile.h
librbp_la_SOURCES = rbp.cpp robjbp.cpp rfchromobp.cpp rfinstbp.cpp \
					rdatabpfile.cpp
librbp_la_LDFLAGS     = -no-undefined -version-info 1:0:0
librbp_la_LIBADD = /usr/lib/libmysqlclient.la $(LIB_R)
