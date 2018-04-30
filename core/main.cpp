#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hall.h"

int main(int argc, char** argv)
{	
	if(argc <3){
		assert(false);
		return -1;
	}
	const char* sName = argv[1];
	int sid = atoi(argv[2]);
	int port = atoi(argv[3]);
	printf("%s %d %d", sName, sid, port);
	Hall hall;
	hall.init(sName, sid, port);
	printf("%s\n", "init");
	hall.start();
	return 0;
}