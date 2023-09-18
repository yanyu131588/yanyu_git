#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sys/time.h"
#include "geometry_msgs/msg/pose_stamped.hpp"

//log
#include <string>
#include <iostream>
#include <fstream>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
using namespace std;
//string file_path_topic_pub_sub_time_txt;
//string file_path_topic_callback_time_txt;
string path_time;
//vector<string> vec_topic_file_pub_sub_txt_name;
//vector<string> vec_topic_file_callback_txt_name;


/***********************log************************/
//obu日志保存文件输出
//ofstream obu_log_output_txt;//未用
//string file_path_txt;//输出文件，初始化
//	fprintf(file,"[%s,%d]",__FUNCTION__,__LINE__) ;
#define printf_log(file_path_txt,format,...) \
do { \
    clock_t time_temp;\
    FILE* file; \
    if((file=fopen(file_path_txt.c_str(),"a"))!=NULL) \
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

//topic 
#define printf_topic_log(file_path_txt,format,...) \
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
/***********************log************************/



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

/*
@brief: log file to txt ,mkdir log path
*/
void xingmaicx_time_log(string log_pwd_path)
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
@brief: output topic time file 
*/
void topic_time_log(string topic)
{
    string topic_file_pub_sub_name = path_time+"/"+topic+"_pubsub.txt";
    string topic_file_callback_name = path_time+"/"+topic+"_callback.txt";
    //vec_topic_file_pub_sub_txt_name.push_back(topic_file_pub_sub_name);
    //vec_topic_file_callback_txt_name.push_back(topic_file_callback_name);

    //file_path_topic_pub_sub_time_txt = topic_file_pub_sub_name;
    //file_path_topic_callback_time_txt = topic_file_callback_name;

}

/*
@brief: close topic time file
*/
void topic_time_log_close(string topic)
{



}

class Subscribe : public rclcpp::Node
{
public:
    Subscribe(std::string name) : Node(name)
    {

        RCLCPP_INFO(this->get_logger(), "大家好，我是%s.", name.c_str());
          // 创建一个订阅者订阅话题
         subscribe_and_publish_subscribe_ = this->create_subscription<std_msgs::msg::String>("subscribe_and_publish", 10, std::bind(&Subscribe::command_callback, this, std::placeholders::_1));
         subscribe_and_publish_subscribe_pose_ = this->create_subscription<geometry_msgs::msg::PoseStamped>("subscribe_and_publish_pose",10,std::bind(&Subscribe::command_callback2, this, std::placeholders::_1));
    
        //log initialize create filepath
        xingmaicx_time_log("./logs");
        //topic_time_log("subscribe_and_publish_pose");
    }


private:
     // 声明一个订阅者
    rclcpp::Subscription<std_msgs::msg::String>::SharedPtr subscribe_and_publish_subscribe_;
    rclcpp::Subscription<geometry_msgs::msg::PoseStamped>::SharedPtr subscribe_and_publish_subscribe_pose_;

    void command_callback2(const geometry_msgs::msg::PoseStamped::SharedPtr msg)
    {
        double curr_time = xingmaicx_time_us();
        double pub_time =msg->header.stamp.sec+msg->header.stamp.nanosec/1e9;
        printf("[%s,%d]:pub time = %f\n",__FUNCTION__,__LINE__,pub_time);
        printf("[%s,%d]:curr time = %f\n",__FUNCTION__,__LINE__,curr_time);

        for(int i=0;i<100;i++)
        {
            int a =0;
            a++;
        }

        double end_time = xingmaicx_time_us();
        printf("[%s,%d]:callback time = %f\n",__FUNCTION__,__LINE__,end_time-curr_time);
        printf("[%s,%d]:sub pub diff time = %f\n",__FUNCTION__,__LINE__,curr_time-pub_time);

        //log output
        //printf_log(vec_topic_file_pub_sub_txt_name[0],"%f",curr_time-pub_time);//printf_log(file_path_txt,format,...)
        //printf_log(vec_topic_file_callback_txt_name[0],"%f",end_time-curr_time);//
        printf_topic_log("command_callback2","%f",curr_time-pub_time);
    }

     // 收到话题数据的回调函数
    void command_callback(const std_msgs::msg::String::SharedPtr msg)
    {
#if 1
        struct timeval tv;
        gettimeofday(&tv,NULL);
        printf("tvsec usec = %ld\n",tv.tv_sec*1000000+tv.tv_usec);//ms

        double t1 = tv.tv_sec*1000000+tv.tv_usec;
        double t2 = t1/1000000;
        printf("t2 = %f\n",t2);
#endif 

        const auto start_time = std::chrono::system_clock::now();
        auto start_time_us = std::chrono::duration_cast<std::chrono::microseconds>(start_time.time_since_epoch());//us

        std::time_t now_c = std::chrono::system_clock::to_time_t(start_time);
        std::cout << "sub Log event happened at " << now_c<<"start time us = "<<start_time_us.count()<<std::endl;//std::ctime(&now_c);
        printf("starttime us=%f\n",double(start_time_us.count())/1000000);

        //const auto current_time = std::chrono::system_clock::now();
        //const auto message_time = std::chrono::seconds(msg->header.stamp.sec)+std::chrono::nanoseconds(msg->header.stamp.nanosec);
        // double speed = 0.0f;
        // if(msg->data == "1234")
        // {
        //     speed = 0.2f;
        // }
        // RCLCPP_INFO(this->get_logger(), "收到[%s]指令，发送速度 %f", msg->data.c_str(),speed);
        RCLCPP_INFO(this->get_logger(), "收到[%s]指令", msg->data.c_str());

        const auto end_time = std::chrono::system_clock::now();
        auto end_time_us = std::chrono::duration_cast<std::chrono::microseconds>(end_time.time_since_epoch());//us

        //auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end_time - start_time);
        std::cout << "sub Log event happened at " << now_c<<"end time us = "<<end_time_us.count()<<std::endl;//std::ctime(&now_c);
        const auto time_diff = end_time-start_time;
        std::cout << "duration: " << start_time_us.count()-end_time_us.count()<< "micro seconds" << std::endl;
        printf("end_time_us us=%f\n",double(end_time_us.count())/1000000);
        std::cout<<"duration: "<<time_diff.count()*1e-9<<"seconds"<<std::endl;
    };
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*产生一个的节点*/
    auto node = std::make_shared<Subscribe>("subscribe1");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

