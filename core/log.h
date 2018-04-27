#ifndef LOG_H
#define LOG_H

#define N 1
#define W 2
#define E 3

/*void logHandler(int, char*, ...)

#define LOG(fa, ...) logHandler(N, fa, ...)
#define WARRING(fa, ...) logHandler(W, fa, ...)
#define ERROR(fa, ...) logHandler(E, fa, ...)

#define MAX_LINE  1024
static char* buff = (char*) malloc(MAX_LINE);

void logHandler(int level, char* fa, ...){
	va_list ap;
	va_start(ap, fmt);
	//int n=vsnprintf(buffer+1,LogMax,fmt,ap);
	snprintf(buff, MAX_LINE, fa, ap);
	va_end(ap);
	printf("%s\n",buff);
}*/

#endif