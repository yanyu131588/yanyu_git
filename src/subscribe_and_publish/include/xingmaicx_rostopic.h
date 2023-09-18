#ifndef _XINGMAICX_ROSTOPIC_H
#define _XINGMAICX_ROSTOPIC_H

//log
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "sys/time.h"
#include <stdarg.h>
using namespace std;

#if 0
    //topic 
#define printf_topic_log(path_time,file_path_txt,format,...) \
    do { \
    clock_t time_temp;\
    FILE* file; \
    string file_name = path_time+"/"+file_path_txt+".txt";\
    if((file=fopen(file_name.c_str(),"a"))!=NULL) \
    { \
    	struct tm *pTm; \
        time_t t;\
        time(&t);\
	pTm=localtime(&t);\
	fprintf(file,"[time:%d-%02d-%02d %02d:%02d:%02d]",1900+pTm->tm_year, 1+pTm->tm_mon,pTm->tm_mday,pTm->tm_hour, pTm->tm_min, pTm->tm_sec);\
	fprintf(file,format,##__VA_ARGS__);\
	fprintf(file,"%s","\n");\
	fclose(file);\
    }\
    }while (0)
#endif 

class xingmaicx_rostopic_log
{
public:
    xingmaicx_rostopic_log(string log_pwd_path);
    //~xingmaicx_rostopic_log();

    string path_time;//pwd path

    /*
    @brief: write time log to txt
    */
    void printf_topic_log(string file_path_txt,const char* format,...);

    /*
    @brief: write time log to txt
    */
    void ros2_printf_topic_log(string pwd_path,const char* file_path_txt,const char* format,...);


    /*
    @brief: time calculate 
    @params[in]: 
    @params[out]:
    @return time
    */
    double xingmaicx_time_us();

};


#endif