#include<stdio.h>
#include<string.h>

int atop = 0, alow = 0, btop = 0, c[1000], ctop = 0;
char a[1000], b[1000];

void pusha(int x){
	a[++atop] = x;
}

char popa(void){
	return a[++alow];
}

void pushb(char x){
	b[++btop] = x;
}

char popb(void){
	return b[btop--];
}

void pushc(double x){
	c[++ctop] = x;
}

double popc(void){
	return c[ctop--];
}

int judge(char x){
	if(x >= '0' && x <= '9') return 0;
	if(x == '*' || x == '/') return 1;
	if(x == '+' || x == '-') return 2;
	if(x == '(') return 3;
	if(x == ')') return 4;
	if(x == '#') return 5;
}

int main(void){
	char s[1000];
	scanf("%s", s+1);
	int l = strlen(s), f = 0, i, j;
	printf("\n中缀表达式："); 
	for(i = 1; i <= l; i++){
		if(judge(s[i]) == 5){
			f++;
		}else{
			printf("%c", s[i]);
		}
		if(f == 2){
			printf("\n\n");
			f = 0;
			break;
		}
	}
	for(i = 1; i <= l; i++){
		if(judge(s[i]) == 5){//井号 
			f++;
		}else if(judge(s[i]) == 1){//乘除
			while(btop != 0 && b[btop] != '(' && (b[btop] == '/' || b[btop] == '*')){
				pusha(popb());
				pusha(' ');
				printf("后缀表达式栈："); 
				for(i = j; j <= atop; j++){
					printf("%c", a[j]);
				}
				printf("\n");
			}
			pushb(s[i]);
		}else if(judge(s[i]) == 2){//加减 
			while(btop != 0 && b[btop] != '('){
				pusha(popb());
				pusha(' ');
				printf("后缀表达式栈："); 
				for(j = 1; j <= atop; j++){
					printf("%c", a[j]);
				}
				printf("\n");
			}
			pushb(s[i]);
		}else if(judge(s[i]) == 3){//左括号 
			pushb(s[i]);
		}else if(judge(s[i]) == 4){//右括号 
			while(btop != 0 && b[btop] != '('){
				pusha(popb());
				pusha(' ');
				printf("后缀表达式栈："); 
				for(j = 1; j <= atop; j++){
					printf("%c", a[j]);
				}
				printf("\n");
			}
			if(b[btop] == '('){
				popb();
			}
		}else if(judge(s[i]) == 0){//数字 
			pusha(s[i]);
			if(judge(s[i+1]) != 0){
				pusha(' ');
				printf("后缀表达式栈："); 
				for(j = 1; j <= atop; j++){
					printf("%c", a[j]);
				}
				printf("\n");
			}
		}
		if(f == 2){
			break;
		}
	}
	while(btop != 0){
		pusha(popb());
		pusha(' ');
		printf("后缀表达式栈："); 
		for(i = 1; i <= atop; i++){
			printf("%c", a[i]);
		}
		printf("\n");
	} 
	printf("\n后缀表达式：");
	for(i = 1; i <= atop; i++){
		printf("%c", a[i]);
	} 
	printf("\n\n");
	while(alow != atop){
		char tmp = popa();
		if(tmp == ' '){
			popa();
			continue;
		}
		int m, n,shu;
		if(judge(tmp) == 0){
			shu = tmp - '0';
			while(judge(a[alow+1]) == 0){
				shu *= 10;
				shu += popa() - '0';
			}
			pushc(shu);
			printf("答案栈："); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}else if(tmp == '+'){
			m = popc();
			n = popc();		
			pushc(m + n);
			printf("答案栈："); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}else if(tmp == '-'){
			m = popc();
			n = popc();
			pushc(n - m);
			printf("答案栈："); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}else if(tmp == '*'){
			m = popc();
			n = popc();
			pushc(n * m);
			printf("答案栈："); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}else if(tmp == '/'){
			m = popc();
			n = popc();
			pushc(n / m);
			printf("答案栈："); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}
	}
	printf("\n答案：%d", popc()); 
	return 0;
} 
