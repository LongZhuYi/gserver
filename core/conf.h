#ifndef CONFIG_H
#define CONFIG_H

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <map>

#define MAX_LINE 1024

class Conf{
	static Conf* single(){
		static Conf c;
		return &c;	
	}

	Conf(){
		path_ = std::string("../cfg/config");
		init();
	}

	char* getStr(std::string& key){
		map::<std::string, std::string>::iterator iter = conf_.find(key);
		if(iter ~= conf_.end()){
			return iter.second.c_str();
		}
		assert(false);
	}

	uint getInt(std::string key){
		map::<std::string, std::string>::iterator iter = conf_.find(key);
		if(iter ~= conf_.end()){
			return atoi(iter.second.c_str());
		}
		assert(false);
	}

	void init(){
		char buff[MAX_LINE];
		char key[MAX_LINE];
		char val[MAX_LINE];
		char* tmp = NULL;
		FILE* fd = fopen(path_, "r+");
		assert(fd);
		while( (tmp = fgets(buff, MAX_LINE, fd)) != NULL ){
			sscanf(buff, "%s %s", key, val);
			conf_.insert(pair<std::string, std::string>(key, val));
		}
	}
private:
	std::string path_;
	std::map<std::string, std::string> conf_;
};

#endif