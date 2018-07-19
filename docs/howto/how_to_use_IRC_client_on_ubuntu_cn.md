# 如何在Ubuntu上使用IRC客户端 

## 简介

网络中继聊天（IRC）是一种实时网络聊天的形式。. 它主要用于在称为频道的论坛中进行群组（多对多）通信，但也允许通过私人消息进行一对一通信。[[参考资料1](https://help.ubuntu.com/community/InternetRelayChat)]

有很多IRC用户, 如 [Quassel](https://quassel-irc.org/), [Hexchat](https://hexchat.github.io/), XChat, Konversation(KDE), 和基于控制台的irssi, WeeChat等.

在本文中，我们用 **Hexchat**作为示例来展示。
Hexchat是免费开源的, 可以在 Linux, Mac OS X 和 Windows平台上使用。

## 安装

安装 hexchat 很简单, 只要打开终端并运行如下命令:
```
sudo apt-get install hexchat
```
(在Ubuntu 14.04上进行测试，但16.04没有太大的区别。)

安装好了以后，从Unity Dash或应用菜单中启动HexChat。

![img](images/irc_image_01.png)

## 怎样用Hexchat

在第一次启动时，您将被要求选择昵称和网络服务器。IRC网络是一个相互连接的IRC服务器网络。[Freenode](https://freenode.net) 是目前最大的IRC网络，也是当前大多数开源项目用到的IRC。[[参考资料 2](https://www.linuxbabe.com/ubuntu/install-use-hexchat-ubuntu-16-04)]

输入您最喜欢的昵称（可以通过命令 `nick`更改，稍后您会看到），并从服务器列表中选择freenode IRC服务器。

然后按下`Connect` 按钮。

![img](images/irc_image_02.png)

注意，如果freenode不在列表中, 只需单击 `添加` 按钮添加一个服务器(这里我们可以使用 "Freenode"作为服务器名),然后单击 `编辑`按钮来添加服务器地址和端口`chat.freenode.net/+6697`, 其中`+` 表示SSL。端口是完全可选的，如果没有端口，则使用的默认端口为SSL的6667和6697。[[参考资料 3](https://hexchat.readthedocs.io/en/latest/settings.html#servers)] 关闭 `编辑对话`并返回`服务器列表`

![img](images/irc_image_03.png)
连接选定的IRC服务器需要几秒钟的时间。

一旦连接，你可以选择加入一个频道，或者稍后再通过`join`命令加入。

![img](images/irc_image_04.png)

点击`Ok` 按钮, 就可以加入 #apolloauto频道了。

![img](images/irc_image_05.png)

现在就可以和频道里的成员们交流了 :)

## 最常用的命令
要加入一个通道，只需键入连接命令（IRC命令加上前缀 `/`) 用通道名（IRC信道名加上前缀 `#`)
```
/join #channel_name
```
To change a new nickname,
```
/nick new_nickname
```
To see all commands,
```
/help
```
To start one-to-one private chat,
```
/query the_nickname_talking_to
```

There are a `NickServ` and a `ChanServ` that you can register you nickname or maitain control of a channel.
To see what you can do,
```
/msg NickServ help
```
and
```
/msg ChanServ help
```

## Further reading
[Basic IRC Commands](http://www.ircbeginner.com/ircinfo/ircc-commands.html)

[Tips and Tricks](http://www.ircbeginner.com/ircinfo/ircc-tips.html)
