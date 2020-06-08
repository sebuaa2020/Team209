# 前端使用说明



## 总体概述

前端的文件是为了北航计算机学院2020年软件工程嵌入式机器人的使用配套开发的web界面，使用了python flask轻量级框架来进行开发，配套有相应的html、css、js等文件，后端通过python来与机器人进行交互。

## 说明

由于项目时间问题，暂时并未部署到服务器上，所以目前只能在本地利用localhost来执行，建议在pycharm等python编译器下运行。

## 页面设计

### 用户登录界面

![image-20200608163311696](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20200608163311696.png)

### 用户注册界面

![image-20200608163333648](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20200608163333648.png)

### 修改密码界面

![image-20200608163356663](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20200608163356663.png)

### 注销账户界面

![image-20200608163418634](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20200608163418634.png)

### 欢迎页面

![image-20200608163505718](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20200608163505718.png)

### 功能选择页面

![image-20200608163530682](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20200608163530682.png)

### 操作文档下载页面

![image-20200608163632818](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20200608163632818.png)

## 前端使用方法

首先确保请安装好相应的环境，包括python3.7、flask等。

然后执行server文件夹中的test_flask.py文件。

如果看到编译成功的显示，说明可以正常使用了。

![image-20200608163900163](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\image-20200608163900163.png)

在这里我们指定的端口为1234，如果该端口已经被占用，那么请修改test_flask.py中main函数的指定端口即可。

然后在浏览器中打开http://localhost:1234/login.html即可进入到登录界面，通过相应操作即可开始使用该软件。