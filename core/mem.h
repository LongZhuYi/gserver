/*
	mem manager module
 */

#ifndef MEM_H
#define MEM_H

class Mem{
public:
	virtual Mem* single();
	virtual void* Alloc(size_t sz);
};

#endif