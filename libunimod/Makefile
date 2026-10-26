PKGDATADIR = \"ms0:\\\\PSP_COMMON\\\\timidity\"
PKGLIBDIR = \".\"
DEFAULT_PATH = \"ms0:\\\\PSP_COMMON\\\\timidity\"

TARGET_LIB = libunimod.a
OBJS = load_669.o load_amf.o load_dsm.o load_far.o load_gdm.o load_imf.o load_it.o load_m15.o load_med.o load_mod.o load_mtm.o load_okt.o load_s3m.o load_stm.o load_stx.o load_ult.o load_uni.o load_xm.o mloader.o mlutil.o mmsup.o munitrk.o
INCDIR = . .. ../timidity ../libarc ../utils
CFLAGS = -DHAVE_CONFIG_H -O2 -G0 -Wall -DHAVE_UNION_SEMUN -DAU_PSP -DPKGDATADIR=$(PKGDATADIR) -DPKGLIBDIR=$(PKGLIBDIR) -DDEFAULT_PATH=$(DEFAULT_PATH) -DTIMIDITY_OUTPUT_ID=\"p\"

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
