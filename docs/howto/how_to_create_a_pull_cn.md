# 怎样提交pull request

您可以按照 [github解决方法](https://help.github.com/articles/using-pull-requests/)将代码提交到Apollo. 设置示例如下:

- 在您的用户名下fork一个新的代码库
- Set up your GitHub personal email and user name设置您的GitHub个人邮箱和用户名

```
git config user.name "XXX"
git config user.email "XXX@[XXX.com]"
```

- 克隆您的fork （请将"USERNAME"替换为您的GitHub用户名)

```
(用SSH) git clone git@github.com:USERNAME/apollo.git
(用HTTPS) git clone https://github.com/USERNAME/apollo.git
```

- 添加 Apollo 代码库作为upstream

```
(用SSH) git remote add upstream git@github.com:ApolloAuto/apollo.git
(用HTTPS) git remote add upstream https://github.com/ApolloAuto/apollo.git
```

- 确认upstream分之已经添加
```
git remote -v
```

- 创建一个新的分支，进行更改和提交

```
git checkout -b  "my_dev"
```

- 与Apolloauto/apollo同步

```
git pull --rebase  upstream master
```

- 上传本地开发内容到您fork的代码库中

```
git push -f -u origin "my_dev"
```

- 在"Apolloauto/apollo:master" 和 "forked repo:my_dev"中生成一个新的pull request
- 合作者将审查和合并提交（这可能需要一些时间，请耐心等待）。

非常感谢您的贡献！
