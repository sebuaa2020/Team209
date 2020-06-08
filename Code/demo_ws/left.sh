#!/usr/bin/expect
source ./devel/setup.bash
yes a | head -1 | rosrun wpr_simulation keyboard_vel_ctrl