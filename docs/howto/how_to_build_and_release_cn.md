# How to Build and Release your Docker Container
# 怎样构建并释放您的Docker容器

* [1. 安装Docker](#docker)
* [2. 构建并释放](#build_release)
* [3. 用VSCode构建](#build_in_vscode)
* [4. 测试](#test)

## <span id="docker">安装Docker</span>
构建Apollo需要Ubuntu 14.04，用Docker容器是为Apollo项目提供构建环境最简单的方法。更详细的Docker教程请参考[这里](https://docs.docker.com/)。

安装Docker，您可以参考
[Docker-ce官方安装指南](https://docs.docker.com/install/linux/docker-ce/ubuntu).
不要忘了用
[Linux安装完成后教程](https://docs.docker.com/install/linux/linux-postinstall)来测试。

## <span id="build_release">构建和释放</span>
### 启动容器
我们提供的构建容器命名为 *dev-latest*。 容器会在*/apollo* 下安装您的Apollo代码库。
```bash
bash docker/scripts/dev_start.sh
```
### 进入容器
```bash
bash docker/scripts/dev_into.sh
```
### 构建模块
```bash
bash apollo.sh build
```
`注意:` 如果您的电脑非常慢，您可以按照如下指令限制CPU。

```
bash apollo.sh build --local_resources 2048,1.0,1.0
```

### 发行版（Release）可执行文件

```bash
bash apollo.sh release
```
这条指令会生成Release目录，该目录包括ROS环境，运行脚本，可执行文件和依赖共享库（.so文件）。

想要创建一个不含专有软件的发行版（例如ESD CAN库），请使用：
```bash
bash apollo.sh release_noproprietary
```

如果要生成并上传您的镜像到您自己的Docker代码库，请参考[怎样生成并上传Docker镜像](how_to_generate_and_push_docker_images.md)

## <span id="build_in_vscode">在Visual Studio Code中构建</span>
### 安装 VSCode
The easiest way to install for Debian/Ubuntu based distributions is to download from  https://code.visualstudio.com and install the .deb package (64-bit) either through the graphical software center if it's available or through the command line with:
在Debian/Ubuntu上最简单的安装方法就是从https://code.visualstudio.com 上下载并安装.deb安装包（64位），也可以从图形软件中心或者通过命令行下载：
```
sudo dpkg -i <file>.deb
sudo apt-get install -f # Install dependencies
```
### 启动 VSCode
用如下命令行启动VSCode；
```bash
code
```
### 在VSCode中启动Apollo项目
用快捷键 **(Ctrl+K Ctrl+O)** 可以打开Apollo项目。
### 在VSCode中构建Apollo项目
用快捷键 **(Ctrl+Shift+B)** 可以构建Apollo项目。 
### 在VSCode中跑所有Apollo项目的单元测试
选择菜单中"任务->运行任务…"命令并在弹出菜单中点击"运行apollo项目的所有单元测试"来检查代码格式。

如果您正在使用16.04，可能会出现构建错误。
如下图所示的两个感知测试，要想避免这种构建错误，请参考 [怎样用Ubuntu16构建Apollo](how_to_run_apollo_2.5_with_ubuntu16.md)。

![构建错误](images/build_fail.png)

### 在VSCode中跑Apollo项目的代码格式检查任务

选择菜单中"任务->运行任务…"命令并在弹出菜单中点击"检查apollo项目代码格式"来检查代码格式。

### 在VSCode中清理Apollo项目
选择菜单中"任务->运行任务…"命令并在弹出菜单中点击"清理apollo项目"来清理Apollo项目。

### 更改构建选项

 
 你可以在".vscode/tasks.json"文件中，更改"build"选项为"build_gpu"（更多细节请参考"apollo.sh"文件）。

## <span id="test">测试</span>
```bash
bash docker/scripts/release_start.sh [release tag]
```

*HMI*将自动启动，您可以在任何Web浏览器通过输入IP地址和端口号，例如 *localhost:8887* 来控制任何apollo模块。如果需要快速修复，可以进入Release容器。
```bash
bash docker/scripts/release_into.sh
```

## 法律免责声明

您所构建的Docker镜像可以包含ESD电子文件（ESD电子设备）所提供的ESD CAN库文件，您可以通过ESD许可协议获得该文件。许可协议应授予您（作为个人或企业实体）使用ESD所提供的软件的权利；然而，您可能（并且可能您需要）需要ESD明确的重新分发许可，以发布镜像供任何其他第三方消费。这样的许可协议只在你和ESD之间，并且不被Apollo计划的许可条款所涵盖（见Apollo顶级目录下的文件许可证）。 
