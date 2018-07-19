
# 如何进行性能分析

分析模块的目的是使用工具（这里我们使用google-perftools）检查模块的性能问题。 
Apollo开发版Docker拥有您需要配置的所有配置工具。因此，你可以在Apollo开发版Docker中做如下所有步骤：

## 在分析模式下构建Apollo

首先，在分析模式下构建Apollo
```
bash apollo.sh build_prof
```

## 播放 rosbag

要配置一个模块，您需要提供它的输入数据以确保它的大部分代码可以被执行。

您可以通过如下指令播放一个信息丰富的rosbag

```
rosbag play -l your_rosbag.bag
```


## 在分析模式中启动模块
用如下指令启动模块

```
CPUPROFILE=/tmp/${MODULE}.prof /path/to/module/bin/${MODULE} --flagfile=modules/${MODULE}/conf/${MODULE}.conf \
 --${MODULE}_test_mode \
 --${MODULE}_test_duration=60.0 \
 --log_dir=/apollo/data/log

```
`MODULE`是您想要测试的模块名。


## 分析模式的gflags
每个模块都有一个预定义的 `${MODULE}_test_mode` 和 `${MODULE}_test_duration` gflag.
这两个gflag告诉模块，当`${MODULE}_test_mode`是true时，运行 `${MODULE}_test_duration` 定义的时间.

大部分Apollo模块已经有这两个gflag了. 如果它们不存在于您感兴趣的模块中，您可以自行定义。 您可以参考gflag `planning_test_mode` 和 `planning_test_duration`的用法来定义您的gflag。

## 生成pdf报告

最后，您可以创建PDF报告来查看分析结果。 

```
google-pprof --pdf --lines /path/to/module/bin/${MODULE} /tmp/${MODULE}.prof > ${MODULE}_profiling.pdf
```

## 示例
下面是启动规划模块的示例命令。
```
PUPROFILE=/tmp/planning.prof /apollo/bazel-bin/modules/planning/planning \
 --flagfile=modules/planning/conf/planning.conf \
 --log_dir=/apollo/data/log \
 --planning_test_mode \
 --test_duration=65.0

google-pprof --pdf --lines /apollo/bazel-bin/modules/planning/planning /tmp/planning.prof > planning_prof.pdf
```

