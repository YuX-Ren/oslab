#include "tick.h"
int ticks=0;
int HH,MM,SS;
extern void oneTickUpdateWallClock(int HH, int MM, int SS);

void tick(void){
	ticks++;
	if (ticks %100 ==0)
	{	ticks=0;
		SS++;
		if(SS%60==0){
			SS=0;
			MM++;
			if(MM%60==0)
			{
			MM=0;
			HH++;
			}
		}
	}
	oneTickUpdateWallClock(HH, MM, SS);

	return;
}

