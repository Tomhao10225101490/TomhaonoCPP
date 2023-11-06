#include <iostream>
#include <stack>
#include <cmath>
#define MAX(a,b) a>b?a:b
using namespace std;

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
    bool find_way(int len);
    Binary_node<Entry> *root;
protected:
    void recursive_preorder(Binary_node<Entry> *sub_root,void (*visit)(Entry &));
    void recursive_inorder(Binary_node<Entry> *sub_root,void (*visit)(Entry &));
    void recursive_postorder(Binary_node<Entry> *sub_root,void (*visit)(Entry &));
    int count;
};

template <class Entry>
bool Binary_tree<Entry>::find_way(int len){
//    double high = re_height();
//    if(high==0){
//        return len == root->data;
//    }
//    for(int i = pow(2, high) -1 ; i < size(); i++){
//        int tmp_sum = 0;
//      //----------------------------------------------
//        stack<int> numbers;
//        int item = 0;
//        int tmpcount = i;
//        while(tmpcount > 0){
//            if(tmpcount%2 == 0){
//                numbers.push(2);//stand for right son
//            }
//            else{
//                numbers.push(1);// stand for left son
//            }
//            tmpcount = (tmpcount - 1)/2;//get to the parent
//        }
//        Binary_node<Entry> *current = root;
//        while(numbers.size() > 1){
//            item = numbers.top();
//            tmp_sum += current->data;
//            if(item == 1) {
//                current = current-> left;
//            }
//            if(item == 2) {
//                current = current-> right;
//            }
//            numbers.pop();
//        }
//        tmp_sum += current->data;
//       item = numbers.top();
//        if(item == 1) tmp_sum += current->left->data;
//        if(item == 2) tmp_sum += current->right->data;
//        //----------------------------------------------------
////        cout<<"the"<< i <<"path:  "<<tmp_sum<<endl;
//        if(tmp_sum == len) return true;
//    }
    return false;
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
    if(sub_root == NULL) return -1;
        int temp = MAX(recursive_height(sub_root->left),recursive_height(sub_root->right));
//        int temp = recursive_height(sub_root->left);
        return temp + 1;
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
    if(current->data == "null") {
        current->left = new Binary_node<Entry>("null");
        current->left = new Binary_node<Entry>("null");
        count += 2;
        insert(x);
        return ;
    }
    if(item == 1) current->left = new Binary_node<Entry>(x);
    if(item == 2) current->right =new Binary_node<Entry>(x);
    count++;
    }



template<class Entry>
void print(Entry &x){
    cout<<x<<' ';
}

class Solution {
public:
     bool isSameTree(Binary_node<string>* p, Binary_node<string>*q) {
             if(p==NULL || q==NULL)
             {
                 if(q == NULL)
                     return p==NULL||p->data=="null";
                 else if(p == NULL)
                     return q==NULL||q->data=="null";
                 return p==q;
             }
             if(p->data=="null" && q->data=="null")
                 return true;
             return p->data==q->data && isSameTree(p->left,q->right)&&isSameTree(p->right,q->left);
    }
    bool isSymmetric(Binary_node<string>* root) {
          return isSameTree(root->left,root->right);
    }
};

int main()
{
    Binary_tree<string> Mytree;
    int num;
    cin>>num;
    for(int i = 0;i < num; i++){
        string read;
        cin>>read;
        Mytree.insert(read);
    }
    cout<<Mytree.re_height()<<' ';
//    cout<<Mytree.size()<<' ';
    Solution so;
    if(so.isSymmetric(Mytree.root)==false)
    {
        cout<<"false"<<endl;
    }
    else cout<<"true"<<endl;
    return 0;
}
