#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int d, b;
int map[101][101];
int vis[101];
int zhan[1000], top;
int que[1000], left, right;
int next[101], to[101], son[101], len; 
int zhann[100], topp;

void addedge(int x, int y){//邻接链表增加一条边 
	next[++len] = son[x]; //将这条边指向x的最后一条边 
	son[x] = len;//更新x的最后一条边 
	to[len] = y;//保存该边的指向 
}

void change1(void){//邻接矩阵转邻接链表 
	for(int i = 1; i <= d; i++){
		for(int j = 1; j <= d; j++){
			if(map[i][j]){
				addedge(i, j);
			}
		}
	}
} 

void change2(void){//邻接链表转邻接矩阵 
	for(int i = 1; i <= d; i++){
		for(int j = son[i]; j; j = next[j]){
			map[i][to[j]] = 1;
		}
	}
}

void dfs1(int x){//邻接矩阵深度优先搜索递归 
	printf("%c ", x+64);
	vis[x] = 1;
	for(int i = d; i >= 1; i--){
		if(!vis[i] && map[x][i]){
			vis[i] = 1;
			dfs1(i);
		}
	}
}

void dfs2(int x){//邻接矩阵深度优先搜索非递归 
	zhan[++top] = x;
	while(top > 0){
		int tmp = zhan[top--];
		if(!vis[tmp]){
			printf("%c ", tmp+64);
			vis[tmp] = 1;
		}
		for(int i = 1; i <= d; i++){
			if(!vis[i] && map[tmp][i]){
				zhan[++top] = i;
			}
		}
	}	
}

void dfs3(int x){//邻接链表深度优先搜索递归 
	printf("%c ", x+64);	
	vis[x] = 1;
	for(int i = son[x]; i; i = next[i]){
		if(!vis[to[i]]){
			vis[to[i]] = 1;
			dfs3(to[i]);
		}
	}
}

void dfs4(int x){//邻接链表深度优先搜索非递归 
	zhan[++top] = x;
	while(top > 0){
		int tmp = zhan[top--];
		if(!vis[tmp]){
			printf("%c ", tmp+64);
			vis[tmp] = 1;
		}
		topp = 0;
		for(int i = son[tmp]; i; i = next[i]){
			if(!vis[to[i]]){
				zhann[++topp] = to[i];
			}
		}
		while(topp){
			zhan[++top] = zhann[topp--];
		}
	}
}

void bfs1(int x){//邻接矩阵广度优先搜索 
	que[++right] = x;
	vis[x] = 1;
	while(left < right){
		int tmp = que[++left];
		printf("%c ", tmp+64);
		for(int i = d; i >= 1; i--){
			if(!vis[i] && map[tmp][i]){
				que[++right] = i;
				vis[i] = 1;
			}
		}
	}
}
 
void bfs2(int x){//邻接链表广度优先搜索 
	que[++right] = x;
	vis[x] = 1;
	while(left < right){
		int tmp = que[++left];
		printf("%c ", tmp+64);
		//topp = 0;
		for(int i = son[tmp]; i; i = next[i]){
			if(!vis[to[i]] && i){
				//zhann[++topp] = to[i];
				que[++right] = to[i];
				vis[to[i]] = 1;
			}
		}
		//while(topp){
			//que[++right] = zhann[--topp];
		//}
		/*printf("队列："); 
		for(int i = left+1; i <= right; i++){
			printf("%c ", que[i]+64);
		}
		printf("\n");*/
	} 
} 
 
 
int main(void){
	freopen("test.txt", "r", stdin); 
	int i, j, k, f;
	char tmp1[10], tmp2[10]; 
	scanf("%d", &b);
	printf("边的个数为：%d\n", b);
	scanf("%d", &d);
	printf("顶点个数为：%d\n", d); 
	scanf("%d", &f);
	if(f == 1){
		printf("用了邻接矩阵储存\n"); 
		memset(map, 0, sizeof(map));//邻接矩阵清零
		for(i = 1; i <= b; i++){
			scanf("%s %s", tmp1, tmp2);
			printf("第%d边为%s %s\n", i, tmp1, tmp2); 
			tmp1[0] -= 64;
			tmp2[0] -= 64;
			map[tmp1[0]][tmp2[0]] = 1;
			map[tmp2[0]][tmp1[0]] = 1;
		}
	}else if(f == 2){
		printf("用了邻接链表储存\n"); 
		len = 0; 
		memset(next, 0, sizeof(next));
		memset(son, 0, sizeof(son));
		memset(to, 0, sizeof(to)); 
		for(i = 1; i <= b; i++){
			scanf("%s %s", tmp1, tmp2);
			printf("第%d边为%s %s\n", i, tmp1, tmp2); 
			tmp1[0] -= 64;
			tmp2[0] -= 64;
			addedge(tmp1[0], tmp2[0]);
			addedge(tmp2[0], tmp1[0]);		
		}
		/*for(i = 1; i <= d; i++){
			printf("%c的链表：", i+64); 
			for(j = son[i]; j; j = next[j]){
				printf("%c ", to[j]+64);
			}
			printf("\n");
		}*/
	}
	printf("输入0结束\n"); 
	printf("输入1矩阵深度递归搜索\n"); 
	printf("输入2矩阵深度非递归搜索\n");
	printf("输入3矩阵广度搜索\n");
	printf("输入4链表深度递归搜索\n");
	printf("输入5链表深度非递归搜索\n");
	printf("输入6链表广度搜索\n");
	printf("输入7矩阵转链表\n");
	printf("输入8链表转矩阵\n"); 
	while(f){
		scanf("%d", &f);
		if(f == 1){
			memset(vis, 0, sizeof(vis));
			printf("矩阵深度递归搜索:    "); 
			dfs1(1);
			printf("\n");
		}else if(f == 2){
			memset(vis, 0, sizeof(vis));
			top = 0;
			printf("矩阵深度非递归搜索:  ");
			dfs2(1);
			printf("\n");
		}else if(f == 3){
			memset(vis, 0, sizeof(vis));
			left = right = 0;
			printf("矩阵广度搜索:        ");
			bfs1(1);
			printf("\n");
		}else if(f == 4){
			memset(vis, 0, sizeof(vis));
			printf("链表深度递归搜索:    ");
			dfs3(1);
			printf("\n");
		}else if(f == 5){
			memset(vis, 0, sizeof(vis));
			printf("链表深度非递归搜索:  ");
			top = 0;
			dfs4(1);
			printf("\n");
		}else if(f == 6){
			memset(vis, 0, sizeof(vis));
			left = right = 0;
			printf("链表广度搜索:        ");
			bfs2(1);
			printf("\n");
		}else if(f == 7){
			len = 0;
			printf("矩阵存储转链表存储\n");
			change1();
		}else if(f == 8){
			memset(map, 0, sizeof(map));
			printf("链表存储转矩阵存储\n"); 
			change2();
		}else if(!f){
			break;
		}
	} 
	printf("结束\n"); 
	return 0;
} 
