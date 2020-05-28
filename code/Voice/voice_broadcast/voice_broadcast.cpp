#include <stdio.h>
#include <stdlib.h>
#include <regex>
#include <cstring>
#include <string>
#include <iostream>
#include <unistd.h>

using namespace std;

class Voice{
    public:
        //启动语音播报
        void start_voice_broadcast()
        {
            int ret = system("gnome-terminal -x roscore");
            if (ret != -1 || ret != 127) {
              cout << "正在启动语音播报程序" << endl;
            } else {
              throw "voice broadcast execute error";
            }
            sleep(5);
            ret = system("gnome-terminal -x rosrun xfyun_waterplus xf_tts_node");
            if (ret != -1 || ret != 127) {
              cout << "语音播报程序已启动" << endl;
            } else {
              throw "voice broadcast execute error";
            }
        }
        //播报语音
        void voice_broadcast(string text)
        {
             regex r("^[\u4E00-\u9FA5A-Za-z0-9 ]+$");
             if(false == regex_match(text,r)){
                 cout << "无法播报该语句 : " << text << endl;
                 return ;
             }
             string link = "gnome-terminal -x rostopic pub  /voice/xf_tts_topic std_msgs/String ";
             system((link + text).c_str());
        }
};

int main() {
    Voice voice;
    voice.start_voice_broadcast();
    voice.voice_broadcast("您好");
    voice.voice_broadcast("hello");
    voice.voice_broadcast("hello@￥");
    return 0;
}