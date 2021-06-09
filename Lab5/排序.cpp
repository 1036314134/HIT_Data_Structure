#include<stdio.h>
#include<string.h>
#include<stdlib.h> 
#include<time.h>

clock_t    start,   stop;
double   duration;

void insort(int aa[], int n){//�������� 
    int i, j, temp;
    for(i = 1; i < n; i++){
        j = i;
        for(j = i; j > 0; j--){//ǰi-1�����ź��ˣ����� i�����ŵ���ȷλ�� 
            if(aa[j] < aa[j-1]){
	            temp = aa[j];
	            aa[j] = aa[j-1];
	            aa[j-1] = temp;	
			}
			
        }
    }
}

void BInsertSort(int aa[], int n){//�۰�������� 
    int i, j, low = 0, high = 0, mid;
    int temp = 0;
    for (i = 1; i < n; i++){
        low = 0;
        high = i - 1;
        temp = aa[i];
        //�����۰���ҷ��жϲ���λ�ã����ձ��� low ��ʾ����λ��
        while (low <= high){
            mid = (low + high)/2;
            if (aa[mid] > temp){
                high = mid-1;
            }else{
                low = mid+1;
            }
        }
        //������в���λ�ú��Ԫ��ͳһ����
        for (j = i; j > low; j--){
            aa[j] = aa[j-1];
        }
        aa[low] = temp;//����Ԫ��
    }
}

void maopao(int aa[], int n){//ð������ 
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

void quicksort(int aa[], int left, int right){//�������� 
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

void selectsort(int aa[], int n){//ѡ������ 
    int i, j, temp;    
    for(i = 0; i < n - 1; i++){
    	for (j = i + 1; j < n; j++){
    		if(aa[i] > aa[j]){//ÿ�δ�δ�ź��������������Сֵ����ǰ�� 
                temp = aa[i]; 
                aa[i] = aa[j];
                aa[j] = temp;
            }
		}  
	}
}

void HeapSort(int aa[], int n){//������ 
	int end = n - 1, temp;     //endָ�����һ��Ԫ�أ�
	while(end != 0){  //end����������
		while(1){
			int pa = end / 2 - 1; //ָ�����һ��˫�׽�㣻
			//�����ֵ�����±�Ϊ1��λ�ã�
			while(pa >= 0){  //����һ��pa�����һ��˫�׽�㵽��һ����
				if(aa[pa] < aa[2*pa+1]){  //˫���������ӱȽϣ�
					temp = aa[pa];
					aa[pa] = aa[2*pa+1];
					aa[2*pa+1] = temp;	
				}
				if((2*pa+1 <= end) && aa[pa] < aa[2*pa+2]){  //˫�������Һ��ӱȽϣ�
					temp = aa[pa];
					aa[pa] = aa[2*pa+2];
					aa[2*pa + 2] = temp;
				}
				pa--;   //����--������������һ��˫�ף�
			}
			//�����ֵ������������һλ��֮��Ĵδ�ֵһ�η����λ�õ�ǰһ��λ�ã�
			temp = aa[0];
			aa[0] = aa[end];
			aa[end] = temp;//������ҵ������ֵ������a[end]��
			break;
		}
		end--;   //endǰ�ƣ�����������һ��ѭ�������ֵ��
	}
}

int get_index(int num, int dec, int order){
    int i, j, n;
    int index;
    int div;
    /* ����λ����ѭ����ȥ����Ҫ�ĸ�λ���� */
    for(i = dec; i > order; i--){
        n = 1;
        for(j = 0; j<dec-1; j++){
        	n *= 10;
		} 
        div = num/n;
        num -= div * n;
        dec--;
    }
    /* ��ö�Ӧλ�������� */
    n = 1;
    for(i = 0; i < order-1; i++){
    	n *= 10;
	}
    /* ��ȡindex */
    index = num / n;
    return index;
}

void radix_sort(int array[], int len, int dec, int order){
    int i, j;
    int index;     /* �������� */
    int tmp[len];  /* ��ʱ���飬���������������м��� */
    int num[10];   /* ��������ֵ������ */
    memset(num, 0, sizeof(num));  /* �����ʼ���� */
    memset(tmp, 0, sizeof(tmp)); /* �����ʼ���� */

    if(dec < order) /* ���λ������ɺ󷵻� */
        return;

    for(i = 0; i < len; i++){
        index = get_index(array[i], dec, order);  /* ��ȡ����ֵ */
        num[index]++;  /* ��Ӧλ��һ */
    }
 	for(i = 1; i < 10; i++){
 		num[i] += num[i-1]; /* ������������ */
	}
 
    for(i = len-1; i >= 0; i--){
        index = get_index(array[i], dec, order);  /* ������β��ʼ���λ�ø������ֵ����� */
        j = --num[index];  /* ������������������ڰ�λ����֮���������е�λ�� */
        tmp[j] = array[i]; /* ���ַ�����ʱ���� */
    }
 
    for (i = 0; i < len; i++)
        array[i] = tmp[i];  /* ����ʱ���鸴�Ƶ�ԭ���� */
    /* ��������һλ�����ִ�С�������� */
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
	printf("����1��������\n");
	printf("����2�۰��������\n"); 
	printf("����3ð������\n");
	printf("����4��������\n");
	printf("����5ѡ������\n");
	printf("����6������\n");
	printf("����7��������\n");
	printf("ѡ��ʹ�ú�������");
	scanf("%d", &f);
	printf("�������ݹ�ģN��");
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
	printf("�������������ޣ�");
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
			insort(a, N);//�������� 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 2:
			start = clock();
			BInsertSort(a, N);//�۰���� 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 3:
			start = clock();
			maopao(a, N);//ð������ 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 4:
			start = clock();
			quicksort(a, 0, N-1);//���� 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 5:
			start = clock();
			selectsort(a, N);//ѡ������ 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 6:
			start = clock();
			HeapSort(a, N);//������ 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
		case 7:
			start = clock();
			radix_sort(a, N, 3, 1);//�������� 
			stop = clock();
			duration = ((double)(stop - start)) * 1000 / CLK_TCK;
			break;
	}
	//print(a, N);
	printf("ʱ��Ϊ%lf����\n", duration);
	return 0;
} 
