#include<stdio.h>
#include<string.h>
#include<stdlib.h>

int main(void){
	freopen("100000.txt", "w", stdout);
	int n, max;
	//printf("�������ݸ�����");
	scanf("%d", &n);
	printf("%d\n", n);
	//printf("������������"); 
	scanf("%d", &max);
	printf("%d\n", max);
	for(int i = 1; i <= n; i++){
		printf("%d ", rand() % (max+1));
	}
	return 0;
}
