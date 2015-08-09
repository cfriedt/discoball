# The compilation of software known as DiscoBall is distributed under the
# following terms:
#
# Copyright (c) 2015 Christopher Friedt. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# 1. Redistributions of source code must retain the above copyright
# notice, this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright
# notice, this list of conditions and the following disclaimer in the
# documentation and/or other materials provided with the distribution.
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
  linux-pinctrl-example \
  tcpip-example

linux_pinctrl_example_SOURCES = \
  linux-pinctrl-data.h \
  linux-pinctrl-data.c \
  linux-pinctrl-example.c

tcpip_example_SOURCES = \
  tcpip-example.c

tcpip_example_LDADD = \
  ../src/discoball/libdiscoball.la \
  ../src/discoball-tcpip-pthread/libdiscoball-tcpip-pthread.la

if ENABLE_GTEST

gtest_programs = \
  strlen \
  discoball-context-size

strlen_SOURCES = \
  strlen.h \
  strlen.cc \
  strlen-unittest.cc
strlen_LDFLAGS = \
  @GTEST_LDFLAGS@
strlen_CXXFLAGS = \
  @GTEST_CXXFLAGS@

discoball_context_size_SOURCES = \
  discoball_context_size.cc
discoball_context_size_LDADD = \
  ../src/discoball/libdiscoball.la
discoball_context_size_LDFLAGS = \
  @GTEST_LDFLAGS@
discoball_context_size_CXXFLAGS = \
  @GTEST_CXXFLAGS@

endif

noinst_PROGRAMS = \
  $(nongtest_programs) \
  $(gtest_programs)

check-local: $(noinst_PROGRAMS)
	for i in $(nongtest_programs); do \
	  ./$$i || ( TEST FAILED $$i; exit 1 ); \
	  echo "TEST PASSED $$i "; \
	done
	for i in $(gtest_programs); do \
	  @LD_LIBRARY_PATH_VAR@=@GTEST_PATH@/lib \
	    ./$$i --gtest_output=xml:TEST$$i.xml; \
	done
