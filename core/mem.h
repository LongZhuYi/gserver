/*
	mem manager module
 */

#ifndef MEM_H
#define MEM_H

#include <string.h>

class Mem{
public:
	static Mem* single(){
		return &m_;
	}
	static void* Alloc(size_t sz){
		void* ptr = malloc(sz);
		return ptr;
	}
private:
	static Mem m_;
};

#endif