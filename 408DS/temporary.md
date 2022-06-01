## 插入排序

~~~c
void insertSort(ELem[] A){
    for(int i = 1; i < A.length; i++){
        if(A[i-1] < A[i]){
            elem temp = A[i];
            for(int j = i-1; j >=0 && A[j]>temp; j--){
                A[j+1] = A[j];
            }
            A[j+1] = temp;
        }
    }
}
~~~

## 折半插入排序

~~~c
void binInsertSort(Elem[] A){
    for(int i = 1; i < A.length; i++){
        lo = 0;
        hi=i-1;
        temp = A[i];
        while(lo <= hi){
            mid=(lo+hi)/2;
            if(A[mid] > temp) lo = mid + 1;
            else hi = mid-1;
        }
        for(int j = i-1; j >= lo; i--){
            A[j+1] = A[j];
        }
        A[lo] = temp;
    }
}

~~~