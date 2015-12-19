INCLUDEDIR = ../include
LIBDIR   = ../lib
TARGETS = student_header
STUDENT_HEADER_FILES = fileMgr.h global.h syscat.h tableInfo.h blockBuffer.h errorObj.h loadTool.cpp bufferMgr.h page.h bufferControlBlock.h bufferAccessControlBlock.h execEngine.h indexMgr.h tuple.h btree.h
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
page.h: $(INCLUDEDIR)/page.h
bufferMgr.h: $(INCLUDEDIR)/bufferMgr.h
bufferControlBlock.h: $(INCLUDEDIR)/bufferControlBlock.h
bufferAccessControlBlock.h: $(INCLUDEDIR)/bufferAccessControlBlock.h
indexMgr.h: $(INCLUDEDIR)/indexMgr.h
execEngine.h: $(INCLUDEDIR)/execEngine.h
btree.h: $(INCLUDEDIR)/btree.h
tuple.h: $(INCLUDEDIR)/tuple.h
