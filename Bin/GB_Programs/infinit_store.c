

void main(void) {
	volatile unsigned char* ptr = (unsigned char*)0x6677;
store:
		*ptr = 0x66;
goto store;

}
