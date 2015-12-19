INCLUDEDIR = ../include
LIBDIR   = ../lib
TARGETS = student_header
STUDENT_HEADER_FILES = fileMgr.h global.h syscat.h tableInfo.h blockBuffer.h errorObj.h loadTool.cpp
TARGET = student_header
include ../Makefile.common

.PHONY: student_header

student_header: $(STUDENT_HEADER_FILES)

.SUFFIXIES:
.SUFFIXIES: .h .cpp

%.h %.h:
	@echo "Create $@ from $<";
	@cat $(INCLUDEDIR)/$< | awk 'BEGIN{skip=0} \
	{if($$0 ~ /.*@START@.*/){skip=1};if(skip==0){print $$0};\
	 if($$0 ~ /.*@END@.*/){skip=0}}' >$@

%.cpp %.cpp:
	@echo "Create $@ from $<";
	@cat $(INCLUDEDIR)/$< | awk 'BEGIN{skip=0} \
	{if($$0 ~ /.*@START@.*/){skip=1};if(skip==0){print $$0};\
	 if($$0 ~ /.*@END@.*/){skip=0}}' >$@

blockBuffer.h: $(INCLUDEDIR)/blockBuffer.h
errorObj.h: $(INCLUDEDIR)/errorObj.h
fileMgr.h: $(INCLUDEDIR)/fileMgr.h
global.h: $(INCLUDEDIR)/global.h
syscat.h: $(INCLUDEDIR)/syscat.h
tableInfo.h: $(INCLUDEDIR)/tableInfo.h
loadTool.cpp: ../loadTool/loadTool.cpp
	@echo "Create $@ from $<";
	@cat $(INCLUDEDIR)/$< | awk 'BEGIN{skip=0} \
	{if($$0 ~ /.*@START@.*/){skip=1};if(skip==0){print $$0};\
	 if($$0 ~ /.*@END@.*/){skip=0}}' >$@
