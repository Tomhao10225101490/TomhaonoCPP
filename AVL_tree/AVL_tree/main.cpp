//
//  main.cpp
//  splay_tree
//
//  Created by TOM钟浩 on 2023/6/5.
//
#include <iostream>
#include <stack>
#define MAX(a,b) a>b?a:b
using namespace std;
enum Error_code {entry_found,success,underflow,overflow,not_present,duplicate_error,entry_inserted};
enum Balance_factor {left_higher, right_higher,equal_height};
typedef string Key_entry;
typedef string Record_entry;

class Key{
    Key_entry key;
public:
    Key();
    Key(const Key_entry &x);
    Key_entry the_key()const;
};
Key::Key(){
//    key = 0;
    key = "";
}
Key::Key(const Key_entry &x){
    key = x;
}
Key_entry Key::the_key()const{
    return key;
}
bool operator == (const Key &x,const Key &y){
    return x.the_key() == y.the_key();
}
bool operator > (const Key &x,const Key &y){
    return x.the_key() > y.the_key();
}
bool operator < (const Key &x,const Key &y){
    return x.the_key() < y.the_key();
}
bool operator >= (const Key &x,const Key &y){
    return x.the_key() >= y.the_key();
}
bool operator <= (const Key &x,const Key &y){
    return x.the_key() <= y.the_key();
}
bool operator != (const Key &x,const Key &y){
    return x.the_key() != y.the_key();
}
class Record{
public:
    operator Key();//!!!implict conversion from Record to Key//
    Record();
    Record(Record &copy);
    Record(const Record_entry &x,const string &str = "",const string &zhongwen = "");
    Key_entry the_key()const;
    string view();
    string china();
    void operator =(const Record &x);
    void operator =( Record &x);
private:
    Record_entry key;
    string words;
    string zhongwen;
};
void Record::operator =( Record &x){
    key = x.the_key();
    words = x.view();
    zhongwen = x.china();
}
void Record::operator=(const Record &x){
    key = x.the_key();
    words = x.words;
    zhongwen = x.zhongwen;
    
}
Record::Record(Record &copy){
    key = copy.key;
    words = copy.words;
    zhongwen =  copy.zhongwen;
}
string  Record::china(){
    return zhongwen;
}
string Record::view(){
    return words;
}
Record::operator Key(){
    Key tmp(key);
    return tmp;
}
Record::Record(){
    key = "";
//    key = 0;
    words = "";
    zhongwen = "";
}
Record::Record(const Record_entry &x,const string &str,const string &zhong){
    key = x;
    words = str;
    zhongwen = zhong;
}
Key_entry Record::the_key()const{
    return key;
}
void print(Record &x){
    cout<<x.the_key()<<' ';
}
bool operator == (const Record &x,const Record &y){
    return x.the_key() == y.the_key();
}
bool operator > (const Record &x,const Record &y){
    return x.the_key() > y.the_key();
}
bool operator < (const Record &x,const Record &y){
    return x.the_key() < y.the_key();
}
bool operator >= (const Record &x,const Record &y){
    return x.the_key() >= y.the_key();
}
bool operator <= (const Record &x,const Record &y){
    return x.the_key() <= y.the_key();
}
bool operator != (const Record &x,const Record &y){
    return x.the_key() != y.the_key();
}

template <class Entry>
class Binary_node{
  //data member;
public:
    Balance_factor balance;
    Entry data;
    Binary_node<Entry> *left;
    Binary_node<Entry> *right;
  //constructors;
    void set_balance(Balance_factor b);
    Balance_factor get_balance()const;
    Binary_node();
    Binary_node(const Entry &x);
};
template<class Entry>
void Binary_node<Entry>::set_balance(Balance_factor b){
    balance = b;
}
template<class Entry>
Balance_factor Binary_node<Entry>::get_balance()const
{
    return balance;
}

template <class Entry>
Binary_node<Entry>::Binary_node(){
    left =  NULL;
    right =  NULL;
    balance = equal_height;
}
template <class Entry>
Binary_node<Entry>::Binary_node(const Entry &x){
    data = x;
    left =  NULL;
    right =  NULL;
    balance = equal_height;
}


template <class Entry>
class Binary_tree{
public:
    Binary_tree();
    bool empty()const;
    void preorder(void(*visit)(Entry &));
    void inorder(void(*visit)(Entry &));
    void postorder(void(*visit)(Entry &));
    int size() const;
    int height() const;
    int re_height() const;
    int recursive_height(Binary_node<Entry> *sub_root)const;
    Error_code insert(const Entry &new_data);
    Error_code BST_insert(const Entry &new_data);
    Error_code remove(Entry &new_data);
    Error_code tree_search( Entry &target);
protected:
    Error_code avl_remove(Binary_node<Entry>* &sub_root,Entry &new_data, bool &shorter);
    Error_code avl_insert(Binary_node<Entry>* &sub_root,const Entry &new_data, bool &taller );
    void rotate_left(Binary_node<Entry> *&current);
    void rotate_right(Binary_node<Entry> *&current);
    void right_balance(Binary_node<Entry> *&current);
    bool right_balance2(Binary_node<Entry> *&current);
    void left_balance(Binary_node<Entry> *&current);
    bool left_balance2(Binary_node<Entry> *&current);
    void recursive_preorder(Binary_node<Entry> *sub_root,void (*visit)(Entry &));
    void recursive_inorder(Binary_node<Entry> *sub_root,void (*visit)(Entry &));
    void recursive_postorder(Binary_node<Entry> *sub_root,void (*visit)(Entry &));
    Binary_node<Entry>* search_for_node(Binary_node<Entry>* sub_root,const Entry &target)const;
    Error_code search_and_insert(Binary_node<Entry>*&sub_root,const Entry &new_data);
    Error_code remove_root(Binary_node<Entry>* &sub_root);
    Error_code search_and_destroy(Binary_node<Entry>* &sub_root,const Entry &target);
    Binary_node<Entry> *root;
    int count;
};
template<class Entry>
Error_code Binary_tree<Entry>::avl_insert(Binary_node<Entry> *&sub_root, const Entry &new_data, bool &taller){
    Error_code result = success;
    if(sub_root == NULL){
        sub_root = new Binary_node<Entry>(new_data);
        taller = true;
    }
    else if(new_data == sub_root->data){
        result  = duplicate_error;
        taller = false;
    }
    else if(new_data < sub_root->data){
        result = avl_insert(sub_root->left, new_data, taller);
        if(taller == true)
            switch (sub_root->get_balance()) {
                case right_higher:
                    sub_root->set_balance(equal_height);
                    taller = false;
                    break;
                case equal_height:
                    sub_root->set_balance(left_higher);
                    break;
                case left_higher:
                    left_balance(sub_root);
                    taller = false;
                    break;
            }
    }
    else{
        result = avl_insert(sub_root->right, new_data, taller);
        if(taller == true)
            switch (sub_root->get_balance()) {
                case left_higher:
                    sub_root->set_balance(equal_height);
                    taller = false;
                    break;
                case equal_height:
                    sub_root->set_balance(right_higher);
                    break;
                case right_higher:
                    right_balance(sub_root);
                    taller = false;
                    break;
            }
    }
    return  result;
}




template <class Entry>
Binary_tree<Entry>::Binary_tree(){
    root = NULL;
    count = 0;
}

template <class Entry>
bool Binary_tree<Entry>::empty()const{
    return root==NULL;
}
template <class Entry>
void Binary_tree<Entry>::preorder(void (*visit)(Entry &)){
    recursive_preorder(root, visit);
}
template <class Entry>
void Binary_tree<Entry>::recursive_preorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &)){
    if(sub_root != NULL){
        (*visit)(sub_root ->data);
        recursive_preorder(sub_root->left, visit);
        recursive_preorder(sub_root->right, visit);
    }
}
template <class Entry>
void Binary_tree<Entry>::inorder(void (*visit)(Entry &)){
    recursive_inorder(root, visit);
}
template <class Entry>
void Binary_tree<Entry>::recursive_inorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &)){
    if(sub_root != NULL){
        recursive_inorder(sub_root->left, visit);
        (*visit)(sub_root ->data);
        recursive_inorder(sub_root->right, visit);
    }
}template <class Entry>
void Binary_tree<Entry>::postorder(void (*visit)(Entry &)){
    recursive_postorder(root, visit);
}
template <class Entry>
void Binary_tree<Entry>::recursive_postorder(Binary_node<Entry> *sub_root, void (*visit)(Entry &)){
    if(sub_root != NULL){
        recursive_postorder(sub_root->left, visit);
        recursive_postorder(sub_root->right, visit);
        (*visit)(sub_root ->data);
    }
}

template <class Entry>
int Binary_tree<Entry>::size()const{
    return count;
}

template <class Entry>
int Binary_tree<Entry>::height()const{
    int count = size();
    if(count == 0) return -1;
    int tmp = 1;
    int k = 0;
    for(k = 0; tmp <= count ; k++) tmp *= 2;
    return k-1;
}
template <class Entry>
int Binary_tree<Entry>::re_height()const{
   return recursive_height(root);
}
template <class Entry>
int Binary_tree<Entry>::recursive_height(Binary_node<Entry> *sub_root)const{
    if(sub_root == NULL) return 0;
    else{
        int temp = MAX(recursive_height(sub_root->left),recursive_height(sub_root->right));
//        int temp = recursive_height(sub_root->left);
        return temp + 1;
    }
}

template <class Entry>
Error_code Binary_tree<Entry>::insert(const Entry &new_data){
    bool taller;
    return avl_insert(root,new_data,taller);
}

template<class Entry>
void print(Entry &x){
    cout<<x<<' ';
}

template <class Record>
Error_code Binary_tree<Record>::remove(Record &new_data){
    bool shorter = true;
    return avl_remove(root,new_data,shorter);
}
template <class Entry>
Error_code Binary_tree<Entry>::avl_remove(Binary_node<Entry> *&sub_root, Entry &new_data, bool &shorter){
    Error_code result = success;
    Record sub_record;
    if(sub_root == NULL){
        shorter = false;
        return not_present;
    }
    else if(new_data == sub_root->data){//删除节点，操作预报二分查找一样
        Binary_node<Entry>* to_delete = sub_root;
        //remember to delete it at end
        if(sub_root->right == NULL){ // right sub_tree is NULL
            sub_root = sub_root->left;
            shorter = true;
            delete to_delete;
            return success;
        }
        else if(sub_root->left == NULL){//left sub_tree is NULL
            sub_root = sub_root->right;
            shorter = true;
            delete to_delete;
            return success;
        }
        else{
            // neither subtree is empty
            to_delete = sub_root->left;
            //move left to find predecessor
            Binary_node<Entry>* parent = sub_root;
            //parent of to_delete
            while(to_delete->right != NULL){
                parent = to_delete;
                to_delete = to_delete->right;
            }
            new_data = to_delete->data;
            sub_record = new_data;
        }
    }
    if(new_data < sub_root->data){
        result = avl_remove(sub_root->left, new_data, shorter);
        if(sub_record.the_key() != "")sub_root->data = sub_record;
        //move data from to_delete to root
        if(shorter == true)
            switch(sub_root->get_balance()){
                case left_higher:
                    sub_root->set_balance(equal_height);
                    break;
                case equal_height:
                    sub_root->set_balance(right_higher);
                    shorter = false;
                    break;
                case right_higher:
                    shorter = right_balance2(sub_root);
                    break;
            }
    }
    if(new_data > sub_root->data){
        result = avl_remove(sub_root->right, new_data, shorter);
        if(sub_record.the_key() != "")sub_root->data = sub_record;
        //move data from to_delete to root
        if(shorter == true)
            switch(sub_root->get_balance()){
                case left_higher:
                    shorter = left_balance2(sub_root);
                    break;
                case equal_height:
                    sub_root->set_balance(left_higher);
                    shorter = false;
                    break;
                case right_higher:
                    sub_root->set_balance(equal_height);
                    break;
            }
    }
    return result;
}




template <class Record>
Error_code Binary_tree<Record>::search_and_destroy(Binary_node<Record> *&sub_root, const Record &target){
    if(sub_root == NULL || sub_root->data==target){
        return remove_root(sub_root);
    }
    else if(target < sub_root->data){
        return search_and_destroy(sub_root->left, target);
    }
    else
        return search_and_destroy(sub_root->right, target);
}

template <class Record>
Error_code Binary_tree<Record>:: remove_root(Binary_node<Record> *&sub_root){
    if(sub_root == NULL)return not_present;
    Binary_node<Record>* to_delete = sub_root;
    if(sub_root->right == NULL) sub_root = sub_root->left;
    else if(sub_root->left == NULL) sub_root = sub_root->right;
    else {
        to_delete = sub_root->left;
        Binary_node<Record>* parent = sub_root;
        while (to_delete->right != NULL) {
            parent = to_delete;
            to_delete  =to_delete->right;
        }
        sub_root->data = to_delete->data;
        if(parent == sub_root) sub_root->left = to_delete->left;
        else parent->right = to_delete->left;
    }
    delete to_delete;
    return success;
}

template <class Record>
Error_code Binary_tree<Record>:: BST_insert(const Record &new_data){
    Error_code result = search_and_insert(root, new_data);
    if(result == success) count++;
    return result;
}
template <class Record>
Error_code Binary_tree<Record>:: search_and_insert(Binary_node<Record> * &sub_root, const Record &new_data){
    if(sub_root ==NULL){
        sub_root = new Binary_node<Record>(new_data);
        return success;
    }
    else if (new_data < sub_root->data)
        return search_and_insert(sub_root->left, new_data);
    else if (new_data > sub_root->data)
        return search_and_insert(sub_root->right, new_data);
    else return duplicate_error;
}



template <class Record>
Error_code Binary_tree<Record>::tree_search( Record &target){
    Error_code result = success;
    Binary_node<Record> *found = search_for_node(root,target);
    if(found == NULL)
    {
        cout<<"NULL"<<endl;
        result = not_present;
    }
    else {
        target = found->data;
    }
    return result;
}
template <class Record>
Binary_node<Record>* Binary_tree<Record>::search_for_node(Binary_node<Record> *sub_root, const Record &target)const{
    if(sub_root == NULL || sub_root->data == target){
        return sub_root;
    }
    else if(sub_root->data < target){
        Record tmp = sub_root->data;
        cout<<tmp.view()<<' ';
        return search_for_node(sub_root->right, target);
    }
    else{
        Record tmp = sub_root->data;
        cout<<tmp.view()<<' ';
        return search_for_node(sub_root->left, target);
    }
}
//----------------------------------------------------------------------2023.6.5

template<class Entry>
void Binary_tree<Entry>::rotate_right(Binary_node<Entry> *&current){
   //just like the rotate in AVL_tree
    if(current==NULL || current->left==NULL)
        cout<<"WARNING"<<endl;
    Binary_node<Entry> *left_tree = current->left;
    current->left = left_tree->right;
    left_tree->right = current;
    current = left_tree;//update the current
}
template<class Entry>
void Binary_tree<Entry>::rotate_left(Binary_node<Entry> *&current){
   //just like the rotate in AVL_tree
    if(current==NULL || current->right==NULL)
        cout<<"WARNING"<<endl;
    Binary_node<Entry> *right_tree = current->right;
    current->right = right_tree->left;
    right_tree->left = current;
    current = right_tree;//update the current
}
template<class Entry>
void Binary_tree<Entry>::right_balance(Binary_node<Entry> *&current){
    Binary_node<Entry>* &right_tree = current->right;
    switch (right_tree->get_balance()) {
        case right_higher:
            current->set_balance(equal_height);
            right_tree->set_balance(equal_height);
            rotate_left(current);
            break;
        case equal_height:
            cout<<"WARNING"<<endl;
            break;
        case left_higher:
            Binary_node<Entry>*sub_tree = right_tree->left;
            switch(sub_tree->get_balance()){
                case equal_height:
                    current->set_balance(equal_height);
                    right_tree->set_balance(equal_height);
                    break;
                case left_higher:
                    current->set_balance(equal_height);
                    right_tree->set_balance(right_higher);
                    break;
                case right_higher:
                    current->set_balance(left_higher);
                    right_tree->set_balance(equal_height);
                    break;
            }
            sub_tree->set_balance(equal_height);
            rotate_right(right_tree);
            rotate_left(current);
            break;
    }
}

template<class Entry>
bool Binary_tree<Entry>::right_balance2(Binary_node<Entry> *&current){
    bool shorter;
    Binary_node<Entry>* &right_tree = current->right;
    switch (right_tree->get_balance()) {
        case right_higher:
            current->set_balance(equal_height);
            right_tree->set_balance(equal_height);
            rotate_left(current);
            shorter = true;
            break;
        case equal_height:
            right_tree->set_balance(left_higher);
            rotate_left(current);
            shorter = false;
            break;
        case left_higher:// double rotate left
            Binary_node<Entry>*sub_tree = right_tree->left;
            switch(sub_tree->get_balance()){
                case equal_height:
                    current->set_balance(equal_height);
                    right_tree->set_balance(equal_height);
                    break;
                case left_higher:
                    current->set_balance(equal_height);
                    right_tree->set_balance(right_higher);
                    break;
                case right_higher:
                    current->set_balance(left_higher);
                    right_tree->set_balance(equal_height);
                    break;
            }
            sub_tree->set_balance(equal_height);
            rotate_right(right_tree);
            rotate_left(current);
            shorter = true;
            break;
    }
    return shorter;
}

template<class Entry>
bool Binary_tree<Entry>::left_balance2(Binary_node<Entry> *&current){
    bool shorter;
    Binary_node<Entry>* &left_tree = current->left;
    switch (left_tree->get_balance()) {
        case left_higher:
            current->set_balance(equal_height);
            left_tree->set_balance(equal_height);
            rotate_right(current);
            shorter = true;
            break;
        case equal_height:
            left_tree->set_balance(right_higher);
            rotate_right(current);
            shorter = false;
            break;
        case right_higher:// double rotate left
            Binary_node<Entry>*sub_tree = left_tree->left;
            switch(sub_tree->get_balance()){
                case equal_height:
                    current->set_balance(equal_height);
                    left_tree->set_balance(equal_height);
                    break;
                case right_higher:
                    current->set_balance(equal_height);
                    left_tree->set_balance(left_higher);
                    break;
                case left_higher:
                    current->set_balance(right_higher);
                    left_tree->set_balance(equal_height);
                    break;
            }
            sub_tree->set_balance(equal_height);
            rotate_left(left_tree);
            rotate_right(current);
            shorter = true;
            break;
    }
    return shorter;
}



template<class Entry>
void Binary_tree<Entry>::left_balance(Binary_node<Entry> *&current){
    Binary_node<Entry>* &left_tree = current->left;
    switch (left_tree->get_balance()) {
        case left_higher:
            current->set_balance(equal_height);
            left_tree->set_balance(equal_height);
            rotate_right(current);
            break;
        case equal_height:
            cout<<"WARNING"<<endl;
            break;
        case right_higher:
            Binary_node<Entry>*sub_tree = left_tree->right;
            switch(sub_tree->get_balance()){
                case equal_height:
                    current->set_balance(equal_height);
                    left_tree->set_balance(equal_height);
                    break;
                case right_higher:
                    current->set_balance(equal_height);
                    left_tree->set_balance(left_higher);
                    break;
                case left_higher:
                    current->set_balance(right_higher);
                    left_tree->set_balance(equal_height);
                    break;
            }
            sub_tree->set_balance(equal_height);
            rotate_left(left_tree);
            rotate_right(current);
            break;
    }
}
int main()
{
    Binary_tree<Record> Mytree;
    int num;
    cin>>num;
    for(int i = 0 ;i <num; i++){
        string wword;
        string zzhong;
        cin>>wword>>zzhong;
        Mytree.insert(Record(wword,wword,zzhong));
    }
    int deleting_num;
    cin>>deleting_num;
    for(int i = 0 ;i <deleting_num ; i++){
        string deleting_word;
        cin>>deleting_word;
         Record ddlet = Record(deleting_word);
        Mytree.remove(ddlet);
    }
       string asking1,asking2;
        cin>>asking1>>asking2;
        Record eye1 = Record(asking1,asking1,asking1);
        Record eye2 = Record(asking2,asking2,asking2);
        if(Mytree.tree_search(eye1) == success)
        cout<<eye1.view()<<' '<<eye1.china()<<endl;
        if(Mytree.tree_search(eye2) == success)
        cout<<eye2.view()<<' '<<eye2.china()<<endl;
    return 0;
}


