#include "ros/ros.h"
#include "std_msgs/Int8.h"
#include "std_msgs/Int16.h"
#include <stdio.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <termio.h>
#include <unistd.h>
//#include <iostream>

int kbhit();
int getch();
int sub_value=0;
ros::Publisher pub2;
ros::Subscriber sub2;
std_msgs::Int8 msg2;
int key = 0;
int count=0;
	


void msgCallback(const std_msgs::Int16::ConstPtr& given_msg) {     
	//printf("do\n");
	
	sub_value = given_msg->data;
	//printf("%d",sub_value);
	if(sub_value == 0)msg2.data = 5; //stop
	else if(sub_value == 2)msg2.data = 1; //forward
	else if (sub_value == 1)msg2.data = 2; //left
	else if (sub_value == 3)msg2.data = 3; //right
	printf("%d",count);	
	
        if(count>200){
	
                msg2.data = 5;
		pub2.publish(msg2);
	}
	else {
		count++;
		pub2.publish(msg2);
	}	
	
}


int main(int argc, char **argv)
{
	//for pub to motor
	ros::init(argc, argv, "msg_publisher");
	ros::NodeHandle nh2;
	ros::Rate loop_rate(1);
	pub2 = nh2.advertise<std_msgs::Int8>("data_msg", 100);
	sub2 = nh2.subscribe("cam_msg",100,msgCallback);
	
	
	

	
	//for sub from cam
	
	
	
	printf("start\n");
	while(ros::ok())
	{
		ros::spinOnce();
		
		//printf("\nESC to quit");
		/*if(kbhit){
			key = getch();
		}else{
			key = 0;
		}
		switch(key){
			case 27:
				msg2.data = 5;
				pub2.publish(msg2);
            	//return 0;
            	break;

			case 's':
				msg2.data = 5;
				pub2.publish(msg2);
				break;

		}*/
		
		//ROS_INFO("send msg = %d \n", msg2.data);
		

		//loop_rate.sleep();

	}

	return 0;
}

int kbhit(void)
{
    struct termios oldt, newt;
    int ch;
    int oldf;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    oldf = fcntl(STDIN_FILENO, F_GETFL, 0);
    fcntl(STDIN_FILENO, F_SETFL, oldf | O_NONBLOCK);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    fcntl(STDIN_FILENO, F_SETFL, oldf);
    if(ch != EOF)
    {
    ungetc(ch, stdin);
    return 1;
    }
    return 0;
}
int getch(){
    int ch;
    struct termios buf, save;
    tcgetattr(0,&save);
    buf = save;
    buf.c_lflag &= ~(ICANON|ECHO);
    buf.c_cc[VMIN] = 1;
    buf.c_cc[VTIME] = 0;
    tcsetattr(0, TCSAFLUSH, &buf);
    ch = getchar();
    tcsetattr(0, TCSAFLUSH, &save);
    return ch;
}
