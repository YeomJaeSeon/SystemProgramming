#include "JSTimer.h"
#include <unistd.h>

int main(void){
	time_t t;
	JSTimer_init(2);

	JSTimer_on(0);
	sleep(1);
	JSTimer_off(0);

	JSTimer_on(1);
	sleep(2);
	JSTimer_off(1);

	JSTimer_print();
	JSTimer_finalize();

	return 0;
}
