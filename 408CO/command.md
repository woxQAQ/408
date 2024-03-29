# 指令格式

## 操作数地址码个数

分为零地址、一地址、二地址、三地址、四地址指令

## 定长操作码

最高位分配固定的若干位作为操作码

## 扩展操作码



## 指令的操作类型

- 数据传送：寄存器之间传送（MOV），读取主存（LOAD），写入主存（STORE）
- 算术和逻辑运算
- 移位操作
- 转移操作：JMP（无条件转移），条件转移BRANCH，调用CALL，返回RET，陷阱TRAP。转移条件一般是PSW中的标记位
- IO操作：IO指令通常是特权指令

# 寻址方式

## 指令寻址

### 顺序寻址

(PC)+1->PC,即程序计数器自动加一形成下一条指令的地址。注意“加1”指的是一个指令字长

### 跳跃寻址

通过转移类指令实现。跳跃寻址本质上还是修改PC，会先进行PC自增，再将指令中的地址来修改PC。

## 数据寻址

### 简单寻址

#### 立即数

地址码是操作数本身，即指令中直接给出数据，补码表示

EA = imm

特点：速度最快，但地址码部分位数限制数据范围

#### 直接寻址

指令中的地址就是操作数的地址。

EA=A

特点：简单，访存次数少，但是寻址范围有限

#### 间接寻址

指令的地址是存放操作数有效地址所在的存储单元的地址，即操作数地址的地址

EA=(A)

特点：寻址范围扩大，但是多次访存，效率低
#### 寄存器寻址

指令的地址是寄存器编号

EA=$R_i$

特点：速度快，支持矩阵/向量运算，但寄存器数量较少，价格昂贵

#### 寄存器间接寻址

寄存器寻址中，寄存器$R_i$中存放的不是操作数而是操作数的地址

EA=($R_i$)

#### 隐含寻址

指令中不直接指出操作数地址。比如单地址结构中规定ACC作为隐含的第二操作数，这就是隐含寻址

特点：减少指令字长，需要增加存储操作数或隐含地址的硬件

### 偏移寻址
>以某个地址为起点，形式地址作为偏移量
#### 相对寻址

相对寻址是把PC的值加上地址码

EA = (PC) + A,A是相对于下一跳指令地址的位移量（相对于PC的偏移量）

操作数的地址不是固定的，便与程序浮动。广泛用于转移指令

#### 基址寻址

基址寄存器（basic address register）：计算机中有专用的BR，也有用寄存器作为基址寄存器。当使用通用寄存器时，要在指令中指出要使用的寄存器编号。而对于有n个寄存器的系统，则在指令中有$/log_2{n}$个寄存器位

EA = (BR) + A

基址寄存器是面向操作系统**管理者**（存放在进程的PCB中）。程序运行时，(BR)的值被修改为进程的起始地址。在操作系统中，有所谓程序设备无关性的概念。采用基址寻址便可忽略底层硬件的实现，只需关注逻辑功能。

基址寻址可以扩大寻址范围，有利于多道程序设计，可用于编制浮动程序。

基址寄存器只能被OS管理。当通用寄存器被指定为BR时，该寄存器只能被OS管理。

#### 变址寻址

如基址寄存器一样，变址寄存器（index register，IX）既有专用的IX，也可以用通用寄存器作为IX

EA = (IX)+A

变址寄存器是面向用户的，即IX是可被修改的。IX主要用于数组问题，A作为数组首地址，不断改变IX以完成遍历数组等操作，适合编制**循环程序**

# CISC和RISC

- CISC(complex instruction system computer，复杂指令系统计算机)，指令字长不定长，指令数多，常用**微程序**。指令较为复杂，CISC的访存指令是无限制的。
- RISC(reduced instruction system computer, 精简指令系统计算机)，指令定长，只有一些适用频率较高的指令，指令较为简单，RISC采用硬布线，访存指令只有Load/Store指令