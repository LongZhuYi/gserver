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
	static Conf* single(){
		static Conf c;
		return &c;
	}
	Conf(){
		const char* path = string("../cfg/conf").c_str();
		loadConf(path);
	}
	const char* getStr(string key){
		map<string, string>::iterator iter = conf_.find(key);
		if(iter != conf_.end()){
			return iter->second.c_str();
		}
		return NULL;
	}

	int getInt(string key){
		map<string, string>::iterator iter = conf_.find(key);
		if(iter != conf_.end()){
			return atoi(iter->second.c_str());
		}
		return 0;
	}

	void loadConf(const char* path){
		char buff[MAX_LINE];
		char key[MAX_LINE];
		char val[MAX_LINE];
		char* tmp = NULL;
		FILE* fd = fopen(path, "r+");
		assert(fd);
		while( (tmp = fgets(buff, MAX_LINE, fd)) != NULL ){
			sscanf(buff, "%s %s", key, val);
			conf_.insert(pair<string, string>(key, val));
		}
		fclose(fd);
	}

	std::string getIp(const char* key){
		char ip[1024];
		char port[8];
		const char* gaddr = getStr(key);
		char* tmp = ip;
		int j=0;
		int len = strlen(gaddr);
		for(int i=0;i<len;i++){
			if(gaddr[i] == ':'){
				tmp[j] = '\0';
				tmp = port;
				j = 0;
			}else
				tmp[j++] = gaddr[i];
		}
		return std::string(ip);
	}

	std::string getPort(const char* key){
		char ip[1024];
		char port[8];
		const char* gaddr = getStr(key);
		char* tmp = ip;
		int j=0;
		int len = strlen(gaddr);
		for(int i=0;i<len;i++){
			if(gaddr[i] == ':'){
				tmp[j] = '\0';
				tmp = port;
				j = 0;
			}else
				tmp[j++] = gaddr[i];
		}
		return std::string(port);
	}
private:
	map<string, string> conf_;
};

#endif