rm -d -r -f out
mkdir out

nasm -f elf src/kernel/boot.asm -o out/boot.o


echo Comp Kernel C Source
gcc -c  src/kernel/kernel.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/kernel.o

gcc -c  src/kernel/cd.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/cd.o
gcc -c  src/kernel/fs.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/fs.o

gcc -c  src/kernel/module.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/module.o

gcc -c  src/kernel/stdlib.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/stdlib.o


echo Link OS
ld -T link.ld -melf_i386 out/boot.o out/kernel.o out/fs.o out/cd.o out/module.o out/stdlib.o -o iso/boot/kernel


echo Comp Kernel Modules
gcc -m32 -c src/modules/VGA/M_Vga.c -o iso/modules/base/Vga.o
objcopy -O binary iso/modules/base/Vga.o iso/modules/base/Vga.kmod
objdump -t iso/modules/base/Vga.o > iso/modules/base/Vga.symbols
python3 symbolConv.py iso/modules/base/Vga.symbols iso/modules/base/VGA.SYM


#gcc -m32 -c src/modules/MemoryManager/M_MemoryManager.c -fPIC -o iso/modules/base/MemMan.kmod
#objdump -t iso/modules/base/MemMan.kmod > iso/modules/base/MemMan.symbols


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

qemu-system-x86_64 -drive file=t54.iso,if=ide,media=cdrom -hdd test.img 