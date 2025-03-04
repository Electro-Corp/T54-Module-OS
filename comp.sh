rm -d -r -f out
mkdir out

nasm -f elf src/kernel/boot.asm -o out/boot.o


echo Comp Kernel C Source
gcc -O0 -c src/kernel/kernel.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/kernel.o

gcc -O0 -c src/kernel/cd.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/cd.o
gcc -O0 -c src/kernel/fs.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/fs.o

gcc -O0 -c src/kernel/module.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/module.o

gcc -O0 -c src/kernel/stdlib.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/stdlib.o

gcc -O0 -c src/kernel/vga.c -m32 -fno-builtin -fno-stack-protector -nostartfiles -W -ffreestanding -o out/vga.o



echo Link OS
ld -T link.ld -melf_i386 out/boot.o out/kernel.o out/fs.o out/cd.o out/module.o out/stdlib.o out/vga.o -o iso/boot/kernel


echo Comp Kernel Modules

rm iso/modules/modules/base -r -f -d

# mkdir iso/modules/modules/base

#gcc -m32 -O0 -c src/modules/VGA/M_Vga.c -o iso/kmods/base/Vga.o
#objcopy -O binary iso/kmods/base/Vga.o iso/kmods/base/Vga.kmod
#gcc -m32 -ffreestanding -nostdlib -fno-pic -O0 -c src/modules/VGA/M_Vga.c -o iso/kmods/base/Vga.o
#ld -Ttext 0x0 --oformat binary iso/kmods/base/Vga.o -o iso/kmods/base/Vga.kmod
gcc -ffreestanding -nostdlib -m32 -fno-pic -c src/modules/VGA/M_Vga.c -o iso/kmods/base/Vga.o
ld -m elf_i386 -Ttext 0x0 --oformat  binary iso/kmods/base/Vga.o -T src/modules/module.ld -o iso/kmods/base/Vga.kmod
objdump -t iso/kmods/base/Vga.o > out/Vga.symbols
rm iso/kmods/base/Vga.o

python3 symbolConv.py out/Vga.symbols iso/kmods/base/VGA.SYM


#gcc -m32 -O0 -csrc/modules/MemoryManager/M_MemoryManager.c -fPIC -o iso/modules/base/MemMan.kmod
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