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
    Record(const Record_entry &x,const string &str,const string &zhongwen);
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
    words = "";
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
    Entry data;
    Binary_node *left;
    Binary_node *right;
  //constructors;
    Binary_node(){
        left =  NULL;
        right =  NULL;
    }
    Binary_node(const Entry &x){
        data = x;
        left = NULL;
        right = NULL;
    }
};

template <class Entry>
class Binary_tree{
public:
    Error_code splay(const Entry &target);
    //splay 方法负责插入或者查询节点target
    //如果target在二分查找树中不存在就插入该节点
    //如果target在二分查找树中存在就查询该节点的详细信息
    //方法结束后，target对应的节点为二分查找树的根节点
    Binary_tree();
    bool empty()const;
    void preorder(void(*visit)(Entry &));
    void inorder(void(*visit)(Entry &));
    void postorder(void(*visit)(Entry &));
    int size() const;
    int height() const;
    int re_height() const;
    int recursive_height(Binary_node<Entry> *sub_root)const;
    void insert(Entry &);
    Error_code BST_insert(const Entry &new_data);
    Error_code remove(const Entry &target);
    Error_code tree_search( Entry &target);
protected:
    void link_left(Binary_node<Entry> *&current,Binary_node<Entry> *&last_small);
    void link_right(Binary_node<Entry> *&current,Binary_node<Entry> *&first_large);
    void rotate_left(Binary_node<Entry> *&current);
    void rotate_right(Binary_node<Entry> *&current);
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
void Binary_tree<Entry>::insert(Entry &x){
    if(empty()){
        root = new Binary_node<Entry>(x);
        count++;
        return;
    }
    stack<int> numbers;
    int item = 0;
    int tmpcount = size();
    while(tmpcount > 0){
        if(tmpcount%2 == 0){
            numbers.push(2);//stand for right son
        }
        else{
            numbers.push(1);// stand for left son
        }
        tmpcount = (tmpcount - 1)/2;//get to the parent
    }
    Binary_node<Entry> *current = root;
    while(numbers.size() > 1){
        item = numbers.top();
        if(item == 1) current = current-> left;
        if(item == 2) current = current-> right;
        numbers.pop();
    }
   item = numbers.top();
    if(item == 1) current->left = new Binary_node<Entry>(x);
    if(item == 2) current->right =new Binary_node<Entry>(x);
    count++;
    }

template<class Entry>
void print(Entry &x){
    cout<<x<<' ';
}

template <class Record>
Error_code Binary_tree<Record>::remove(const Record &target){
    Error_code result = search_and_destroy(root, target);
    if(result == success)count--;
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
Error_code Binary_tree<Entry>::splay(const Entry &target){
    Binary_node<Entry> *dummy = new Binary_node<Entry>;
    Binary_node<Entry> *current = root;
    Binary_node<Entry> *child;
    Binary_node<Entry> *last_small = dummy;
    Binary_node<Entry> *first_large = dummy;
    //search for  target while splaying the tree
    while(current!=NULL && current->data!=target){
        if(target < current->data){
            child = current->left;
            if(child==NULL || target == child->data){
                link_right(current, first_large);
            }
            else if(target < child->data){//zig-zig
                rotate_right(current);
                link_right(current, first_large);
            }
            else{  //zig-zag
                link_right(current, first_large);
                link_left(current, last_small);
            }
        }
        else{//case: target > curent->data
            child = current->right;
            if(child==NULL || target== child->data){
                link_left(current, last_small);
            }
            else if(target > child->data){//zag-zag move
                rotate_left(current);
                link_left(current, last_small);
            }
            else{  //zag-zig move
                rotate_right(current);
                link_right(current, first_large);
            }
        }
    }
    //move root to the curent node ,which is created if necessary
    Error_code result;
    if(current == NULL){
        current = new Binary_node<Entry>(target);
        result = entry_inserted;
        last_small->right = first_large->left = NULL;
    }
    else{
        result = entry_found;
        //move remaining central nodes
        last_small->right = current->left;
        first_large->left = current->right;
    }
    root = current;
    root->right =dummy->left;
    root->left =  dummy->right;
    delete dummy;
    return result;
}

template<class Entry>
void Binary_tree<Entry>::link_right(Binary_node<Entry> *&current, Binary_node<Entry> *&first_large){
    //curent 指向central tree 的根节点
    //first_large 指向 last-key tree 的最小值
    first_large->left = current;
    first_large = current;
    current = current->left;
}
template<class Entry>
void Binary_tree<Entry>::link_left(Binary_node<Entry> *&current, Binary_node<Entry> *&last_small){
    //curent 指向central tree 的根节点
    //last_small 指向 first-key tree 的最大值
    last_small->right = current;
    last_small = current;
    current = current->right;
}

template<class Entry>
void Binary_tree<Entry>::rotate_right(Binary_node<Entry> *&current){
   //just like the rotate in AVL_tree
    Binary_node<Entry> *left_tree = current->left;
    current->left = left_tree->right;
    left_tree->right = current;
    current = left_tree;//update the current
}
template<class Entry>
void Binary_tree<Entry>::rotate_left(Binary_node<Entry> *&current){
   //just like the rotate in AVL_tree
    Binary_node<Entry> *right_tree = current->right;
    current->right = right_tree->left;
    right_tree->left = current;
    current = right_tree;//update the current
}

int main()
{
    Binary_tree<int> Mytree;
    Mytree.BST_insert(13);
    Mytree.BST_insert(5);
    Mytree.BST_insert(16);
    Mytree.BST_insert(3);
    Mytree.BST_insert(10);
    Mytree.BST_insert(14);
    Mytree.BST_insert(18);
    Mytree.BST_insert(2);
    Mytree.BST_insert(4);
    Mytree.BST_insert(8);
    Mytree.BST_insert(11);
    Mytree.BST_insert(15);
    Mytree.BST_insert(17);
    Mytree.BST_insert(20);
    Mytree.BST_insert(1);
    Mytree.BST_insert(7);
    Mytree.BST_insert(9);
    Mytree.BST_insert(12);
    Mytree.BST_insert(19);
    Mytree.BST_insert(6);
    cout<<"Preorder:"<<endl;
    Mytree.preorder(print);
    cout<<endl;
    cout<<"inorder:"<<endl;
    Mytree.inorder(print);
    cout<<endl;
    cout<<"postorder:"<<endl;
    Mytree.postorder(print);
    cout<<endl;
    return 0;
}


