#include <iostream>
#include <stack>
#define MAX(a,b) a>b?a:b
using namespace std;
enum Error_code {success,underflow,overflow,not_present,duplicate_error};

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

int main()
{
    Binary_tree<Record> mytree;
//    Record eye = Record(4," "," ");
//    mytree.tree_search(eye);
//    cout<<eye.view()<<' '<<eye.china()<<endl;
    int n;
    cin>>n;
    for(int i = 0;i < n; i++){
        string word;
        string zhong;
        cin>>word>>zhong;
        mytree.BST_insert(Record(word,word,zhong));
    }
    int deleting;
    cin>>deleting;
    for(int i = 0 ;i < deleting ; i++){
        string bitch;
        cin>>bitch;
        mytree.remove(Record(bitch,bitch,bitch));
    }
    string asking1,asking2;
    cin>>asking1>>asking2;
    Record eye1 = Record(asking1,asking1,asking1);
    Record eye2 = Record(asking2,asking2,asking2);
    if(mytree.tree_search(eye1) == success)
    cout<<eye1.view()<<' '<<eye1.china()<<endl;
    if(mytree.tree_search(eye2) == success)
    cout<<eye2.view()<<' '<<eye2.china()<<endl;
//    cout<<"Tree size is : "<<mytree.size()<<endl;
//    cout<<"Preorder: "<<endl;
//    mytree.preorder(print);
//    cout<<endl;
//    cout<<"inorder: "<<endl;
//    mytree.inorder(print);
//    cout<<endl;
//    cout<<"postorder: "<<endl;
//    mytree.postorder(print);
//    cout<<endl;
    
    
//    mytree.remove(Record(4," "," "));
//    cout<<"Tree size is : "<<mytree.size()<<endl;
//    cout<<"Preorder: "<<endl;
//    mytree.preorder(print);
//    cout<<endl;
//    cout<<"inorder: "<<endl;
//    mytree.inorder(print);
//    cout<<endl;
//    cout<<"postorder: "<<endl;
//    mytree.postorder(print);
//    cout<<endl;
    return 0;
}

