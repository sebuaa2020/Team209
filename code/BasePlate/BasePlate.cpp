#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <termios.h>

static double linear_vel = 0.1;
static double angular_vel = 0.1;
static int k_vel = 3; //限速

struct state{
	int x,y;
};

class BasePlate{
	public:
		double speed_x=0,speed_y=0,rotate_z=0;
		double position_x=0,position_y=0;
		
		struct return_base_state(){
			struct state s;
			s.x = position_x;
			s.y = position_y;
			return s;
		}
		
		void control_base(struct ctrl){
			speed_x=ctrl.x;
			speed_y=ctrl.y;
			rotate_z=ctrl.z;
		}
};

int main(int argc, char** argv)
{
	ros::init(argc, argv, "BasePlate");
	ros::NodeHandle n;
	ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

	geometry_msgs::Twist base_cmd;
	base_cmd.linear.x = 0;
	base_cmd.linear.y = 0;
	base_cmd.angular.z = 0;

	while(ros::ok())
	{
		if(speed_x > linear_vel*k_vel)
			speed_x = linear_vel*k_vel;
		if(speed_x < -linear_vel*k_vel)
			speed_x = -linear_vel*k_vel;
		if(speed_y > linear_vel*k_vel)
			speed_y = linear_vel*k_vel;
		if(speed_y < -linear_vel*k_vel)
			speed_y = -linear_vel*k_vel;
		if(rotate_z > angular_vel*k_vel)
			rotate_z = angular_vel*k_vel;
		if(rotate_z < -angular_vel*k_vel)
			rotate_z = -angular_vel*k_vel;
		base_cmd.linear.x = speed_x;
		base_cmd.linear.y = speed_y;
		base_cmd.angular.z = rotate_z;
		cmd_vel_pub.publish(base_cmd);
	}
	return 0;
}