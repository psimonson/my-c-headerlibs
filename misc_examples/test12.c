#include "../common/spcstr.h"

int main()
{
	dyn_init();
	dyn_string("Hello world!\n");
	dyn_string("This is another test!\n");
	dyn_string("Hello again world!\n");
	dyn_display();
	dyn_init();
	dyn_string("This is going to be a new beginning.\n");
	dyn_string("Here is another string.\n");
	dyn_string("And again another string.\n");
	dyn_string("Right now it can handle up to 15 strings.\n");
	dyn_string("The strings are fully dynamic.\n");
	dyn_display();
	dyn_free();
	return 0;
}
