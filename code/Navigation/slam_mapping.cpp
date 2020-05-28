#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <cstring>
#include <string>
#include <sstream>
	
#define map_pgm "/home/user/catkin_ws/src/maps/Software_Museum.pgm"
#define map_yaml "/home/user/catkin_ws/src/maps/Software_Museum.yaml"
using namespace std;

class Slam {
public:
    //手动建图
    void create_map() {
        int ret = system("gnome-terminal -x roslaunch slam_sim_demo gmapping_demo.launch");
        if (ret != -1 || ret != 127) {
            cout << "Gmapping建图程序已启动" << endl;
        } else {
            throw "command execute error";
        }
    }

    //存储地图
    void save_map() {
        int ret = system("gnome-terminal -x rosrun map_server map_saver -f map");
        if (ret != -1 || ret != 127) {
            cout << "地图文件被成功保存" << endl;
        } else {
            throw "command execute error";
        }
    }

    //删除地图
    void delete_map() {
        try {
            check_map();
        } catch(...) {
            throw "the file doesn't exist";
        }
        string link1 = "gonme-terminal -x rm";
        string link2 = map_pgm;
        string link3 = map_yaml;
        system((link1 + link2).c_str());
        system((link1 + link3).c_str());
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
};

int main() {
    return 0;
}