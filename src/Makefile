CC=i686-elf-gcc
AS=i686-elf-as
OBJ=boot.o kernel.o
CKFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra
CMFLAGS=-ffreestanding -O2 -nostdlib -lgcc

all: myos.bin

myos.bin: $(OBJ)
	$(CC) -T linker.ld -o myos.bin $(CMFLAGS) $(OBJ)

boot.o: boot.s
	$(AS) boot.s -o boot.o

kernel.o: kernel.c
	$(CC) -c kernel.c -o kernel.o $(CKFLAGS)

clean:
	rm *o myos.bin
