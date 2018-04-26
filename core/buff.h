#ifndef BUFF_H
#define BUFF_H

#include <string>

class Buff{
public:
	void writeInt(int&);
	int  readInt();

	void writeStr(std::string);
	std::string readStr();

/*	virtual void writeLar(Lar*);
	virtual Lar* readLar();*/
};

#endif