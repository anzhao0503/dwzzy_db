int Printdmy(){
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

  cout << "JOIN" <<endl;
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

  cout<<endl<<"执行顺序"<<endl;
  vector<Message>::iterator it;
  int tmp_id =0;
  char *s = "tmptb";
  for(it=nodes.begin(); it!=nodes.end();it++){
    if (it != nodes.end() - 1) {
      if ((*it).key == "⋈"){
        //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
        print_join((*(it-2)).tbl_name,(*(it-1)).tbl_name,(*(it)).attribute,(*(it)).value,(*(it)).op);
        
          int left_tb_id = table_manager->GetTableId((*(it-2)).tbl_name);
          int right_tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
          vector<int> cols1;
          vector<int> cols2;
        for (int i = 0; i < (*(it)).attribute.size(); i++) {
        int col = table_manager->tables[left_tb_id]->GetAttrId((*(it)).attribute[i]);
        cols1.push_back(col);
        }
        for (int i = 0; i < (*(it)).value.size(); i++) {
        int col = table_manager->tables[right_tb_id]->GetAttrId((*(it)).value[i]);
        cols2.push_back(col);
        }
          tmp_id = table_manager->NestedLoopJoinTmp(left_tb_id, right_tb_id, cols1, cols2, (*(it)).op, false); 


          it=nodes.erase(it-2, it);
        
          string str = table_manager->GetTableName(tmp_id);
        char* s = new char[str.size() + 1];
          copy(str.begin(), str.end(), s);
          s[str.size()] = '\0';
        (*(it)).tbl_name = s;

        cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
      }
      if ((*it).key == "x"){
        //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
        print_kashi((*(it-2)).tbl_name, (*(it-1)).tbl_name);

          int left_tb_id = table_manager->GetTableId((*(it-2)).tbl_name);
          int right_tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
          tmp_id = table_manager->NestedLoopCartesianProductTmp(left_tb_id, right_tb_id, false); 
        it=nodes.erase(it-2, it);

          string str = table_manager->GetTableName(tmp_id);
        char* s = new char[str.size() + 1];
          copy(str.begin(), str.end(), s);
          s[str.size()] = '\0';
        (*(it)).tbl_name = s;

        cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
      }
      if ((*it).key == "π"){
        
        print_project((*(it-1)).tbl_name, (*(it)).attribute);
        int tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
        vector<int> cols;
          if (strcmp((*(it)).attribute[0], "*") != 0) {
          for (int i = 0; i < (*(it)).attribute.size(); i++) {
          int col = table_manager->tables[tb_id]->GetAttrId((*(it)).attribute[i]);
          cols.push_back(col);
          }
          }
          for_each(cols.begin(),cols.end(),print_order_int);

        tmp_id = table_manager->ProjectTmp(tb_id, cols);
        
          it=nodes.erase(it-1, it);
        

          string str = table_manager->GetTableName(tmp_id);
        char* s = new char[str.size() + 1];
          copy(str.begin(), str.end(), s);
          s[str.size()] = '\0';
        (*(it)).tbl_name = s;
        
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
        
          int tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
        vector<int> cols;
        for (int i = 0; i < (*(it)).attribute.size(); i++) {
        int col = table_manager->tables[tb_id]->GetAttrId((*(it)).attribute[i]);
        cols.push_back(col);
        }
        tmp_id = table_manager->SelectTmp(tb_id, cols, (*(it)).op, keys);
        
          it=nodes.erase(it-1, it);
          string str = table_manager->GetTableName(tmp_id);
          cout <<str <<endl;
        char* s = new char[str.size() + 1];
          copy(str.begin(), str.end(), s);
          s[str.size()] = '\0';
        (*(it)).tbl_name = s;
        (*(it)).key = s;
        cout<<"\t\t\t\t\t\t"<<(*(it)).tbl_name<<endl;
      }
     } else {
      if ((*it).key == "⋈"){
        //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
        print_join((*(it-2)).tbl_name,(*(it-1)).tbl_name,(*(it)).attribute,(*(it)).value,(*(it)).op);
        
          int left_tb_id = table_manager->GetTableId((*(it-2)).tbl_name);
          int right_tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
          vector<int> cols1;
          vector<int> cols2;
        for (int i = 0; i < (*(it)).attribute.size(); i++) {
        int col = table_manager->tables[left_tb_id]->GetAttrId((*(it)).attribute[i]);
        cols1.push_back(col);
        }
        for (int i = 0; i < (*(it)).value.size(); i++) {
        int col = table_manager->tables[right_tb_id]->GetAttrId((*(it)).value[i]);
        cols2.push_back(col);
        }
          table_manager->NestedLoopJoin(left_tb_id, right_tb_id, cols1, cols2, (*(it)).op, false); 


          it=nodes.erase(it-2, it);
      }
      if ((*it).key == "x"){
        //cout<<(*(it-2)).key<<(*(it-1)).key<<(*(it-0)).key<<" ";
        print_kashi((*(it-2)).tbl_name, (*(it-1)).tbl_name);

          int left_tb_id = table_manager->GetTableId((*(it-2)).tbl_name);
          int right_tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
          table_manager->NestedLoopCartesianProduct(left_tb_id, right_tb_id, false); 

        it=nodes.erase(it-2, it);
      }
      if ((*it).key == "π"){
        
        print_project((*(it-1)).tbl_name, (*(it)).attribute);
        int tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
        vector<int> cols;
          if (strcmp((*(it)).attribute[0], "*") != 0) {
          for (int i = 0; i < (*(it)).attribute.size(); i++) {
          int col = table_manager->tables[tb_id]->GetAttrId((*(it)).attribute[i]);
          cols.push_back(col);
          }
          }
          for_each(cols.begin(),cols.end(),print_order_int);

        table_manager->Project(tb_id, cols);
        
          it=nodes.erase(it-1, it);
      }
      if ((*it).key == "σ"){
        //cout<<(*(it-1)).key<<(*(it-0)).key<<" ";
        char* keys[10];
        memset(keys,0,sizeof(char* )*10);
        for(i = 0;i<(*(it)).value.size();i++){
           keys[i] = (*(it)).value[i];
        }
        print_select((*(it-1)).tbl_name, (*(it)).attribute, (*(it)).op, keys);
        
          int tb_id = table_manager->GetTableId((*(it-1)).tbl_name);
        vector<int> cols;
        for (int i = 0; i < (*(it)).attribute.size(); i++) {
        int col = table_manager->tables[tb_id]->GetAttrId((*(it)).attribute[i]);
        cols.push_back(col);
        }
        table_manager->Select(tb_id, cols, (*(it)).op, keys);
        
          it=nodes.erase(it-1, it);
      }
     }
  }


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
/*
int main(){
  cout<<"begin"<<endl;
  InitQuery();
  while(1)
    {
       parser_init();
       int rnt = yyparse();
       if(rnt==-1)
            break;
    }
  DestoryQuery();
  return 0;
}
*/

