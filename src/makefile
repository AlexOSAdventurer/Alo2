.PHONY: all micro initrd clean micro_clean initrd_clean

all: micro

clean: micro_clean

micro: 
	make -C micro all
	
micro_clean:
	make -C micro clean

initrd:
	make -C initrd all

initrd_clean:
	make -C initrd_clean clean