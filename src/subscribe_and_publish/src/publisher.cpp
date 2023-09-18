#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sys/time.h"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "xingmaicx_rostopic_log.h"
//#include "xingmaicx_rostopic.h"

//@@@@1 topic log define pwd path
//xingmaicx_rostopic_log rostopic_log("./logs2");//

class Publisher : public rclcpp::Node
{
public:
    // 构造函数,有一个参数为节点名称
    Publisher(std::string name) : Node(name)
    {
        RCLCPP_INFO(this->get_logger(), "大家好，我是%s.", name.c_str());
        // 创建发布者
        subscribe_and_publish_publisher_ = this->create_publisher<std_msgs::msg::String>("subscribe_and_publish", 10);

        subscribe_and_publish_publisher_pose_ = this->create_publisher<geometry_msgs::msg::PoseStamped>("subscribe_and_publish_pose",10);

        // 创建定时器，500ms为周期，定时发布
        timer_ = this->create_wall_timer(std::chrono::milliseconds(500), std::bind(&Publisher::timer_callback, this));
    
        //log
        
    }


private:
    void timer_callback()
    {
        //double start_time = xingmaicx_time_us();

#if 0 
        // 创建消息
        std_msgs::msg::String message;
        //rclcpp::Clock().now();

        message.data = "1234";
        // 日志打印
        RCLCPP_INFO(this->get_logger(), "Publishing: '%s'", message.data.c_str());
        // 发布消息
        subscribe_and_publish_publisher_->publish(message);
#endif 

#if 0
        auto now = std::chrono::system_clock::now();
        std::time_t now_c = std::chrono::system_clock::to_time_t(now);
        std::cout << "Log event happened at " << now_c<<std::endl;//std::ctime(&now_c);
#endif 

#if 1
        geometry_msgs::msg::PoseStamped pose_msg;
        pose_msg.header.frame_id = "base_link";
        pose_msg.header.stamp = this->now();
        pose_msg.pose.position.x=1.0;
        pose_msg.pose.position.y=2.0;
        pose_msg.pose.position.z=0.5;
        pose_msg.pose.orientation.w=1.0;

        subscribe_and_publish_publisher_pose_->publish(pose_msg);
#endif 

#if 1
        struct timeval tv;
        gettimeofday(&tv,NULL);
        printf("tvsec usec = %ld\n",tv.tv_sec*1000000+tv.tv_usec);//ms

        double t1 = tv.tv_sec*1000000+tv.tv_usec;
        double t2 = t1/1000000;
        printf("t2 = %f\n",t2);
#endif 

        //double t = rostopic_log.xingmaicx_time_us();//@@@@2 record time 
        //rostopic_log.printf_topic_log("publish","%f",t);//@@@3 write log txt
        //double end_time = xingmaicx_time_us();
        //ros2_printf_topic_log("/tmp","pose_topic","%f",end_time-start_time);

    }
    // 声名定时器指针
    rclcpp::TimerBase::SharedPtr timer_;
    // 声明话题发布者指针
    rclcpp::Publisher<std_msgs::msg::String>::SharedPtr subscribe_and_publish_publisher_;
    rclcpp::Publisher<geometry_msgs::msg::PoseStamped>::SharedPtr subscribe_and_publish_publisher_pose_;
    
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    /*产生一个的节点*/
    auto node = std::make_shared<Publisher>("publisher");
    /* 运行节点，并检测退出信号*/
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

