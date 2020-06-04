#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <cstring>
#include <sstream>

int main() {
    system("gnome-terminal -x roslaunch robot_sim_demo robot_spawn.launch");
}
