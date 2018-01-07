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


struct table
{
    char* name;
    double tuple;
    vector<char*> attr;
    map<string,int> V_attr;
};

void PrintWhiteSpaces(int num)  
{  
  for(int i=0; i<num; ++i)  
    cout << " ";  
} 
static vector<table> tb_totle;
static table tb1;
static table tb2;
static table tb3;
static table tb4;
static table tb5;
static table tb6;
static table tb7;
static table tb8;
static table tb_con;


vector<char*> jiaoji(vector<table> &tb,int i,int j)
{
    vector<char*>  tb_jiaoji;
    table table1 = tb[i];
    table table2 = tb[j];
    for(int i = 0;i < table1.attr.size();i++)
    {
        for(int j = 0;j < table2.attr.size();j++)
        {
            // cout<< "i" << table1.attr[i]<<endl;
            // cout<< "j" << table2.attr[j]<<endl;
            if(strcmp(table1.attr[i],table2.attr[j]) == 0)
                tb_jiaoji.insert(tb_jiaoji.begin(),table1.attr[i]);
        }
    }
    return tb_jiaoji;
}

double compute_loss(vector<table> &tb,int i,int j)
{

    //相关信息需要统计信息，T(R),B(R),V(R,X),B(R)可以不要吧
    //找交集
    vector<char*> tb_common;
    tb_common = jiaoji(tb,i,j);
    // cout << tb_common.size() << endl;

    if(tb_common.size() == 0)
        return tb[i].tuple*tb[j].tuple;
    else{
        double temp = 1;
        double max ;
        for(int k=0;k < tb_common.size();k++)
        {
            max = tb[i].V_attr[tb_common[k]]>tb[j].V_attr[tb_common[k]]?tb[i].V_attr[tb_common[k]]:tb[j].V_attr[tb_common[k]];
            temp *= max; 
            // cout << temp << endl;
        }
        return tb[i].tuple*tb[j].tuple/temp;
    }
    return 0;
}

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
        void optimize();
        void PrintTree();
        void Phy_optimize();
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
        void optimize(BSTNode<T>* tree);
        bool rightxuanze(BSTNode<T>* tree);
        bool righttouying(BSTNode<T>* tree);
        void optimizetouiying(BSTNode<T>* tree);
        void PrintTree(BSTNode<T>* tree);
        int  MaxLevel(BSTNode<T>* tree);
        bool IsAllElementsNULL(const vector<BSTNode<T>*> &nodes);
        void PrintNode(vector<BSTNode<T>*> &nodes,int level, int max_level);
        void Phy_optimize(BSTNode<T>* tree);
        void get_tb(BSTNode<T>* tree,vector<BSTNode<T>*> &nodes);
        BSTNode<T>* generate_new_tree(vector<table> &tb_right,BSTNode<T>* last_connects);
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


//优化查询树，先选择下移，再投影下移，投影下移写在函数里方便递归
template <class T>
void BSTree<T>::optimize(BSTNode<T>* tree)
{ 
    //选择下移
   while(1){
   BSTNode<T> *find_ob =  search(tree,"σ");
   if(find_ob == NULL){
        break;
    }
   if(find_ob!=NULL)
   {
   bool flag = rightxuanze(find_ob);
   if(flag == true)
     break;
   // cout<< "key  " << find_ob->key << "  tbl_name  " << find_ob->tbl_name ;
   // cout<<" attr: ";
   //      for_each(find_ob->attribute.begin(),find_ob->attribute.end(),print_order);
   //      cout<<"op: ";
   //      for_each(find_ob->op.begin(),find_ob->op.end(),print_order_int);
   //      cout<<"value: ";
   //      for_each(find_ob->value.begin(),find_ob->value.end(),print_order);
   //      cout<<endl;
   BSTNode<T> *find_target =  search(tree,find_ob->tbl_name);
   // cout<< "key  " << find_target->key << "  tbl_name  " << find_target->tbl_name ;
   // cout<<" attr: ";
   //      for_each(find_target->attribute.begin(),find_target->attribute.end(),print_order);
   //      cout<<endl;
   find_ob->parent->left = find_ob->left;
   find_ob->left->parent = find_ob->parent;
   if(find_target->parent->left == find_target)
   {
    find_ob->parent = find_target->parent;
    find_ob->left = find_target;
    find_target->parent->left = find_ob;
    find_target->parent = find_ob;
   }
   else if(find_target->parent->right == find_target)
   {
    find_ob->parent = find_target->parent;
    find_ob->right = find_target;
    find_ob->left = NULL;
    find_target->parent->right = find_ob;
    find_target->parent = find_ob;
   }
   }

  }
  //投影下移
  optimizetouiying(mRoot);
  
}

template <class T>
void BSTree<T>::optimizetouiying(BSTNode<T>* tree)
{
    BSTNode<T> *find_ob =  search(tree,"π");
    if( find_ob!=NULL && !righttouying(find_ob))
    { 
     // cout<< "key  " << find_ob->key;
     // cout<<" attr: ";
     //    for_each(find_ob->attribute.begin(),find_ob->attribute.end(),print_order);
     //    cout<<"op: ";
     //    for_each(find_ob->op.begin(),find_ob->op.end(),print_order_int);
     //    cout<<"value: ";
     //    for_each(find_ob->value.begin(),find_ob->value.end(),print_order);
     //    cout<<endl;
     if(find_ob->left != NULL && strcmp(find_ob->left->key,"x") == 0)
     {
        BSTNode<T>* Ty1_left = NULL;
        BSTNode<T>* Ty1_right = NULL;
        BSTNode<T>* leftchild = find_ob->left;
        vector<T> attribute1(find_ob->attribute);
        vector<T> attribute2(find_ob->attribute);
        vector<OP> op1;
        vector<OP> op2;
        vector<T> value1;
        vector<T> value2;
        //这里目前是把所有的属性都下移，因为不知道每个表的属性，就假设所有表都含有我们要查的属性，暂时这样下移，以后再改
        if ((Ty1_left=new BSTNode<T>("π",NULL,attribute1,op1,value1,NULL,NULL,NULL)) == NULL)
           return ;
        if ((Ty1_right=new BSTNode<T>("π",NULL,attribute2,op2,value2,NULL,NULL,NULL)) == NULL)
           return ;
        Ty1_left->parent = leftchild;
        Ty1_left->left = leftchild->left;
        leftchild->left->parent = Ty1_left;
        leftchild->left = Ty1_left;
        Ty1_right->parent = leftchild;
        Ty1_right->right = leftchild->right;
        leftchild->right->parent = Ty1_right;
        leftchild->right = Ty1_right;
        if(!righttouying(leftchild->left))
           optimizetouiying(leftchild->left);
        if(!righttouying(leftchild->right))
           optimizetouiying(leftchild->right);
     }else if(find_ob->right != NULL && strcmp(find_ob->right->key,"x") == 0)
     {
         BSTNode<T>* Ty1_left = NULL;
        BSTNode<T>* Ty1_right = NULL;
        BSTNode<T>* rightchild = find_ob->right;
        vector<T> attribute1(find_ob->attribute);
        vector<T> attribute2(find_ob->attribute);
        vector<OP> op1;
        vector<OP> op2;
        vector<T> value1;
        vector<T> value2;
        if ((Ty1_left=new BSTNode<T>("π",NULL,attribute1,op1,value1,NULL,NULL,NULL)) == NULL)
           return ;
        if ((Ty1_right=new BSTNode<T>("π",NULL,attribute2,op2,value2,NULL,NULL,NULL)) == NULL)
           return ;
        Ty1_left->parent = rightchild;
        Ty1_left->left = rightchild->left;
        rightchild->left->parent = Ty1_left;
        rightchild->left = Ty1_left;
        Ty1_right->parent = rightchild;
        Ty1_right->right = rightchild->right;
        rightchild->right->parent = Ty1_right;
        rightchild->right = Ty1_right;
        if(!righttouying(rightchild->left))
           optimizetouiying(rightchild->left);
        if(!righttouying(rightchild->right))
           optimizetouiying(rightchild->right);
      }
      else if(find_ob->left != NULL && strcmp(find_ob->left->key,"⋈") == 0)
      {
        BSTNode<T>* Ty1_left = NULL;
        BSTNode<T>* Ty1_right = NULL;
        BSTNode<T>* leftchild = find_ob->left;
        vector<T> attribute1(find_ob->attribute);
        vector<T> attribute2(find_ob->attribute);
        vector<OP> op1;
        vector<OP> op2;
        vector<T> value1;
        vector<T> value2; 
        int flag = 0;
        for(int i = 0;i < attribute1.size();i++){
            if(strcmp(attribute1[i],leftchild->attribute[0]) == 0)
                flag = 1;
            else
                continue;
        }
        if (flag == 0) //没找到
        {
           attribute1.insert(attribute1.end(),leftchild->attribute.begin(),leftchild->attribute.end());
           attribute2.insert(attribute2.end(),leftchild->attribute.begin(),leftchild->attribute.end());
        }
        if ((Ty1_left=new BSTNode<T>("π",NULL,attribute1,op1,value1,NULL,NULL,NULL)) == NULL)
           return ;
        if ((Ty1_right=new BSTNode<T>("π",NULL,attribute2,op2,value2,NULL,NULL,NULL)) == NULL)
           return ;
        Ty1_left->parent = leftchild;
        Ty1_left->left = leftchild->left;
        leftchild->left->parent = Ty1_left;
        leftchild->left = Ty1_left;
        Ty1_right->parent = leftchild;
        Ty1_right->right = leftchild->right;
        leftchild->right->parent = Ty1_right;
        leftchild->right = Ty1_right;
        if(!righttouying(leftchild->left))
           optimizetouiying(leftchild->left);
        if(!righttouying(leftchild->right))
           optimizetouiying(leftchild->right);
      }
      else if(find_ob->right != NULL && strcmp(find_ob->right->key,"⋈") == 0)
      {
         BSTNode<T>* Ty1_left = NULL;
        BSTNode<T>* Ty1_right = NULL;
        BSTNode<T>* rightchild = find_ob->right;
        vector<T> attribute1(find_ob->attribute);
        vector<T> attribute2(find_ob->attribute);
        vector<OP> op1;
        vector<OP> op2;
        vector<T> value1;
        vector<T> value2;
        int flag = 0;
        for(int i = 0;i < attribute1.size();i++){
            if(strcmp(attribute1[i],rightchild->attribute[0]) == 0)
                flag = 1;
            else
                continue;
        }
        if (flag == 0) //没找到
        {
           attribute1.insert(attribute1.end(),rightchild->attribute.begin(),rightchild->attribute.end());
           attribute2.insert(attribute2.end(),rightchild->attribute.begin(),rightchild->attribute.end());
        }
        if ((Ty1_left=new BSTNode<T>("π",NULL,attribute1,op1,value1,NULL,NULL,NULL)) == NULL)
           return ;
        if ((Ty1_right=new BSTNode<T>("π",NULL,attribute2,op2,value2,NULL,NULL,NULL)) == NULL)
           return ;
        Ty1_left->parent = rightchild;
        Ty1_left->left = rightchild->left;
        rightchild->left->parent = Ty1_left;
        rightchild->left = Ty1_left;
        Ty1_right->parent = rightchild;
        Ty1_right->right = rightchild->right;
        rightchild->right->parent = Ty1_right;
        rightchild->right = Ty1_right;
        if(!righttouying(rightchild->left))
           optimizetouiying(rightchild->left);
        if(!righttouying(rightchild->right))
           optimizetouiying(rightchild->right);
      }
    }


}

template <class T>
void BSTree<T>::optimize()
{
    optimize(mRoot);
}

template <class T>
bool BSTree<T>::rightxuanze(BSTNode<T>* tree)
{
    if(tree->left != NULL){
        if(strcmp(tree->left->key,tree->tbl_name) == 0)
            return true;
    }else if(tree->right != NULL){
        if(strcmp(tree->right->key,tree->tbl_name) == 0)
            return true;
    }
   return false;
}

template <class T>
bool BSTree<T>::righttouying(BSTNode<T>* tree)
{
    if(tree->left != NULL){
        if(strcmp(tree->left->key,"x") == 0) 
            return false;
        else if(strcmp(tree->left->key,"⋈") == 0)
            return false;
        return true;
    }else if(tree->right != NULL){
        if(strcmp(tree->right->key,"x") == 0)
            return false;
        else if(strcmp(tree->right->key,"⋈") == 0)
            return false;
        return true;
    }
   return true;
}

template <class T>
void BSTree<T>::PrintTree(BSTNode<T>* tree)
{
  int max_level = MaxLevel(tree);  
  if (max_level<7)
    max_level = 7;
  vector<BSTNode<char*>*> nodes;  
    
  nodes.push_back(tree);
   
  PrintNode(nodes, 1, max_level);
}

template <class T>
void BSTree<T>::PrintTree()
{
    PrintTree(mRoot);
}

template <class T>
bool BSTree<T>::IsAllElementsNULL(const vector<BSTNode<T>*> &nodes)
{
  vector<BSTNode<char*>*>::const_iterator it = nodes.begin();  
  
  while(it != nodes.end()){  
    if(*it) return false;   
    ++it;  
  }  
  return true;  
}

template <class T>
void BSTree<T>::PrintNode(vector<BSTNode<T>*> &nodes,int level, int max_level)
{
    if(nodes.empty() || IsAllElementsNULL(nodes)) return; 
    int floor = max_level - level;  
    int endge_lines = 1 << (max(floor-1, 0));  
    int first_spaces = (1 << floor) - 1;  
    int between_spaces = (1 << (floor+1)) - 1; 

    PrintWhiteSpaces(first_spaces); 

    // print the 'level' level   
  vector<BSTNode<char*>*> new_nodes;  
  vector<BSTNode<char*>*>::const_iterator it = nodes.begin();  
  for(; it != nodes.end(); ++it){  
    if(*it != NULL){  
      cout << (*it)->key;  
      new_nodes.push_back((*it)->left);  
      new_nodes.push_back((*it)->right);  
    }  
    else{  
      new_nodes.push_back(NULL);  
      new_nodes.push_back(NULL);  
      cout << " ";  
    }  
    PrintWhiteSpaces(between_spaces);  
  }  
  cout << endl;  
  
  // print the following /s and \s  
  for(int i=1; i<= endge_lines; ++i){  
    for(int j=0; j<nodes.size(); ++j){  
      PrintWhiteSpaces(first_spaces - i);  
      if(nodes[j] == NULL){  
        PrintWhiteSpaces(endge_lines + endge_lines + i + 1);  
        continue;  
      }  
      if(nodes[j]->left != NULL)  
        cout << "/";  
      else  
        PrintWhiteSpaces(1);  
  
      PrintWhiteSpaces(i+i-1);  
        
      if(nodes[j]->right != NULL)  
        cout << "\\";  
      else  
        PrintWhiteSpaces(1);  
  
      PrintWhiteSpaces(endge_lines + endge_lines - i);  
    }  
    cout << endl;  
  }  
  
  PrintNode(new_nodes, level+1, max_level);  
  
}

template <class T>
int BSTree<T>::MaxLevel(BSTNode<T>* tree)
{
  if(tree == NULL) return 0;  
  return max(MaxLevel(tree->left), MaxLevel(tree->right)) + 1;
}


template <class T>
void BSTree<T>::Phy_optimize(BSTNode<T>* tree)
{
 

 tb1.name = "NATION";
 tb1.tuple = 25;
 tb1.attr.insert(tb1.attr.begin(),"N_NATIONKEY");
 tb1.attr.insert(tb1.attr.begin(),"N_NAME");
 tb1.attr.insert(tb1.attr.begin(),"N_REGIONKEY");
 tb1.attr.insert(tb1.attr.begin(),"N_COMMENT");
 tb1.V_attr.insert(pair<string,int>("N_NATIONKEY",25));
 tb1.V_attr.insert(pair<string,int>("N_NAME",25));
 tb1.V_attr.insert(pair<string,int>("N_REGIONKEY",5));
 tb1.V_attr.insert(pair<string,int>("N_COMMENT",25));
 tb_totle.insert(tb_totle.end(),tb1);

 tb2.name = "REGION";
 tb2.tuple = 5;
 tb2.attr.insert(tb2.attr.begin(),"R_REGIONKEY");
 tb2.attr.insert(tb2.attr.begin(),"R_NAME");
 tb2.attr.insert(tb2.attr.begin(),"R_COMMENT");
 tb2.V_attr.insert(pair<string,int>("R_REGIONKEY",5));
 tb2.V_attr.insert(pair<string,int>("R_NAME",5));
 tb2.V_attr.insert(pair<string,int>("R_COMMENT",5));
 tb_totle.insert(tb_totle.end(),tb2);

 tb3.name = "PART";
 tb3.tuple = 200000;
 tb3.attr.insert(tb3.attr.begin(),"P_PARTKEY");
 tb3.attr.insert(tb3.attr.begin(),"P_NAME");
 tb3.attr.insert(tb3.attr.begin(),"P_MFGR");
 tb3.attr.insert(tb3.attr.begin(),"P_BRAND");
 tb3.attr.insert(tb3.attr.begin(),"P_TYPE");
 tb3.attr.insert(tb3.attr.begin(),"P_SIZE");
 tb3.attr.insert(tb3.attr.begin(),"P_CONTAINER");
 tb3.attr.insert(tb3.attr.begin(),"P_RETAILPRICE");
 tb3.attr.insert(tb3.attr.begin(),"P_COMMENT");
 tb3.V_attr.insert(pair<string,int>("P_PARTKEY",200000));
 tb3.V_attr.insert(pair<string,int>("P_NAME",199997));
 tb3.V_attr.insert(pair<string,int>("P_MFGR",5));
 tb3.V_attr.insert(pair<string,int>("P_BRAND",25));
 tb3.V_attr.insert(pair<string,int>("P_TYPE",150));
 tb3.V_attr.insert(pair<string,int>("P_SIZE",50));
 tb3.V_attr.insert(pair<string,int>("P_CONTAINER",40));
 tb3.V_attr.insert(pair<string,int>("P_RETAILPRICE",20899));
 tb3.V_attr.insert(pair<string,int>("P_COMMENT",127463));
 tb_totle.insert(tb_totle.end(),tb3);

 tb4.name = "SUPPLIER";
 tb4.tuple = 10000;
 tb4.attr.insert(tb4.attr.begin(),"S_SUPPKEY");
 tb4.attr.insert(tb4.attr.begin(),"S_NAME");
 tb4.attr.insert(tb4.attr.begin(),"S_ADDRESS");
 tb4.attr.insert(tb4.attr.begin(),"S_NATIONKEY");
 tb4.attr.insert(tb4.attr.begin(),"S_PHONE");
 tb4.attr.insert(tb4.attr.begin(),"S_ACCTBAL");
 tb4.attr.insert(tb4.attr.begin(),"S_COMMENT");
 tb4.V_attr.insert(pair<string,int>("S_SUPPKEY",10000));
 tb4.V_attr.insert(pair<string,int>("S_NAME",10000));
 tb4.V_attr.insert(pair<string,int>("S_ADDRESS",10000));
 tb4.V_attr.insert(pair<string,int>("S_NATIONKEY",25));
 tb4.V_attr.insert(pair<string,int>("S_PHONE",10000));
 tb4.V_attr.insert(pair<string,int>("S_ACCTBAL",9955));
 tb4.V_attr.insert(pair<string,int>("S_COMMENT",10000));
 tb_totle.insert(tb_totle.end(),tb4);

 tb5.name = "PARTSUPP";
 tb5.tuple = 200000;
 tb5.attr.insert(tb5.attr.begin(),"PS_PARTKEY");
 tb5.attr.insert(tb5.attr.begin(),"PS_SUPPKEY");
 tb5.attr.insert(tb5.attr.begin(),"PS_AVAILQTY");
 tb5.attr.insert(tb5.attr.begin(),"PS_SUPPLYCOST");
 tb5.attr.insert(tb5.attr.begin(),"PS_COMMENT");
 tb5.V_attr.insert(pair<string,int>("PS_PARTKEY",200000));
 tb5.V_attr.insert(pair<string,int>("PS_SUPPKEY",10000));
 tb5.V_attr.insert(pair<string,int>("PS_AVAILQTY",9999));
 tb5.V_attr.insert(pair<string,int>("PS_SUPPLYCOST",99865));
 tb5.V_attr.insert(pair<string,int>("PS_COMMENT",799123));
 tb_totle.insert(tb_totle.end(),tb5);

 tb6.name = "CUSTOMER";
 tb6.tuple = 150000;
 tb6.attr.insert(tb6.attr.begin(),"C_CUSTKE");
 tb6.attr.insert(tb6.attr.begin(),"C_NAME");
 tb6.attr.insert(tb6.attr.begin(),"C_ADDRESS");
 tb6.attr.insert(tb6.attr.begin(),"C_NATIONKE");
 tb6.attr.insert(tb6.attr.begin(),"C_PHONE");
 tb6.attr.insert(tb6.attr.begin(),"C_ACCTBAL");
 tb6.attr.insert(tb6.attr.begin(),"C_MKTSEGMENT");
 tb6.attr.insert(tb6.attr.begin(),"C_COMMENT");
 tb6.V_attr.insert(pair<string,int>("C_CUSTKE",150000));
 tb6.V_attr.insert(pair<string,int>("C_NAME",150000));
 tb6.V_attr.insert(pair<string,int>("C_ADDRESS",150000));
 tb6.V_attr.insert(pair<string,int>("C_C_NATIONKE",25));
 tb6.V_attr.insert(pair<string,int>("C_PHONE",150000));
 tb6.V_attr.insert(pair<string,int>("C_ACCTBAL",140187));
 tb6.V_attr.insert(pair<string,int>("C_MKTSEGMENT",5));
 tb6.V_attr.insert(pair<string,int>("C_COMMENT",149965));
 tb_totle.insert(tb_totle.end(),tb6);

 tb7.name = "ORDERS";
 tb7.tuple = 150000;
 tb7.attr.insert(tb7.attr.begin(),"O_ORDERKEY");
 tb7.attr.insert(tb7.attr.begin(),"O_CUSTKEY");
 tb7.attr.insert(tb7.attr.begin(),"O_ORDERSTATUS");
 tb7.attr.insert(tb7.attr.begin(),"O_TOTALPRICE");
 tb7.attr.insert(tb7.attr.begin(),"O_ORDERDATE");
 tb7.attr.insert(tb7.attr.begin(),"O_ORDERPRIORITY");
 tb7.attr.insert(tb7.attr.begin(),"O_CLERK");
 tb7.attr.insert(tb7.attr.begin(),"O_SHIPPRIORITY");
 tb7.attr.insert(tb7.attr.begin(),"O_COMMENT");
 tb7.V_attr.insert(pair<string,int>("O_ORDERKEY",150000));
 tb7.V_attr.insert(pair<string,int>("O_CUSTKEY",99996));
 tb7.V_attr.insert(pair<string,int>("O_ORDERSTATUS",3));
 tb7.V_attr.insert(pair<string,int>("O_TOTALPRICE",1464556));
 tb7.V_attr.insert(pair<string,int>("O_ORDERDATE",2406));
 tb7.V_attr.insert(pair<string,int>("O_ORDERPRIORITY",5));
 tb7.V_attr.insert(pair<string,int>("O_CLERK",1000));
 tb7.V_attr.insert(pair<string,int>("O_SHIPPRIORITY",1));
 tb7.V_attr.insert(pair<string,int>("O_COMMENT",1478684));
 tb_totle.insert(tb_totle.end(),tb7);

 tb8.name = "LINEITEM";
 tb8.tuple = 1500000;
 tb8.attr.insert(tb8.attr.begin(),"L_ORDERKE");
 tb8.attr.insert(tb8.attr.begin(),"L_PARTKEY");
 tb8.attr.insert(tb8.attr.begin(),"L_SUPPKEY");
 tb8.attr.insert(tb8.attr.begin(),"L_LINENUMBER");
 tb8.attr.insert(tb8.attr.begin(),"L_QUANTITY");
 tb8.attr.insert(tb8.attr.begin(),"L_EXTENDEDPRICE");
 tb8.attr.insert(tb8.attr.begin(),"L_DISCOUNT");
 tb8.attr.insert(tb8.attr.begin(),"L_TAX");
 tb8.attr.insert(tb8.attr.begin(),"L_RETURNFLAG");
 tb8.attr.insert(tb8.attr.begin(),"L_LINESTATUS");
 tb8.attr.insert(tb8.attr.begin(),"L_SHIPDATE");
 tb8.attr.insert(tb8.attr.begin(),"L_COMMITDATE");
 tb8.attr.insert(tb8.attr.begin(),"L_RECEIPTDATE");
 tb8.attr.insert(tb8.attr.begin(),"L_SHIPINSTRUCT");
 tb8.attr.insert(tb8.attr.begin(),"L_SHIPMODE");
 tb8.attr.insert(tb8.attr.begin(),"L_COMMENT");
 tb8.V_attr.insert(pair<string,int>("L_ORDERKE",1500000));
 tb8.V_attr.insert(pair<string,int>("L_PARTKEY",200000));
 tb8.V_attr.insert(pair<string,int>("L_SUPPKEY",10000));
 tb8.V_attr.insert(pair<string,int>("L_LINENUMBER",7));
 tb8.V_attr.insert(pair<string,int>("L_QUANTITY",50));
 tb8.V_attr.insert(pair<string,int>("L_EXTENDEDPRICE",933900));
 tb8.V_attr.insert(pair<string,int>("L_DISCOUNT",11));
 tb8.V_attr.insert(pair<string,int>("L_TAX",9));
 tb8.V_attr.insert(pair<string,int>("L_RETURNFLAG",3));
 tb8.V_attr.insert(pair<string,int>("L_LINESTATUS",2));
 tb8.V_attr.insert(pair<string,int>("L_SHIPDATE",2526));
 tb8.V_attr.insert(pair<string,int>("L_COMMITDATE",2466));
 tb8.V_attr.insert(pair<string,int>("L_RECEIPTDATE",2554));
 tb8.V_attr.insert(pair<string,int>("L_SHIPINSTRUCT",4));
 tb8.V_attr.insert(pair<string,int>("L_SHIPMODE",7));
 tb8.V_attr.insert(pair<string,int>("L_COMMENT",4502054));
 tb_totle.insert(tb_totle.end(),tb8);

  
  vector<BSTNode<char*>*> tbs;
  get_tb(tree,tbs);
  int tblsize = tbs.size();
  vector<table> tb;
  vector<table> tb_right;
  for(int i=0;i<tblsize;i++)
  {
    cout << tbs[i]->key << endl;
    for(int j = 0;j < tb_totle.size();j++){
        if(strcmp(tb_totle[j].name,tbs[i]->key) == 0)
           tb.insert(tb.begin(),tb_totle[j]);
    }
  }
  //利用贪婪算法算出正确的顺序
  int t = 0;
  while(tb.size() > 2){
  int tb_size = tb.size();
  double min = 1.79769e+308;
  if(t == 0)
  {
  double a[tb_size][tb_size];
  double remember[2];
  for(int i=0;i<tb_size-1;i++)
  { for(int j=i+1;j<tb_size;j++)
    {
        a[i][j] = compute_loss(tb,i,j);
        if(a[i][j] < min){
            remember[0] = i;
            remember[1]=j;
            min = a[i][j];
        }
        cout << tb[i].name << "   " << tb[j].name <<"   " << a[i][j] << endl;
    }
  }
  tb_right.insert(tb_right.begin(),tb[remember[0]]);
  tb_right.insert(tb_right.begin(),tb[remember[1]]);
  tb_con.name = "tb_con";
  tb_con.tuple = compute_loss(tb,remember[0],remember[1]);
  tb_con.attr.insert(tb_con.attr.begin(),tb[remember[0]].attr.begin(),tb[remember[0]].attr.end());
  tb_con.V_attr = tb[remember[0]].V_attr;
  // cout << "tb_con.V_attr.size()" << tb_con.V_attr.size() << endl;
  int flag = 0;
  for(int i = 0;i < tb[remember[1]].attr.size();i++) {
    flag = 0;
    for(int j = 0;j<tb_con.attr.size();j++){
        if(strcmp(tb[remember[1]].attr[i],tb_con.attr[j]) == 0)
            flag = 1;
    }
    if(flag == 0)
        tb_con.attr.insert(tb_con.attr.end(),tb[remember[1]].attr[i]);
  }
  map<string,int>::iterator it; 
  map<string,int>::iterator it1; 
  for(it = tb[remember[1]].V_attr.begin() ;it != tb[remember[1]].V_attr.end();it++){
    // cout <<"it  " <<it->first <<endl;
    it1 = tb_con.V_attr.find(it->first);
    if(it1 != tb_con.V_attr.end()){
        tb_con.V_attr[it->first] = tb_con.V_attr[it->first] >  it->second ? tb_con.V_attr[it->first] : it->second;
    }else
    tb_con.V_attr.insert(pair<string,int>(it->first,it->second));
  }
  // cout << "tb_con.V_attr.size()" << tb_con.V_attr.size() << endl;
  // for(it1 = tb_con.V_attr.begin();it1 != tb_con.V_attr.end();it1++)
  //   cout << it1->first<<"   "<< it1->second<<endl;
  // cout <<  " tb_con.tuple :" << tb_con.tuple << endl;
  // vector<char*>::iterator it2;
  // for(it2 = tb_con.attr.begin();it2!= tb_con.attr.end();it2++)
  //   cout << *it2  <<endl;
  vector<table>::iterator   iter   =   tb.begin() + remember[0];
  tb.erase(iter);
  tb.erase(iter + remember[1] - remember[0] - 1);
  if(tb.size() == 1)
  {
    tb_right.insert(tb_right.end(),tb[0]);
    break;
  }
  tb.insert(tb.begin(),tb_con);
  }else{
    int remember;
    double a[tb_size];
    for(int i = 1;i<tb_size;i++){
        a[i] = compute_loss(tb,0,i);
        if(a[i] < min){
            remember = i;
            min = a[i];
        }
        cout << tb[0].name << "   " << tb[i].name <<"   " << a[i] << endl;
    }
    tb_right.insert(tb_right.end(),tb[remember]);
    tb_con.tuple = compute_loss(tb,0,remember);
    // cout << "tb_con.V_attr.size()" << tb_con.V_attr.size() << endl;
    int flag = 0;
    for(int i = 0;i < tb[remember].attr.size();i++) {
        flag = 0;
      for(int j = 0;j<tb_con.attr.size();j++){
          if(strcmp(tb[remember].attr[i],tb_con.attr[j]) == 0)
              flag = 1;
      }
      if(flag == 0)
          tb_con.attr.insert(tb_con.attr.end(),tb[remember].attr[i]);
    }
    map<string,int>::iterator it; 
    map<string,int>::iterator it1; 
    for(it = tb[remember].V_attr.begin() ;it != tb[remember].V_attr.end();it++){
      // cout <<"it  " <<it->first <<endl;
      it1 = tb_con.V_attr.find(it->first);
      if(it1 != tb_con.V_attr.end()){
          tb_con.V_attr[it->first] = tb_con.V_attr[it->first] >  it->second ? tb_con.V_attr[it->first] : it->second;
      }else
      tb_con.V_attr.insert(pair<string,int>(it->first,it->second));
    }
    // cout << "tb_con.V_attr.size()" << tb_con.V_attr.size() << endl;
    // for(it1 = tb_con.V_attr.begin();it1 != tb_con.V_attr.end();it1++)
    //   cout << it1->first<<"   "<< it1->second<<endl;
    // cout <<  " tb_con.tuple :" << tb_con.tuple << endl;
    // vector<char*>::iterator it2;
    // for(it2 = tb_con.attr.begin();it2!= tb_con.attr.end();it2++)
    //   cout << *it2  <<endl;
    vector<table>::iterator   iter   =   tb.begin() + remember;
    tb.erase(iter);
    if(tb.size() == 2)
    {
      tb_right.insert(tb_right.end(),tb[1]);
      break;
    }
    }
  
  t++;
  }
  // cout << tb_right.size() << endl;
  vector<table>::iterator it2;
  cout << "right order: "  ;
  for(it2 = tb_right.begin();it2!= tb_right.end();it2++){
      if(it2 == tb_right.end()-1)
        cout << (*it2).name << endl;
      else
        cout << (*it2).name << "⋈" ;
  }
  BSTNode<T>* connect =  generate_new_tree(tb_right,NULL);
  cout << "connect->attribute[0]  " <<connect->attribute[0]<< endl;
  cout << "connect->key  " <<connect->key<< endl; 
  mRoot->left = connect;
  connect->parent = mRoot;
  PrintTree(mRoot);
  postOrder(mRoot);
}
template <class T>
void BSTree<T>::Phy_optimize()
{
  Phy_optimize(mRoot);
}

template <class T>
BSTNode<T>* BSTree<T>::generate_new_tree(vector<table> &tb_right,BSTNode<T>* last_connect)
{
  BSTNode<T>* connect;
  vector<T> attribute;
  vector<OP> op;
  vector<T> value;
  connect=new BSTNode<T>("⋈",NULL,attribute,op,value,NULL,NULL,NULL);
  connect->key = "⋈";
  vector<char*> tb_common;
  if(last_connect == NULL)
  {
  tb_common = jiaoji(tb_right,0,1);
  tb_con.name = "tb_con";
  tb_con.attr = tb_right[0].attr;
  int flag = 0;
  for(int i = 0;i < tb_right[1].attr.size();i++) {
    flag = 0;
    for(int j = 0;j<tb_con.attr.size();j++){
        if(strcmp(tb_right[1].attr[i],tb_con.attr[j]) == 0)
            flag = 1;
    }
    if(flag == 0)
        tb_con.attr.insert(tb_con.attr.end(),tb_right[1].attr[i]);
  }
   BSTNode<T>* tb1 = search(tb_right[0].name);
   BSTNode<T>* tb2 = search(tb_right[1].name);
   cout << "tb1->key  " << tb1->key<<endl;
   cout << "tb2->key  " << tb2->key<<endl;
   BSTNode<T>* p_tb1  = tb1;
   while(p_tb1->key != "⋈" && p_tb1->key != "x")
         p_tb1 = p_tb1->parent;
   
   cout << "p_tb1->key   " << p_tb1->key << endl;
   BSTNode<T>* p_tb2  = tb2;
   while(p_tb2->key != "⋈" && p_tb2->key != "x")
         p_tb2 = p_tb2->parent;
   cout << "p_tb2->key   " << p_tb2->key <<endl;
// 找到相应的树枝，连接到新节点connect下面

   BSTNode<T>* parent1 = tb1->parent;
   BSTNode<T>* parent_old = parent1->parent;
    
   if(tb1 = parent1->right){
    parent1->left = tb1;
    parent1->right = NULL;
    if(parent1->key == "σ"){
      parent_old->left = parent1;
      parent_old->right = NULL;
    }
    connect->left = p_tb1->right;
    p_tb1->right->parent = connect;
    connect->attribute = p_tb1->value;    
   }else{
    connect->left = p_tb1->left;
    p_tb1->left->parent = connect;
    connect->attribute = p_tb1->attribute;
    }
    connect->op = p_tb1->op;

    BSTNode<T>* parent2 = tb2->parent;
    BSTNode<T>* parent_old1 = parent2->parent;
    if(tb2 = parent2->left){
    parent2->right = tb2;
    parent2->left =NULL;
    if(parent2->key == "σ"){
      parent_old1->right = parent2;
      parent_old1->left = NULL;
    }
    connect->right = p_tb2->left;
    p_tb2->left->parent = connect;
    connect->value = p_tb2->attribute;
   }else{
    connect->right = p_tb2->right;
    p_tb2->right->parent = connect;
    connect->value = p_tb2->value;
   }
   //删除已连接节点
   vector<table>::iterator   iter   =   tb_right.begin();
   tb_right.erase(iter);
   tb_right.erase(iter);
   cout << "tb_right.size()"<< tb_right.size() << endl;
   cout << "tb_right[0]"<< tb_right[0].name << endl;
   tb_right.insert(tb_right.begin(),tb_con);
   cout << "tb_right.size()"<< tb_right.size() << endl;
   cout << "tb_right[0]"<< tb_right[0].name << endl;
   if(tb_right.size() > 1)
     connect = generate_new_tree(tb_right,connect);
    }else{
  tb_common = jiaoji(tb_right,0,1);
  tb_con.name = "tb_con";
  tb_con.attr=tb_right[0].attr;
  int flag = 0;
  for(int i = 0;i < tb_right[1].attr.size();i++) {
    flag = 0;
    for(int j = 0;j<tb_con.attr.size();j++){
        if(strcmp(tb_right[1].attr[i],tb_con.attr[j]) == 0)
            flag = 1;
    }
    if(flag == 0)
        tb_con.attr.insert(tb_con.attr.end(),tb_right[1].attr[i]);
  }
  BSTNode<T>* tb1 = search(tb_right[1].name);
  cout << "tb1->key  " << tb1->key<<endl;
  BSTNode<T>* p_tb1  = tb1;
        while(p_tb1->key != "⋈" && p_tb1->key != "x")
            p_tb1 = p_tb1->parent;
        cout << "p_tb1->key   " << p_tb1->key<< "  p_tb1->attribute[0]  "<< p_tb1->attribute[0]<<endl;

   
// 找到相应的树枝，连接到新节点connect下面

   connect->left = last_connect;
   last_connect->parent = connect;
   BSTNode<T>* parent = tb1->parent;
   BSTNode<T>* parent_old = parent->parent;
    if(tb1 = parent->left){
    parent->right = tb1;
    parent->left = NULL;
    if(parent->key == "σ"){
      parent_old->right = parent;
      parent_old->left = NULL;
    }
    connect->right = p_tb1->left;
    p_tb1->left->parent = connect;
    connect->attribute = p_tb1->attribute;
   }else{
    connect->right = p_tb1->right;
    p_tb1->right->parent = connect;
    connect->attribute = p_tb1->value;
   }
   connect->op = p_tb1->op;

   //删除已连接节点
   vector<table>::iterator   iter   =   tb_right.begin();
   tb_right.erase(iter);
   tb_right.erase(iter);
   cout << "tb_right.size()"<< tb_right.size() << endl;
   cout << "tb_right[0]"<< tb_right[0].name << endl;
   tb_right.insert(tb_right.begin(),tb_con);
   cout << "tb_right.size()"<< tb_right.size() << endl;
   cout << "tb_right[0]"<< tb_right[0].name << endl;

   if(tb_right.size() > 1)
    connect = generate_new_tree(tb_right,connect);

   }

  return connect;
}

template <class T>
void BSTree<T>::get_tb(BSTNode<T>* tree,vector<BSTNode<T>*> &tbs) 
{
   if(tree != NULL)
    {
        if(tree->left==NULL && tree->right==NULL)
            tbs.insert(tbs.begin(),tree);
        get_tb(tree->left,tbs);
        get_tb(tree->right,tbs);
    }
}

#endif

