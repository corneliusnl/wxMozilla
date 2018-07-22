AM_CXXFLAGS = -fno-rtti -fno-exceptions 
bin_PROGRAMS = wxMozillaDemo
INCLUDES = \
	-I../src \
	$(CFLAGS) $(CPPFLAGS) $(GTK_FLAGS) $(GLIB_FLAGS)
wxMozillaDemo_CFLAGS =  -fno-rtti -fno-exceptions $(INCLUDES) $(CPPFLAGS) $(CFLAGS)

wxMozillaDemo_SOURCES = main.cpp

#lib_LTLIBRARIES = -lwxmozilla
LDADD = -lplds4 -lplc4 -lnspr4 -lxpcom -lpthread -ldl -lc $(top_builddir)/src/libwxmozilla.la 
wxMozillaDemo_LDFLAGS = -rdynamic -pedantic -rpath /usr/lib/mozilla 

#-fno-rtti
