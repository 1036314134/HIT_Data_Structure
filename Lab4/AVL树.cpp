#include<stdio.h>
#include<stdlib.h> 
#include<malloc.h>

struct AVLNode{
    int value;//权值 
    int balance;//平衡值 
    AVLNode* left;//左子树 
    AVLNode* right;//右子树 
    AVLNode* parent;//父节点 
};

struct AVLTree{
    AVLNode* root;
}tree;

int height(AVLNode* a){//求高度 
    if(!a){//空节点高度算0 
        return 0;
    }
    int rightheight = height(a->right);
    int leftheight = height(a->left);
    return rightheight > leftheight ? (rightheight+1) : (leftheight+1);
}

struct AVLNode* select(int value,AVLNode* root){//查询操作 
    if(!root){//树为完全空
        return 0;
    }
    if(root->value == value){//要查的是数根节点 
        return root;
    }
    if(root->value > value){//大于从左边查找
        if(root->left)
            return select(value, root->left);
        else
            return root;//没找到 
    }
    if(root->value < value){//大于从左边查找 
        if(root->right)
            return select(value,root->right);
        else
            return root;//没找到 
    }
}

void setBalance(AVLNode* a){//设置平衡值 
    if(a){
    	a->balance = height(a->right) - height(a->left);
	}      
}

struct AVLNode* turnLeft(AVLNode* a){//左旋 
    //左旋把a的父节点的子节点替换为b
    AVLNode* b = a->right;
    if(a->parent){//a与b换位置 
        if(a->parent->right == a){
            a->parent->right = b;
        }else{
            a->parent->left = b;
        }
    }
    b->parent = a->parent;
    //将a作为b的左子树，并将b的左子树作为a的右子树
    a->parent = b;
    a->right = b->left;
    b->left = a; 
    if(a->right){
    	a->right->parent = a;
	}  
    //重新设置a\b的balance值
    setBalance(a);
    setBalance(b);
    return b;
}
struct AVLNode* turnRight(AVLNode* a){//右旋 
    //右旋使a的父节点的子节点替换为b
    AVLNode* b = a->left;
    if(a->parent){//a与b换位置 
        if(a->parent->right == a){
            a->parent->right = b;
        }else{
            a->parent->left = b;
        }
    }
    b->parent = a->parent;
    //将b的右子树作为a的左子树，并将a作为b的右子树
    a->parent = b;
    a->left = b->right; 
    if(a->left){
    	a->left->parent = a;
	}  
    b->right = a;
    //重新设置a、b节点的balance值
    setBalance(a);
    setBalance(b);
    return b;
}    

struct AVLNode* turnLeftThenRight(AVLNode* a){//先左后右 
    a->left = turnLeft(a->left);
    return turnRight(a);
}

struct AVLNode* turnRightThenLeft(AVLNode* a){//先右后左 
    a->right = turnRight(a->right);
    return turnLeft(a);
}

//AVL树在insert或者del之后进行rebalance操作，从插入节点的父节点开始，逐层向上遍历进行rebalance，直到遍历到根节点。 
void rebalance(AVLNode* a){
    setBalance(a);
    if(a->balance == -2){          //如果左子树比右子树高2层，需要通过旋转来重新平衡
        if(a->left->balance <=0){ //如果左子节点的左子树比右子树高，则进行一次右旋；如果左子节点的右子树比左子树高，则先进行左旋，再进行右旋。
            a = turnRight(a);
        }else{
            a = turnLeftThenRight(a);
        }
    }else if(a->balance == 2){       //如果右子树比左子树高2层，需要通过旋转来重新平衡
        if(a->right->balance>=0){       //如果右子节点的右子树比左子树高，则进行一次左旋；如果右子节点的右子树比左子树低，则先进行右旋，再进行左旋。
            a = turnLeft(a);
        }else{
            a = turnRightThenLeft(a);
        }
    }
    if(a-> parent){
        rebalance(a->parent);
    }else{
        tree.root = a;
    }
}

void insert(int value, AVLNode* root){//插入节点 
    AVLNode* node = select(value, root);
    if(node == 0){
        tree.root = (AVLNode*)malloc(sizeof(AVLNode));
        tree.root->value = value;
        tree.root->left = tree.root->right = 0;
        tree.root->parent = 0;
        tree.root->balance = 0;
    }else if(node->value != value){
        if(node->value > value){//大于插左边 
            node->left = (AVLNode*)malloc(sizeof(AVLNode));
            node->left->value = value;
            node->left->left = node->left->right = 0;
            node->left->parent = node;
            node->left->balance = 0;
            rebalance(node);           //插入完成后进行rebalance
        }else if(node->value < value){//小于插右边 
            node->right = (AVLNode*)malloc(sizeof(AVLNode));
            node->right->value = value;
            node->right->left = node->right->right = 0;
            node->right->parent = node;
            node->right->balance = 0;
            rebalance(node);           //插入完成后进行rebalance
        }
    }
}

void delnodeifhas1childornot(AVLNode* a){
    if(a->parent == 0){//如果要删除根节点 
        if(a->left){ 
            tree.root = a->left;
            a->left->parent = 0;
        }else{
            tree.root = a->right;
            a->right->parent = 0;
        }
    }else{//不是根节点 
        if(a->parent->left == a){//要删除的节点是左儿子 
            if(a->left){//如果它有左儿子就将左儿子提上来 
                a->parent->left = a->left;
                a->left->parent = a->parent;
            }else{//没有就将右儿子提上来 
                a->parent->left = a->right;
                if(a->right){
                	a->right->parent = a->parent;
				} 
            }
        }else{//要删除的节点是右儿子 
            if(a->left){
                a->parent->right = a->left;
                a->left->parent = a->parent;
            }else{
                a->parent->right = a->right;
                if(a->right){
                	a->right->parent = a->parent;
				}      
            }
        }
        rebalance(a->parent);//重新平衡 
    }
}

struct AVLNode* getmin(AVLNode* a){//找到该节点子树中值最小的节点 
    if(a->left)//遍历左儿子 
        getmin(a->left);
    else
        return a;
} 

void delnodeifhas2child(AVLNode* a){
    AVLNode* after = getmin(a->right);//把该删除的节点的右子树的子树中最小的找出来 
    a->value = after->value;//替换该节点 
    delnodeifhas1childornot(after);//删除最小的节点 
}

void del(int value, AVLNode* root){//删除 
    AVLNode* node = select(value, root);
    if(node->value == value){//确定找到该节点而不是根节点 
        if(node->left && node->right){//要删除的节点有两个子树的情况 
            delnodeifhas2child(node);
        }else{//要删除的节点只有一个子树的情况 
            delnodeifhas1childornot(node);
        }
    }
}

void zhongxudp(AVLNode* root){
	if(root->left){
		zhongxudp(root->left);
	}
	printf("%d ", root->value);
	if(root->right){
		zhongxudp(root->right);
	}
	return;
}

void xianxudp(AVLNode* root){
	printf("%d ", root->value);
	if(root->left){
		zhongxudp(root->left);
	}
	if(root->right){
		zhongxudp(root->right);
	}
	return;
}

void find(int value, AVLNode* root){
	AVLNode* node = select(value, root);
	if(node->value == value){//找到节点 
		if(node->parent){
			printf("它的父亲是%d,", node->parent->value);
		}else{
			printf("它没有父亲,");
		}
		if(node->left){
			printf("它的左儿子是%d,", node->left->value);
		}else{
			printf("它没有左儿子，"); 
		}
		if(node->right){
			printf("它的右儿子是%d。\n", node->right->value);
		}else{
			printf("它没有右儿子。\n"); 
		}
	}else{
		printf("没找到该节点。\n"); 
	} 
}


int main(void){
	freopen("zuo.txt","r",stdin);
	//freopen("you.txt","r",stdin);
	//freopen("zuoyou.txt","r",stdin);
	//freopen("youzuo.txt","r",stdin);
	int f, tmp;
	printf("输入1插入节点\n");
	printf("输入2删除节点\n");
	printf("输入3查找节点\n");
	printf("输入4中序搜索\n");
	printf("输入5前序搜索\n");
	printf("输入0结束程序\n\n"); 
	while(1){
		scanf("%d", &f);
		if(!f){
			printf("程序结束");
			break;
		}
		switch(f){
			case 1:
				scanf("%d", &tmp);
				insert(tmp, tree.root);
				printf("插入了%d\n", tmp);
				break;
			case 2:
				scanf("%d", &tmp);
				del(tmp, tree.root);
				printf("删除了%d\n", tmp);
				break;
			case 3:
				scanf("%d", &tmp);
				printf("查找%d,", tmp);
				find(tmp, tree.root); 
				break;
			case 4:
				printf("中序搜索："); 
				zhongxudp(tree.root);
				printf("\n");
				break;
			case 5:
				printf("先序搜索：");
				xianxudp(tree.root);
				printf("\n"); 
				break;
		}
	}
	return 0;
}
