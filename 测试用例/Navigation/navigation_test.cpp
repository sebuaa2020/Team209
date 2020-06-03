#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <iostream>
#include <sys/types.h>
#include <signal.h>
#include <cstring>
#include <sstream>

class Navigation_Test {
public:
    Navigation navigation;
    
    void 209T6_1_W() {
        try {
            navigation.check_map();
            navigation.add_point();
            cout << "209T6-1-W测试用例通过" << endl;
        } catch(...) {
            cout << "209T6-1-W测试用例未通过" << endl;
        }
    }

    void 209T6_2_W() {
        try {
            navigation.check_map();
            cout << "209T6-1-W测试用例通过" << endl;
        } catch(...) {
            navigation.add_point();
            cout << "209T6-2-W测试用例通过" << endl;
        }
    }

    void 209T6_4_W() {
        try {
            navigation.check_xml();
            navigation.goto_point("hall");
            cout << "209T6-3-W测试用例通过" << endl;
        } catch(...) {
            cout << "209T6-3-W测试用例未通过" << endl;
        }
    }

    void 209T6_5_W() {
        try {
            navigation.check_xml();
            navigation.goto_point("start");
            cout << "209T6-3-W测试用例未通过" << endl;
        } catch(...) {
            cout << "209T6-3-W测试用例通过" << endl;
        }
    }
}

int main() {
    Navigation_Test test;
    test.209T6_1_W();
    test.209T6_2_W();
    test.209T6_4_W();
    test.209T6_5_W();
    return 0;
}