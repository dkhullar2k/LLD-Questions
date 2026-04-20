/*
Advanced Approach: Move the node (Not delete)
*/
#include <iostream>
#include <unordered_map>
using namespace std;

class LRU{
    public:
    int capacity;

    class Node{
        public:
        int key;
        int val;
        Node* next;
        Node* prev;
        Node(int key, int val)
        : key(key), val(val), next(nullptr), prev(nullptr){}
    };
    Node* head;
    Node* tail;
    unordered_map<int,Node*> map;
    
    LRU(int capacity): capacity(capacity), head(nullptr), tail(nullptr){}

    private:

    void insertFront(Node* node){
        if(!head){//first node in DLL
            head=node;
            tail=node;
            return;
        }
    
        node->next=head;
        node->prev=nullptr;
        head->prev=node;
        head=node;
    }

    void removeNode(Node* node){ //node cannot be nullptr
        Node* newPrev=node->prev;
        Node* newNext=node->next;
        if(newPrev){
            newPrev->next=newNext;
        }
        else{
            //head node being removed
            head=newNext;
        }
        if(newNext){
            newNext->prev=newPrev;   
        }
        else{
            //tail node being removed
            tail=newPrev;
        }

        node->next=nullptr;
        node->prev=nullptr;
    }

    public:

    void put(int key, int val){
        if(capacity==0) return;
        //Step 1: check if already in map
        if(map.count(key)){
            Node* node=map[key];
            node->val=val;
            removeNode(node);
            insertFront(node);
            return;
        }

        //Step 2: check capacity
        if(map.size()>=capacity){ //capacity has to be ofc greater than 0
            //delete last node and remove entry
            Node* temp=tail;
            int tKey=temp->key;
            removeNode(tail);

            delete(temp);
            map.erase(tKey);
        }

        Node* newNode=new Node(key,val);
        insertFront(newNode);
        map[key]=newNode;
    }

    int get(int key){
        if(map.count(key)<=0){
            return -1; //Not found
        }
        Node* node=map[key];
        removeNode(node);
        insertFront(node);
        return node->val;
    }
};

//Client code
int main(){
    // Assumption: Capacity should be greater than 0
    LRU obj(2);

    obj.put(1,1);
    cout<<obj.get(2)<<endl;
    obj.put(2,2);
    obj.put(3,3);
    cout<<obj.get(3)<<endl;
    obj.put(4,4);
    cout<<obj.get(1)<<endl;
    cout<<obj.get(2)<<endl;
    cout<<obj.get(4)<<endl;
    cout<<obj.get(3)<<endl;
}