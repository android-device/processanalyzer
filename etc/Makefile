#
# Makefile for "sgc"
#

CC = /opt/intel-fca-socp-distro/2015.12/sysroots/i686-melsdk-linux/usr/bin/x86_64-mel-linux/x86_64-mel-linux-gcc
CFLAGS +=  --sysroot=/opt/intel-fca-socp-distro/2015.12/sysroots/corei7-64-mel-linux

LDFLAGS +=  --target=elf64-x86-64 --sysroot=/opt/intel-fca-socp-distro/2015.12/sysroots/corei7-64-mel-linux -lpthread

OBJDIR=../obj
SRCDIR=../src
RELDIR=../rel
INCDIR=../inc
ETCDIR=../etc

C_INCS += -I../inc/
ARFLAGS  = -r -s --target=elf64-x86-64 

PROG     = $(RELDIR)/can-poll

SRCS     = $(wildcard $(SRCDIR)/*.cpp)
TMP_OBJS = $(subst .cpp,.o,$(filter %.cpp, $(SRCS)))
LIB_OBJS = $(addprefix $(OBJDIR), $(subst $(SRCDIR), , $(TMP_OBJS)))

#  VPATH: Source file search path. Format <dir>:<dir>:<dir>
VPATH    = $(SRCDIR)

all: time_stamp $(PROG)
	@echo "can-poll: Build complete ..."

time_stamp:
	@touch ../src/main.cpp

# Use target below for debugging makefile issues.
info:
	@echo  SRCS      $(SRCS)
	@echo  TMP_OBJS  $(TMP_OBJS)
	@echo  LIB_OBJS  $(LIB_OBJS)
	@echo  G3G_ROOT  $(G3G_ROOT)
	@echo  G3G_LIB   $(G3G_LIB)
	@echo  G3G_GEN   $(G3G_GEN)

incs:
	@echo  INCS      $(C_INCS)

$(OBJDIR)/%.o : %.cpp
	@echo Compiling $<
	@$(CC) $(CFLAGS) $(CDEFS) $(C_INCS) -o $@ -c $<

$(PROG): $(LIB_OBJS)
	@echo "can-poll: Building .."
	@$(CC) -o $@ $^ $(LDFLAGS) -lstdc++

clean:
	@echo "can-poll: Cleanup obj & rel dir ..."
	@rm -f $(OBJDIR)/*
	@rm -f $(RELDIR)/*

