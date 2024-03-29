# 进制之间转换

不用多说

# 数据的表达形式

## 原码

最高位表示符号，剩余位表示绝对值

假设字长为n+1位，则可以表示$-2^n+1\le x\le2^n-1（整数）,-(1-2^{-n})\le x\le(1-2^{-n}) (小数)$

注意，原码0有两个表达形式，即100000...和000000...

原码表示简单直观，但是加减运算比较复杂，且零有两种形式

## 反码

反码是将原码每位取反得到的，通常是作为原码和补码转换的中间表示

## 补码

正数的补码等于原码，负数的补码等于反码末位加1

原码:1,101100<span style="border-bottom:1px solid green;">1</span>

反码:1,<span style="border-bottom:1px solid red;">010011</span>0

补码:1,<span style="border-bottom:1px solid red;">010111</span><span style="border-bottom:1px solid green;">1</span>

可以看出，负数补码从最右边的1记起，左边的部分和反码一致，右边的部分和原码一致，即**高位和反码一致，低位和原码一致**这个特性在移位运算中特别有用

补码相对于原码而言，1,00000表示最小的负数$-2^5$,补码的表示范围为$-2^{n}\le x\le2^{n}-1或-1\le x\le1-2^{-n}$由此可知为什么c语言中int的负数最小值的绝对值比正数最大值多1

$[x]_{补}\rightarrow [-x]_{补}$:符号为和数值位全部取反末位加1

对于负数而言，数值部分绝对值越大，绝对值越小，真值越大

如：1,0111011和1,1111001,前者转化为真值-69，后者转化为真值为-7

## 移码

移码用于浮点数阶码，只能表示整数。移码是在真值的基础上加上一个偏移量得到的。移码保持了数据原有的大小顺序

移码等于补码符号为取反

移码具体放在浮点数中具体叙述

## 编码之间转换

编码(n+1位)|最小值|最大值|零
:-:|:-:|:-:|:-:
原码带符号|1,1111...=$-(2^{n}-1)$|0,1111....=$2^n-1$|1,0000....;0,0000....
补码带符号|1,0000...=$-2^{n}$|0,1111....=$2^n-1$|0,0000....

# 移位运算

移位运算总结如下表

-|编码|添比特
:-:|:-:|:-:
正数|补，原，反|0
负数|原|0
负数|反|1
负数|补|左移添0,右移添1(由于补码高位和反码一致，低位和原码一致)

## 循环移位

循环移位的特点是移出的数位又被移入数据中，循环移位也分为带进位和不带进位

![cycle-shift](picture/cycle-shift.png)

循环移位适合将高位数据和低位数据互换

# 加法

> 加法是计算机中四则运算的基础，所有四则运算都转化为加减运算和移位运算的组合
## 运算器

这部分内容是有关CPU的运算器的，涉及较多底层硬件内容，暂且不关注

![PSWR](picture/PSWR.png)

我们主要关注加法运算电路所产生的四个程序状态字标识符:

- ZF,零标识符，顾名思义，结果为0则ZF=1
- OF,overflow flag,溢出标识符，表示**带符号**整数运算出现溢出，对无符号数没有意义
- SF,sign flag，符号标识符，即F的最高位，对无符号数没有意义
- CF,carrying flag，进位标识符，表示无符号数运算时产生的进位/错位，判断是否溢出。对符号数没有意义

## 运算方法

通常进行补码加减法：$[x+y]=[x]+[y],[x-y]=[x]+[-y],[x]代表x的补码$

- 符号位参与运算
- 最高位丢弃，保留n+1位
- 运算结果为补码

如：$x=15,y=24$,求$[x+y]_{补},[x-y]_{补}$

$
[x]_{补}=00001111，[y]_补=00011000,[-y]_补=11101000\\\
[x+y]_补=00100111,[x-y]_补=[x]_补+[-y]_补=11110111
$
## 溢出判断

只有带符号数进行运算时才会出现溢出，且出现溢出的情况一定是**正+正=负->上溢或负-正=负+负=正->下溢**

判断运算溢出最基本的方法是人工带入真值进行运算，若超出补码范围则必然发生溢出

而计算机由三种方法可以检验溢出

- 单符号位：由于溢出的两种情况**正+正=负->上溢或负-正=负+负=正->下溢**，可知溢出发生时运算结果的符号位和两个运算数的符号位相反，得到判别逻辑式$(A_sB_s\oplus S),A_s,B_s$为运算数A，B的符号，S为运算结果的符号
- 双符号位(变形补码)：首先说明的是，变形补码只存储一个符号位，当要用到第二个符号位时便复制一份符号位。一般的变形补码两个符号位相同，当出现溢出时，就会有两个符号位不同的情况：
  1. 两个正数运算时发生正溢出，必然是<u>00,1....+00,1....</u>的情况，在这个情况下便会得到结果为01,.....的数，故发生正溢出的符号位$S_1S_2=01$,
  2. 两个负数运算时发生正溢出，必然是<u>11,1/0....+11,0...</u>的情况，在这个情况下便会得到结果为10,.....的数，故发生负溢出的符号位$S_1S_2=10$,
  3. 高位符号表示运算结果真实的符号，低位符号表示运算结果实际的符号，两个符号位不同则发生溢出
- 采用一位符号的进位$C_s$和最高数据位$C_1$的进位判断：其实是前两种方法的结合

# 乘除运算

> 乘法运算由累加和右移组成,除法运算由累加和左移组成，这一块内容要多感受例题

## 原码一位乘

算法思想:

- 符号位单独运算
- 部分积是乘法运算的中间结果，每次$x\times y_i$的值与前面结果累加就是部分积
- 从乘数的最低位开始判断，若$y_i=0$，则部分积乘0右移一位，若$y_i=1$,则部分积$+|x|$然后右移一位(移位是逻辑移位)
- 共进行n次循环，用双符号位进行运算
  
![times1](picture/times_1.png)

## 补码一位乘（booth算法）

乘数末尾添加一个附加位，由附加位和低位的取值决定运算

- 符号位参与运算
- 采用双符号位
- 乘数末尾添加附加位$y_{n+1}$初值为0
- 根据($y_n,y_{n+1}$)取值来判断操作：
  1. 若$y_n=y_{n+1}$只进行右移位
  2. 若$y_n-y_{n+1}>0$部分积$+[-x]_{补}$,右移
  3. 若$y_n-y_{n+1}<0$部分积$+[x]_{补}$，右移
  4. 移位按补码移位规则进行
- 进行n+1步运算，但n+1步时不进行移位,只根据$(y_n,y_{n+1})$决定运算

![booth](picture/booth.png)

## 加减交替法

- 符号位单独运算
- 先用被除数减去除数$x-y=[x]+[-y]$
  1. 余数大于0,商1，商和余数左移，减除数
  2. 余数小于0,商0，商和余数左移，加除数
- 第n+1步余数为负，加上除数得到正确的余数

![div](picture/add-sub-div.png)

# 强制类型转换

## 符号拓展

符号拓展是两个不同位的定点带符号数相加时进行的，比如8bit数和32bit数相加时候要将8bit数拓展为32bit数

正数符号拓展高位添0

负数原码符号拓展高位添1，补码添1（整数部分）或0（小数）

## 浮点数强制类型转换

- int->float,不会导致溢出，但是会导致舍入：
  若int型的高位（24~31位）不全为0，由于float类型的尾数部分只有24位,进行转化时高位会丢弃，导致舍入
- int/float->double，由于double精度高，故可以精确转换
- double->float:大数转化时会导致溢出，float尾数位数少，会发生舍入
- float/double->int:数据会只保留证书，发生舍入。int表示范围较小，大数转化会溢出

# 浮点数

## 浮点数表示

### 组成

由科学计数法可以引申出浮点数的机器表示。如$2\times 10^8$等

浮点数可以表示成$N =(-1)^S\times M \times r^E$，其中S为数符，M为尾数，r为底数，在计算机中r一般为2或2的整数倍，E为阶码

尾数影响精度，阶码影响范围

### 尾数规格化

规格化：调整尾数和阶数的大小，使得尾数的最高数位上是有效值，保证浮点数的精度

正数的规格化数为$0.1xx...x$，负数的规格化数为$1.1xx...x$

左规：当尾数出现$\pm 0.0...0x..x$时，要将尾数向左移动若干位，每移动一位，阶码减1，直到规格化为止

右规：当尾数出现的有效位在最大数位之前，将尾数向右移动1位(**只需移动一次**)，阶码加1

# IEEE 754
>IEEE 754是408的重点
## 组成

IEEE754有两种形式，*32位短浮点数*，*64位长浮点数*

![](picture/IEEE754-structure.png)

IEEE754尾数采取**隐藏位策略的原码**的策略，阶码采用**移码**表示，移码的**偏移量**$2^{8-1}-1=127$(短浮点数)或$2^{11-1}-1=1023$(长浮点数)

隐藏位策略：数位的最高位总是1，为了多表示一位有效位，将最高位1隐藏，故23位的尾数表示24位有效数字。如$12=1100=1.1\times 2^3$

阶码值=阶码-偏移量，如短浮点数阶码值位3，其阶码为127+3=130=82H，长浮点数阶码为1023+3=1026=402H

## 真值

下表给出了IEEE754浮点数的范围

格式|最小值|最大值|
:-:|:-:|:-:
单精度|$E=1,M=0,N=1.0\times 2^{1-127}=2^{-126}$|$E=255-1=254,M=.111...,N=1.111\times2^{254-127}=2^{127}(2-2^{-23})$
双精度|$E=1,M=0,N=1.0\times 2^{1-1023}=2^{-1022}$|$E=2047-1=2046,M=.111...,N=1.111\times 2^{2046-1023}=2^{1023}(2-2^{-52})$

由上表我们可以看到，阶码不能全为0或全为1，这是我们要讲的特殊情况

## 特殊情况

- 当阶码全1尾数全0时，表示无穷大
- 当阶码全1尾数不为0时候，表示不是一个数（NaN）
- 阶码为1时导致数字溢出，发生异常
- 阶码全0而尾数全0，表示正负0，符号取决于数符
- 阶码全0时候，得到的数是非规格化数，表示小于IEEE754浮点数最小值的数，这些数非常接近于0

## 浮点数加减法

### 对阶

对阶指的是把两个阶数不同的浮点数阶码相等

对阶遵循小阶向大阶看齐，同时尾数右移一位，故有可能会舍弃有效位，影响精度

### 尾数求和

尾数按照定点数加减法运算

### 规格化

尾数求和后可能会导致运算结果非规格化，规格化的流程见浮点数尾数规格化部分

### 舍入

尾数对阶和右规时，会导致有效位移出，影响精度

常见的舍入方法：

- 舍1入0法：若保留位最高位数位为0，舍去；最高位为1，尾数末位加1；可能会导致尾数溢出，需要进行右规，直到不溢出为止
- 恒置1法：移位丢失的位中有1，则末位置1
- 截断法：直接截取，舍弃后面所有位

### 溢出判断

规格化和舍入时，可能会对阶码进行运算，从而会导致溢出

- 右规和舍入：舍入时，可能因为末位加1导致尾数溢出，从而需要进行右规，若右规前阶码位11111110，加1变成11111111，这个是特殊情况，上溢
- 左规：左规阶码减1，左规前阶码00000001，减1变为00000000，这是非规格数，下溢