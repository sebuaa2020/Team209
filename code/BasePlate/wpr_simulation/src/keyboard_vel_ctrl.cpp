#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <termios.h>

static double linear_vel = 0.1;
static double angular_vel = 0.1;
static int k_vel = 3; //限速
double speed_x=0,speed_y=0,rotate_z=0,q=0;

struct state{
	int x,y;
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
  return (char) c;
}

void control_base(char c){
	if(c=='w')
	{
	  speed_x += linear_vel;
	} 
	else if(c=='s')
	{
	  speed_x += -linear_vel;
	} 
	else if(c=='a')
	{
	  speed_y += linear_vel;
	}
	else if(c=='d')
	{
	  speed_y += -linear_vel;
	} 
	else if(c=='q')
	{
	  rotate_z += angular_vel;
	} 
	else if(c=='e')
	{
	  rotate_z += -angular_vel;
	} 
	else if(c=='t')
	{
	  speed_x = 0;
	  speed_y = 0;
	  rotate_z = 0;
	} 
	else if(c=='x')
	{
	  q = 1;
	} 
	else
	{
	   printf(" - 未定义指令 \n");
	}
}


int main(int argc, char** argv)
{
	ros::init(argc, argv, "keyboard_vel_ctrl");
	ros::NodeHandle n;
	ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	//ros::Rate loop_rate(10);
	geometry_msgs::Twist base_cmd;
	base_cmd.linear.x = 0;
	base_cmd.linear.y = 0;
	base_cmd.angular.z = 0;

	/*printf("键盘控制WPR机器人： \n");
	printf("w - 向前加速 \n");
	printf("s - 向后加速 \n");
	printf("a - 向左加速 \n");
	printf("d - 向右加速 \n");
	printf("q - 左旋加速 \n");
	printf("e - 右旋加速 \n");
	printf("t - 刹车 \n");
	printf("x - 退出 \n");
	printf("------------- \n");*/
	
	while(ros::ok())
	{
		char cKey = GetCh();
		control_base(cKey);
		if(q==1){
			speed_x = 0;
			speed_y = 0;
			rotate_z = 0;
			base_cmd.linear.x = speed_x;
			base_cmd.linear.y = speed_y;
			base_cmd.angular.z = rotate_z;
			cmd_vel_pub.publish(base_cmd);
			printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
			printf("退出！ \n");
			return 0;
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
		base_cmd.linear.x = speed_x;
		base_cmd.linear.y = speed_y;
		base_cmd.angular.z = rotate_z;
		cmd_vel_pub.publish(base_cmd);
		printf(" - linear.x= %.2f linear.y= %.2f angular.z= %.2f \n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
		//loop_rate.sleep();
	}
	return 0;
} 
