# 说明

通过使用 Gtk Module, 可以让系统中使用显示日历的地方，自动带农历显示。

## 编译

使用 `meson configure -Denable_gtk_modules=true`，来编译出 gtk3 的module.

## 使用

通过环境变量运行：

```
GTK3_MODULES=lunar-calendar-module gtk3-widget-factory
```

让系统全局生效：

编写文件  `/etc/profile.d/lunar-calendar.sh`, 内容为：

```
export GTK3_MODULES=lunar-calendar-module
```

注销，重新登录。

