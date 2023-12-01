src_s := $(shell find . -name *.s)
src_asm := $(patsubst %.s,%.asm,$(src_s))


%.s : %.asm
	mv %.asm %.s

%.asm : %.s
	mv %.s %.asm

change_asm : $(src_s)
	ls
	
change_s : $(src_asm)
	ls

debug:
	@ echo $(src_s)
	@ echo $(src_asm)

.PHONY : 