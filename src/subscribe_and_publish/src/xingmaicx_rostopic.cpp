#include "xingmaicx_rostopic.h"


/*
@brief: log file to txt ,mkdir log path
*/
xingmaicx_rostopic_log::xingmaicx_rostopic_log(string log_pwd_path)
{
    //输出obu log初始化
    //time
    time_t now = time(NULL);
    struct tm *time_info=localtime(&now);
    char timepath[60];
    strftime(timepath,60,"%Y_%m_%d_%H_%M_%S",time_info);

    //ofstream 
    //string path="./logs";
    if(access(log_pwd_path.c_str(),0)==-1)
    {
        mkdir(log_pwd_path.c_str(),S_IRWXU);
    }

    path_time=log_pwd_path+"/"+string(timepath);
    if(access(path_time.c_str(),0)==-1)
    {
	    mkdir(path_time.c_str(),S_IRWXU);
    }

    //file_path_txt=path_time+"/obu_output_log.txt";

}

/*
@brief: time calculate 
@params[in]: 
@params[out]:
@return time
*/
double xingmaicx_rostopic_log::xingmaicx_time_us()
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    //printf("tvsec usec = %ld\n",tv.tv_sec*1000000+tv.tv_usec);//ms

    double t1 = tv.tv_sec*1000000+tv.tv_usec;
    double t2 = t1/1000000;
    //printf("t2 = %f\n",t2);
    return t2;
}

//topic 
void xingmaicx_rostopic_log::printf_topic_log(string file_path_txt,const char* format,...)
{
    va_list arg_ptr;
    
    //size = vsnprintf(NULL, 0, format, arg_ptr);
    
    do { 
    clock_t time_temp;
    FILE* file; 
    string file_name = path_time+"/"+file_path_txt+".txt";
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
    @brief: write time log to txt
*/
void xingmaicx_rostopic_log::ros2_printf_topic_log(string pwd_path,const char* file_path_txt,const char* format,...)
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
