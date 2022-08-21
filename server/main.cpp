#include <iostream>
#include <signal.h>

int main(int argc, char const *argv[])
{	
	signal(SIGHUP, SIG_IGN);
	return 0;
}
