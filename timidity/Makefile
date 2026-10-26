PKGDATADIR = \"ms0:\\\\PSP_COMMON\\\\timidity\"
PKGLIBDIR = \".\"
DEFAULT_PATH = \"ms0:\\\\PSP_COMMON\\\\timidity\"

TARGET = timidity
OBJS = aiff_a.o aq.o au_a.o audio_cnv.o common.o controls.o effect.o filter.o freq.o instrum.o list_a.o loadtab.o m2m.o miditrace.o mix.o mod.o mod2midi.o modmid_a.o output.o playmidi.o raw_a.o rcp.o readmidi.o recache.o resample.o reverb.o sbkconv.o sffile.o sfitem.o smfconv.o sndfont.o tables.o timidity.o version.o wave_a.o wrd_read.o wrdt.o psp_a.o ../interface/libinterface.a ../libarc/libarc.a ../libunimod/libunimod.a ../utils/libutils.a

INCDIR = . .. ../libarc ../libunimod ../interface ../utils
CFLAGS = -DHAVE_CONFIG_H -G0 -O2 -Wall -DHAVE_UNION_SEMUN -DAU_PSP -DPKGDATADIR=$(PKGDATADIR) -DPKGLIBDIR=$(PKGLIBDIR) -DDEFAULT_PATH=$(DEFAULT_PATH) -DTIMIDITY_OUTPUT_ID=\"p\" -DTIMID_VERSION=\"2.11.2\"
CXXFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
ASFLAGS = $(CFLAGS)

LIBDIR = 
LDFLAGS = 
LIBS = ../interface/libinterface.a ../libarc/libarc.a ../libunimod/libunimod.a ../utils/libutils.a -lm  -lpspaudiolib -lpspaudio -lm -lpspdebug -lpspdisplay -lpspge -lpspctrl -lpspsdk -lpsppower -lc -lpspuser -lpspkernel

EXTRA_TARGETS = EBOOT.PBP
PSP_EBOOT_TITLE = TiMidity++-2.11.2 for PSP ver20

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak

