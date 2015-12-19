include $(top_srcdir)/src/Makefile.shared

bin_PROGRAMS = clingo3to4

clingo3to4_CPPFLAGS = $(BOOST_CPPFLAGS)

clingo3to4_LDADD = $(BOOST_REGEX_LIBS) $(BOOST_PROGRAM_OPTIONS_LIBS)

BUILT_SOURCES = main.cpp

clingo3to4_SOURCES = \
main.cpp \
clingo3to4.cpp \
domain.cpp 

