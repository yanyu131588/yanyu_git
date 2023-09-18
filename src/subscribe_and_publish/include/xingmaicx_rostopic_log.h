#ifndef XINGMAICX_ROSTOPIC_LOG_H
#define XINGMAICX_ROSTOPIC_LOG_H

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

 /*
@brief: write time log to txt
*/
extern void ros2_printf_topic_log(string pwd_path,const char* file_path_txt,const char* format,...);


/*
@brief: time calculate 
@params[in]: 
@params[out]:
@return time
*/
extern double xingmaicx_time_us();

#endif 