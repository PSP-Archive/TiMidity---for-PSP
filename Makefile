PKGDATADIR = \"ms0:\\\\PSP_COMMON\\\\timidity\"
PKGLIBDIR = \".\"
DEFAULT_PATH = \"ms0:\\\\PSP_COMMON\\\\timidity\"

all	: EBOOT.PBP

EBOOT.PBP	: libinterface.a libarc.a libunimod.a libutils.a
	gmake -C timidity
	
libinterface.a	:
	gmake -C interface 
libarc.a	:
	gmake -C libarc 
libunimod.a	:
	gmake -C libunimod 
libutils.a	:
	gmake -C utils 

clean	:
	gmake -C timidity clean
	gmake -C interface clean
	gmake -C libarc clean
	gmake -C libunimod clean
	gmake -C utils clean



