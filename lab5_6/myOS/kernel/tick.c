extern void oneTickUpdateWallClock(void);       //TODO: to be generalized

//#ifndef __TICK_HOOK__
//#define __TICK_HOOK__
void (*tick_hook)() = 0; //{};
//#endif
// void (*scheduler_tick)(void)=0;
int tick_hook_arr();
int tick_number = 0;
void tick(void){
	int temp_col, temp_row;	
	tick_number++;
	//myPrintk(0x4,"tick::%d\n",tick_number);
	
	oneTickUpdateWallClock();

	// call hooks 
	// if(*scheduler_tick) scheduler_tick();  // RR
	tick_hook_arr();  // arriving	

	// if(watchdogTimer_func) watchdogTimer_func(); 
	if(tick_hook) tick_hook();  //user defined   
}
