INCLUDES = \
	-I/usr/include/mozilla \
	-I/usr/include/nspr \
	-I/usr/include/mozilla/dom \
	-I/usr/include/mozilla/windowwatcher \
	-I/usr/include/mozilla/webbrowserpersist \
	-I/usr/include/mozilla/appcomps \
	-I/usr/include/mozilla/find \
	-I/usr/include/mozilla/txtsvc \
	-I/usr/include/mozilla/docshell \
	-I/usr/include/mozilla/shistory \
	-I/usr/include/mozilla/webshell \
	-I/usr/include/mozilla/gfx \
	-I/usr/include/mozilla/necko \
	-I/usr/include/mozilla/widget \
	-I/usr/include/mozilla/content \
	-I/usr/include/mozilla/layout \
	-I/usr/include/mozilla/browser \
	-I/usr/include/mozilla/webbrwsr \
	-I/usr/include/mozilla/string \
	-I/usr/include/mozilla/xpcom \
	-I/usr/include/mozilla/pref \
	-I/usr/include/mozilla/nspr \
	-I/usr/include/mozilla/uconv \
	-I/usr/include/mozilla/embed_base \
	-I/usr/include/mozilla/uriloader \
	$(CFLAGS) $(CPPFLAGS) $(GTK_FLAGS) $(GLIB_FLAGS)
lib_LTLIBRARIES = libwxmozilla.la
AM_CXXFLAGS = -fno-rtti -fno-exceptions
libwxmozilla_la_CFLAGS = -fno-rtti -fno-exceptions $(GTK_FLAGS) $(GLIB_FLAGS)
libwxmozilla_la_SOURCES = \
	wxMozillaBrowser.cpp wxMozillaBrowserChrome.cpp
noinst_HEADERS = \
	wxMozillaBrowser.h wxMozillaBrowserChrome.h wxMozilla.h
libwxmozilla_la_LDFLAGS = -version-info 1:0:0 -rdynamic --whole-archive -fno-rtti -fno-exceptions
libwxmozilla_la_LIBADD = -liberty -lgtkembedmoz -lplds4 -lplc4 -lnspr4 -lxpcom -lmozjs -lpthread -ldl -lc

#optional
# -lpthread
# -fno-rtti
