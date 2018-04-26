#ifndef CONFIG_H
#define CONFIG_H

#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string>
#include <map>

using namespace std;

#define MAX_LINE 1024

class Conf{
public:
/*	static Conf* single(){
		static Conf c;
		return &c;
	}
	Conf(){
		path_ = string("../cfg/config");
		init();
	}*/
	static char* getStr(string key){
		//map<string, string>::iterator iter = conf_.find(key);
		//if(iter != conf_.end()){
			//return iter.c_str();
		//}
		return NULL;
	}

	static int getInt(string key){
		//map<string, string>::iterator iter = conf_.find(key);
		//if(iter != conf_.end()){
			//return atoi(iter.second.c_str());
		//}
		//assert(false);
		return 0;
	}

	void init(){
		char buff[MAX_LINE];
		char key[MAX_LINE];
		char val[MAX_LINE];
		char* tmp = NULL;
		FILE* fd = fopen(path_.c_str(), "r+");
		assert(fd);
		while( (tmp = fgets(buff, MAX_LINE, fd)) != NULL ){
			sscanf(buff, "%s %s", key, val);
			conf_.insert(pair<string, string>(key, val));
		}
	}
private:
	string path_;
	map<string, string> conf_;
};

#endif