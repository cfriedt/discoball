# The compilation of software known as DiscoBall is distributed under the
# following terms:
# 
# Copyright (c) 2015 Christopher Friedt. All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the
#    documentation and/or other materials provided with the distribution.
# 
# THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
# FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
# DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
# OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
# HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
# OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
# SUCH DAMAGE.

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
