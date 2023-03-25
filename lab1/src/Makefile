ASM_FLAGS= -m32 --pipe -Wall -fasm -g -O1 -fno-stack-protector #定义宏

multibootHeader.bin: multibootHeader.S
	gcc -c ${ASM_FLAGS} multibootHeader.S -o multibootHeader.o #对汇编文件编译生成可重定位文件
	ld -n -T multibootHeader.ld multibootHeader.o -o multibootHeader.bin #对文件进行重定位 链接生成 bin

clean:
	rm -rf ./multibootHeader.bin ./multibootHeader.o #删除文件
