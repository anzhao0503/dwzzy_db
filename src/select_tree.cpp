#include <malloc.h>
#include <iostream>
#include <string>
#include "../include/parser.h"
// #include "../include/select_tree.h"
#include "../include/BST.h"
// #include "../include/logger.h"

using namespace std;
using std::string;

extern SelectQuery* query;
extern TableManagement* table_manager;

extern int join_count;
extern int sel_count;
extern int from_count;
extern int cond_count;
extern Condition cond_list[MAX_COND_NUM];

void print_select(char* tbl, vector<char*> cols, vector<OP> ops, char** keys){
  cout<<"σ "<<tbl<<" ";
  for_each(cols.begin(),cols.end(),print_order);
  for_each(ops.begin(),ops.end(),print_order_int);
  for(int i=0; i< 10;i++){
    if(keys[i] != NULL){
      cout<<keys[i]<<" ";
    }
    else
      break;
  }
  cout<<endl;
}
void print_project(char* tbl, vector<char*> cols){
  cout <<"π "<<tbl<<" ";
  for_each(cols.begin(),cols.end(),print_order);
  cout<<endl;
}
void print_join(char* tb1, char* tb2, vector<char*> cols1, vector<char*> cols2, vector<OP> ops){
  cout <<"⋈ " << tb1 << " "<<tb2<<" ";
  for_each(cols1.begin(),cols1.end(),print_order);
  for_each(cols2.begin(),cols2.end(),print_order);
  for_each(ops.begin(),ops.end(),print_order_int);
  cout<<endl;
}
void print_kashi(char* tb1, char* tb2){
  cout << "x " << tb1<<" "<<tb2<<endl;
}

int select_tree(){
  int i, ilen;
  BSTree<char*>* tree=new BSTree<char*>();
//    for_each(attribute.begin(),attribute.end(),print);//用for_each进行遍历    
//    cout<<endl;
  if(from_count!=0)
    cout << "SELECT "<< endl;

  vector<char*> attribute1;
  if(query->all != 0){
    cout<< "*" << endl;
    attribute1.insert(attribute1.end(),"*");
  }
  if(sel_count!=0){
    cout << "SEL_LIST" <<endl;
    for(i=0; i < sel_count; i++){
      attribute1.insert(attribute1.end(),query->SelList[i].col_name);
    }
  }
  tree->insert_touying(NULL, attribute1);

  cout << "CONDITION" <<endl;
  for(i = 0; i < cond_count; i++){
    vector<char*> attribute2;
    attribute2.insert(attribute2.end(),cond_list[i].col_name);
    int b2[] = {1,2};
    vector<OP> op2;
    op2.insert(op2.end(),cond_list[i].op);
    vector<char*> value2;
    value2.insert(value2.end(),cond_list[i].value);
    tree->insert_xuanze(cond_list[i].tb_name, attribute2, op2, value2);
  }

  cout << "JOIN" << join_count <<endl;
  for(i = 0; i < join_count; i++){
    if (i==0)
      tree->insert_lianjie(query->JoinList[i].op, query->JoinList[i].tb_name1, query->JoinList[i].col_name1, query->JoinList[i].tb_name2, query->JoinList[i].col_name2, 0);
    else
      tree->insert_lianjie(query->JoinList[i].op, query->JoinList[i].tb_name1, query->JoinList[i].col_name1, query->JoinList[i].tb_name2, query->JoinList[i].col_name2, 1);
  }

  cout << "FROMLIST" << endl;
  vector<char*> tbl;
  for(i = 0; i < from_count; i++){
    tbl.insert(tbl.end(), query->FromList[i].tb_name);
  }  

  tree->insert_kashiji(tbl);

  Message message[100];
  memset(message,0,sizeof(struct Message)*100);
  tree->get(message);

  for(i=0; i<100; i++){  
    if (message[i].key == NULL){// and message[i].key == ""){
        break;
    } 
    cout<<message[i].key<<"\t";  
    for_each(message[i].attribute.begin(),message[i].attribute.end(),print_order);
    cout<<"\t";
    for_each(message[i].value.begin(),message[i].value.end(),print_order);
    cout<<"\t";
    for_each(message[i].op.begin(),message[i].op.end(),print_order_int);
    cout<<"\t";
    if (message[i].tbl_name != NULL)
      cout <<message[i].tbl_name;
    cout <<endl;
  } 

  vector<Message> nodes;
  for(i=0; i<100; i++){  
    if (message[i].key == NULL){// and message[i].key == ""){
        break;
    }
    nodes.insert(nodes.end(), message[i]);
  }
  Logger log("log", LogLevelAll);
  log.SetLogLevel(LogLevelAll);
  log.TraceInfo("执行顺序");
  cout<<endl<<"执行顺序"<<endl;
  vector<Message>::iterator it;
  int tmp_id =0;
  char *s = "tmptb";
  for(it=nodes.begin(); it!=nodes.end();it++){
    if ((*it).key == "⋈"){
      //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
      print_join((*(it-2)).tbl_name,(*(it-1)).tbl_name,(*(it)).attribute,(*(it)).value,(*(it)).op);
      it=nodes.erase(it-2, it);
      char *buf = new char[strlen(s) + sizeof(tmp_id) + 1];
      sprintf(buf, "%s%d", s, tmp_id);
      (*(it)).tbl_name = buf;
      (*(it)).key = buf;
      tmp_id ++;
      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
    }
    if ((*it).key == "x"){
      //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
      print_kashi((*(it-2)).tbl_name, (*(it-1)).tbl_name);
      it=nodes.erase(it-2, it);
      char *buf = new char[strlen(s) + sizeof(tmp_id) + 1];
      sprintf(buf, "%s%d", s, tmp_id);
      (*(it)).tbl_name = buf;
      (*(it)).key = buf;
      tmp_id ++;
      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
    }
    if ((*it).key == "π"){
      //cout<<(*(it-1)).key<<(*(it-0)).key<<" " ;
      print_project((*(it-1)).tbl_name, (*(it)).attribute);
      it=nodes.erase(it-1, it);
      char *buf = new char[strlen(s) + sizeof(tmp_id) + 1];
      sprintf(buf, "%s%d", s, tmp_id);
      (*(it)).tbl_name = buf;
      (*(it)).key = buf;
      tmp_id ++;
      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
    }
    if ((*it).key == "σ"){
      //cout<<(*(it-1)).key<<(*(it-0)).key<<" ";
      char* keys[10];
      memset(keys,0,sizeof(char* )*10);
      for(i = 0;i<(*(it)).value.size();i++){
        keys[i] = (*(it)).value[i];
      }
      print_select((*(it-1)).tbl_name, (*(it)).attribute, (*(it)).op, keys);
      it=nodes.erase(it-1, it);
      char *buf = new char[strlen(s) + sizeof(tmp_id) + 1];
      sprintf(buf, "%s%d", s, tmp_id);
      (*(it)).tbl_name = buf;
      (*(it)).key = buf;
      tmp_id ++;
      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
    }
  }

  tree->PrintTree();

  memset(message,0,sizeof(struct Message)*100);
  tree->get(message);

  for(i=0; i<100; i++){  
    if (message[i].key == NULL){// and message[i].key == ""){
        break;
    } 
    cout<<message[i].key<<"\t";  
    for_each(message[i].attribute.begin(),message[i].attribute.end(),print_order);
    cout<<"\t";
    for_each(message[i].value.begin(),message[i].value.end(),print_order);
    cout<<"\t";
    for_each(message[i].op.begin(),message[i].op.end(),print_order_int);
    cout<<"\t";
    if (message[i].tbl_name != NULL)
      cout <<message[i].tbl_name;
    cout <<endl;
  } 

  vector<Message> nodes1;
  for(i=0; i<100; i++){  
    if (message[i].key == NULL){// and message[i].key == ""){
        break;
    }
    nodes1.insert(nodes1.end(), message[i]);
  }
  log.SetLogLevel(LogLevelAll);
  log.TraceInfo("执行顺序");
  cout<<endl<<"执行顺序"<<endl;
  tmp_id =0;
  char *s1 = "tmptb";
  for(it=nodes1.begin(); it!=nodes1.end();it++){
    if ((*it).key == "⋈"){
      //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
      print_join((*(it-2)).tbl_name,(*(it-1)).tbl_name,(*(it)).attribute,(*(it)).value,(*(it)).op);
      it=nodes1.erase(it-2, it);
      char *buf = new char[strlen(s1) + sizeof(tmp_id) + 1];
      sprintf(buf, "%s%d", s1, tmp_id);
      (*(it)).tbl_name = buf;
      (*(it)).key = buf;
      tmp_id ++;
      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
    }
    if ((*it).key == "x"){
      //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
      print_kashi((*(it-2)).tbl_name, (*(it-1)).tbl_name);
      it=nodes1.erase(it-2, it);
      char *buf = new char[strlen(s1) + sizeof(tmp_id) + 1];
      sprintf(buf, "%s%d", s1, tmp_id);
      (*(it)).tbl_name = buf;
      (*(it)).key = buf;
      tmp_id ++;
      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
    }
    if ((*it).key == "π"){
      //cout<<(*(it-1)).key<<(*(it-0)).key<<" " ;
      print_project((*(it-1)).tbl_name, (*(it)).attribute);
      it=nodes1.erase(it-1, it);
      char *buf = new char[strlen(s1) + sizeof(tmp_id) + 1];
      sprintf(buf, "%s%d", s1, tmp_id);
      (*(it)).tbl_name = buf;
      (*(it)).key = buf;
      tmp_id ++;
      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
    }
    if ((*it).key == "σ"){
      //cout<<(*(it-1)).key<<(*(it-0)).key<<" ";
      char* keys[10];
      memset(keys,0,sizeof(char* )*10);
      for(i = 0;i<(*(it)).value.size();i++){
        keys[i] = (*(it)).value[i];
      }
      print_select((*(it-1)).tbl_name, (*(it)).attribute, (*(it)).op, keys);
      it=nodes1.erase(it-1, it);
      char *buf = new char[strlen(s1) + sizeof(tmp_id) + 1];
      sprintf(buf, "%s%d", s1, tmp_id);
      (*(it)).tbl_name = buf;
      (*(it)).key = buf;
      tmp_id ++;
      cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
    }
  }

  tree->optimize();
  tree->Phy_optimize();



  tree->destroy();
  return 0;
/*  int i;
  if(from_count!=0)
    cout << "SELECT "<< endl;
  if(query->all != 0)
    cout<< "*" << endl;
  if(sel_count!=0){
    cout << "SEL_LIST" <<endl;
    for(i=0; i < sel_count; i++){
      //cout<<" "<<query->SelList[i].col_name<<endl;
      if (NULL ==query->SelList[i].table_name)
        cout<<" "<<query->SelList[i].col_name<<endl;
      else
        cout<< query->SelList[i].table_name << " "<<query->SelList[i].col_name<<endl;
    }
  }

  cout << "FROMLIST" << endl;
  for(i = 0; i < from_count; i++){
    cout<<"\t"<<query->FromList[i].tb_name<<endl;
  }  
  cout << "CONDITION" <<endl;
  for(i = 0; i < cond_count; i++){
    cout << cond_list[i].op <<" "<< cond_list[i].tb_name <<" "<< cond_list[i].tb_id <<" "<< cond_list[i].col_name <<" "<< cond_list[i].value <<" "<< cond_list[i].value_type << endl;
  }
  cout << "JOIN" <<endl;
  for(i = 0; i < join_count; i++){
    cout << query->JoinList[i].op <<" "<< query->JoinList[i].tb_name1 <<" "<< query->JoinList[i].col_name1 << query->JoinList[i].tb_name2 <<" "<< query->JoinList[i].col_name2 << endl;
  }*/
}