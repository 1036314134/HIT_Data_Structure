#include<stdio.h>
#include<stdlib.h> 
#include<malloc.h>

struct AVLNode{
    int value;//Ȩֵ 
    int balance;//ƽ��ֵ 
    AVLNode* left;//������ 
    AVLNode* right;//������ 
    AVLNode* parent;//���ڵ� 
};

struct AVLTree{
    AVLNode* root;
}tree;

int height(AVLNode* a){//��߶� 
    if(!a){//�սڵ�߶���0 
        return 0;
    }
    int rightheight = height(a->right);
    int leftheight = height(a->left);
    return rightheight > leftheight ? (rightheight+1) : (leftheight+1);
}

struct AVLNode* select(int value,AVLNode* root){//��ѯ���� 
    if(!root){//��Ϊ��ȫ��
        return 0;
    }
    if(root->value == value){//Ҫ����������ڵ� 
        return root;
    }
    if(root->value > value){//���ڴ���߲���
        if(root->left)
            return select(value, root->left);
        else
            return root;//û�ҵ� 
    }
    if(root->value < value){//���ڴ���߲��� 
        if(root->right)
            return select(value,root->right);
        else
            return root;//û�ҵ� 
    }
}

void setBalance(AVLNode* a){//����ƽ��ֵ 
    if(a){
    	a->balance = height(a->right) - height(a->left);
	}      
}

struct AVLNode* turnLeft(AVLNode* a){//���� 
    //������a�ĸ��ڵ���ӽڵ��滻Ϊb
    AVLNode* b = a->right;
    if(a->parent){//a��b��λ�� 
        if(a->parent->right == a){
            a->parent->right = b;
        }else{
            a->parent->left = b;
        }
    }
    b->parent = a->parent;
    //��a��Ϊb��������������b����������Ϊa��������
    a->parent = b;
    a->right = b->left;
    b->left = a; 
    if(a->right){
    	a->right->parent = a;
	}  
    //��������a\b��balanceֵ
    setBalance(a);
    setBalance(b);
    return b;
}
struct AVLNode* turnRight(AVLNode* a){//���� 
    //����ʹa�ĸ��ڵ���ӽڵ��滻Ϊb
    AVLNode* b = a->left;
    if(a->parent){//a��b��λ�� 
        if(a->parent->right == a){
            a->parent->right = b;
        }else{
            a->parent->left = b;
        }
    }
    b->parent = a->parent;
    //��b����������Ϊa��������������a��Ϊb��������
    a->parent = b;
    a->left = b->right; 
    if(a->left){
    	a->left->parent = a;
	}  
    b->right = a;
    //��������a��b�ڵ��balanceֵ
    setBalance(a);
    setBalance(b);
    return b;
}    

struct AVLNode* turnLeftThenRight(AVLNode* a){//������� 
    a->left = turnLeft(a->left);
    return turnRight(a);
}

struct AVLNode* turnRightThenLeft(AVLNode* a){//���Һ��� 
    a->right = turnRight(a->right);
    return turnLeft(a);
}

//AVL����insert����del֮�����rebalance�������Ӳ���ڵ�ĸ��ڵ㿪ʼ��������ϱ�������rebalance��ֱ�����������ڵ㡣 
void rebalance(AVLNode* a){
    setBalance(a);
    if(a->balance == -2){          //�������������������2�㣬��Ҫͨ����ת������ƽ��
        if(a->left->balance <=0){ //������ӽڵ�����������������ߣ������һ��������������ӽڵ�����������������ߣ����Ƚ����������ٽ���������
            a = turnRight(a);
        }else{
            a = turnLeftThenRight(a);
        }
    }else if(a->balance == 2){       //�������������������2�㣬��Ҫͨ����ת������ƽ��
        if(a->right->balance>=0){       //������ӽڵ�����������������ߣ������һ��������������ӽڵ�����������������ͣ����Ƚ����������ٽ���������
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

void insert(int value, AVLNode* root){//����ڵ� 
    AVLNode* node = select(value, root);
    if(node == 0){
        tree.root = (AVLNode*)malloc(sizeof(AVLNode));
        tree.root->value = value;
        tree.root->left = tree.root->right = 0;
        tree.root->parent = 0;
        tree.root->balance = 0;
    }else if(node->value != value){
        if(node->value > value){//���ڲ���� 
            node->left = (AVLNode*)malloc(sizeof(AVLNode));
            node->left->value = value;
            node->left->left = node->left->right = 0;
            node->left->parent = node;
            node->left->balance = 0;
            rebalance(node);           //������ɺ����rebalance
        }else if(node->value < value){//С�ڲ��ұ� 
            node->right = (AVLNode*)malloc(sizeof(AVLNode));
            node->right->value = value;
            node->right->left = node->right->right = 0;
            node->right->parent = node;
            node->right->balance = 0;
            rebalance(node);           //������ɺ����rebalance
        }
    }
}

void delnodeifhas1childornot(AVLNode* a){
    if(a->parent == 0){//���Ҫɾ�����ڵ� 
        if(a->left){ 
            tree.root = a->left;
            a->left->parent = 0;
        }else{
            tree.root = a->right;
            a->right->parent = 0;
        }
    }else{//���Ǹ��ڵ� 
        if(a->parent->left == a){//Ҫɾ���Ľڵ�������� 
            if(a->left){//�����������Ӿͽ������������ 
                a->parent->left = a->left;
                a->left->parent = a->parent;
            }else{//û�оͽ��Ҷ��������� 
                a->parent->left = a->right;
                if(a->right){
                	a->right->parent = a->parent;
				} 
            }
        }else{//Ҫɾ���Ľڵ����Ҷ��� 
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
        rebalance(a->parent);//����ƽ�� 
    }
}

struct AVLNode* getmin(AVLNode* a){//�ҵ��ýڵ�������ֵ��С�Ľڵ� 
    if(a->left)//��������� 
        getmin(a->left);
    else
        return a;
} 

void delnodeifhas2child(AVLNode* a){
    AVLNode* after = getmin(a->right);//�Ѹ�ɾ���Ľڵ������������������С���ҳ��� 
    a->value = after->value;//�滻�ýڵ� 
    delnodeifhas1childornot(after);//ɾ����С�Ľڵ� 
}

void del(int value, AVLNode* root){//ɾ�� 
    AVLNode* node = select(value, root);
    if(node->value == value){//ȷ���ҵ��ýڵ�����Ǹ��ڵ� 
        if(node->left && node->right){//Ҫɾ���Ľڵ���������������� 
            delnodeifhas2child(node);
        }else{//Ҫɾ���Ľڵ�ֻ��һ����������� 
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
	if(node->value == value){//�ҵ��ڵ� 
		if(node->parent){
			printf("���ĸ�����%d,", node->parent->value);
		}else{
			printf("��û�и���,");
		}
		if(node->left){
			printf("�����������%d,", node->left->value);
		}else{
			printf("��û������ӣ�"); 
		}
		if(node->right){
			printf("�����Ҷ�����%d��\n", node->right->value);
		}else{
			printf("��û���Ҷ��ӡ�\n"); 
		}
	}else{
		printf("û�ҵ��ýڵ㡣\n"); 
	} 
}


int main(void){
	freopen("zuo.txt","r",stdin);
	//freopen("you.txt","r",stdin);
	//freopen("zuoyou.txt","r",stdin);
	//freopen("youzuo.txt","r",stdin);
	int f, tmp;
	printf("����1����ڵ�\n");
	printf("����2ɾ���ڵ�\n");
	printf("����3���ҽڵ�\n");
	printf("����4��������\n");
	printf("����5ǰ������\n");
	printf("����0��������\n\n"); 
	while(1){
		scanf("%d", &f);
		if(!f){
			printf("�������");
			break;
		}
		switch(f){
			case 1:
				scanf("%d", &tmp);
				insert(tmp, tree.root);
				printf("������%d\n", tmp);
				break;
			case 2:
				scanf("%d", &tmp);
				del(tmp, tree.root);
				printf("ɾ����%d\n", tmp);
				break;
			case 3:
				scanf("%d", &tmp);
				printf("����%d,", tmp);
				find(tmp, tree.root); 
				break;
			case 4:
				printf("����������"); 
				zhongxudp(tree.root);
				printf("\n");
				break;
			case 5:
				printf("����������");
				xianxudp(tree.root);
				printf("\n"); 
				break;
		}
	}
	return 0;
}
