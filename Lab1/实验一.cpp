#include<stdio.h>
#include<string.h>

int atop = 0, alow = 0, btop = 0, c[1000], ctop = 0;//cΪ��ջ 
char a[1000], b[1000];//aΪ��׺���ʽ�Ķ��У�bΪ����ŵĸ���ջ 

void pusha(int x){//aջѹ����� 
	a[++atop] = x;
}

char popa(void){//aջ�������� 
	return a[++alow];
}

void pushb(char x){//bջѹ����� 
	b[++btop] = x;
}

char popb(void){//bջ�������� 
	return b[btop--];
}

void pushc(int x){//cջѹ����� 
	c[++ctop] = x;
}

int popc(void){//cջ��������
	return c[ctop--];
}

int judge(char x){//�ж϶������Ϣ 
	if(x >= '0' && x <= '9') return 0;
	if(x == '*' || x == '/') return 1;
	if(x == '+' || x == '-') return 2;
	if(x == '(') return 3;
	if(x == ')') return 4;
	if(x == '#') return 5;
	if(x >= 'a' && x <= 'z') return 6;
}

void print(char s[]){
	int l = strlen(s), f = 0, i, j;
	printf("\n��׺���ʽ��"); 
	for(i = 1; i <= l; i++){
		if(judge(s[i]) == 5){//������# 
			f++;
		}else{
			printf("%c", s[i]);//�����ʽ���δ�ӡ���� 
		}
		if(f == 2){//����������#�ͽ��� 
			printf("\n\n");
			f = 0;
			break;
		}
	}
} 

void change(char s[]){
	int l = strlen(s), f = 0, i, j;
	for(i = 1; i <= l; i++){
		if(judge(s[i]) == 5){//���� 
			f++;
		}else if(judge(s[i]) == 1){//�˳�
			while(btop != 0 && b[btop] != '(' && (b[btop] == '/' || b[btop] == '*')){ 
				pusha(popb());//������ջ���������ȼ������ڵķ��ŵ�����ѹ���׺���ʽջ 
				pusha(' ');
				printf("��׺���ʽջ��"); 
				for(i = j; j <= atop; j++){
					printf("%c", a[j]);
				}
				printf("\n");
			}
			pushb(s[i]);//�ٽ���ѹ�����ջ 
		}else if(judge(s[i]) == 2){//�Ӽ� 
			while(btop != 0 && b[btop] != '('){
				pusha(popb());
				pusha(' ');
				printf("��׺���ʽջ��"); 
				for(j = 1; j <= atop; j++){
					printf("%c", a[j]);
				}
				printf("\n");
			}
			pushb(s[i]);
		}else if(judge(s[i]) == 3){//������ 
			pushb(s[i]);//����������ֱ�������ջ 
		}else if(judge(s[i]) == 4){//������ 
			while(btop != 0 && b[btop] != '('){// ���������Ž���������֮��ķ���ȫ������ʽջ 
				pusha(popb());
				pusha(' ');
				printf("��׺���ʽջ��"); 
				for(j = 1; j <= atop; j++){
					printf("%c", a[j]);
				}
				printf("\n");
			}
			if(b[btop] == '('){//���������ŵ��� 
				popb();
			}
		}else if(judge(s[i]) == 0){//���� 
			pusha(s[i]);
			if(judge(s[i+1]) != 0){
				pusha(' ');
				printf("��׺���ʽջ��"); 
				for(j = 1; j <= atop; j++){
					printf("%c", a[j]);
				}
				printf("\n");
			}
		}
		if(f == 2){//����������# 
			break;
		}
	}
	while(btop != 0){//��󽫷���ջ����ѹ���׺���ʽջ 
		pusha(popb());
		pusha(' ');
		printf("��׺���ʽջ��"); 
		for(i = 1; i <= atop; i++){
			printf("%c", a[i]);
		}
		printf("\n");
	} 
	printf("\n��׺���ʽ��");
	for(i = 1; i <= atop; i++){
		printf("%c", a[i]);
	} 
	printf("\n\n");
}

void jisuan(void){
	int i, j;
	while(alow != atop){
		char tmp = popa();
		if(tmp == ' '){
			popa();
			continue;
		}
		int m, n,shu;
		if(judge(tmp) == 0){//��charתΪint 
			shu = tmp - '0';
			while(judge(a[alow+1]) == 0){ 
				shu *= 10;
				shu += popa() - '0';
			}
			pushc(shu);//��������ֱ��ѹ���ջ 
			printf("��ջ��"); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}else if(tmp == '+'){//�������žͽ�������ջ����������ȡ��
			m = popc();
			n = popc();		
			pushc(m + n);//���м��㣬��ѹ���ջ 
			printf("��ջ��"); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}else if(tmp == '-'){
			m = popc();
			n = popc();
			pushc(n - m);
			printf("��ջ��"); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}else if(tmp == '*'){
			m = popc();
			n = popc();
			pushc(n * m);
			printf("��ջ��"); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}else if(tmp == '/'){
			m = popc();
			n = popc();
			pushc(n / m);
			printf("��ջ��"); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}
	}
	printf("\n�𰸣�%d", popc()); 
}

int main(void){
	char s[1000];
	scanf("%s", s+1);
	
	print(s);
	
	change(s);
	
	jisuan();
	
	return 0;
} 
