#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <termios.h>

static double linear_vel = 0.1;
static double angular_vel = 0.1;
static int k_vel = 3; //限速

struct state{
	double x,y,z;
};

class BasePlate{
	public:
		double speed_x=0,speed_y=0,rotate_z=0;
		
		struct return_base_state(){
			struct state s;
			s.x = speed_x;
			s.y = speed_y;
			s.z = rotate_z;
			return s;
		}
		
		void control_base(double x,double y,double z){
			speed_x += x;
			speed_y += y;
			rotate_z += z;
		}
};

int GetCh()
{
  static struct termios oldt, newt;
  tcgetattr( STDIN_FILENO, &oldt);
  newt = oldt;
  newt.c_lflag &= ~(ICANON);
  tcsetattr( STDIN_FILENO, TCSANOW, &newt);
  int c = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt);
  return c;
}

int main(int argc, char** argv)
{
	ros::init(argc, argv, "BasePlate");
	
	printf("键盘控制WPR机器人： \n");
	printf("w - 向前加速 \n");
	printf("s - 向后加速 \n");
	printf("a - 向左加速 \n");
	printf("d - 向右加速 \n");
	printf("q - 左旋加速 \n");
	printf("e - 右旋加速 \n");
	printf("空格 - 刹车 \n");
	printf("x - 退出 \n");
	printf("------------- \n");
	BasePlate* base = new BasePlate();
	ros::NodeHandle n;
	ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);

	geometry_msgs::Twist base_cmd;
	base_cmd.linear.x = 0;
	base_cmd.linear.y = 0;
	base_cmd.angular.z = 0;

	while(ros::ok())
	{
		int cKey = GetCh();
		if(cKey=='w')
		{
		  base->speed_x += linear_vel;
		} 
		else if(cKey=='s')
		{
		  base->speed_x += -linear_vel;
		} 
		else if(cKey=='a')
		{
		  base->speed_y += linear_vel;
		}
		else if(cKey=='d')
		{
		  base->speed_y += -linear_vel;
		} 
		else if(cKey=='q')
		{
		  base->rotate_z += angular_vel;
		} 
		else if(cKey=='e')
		{
		  base->rotate_z += -angular_vel;
		} 
		else if(cKey==' ')
		{
		  base->speed_x = 0;
		  base->speed_y = 0;
		  base->rotate_z = 0;
		} 
		else if(cKey=='x')
		{
		  base_cmd.linear.x = speed_x;
		  base_cmd.linear.y = speed_y;
		  base_cmd.angular.z = rotate_z;
		  cmd_vel_pub.publish(base_cmd);
		  printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
		  printf("退出！ \n");
		  return 0;
		} 
		else
		{
		   printf(" - 未定义指令 \n");
		}
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
		base_cmd.linear.x = base->speed_x;
		base_cmd.linear.y = base->speed_y;
		base_cmd.angular.z = base->rotate_z;
		cmd_vel_pub.publish(base_cmd);
		printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
	}
	return 0;
}
