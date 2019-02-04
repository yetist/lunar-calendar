# 农历日历 [![Build Status](https://travis-ci.org/yetist/lunar-calendar.svg?branch=master)](https://travis-ci.org/yetist/lunar-calendar)

![](docs/images/lunar-calendar.png)

# 编译安装

```
meson build -Dprefix=/usr
ninja -C build
sudo ninja -C build install
```

编译依赖于 [LunarDate](https://github.com/yetist/lunar-date)， 更多编译选项见 [meson_options.txt](meson_options.txt)。

# 自动显示农历

编译时启用gtk模块：

```
meson build -Dprefix=/usr -Denable_gtk_modules=true
ninja -C build
sudo ninja -C build install
```

在 /etc/X11/xinit/xinitrc.d/ 新建文件 70-lunar-calendar.sh，并增加可执行权限， 内容为：

```
export GTK3_MODULES=lunar-calendar-module
```

重新注销、登录系统，会发现所有使用日历的gtk3应用都会自动显示出农历来，如：mate-panel、gtk3-widget-factory等。

Gtk2 应用理论上也是行的，前提是要把 lunar-calendar 编译为 gtk2 的，环境变量名使用 `GTK_MODULES`。
