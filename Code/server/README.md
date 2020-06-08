# 前端使用说明



## 总体概述

前端的文件是为了北航计算机学院2020年软件工程嵌入式机器人的使用配套开发的web界面，使用了python flask轻量级框架来进行开发，配套有相应的html、css、js等文件，后端通过python来与机器人进行交互。

## 说明

由于项目时间问题，暂时并未部署到服务器上，所以目前只能在本地利用localhost来执行，建议在pycharm等python编译器下运行。

## 页面设计

### 用户登录界面

![](https://github.com/sebuaa2020/Team209/blob/master/Code/server/image/%E7%99%BB%E5%BD%95.png)

### 用户注册界面

![](https://github.com/sebuaa2020/Team209/blob/master/Code/server/image/%E6%B3%A8%E5%86%8C.png)

### 修改密码界面

![](https://github.com/sebuaa2020/Team209/blob/master/Code/server/image/%E4%BF%AE%E6%94%B9%E5%AF%86%E7%A0%81.png)

### 注销账户界面

![](https://github.com/sebuaa2020/Team209/blob/master/Code/server/image/%E6%B3%A8%E9%94%80.png)

### 欢迎页面

![](https://github.com/sebuaa2020/Team209/blob/master/Code/server/image/%E6%AC%A2%E8%BF%8E.png)

### 功能选择页面

![](https://github.com/sebuaa2020/Team209/blob/master/Code/server/image/%E5%8A%9F%E8%83%BD%E9%80%89%E6%8B%A9.png)

### 操作文档下载页面

![](https://github.com/sebuaa2020/Team209/blob/master/Code/server/image/%E6%93%8D%E4%BD%9C%E6%96%87%E6%A1%A3%E4%B8%8B%E8%BD%BD.png)

## 前端使用方法

首先确保请安装好相应的环境，包括python3.7、flask等。

然后执行server文件夹中的test_flask.py文件。

如果看到编译成功的显示，说明可以正常使用了。

![](https://github.com/sebuaa2020/Team209/blob/master/Code/server/image/%E7%BC%96%E8%AF%91.png)

在这里我们指定的端口为1234，如果该端口已经被占用，那么请修改test_flask.py中main函数的指定端口即可。

然后在浏览器中打开http://localhost:1234/login.html即可进入到登录界面，通过相应操作即可开始使用该软件。
