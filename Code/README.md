# 软件工程（嵌入式开发）209代码使用说明

## 环境配置

在本地新建文件夹demo_ws，在src中新建一个src文件夹，将src中的所有文件复制至其中，并为其配置设备访问权限。使用以下命令进行并编译工作空间

```
cd ~/demo_ws
catkin_make
```

将demo2_ws刷新并写入~/.bashrc文件

```
source ./devel/setup.bash
```

启动Gazebo仿真环境  

```
roslaunch robot_sim_demo robot_spawn.launch
```

![1591604110530](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\1591604110530.png)

## 移动控制

使用demo_ws/下的已经编写好的.sh文件进行移动控制

```
bash ahead.sh #机器人前进
bash back.sh #机器人后退
bash left.sh #机器人左移
bash right.sh #机器人右移
bash left_turn.sh #机器人左转
bash right_turn.sh #机器人右转
```

## SLAM建图

启动建图程序  

```
roslaunch slam_sim_demo gmapping_demo.launch
```

启动rviz可视化工具，这里已经添加了一些必须模块，如LaserScan，Map等等  

```
roslaunch slam_sim_demo view_slam.launch
```

![1591604328727](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\1591604328727.png)

运行键盘控制程序，可控制小车在地图中建图 

```
rosrun robot_sim_demo robot_keyboard_teleop.py
```

地图完成后，执行保存地图指令

```
rosrun map_server map_saver -f map
```

## 导航

### 即时目标导航

启动蒙特卡罗自适应算法

```
roslaunch navigation_sim_demo amcl_demo.launch
```

启动rivz可视化工具

```
roslaunch navigation_sim_demo view_navigation.launch
```

![1591604499358](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\1591604499358.png)

### 固定导航点

添加导航点

```
roslaunch waterplus_map_tools add_waypoint.launch
```

![1591604559950](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\1591604559950.png)

保存固定导航点，在根目录下可以看到保存的waypoints.xml文件 

```
roslaunch waterplus_map_tools add_waypoint.launch
```

![1591604598866](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\1591604598866.png)

修改路径点名称，用nano或者vim打开waypoint.xml文件，并修改节点的name部分

```
nano waypoint.xml
vim waypoint.xml
```



## 目标检测

启动rivz可视化工具，通过任何使机器人移动的方式使机器人朝向目标

```
roslaunch detect_209 obj_detect.launch
```

![1591605748620](C:\Users\DELL\AppData\Roaming\Typora\typora-user-images\1591605748620.png)

保存目标识别信息

```
echo "object: coke" > the_path_you_want
rostopic echo -c /recognized_object_array | grep -m1 confidence >> the_path_you_want
rostopic echo -c /recognized_object_array | grep -m1 -A8 position >> the_path_you_want
```

## 语音控制

语音识别命令无法在代码中独立开启，请结合前端体验。