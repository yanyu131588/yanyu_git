#include "xingmaicx_rostopic.h"


/*
    @brief: write time log to txt
*/
void ros2_printf_topic_log(string pwd_path,const char* file_path_txt,const char* format,...)
{
    va_list arg_ptr;
    
    //size = vsnprintf(NULL, 0, format, arg_ptr);
    //string file_path = string(file_path_txt);
    do { 
    clock_t time_temp;
    FILE* file; 
    string file_name = pwd_path+"/"+string(file_path_txt)+".txt";
    if((file=fopen(file_name.c_str(),"a"))!=NULL) 
    { 
    	struct tm *pTm; 
        time_t t;
        time(&t);
	pTm=localtime(&t);
	fprintf(file,"[time:%d-%02d-%02d %02d:%02d:%02d]",1900+pTm->tm_year, 1+pTm->tm_mon,pTm->tm_mday,pTm->tm_hour, pTm->tm_min, pTm->tm_sec);
	va_start(arg_ptr, format);
    vfprintf(file,format,arg_ptr);
    va_end(arg_ptr);
	fprintf(file,"%s","\n");
	fclose(file);
    }
    }while (0);

}


/*
@brief: time calculate 
@params[in]: 
@params[out]:
@return time
*/
double xingmaicx_time_us()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    //printf("tvsec usec = %ld\n",tv.tv_sec*1000000+tv.tv_usec);//ms

    double t1 = tv.tv_sec*1000000+tv.tv_usec;
    double t2 = t1/1000000;
    //printf("t2 = %f\n",t2);
    return t2;
}
