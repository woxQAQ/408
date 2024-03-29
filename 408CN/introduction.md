# 计算机网络概述
>概述没有出题，但是这部分内容对把握计算机网络而言很重要，而且有些概念会在以后的章节中经常涉及
## 计算机网络的组成部分

- 网络边缘：指的是所有连接到Internet上的主机
- 网络核心：由大量的网络和连接网络的路由器组成
- 协议：协议规范了两个或多个通信实体之间交换的报文的格式和顺序，以及报文发送和/或接收一条报文或其他事件所采取的动作。
- 通信子网：由各种传输介质，通信设备和网络协议组成
- 资源子网：实现资源共享功能的设备机器软件的集合

## 功能

- 数据通信
- 资源共享
- 分布式处理：某个计算机负荷过重，将其处理的某个复杂任务分配为网络中的其他设备进行处理
- 提高可靠性
- 负载均衡：将任务均衡的分配给网络中的计算机

## 计算机网络的分类

按分布范围。在计算机网络中，我们将重点掌握**广域网和局域网**，分别对应了网络层和链路层

- 广域网WAN：长距离通信，使用**交换**技术。广域网是Internet的核心
- 城域网MAN
- 局域网LAN：覆盖范围小，通常是直径几十米到几千米的区域。采用**广播技术**
- 个人区域网PAN
>区分LAN和WAN的最重要指标不是距离，而是二者采用的技术。广域网采用交换技术，而局域网采用广播技术

按传输技术

- 广播网：所有联网计算机共享同一通信信道，所有计算机都会收听信道中的报文分组，根据分组头部的地址决定是否接收分组。局域网基本上都是广播网。
- p2p网：每条线路连接一对计算机，他们的分组传输需要通过中间节点进行接收存储和转发。广域网基本上采用p2p网

按拓扑结构

- 总线形：最著名的总线形网络是以太网，然而以太网的物理拓扑是星形或拓展星形
- 星形
- 环形：令牌环(IEEE802.5)网采用环形结构，光纤分布数字接口(IEEE802.8)也采用环形拓扑
- 网状

按交换技术

- 电路交换：有线电话就是经典的电路交换。点到点之间有专门的物理线路连接；通话期间信道不进行共享
- 报文交换：报文交换也叫存储转发；现代的网络部分基本都采用存储转发网络。存储转发网络的特点就是将报文传送到中间节点，然后再查询转发表确定要转发的目标。路由器是存储转发网最重要的组成部件。
- 分组交换：分组交换是将报文进行细分，也采用存储转发技术。现在的网络基本上都采用分组交换网络

按传输介质

- 有线网络
- 无线网络

## 计算机网络的性能指标

- 带宽：表示信道所能达到的数据传送速率的**最值**(b/s)
- 时延：时延是计算机网络中非常重要的概念，基本上是必考点
  - 发送时延：指的是将分组的所有比特送上链路的时间，即**发送第一个bit到发送完分组所有bit的时间**。
  发送时延=分组长度/信道宽度
  - 传播时延：电磁波在信道传播所需的时间
  传播时延=信道长度/电磁波传播速率
  - 处理时延：数据包为存储转发而进行的处理而产生的时延
  - 排队时延：分组在路由器中输入队列和输出队列中排队的时延
- 时延带宽积：也叫**链路比特长度**，时延带宽积=发送时延×带宽
- 往返时延RTT：非常非常重要的概念，指的是发送方发送一个分组到发送方**接收到来自接收端的ACK**所需的时间，一般来说，**RTT=2×传播时延+末端处理时间**
- 吞吐量
- 速率：最高速率即为带宽
- 信道利用率：指的是某一信道有百分之多少的时间是有数据通过的

# 计算机网络体系结构与参考模型
>这部分内容是第一章的必考题，一题选择题，结构模型考察的频率较高
## 分层结构原理

我们将计算机网络体系分为若干层，不同机器的同一层称为对等层，同一层的实体称为对等实体

对等层次发送的数据单元称为**协议控制单元PDU**，PDU由控制信息和数据信息组成。

通常我们所说的IP头部，MAC头部即为控制信息。链路层的PDU称为帧，网络层的PDU称为分组，传输层的PDU称为报文段。要注意的是MAC不仅加头部也加尾部

协议规范了两个或多个通信实体之间交换的报文的格式和顺序，以及报文发送和/或接收一条报文或其他事件所采取的动作。

协议由语法、语义、同步(时序)三部分组成。

- 语法规定传输数据的格式
- 语义规定所要完成的功能，包括要发送的控制信息、完成的动作和做出的应答
- 时序规定各种操作的条件和时序关系。
  >这部分内容已经考察过，不用特别关注，但不排除再进行考察

接口是同一结点内相邻两层交换信息的连接点

协议的实现要通过接口获得下层提供的服务，协议的目的是为上层提供更好的服务

服务是下层为上层提供的功能调用
> 并不是所有下层的功能都是服务，只有上层可见的功能才是服务

- 面向连接服务和无连接服务：
  面向连接到意思是，通信双方进行通信之前，必须**建立连接**，**分配缓冲区**，传输结束后**释放连接和所占用的资源**。
  包括连接建立，数据传输和连接释放三个部分。**TCP**协议是经典的面向连接服务
  无连接服务中，通信双方通信前无需建立连接，需要发送数据直接发送。这种服务同时也是不可靠服务，通常被描述为**尽力而为交付**
  IP和UDP是经典的无连接服务
- 可靠服务和不可靠服务
  可靠服务是指网络具有纠错，检错和应答机制。
  不可靠服务指的是网络只保证尽可能正确送达，不能保证数据正确、可靠。
  对于不可靠服务，需要通过用户或应用来保证其可靠性。
- 有应答服务和无应答服务
  有应答指的是接收方在收到数据后给发送方给出相应的应答，如FTP服务。
  无应答服务指的是接收方接收到数据不发送应答，如HTTP服务。

## OSI/ISO模型

OSI/ISO模型是法定标准，然而通常应用的是TCP/IP模型及其衍生。

- 应用层:应用层是用户和网络的界面。
- 表示层：处理两个通信系统中交换信息的方式，即**数据格式变换**，如数据压缩，加密和解密
- 会话层：会话层**管理主机之间的会话**，包括建立、管理及终止进程间的会话
  会话层可以使用校验点使通信失效时从校验点恢复通信，实现数据同步
- 传输层：传输层的传输单元是报文段(TCP)或用户数据报(UDP)。
  传输层负责主机中两个**进程之间**的通信，功能是提供**端到端**可靠服务的连接。
  传输层的"地址"是**端口**，用来**标识进程**。
  **复用**是多个应用层进程可以同时使用传输层的服务
  **分用**是传输层把收到的信息交付给应用层的进程
- 网络层：网络层是网络的核心。网络层的PDU是**数据报**。
  网络层主要解决的是将PDU从源端传送到目的端，于是就有**路由和转发**两大功能
  在网络层中我们会学习很多的协议，如IP，NAT，DHCP，ARP，OSPF，RIP，ICMP等等
- 数据链路层:数据链路层的PDU是**帧**，任务是打包IP数据报成帧，链路层的功能是成帧、差错控制、流量控制和传输管理
  对于广播网络来讲，如何处理共享信道的数据访问是很重要的，这个功能是由**介质访问控制(MAC)**层来处理的，因此数据链路层的协议也叫**MAC协议**，常见的MAC协议有Aloha，CSMA-CD，CSMA-CA
  对于点到点网络，有ppp协议和HDLC协议
- 物理层：物理层的任务很简单，传输比特流，一切上层的PDU在物理层都抽象成比特流，不进行任何处理
  物理层的协议(接口标准)包括EIA-232C、RS449、X.21
  物理层的协议既包括物理层面的**机械特性**，也包括信号的意义和**电气特性**，如编码方式和译码方式

## TCP/IP模型

TCP/IP模型的核心是TCP协议和IP协议。TCP/IP模型和上面OSI/ISO模型大差不差，

- 应用层
- 传输层
- 网际层
- 网络接口层

OSI/ISO模型和TCP/IP模型的区别如下表：

-|OSI/ISO|TCP/IP
-|:-:|:-:
网络层|无连接，面向连接|无连接
传输层|有连接|无连接，面向连接
