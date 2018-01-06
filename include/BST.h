#ifndef _BINARY_SEARCH_TREE_HPP_
#define _BINARY_SEARCH_TREE_HPP_

#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>  
using namespace std;

struct Message{
    char* key;            // 关键字(键值)
    char* tbl_name;
    vector<char*> attribute;
    vector<OP> op;
    vector<char*> value;
};

void print_order(char* n)  
{  
    cout<<n<<" ";  
}  

void print_order_int(int n)  
{  
    cout<<n<<" ";  
}  

template <class T>
class BSTNode{
    public:
        T key;            // 关键字(键值)
        T tbl_name;
        vector<T> attribute;
        vector<OP> op;
        vector<T> value;
        BSTNode *left;    // 左孩子
        BSTNode *right;    // 右孩子
        BSTNode *parent;// 父结点

        BSTNode(T key, T tbl_name, vector<T> attribute, vector<OP> op, vector<T> value, BSTNode *p, BSTNode *l, BSTNode *r):
            key(key),tbl_name(tbl_name),attribute(attribute),op(op),value(value),parent(),left(l),right(r) {}
};

template <class T>
class BSTree {
    private:
        BSTNode<T> *mRoot;    // 根结点

    public:
        BSTree();
        ~BSTree();
        // 前序遍历"二叉树"
        void preOrder();
        // 中序遍历"二叉树"
        void inOrder();
        // 后序遍历"二叉树"
        void postOrder();
        void insert_touying(T tbl_name, vector<T> attribute);
        void insert_xuanze(T tbl_name, vector<T> attribute, vector<OP> op, vector<T> value);
        void insert_lianjie(OP op, T tbl_name1, T attr1, T tbl_name2, T attr2, int flag);
        void insert_kashiji(vector<T> tbls);
        // 销毁二叉树
        void destroy();
        // (递归实现)查找"二叉树"中键值为key的节点
        BSTNode<T>* search(T key);
        // 打印二叉树
        void print();
        void get(struct Message message[]);
        void get_easy(vector<T>* xxx);
    private:
        // 前序遍历"二叉树"
        void preOrder(BSTNode<T>* tree) const;
        // 中序遍历"二叉树"
        void inOrder(BSTNode<T>* tree) const;
        // 后序遍历"二叉树"
        void postOrder(BSTNode<T>* tree) const;
        BSTNode<T>* search(BSTNode<T>* x, T key) const;
        void insert_touying(BSTNode<T>* &tree, BSTNode<T>* z);
        void insert_lianjie(BSTNode<T>* &tree, BSTNode<T>* z1, BSTNode<T>* z2, BSTNode<T>* z3, int flag);
        void insert_kashiji(BSTNode<T>* &tree, BSTNode<T>* z);
        // 销毁二叉树
        void destroy(BSTNode<T>* &tree);

        // 打印二叉树
        void print(BSTNode<T>* tree, T key, int direction);   
        void get(BSTNode<T>* tree, struct Message message[]) const;
        void get_easy(BSTNode<T>* tree, vector<T>* xxx) const;
};


/* 
 * 构造函数
 */
template <class T>
BSTree<T>::BSTree():mRoot(NULL)
{
}

/* 
 * 析构函数
 */
template <class T>
BSTree<T>::~BSTree() 
{
    destroy();
}

/*
 * 前序遍历"二叉树"
 */
template <class T>
void BSTree<T>::preOrder(BSTNode<T>* tree) const
{
    if(tree != NULL)
    {
        cout<< tree->key << " " ;
        preOrder(tree->left);
        preOrder(tree->right);
    }
}

template <class T>
void BSTree<T>::preOrder() 
{
    preOrder(mRoot);
}

/*
 * 中序遍历"二叉树"
 */
template <class T>
void BSTree<T>::inOrder(BSTNode<T>* tree) const
{
    if(tree != NULL)
    {
        inOrder(tree->left);
        cout<< tree->key << " " ;
        inOrder(tree->right);
    }
}

template <class T>
void BSTree<T>::inOrder() 
{
    inOrder(mRoot);
}

/*
 * 后序遍历"二叉树"
 */
template <class T>
void BSTree<T>::postOrder(BSTNode<T>* tree) const
{
    if(tree != NULL)
    {
        postOrder(tree->left);
        postOrder(tree->right);
        if (tree->tbl_name != NULL)
            cout<<"key: " <<tree->key << " " << "tbl: "<<tree->tbl_name<<" " ;
        else
            cout<< "key: " <<tree->key<< " " ;
        cout<<"attr: ";
        for_each(tree->attribute.begin(),tree->attribute.end(),print_order);
        cout<<"op: ";
        for_each(tree->op.begin(),tree->op.end(),print_order_int);
        cout<<"value: ";
        for_each(tree->value.begin(),tree->value.end(),print_order);
        cout<<endl;
    }
}

template <class T>
void BSTree<T>::postOrder() 
{
    postOrder(mRoot);
}


template <class T>
void BSTree<T>::get(BSTNode<T>* tree, struct Message message[]) const
{
    if(tree != NULL)
    {
        get(tree->left, message);
        get(tree->right, message);
        int i = 0;
        for(i; i<100; i++){
            if (message[i].key == NULL){// and message[i].key == ""){
                break;
            }
        }
        message[i].key = tree->key;
        message[i].tbl_name = tree->tbl_name;
        message[i].op = tree->op;
        message[i].attribute = tree->attribute;
        message[i].value = tree->value;

        
        //(*xxx).insert((*xxx).end(), tree->key);
    }
}

template <class T>
void BSTree<T>::get(struct Message message[]) 
{
    get(mRoot, message);
}

template <class T>
void BSTree<T>::get_easy(BSTNode<T>* tree, vector<T>* xxx) const
{
    if(tree != NULL)
    {
        get_easy(tree->left, xxx);
        get_easy(tree->right, xxx);
        
        (*xxx).insert((*xxx).end(), tree->key);
    }
}

template <class T>
void BSTree<T>::get_easy(vector<T>* xxx) 
{
    get_easy(mRoot, xxx);
}


/*
 * (递归实现)查找"二叉树x"中键值为key的节点
 */
template <class T>
BSTNode<T>* BSTree<T>::search(BSTNode<T>* x, T key) const
{
    if (x->key == key)
        return x;
    if (x->left != NULL)
        if (search(x->left, key) != NULL) 
            return search(x->left, key);
    if (x->right != NULL)
        if (search(x->right, key) != NULL) 
            return search(x->right, key);
    return NULL;
}

template <>
BSTNode<char*>* BSTree<char*>::search(BSTNode<char*>* x, char* key) const
{
    if (strcmp(x->key, key) == 0)
        return x;
    if (x->left != NULL)
        if (search(x->left, key) != NULL) 
            return search(x->left, key);
    if (x->right != NULL)
        if (search(x->right, key) != NULL) 
            return search(x->right, key);
    return NULL;
}

template <class T>
BSTNode<T>* BSTree<T>::search(T key) 
{
    search(mRoot, key);
}






template <class T>
void BSTree<T>::insert_touying(T tbl_name, vector<T> attribute)
{
    BSTNode<T> *z=NULL;
    // 如果新建结点失败，则返回。
    vector<OP> op;
    vector<T> value;
    if ((z=new BSTNode<T>("π",tbl_name,attribute,op,value,NULL,NULL,NULL)) == NULL)
        return ;
    insert_touying(mRoot, z);
}

template <class T>
void BSTree<T>::insert_touying(BSTNode<T>* &tree, BSTNode<T>* z)
{
    BSTNode<T> *y = NULL;
    BSTNode<T> *x = tree;

    // 查找z的插入位置
    while (x != NULL)
    {
        y = x;
        x = x->left;
    }

    z->parent = y;
    if (y==NULL)
        tree = z;
    else
        y->left = z;
}

template <class T>
void BSTree<T>::insert_xuanze(T tbl_name, vector<T> attribute, vector<OP> op, vector<T> value)
{
    BSTNode<T> *z=NULL;
    // 如果新建结点失败，则返回。
    if ((z=new BSTNode<T>("σ",tbl_name,attribute,op,value,NULL,NULL,NULL)) == NULL)
        return ;
    insert_touying(mRoot, z);
}

template <class T>
void BSTree<T>::insert_kashiji(BSTNode<T>* &tree, BSTNode<T>* z)
{
    BSTNode<T> *y = NULL;
    BSTNode<T> *x = tree;
    // 查找z的插入位置
    while (x->key != "⋈" and x->key != "x")
    {
        y = x;
        x = x->left;
        if (x==NULL or(x->key != "⋈" and x->key != "x" and x-> key !="π" and x-> key !="σ"))
            break;
    }
    BSTNode<T> *join=NULL;
    vector<T> attribute1;
    vector<OP> op1;
    vector<T> value1;    
    if ((join=new BSTNode<T>("x",NULL,attribute1,op1,value1,NULL,NULL,NULL)) == NULL)
        return ;
    if (x == NULL){
        z -> parent = y;
        y->left =z;        
    }
    else if (x->key != "⋈" and x->key != "x" and x-> key !="π" and x-> key !="σ"){
        join -> parent = y;
        y->left =join;
        x -> parent = join;
        join -> left = x;
        z -> parent = join;
        join ->right = z;             
    }
    else{
        join -> parent = y;
        y->left =join;
        x -> parent = join;
        join -> left = x;
        z -> parent = join;
        join ->right = z;          
    }
}

template <class T>
void BSTree<T>::insert_kashiji(vector<T> tbls)
{
    int count = tbls.size();
    for (int i = 0; i < count;i++)
    {
        BSTNode<T> *find_tbl = this->search(tbls[i]);
        if (find_tbl == NULL){
            vector<T> attribute;
            vector<OP> op;
            vector<T> value;  
            BSTNode<T> *z=NULL;
            if ((z=new BSTNode<T>(tbls[i],tbls[i],attribute,op,value,NULL,NULL,NULL)) == NULL)
                return ;
            insert_kashiji(mRoot, z);
        }
    }
}


template <class T>
void BSTree<T>::insert_lianjie(BSTNode<T>* &tree, BSTNode<T>* z1, BSTNode<T>* z2, BSTNode<T>* z3, int flag)
{
    if (flag==0){
        BSTNode<T> *y = NULL;
        BSTNode<T> *x = tree;

        // 查找z的插入位置
        while (x != NULL)
        {
            y = x;
            x = x->left;
        }

        z1->parent = y;
        if (y==NULL)
            tree = z1;
        else
            y->left = z1;
        z2->parent = z1;
        z3->parent = z1;
        z1->left = z2;
        z1->right = z3;
    }
    else {
        BSTNode<T> *find_z2 = this->search(z2->key);
        BSTNode<T> *find_z3 = this->search(z3->key);
        if (find_z2 != NULL and find_z3 != NULL){
            cout<<"1"<<endl;
        }
        if (find_z2 == NULL and find_z3 != NULL){
            cout<<"2"<<endl;
            find_z3->key = z1->key;
            find_z3->tbl_name = NULL;
            find_z3->attribute = z1->attribute;
            find_z3->op = z1->op;
            find_z3->value = z1->value;
            z2->parent = find_z3;
            z3->parent = find_z3;
            find_z3->left = z2;
            find_z3->right = z3;            
        }    
        if (find_z2 != NULL and find_z3 == NULL){
            cout<<"3"<<endl;
            find_z2->key = z1->key;
            find_z2->tbl_name = NULL;
            find_z2->attribute = z1->attribute;
            find_z2->op = z1->op;
            find_z2->value = z1->value;
            z2->parent = find_z2;
            z3->parent = find_z2;
            find_z2->left = z2;
            find_z2->right = z3;            
        }
        if (find_z2 == NULL and find_z3 == NULL){
            cout<<"4"<<endl;
            BSTNode<T> *y = NULL;
            BSTNode<T> *x = tree;
            // 查找z的插入位置
            while (x->key != "⋈" and x->key != "x")
            {
                y = x;
                x = x->left;
            }
            BSTNode<T> *join=NULL;
            vector<T> attribute;
            vector<OP> op;
            vector<T> value;    
            if ((join=new BSTNode<T>("x",NULL,attribute,op,value,NULL,NULL,NULL)) == NULL)
                return ;
            join -> parent = y;
            y->left =join;
            x -> parent = join;
            join -> left = x;
            z1 -> parent = join;
            join ->right = z1;
            z2->parent = z1;
            z3->parent = z1;
            z1->left = z2;
            z1->right = z3;              
        }         
    }
}




template <class T>
void BSTree<T>::insert_lianjie(OP op, T tbl_name1, T attr1, T tbl_name2, T attr2, int flag)
{
    BSTNode<T> *z1=NULL;
    BSTNode<T> *z2=NULL;
    BSTNode<T> *z3=NULL;
    vector<T> attribute1;
    attribute1.insert(attribute1.begin(), attr1);
    vector<T> attribute2;
    attribute2.insert(attribute2.begin(), attr1);
    vector<T> attribute3;
    attribute3.insert(attribute3.begin(), attr2);
    vector<OP> op1;
    op1.insert(op1.begin(), op);
    vector<OP> op2;
    vector<OP> op3;
    vector<T> value1;
    value1.insert(value1.begin(), attr2);
    vector<T> value2; 
    vector<T> value3;  
    // 如果新建结点失败，则返回。
    if ((z1=new BSTNode<T>("⋈",NULL,attribute1,op1,value1,NULL,NULL,NULL)) == NULL)
        return ;
    if ((z2=new BSTNode<T>(tbl_name1,tbl_name1,attribute2,op2,value2,NULL,NULL,NULL)) == NULL)
        return ;
    if ((z3=new BSTNode<T>(tbl_name2,tbl_name2,attribute3,op3,value3,NULL,NULL,NULL)) == NULL)
        return ;
    insert_lianjie(mRoot, z1, z2, z3, flag);
}


/*
 * 销毁二叉树
 */
template <class T>
void BSTree<T>::destroy(BSTNode<T>* &tree)
{
    if (tree==NULL)
        return ;

    if (tree->left != NULL)
        return destroy(tree->left);
    if (tree->right != NULL)
        return destroy(tree->right);

    delete tree;
    tree=NULL;
}

template <class T>
void BSTree<T>::destroy()
{
    destroy(mRoot);
}

/*
 * 打印"二叉查找树"
 *
 * key        -- 节点的键值 
 * direction  --  0，表示该节点是根节点;
 *               -1，表示该节点是它的父结点的左孩子;
 *                1，表示该节点是它的父结点的右孩子。
 */
template <class T>
void BSTree<T>::print(BSTNode<T>* tree, T key, int direction)
{
    if(tree != NULL)
    {
        if(direction==0)    // tree是根节点
            cout << setw(2) << tree->key << " is root" << endl;
        else                // tree是分支节点
            cout << setw(2) << tree->key << " is " << setw(2) << key << "'s "  << setw(12) << (direction==1?"right child" : "left child") << endl;

        print(tree->left, tree->key, -1);
        print(tree->right,tree->key,  1);
    }
}

template <class T>
void BSTree<T>::print()
{
    if (mRoot != NULL)
        print(mRoot, mRoot->key, 0);
}

#endif

