<font face="宋体"> 

# <center><b> Homework 03 </center></b>
<center><font face='black'> Name:Limingwei ID:3190106234 </font ></center>

## 1.

### (a)

容易分析，电子受电场力大小$$F_e=|q|E$$方向向上。
通过长度为$L$的平行板电容器所需时间$$t=\frac{L}{v}$$
在$t$时间内，电子向上移动的距离$$ \Delta y =\frac{1}{2}at^2$$
$y$方向牛顿第二定律容易得到：
$$qE = ma \Rightarrow a = \frac{|q|E}{m}$$
由此容易得到在$y$方向的偏移
$$\Delta y =\frac{|q|EL^2}{2mv}$$
### (b)
当磁感应强度为$B$时,电子所受洛伦兹力大小
$$F_B=B|q|v$$
若刚好没有偏转，则$F_B=F_e$
即有：$$B|q|v=|q|E \Rightarrow E=Bv(*)$$
由$(a)$中的结论$$\Delta y =\frac{|q|EL^2}{2mv}\Rightarrow\frac{|q|}{m}=\frac{2\Delta yv}{EL^2}$$
利用$(*)$式容易消去$v$得到：
$$\frac{|q|}{m}=\frac{2\Delta yE}{B^2L^2}$$
## 2.
### (a)
$$\vec{\tau}=i\vec{L_2}\times(\vec{L_3}\times\vec{B})=i\vec{L_3}(\vec{L_2}\cdot\vec{B})-i\vec{B}(\vec{L_2}\cdot\vec{L_3})$$
注意到$\vec{L_2} $ and $\vec{L_3}$ is perpendicular，则有$$\vec{L_2}\cdot\vec{L_3}=\vec{0}$$
$$\therefore\vec{\tau}=i\vec{L_3}(\vec{L_2}\cdot\vec{B})=i\vec{L_3}\|\vec{B}\|\|\vec{L_2}\|\cos\theta=i\|\vec{B}\|\|\vec{L_2}\|\|\vec{L_3}\|\cos\theta=i\vec{A}\times\vec{B}$$
其中$\vec{A}=ab\hat{n}$,$a,b$为矩形边框的两条边长
### (b)
事实上，对于一个任意形状的平面线圈，任取其中一小段面积为$\|\vec{dA}\|$的小矩形，它所受到的力矩$\vec{d\tau}=i\vec{dA}\times\vec{B}=i\|\vec{B}\|\sin\theta \hat{n}dA$
因而对于面积存在（为$A$）的线圈，总存在$A=\iint dxdy=\int dA$
因而$$\vec{\tau}=\int d\tau=i\|\vec{B}\|\sin\theta \hat{n}dA=i\|\vec{B}\|\sin\theta A\hat{n}=i\vec{A}\times\vec{B}$$
## 3.
从图$b$容易看出，当$x_1=4cm$时，$F_2$恰好为$0$，而
$$I_1:I_3=0.750A:0.250A=3:1$$
通过电流$I$的长直导线在其周围距离$r$处产生的磁感应强度$B$的大小：
$$B=\frac{\mu_0 I}{2\pi r}$$
所以容易知道
$$d:x_1=I_3:I_1=3:1\Rightarrow d=3x_1=x_s=12cm$$
所以在wire 2处磁感应强度
$$B_{wire2}(x)=-\frac{\mu_0 I_1}{2\pi d}+\frac{\mu_0 I_3}{2\pi x}$$
当$x\rightarrow +\infin$时$B_{wire2}\rightarrow -\frac{\mu_0 I_1}{2\pi d}=1.25\times10^{-6} T$
因而此时wire 2单位长度所受安培力
$$F_2/L=B_{wire2}I_2=-0.627 \mu N/m \Rightarrow I_2 = 0.5016A$$


## 4.
由安培环路定理知道：
$$\int_L \vec{B}\cdot\vec{dL}=\mu_0 \sum I$$
所以有
$$
B_{center}=\frac{\mu_{0} i_{{wire }}}{2 \pi(3 R)}=\frac{\mu_{0} i_{{wire }}}{6 \pi R}
$$
所以说$B_p=B_{center}$，则电流方向一定是垂直指向纸面向内的
$$
B_{P}=B_{P, { wire }}-B_{P,  { pipe }}=\frac{\mu_{0} i_{{wire }}}{2 \pi R}-\frac{\mu_{0} i}{2 \pi(2 R)}
$$

令两者大小相等方向相反，则：
### (a)
$$i_{wire}=\frac{3}{8}i=3mA$$

### (b)
由右手螺旋定则容易判断，电流方向垂直纸面向内
## 5.
通电螺线管的磁感应强度：
$$B=\mu_0 nI=\frac{\mu_0 NI}{L}$$
则$$F_B=qBv\sin\theta=\frac{qBv}{2}$$
牛二：$$\frac{Bqv}{2}=\frac{mv^2}{R}\Rightarrow R=\frac{2mv}{Bq}$$
旋转一圈的周期$$T=\frac{2\pi m}{Bq}$$
而沿着轴线方向的速度
$$v_\parallel=\frac{\sqrt 3}{2}v$$
于是
$$t=\frac{L}{\frac{\sqrt 3}{2}v}=\frac{2L}{\sqrt{3}v}$$
旋转圈数
$$N_{roll}=\frac{t}{T}=\frac{BqL}{\sqrt{3}v\pi m}$$
代入$B=\frac{\mu_0 NI}{L}$
得到$$N_{roll}=\frac{\mu_0 NI}{L}\frac{qL}{\sqrt{3}v\pi m}=\frac{\mu_0NIq}{\sqrt{3}\pi vm}=1.6\times 10^{6}$$
## 6.
磁偶极矩$$\vec{\mu}=\sum i\vec{A}$$
所以$$\mu=Ni*\pi d^2=2.36 A\cdot m^2$$
当$d \ll z$注意到电偶极矩产生的磁场$$B(z)=\frac{\mu_0}{2\pi}\frac{\mu}{(R^2+z^2)^{\frac{3}{2}}}\approx \frac{\mu_0}{2\pi}\frac{\mu}{z^3}=5.0\mu T=5.0\times 10^{-6}T$$
则

$$ z=0.46m=46cm$$
## 7.
铜的自由电子密度为$n=8.5×10^{28}m^{−3}$。铜在室温下的电阻率$\rho=1.7×10^{−8}Ω·m$。在金属的经典理论中，估计铜中电子的平均自由程$l$，以米为单位？
设mean free time为$\tau$,则每个电子的加速度$$\vec{a}=\frac{\vec{F}}{m}=-\frac{e\vec{E}}{m}$$
电子的平均漂移速度$$\vec{v_d}=\vec{a}\tau =-\frac{e\vec{E}}{m}\tau$$
注意到电流密度$$\vec{J}=-ne\vec{v_d}\Rightarrow \vec{v_d}=-\frac{J}{ne}=-\frac{e\vec{E}\tau}{m}$$
注意到$$\vec{J}=\rho \vec{E}$$
则有$$\tau=\frac{m}{ne^2\rho}$$
由热力学的知识我们知道
$$\frac{1}{2}m\bar{v}^2=\frac{3}{2}kT\Rightarrow\bar{v}=\sqrt{\frac{3kT}{m}}$$
所以平均自由程$$\lambda=\bar{v}\tau=\frac{m}{ne^2\rho}\sqrt{\frac{3kT}{m}}=3\times10^{-9}m$$其中$T$按照室温为$293K$计算
## 8.
霍尔效应达到平衡的时候满足：
$$B_zqv_y=qE_y$$
$$I=neSv_y=neL_yL_zv_y$$
$$R=\frac{\rho l}{S}=\frac{\rho L_x}{L_yL_z}$$
$$V_x=IR$$
$$E_y=\frac{\sigma_0}{\varepsilon}=\frac{\sigma_0}{\kappa\varepsilon_0}$$
则总共的载流子数目
$$N_{total}=nL_xL_yL_z$$
参与产生霍尔电场的载流子数目
$$N_{Hall}=\sigma_0 L_xL_z=\kappa\varepsilon_0E_yL_xL_z=\kappa\varepsilon_0B_z\cdot\frac{V_x}{\rho neL_x}L_xL_z=\frac{\kappa\varepsilon_0B_zV_xL_z}{\rho ne}$$
所以
$$\frac{N_{Hall}}{N_{total}}=\frac{\kappa\varepsilon_0B_zV_x}{\rho n^2eL_xL_y}$$
代入$\kappa=1$可以计算得到
$$\frac{N_{Hall}}{N_{total}}=5.52\times10^{-32}$$
代入$\kappa=12$可以计算得到
$$\frac{N_{Hall}}{N_{total}}=6.63\times10^{-31}$$
