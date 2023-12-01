### Lab1.准备实验环境
在`VMware`中安装`ubuntu22`版本，之后使用`apt install`命令安装`git`,`vim`等基本工具，在用户家目录执行如下命令，即可完成初始化：
```
git clone https://github.com/DeathKing/hit-oslab.git ~/hit-oslab
cd ~/hit-oslab
./setup.sh
```

---

考虑到操作系统试验每次需要重置`linux-0.11`目录，`oslab`特别添加了重置功能，注意需要在`oslab`文件夹中。

> ./run init

执行完如上步骤后就可以正式开始实验了。

---

Step1. 进入`oslab/linux0.11/`文件夹下，使用`make all`指令编译`linux0.11`操作系统，此时会生成一个`Image`文件

Step2. 进入到`oslab`文件夹下，执行`run`脚本即可启动`Bochs`

Step3. 为了在宿主机中对`Linux0.11`中的文件进行操作，可以使用`sudo ./mount-hdc`来挂在`hdc`，然后就可以在宿主机中1`hdc`文件夹中对`Linux0.11`中的文件进行操作。<font color="red" weight="500px">*注意*：</font>操作之后需要使用`sudo umount hdc`来解除挂载，避免启动`Bonus`时出现文件系统问题。

> `Bochs`是一个模拟器，可以模拟出硬件来供实验中过的`linux0.11`操作系统使用。