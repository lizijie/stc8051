include common.mk

BUILD = build

.PHONY: default $(BINS)
default:
	$(MAKE) $(BINS)

BINS = template/template flow_led/flow_led
$(BINS):
	$(CC) $(CFLAGS) $@.c  -o $@.ihx
	$(PACKIHX) $@.ihx > $@.hex
	$(RM) $@.asm $@.ihx $@.lk $@.lst $@.map $@.mem $@.rel $@.rst $@.sym