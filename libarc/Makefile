PKGDATADIR = \"ms0:\\\\PSP_COMMON\\\\timidity\"
PKGLIBDIR = \".\"
DEFAULT_PATH = \"ms0:\\\\PSP_COMMON\\\\timidity\"

TARGET_LIB = libarc.a
OBJS = arc.o arc_lzh.o arc_mime.o arc_tar.o arc_zip.o deflate.o explode.o inflate.o unlzh.o url.o url_b64decode.o url_buff.o url_cache.o url_dir.o url_file.o url_hqxdecode.o url_inflate.o url_mem.o url_pipe.o url_qsdecode.o url_uudecode.o

INCDIR = . .. ../utils ../timidity
CFLAGS = -DHAVE_CONFIG_H -O2 -G0 -Wall -DHAVE_UNION_SEMUN -DAU_PSP -DPKGDATADIR=$(PKGDATADIR) -DPKGLIBDIR=$(PKGLIBDIR) -DDEFAULT_PATH=$(DEFAULT_PATH) -DTIMIDITY_OUTPUT_ID=\"p\"

PSPSDK=$(shell psp-config --pspsdk-path)
include $(PSPSDK)/lib/build.mak
