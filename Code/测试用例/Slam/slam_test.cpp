class Slam_Test {
public:
    Slam slam;
    void 209T5_1_W() {
        try {
            slam.create_map();
            cout << "209T5-1-W测试用例未通过" << endl;
        } catch {
            cout << "209T5-1-W测试用例通过" << endl;
        }
    }

    void 209T5_2_W() {
        try {
            slam.check_map();
            slam.create_map();
            cout << "209T5-2-W测试用例通过" << endl;
        } catch {
            cout << "209T5-2-W测试用例未通过" << endl;
        }
    }

    void 209T5_3_W() {
        try {
            slam.check_map();
            cout << "209T5-2-W测试用例未通过" << endl;
        } catch {
            slam.create_map();
            cout << "209T5-2-W测试用例通过" << endl;
        }
    }

    void 209T5_4_W() {
        try {
            slam.check_map();
            cout << "209T5-2-W测试用例未通过" << endl;
        } catch {
            slam.create_map();
            slam.save_map();
            cout << "209T5-2-W测试用例通过" << endl;
        }
    }
}

int main() {
    Slam_Test test;
    test.209T5_1_W();
    test.209T5_2_W();
    test.209T5_3_W();
    test.209T5_4_W();
    return 0;
}