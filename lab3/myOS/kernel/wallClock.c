#include "wallClock.h"
void put_char2pos(unsigned char c, int color, unsigned int pos);
void (*wallClock_hook)(int, int, int) = 0;
//hook
void oneTickUpdateWallClock(int HH, int MM, int SS){
	if(wallClock_hook) wallClock_hook(HH,MM,SS);
}

void setWallClockHook(void (*func)(int, int, int)) {
	wallClock_hook = func;
}

void setWallClock(int HH,int MM,int SS){
	unsigned char time[8];
	int pos=1960;
	time[0]=(char)(HH/10+48);
	time[1]=(char)(HH%10+48);
	time[2]=':';
	time[3]=(char)(MM/10+48);
	time[4]=(char)(MM%10+48);
	time[5]=':';
	time[6]=(char)(SS/10+48);
	time[7]=(char)(SS%10+48);
	for(int i=0;i<8;i++,pos++)
	{put_char2pos(time[i],0x04,pos);
	}
	return;
}
//将getwallclock 写入setwallclock
