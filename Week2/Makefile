COMPILER=G++

# todo: object files into output path, processing c / c++ files in the same time (?), nested directories for source files (?)
C = cpp
OUTPUT_PATH = out/
SOURCE_PATH = src/
EXE = $(OUTPUT_PATH)Week2

ifeq ($(COMPILER), G++)
  ifeq ($(OS),Windows_NT)
    OBJ = obj
  else
    OBJ = o
  endif
  COPT = -O2 -std=c++11 -stdlib=libc++
#  CCMD = g++
  CCMD = clang++
  OBJFLAG = -o
  EXEFLAG = -o
  INCLUDES = -I/opt/local/include/
#  INCLUDES =
# LIBS = -lgc
  LIBS = -std=c++11 -stdlib=libc++ -lboost_unit_test_framework-mt
  LIBPATH = -L/opt/local/lib/
#  LIBPATH =
  CPPFLAGS = $(COPT) -g $(INCLUDES)
  LDFLAGS = -v $(LIBPATH) -g $(LIBS)
  DEP = dep
else
  OBJ = obj
  COPT = /O2
  CCMD = cl
  OBJFLAG = /Fo
  EXEFLAG = /Fe
# INCLUDES = /I..\\.includes
  INCLUDES =
# LIBS = ..\\.libs\\libgc.lib
  LIBS =
  CPPFLAGS = $(COPT) /DEBUG $(INCLUDES)
  LDFLAGS = /DEBUG
endif

OBJS := $(patsubst %.$(C),%.$(OBJ),$(wildcard $(SOURCE_PATH)*.$(C)))

%.$(OBJ):%.$(C)
	@echo Compiling $(basename $<)...
	$(CCMD) -c $(CPPFLAGS) $(CXXFLAGS) $< $(OBJFLAG)$@

all: $(OBJS)
	@echo Linking...
	$(CCMD) $(LDFLAGS) $^ $(LIBS) $(EXEFLAG) $(EXE)

clean:
	rm -rf $(SOURCE_PATH)*.$(OBJ) $(EXE)

rebuild: clean all
#rebuild is not entirely correct