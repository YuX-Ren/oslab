STACK_SIZE = 0x4000	# 栈的大小，可自行修改

/* ===== code32 ========================== */

.globl _start                   # GNU default entry point
.text
.code32
_start:
    jmp establish_stack

dead:	jmp dead                # Never here

# Set up the stack
establish_stack:

    movl    $0x18000, %eax     # 填入栈底地址
	
    movl    %eax, %esp          # set stack pointer
    movl    %eax, %ebp          # set base pointer

# Zero out the BSS segment
zero_bss:
    cld                         # make direction flag count up
    movl    $_end, %ecx         # find end of .bss
    movl    $_bss_start, %edi   # edi = beginning of .bss
    subl    %edi, %ecx          # ecx = size of .bss in bytes
    shrl    %ecx                # size of .bss in longs
    shrl    %ecx
	
    xorl    %eax, %eax          # value to clear out memory
    repne                       # while ecx != 0
    stosl                       # clear a long in the bss


# Transfer control to main
to_main:	
    call osStart

shut_down:	
    jmp shut_down	# Never here	

/* ===== data =========================== */
