#include<stdio.h>
#include <Windows.h>
#include <stdlib.h>
#include<conio.h>
#include<time.h>
#include <termios.h>

int get_key(){
	char a[9] = "wsadqetx";
	srand((int)time(0));
 	int rand_num = rand();
	char c = a[rand_num % 8];
	int num; 
	num = 65+c-'a';
	return num;
}

int main(int argc, char** argv){
	int num = 0;
	for(i = 0; i < 20; i++){//共进行20组测试正常测试
		while(num != 65+'x'-'a'){ //当未出现退出键时 
	        num = get_key();
			keybd_event(num,0,0,0);
		} 
		move(argc, argv);
	}
	for(i = 0; i < 10; i++){//共进行10组测试随机测试
		while(num != 65+'x'-'a'){ //当未出现退出键时 
			srand((int)time(0));
			int rand_num = rand();
			num = rand_num % 26 + 65;
	        num = get_next_key();
			keybd_event(num,0,0,0);
		} 
		move(argc, argv);
	}
}
