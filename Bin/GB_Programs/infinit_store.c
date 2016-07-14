


typedef volatile unsigned char* Addr;
#define ADDR(x) ((Addr)x)

void main(void) {

//	Addr ptr = ADDR(0x6677);
//	Addr ptr = ADDR(0x1111);
//	Addr ptr = ADDR(0x2222);
	Addr ptr = ADDR(0x3031);
//	Addr ptr = ADDR(0x4444);

store:

	*ptr = 0x66;

goto store;

}
