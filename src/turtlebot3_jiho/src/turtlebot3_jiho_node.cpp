#include <ros/ros.h> 
#include <cv_bridge/cv_bridge.h> 
#include <cv.hpp> 
#include <iostream> 

#include <sensor_msgs/LaserScan.h>
#include <geometry_msgs/Twist.h>

#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <termio.h>
#include <unistd.h>
 
using namespace std; 
using namespace cv;

ros::Publisher pub; 
geometry_msgs::Twist cmd;    
ros::Subscriber sub_image;  

void getImage(const sensor_msgs::CompressedImageConstPtr& msg) 

{     
    cv_bridge::CvImageConstPtr cv_ptr;     
    
    Mat src; 
    Mat src1 ; 
    Mat ex1 ; 

    try
    {         
        cv_ptr = cv_bridge::toCvCopy(msg, sensor_msgs::image_encodings::BGR8);     
    }     

    catch (cv_bridge::Exception& e)
    {         
        ROS_ERROR("cv_bridge exception: %s", e.what());         
        return;     
    } 

    src = cv_ptr->image;  
    
    imshow("src", src);  
    inRange(src,Scalar(40,210,210),Scalar(252,255,255),ex1);   
    
    cvtColor(src,src1,CV_BGR2HSV);  

    Mat ex3 ; 

    inRange(src1,Scalar(160,70,50),Scalar(180,250,250),ex3);
    
    Rect rect(0,0,640,480);
    Rect rect1(0,54,640,90) ; 

    Mat rect_roi=ex1(rect) ;  
    Mat rect_roi3=ex3(rect1) ; 
    
    
    imshow("Line", rect_roi);   
    imshow("Red", rect_roi3);  
    
    int value ;  
    int count3 = 1; 
    int count = 1; 
    int i = 0 ; 
    int j = 0 ;    
    int a = 0 ;     
    
    //////////////////////////////////////////////////////////
    for (a=0;a<640;a++) 
    {   
        value = rect_roi.at<uchar>(400,a) ; 
        if(value==255) 
        {  
            count++ ; 
        }
    }
    if (count>100) 
    { 
        cmd.linear.x =0.05;
        cmd.angular.z =0;
        pub.publish(cmd);  
        return ; 
    }
    //////////////////////////////////////////////////////////
    for(j=0;j<10;j++) 
    {
    for (i=0;i<640;i++) 
    {   
        value = rect_roi3.at<uchar>(30+j,i) ; 
       if(value==255) 
       { 
           count3++ ;  
       }  
    } 
    }

    for (i=0;i<320;i++) 
    {   
        value = rect_roi.at<uchar>(400,i+320) ; 
        if(value==255) 
        {  
            
            break ; 
        }
    }

    for (j=0;j<320;j++) 
    {   
        value = rect_roi.at<uchar>(400,320-j) ; 
        if(value==255) 
        {
            
            break ; 
        }
    } 
    //////////////////////////////////////////////////////////
    
    if(count3>50)
        { 
            cmd.linear.x =0;
            cmd.angular.z =0;
            pub.publish(cmd);     
            return ; 
        }
    j = j+55 ;
    //////////////////////////////////////////////////////////
        if(i>300) 
        { 
            cmd.linear.x =0.05;
            cmd.angular.z =0;
            pub.publish(cmd);     
            return ; 
        }
         if(j>300) 
        { 
            cmd.linear.x =0.05;
            cmd.angular.z =0;
            pub.publish(cmd);     
            return ; 
        }
    //////////////////////////////////////////////////////////

    cout<<i<<"////"<<j<<endl;
    
    //////////////////////////////////////////////////////////
    int dis = i-j ; 
        if(dis>20) 
    {   
        cmd.linear.x =0;
        cmd.angular.z = -0.1 ; 
        pub.publish(cmd);     
    }
        else if(dis<-20) 
    {   
        cmd.linear.x =0;
        cmd.angular.z = 0.1 ; 
        pub.publish(cmd);  
    } 
        else  
    { 
        cmd.linear.x = 0.05  ;
        cmd.angular.z = 0 ; 
        pub.publish(cmd);
    }  
    ////////////////////////////////////////////////////////// 

    // cout <<  vx  <<  "\t" <<  vr << endl ;  
    
    
    waitKey(1); 

} 

int main(int argc, char **argv)
{     

    ros::init(argc, argv, "turtlebot3_opencv");     
    ros::NodeHandle nh; 
    
    pub = nh.advertise<geometry_msgs::Twist>("/cmd_vel", 5);
    sub_image = nh.subscribe("/usb_cam/image_raw/compressed", 100, getImage); 

    while(ros::ok())
    {   
        ros::spinOnce();     
    } 

    return 0; 

}
