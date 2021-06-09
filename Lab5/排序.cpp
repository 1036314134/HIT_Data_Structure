#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<time.h>

clock_t    start,   stop;
double   duration;

void insort(int aa[], int n){//插入排序 
    int i, j, temp;
    for(i = 1; i < n; i++){
        j = i;
        for(j = i; j > 0; j--){//前i-1个数排好了，将第 i个数排到正确位置 
            if(aa[j] < aa[j-1]){
	            temp = aa[j];
	            aa[j] = aa[j-1];
	            aa[j-1] = temp;	
			}
			
        }
    }
}

void BInsertSort(int aa[], int n){//折半插入排序 
    int i, j, low = 0, high = 0, mid;
    int temp = 0;
    for (i = 1; i < n; i++){
        low = 0;
        high = i - 1;
        temp = aa[i];
        //采用折半查找法判断插入位置，最终变量 low 表示插入位置
        while (low <= high){
            mid = (low + high)/2;
            if (aa[mid] > temp){
                high = mid-1;
            }else{
                low = mid+1;
            }
        }
        //有序表中插入位置后的元素统一后移
        for (j = i; j > low; j--){
            aa[j] = aa[j-1];
        }
        aa[low] = temp;//插入元素
    }
}

void maopao(int aa[], int n){//冒泡排序 
	int i, j, temp;
	for (i = 0; i < n - 1; i++){
        for (j = 0; j < n - 1 - i; j++){
            if (aa[j] > aa[j + 1]){
                temp = aa[j];
                aa[j] = aa[j+1];
                aa[j+1] = temp;
            }
        }
    }
} 

void quicksort(int aa[], int left, int right){//快速排序 
	int l = left, r = right;
	int temp, x = aa[(l + r)/2];
	while (l <= r){
		while (aa[l] < x) ++l;
		while (aa[r] > x) --r;
		if (l <= r){
		    temp = aa[l]; 
			aa[l] = aa[r]; 
			aa[r] = temp;	
		    ++l; 
			--r;
		}
	}
	if (left < r) 
		quicksort(aa, left, r);
	if (l < right) 
		quicksort(aa, l, right);
}

void selectsort(int aa[], int n){//选择排序 
    int i, j, temp;    
    for(i = 0; i < n - 1; i++){
    	for (j = i + 1; j < n; j++){
    		if(aa[i] > aa[j]){//每次从未排好序的数中挑出最小值放最前面 
                temp = aa[i]; 
                aa[i] = aa[j];
                aa[j] = temp;
            }
		}  
	}
}

void HeapSort(int aa[], int n){//堆排序 
	int end = n - 1, temp;     //end指向最后一个元素；
	while(end != 0){  //end到根结点结束
		while(1){
			int pa = end / 2 - 1; //指向最后一个双亲结点；
			//将最大值移至下标为1的位置；
			while(pa >= 0){  //进行一次pa从最后一个双亲结点到第一个；
				if(aa[pa] < aa[2*pa+1]){  //双亲与其左孩子比较；
					temp = aa[pa];
					aa[pa] = aa[2*pa+1];
					aa[2*pa+1] = temp;	
				}
				if((2*pa+1 <= end) && aa[pa] < aa[2*pa+2]){  //双亲与其右孩子比较；
					temp = aa[pa];
					aa[pa] = aa[2*pa+2];
					aa[2*pa + 2] = temp;
				}
				pa--;   //进行--操作，移向上一个双亲；
			}
			//将最大值放在数组的最后一位，之后的次大值一次放这个位置的前一个位置；
			temp = aa[0];
			aa[0] = aa[end];
			aa[end] = temp;//将这次找到的最大值放置在a[end]；
			break;
		}
		end--;   //end前移，用来放置下一个循环的最大值；
	}
}

int get_index(int num, int dec, int order){
    int i, j, n;
    int index;
    int div;
    /* 根据位数，循环减去不需要的高位数字 */
    for(i = dec; i > order; i--){
        n = 1;
        for(j = 0; j<dec-1; j++){
        	n *= 10;
		} 
        div = num/n;
        num -= div * n;
        dec--;
    }
    /* 获得对应位数的整数 */
    n = 1;
    for(i = 0; i < order-1; i++){
    	n *= 10;
	}
    /* 获取index */
    index = num / n;
    return index;
}

void radix_sort(int array[], int len, int dec, int order){
    int i, j;
    int index;     /* 排序索引 */
    int tmp[len];  /* 临时数组，用来保存待排序的中间结果 */
    int num[10];   /* 保存索引值的数组 */
    memset(num, 0, sizeof(num));  /* 数组初始清零 */
    memset(tmp, 0, sizeof(tmp)); /* 数组初始清零 */

    if(dec < order) /* 最高位排序完成后返回 */
        return;

    for(i = 0; i < len; i++){
        index = get_index(array[i], dec, order);  /* 获取索引值 */
        num[index]++;  /* 对应位加一 */
    }
 	for(i = 1; i < 10; i++){
 		num[i] += num[i-1]; /* 调整索引数组 */
	}
 
    for(i = len-1; i >= 0; i--){
        index = get_index(array[i], dec, order);  /* 从数组尾开始依次获得各个数字的索引 */
        j = --num[index];  /* 根据索引计算该数字在按位排序之后在数组中的位置 */
        tmp[j] = array[i]; /* 数字放入临时数组 */
    }
 
    for (i = 0; i < len; i++)
        array[i] = tmp[i];  /* 从临时数组复制到原数组 */
    /* 继续按高一位的数字大小进行排序 */
    radix_sort(array, len, dec, order+1);
}

int a[300001];

void print(int aa[], int n){
	for(int i = 0; i < n; i++){
		printf("%d ", aa[i]);
	}
	printf("\n");
}

int main(void){
	int i, j, f, t, n, N, max;
	printf("输入1插入排序\n");
	printf("输入2折半插入排序\n"); 
	printf("输入3冒泡排序\n");
	printf("输入4快速排序\n");
	printf("输入5选择排序\n");
	printf("输入6堆排序\n");
	printf("输入7基数排序\n");
	printf("选择使用何种排序：");
	scanf("%d", &f);
	printf("输入数据规模N：");
	//scanf("%d", &n); 
	/*switch(n){
		case 500:
			freopen("500.txt", "r", stdin);
			break;
		case 1000:
			freopen("1000.txt", "r", stdin);
			break;
		case 2000:
			freopen("2000.txt", "r", stdin);
			break;
		case 5000:
			freopen("5000.txt", "r", stdin);
			break;
		case 10000:
			freopen("10000.txt", "r", stdin);
			break;
		case 30000:
			freopen("30000.txt", "r", stdin);
			break;
		case 50000:
			freopen("50000.txt", "r", stdin);
			break;
		case 100000:
			freopen("100000.txt", "r", stdin);
			break; 
		case 300000:
			freopen("300000.txt", "r", stdin);
			break;
	}*/ 
	scanf("%d", &N);	
	printf("请输入数据上限：");
	scanf("%d", &max); 
	for(i = 0; i < N; i++){
		a[i] = rand() % (max+1);
	}
	//for(i = 0; i < N; i++){
	//	scanf("%d", &a[i]);
	//}
	//print(a, N);
	switch(f){
		case 1:
			start = clock();
			insort(a, N);//插入排序 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 2:
			start = clock();
			BInsertSort(a, N);//折半插入 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 3:
			start = clock();
			maopao(a, N);//冒泡排序 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 4:
			start = clock();
			quicksort(a, 0, N-1);//快排 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 5:
			start = clock();
			selectsort(a, N);//选择排序 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 6:
			start = clock();
			HeapSort(a, N);//堆排序 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 7:
			start = clock();
			radix_sort(a, N, 3, 1);//基数排序 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
	}
	//print(a, N);
	printf("时间为%lf毫秒\n", duration);
	return 0;
} 
