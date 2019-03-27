# 纯C++ 捕鱼游戏  
语言:C++  
编辑器:VS2015  
渲染:D2D  
碰撞:obb和aabb  
编译选项:请选择Release x86 编译
## 项目文件目录说明
img 放游戏所使用的图片文件夹  
frame 放控制游戏场景相关的文件  
instance 放游戏窗口进程 游戏循环 工具类 碰撞类的文件  
render 放游戏渲染引擎的文件夹  
trigger 放对一些消息进行映射的文件夹  
后面会详细对游戏的各个流程进行详细说明   
主要说明:  
[开发流程介绍](https://blog.csdn.net/baidu_38766085/article/details/83512219)  
[渲染类content.h的封装](https://blog.csdn.net/baidu_38766085/article/details/83513339)  
[显示对象DisplayObject.h的封装](https://blog.csdn.net/baidu_38766085/article/details/83549116)  
[精灵对象sprite.h的封装](https://blog.csdn.net/baidu_38766085/article/details/83685196)  
[场景类action.h的封装](https://blog.csdn.net/baidu_38766085/article/details/83796034)  
[计时器对象ticker.h的封装](https://blog.csdn.net/baidu_38766085/article/details/83956184)  
[窗口对象DemoApp.h的说明](https://blog.csdn.net/baidu_38766085/article/details/83796063)  
[消息映射和流程触发结构 createBefore.h](https://blog.csdn.net/baidu_38766085/article/details/83956221)  
[子弹对象bullet.h的封装](https://blog.csdn.net/baidu_38766085/article/details/83956242)  
[鱼类fish.h的封装](https://blog.csdn.net/baidu_38766085/article/details/83956260)  
[控制创建鱼类fishConfig.h的封装](https://blog.csdn.net/baidu_38766085/article/details/84074258)  
[编写场景0结构frame0.h](https://blog.csdn.net/baidu_38766085/article/details/84074308)  
[编写场景2结构frame2.h](https://blog.csdn.net/baidu_38766085/article/details/84260688)  
[编写场景1结构frame1.h](https://blog.csdn.net/baidu_38766085/article/details/84260711)  
[金币对象gold.h的封装](https://blog.csdn.net/baidu_38766085/article/details/84260761)  
## 项目目录  
![项目目录截图](https://raw.githubusercontent.com/yinhui1129754/fishing/master/img/pro/m.png)  
## 运行效果截图
![项目运行效果截图](https://raw.githubusercontent.com/yinhui1129754/fishing/master/img/pro/play.gif)  
## 这里说明一下  
由于这是我第一个c++游戏所以这个里面有非常多的bug如果要进行商业开发的话请另行更加快捷的渲染流程(我的这个里面的渲染有问题)
我会在后面的开源游戏中重新构建一种多线程的 非常流畅 非常流畅 非常流畅的渲染形式 后面会对捕鱼的源码进行重写 如果要商用的朋友请一定要记住呀!!!!

