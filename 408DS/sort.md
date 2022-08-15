# 排序

>排序算法经常结合顺序表考察算法题，而且在选择题中排序算法是必考知识点。其中的**快速排序**，**堆排序**，**基数排序**，**希尔排序**是考察的重点，**各种内部排序算法**的比较也是高频考点，给出特定序列要能判断出进行了何种排序。要关注各种算法的思想，算法的效率和稳定性，不排除对稳定性进行考察。

## 直接插入排序

### 算法思想

&emsp;&emsp;假定每轮待排序的元素A[i]前面的元素均以有序，将A[i]插入前面的有序序列，将A[i]插入位置之后的元素后移一位；

~~~c
void insertSort(ELem[] A){
    for(int i = 1; i < A.length(); i++){
        if(A[i-1] < A[i]){
            elem temp = A[i];
            for(int j = i-1; j >=0 && A[j]>temp; j--){
                A[j+1] = A[j];
            }
            //循环结束时，j指向的是使得A[j]<temp的元素，即插入位置之前的元素，故插入位置为j+1,后面折半插入和希尔插入同理
            A[j+1] = temp;
        }
    }
}
~~~

## 折半插入排序

~~~c
void binInsertSort(Elem[] A){
    for(int i = 1; i < A.length(); i++){
        lo = 0;
        hi=i-1;
        temp = A[i];
        while(lo <= hi){
            mid=(lo+hi)/2;
            if(A[mid] > temp) lo = mid + 1;
            else hi = mid-@ext:yzane.markdown-pdf
    }
}

~~~

## 希尔排序

~~~c
    void heelSort(Elem[] A){
        for(int d = A.length()/2; d>=1; d/=2){
            for(int i = d + 1; i < A.length(); i++){
                if(A[i-d] > A[i]){
                    int temp = A[i];
                    for(int j = i-d; j > =0 && A[j] >temp; j -= d)
                        A[j+d] = A[j];
                    A[j+d] = temp;
                }
            }
        }
    }
~~~

## 冒泡排序

~~~C
    void bubbleSort(Elem[] A){
        for(int i = 0; i < A.length() - 1; i++){
            bool flag = false;
            for(int j = A.length() - 1; j > i; j--){
                if(A[j-1] > A[j])//逆序
                    swap(A[j-1], A[j]);//交换
                    flag = true;//标志本轮循环发生交换
            }
            if(flag == false) return;//本轮循环未发生交换，则表有序
        }
    }

~~~

## 快速排序

~~~C
    void QuickSort(Elem[] A, int low, int high){
        if(low < high){
            int pivotindex = partition(A, low, high);
            QuickSort(A, low, pivotindex - 1);//左子表快排
            QuickSort(A， Pivotindex + 1, high);//右子表快排
        }
    }
    int partition(Elem[] A, int low, int high){
        Elem pivot = A[low];
        while(low < high){
            while(low < high && A[high] >= pivot) --high;
            A[low] = A[high];
            while(low < high && A[low] <= pivot) --low;
            A[high] = A[low];
        }
        A[low] = pivot;
        return low;
    }


~~~

## 简单选择排序

~~~c
    void seleteSort(Elem[] A){
        for(int i = 0; i < A.length(); i++){
            int min = A[i];
            for(int j = i + 1; j < A.length(); j++){
                if(A[j] < min) min = A[j];
            }
            if(A[i] !=min)
                swap(A[i], A[min]);
        }
    }
~~~

## **堆排序**

>堆排序考察频率up，需要得到重视

堆是满足下列条件之一的序列：

1. L[i] > L[2i], L[i] > L[2i-1];
2. L[i] < L[2i], L[i] < L[2i-1];

堆可以视为一颗完全二叉树(顺序存储)，其根节点的值大于或小于其孩子节点的值

堆排序的关键有两个，一个是建立初始堆，第二个是通过对堆进行调整来完成排序

以大根堆为例，建立初始堆的过程实际上是不断调整序列的过程，而调整堆的过程可以概括为**小元素不断下坠**的过程。

调整堆和建立堆的算法实现如下

~~~c
    void BuildMaxHeap(elem[] A){
        for(int i = A.length()/2; i>0; i--){
            HeadAdjust(A, i, A.length());
        }
    }
    void HeadAdjust(Elem[]A, int k, int length){
        A[0] = A[k];//保存根节点值
        for(int i = 2*k; i <= length; i*=2){//i*2是为了进入下层检查堆是否被破坏
            if(i < length && A[i+1] > A[i]) 
                i++;//选取较大子元素
            if(A[0] >= A[i])
                break;//大根堆不被破坏则跳出循环
            else{
                A[k] = A[i];//较大子元素A[i]调整到根节点
                k = i;//记住被替换元素位置，方便继续下坠
            }
        }
        A[k] = A[0];
    }
~~~

现在我们建立了一个大根堆，那么如何进行排序呢？

由堆的性质可以知道根节点的关键字是最大的，**将根节点和堆的最后一个节点进行交换，对剩下的堆进行调整，重复这个过程，就能得到一个递增序列**

## 归并排序

归并：将两个有序的关键字序列合并为一个有序的序列

归并排序：初始状态每个元素都是单独的有序序列

~~~c
    Elem[] B = (Elem *)malloc(A.length()*sizeof(Elem));
    void mergeSort(Elem[] A, ,int lo, int hi){
        if(lo < hi){
            int mid = (lo+hi)/2;
            mergeSort(A, lo, mid);//前半子表递归归并
            mergeSort(A, mid+1, hi);//后半字表递归归并
            merge(A, lo, mid, hi);
        }
    }
    void merge(ELem[] A,int low, int mid, int hi){
        for(int k = low; k < hi; k++){
            B[k] = A[k];
        }
        for(int k = lo; k < hi; k++){
            int i = lo, j = mid + 1;
            if(A[i] <=A[j]) A[k] = B[i++];//保证稳定性
            else A[k] = B[j++];
        }
        while(i<=mid) A[k++] = B[i++];//剩余部分复制
        while(j<=hi) A[k++] = B[j++];
    }
~~~

## 基数排序

>基数排序可以和hash表的拉链法，树的孩子表示法，图的邻接矩阵表联系起来学习和理解

## 内部排序比较和应用

## 外部排序
>最佳归并树从未作为大题考点，但是就408的考察趋势来说，很有可能在大题中考察最佳归并树的内容，要引起重视。本节其他考点并不重要，主要是最佳归并树的构造，因为408中已经多次考察过哈夫曼树了，而哈夫曼树是二叉的最佳归并树。

### 外部排序的概念

### 败者树

### 置换选择排序

### 最佳归并树

经过置换选择排序后，会得到若干大小不等的初始归并段。现在的问题就是如何组织这些归并段的归并次序，使得IO次数最少。

借鉴哈夫曼树的思想，也就是每次归并选取长度最短的k个归并段，，则可以得到最少的归并次数。

然而，并不是所有的归并段数都能构成严格的k叉树，当初始归并段不能构成一棵严格的k叉树时，就要增加**虚段**

下面推导虚段个数

$
\begin{cases}n_0=虚段+初始归并段数\\n=n_0+n_k\\kn_k=n-1(分支数=节点数-1)
\end{cases}\Rightarrow n_k=\frac{n_0-1}{k-1}
$

$n_k$代表了度为k的节点，这个值必然是整数，若计算出$n_k$不是整数，则说明$n_0$的值需要增加一个常数，也就是虚段数

- 若$n_k$除得尽，则符合严格k叉树
- 若$n_k$除不尽，虚段数为$k-1-u(u为余数)$
