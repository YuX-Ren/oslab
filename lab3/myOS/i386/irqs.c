void put_char2pos(unsigned char c, int color, unsigned int pos);
void ignoreIntBody(void){
    char a[20]="Unknown interrupt";
    char *str=a;
    int pos=1920;
    while(*str!='\0'){
        put_char2pos(*str,0x07,pos);
        pos++;
        str++;
        }
}
