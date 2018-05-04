#ifndef LOG_H
#define LOG_H

#include <stdio.h>
#include <stdarg.h>


#define N 1
#define W 2
#define E 3
#define MAX_LINE  1024

void logHandler(int, char*, ...);

#define LOG(fa, args...) logHandler(N, fa, ##args)
#define WARRING(fa, args...) logHandler(W, fa, ##args)
#define ERROR(fa, args...) logHandler(E, fa, ##args)



void logHandler(int level, const char* format, ...){
	char buffer[MAX_LINE];
	va_list args;
	va_start(args, format);
	vsnprintf (buffer,MAX_LINE,format, args);
	//perror (buffer);
	printf("%s\n", buffer);
	va_end (args);
}
#endif