#!/usr/bin/expect
source ./devel/setup.bash
yes w | head -1 | rosrun move_209 keyboard_vel_ctrl
