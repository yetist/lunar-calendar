# 农历日历 [![Build Status](https://travis-ci.org/yetist/lunar-calendar.svg?branch=master)](https://travis-ci.org/yetist/lunar-calendar)

![](docs/images/lunar-calendar.png)

## 编译安装

```
meson build -Dprefix=/usr
ninja -C build
sudo ninja -C build install
```

编译依赖于 [LunarDate](https://github.com/yetist/lunar-date)， 更多编译选项见 [meson_options.txt](meson_options.txt)。

## FAQ

1. **GTK 应用如何自动显示农历?**

运行应用时，设置环境变量 `GTK3_MODULES=lunar-calendar-module`，对于 GTK2 应用来说，应该设置环境变量 `GTK_MODULES=lunar-calendar-module`。

如果希望自动对所有 GTK3 应用生效，可以将环境变量设置在 Xorg 启动时执行的脚本中。

不同发行版 Xorg 启动时的脚本路径不同，在 Archlinux 上可如下设置：

新建文件 `/etc/X11/xinit/xinitrc.d/70-lunar-calendar.sh` ，并增加可执行权限， 内容为：

```
export GTK3_MODULES=lunar-calendar-module
```

重新注销、登录系统，会发现所有使用日历的 GTK3 应用都会自动显示出农历来，如：mate-panel、gtk3-widget-factory等等。

2. **非中文环境不想显示拼音怎么办?**

在非中文环境下会显示为带声调的拼音，如果不想显示拼音，可以给应用程序设置环境 `LUNAR_CALENDAR_IGNORE_NON_CHINESE=1` 以关闭拼音显示。
