## 截图

`Ctrl+j/k` 在匹配候选列表中进行选择。按下`Enter`之后在浏览器中打开对应命令的链接，并复制命令名字到剪切板。

![screenshot](https://i.imgur.com/SWBUmkt.png)

#### 配置

![config](https://i.imgur.com/tMkhTA4.png)

## 准备

下载`linux-command`的配置文件到主目录，[提升命令查询速度](https://github.com/jaywcjlove/linux-command/issues/73)。

```
wget https://raw.githubusercontent.com/jaywcjlove/linux-command/master/dist/data.json ~/.data.json
```

## 安装

```
git clone https://github.com/roachsinai/krunner-linuxcommands.git && cd krunner-linuxcommands
mkdir build && cd build
cmake .. -DCMAKE_INSTALL_PREFIX=`kf5-config --prefix` -DQT_PLUGIN_INSTALL_DIR=`kf5-config --qt-plugins`
make 
sudo make install
kquitapp5 krunner
krunner
```

#### 脚本

也可以运行下面的脚本进行安装与卸载。

+ [安装](./install.sh)（前提条件：1. 下载好配置文件；2. repo clone finished.）
+ [卸载](./uninstall.sh)

## ToDo

+ [x] 添加配置制定`linux-command`的配置文件存放位置
