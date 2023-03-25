.globl start 

MULTIBOOT_HEADER_MAGIC=0x1BADB002
MULTIBOOT_HEADER_FLAGS=0
MULTIBOOT_HEADER_CHECKSUM=0xE4524FFE
.section multiboot_header
.align 4
.long MULTIBOOT_HEADER_MAGIC
.long MULTIBOOT_HEADER_FLAGS
.long MULTIBOOT_HEADER_CHECKSUM
.text #进入代码段
.code32 #32位代码
start:
# vga输出
movl $0x2f652f48, 0xB8000
movl $0x2f6c2f6c, 0xB8004
movl $0x2f6f, 0xB8008
movl $0xce6fce77, 0xB8012
movl $0xce6cce72, 0xB8016
movl $0xce64, 0xB801A #hello world

movl $0x3c423c50, 0xB80A0
movl $0xfc30fc32, 0xB80A4
movl $0xfc33fc30, 0xB80A8
movl $0xfc37fc30, 0xB80AC
movl $0xfc36fc33, 0xB80B0
#学号输出

# 串口输出
movb $0x50,%al
movw $0x3F8, %dx
outb %al, %dx
movb $0x4F,%al
movw $0x3F8, %dx
outb %al, %dx
movb $0x57,%al
movw $0x3F8, %dx
outb %al, %dx
movb $0x45,%al
movw $0x3F8, %dx
outb %al, %dx
movb $0x52,%al
movw $0x3F8, %dx
outb %al, %dx
movb $0x65,%al
movw $0x3F8, %dx
outb %al, %dx
movb $0x64,%al
movw $0x3F8, %dx
outb %al, %dx
# POWERed
movb $0x40,%al
movw $0x3F8, %dx
outb %al, %dx 
#0x40 @

movb $0x62,%al
movw $0x3F8, %dx
outb %al, %dx
movb $0x79,%al
movw $0x3F8, %dx
outb %al, %dx
movb $0x40,%al
movw $0x3F8, %dx
outb %al, %dx
#0x40@
movb $0x48, %al 
movw $0x3F8, %dx
outb %al, %dx
movb $0x61, %al
movw $0x3F8, %dx
outb %al, %dx 
movb $0x72, %al
movw $0x3F8, %dx
outb %al, %dx
movb $0x72, %al
movw $0x3F8, %dx
outb %al, %dx
movb $0x79, %al
movw $0x3F8, %dx
outb %al, %dx
#harry
nop
nop
hlt
