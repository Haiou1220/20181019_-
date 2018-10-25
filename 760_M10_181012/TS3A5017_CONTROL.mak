CC = iccavr
LIB = ilibw
CFLAGS =  -e -D__ICC_VERSION=722 -DATtiny24  -l -g -MEnhanced 
ASFLAGS = $(CFLAGS) 
LFLAGS =  -g -e:0x0800 -bfunc_lit:0x22.0x800 -dram_end:0xdf -bdata:0x60.0xdf -dhwstk_size:30 -beeprom:0.128 -fihx_coff -S2
FILES = TS3A5017_control.o 

TS3A5017_CONTROL:	$(FILES)
	$(CC) -o TS3A5017_CONTROL $(LFLAGS) @TS3A5017_CONTROL.lk   -lstudio
TS3A5017_control.o: C:\iccv7avr\include\iot24v.h C:\iccv7avr\include\_iotX4v.h C:\iccv7avr\include\macros.h C:\iccv7avr\include\AVRdef.h
TS3A5017_control.o:	TS3A5017_control.c
	$(CC) -c $(CFLAGS) TS3A5017_control.c
