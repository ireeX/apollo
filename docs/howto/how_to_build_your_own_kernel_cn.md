# 安装您自己的内核

## 在您开始安装之前的提示

如果您更改过内核，或者预编译内核不是您最适合您的平台的选择，您可以根据以下步骤构建自己的内核：
## 安装适合您的内核
1.  从代码库克隆代码
```
git clone https://github.com/ApolloAuto/apollo-kernel.git
cd apollo-kernel
```

2.  根据[ESDCAN-README.md](https://github.com/ApolloAuto/apollo-kernel/blob/master/linux/ESDCAN-README.md)添加ESD CAN驱动源代码。
3.  根据如下命令构建内核：
```bash build.sh```
4.  与预编译[Apollo 内核](https://github.com/ApolloAuto/apollo/blob/master/docs/howto/how_to_install_apollo_kernel.md)时一样安装内核。
