nongtest_programs = \
  linux_pinctrl_example

linux_pinctrl_example_SOURCES = \
  linux_pinctrl_data.h \
  linux_pinctrl_data.c \
  linux_pinctrl_example.c

if ENABLE_GTEST

gtest_programs = strlen

strlen_CXXFLAGS = @GTEST_CXXFLAGS@
strlen_LDFLAGS = @GTEST_LDFLAGS@
strlen_SOURCES = \
  strlen.h \
  strlen.cc \
  strlen_unittest.cc

endif

noinst_PROGRAMS = \
  $(nongtest_programs) \
  $(gtest_programs)

check-local: $(noinst_PROGRAMS)
	for i in $(nongtest_programs); do \
	  ./$$i; \
	done
	for i in $(gtest_programs); do \
	  @LD_LIBRARY_PATH_VAR@=@GTEST_PATH@/lib \
	    ./$$i --gtest_output=xml:TEST$$i.xml; \
	done
