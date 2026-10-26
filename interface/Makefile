PKGDATADIR = \"ms0:\\\\PSP_COMMON\\\\timidity\"
PKGLIBDIR = \".\"
DEFAULT_PATH = \"ms0:\\\\PSP_COMMON\\\\timidity\"

TARGET_LIB = libinterface.a
OBJS = psp_c.o dumb_c.o wrdt_dumb.o wrdt_tty.o

INCDIR = . .. ../timidity ../libarc ../utils
CFLAGS = -DHAVE_CONFIG_H -O2 -G0 -Wall -DHAVE_UNION_SEMUN -DAU_PSP -DPKGDATADIR=$(PKGDATADIR) -DPKGLIBDIR=$(PKGLIBDIR) -DDEFAULT_PATH=$(DEFAULT_PATH) -DTIMIDITY_OUTPUT_ID=\"p\"

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
