#include<stdio.h>

typedef struct tree{//������һ�������������� 
	char v;//�ڵ�Ȩֵ 
	int l;//��������� 
	int r;//��������� 
}erchashu; 

erchashu a[1000];

void xianxudp(int x){//����ݹ���� 
	printf("%c ", a[x].v);//������ڵ�Ȼ�����������Ȼ����������� 
	if(a[x].l){
		xianxudp(a[x].l);
	}
	if(a[x].r){
		xianxudp(a[x].r);
	}
	return ;
}

void zhongxudp(int x){//����ݹ���� 
	if(a[x].l){//�ȱ���������Ȼ������ڵ�Ȼ����������� 
		zhongxudp(a[x].l);
	}
	printf("%c ", a[x].v);
	if(a[x].r){
		zhongxudp(a[x].r);
	}
	return ;
}

void houxudp(int x){//����ݹ���� 
	if(a[x].l){//�ȱ���������Ȼ�����������Ȼ������ڵ� 
		houxudp(a[x].l);
	}
	if(a[x].r){
		houxudp(a[x].r);
	}
	printf("%c ", a[x].v);
	return ;
}

int zhan[1000], top = 0;

void xianxu(int x){//����ǵݹ���� 
	top = 0;
	while(top >= 0){//�ж�ջ�Ƿ�Ϊ�� 
		while(x){//�ж��Ƿ������ 
			zhan[++top] = x;//��ջ 
			printf("%c ", a[x].v);//����ڵ� 
			x = a[x].l;//���������� 
		}
		x = zhan[top--];//������һ���ڵ� 
		x = a[x].r;//���������� 
	}
	return;
}

void zhongxu(int x){//����ǵݹ���� 
	top = 0;
	while(top >= 0){
		while(x){//�ж��Ƿ������ 
			zhan[++top] = x;//��ջ 
			x = a[x].l;//���������� 
		}
		x = zhan[top--];//������һ�ڵ� 
		printf("%c ", a[x].v);//����ڵ� 
		x = a[x].r;//���������� 
	}
	return;
}

void houxu(int x){//�����ǵݹ���� 
	int last = x;//��ʾ��һ������Ľڵ� 
	top = 0;//���ջ 
	zhan[++top] = x;//�ȴ�����ڵ� 
	while(top){//�ж�ջ�ǿ� 
		x = zhan[top];//ȡ��ջ���ڵ� 
		if(!a[x].l && !a[x].r){//�����û�������Ľڵ� 
			printf("%c ", a[x].v); //����ڵ� 
			last = x;
			top--;
		}else if(!a[x].r && last == a[x].l){//���û�����������������Ѿ������ 
			printf("%c ", a[x].v);//����ڵ� 
			last = x;
			top--;
		}else if(last == a[x].r){//����������Ѿ������ 
			printf("%c ", a[x].v);//����ڵ� 
			last = x;
			top--;
		}else{//��������ջ����������ջ������ 
			if(a[x].r){ 
				zhan[++top] = a[x].r;
			}
			if(a[x].l){
				zhan[++top] = a[x].l; 		
			}	
		}
	}
	return;	
}

int dui[1000], left = 0, right = 0;

void cenxu(int x){//��������㷨 ������������� 
	left = right = 0;//��ն��� 
	printf("%c ", a[x].v);//����ڵ� 
	if(a[x].l){ //������������� 
		dui[++right] = a[x].l; 
	}
	if(a[x].r){//��������������� 
		dui[++right] = a[x].r;
	}
	while(left < right){//���в�Ϊ�� 
		x = dui[++left];//����ȡ������Ԫ�� 
		printf("%c ", a[x].v);//����ڵ� 
		if(a[x].l){//������������������������� 
			dui[++right] = a[x].l; 
		}
		if(a[x].r){
			dui[++right] = a[x].r;
		}
	}
	return;
}

void panduan(int x){	
	left = right = 0;//��ն��� 
	int f = 0; 
	dui[++right] = x;//���ڵ������ 
	while(left < right){//���в�Ϊ�� 
		x = dui[++left];//ȡ��������˽ڵ� 
		if(x){//����Ϊ�������������������Ⱥ���ջ��������Ҳ��ջ 
			dui[++right] = a[x].l; 
			dui[++right] = a[x].r;
		}else{//��������ж� 
			for(int i = left + 1; i <= right; i++){//ֻҪջ�в����зǿսڵ���Ϊ��ȫ������ 
				if(dui[i] != 0){
					f = 1;
					break;
				}
			}
			if(f){
				printf("\n\n������ȫ������");
				return;
			}else{
				printf("\n\n����ȫ������"); 
				return;
			}
		}
	}
} 

int main(void){
	//����һ�����������ֱ��趨Ȩֵ����������ţ���������� 
	a[1].v = 'A'; a[1].l = 2; a[1].r = 3;
	a[2].v = 'B'; a[2].l = 4; a[2].r = 5;
	a[3].v = 'C'; a[3].l = 6; a[3].r = 7;
	a[4].v = 'D'; a[4].l = 8; a[4].r = 9;
	a[5].v = 'E'; a[5].l = 10; a[5].r = 11;
	a[6].v = 'F'; a[6].l = 0; a[6].r = 0;
	a[7].v = 'G'; a[7].l = 0; a[7].r = 0;
	a[8].v = 'H'; a[8].l = 0; a[8].r = 0;
	a[9].v = 'I'; a[9].l = 0; a[9].r = 0;
	a[10].v = 'J'; a[10].l = 0; a[10].r = 0;	
	a[11].v = 'K'; a[10].l = 0; a[10].r = 0;	
	/*a[1].v = 'A'; a[1].l = 2; a[1].r = 3;
	a[2].v = 'B'; a[2].l = 4; a[2].r = 5;
	a[3].v = 'C'; a[3].l = 0; a[3].r = 0;
	a[4].v = 'D'; a[3].l = 0; a[3].r = 0;
	a[5].v = 'E'; a[3].l = 0; a[3].r = 0;*/	
	printf("ǰ��ݹ飺  "); 
	xianxudp(1);
	printf("\n\nǰ��ǵݹ飺"); 
	xianxu(1);
	printf("\n\n����ݹ飺  ");
	zhongxudp(1);
	printf("\n\n����ǵݹ飺"); 
	zhongxu(1);
	printf("\n\n����ݹ飺  ");
	houxudp(1);
	printf("\n\n�����ǵݹ飺"); 
	houxu(1);
	printf("\n\n����"); 
	cenxu(1);
	panduan(1);
	return 0;
} 






