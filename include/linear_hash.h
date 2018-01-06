#include <iostream>
#include <fstream>
#include "../include/storage.h"
#include "../include/format.h"
#include <string>
#include <cstring>
#include <stdlib.h>

using namespace std;

const double P=1.7;//平均每个桶装的元素个数的上限
int E;//目前使用了哈希值的前 E 位来分组
int R;//实际装入本哈希表的元素总数
int N;//目前使用的桶的个数
/*
操作过程中，始终维护两个性质
1. R/N <= P          可以推出  max(N) = max(R/P) = maxn/P   所以，所需链表的个数为 maxn/P
2. 2^(E-1) <=  N  < 2^E
*/
int p2[33];//记录2的各个次方  p2[i]=2^i
int mask[33]; //记录掩码 mask[i]=p2[i]-1
bool ERROR;//错误信息

int hash(string x);
bool hashEq(int x,int y);
int currentHash(int Hash);

struct ListNode{//链表节点定义
    int Hash;//32位哈希值，根据Key计算，通常为 hash(Key)
    string Key;//键值，唯一
    int Value;//键值Key对应的值
    ListNode *next;//指向链表中的下一节点，或者为空
    //构造函数
    ListNode(){}
    ListNode(int H,string K,int V):Hash(H),Key(K),Value(V){}
};

struct List{//链表定义
    ListNode *Head;//头指针
    //构造函数 析构函数
    List():Head(NULL){}
    ~List(){clear();}
    //插入函数
    void Insert(int H,string K,int V){
        Insert(new ListNode(H,K,V));
    }
    void Insert(ListNode *temp){
        temp->next=Head;
        Head=temp;
    }
    //转移函数
    void Transfer(int H,List *T){//将本链表中，Hash值掩码之后为H的元素加入到链表T中去。
        ListNode *temp,*p;
        while(Head && hashEq(Head->Hash,H)){
            temp=Head;
            Head=Head->next;
            T->Insert(temp);
        }
        p=Head;
        while(p&&p->next){
            if(hashEq(p->next->Hash,H)){
                temp=p->next;
                p->next=p->next->next;
                T->Insert(temp);
            }
            else p=p->next;
        }
    }
    //寻找函数
    int Find(string Key){
        ERROR=false;
        ListNode *temp=Head;
        while(temp){
          cout<<temp->Key<<endl;
            if(!temp->Key.compare(Key)) return temp->Value;
            temp=temp->next;
        }
        return ERROR = true;
    }
    //删除函数
   int Delete(string Key){
    ListNode  *temp = Head;
    if(temp->Key == Key) {
     Head = Head->next;
     return true;
    }
    ListNode  *p = temp->next;
    while(p){
     if(p->Key == Key) {
      temp->next = temp->next->next;
      return true;
     }
     temp = temp->next;
     p = p->next;
    }
    return ERROR = false;
   }
    //显示函数
    void Show(){
        ListNode *temp=Head;
        while(temp){
            cout << temp->Key<<","<< temp->Value << endl;
            temp=temp->next;
        }
    }
    //释放申请空间
    void clear(){
        while(Head){
            ListNode *temp=Head;
            Head=Head->next;
            delete temp;
        }
    }
}L[10000];

void Init();
void Adjust();
void Insert(int Hash,string Key,int Value);
int Delete(int Hash,string Key);
int Find(string Key);
void FreeAll();
void ShowList();
void write(List *L);
void read(List *Read_L);
void read();
