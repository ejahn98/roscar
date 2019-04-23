#include <ros/ros.h> 
#include <cv_bridge/cv_bridge.h> 
#include <cv.hpp> 
#include <iostream> 
#include <string>
#include <fcntl.h>
#include <sys/wait.h>
#include <termio.h>
#include <unistd.h>


#include <geometry_msgs/Twist.h>
#include <sensor_msgs/LaserScan.h>

#include "std_msgs/Int16.h"
using namespace std; 
using namespace cv;

ros::Subscriber sub_image;
std_msgs::Int16 cam_msg;
ros::Publisher pub;
int const Xcenter = 320;
  int const Yvalue = 200;
  int const width =639;
  int const range =40;
  Point p1(1,Yvalue), p2(width,Yvalue);
  Point p3(Xcenter,Yvalue-20), p4(Xcenter,Yvalue+20);
	
  int Lpixel=0, Rpixel=0;
  int Ldistance=320, Rdistance=320;
  int differ;





//-----------------------------------------------------------------

void getImage(const sensor_msgs::CompressedImageConstPtr& msg)
{
   
    
    cv_bridge::CvImageConstPtr cv_ptr;
    Mat frame,grayframe;

     try{
         cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);
     }
     catch (cv_bridge::Exception& e){ 
         ROS_ERROR("cv_bridge exception: %s", e.what());
         return;
     }
     
     frame=cv_ptr->image;
     
     
     //waitKey(10);

    cvtColor(frame,grayframe,COLOR_BGR2GRAY) ; 
    //imshow("frame",frame2);
    adaptiveThreshold(grayframe,grayframe,255,ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY_INV,21,5);
    medianBlur(grayframe,grayframe,15);
	//medianBlur(grayframe,grayframe,9);
	//medianBlur(grayframe,grayframe,7);




    //line(frame,p1,p2,Scalar(100,100,255),3);
    //line(frame,p3,p4,Scalar(100,100,255),3);
    

	//imshow("frame",frame);
    //imshow("lane_detection",grayframe);

    for(int c1=Xcenter;c1<639;c1++){
      Rpixel = grayframe.at<uchar>(Yvalue,c1);
      if(Rpixel == 255){
        Rdistance = c1-Xcenter;
        break;
      }

    }
    //cout<<Rdistance<<endl;
    for(int c2=Xcenter;c2>0;c2--){
      Lpixel = grayframe.at<uchar>(Yvalue,c2);
      if(Lpixel == 255){
        Ldistance = Xcenter-c2;
        break;
      }

    }
    differ = Ldistance - Rdistance;
    //putText(frame,format("Left:%d, Right:%d, differ:%d", Ldistance,Rdistance,abs(Ldistance-Rdistance)),Point(10,30),FONT_HERSHEY_SIMPLEX,1,Scalar(0,200,200),4);
    //imshow("frame",frame);
    
    if(abs(differ)<=range){
      cam_msg.data=2;
    }
    else if(differ>range){
      cam_msg.data=1;
    }
    else if(differ<(-range)){
      cam_msg.data=3;
    }
    else {
      cam_msg.data=2;
    }
    //ROS_INFO("send msg = %d\n", cam_msg.data);
    
    pub.publish(cam_msg);
    imshow("src",frame);
    imshow("result",grayframe);
    
    waitKey(10);
 
}









int main(int argc, char **argv)
{
  
   
    ros::init(argc, argv, "turtlebot3_opencv"); 
    ros::NodeHandle nh;
    sub_image = nh.subscribe("/usb_cam/image_raw/compressed", 100, getImage);
    pub = nh.advertise<std_msgs::Int16>("cam_msg",100);
    while(ros::ok()){
        ros::spinOnce();
    }
    return 0;
}