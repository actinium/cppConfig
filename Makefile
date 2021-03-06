################################################################################
# cppConfig Makefile
################################################################################

CXX= clang++
CXXFLAGS= -Wall -std=c++11 -I$(INCLUDEDIR)

INCLUDEDIR=src

test/test: test/test_1.cpp src/cppconfig.h
	$(CXX) $(CXXFLAGS) -o $@ $<
