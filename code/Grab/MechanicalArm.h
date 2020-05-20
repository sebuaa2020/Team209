#pragma once
#define WPBH_TEST_MANI_ZERO 0
#define WPBH_TEST_MANI_DOWN 1
#define WPBH_TEST_MANI_UP   2
#define WPBH_TEST_MANI_FOLD 3

class MechanicalArm
{
public:
	double height;
	double separation;
	int nState;
	void user_control(int state);
	void robot_control();
	MechanicalArm();
};

