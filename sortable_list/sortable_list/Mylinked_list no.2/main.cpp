//相较于第一版，我们用current来记录最后一次操作的node，用current_position来记录它的位置
#ifndef Mylinked_listno2
#define Mylinked_listno2

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;
enum Error_code{overflow,underflow,range_Error,success};

struct web{
    string str;
    int xishu;
    int rank;
};

template <class Node_entry>
struct Node{
  //data members
    Node_entry entry;
    Node<Node_entry> *next;
    //constructors
    Node();
    Node(Node_entry item,Node<Node_entry> *link = nullptr);
};
template<class Node_entry>
Node<Node_entry>::Node(){
    next = nullptr;
}
template<class Node_entry>
Node<Node_entry>::Node(Node_entry item,Node<Node_entry> *link){
    entry = item;
    next = link;
}

template<class List_entry>
class List{
public:
    ~List();
    List();
    List(const List<List_entry> &entry);
    void operator = (const List<List_entry> &copy);
    int size()const;
    bool full()const;
    bool empty()const;
    void clear();
    Error_code insert(int position,const List_entry& x);
    Error_code remove(int position,List_entry& x);
    Error_code retrieve(int position ,List_entry& x)const;
    Error_code replace(int position ,List_entry& x);
    void traverse(void(*visit)(List_entry& ));
protected:
    int count;
    mutable int current_position;
    mutable Node<List_entry> *current;
    Node<List_entry> *head;
//    Node <List_entry> *set_position(int position)const;这个是第一版的
    void set_position(int position)const;//空类型就可以，改变的是自己的成员数据
};
//关键字mutable
//类的mutable 成员可以被任何 成员函数修改，就算是


template<class List_entry>
List<List_entry>::List(){
    count = 0;
    head =nullptr;
}
template<class List_entry>
List<List_entry>::List(const List<List_entry> &copy){
    count = 0;
    head = nullptr;
    Node<List_entry> *q = copy.head;
    int i = 0;
    while(q){
        insert(i, q->entry);
        q = q->next;
        i++;
    }
}
template<class List_entry>
List<List_entry>::~List(){
    List_entry x;
    while(!empty())remove(0, x);
}


template<class List_entry>
void List<List_entry>::operator=(const List<List_entry> &copy){
    List_entry x;
    if(this == &copy)return;//自己对自己操作特判，不然的话会变为空空哟
    while(!empty())remove(0,x);// 先清空
    Node<List_entry> *q = copy.head;//后面相当于list：：list（copy）（见上）
    int i =0;
    while(q){
        insert(i, q->entry);
        i++;
    }
}

template<class List_entry>
void List<List_entry>::set_position(int position)const
{
    if(position < current_position){
        current_position = 0;
        current = head;
    }
    for(;current_position != position ;current_position++) current= current->next;
}

template<class List_entry>
Error_code List<List_entry>::insert(int position ,const List_entry &x){
    if(position<0 || position>count) return range_Error;
    Node<List_entry> *new_node, *previous, *following;
    if(position > 0){
        set_position(position-1);
        previous = current;
        following = previous->next;
    }
    else following = head;
    new_node = new Node<List_entry>(x, following);
    if(new_node == nullptr) return overflow;//没有分派到，overflow
    if(position == 0) {
        head = new_node;//在开头
        //should add on that
        current_position = 0;
        current = head;
    }
    //-------
    else{
        previous->next = new_node;//普通情况
        //add on
        set_position(position);
        //------
    }
    count++;
    return success;
}

template<class List_entry>
Error_code List<List_entry>::remove(int position , List_entry &x){
    if(position <0 || position >= count) return range_Error;
    Node<List_entry> *previous,*following;
    if(position > 0){
        set_position(position-1);
        previous = current;
        following = previous->next;
        previous->next = following->next;
    }
    else{
        following = head;
        head = head->next;
        // add on
        current_position = 0;
        current = head;
        //------
    }
    x = following->entry;
    delete following;
    count--;
    return success;
}

template<class List_entry>
int List<List_entry>::size()const{
    return count;
}

template<class List_entry>
bool List<List_entry>::full()const{
    Node<List_entry> *new_node;
    new_node = new Node<List_entry>;
    if(new_node == nullptr) return true;
    else{
        delete new_node;
        return false;
    }
}

template<class List_entry>
bool List<List_entry>::empty()const{
    return count==0;
}
template<class List_entry>
void List<List_entry>::clear(){
    List_entry x;
    while(!empty())remove(0, x);
}
template<class List_entry>
void List<List_entry>::traverse(void (*visit)(List_entry &)){
    Node<List_entry> *p_node = head;
    while(p_node){
        (*visit)(p_node->entry);
        p_node = p_node->next;
    }
}
template<class List_entry>
Error_code List<List_entry>::retrieve(int position, List_entry &x)const{
    if(position <0||position >= count)return range_Error;
//    Node<List_entry> *p_node;
    set_position(position);
    x = current->entry;
    return success;
}

template<class List_entry>
Error_code List<List_entry>::replace(int position, List_entry &x){
    if(position < 0|| position >=count) return range_Error;
    Node<List_entry> *p_node;
    set_position(position);
    p_node = current;
    p_node->entry = x;
    return success;
}
template<class List_entry>
void update(List_entry &x){
    x*=2;
}
template<class List_entry>
void print(List_entry &x){
    cout<<x<<' ';
}
bool cmp(web a, web b){
    if(a.xishu != b.xishu)return a.xishu > b.xishu;
    else return a.rank < b.rank;
}

#endif

int main(){
    int n;
    cin>>n;
    web res[n];
    for(int i = 0;i < n ;i++){
        cin>>res[i].str>>res[i].xishu;
        res[i].rank = i;
    }
    sort(res, res+n,cmp);
    int maxnum = res[0].xishu;
    for(auto it : res){
        if(it.xishu==maxnum)
            cout<<it.str<<endl;
        else break;
    }
    return 0;
}
