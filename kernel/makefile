GCC := arm-eabi-gcc
AS := arm-eabi-as
LD := arm-eabi-ld

SYS_MEM :=  128 


CFLAGS := -ffreestanding -nostdlib -Wall -Wextra  -I  inc -I ~/opt/cross/newlib/arm-eabi/include/

DEFINES :=  -D SYS_MEM=$(SYS_MEM)

ASRC := $(wildcard src/*.S) 
CSRC := $(wildcard src/*.c)
SRC := $(ASRC:%.S=%.ao) $(CSRC:%.c=%.o) 
OBJ := $(subst src, obj, $(SRC))  


obj/%.ao : src/%.S
	@echo "Assembeling " $<
	$(AS) $< -o $@ -g

obj/%.o: src/%.c
	@echo "compiling " $<
	$(GCC) $(CFLAGS) $(DEFINES) -c $< -o $@ -g 

all : $(OBJ)
	$(LD) -T linker.ld $(OBJ) -o ../bin/kernel.bin -L ~/opt/cross/lib/gcc/arm-eabi/10.0.1/ -L ~/opt/cross/arm-eabi/lib/ -lc -lgcc
	
clean:
	rm obj/*.ao
	rm obj/*.o
		
