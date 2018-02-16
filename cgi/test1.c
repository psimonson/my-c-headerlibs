#include "../common/cgi_helper.h"

int main(int argc, char **argv, char **envp)
{
	setup_args1("Simple CGI Web page", "000000", "00FF00",
		"Written by Philip Simonson", header_default, body_default,
		footer_default);
	return 0;
}

