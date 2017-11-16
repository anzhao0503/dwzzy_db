/*
 * linear_hash.cpp
 *
 *  Created on: 2017年11月1日
 *      Author: ycm
 */
#include "linear_hash.h"

int hash(string x){//32位哈希函数
 int t = 0;
 for(int i = 0;i < x.size(); i++ ){
  t = t*10 + (x.at(i) - 48);//*(i*(i+1)+3);
 }
    return t;
}
bool hashEq(int x,int y){//判断x与y在当前条件下属不属于一个桶
    return (x&mask[E])==(y&mask[E]);
}
//
int currentHash(int Hash){//当前哈希值
    Hash=Hash&mask[E];
    return Hash < N ? Hash : Hash&mask[E-1];
}

//初始化
void Init(){
    p2[0]=1;
    for(int i=1;i<=32;++i) p2[i]=p2[i-1]<<1;
    for(int i=0;i<=32;++i) mask[i]=p2[i]-1;
    E=1;N=1;R=0;L[0]=List();
}
//调整
void Adjust(){
    while((double)R/N > P){
        //将属于N的信息加入List[N]
        L[N&mask[E-1]].Transfer(N,&L[N]);
        //更正 N 和 E
        if(++N >= p2[E])  ++E;
        L[N]=List();
    }
}
//插入
void Insert(int Hash,string Key,int Value){
    //插入元素
    L[currentHash(Hash)].Insert(Hash,Key,Value);
    ++R;
    //调整 N 和 E
    Adjust();
}
//删除
int Delete(int Hash,string Key){
 //删除元素
   int i = L[currentHash(Hash)].Delete(Key);
// --R;
 //调整 N 和 E
   Adjust();
   return i;
}
//寻找
int Find(string Key){
  int Hash = hash(Key);
  cout<<currentHash(Hash)<<endl;
    return L[currentHash(Hash)].Find(Key);
}
//释放所有
void FreeAll(){
    for(int i=0;i<N;++i) L[i].clear();
}
//显示
void ShowList(){
    cout << "E: " << E  << ", R: " << R << ", N: " << N << endl;
    for(int i=0;i < N;++i){
        cout << i << endl;
        L[i].Show();
    }
}
//写文件函数
void write(List *L){
 string filename ="linear_hash.txt";
    ofstream fout;
    fout.open(filename.c_str());
    ListNode *p;
    for(int i = 0;i < N; i++){
     p = L[i].Head;
        while(p){
     fout << p->Key << "," << p->Value << "|";
     cout << p->Key << "," << p->Value << "|";
     p = p->next;
    }
        fout<<endl;
        cout<<endl;
}
    fout.close();
}

//读取文件函数
void read(List *Read_L){
 FILE* fp;
 if ((fp = fopen("linear_hash.txt", "r")) == NULL) {
   cout<<"error"<<endl;
  }
 char line[512];
 while(fgets(line, 512, fp)){
  char seg[] = "|";
  char* key_value_1;
  char* key_value_2;
  key_value_1 = strtok(line, seg);
  key_value_2 = strtok( NULL,seg);
  cout << key_value_1 << endl;
     char* s_key_1 = strtok(key_value_1,",");
     char* Key = s_key_1;
     cout << Key <<  endl;
     s_key_1 = strtok(NULL,",");
     string s_value = s_key_1;
     int value = atoi(s_value.c_str());
     cout << value << endl;
  Read_L[0].Insert(hash(Key),Key,value);
  int p = key_value_2[0];
  if( p != 10){
  cout << key_value_2 <<endl;
  char* s_key_2 = strtok(key_value_2,",");
  Key = s_key_2;
     cout << Key <<  endl;
  s_key_2 = strtok(NULL,",");
  s_value = s_key_2;
  value = atoi(s_value.c_str());
     cout << value << endl;
  Read_L[1].Insert(hash(Key),Key,value);
  }
 }
 fclose(fp);
}

//读取文件函数
void read(){
 FILE* fp;
 if ((fp = fopen("linear_hash.txt", "r")) == NULL) {
   cout<<"error"<<endl;
  }
 char line[512];
 int i = 0;
 while(1){
   fgets(line, 512, fp);
   int a = line[0];
   if(a == 10) {i++;
     continue;}
   if(line[0] == '$') break;
     if(line[0] == '!'){
    char* temp ;
    temp = strtok(line,"@");
    temp = strtok(NULL,"@");
    string E_string = temp;
    E = atoi(E_string.c_str());
    temp = strtok(NULL,"@");
    string R_string = temp;
    R = atoi(R_string.c_str());
    temp = strtok(NULL,"@");
    string N_string = temp;
    N = atoi(N_string.c_str());
    continue;
  }
  char seg[] = "|";
  char* key_value_1;
  char* key_value_2;
  key_value_1 = strtok(line, seg);
  key_value_2 = strtok( NULL,seg);
  //cout << key_value_1 <<"~~~~~~~~~~~~~~~~"<< endl;
     char* s_key_1 = strtok(key_value_1,"@");
     char* Key = s_key_1;
//     cout << Key <<  endl;
     s_key_1 = strtok(NULL,"@");
     string s_value = s_key_1;
     int value = atoi(s_value.c_str());
//     cout << value << endl;
     L[i].Insert(hash(Key),Key,value);
  int p = key_value_2[0];
  if( p != 10){
  //cout << key_value_2 <<endl;
  char* s_key_2 = strtok(key_value_2,"@");
  Key = s_key_2;
//     cout << Key <<  endl;
  s_key_2 = strtok(NULL,"@");
  s_value = s_key_2;
  value = atoi(s_value.c_str());
//     cout << value << endl;
     L[i].Insert(hash(Key),Key,value);
  }
  i++;
 }
 fclose(fp);
}
