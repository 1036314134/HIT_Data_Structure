#include<stdio.h>
#include<string.h>

int atop = 0, alow = 0, btop = 0, c[1000], ctop = 0;//c为答案栈 
char a[1000], b[1000];//a为后缀表达式的队列，b为存符号的辅助栈 

void pusha(int x){//a栈压入操作 
	a[++atop] = x;
}

char popa(void){//a栈弹出操作 
	return a[++alow];
}

void pushb(char x){//b栈压入操作 
	b[++btop] = x;
}

char popb(void){//b栈弹出操作 
	return b[btop--];
}

void pushc(int x){//c栈压入操作 
	c[++ctop] = x;
}

int popc(void){//c栈弹出操作
	return c[ctop--];
}

int judge(char x){//判断读入的信息 
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
	printf("\n中缀表达式："); 
	for(i = 1; i <= l; i++){
		if(judge(s[i]) == 5){//读到了# 
			f++;
		}else{
			printf("%c", s[i]);//将表达式依次打印出来 
		}
		if(f == 2){//读入了两个#就结束 
			printf("\n\n");
			f = 0;
			break;
		}
	}
} 

void change(char s[]){
	int l = strlen(s), f = 0, i, j;
	for(i = 1; i <= l; i++){
		if(judge(s[i]) == 5){//井号 
			f++;
		}else if(judge(s[i]) == 1){//乘除
			while(btop != 0 && b[btop] != '(' && (b[btop] == '/' || b[btop] == '*')){ 
				pusha(popb());//将符号栈顶所有优先级不大于的符号弹出并压入后缀表达式栈 
				pusha(' ');
				printf("后缀表达式栈："); 
				for(i = j; j <= atop; j++){
					printf("%c", a[j]);
				}
				printf("\n");
			}
			pushb(s[i]);//再将其压入符号栈 
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
			pushb(s[i]);//遇到左括号直接入符号栈 
		}else if(judge(s[i]) == 4){//右括号 
			while(btop != 0 && b[btop] != '('){// 遇到右括号将两个括号之间的符号全部入表达式栈 
				pusha(popb());
				pusha(' ');
				printf("后缀表达式栈："); 
				for(j = 1; j <= atop; j++){
					printf("%c", a[j]);
				}
				printf("\n");
			}
			if(b[btop] == '('){//并将左括号弹出 
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
		if(f == 2){//读入了两个# 
			break;
		}
	}
	while(btop != 0){//最后将符号栈依次压入后缀表达式栈 
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
		if(judge(tmp) == 0){//将char转为int 
			shu = tmp - '0';
			while(judge(a[alow+1]) == 0){ 
				shu *= 10;
				shu += popa() - '0';
			}
			pushc(shu);//遇到数字直接压入答案栈 
			printf("答案栈："); 
			for(i = 1; i <= ctop; i++){
				printf("%d ", c[i]);
			}
			printf("\n");
			popa();
		}else if(tmp == '+'){//遇到符号就将最新入栈的两个数字取出
			m = popc();
			n = popc();		
			pushc(m + n);//进行计算，再压入答案栈 
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
}

int main(void){
	char s[1000];
	scanf("%s", s+1);
	
	print(s);
	
	change(s);
	
	jisuan();
	
	return 0;
} 
