#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <stdio.h>
#include <termios.h>
#include <sensor_msgs/LaserScan.h>

static double linear_vel = 0.1;
static double angular_vel = 0.1;
static int k_vel = 3; //限速
double speed_x=0,speed_y=0,rotate_z=0,q=0;
std::vector<float> ranges;


struct state{
	int x,y;
};

void laserCallback(const sensor_msgs::LaserScan::ConstPtr& msg)
{
	ranges=msg->ranges;
}

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
	FILE *fp;
	ros::init(argc, argv, "keyboard_vel_ctrl");
	ros::NodeHandle n;
	ros::Publisher cmd_vel_pub = n.advertise<geometry_msgs::Twist>("/cmd_vel", 10);
	ros::Rate loop_rate(10);
	geometry_msgs::Twist base_cmd;
	ros::NodeHandle node;
        ros::Subscriber sub = node.subscribe("/scan", 1, laserCallback);

	fp=fopen("state.txt","wt+");
	fscanf(fp, "%f %f %f\n", &speed_x, &speed_y, &rotate_z);
	/*base_cmd.linear.x = 0;
	base_cmd.linear.y = 0;
	base_cmd.angular.z = 0;*/
	rewind(fp);
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
		ros::spinOnce();
		//geometry_msgs::Twist base_cmd;
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
			fprintf(fp,"%.2f %.2f %.2f\n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
			printf("退出！ \n");
			return 0;
		}
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
		fprintf(fp,"%.2f %.2f %.2f\n",base_cmd.linear.x,base_cmd.linear.y,base_cmd.angular.z);
		loop_rate.sleep();
	}
	return 0;
} 
