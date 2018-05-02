#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "hall.h"

int main(int argc, char** argv)
{	assert(argc>3);
	const char* sName = argv[1];
	int sid = atoi(argv[2]);
	int port = atoi(argv[3]);
	Hall* hall = Hall::single();
	hall->init(sName, sid, port);
	hall->start();
	return 0;
}