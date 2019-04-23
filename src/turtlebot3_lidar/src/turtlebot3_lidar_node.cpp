#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

using namespace std;
geometry_msgs::Twist cmd;
ros::Publisher pub;

//double vx=1, vy=0, vz=0, vr=0;
//void stop();
//void go();

void msgCallback(const sensor_msgs::LaserScan::ConstPtr& msg){
    std::vector<float> ranges = msg->ranges;
    for(int i=0; i<30; i++){
        
        if(ranges[i]<0.2&&ranges[i]!=0){
            cmd.linear.x=0;
            pub.publish(cmd);
            }
        else {
            cmd.linear.x=0.00;//0.05
            pub.publish(cmd);
        }
        
        //cout<<"run"<<endl;
        cout<<i<<":     "<<ranges[i]<<endl;
        cout<<cmd.linear.x<<endl;
    }
 
}

int main(int argc, char** argv){
    ros::init(argc, argv, "turtlebot3_lidar");
    ros::NodeHandle nh;
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 5);
    ros::Rate loop_rate(2);
    ros::Subscriber sub = nh.subscribe("/scan", 100, msgCallback);
    
    
    

    while(ros::ok()){
        
        ros::spinOnce();
        loop_rate.sleep();
    }
    return 0;
}

//void stop(){
//    vx=0, vy=0, vz=0, vr=0;
//void go(){
  //  vx=1, vy=0, vz=0, vr=0;}
    
