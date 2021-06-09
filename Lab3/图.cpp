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

void addedge(int x, int y){//�ڽ���������һ���� 
	next[++len] = son[x]; //��������ָ��x�����һ���� 
	son[x] = len;//����x�����һ���� 
	to[len] = y;//����ñߵ�ָ�� 
}

void change1(void){//�ڽӾ���ת�ڽ����� 
	for(int i = 1; i <= d; i++){
		for(int j = 1; j <= d; j++){
			if(map[i][j]){
				addedge(i, j);
			}
		}
	}
} 

void change2(void){//�ڽ�����ת�ڽӾ��� 
	for(int i = 1; i <= d; i++){
		for(int j = son[i]; j; j = next[j]){
			map[i][to[j]] = 1;
		}
	}
}

void dfs1(int x){//�ڽӾ���������������ݹ� 
	printf("%c ", x+64);
	vis[x] = 1;
	for(int i = d; i >= 1; i--){
		if(!vis[i] && map[x][i]){
			vis[i] = 1;
			dfs1(i);
		}
	}
}

void dfs2(int x){//�ڽӾ���������������ǵݹ� 
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

void dfs3(int x){//�ڽ�����������������ݹ� 
	printf("%c ", x+64);	
	vis[x] = 1;
	for(int i = son[x]; i; i = next[i]){
		if(!vis[to[i]]){
			vis[to[i]] = 1;
			dfs3(to[i]);
		}
	}
}

void dfs4(int x){//�ڽ�����������������ǵݹ� 
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

void bfs1(int x){//�ڽӾ������������� 
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
 
void bfs2(int x){//�ڽ��������������� 
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
		/*printf("���У�"); 
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
	printf("�ߵĸ���Ϊ��%d\n", b);
	scanf("%d", &d);
	printf("�������Ϊ��%d\n", d); 
	scanf("%d", &f);
	if(f == 1){
		printf("�����ڽӾ��󴢴�\n"); 
		memset(map, 0, sizeof(map));//�ڽӾ�������
		for(i = 1; i <= b; i++){
			scanf("%s %s", tmp1, tmp2);
			printf("��%d��Ϊ%s %s\n", i, tmp1, tmp2); 
			tmp1[0] -= 64;
			tmp2[0] -= 64;
			map[tmp1[0]][tmp2[0]] = 1;
			map[tmp2[0]][tmp1[0]] = 1;
		}
	}else if(f == 2){
		printf("�����ڽ�������\n"); 
		len = 0; 
		memset(next, 0, sizeof(next));
		memset(son, 0, sizeof(son));
		memset(to, 0, sizeof(to)); 
		for(i = 1; i <= b; i++){
			scanf("%s %s", tmp1, tmp2);
			printf("��%d��Ϊ%s %s\n", i, tmp1, tmp2); 
			tmp1[0] -= 64;
			tmp2[0] -= 64;
			addedge(tmp1[0], tmp2[0]);
			addedge(tmp2[0], tmp1[0]);		
		}
		/*for(i = 1; i <= d; i++){
			printf("%c������", i+64); 
			for(j = son[i]; j; j = next[j]){
				printf("%c ", to[j]+64);
			}
			printf("\n");
		}*/
	}
	printf("����0����\n"); 
	printf("����1������ȵݹ�����\n"); 
	printf("����2������ȷǵݹ�����\n");
	printf("����3����������\n");
	printf("����4������ȵݹ�����\n");
	printf("����5������ȷǵݹ�����\n");
	printf("����6����������\n");
	printf("����7����ת����\n");
	printf("����8����ת����\n"); 
	while(f){
		scanf("%d", &f);
		if(f == 1){
			memset(vis, 0, sizeof(vis));
			printf("������ȵݹ�����:    "); 
			dfs1(1);
			printf("\n");
		}else if(f == 2){
			memset(vis, 0, sizeof(vis));
			top = 0;
			printf("������ȷǵݹ�����:  ");
			dfs2(1);
			printf("\n");
		}else if(f == 3){
			memset(vis, 0, sizeof(vis));
			left = right = 0;
			printf("����������:        ");
			bfs1(1);
			printf("\n");
		}else if(f == 4){
			memset(vis, 0, sizeof(vis));
			printf("������ȵݹ�����:    ");
			dfs3(1);
			printf("\n");
		}else if(f == 5){
			memset(vis, 0, sizeof(vis));
			printf("������ȷǵݹ�����:  ");
			top = 0;
			dfs4(1);
			printf("\n");
		}else if(f == 6){
			memset(vis, 0, sizeof(vis));
			left = right = 0;
			printf("����������:        ");
			bfs2(1);
			printf("\n");
		}else if(f == 7){
			len = 0;
			printf("����洢ת����洢\n");
			change1();
		}else if(f == 8){
			memset(map, 0, sizeof(map));
			printf("����洢ת����洢\n"); 
			change2();
		}else if(!f){
			break;
		}
	} 
	printf("����\n"); 
	return 0;
} 
