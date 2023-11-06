//
//  Record.h
//  sortable_list
//
//  Created by TOM钟浩 on 2023/5/8.
//

#ifndef Record_h
#define Record_h

typedef int Key_entry;
typedef int Record_entry;
class Key{
    Key_entry key;
public:
    Key();
    Key(const Key_entry &x);
    Key_entry the_key()const;
};
Key::Key(){
    key = 0;
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
    Record(const Record_entry &x,const string &str,const string &zhongwen);
    Key_entry the_key()const;
    string view();
    string china();
private:
    Record_entry key;
    string words;
    string zhongwen;
};
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
    key = 0;
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

void RecordPrintKey(Record &x){
    Key_entry temp = x.the_key();
    cout<<temp<<' ';
}

#endif /* Record_h */
