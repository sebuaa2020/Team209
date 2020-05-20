#include "MechanicalArm.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

//用户手动控制机械臂
void MechanicalArm::user_control(int state)
{
	if (state<WPBH_TEST_MANI_ZERO || state>WPBH_TEST_MANI_FOLD)
		throw "state not defined!";
	else {
		nState = state;
		system("gnome-terminal -x  roslaunch wpb_home_tutorials mani_ctrl.launch");
	}
}

//机器人自动抓取物体
void MechanicalArm::robot_control()
{
	system("gnome-terminal -x  roslaunch wpb_home_tutorials grab_demo.launch");
}

MechanicalArm::MechanicalArm()
{
	height = 0.0;
	separation = 0.0;
	nState = WPBH_TEST_MANI_ZERO;
}

