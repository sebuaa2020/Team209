#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <cstring>
#include <sstream>

#define map_pgm "/home/dell/demo_ws/src/wpb_home/wpb_home_tutorials/maps/Software_Museum.pgm"
#define map_yaml "/home/dell/demo_ws/src/wpb_home/wpb_home_tutorials/maps/Software_Museum.yaml"
#define waypoints "~/waypoints.xml"
using namespace std;

class Navigation {
public:
    //添加导航点
    void add_point(){
        try {
            check_map();
        } catch(...) {
            throw "the file doesn't exist";
        }
        system("rm ~/waypoints.xml");
        int ret = system("gnome-terminal -x roslaunch waterplus_map_tools add_waypoint.launch");
        if (ret != -1 || ret != 127) {
            cout << "添加航点进程已启动" << endl;
         } else {
             throw "command execute error";
         }
    }

    //保存导航点
    void save_addpoint() {
        int ret = system("gnome-terminal -x rosrun waterplus_map_tools wp_saver");
        if (ret != -1 || ret != 127) {
            cout << "航点被成功保存" << endl; 
        } else { 
            throw "command execute error";
        }
    }

    //移动到指定导航点
    void goto_point(string name) {
        system("gnome-terminal -x roslaunch waterplus_map_tools wpb_home_nav_test.launch");
        sleep(3);
        system("gnome-terminal -x roslaunch navigation_sim_demo amcl_demo.launch");
        sleep(1);
        string str = "gnome-terminal -x rosrun waterplus_map_tools wp_nav_test " + name;
        char * strc = new char[strlen(str.c_str()) + 1];
        strcpy(strc, str.c_str());
        int ret = system(strc);
        if (ret != -1 || ret != 127) {
            cout << "机器即将移动" << endl;
        } else {
            throw "command execute error";
        }
    }

    //修改某个导航点的名称
    void change_num2name(string num, string name) {
        string str = "sed -i s/\\<Name\\>" + num + "/\\<Name\\>" + name + "/g " + waypoints;
        cout << str << endl;
        char * strc = new char[strlen(str.c_str()) + 1];
        strcpy(strc, str.c_str());
        int ret = system(strc);
        if (ret != -1 || ret != 127) {
            cout << num + "航点名称被成功替换" << endl;
        } else {
            throw "command execute error";
        }
    }

    //检查xml文件是否完好
    void check_xml() {
        fstream xml_file;
        xml_file.open(waypoints, ios::in);
        if (xml_file) {
            cout << waypoints << "文件没有被创建！" << endl;
            throw "the file doesn't exist";
        } 
    }

    //检查地图文件是否完好
    void check_map() {
        fstream png_file;
        png_file.open(map_pgm, ios::in);
        if (png_file) {
            cout << map_pgm << "文件没有被创建！" << endl;
            throw "the file doesn't exist";
        } 
        fstream yaml_file;
        yaml_file.open(map_yaml, ios::in);
        if (png_file) {
            cout << map_yaml << "文件没有被创建！" << endl;
            throw "the file doesn't exist";
        }
    }

    //手动控制+自适应蒙特卡洛定位
    void manual_handle() {
        system("gnome-terminal -x roslaunch robot_sim_demo robot_spawn.launch");
        sleep(1);
        //system("gnome-terminal -x rosrun robot_sim_demo robot_keyboard_teleop.py");
        int ret = system("gnome-terminal -x roslaunch navigation_sim_demo amcl_demo.launch");
        sleep(1);
        if (ret != -1 || ret != 127) {
            cout << "AMCL定位程序已启动" << endl;
        } else {
            throw "command execute error";
        }
        ret = system("gnome-terminal -x roslaunch navigation_sim_demo view_navigation.launch");
        if (ret != -1 || ret != 127) {
            cout << "RVIZ可视化界面已启动" << endl;
        } else {
            throw "command execute error";
        }
    }
};

int main() {
    Navigation navigation;
    //navigation.add_point();
    //navigation.save_addpoint();
    navigation.goto_point("rest");
    //navigation.change_num2name("2", "ace");
    //navigation.manual_handle();

    return 0;
}