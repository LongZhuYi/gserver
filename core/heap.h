#ifndef HEAP_H
#define HEAP_H

#include "stdlib.h"

#define  HEAP_MAX_CNT 1024

template<typename T>
class Heap{
public:
	Heap();
	T*   top();
	T*    pop();
	bool push(T*);
	void upper(int pos);
	void lower(int pos);
	int   size(){ return pos_; }
private:
	int pos_;
	T* arr_[HEAP_MAX_CNT];
};

template<typename T>
Heap<T>::Heap():pos_(0){
}

template<typename T>
void Heap<T>::upper(int pos){
	int parent=0, pkey = 0;
	T* tmp     = NULL;
	while(pos>1){
		parent = int(pos/2);
		pkey = arr_[parent]->key;
		if(pkey > arr_[pos]->key){
			tmp = arr_[pos];
			arr_[pos] = arr_[parent];
			arr_[parent] = tmp;
			pos = parent;
		}else{
			break;
		}
	}
}

template<typename T>
void Heap<T>::lower(int pos){
	int l, r, m=pos;
	while(m<pos_){
		l = m*2;
		r = m*2+1;
		if(l<=pos_ && arr_[l]->key < arr_[m]->key){
			m = l;
		}
		if(r<=pos_ && arr_[r]->key < arr_[m]->key){
			m = r;
		}
		if(m != l && m!=r)
			break;
	}
}

template<typename T>
bool Heap<T>::push(T* t){
	if(pos_ == HEAP_MAX_CNT-1) return false;
	int key = t->key;
	arr_[++pos_] = t;
	upper(pos_);
	return true;
}

template<typename T>
T* Heap<T>::pop(){
	if(pos_ < 1) return NULL;
	T* tmp = arr_[1];
	arr_[1]  = arr_[pos_];
	arr_[pos_] = tmp;
	lower(1);
	return tmp;
}

template<typename T>
T* Heap<T>::top(){
	if(pos_ == 0) return NULL;
	return arr_[1];
}
#endif