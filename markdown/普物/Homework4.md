# Homework4

Name:李明伟 ID:3190106234

## P4-1:

### a)

容易见得，N匝线圈在磁场中总的磁通量满足：
$$
\Phi(\theta) =NabB\cos (\theta )
$$
有$\theta = \omega t= 2\pi f t$
$$
\Phi(t) =NabB\cos (2\pi f t)
$$
因而由法拉第电磁感应定律得到：
$$
\mathscr{E}=-\frac{\partial \Phi}{\partial t}=2\pi f NabB\sin(2\pi f t)=\mathscr{E}_0\sin(2\pi f t)
$$
其中$\mathscr{E}_0 = 2\pi f NabB$

### b)

$$
Nab = \frac{\mathscr{E}_0}{2\pi f B}=\frac{150}{2\pi \cdot 60.0 \cdot 0.500}m^2=0.80 m^2
$$

## P4-2:

### a)

由对称性容易知道，在线圈上面部分的磁通量正反相互抵消，只有线圈下方$2a-b$长度的距离磁通量不为0
$$
\Phi(t)=\int _{b-a} ^a \frac{\mu_0}{2\pi}\frac{i(t)}{r}dr=\frac{\mu_0}{2\pi}\ln \frac{a}{b-a}i(t)=\frac{4\pi \times 10^{-7}}{2\pi}\ln 4\cdot (4.50t^2 − 10.0t) T\cdot m^2
$$
因而
$$
\mathscr{E}(t)=-\frac{\partial \Phi(t)}{\partial t}=4\ln 2 (9t-10)\times10^{-7} V
$$
代入$t= 3.0s$容易得到
$$
\mathscr{E}(3.0)=4.7\times10^{-6}V
$$

### b)

根据右手螺旋定则不难判断$t=3.0s$时刻磁通量的方向垂直纸面向里且在增大，因而产生的感应电动势的方向应该为逆时针方向。

## P4-3

### a)

$$
S=L(s_0+vt)
$$

$$
\Phi(t) =\int _a ^{a+L} \frac{\mu_0}{2\pi} \frac{I}{r}\cdot L(s_0+vt)dr= \frac{\mu_0IL}{2\pi}\ln\frac{a+L}{a}(s_0+vt)
$$


$$
\mathscr{E}=-\frac{\partial \Phi(t)}{\partial t}=\frac{\mu_0IL}{2\pi}\ln\frac{a+L}{a}v=
$$

### b)

$$
i=\mathscr{E}/R=\frac{\mu_0IL}{2\pi R}\ln\frac{a+L}{a}v = 
$$

方向沿顺时针方向

### c)

$$
P_{thermal} = i^2R=
$$

### d)

$$
F=\int _a ^{a+L} \frac{\mu_0}{2\pi} \frac{I}{r} \cdot i \cdot dr = \frac{\mu_0 Ii}{2\pi} \ln \frac{a+L}{a}
$$

### e)

$$
P = Fv = \frac{\mu_0 Ii}{2\pi} \ln \frac{a+L}{a}v
$$

## P4-4



















## P4-5

### a)

由安培环路定理知道：
$$
\mathscr{E}=iR+L\frac{di}{dt} \Rightarrow  \frac{\mathscr{E}-iR}{L} dt = di
$$

$$
\Rightarrow \frac{L}{\mathscr{E}-iR}di = dt \Rightarrow \frac{L/R}{\mathscr{E}/R-i} di =dt
$$

因而有
$$
t =\frac{L}{R}\ln \frac{\mathscr{E}/R}{\mathscr{E}/R-i}
$$

$$
\frac{\mathscr{E}/R}{\mathscr{E}/R-i}=e^{\frac{R}L t} \Rightarrow i = \frac{\mathscr{E}}{R} (1-e^{-\frac{R}{L}t})
$$
所以由电池传送的能量
$$
E_{battery} = q\mathscr{E} =\mathscr{E}\int _0 ^t \frac{\mathscr{E}}{R} (1-e^{-\frac{R}{L}t}) dt =
$$

### b)

$$
E_{L} = \frac{1}{2} L i^2 = 
$$

### c)

$$
Q = \int _0 ^t i^2_{(t)}r dt =
$$

其实上面的能量也可以由能量守恒式得到

