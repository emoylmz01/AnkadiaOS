CC=i686-elf-gcc
AS=nasm
CFLAGS=-std=gnu99 -ffreestanding -O2 -Wall -Wextra

SRCS=$(wildcard kernel/*.c drivers/*.c gui/*.c)
OBJS=$(SRCS:.c=.o)

all: ankadiaos.bin

boot/boot.o: boot/boot.asm
	$(AS) -f elf32 boot/boot.asm -o boot/boot.o

kernel/%.o: kernel/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

drivers/%.o: drivers/%.c
	$(CC) -c $< -o $@ $(CFLAGS)

ankadiaos.bin: boot/boot.o $(OBJS)
	$(CC) -T linker.ld -o ankadiaos.bin -ffreestanding -O2 -nostdlib boot/boot.o $(OBJS) -lgcc

run: ankadiaos.bin
	qemu-system-i386 -kernel ankadiaos.bin

iso: ankadiaos.bin
	mkdir -p isodir/boot/grub
	cp ankadiaos.bin isodir/boot/ankadiaos.bin
	cp grub.cfg isodir/boot/grub/grub.cfg
	grub-mkrescue -o ankadiaos.iso isodir

clean:
	rm -f boot/*.o kernel/*.o drivers/*.o gui/*.o *.bin *.iso
