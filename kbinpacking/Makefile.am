####### kdevelop will overwrite this part!!! (begin)##########
bin_PROGRAMS = kbinpacking

## INCLUDES were found outside kdevelop specific part

kbinpacking_SOURCES = kappoptions.ui kbpgaview.cpp kbpprjview.cpp kbinpackingview.cpp \
	kbinpackingdoc.cpp kbinpacking.cpp main.cpp qdrawgroups.cpp
kbinpacking_LDFLAGS=$(all_libraries) -export-dynamic $(KDE_RPATH)
kbinpacking_LDADD   = $(KBINPACKING_ADD) $(LIB_R) \
	$(LIB_KFILE) $(LIB_KDEUI) $(LIB_KDECORE) $(LIB_QT) $(LIBSOCKET)

SUBDIRS =

EXTRA_DIST = main.cpp kbinpacking.cpp kbinpacking.h kbinpackingdoc.cpp kbinpackingdoc.h \
	kbinpackingview.cpp kbinpackingview.h kbinpackingui.rc kbinpacking.desktop \
	lo32-app-kbinpacking.png lo16-app-kbinpacking.png kbpprjview.cpp kbpprjview.h \
	kbpgaview.cpp kbpgaview.h kappoptions.ui qdrawgroups.cpp qdrawgroups.h

install-data-local:
	$(mkinstalldirs) $(kde_appsdir)/Applications/
	$(INSTALL_DATA) $(srcdir)/kbinpacking.desktop $(kde_appsdir)/Applications/kbinpacking.desktop
	$(mkinstalldirs) $(kde_icondir)/locolor/32x32/apps/
	$(INSTALL_DATA) $(srcdir)/lo32-app-kbinpacking.png $(kde_icondir)/locolor/32x32/apps/kbinpacking.png
	$(mkinstalldirs) $(kde_icondir)/locolor/16x16/apps/
	$(INSTALL_DATA) $(srcdir)/lo16-app-kbinpacking.png $(kde_icondir)/locolor/16x16/apps/kbinpacking.png

uninstall-local:
	-rm -f $(kde_appsdir)/Applications/kbinpacking.desktop
	-rm -f $(kde_icondir)/locolor/32x32/apps/kbinpacking.png
	-rm -f $(kde_icondir)/locolor/16x16/apps/kbinpacking.png

####### kdevelop will overwrite this part!!! (end)############
# this 10 paths are KDE specific. Use them:
# kde_htmldir       Where your docs should go to. (contains lang subdirs)
# kde_appsdir       Where your application file (.kdelnk) should go to. 
# kde_icondir       Where your icon should go to.
# kde_minidir       Where your mini icon should go to.
# kde_datadir       Where you install application data. (Use a subdir)
# kde_locale        Where translation files should go to.(contains lang subdirs)
# kde_cgidir        Where cgi-bin executables should go to.
# kde_confdir       Where config files should go to.
# kde_mimedir       Where mimetypes should go to.
# kde_toolbardir    Where general toolbar icons should go to.
# kde_wallpaperdir  Where general wallpapers should go to.

# set the include path for X, qt and KDE
INCLUDES= $(all_includes)


METASOURCES = AUTO

rcdir = $(kde_datadir)/kbinpacking
rc_DATA = kbinpackingui.rc

messages: rc.cpp
	LIST=`find . -name \*.h -o -name \*.hh -o -name \*.H -o -name \*.hxx -o -name \*.hpp -o -name \*.cpp -o -name \*.cc -o -name \*.cxx -o -name \*.ecpp -o -name \*.C`; \
	if test -n "$$LIST"; then \
	 $(XGETTEXT) $$LIST -o $(podir)/kbinpacking.pot; \
	fi

