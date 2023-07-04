include common.mk

BUILD = build

.PHONY: default all clean
default:
	$(MAKE) all

HEX = template/template.hex \
soft_sleep/soft_sleep.hex \
timer/timer.hex

${HEX}:%.hex : %.c
	$(CC) $(CFLAGS) $^ -o $*.ihx
	$(PACKIHX) $*.ihx > $*.hex
	$(RM) $*.asm $*.ihx $*.lk $*.lst $*.map $*.mem $*.rel $*.rst $*.sym
all: ${HEX}

clean:
	$(RM) $(HEX)