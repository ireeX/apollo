如何理解体系结构和工作流
===========================================

## 理解Apollo内核的基本原理

自动驾驶汽车\(AV\) 通过控制器局域网络总线 \(CAN bus\)计划引擎计划动力. 软件从硬件寄存器读取数据，并像我们用汇编语言那样把它们写回去。为了简洁地计算，定位模块、感知模块、规划模块作为独立的输入源和输出源通过P2P一起工作。P2P由RPC网络应用支持。
ApolloAuto使用ROS1作为底层网络，这意味着ApolloAuto从ROS1借用主节点框架。 由于来自ROS1的XMLRPC真的很旧（与最近的 brpc和 [grpc](https://yiakwy.github.io/blog/2017/10/01/gRPC-C-CORE)相比来说）, 百度开发了自己的RPC原型的protobuff版本。 

在百度的ApolloAuto中，已经描述了三个发展阶段。
1. 离线仿真引擎Dreamview/ApolloAuto内核软件模块
   - 首先了解算法是如何为汽车工作的 
   - 我们不需要触摸真正的汽车或硬件，立即开始开发。
2. 核心模块集成： 
   - 定位
   - 感知：\(支持第三方解决方案，如为L2开发基于Mobileye ES4 芯片的相机\) 处理 `Lidar`传来的点云数据并根据请求返回分段对象信息
   - 规划：计算微调路径和从Routine部分传递来的路径段进行汽车动态控制信息
   - 路线: 通过 `Navigator` 接口寻找路径段的本地实现; 用 A\*star 算法 
3. 高清地图。 是与L2自动驾驶车辆开发的关键不同点之一。 L4自动驾驶车辆需要高精地图。因此机器人 \(一辆自动驾驶车辆 \)需要在微处理器中重新构建3d世界 \(请查看 OpenCV [SLAM]() 章节\) , 地图和现实世界中重新定位AV中，参考物体坐标都发挥着巨大的作用。
4. 基于云的在线仿真驱动场景引擎和数据中心。 
   - 作为百度的合作伙伴, 您将获得docker凭据以提交新图像并重放您在云上开发的算法。
   - 创建和管理复杂场景以模拟真实世界的驾驶体验

## ROS基础订阅和发布机制以及ApolloAuto模块结构


#### ROS基础订阅和发布机制

那么基于ROS1的系统如何相互通信以及ApolloAuto如何利用它呢? ROS有[教程](http://wiki.ros.org/ROS/Tutorials), 在分析ApolloAuto模块结构之前，我会快速解释一下。

ROS是一款软件，目前仅由Ubuntu系列提供支持。它有一个主要roscore. 

> printenv | grep ROS

默认的ros主要uri是http://localhost:11311. 可以通过执行ros::init来创建一个独立的可执行文件，并通过使用c++或python执行ros::spin（某种Linux事件循环）来启动它。
新创建的包的可执行文件叫做 ***ROS node***. 为了方便其它节点查询，节点将在Master中注册其名称和IP地址。 节点通过直接构建TCP连接与每个节点进行通信。

如果节点想要从其他节点读取数据，我们称之为订户（subscriber）。 典型的格式如下

```
... bla bla bla
ros::NodeHandle h;
ros::Subscriber sub = h.subscribe("topic_name", q_size, cb)
.. bla bla bla
```

如果某个节点想要为订阅者提供读取数据，我们将其称为发布者（publisher）。 典型的格式如下 

```
... bla bla bla
ros::NodeHandle h;
ros::Publisher pub = h.advertise<generated_msg_format_cls>("topic_name", q_size)
... bla bla bla
```

这里的cb是Linux内核IO准备就绪时执行的回调。 考虑到这些签名，我们可以在深入研究核心模块实现之前快速分析ApolloAuto模块结构。

#### ApolloAuto模块结构

我已对此进行了全面的研究，但我无法全部向您展示。 ApolloAuto modules/common/ 提供基本的微控制器来控制每个模块的ros::spin并且/modules/common/adaptor包含有关如何注册主题的最多信息。 每个模块都将从[点](https://github.com/yiakwy/apollo/blob/master/modules/common/adapters/adapter_manager.cc#L50)注册。通过阅读定义了${MODULE_NAME}/conf的配置文件，我们可以获得有关模块订阅和发布的主题的基本信息。

每个模块首先触发 "Init" 接口并注册回调。 如果你想在gdb中逐步调试ApolloAuto，请确保在这些中添加了断点。 这也表明如果你不喜欢百度的实现方法，只需覆盖回调。

## 数据预处理和扩展卡尔曼滤波器

卡尔曼滤波器是数学交互方法，在不知道整个实时输入序列的情况下收敛到实际估计。 无论您需要处理哪种数据，都可以依赖卡尔曼滤波器。 扩展卡尔曼滤波器用于矩阵格式的3d刚性运动。 这并不难。我向您推荐由United States F15导演的系列教程[Michel van Biezen](https://www.youtube.com/watch?v=CaCcOwJPytQ).

由于它用于输入数据预处理，您可能会在高清地图，感知，规划等中看到它。
 
## 选择的模块分析

#### HMI & Dreamviewer

HMI交互和Dreamview没有太多可以说的地方，但它是一个可视化topic参数的好地方。 

HMI是一个简单的基于Flask的Python应用程序。
它不使用HTTP，而是使用Web套接字查询ROS模块应用程序。如果您有异步HTTP下载器的经验，很容易理解，HTTP连接只是一个套接字连接文件描述符，我们已经将HTTP报头、方法写入该缓冲区。一旦HMI Flask后端接收到一个命令，它将执行一个子进程来执行相应的二进制文件
。
相比之下Dreamviewer, 更像是由 React, Webpack, and Threejs 技术\( WebGL, see /dreamview/backend/simulation_world,/dreamview/frontend/src/render \)写成的前端应用程序, 它订阅来自ROS节点的消息，并在一帧一帧绘制

#### 感知

最初，该模块实现逻辑专用于激光雷达和雷达过程。它被AdvestMeor注册为ROS节点，作为信息融合系统来输出观测到的障碍信息。在最新版本的代码中，ROS节点的不同硬件输入处理器被指定在/perception/obstacles/onboard
，并在不同的并行位置上实现，其由*激光雷达、雷达、交通灯和GPS*组成。
1. 激光雷达:
   - 高精地图：获得转换矩阵转换点世界坐标到局部坐标并建立地图多边形
   - ROI 滤波器: 获取ROI并对输入数据进行卡尔曼滤波
   - Segmentation: 基于U-NET的（许多变体）CAFFE模型将加载并基于HD映射和ROI滤波结果的数据进行正向计算。
   对象构建：激光雷达返回点（x，y，z）。因此，你需要把它们分成“障碍”\（向量或集合\）。   
   - 障碍物跟踪器：百度正在使用来自谷歌的HM求解器。对于一个大的二部图，拉格朗日格式的KM算法通常被部署，因为SGD是可以非常简单使用的。
2. 雷达:
   - 类似于激光雷达与来自传感器的raw_obstacles信息。
   - ROI滤波器：获取ROI对象并对输入数据进行卡尔曼滤波
   - 障碍物跟踪器

3. 概率融合\（阿波罗1.5的新内容\）：
   - 据我所知，Apple Load中的融合系统
   - 它通常是一个最重要的部分：收集所有的信息，并将主板上的传感器的信息与跟踪列表和基于规则的认知引擎进行最终组合
   - 主要过程是关联，因此这里的HM算法被再次用作二部图。
   - 根据时间戳维护跟踪列表，并基于概率规则引擎更新每个列表。
