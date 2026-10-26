PKGDATADIR = \"ms0:\\\\PSP_COMMON\\\\timidity\"
PKGLIBDIR = \".\"
DEFAULT_PATH = \"ms0:\\\\PSP_COMMON\\\\timidity\"

TARGET_LIB = libutils.a
OBJS = bitset.o fft4g.o mblock.o memb.o nkflib.o strtab.o support.o timer.o

INCDIR = . .. ../libarc ../timidity
CFLAGS = -DHAVE_CONFIG_H -O2 -G0 -Wall -DHAVE_UNION_SEMUN -DAU_PSP -DPKGDATADIR=$(PKGDATADIR) -DPKGLIBDIR=$(PKGLIBDIR) -DDEFAULT_PATH=$(DEFAULT_PATH) -DTIMIDITY_OUTPUT_ID=\"p\"

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
