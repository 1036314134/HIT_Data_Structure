#include<stdio.h>

typedef struct tree{//定义了一个二叉树的声明 
	char v;//节点权值 
	int l;//左子树编号 
	int r;//右子树编号 
}erchashu; 

erchashu a[1000];

void xianxudp(int x){//先序递归遍历 
	printf("%c ", a[x].v);//先输出节点然后遍历左子树然后遍历右子树 
	if(a[x].l){
		xianxudp(a[x].l);
	}
	if(a[x].r){
		xianxudp(a[x].r);
	}
	return ;
}

void zhongxudp(int x){//中序递归遍历 
	if(a[x].l){//先遍历左子树然后输出节点然后遍历右子树 
		zhongxudp(a[x].l);
	}
	printf("%c ", a[x].v);
	if(a[x].r){
		zhongxudp(a[x].r);
	}
	return ;
}

void houxudp(int x){//后序递归遍历 
	if(a[x].l){//先遍历左子树然后遍历右子树然后输出节点 
		houxudp(a[x].l);
	}
	if(a[x].r){
		houxudp(a[x].r);
	}
	printf("%c ", a[x].v);
	return ;
}

int zhan[1000], top = 0;

void xianxu(int x){//先序非递归遍历 
	top = 0;
	while(top >= 0){//判断栈是否为空 
		while(x){//判断是否遍历完 
			zhan[++top] = x;//入栈 
			printf("%c ", a[x].v);//输出节点 
			x = a[x].l;//遍历左子树 
		}
		x = zhan[top--];//返回上一个节点 
		x = a[x].r;//遍历右子树 
	}
	return;
}

void zhongxu(int x){//中序非递归遍历 
	top = 0;
	while(top >= 0){
		while(x){//判断是否遍历完 
			zhan[++top] = x;//入栈 
			x = a[x].l;//遍历左子树 
		}
		x = zhan[top--];//返回上一节点 
		printf("%c ", a[x].v);//输出节点 
		x = a[x].r;//遍历右子树 
	}
	return;
}

void houxu(int x){//后续非递归遍历 
	int last = x;//表示上一个输出的节点 
	top = 0;//清空栈 
	zhan[++top] = x;//先存入根节点 
	while(top){//判断栈非空 
		x = zhan[top];//取出栈顶节点 
		if(!a[x].l && !a[x].r){//如果是没有子树的节点 
			printf("%c ", a[x].v); //输出节点 
			last = x;
			top--;
		}else if(!a[x].r && last == a[x].l){//如果没有右子树但左子树已经输出了 
			printf("%c ", a[x].v);//输出节点 
			last = x;
			top--;
		}else if(last == a[x].r){//如果右子树已经输出了 
			printf("%c ", a[x].v);//输出节点 
			last = x;
			top--;
		}else{//否则先入栈右子树再入栈左子树 
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

void cenxu(int x){//层序遍历算法 ，广度优先搜索 
	left = right = 0;//清空队列 
	printf("%c ", a[x].v);//输出节点 
	if(a[x].l){ //有左子树入队列 
		dui[++right] = a[x].l; 
	}
	if(a[x].r){//再让右子树入队列 
		dui[++right] = a[x].r;
	}
	while(left < right){//队列不为空 
		x = dui[++left];//从左取出队列元素 
		printf("%c ", a[x].v);//输出节点 
		if(a[x].l){//继续让左子树与右子树入队列 
			dui[++right] = a[x].l; 
		}
		if(a[x].r){
			dui[++right] = a[x].r;
		}
	}
	return;
}

void panduan(int x){	
	left = right = 0;//清空队列 
	int f = 0; 
	dui[++right] = x;//根节点入队列 
	while(left < right){//队列不为空 
		x = dui[++left];//取出队列左端节点 
		if(x){//若不为空则让它的左右子树先后入栈，空子树也入栈 
			dui[++right] = a[x].l; 
			dui[++right] = a[x].r;
		}else{//否则进行判断 
			for(int i = left + 1; i <= right; i++){//只要栈中不含有非空节点则为完全二叉树 
				if(dui[i] != 0){
					f = 1;
					break;
				}
			}
			if(f){
				printf("\n\n不是完全二叉树");
				return;
			}else{
				printf("\n\n是完全二叉树"); 
				return;
			}
		}
	}
} 

int main(void){
	//设置一个二叉树，分别设定权值，左子树编号，右子树编号 
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
	printf("前序递归：  "); 
	xianxudp(1);
	printf("\n\n前序非递归："); 
	xianxu(1);
	printf("\n\n中序递归：  ");
	zhongxudp(1);
	printf("\n\n中序非递归："); 
	zhongxu(1);
	printf("\n\n后序递归：  ");
	houxudp(1);
	printf("\n\n后续非递归："); 
	houxu(1);
	printf("\n\n层序："); 
	cenxu(1);
	panduan(1);
	return 0;
} 






