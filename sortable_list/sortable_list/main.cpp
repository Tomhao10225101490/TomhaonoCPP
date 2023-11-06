#include "Header.h"
#include "Record.h"

class Sortable_list: public List<Record>{
public :
    void insertion_sort();
    //for insertion_sort.
    void swap(int  low, int high);
    int max_key(int low, int high);
    void selection_sort();
    
    //for shell_sort.
    void sort_interval(int start, int increment);
    void shell_sort();
private:
};
void Sortable_list::insertion_sort(){
    int first_unsorted;//position of first unsorted entry
    Record current;//holds the entry temporarily removed from list
    for(first_unsorted = 1; first_unsorted < count; first_unsorted++){
        Record val_first_unsorted;
        Record val_front_first_unsorted;
        retrieve(first_unsorted, val_first_unsorted);
        retrieve(first_unsorted - 1, val_front_first_unsorted);
        //if the first unsorted one is smaller than the pre one
        //then we need do the following steps
        //otherwise nothing is needed to be done
        for(int i = 1 ;i < count; i++){
            retrieve(i, val_first_unsorted);
            for(int j = i - 1; j >=0 ;j--){
                retrieve(j, val_front_first_unsorted);
                if(val_front_first_unsorted <= val_first_unsorted){
                    //remove i
                    remove(i, val_first_unsorted);
                    //insert i to j+1
                    insert(j+1, val_first_unsorted);
                    break;
                }
                if(j==0){
                    remove(i, val_first_unsorted);
                    insert(j, val_first_unsorted);
                }
            }
        }
    }
}

int main(){
    Sortable_list  test;
    for(int i = 0; i < 9 ;i++){
        test.insert(i, {9 - i ,"z","h"});
    }
    for(int i = 9; i<18;i++){
        test.insert(i, {i+1,"z","h"});
    }
    test.traverse(RecordPrintKey);
    cout<<endl;
    test.insertion_sort();
    test.traverse(RecordPrintKey);
    cout<<endl;
    return 0;
}
