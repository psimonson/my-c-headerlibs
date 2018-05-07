#include "../common/spcstr.h"

int main()
{
	dyn_init();
	dyn_string("Hello world!\n");
	dyn_string("This is another test!\n");
	dyn_string("Hello again world!\n");
	dyn_string("This is going to be a new beginning.\n");
	dyn_string("Here is another string.\n");
	dyn_string("And again another string.\n");
	dyn_string("Right now it can handle up to 15 strings.\n");
	dyn_string("The strings are fully dynamic.\n");
	dyn_string("Here is another bunch of strings.\n");
	dyn_string("You can probably guess what it is gonna be now.\n");
	dyn_string("Here is another string for my program.\n");
	dyn_string("This goes for as long as you have memory now.\n");
	dyn_string("There are no problems that I know of in this program.\n");
	dyn_display();
	dyn_free();
	return 0;
}
