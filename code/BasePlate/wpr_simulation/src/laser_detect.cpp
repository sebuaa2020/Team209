#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <termios.h>
#include <sensor_msgs/LaserScan.h>

std::vector<float> ranges;



void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
	ranges=msg->ranges;
}


int main(int argc, char** argv)
{
	FILE *fp,*fp1;
	ros::init(argc, argv, "laser_detect");
	ros::NodeHandle n;
	ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	ros::Rate loop_rate(10);
	ros::NodeHandle node;
        ros::Subscriber sub = node.subscribe("/scan", 1, laserCallback);

	double speed_x=0,speed_y=0,rotate_z=0,q=0;
	fp=fopen("find.txt","wt+");
	fp1=fopen("state.txt","r");
	/*base_cmd.linear.x = 0;
	base_cmd.linear.y = 0;
	base_cmd.angular.z = 0;*/
	
	while(ros::ok())
	{
		ros::spinOnce();
		//geometry_msgs::Twist base_cmd;
		fscanf(fp1, "%f %f %f\n", &speed_x, &speed_y, &rotate_z);
		rewind(fp1);
		if (ranges.size() == 360) {
			int flag = 0;
			for (int i = 150;i < 210;i++) {
				if (ranges[i] < 0.30) {
					//printf("检测到障碍物！");
					if(speed_x > 0)
						speed_x = 0;
					break;
				}
			}
			for (int i = 0;i < 30;i++) {
				if (ranges[i] < 0.30) {
					//printf("检测到障碍物！");
					if(speed_x < 0)
						speed_x = 0;
					break;
				}
			}
			for (int i = 330;i < 360;i++) {
				if (ranges[i] < 0.30) {
					//printf("检测到障碍物！");
					if(speed_x < 0)
						speed_x = 0;
					break;
				}
			}
			for (int i = 240;i < 300;i++) {
				if (ranges[i] < 0.30) {
					//printf("检测到障碍物！");
					if(speed_y > 0)
						speed_y = 0;
					break;
				}
			}
			for (int i = 60;i < 120;i++) {
				if (ranges[i] < 0.30) {
					//printf("检测到障碍物！");
					if(speed_y < 0)
						speed_y = 0;
					break;
				}
			}
		}
		fprintf(fp, "%.2f %.2f %.2f\n", speed_x, speed_y, rotate_z);
		rewind(fp);
		loop_rate.sleep();
	}
	return 0;
} 
