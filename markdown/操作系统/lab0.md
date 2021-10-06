# lab0 GDB + QEMU 调试 64 位 RISC-V LINUX 实验报告

Name: 李明伟 ID:3190106234

[TOC]



## 1. 搭建基础实验环境

由于本实验最好在Linux系统下进行，因而选择利用VMware Workstation 16.1.2来进行虚拟机的搭建。

* 实验环境：Windows 10 20H2
* 处理器：Intel(R) Core(TM) i7-10510U CPU @ 1.80GHz   2.30 GHz （**x86架构**）
* 所用软件：Vmware Workstation 16.1.2 for Windows 64-bit
* 虚拟机版本：Ubuntu-18.04.5-desktop-amd64.iso

### 1.1 下载并安装 VMWare Workstation 16.1.2

![image-20210915161635777](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210915161635777.png)

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210915161839488.png" alt="image-20210915161839488" style="zoom:50%;" />

### 1.2 下载Ubuntu镜像

这里选择官网的 `Ubuntu-18.04.5-desktop-amd64.iso` 版本进行下载

![image-20210915162739311](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210915162739311.png)

### 1.3 安装Ubuntu虚拟机

* 打开VMware Workstation 16 Player，创建新虚拟机。

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210915163328184.png" alt="image-20210915163328184" style="zoom:50%;" />

* 将先前下载好的Ubuntu-18.04.5-desktop-amd64.iso镜像搭载在虚拟机中

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210915163416931.png" alt="image-20210915163416931" style="zoom:50%;" />



* 为虚拟机分配合适的硬盘容量，为配合课程要求，这里分配35.0GB的磁盘空间以及4.0GB的内存

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210915163721901.png" alt="image-20210915163721901" style="zoom:50%;" />

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210915163752803.png" alt="image-20210915163752803" style="zoom:50%;" />

* Ubuntu 成功运行

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210915163924658.png" alt="image-20210915163924658" style="zoom:50%;" />

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210915164015060.png" alt="image-20210915164015060" style="zoom:50%;" />

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210915170341416.png" alt="image-20210915170341416" style="zoom:50%;" />





### 1.4 搭建docker环境

​	按照课程实验指导以及网络上的一些教程来对docker环境进行搭建。

​	首先对`apt-get`进行更新，在终端利用管理员权限运行来防止运行失败，接着安装必要的文件

```shell
$ sudo apt-get update
$ sudo apt-get install \
apt-transport-https \
curl \
gnupg \
lsb-release
```

![image-20210916191507142](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210916191507142.png)

这里发现提示 `could not get lock xxx open, unable to acquire the dpkg frontend lock`，是系统提示权限不足，因而用下面的两条语句来更改权限设置（实际上是删除了`lock`），删除后则安装成功。

```shell
$ sudo rm /var/lib/dpkg/lock-frontend
$ sudo rm /var/lib/dpkg/lock
```

![image-20210916191529824](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210916191529824.png)

![image-20210916192213970](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210916192213970.png)

最后输入下面的命令来安装docker：

```shell
$ sudo snap install docker
```

![image-20210918142117456](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918142117456.png)



### 1.5 下载并导入实验所需docker环境oslab.tar

* 从浙大云盘下载oslab.tar文件到虚拟机。

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918150908899.png" alt="image-20210918150908899" style="zoom:50%;" />

* 试图将oslab.tar导入docker

  导入过程中即使使用了`sudo`仍存在`Got permission denied`的情况，证明所需权限不足，进行授权操作。其中进行了以下几种尝试。

  ```shell
  $ sudo gpasswd -a $USER docker ### 试图将本用户（limingwei）加入到group docker之中，但似乎效果仍不佳
  $ sudo chmod 777 oslab.tar ### 试图用chmod来对oslab.tar进行权限授予，但仍然失败
  $ sudo chmod a+rw /var/run/docker.sock ### 修改docker.sock的权限为a+rw后成功
  ### 将oslab添加到docker镜像
  $ sudo cat oslab.tar | docker import - oslab:2021
  ```

![image-20210918151351389](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918151351389.png)

![image-20210918151949504](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918151949504.png)

![image-20210918152240870](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918152240870.png)

```shell
$ docker images ### 导入docker镜像后查看是否导入成功
```

![image-20210918152314171](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918152314171.png)



### 1.6 在docker中创建容器

#### 1.6.1 下载git，并将实验需要用到的容器环境下载到虚拟机

```shell
$ sudo apt install git
$ git clone https://gitee.com/zjusec/os21fall
```

![image-20210918152633846](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918152633846.png)

![image-20210918153006327](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918153006327.png)

可以使用`ls`指令看到后面需要使用的`rootfs.img`文件在`/os21fall/src/lab0`目录下

![image-20210918153203408](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918153203408.png)



#### 1.6.2 下载Linux源码

由于我们接下来需要在容器中对Linux进行编译，所以这里先在网站https://www.kenel.org/pub/上下载最新版本的Linux源码，这里选择的是5.14.5版本的Linux

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918153325705.png" alt="image-20210918153325705" style="zoom:50%;" />

解压下载好的linux源码，这里解压到的目录是`/Downloads/linux-5.14.5`

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918161010368.png" alt="image-20210918161010368" style="zoom:50%;" />

#### 1.6.3 从镜像中创建一个新容器

```shell
$ docker run --name oslab -it oslab:2021 bash ### -it 指用交互式操作，在终端进行，最后在bash中进行交互
```

![image-20210918160031121](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918160031121.png)

* 开启容器，以及一些docker的基本操作

  ```shell
  $ docker start oslab	### 开启oslab容器
  $ docker ps				### 查看docker目前各容器的状态，可以看到oslab容器成功开启了
  $ docker exec -it oslab bash ### 以终端的方式执行容器
  ### 容器中进行的语句用'#'开头以作区分，注释采用仍'###'作为标识
  # exit 					### 在容器中输入exit来退出
  ```

  

![image-20210918160046105](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918160046105.png)

![image-20210918160140055](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918160140055.png)

#### 1.6.4 将Linux源码拷贝到docker容器中

​	**注意**：这里本人犯了一个错误，即先前忘记将Linux源码copy到容器中再进行编译，因而在编译的过程中会提示缺乏许多环境，无法顺利进行。而本实验提供的`os21fall`文件夹中实际上已经包含了编译Linux源码需要的所有环境，因而，要将Linux源码先挪动到docker容器中才能顺利进行编译。

```shell
$ docker cp ~/Downloads/linux-5.14.5 oslab:/root/linux ### 这里的cp命令将前面目录中下载好的Linux源码copy到了名为oslab的容器中/root/linux文件夹内
### 注：上面的步骤其实也可以不必在docker外部重复进行，可以直接在先前创好的容器中下载Linux的源代码
```

![image-20210918163436113](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918163436113.png)

### 1.7 编译Linux内核

​	在进行了1.6.1~1.6.4的步骤之后，我们已经准备好了docker容器:`oslab`，以及编译Linux内核需要的环境(`os21fall`)，并将Linux源码拷贝到容器中，接下来我们只需要使用make命令对Linux内核进行编译即可。

```shell
# cd /root/linux     ### 进入容器中先前拷贝好的linux内核的文件夹所在位置
# make ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-gnu- defconfig  ### 这里选择生成riscv架构的配置文件
# make ARCH=riscv CROSS_COMPILE=riscv64-unknown-linux-gnu- -j$(nproc) ### 使用-j选项进行编译
```

![image-20210918164401817](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918164401817.png)

​	在经过较长的一段时间等待后，编译成功完成：

![image-20210918170600926](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210918170600926.png)

## 2. 利用QEMU+GDB对Linux内核进行调试

### 2.1 使用QEMU运行内核

由于这里采用的是riscv架构对Linux内核进行编译，而本机为x86架构，因而需在docker容器中使用QEMU来对riscv64位的系统进行模拟才可以正常运行，在docker中输入以下命令来调用qemu

```shell
# qemu-system-riscv64 -nographic -machine virt -kernel /root/linux/arch/riscv/boot/Image -device virtio-blk-device,drive=hd0 -append "root=/dev/vda ro console=ttyS0" -bios default -drive file=linux/os21fall/src/lab0/rootfs.img,format=raw,id=hd0
### -nographic : 非图形化界面
### -kernel : 代表指定内核Image
### -device : 制定要模拟的设备
### /root/linux/arch/riscv/boot/Image 为Image镜像的地址
### file=linux/os21fall/src/lab0/rootfs.img 为rootfs.img的地址，使用file作为文件地址
### -bios default: 使用默认的OpenSBI firmware作为bootloader
```

可以发现借助qemu,OpenSBI成功运行了

![image-20210919235026432](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210919235026432.png)



### 2.2 打开GDB调试

打开一个新的终端，在docker中输入下面的代码进入GNU调试模式。

```shell
# riscv64-unknown-linux-gnu-gdb root/linux/vmlinux
```

<img src="C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210920000002080.png" alt="image-20210920000002080" style="zoom:67%;" />

注意到，由于先前使用QEMU时缺少参数，其不会在运行开始时自动暂停，因而这里需要在先前终端中对qemu的运行语句末端加入`-S`以确保启动时CPU自动暂停。同时，为GDB调试提供方便，需添加`-s`来将默认的1234端口作为调试端口(`-s`为`-gdb tcp::1234`的缩写)。

```shell
# qemu-system-riscv64 -nographic -machine virt -kernel /root/linux/arch/riscv/boot/Image -device virtio-blk-device,drive=hd0 -append "root=/dev/vda ro console=ttyS0" -bios default -drive file=linux/os21fall/src/lab0/rootfs.img,format=raw,id=hd0 -S -s
```

此时在GDB运行的终端中即可进行调试

### 2.3 调试细节

首先需要在GDB中连接先前设置的端口1234

```shell
(gdb) target remote localhost:1234 ### 此处的localhost也可以省略不写，如下
(gdb) target remote :1234
```

#### 2.3.1 backtrace

`backtrace`能够显示当前的函数运行栈，这里贴出几个使用的例子。

![image-20210929192105775](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929192105775.png)

注意到，这里使用backtrace的时候，由于断点设置在0x80000000以及0x80200000处，这里GDB并不能很好的定位出运行到哪条函数了，所以只现实了一层堆栈，且应表达的函数处显示了`??`字符

![image-20210929192251909](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929192251909.png)

当我们将程序运行断点位置设在start_kernel时，便可以显示出如上图的调用关系

#### 2.3.2 layout

`layout`功能可以分割窗口，将显示区分为两个部分，可以加不同的参数来得到不同的效果：

```shell
(gdb) layout src		### 显示源代码
(gdb) layout asm		### 显示反汇编码
(gdb) layout regs		### 显示CPU寄存器
(gdb) layout split		### 显示源代码+反汇编
### ctrl+x 然后按a可以退出layout调试模式
```

下图是`layout asm`条件下的显示结果。

![image-20210929192517817](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929192517817.png)

#### 2.3.3 finish

`finish`命令的功能是运行程序直到当前函数完成返回，并在返回后打印函数返回时的堆栈地址和返回值及参数值等信息。如运行下面该行命令，则会使得start_kernel函数返回，即整个程序结束(exit)。

```shell
(gdb) finish
```

![image-20210929193505198](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929193505198.png)

#### 2.3.4 info

`info` 功能能够查看程序运行中的各种信息，info在调试的各种时刻均可使用，是非常有用的查询函数，通常与其它功能配合使用，这里便不再单独为其贴图，下面列出集中常用的`info`语句用法。

```shell
(gdb) info program 			### 输出当前程序运行的状态（正在运行/暂停/停止）
(gdb) info breakpoints 		### 查看所有断点信息
(gdb) info regs				### 查看运行当前时寄存器信息
(gdb) info locals			### 显示当前堆栈页的所有变量
(gdb) info function			### 显示当前运行程序的所有函数及其地址
(gdb) info frame 			### 展示当前栈帧中储存的信息
```

#### 2.3.5 frame 

`frame`命令能够切换函数的栈帧，简写为`f`，通常与`up` ,`down` 以及`backtrace`，`info frame`配合使用。在任何一个函数被调用执行时，都会生成一个存储必要信息的栈帧，frame命令则能允许我们在递归函数的不同递归层级之间寻找栈帧的信息及变化。在调试具有循环调用或递归调用时的程序时，通过这个命令可以让我们更容易定位异常发生的位置。

```shell
(gdb) frame spec ### 将spec参数指定为当前的栈帧
(gdb) up n		 ### 将x+n栈帧作为新的当前栈帧。
(gdb) down n	 ### 将x-n栈帧作为新的当前栈帧。
(gdb) info frame ### 打印当前栈帧的编号、地址、对应函数的储存地址、该函数被调用时代码的储存地址等等
```

![image-20210929195645268](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929195645268.png)

#### 2.3.6 break

`break`命令（简写为`b`）能帮助我们设置断点，程序运行在断点处即自动暂停。该功能最为常用且使用较为简单，这里不做过多解释。

```shell
(gdb) b function_name ### 在function_name处设置断点
(gdb) b *0x80000000   ### 在程序运行至内存0x80000000处设置断点
(gdb) break test.c:10 ### 在test.c的第十行设置断点
(gdb) info b			### 查看当前所有断点的信息
```

#### 2.3.7 display

`display`命令（简写为`d`），它能够在设置一个表达式的值后，每次单步运行输出该表达式的值，起到实时监控的效果。在使用时可以采用如下的方式：

```shell
(gdb) display variable_a ### 设置显示变量a的内容
(gdb) next				 ### 在执行next后变量a的内容将被打印
```

![image-20210929204425917](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929204425917.png)

如上图中的`3+5`可替换为任意其它在该语言下能够运行的表达式，如在C语言中可以写入一个C表达式，而在Python调试中可以写入一个Python表达式。

#### 2.3.8 next & step

`next` 和 `step`指令可以用于单步调试，主要使用的有以下四种形式，可根据情况要求的不同来灵活使用。

```shell
(gdb) nexti 	### 单步运行下一条指令，不进入函数
(gdb) stepi 	### 单步运行一条指令
(gdb) next		### 单步进行到源代码的下一行，不进入函数
(gdb) step 		### 单步到下一个不同的源代码行（包括进入函数）。
```



## 3. 总结与感想

### 3.1 思考题

#### 3.1.1 使用 `riscv64-unknown-elf-gcc` 编译单个 `.c` 文件

在terminal 输入 `vim test.c` ，输入i进入插入模式，然后编写一个简单的c语言程序输出"hello world"

```shell
$ vim test.c
```

```C
#include<stdio.h>
#include<stdlib.h>
int main(){
printf("hello,world");
exit(0);
}
```

按下esc后输入`:wq`，保存并退出vim

然后在控制台中输入`riscv64-unknown-elf-gcc test.c -o test`进行编译，输入`ls`可以看到编译成功的test可执行文件

```shell
$ riscv64-unknown-elf-gcc test.c -o test
$ ls
```

![image-20210927202214862](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210927202214862.png)

#### 3.1.2使用 `riscv64-unknown-elf-objdump` 反汇编 1 中得到的编译产物

完成1后，输入`riscv64-unknown-elf-objdump -d test` 对test进行反汇编，可以得到反汇编的结果：

![image-20210927202424042](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210927202424042.png)

#### 3.1.3 调试 Linux 时:

1. 在 GDB 中查看汇编代码

   首先使用`info func`来查看编译过程中所有的函数，然后随便选取其中的一个函数进行反汇编，这里选择_start

   ![image-20210929171958506](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929171958506.png)

   ```shell
   (gdb) disass _start 
   ```

   结果发现系统提示`Cannot access memory`

   ![image-20210929172604556](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929172604556.png)

   这里证明在进行gdb调试的过程中，内存的访问并不是完全自由的，`_start`所处的内存此时无法访问，不过我们可以去访问指定内存范围的汇编码，如下面这行代码就可以访问0x80000000~0x800000ff处的汇编码：

   ```shell
   (gdb) disass 0x80000000,0x800000ff
   ```

   ![image-20210929172520704](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929172520704.png)

2. 在 0x80000000 处下断点

   

   ```shell
   (gdb) b *0x80000000
   ```

   

3. 查看所有已下的断点

   

   ```shell
   (gdb) info breakpoints
   ```

   

4. 在 0x80200000 处下断点

   

   ```shell
   (gdb) b* 0x80200000
   ```

   

5. 清除 0x80000000 处的断点

   

   ```shell
   (gdb) del 1	### 此时0x80000000处的断点为第一个断点，所以清除时直接输入del 1即可
   ```

   

6. 继续运行直到触发 0x80200000 处的断点

   

   ```shell
   (gdb) continue
   ```

   

7. 单步调试一次

   ```shell
   (gdb) nexti 	### 单步运行下一条指令，不进入函数
   (gdb) stepi 	### 单步运行一条指令
   (gdb) next		### 单步进行到源代码的下一行，不进入函数
   (gdb) step 		### 单步到下一个不同的源代码行（包括进入函数）。
   ```

   

8. 退出 QEMU

   ![image-20210929171706866](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929171706866.png)

   ![image-20210929171802121](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929171802121.png)

   在QEMU中按`ctrl+A`然后按`x`即可退出QEMU

#### 3.1.4 使用 `make` 工具清除 Linux 的构建产物

可以用以下的两条指令来清除，注意到，`make mrproper`的程度更深，其首先会调用`make clean`，这里选择`make clean`来进行执行即可。

```shell
$ make clean	                ### 使用make clean可以清除所有编译好的obj文件
$ make mrproper	                ### 删除所有的编译生成文件、内核配置文件(.config文件)和各种备份文件
```

![image-20210929204954210](C:\Users\LiMingwei\AppData\Roaming\Typora\typora-user-images\image-20210929204954210.png)

#### 3.1.5 `vmlinux` 和 `Image` 的关系和区别是什么？

objcopy用于将object的部分或全部内容拷贝到另一个object，从而可以实现格式的变换。Image是经过objcopy后处理的，只包含内核代码和数据的文件，Image是一个二进制格式的文件而不是.elf格式文件，没有经过压缩。而vmlinux是由经过压缩的Image和加入解压头文件组成的ELF格式文件。因而，在使用QEMU运行的是Image而用GDB运行的是vmlinux。

### 3.2 一些心得体会

Linux作为一个之前未曾接触过的操作系统，我在学习Linux的终端、命令行操作的过程中花费了一些时间和精力，而对于这次的实验来说，重要的前提是理解虚拟机、Ubuntu系统、docker、GDB、QEMU以及所需编译的Linux内核之间的关系和结构。在了解清楚这些工具之间的关系之后，利用GDB强大的功能进行调试、测试的过程，其实是较为轻松的一个过程。除了完成实验本身的探索之外，我还学习了Linux系统一些其它软件、工具的使用方法，我相信这能给我今后更好的了解Linux操作系统，更方便的完成实验提供一个较好的基础。我在这次实验中的收获颇深。
