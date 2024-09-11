rm -d -r -f out
mkdir out

nasm -f elf src/kernel/boot.asm -o out/boot.o


echo Comp Kernel C Source
gcc -c  src/kernel/kernel.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/kernel.o

echo Link OS
ld -T link.ld -melf_i386 out/boot.o out/kernel.o -o iso/boot/kernel


echo Comp Kernel Modules


mkisofs -R                              \
-b  boot/grub/stage2_eltorito    \
-no-emul-boot                   \
-boot-load-size 4               \
-A os                           \
-input-charset utf8             \
-quiet                          \
-boot-info-table                \
-o t54.iso                       \
-V "T54 Root FS"                \
iso

qemu-system-x86_64 -drive file=t54.iso,if=ide,media=cdrom