/*
Basic Approach - Delete and Create new nodes for an operation
*/
#include<iostream>
#include<unordered_map>
using namespace std;

class LRU{

    class Node{
        public:
        Node* next;
        Node* prev;
        int key;
        int val;

        public:
        Node(int key, int val){
            this->key=key;
            this->val=val;
            this->next=nullptr;
            this->prev=nullptr;
        }
    };
    unordered_map<int,Node*> mp;
    Node* head;
    Node* tail;
    int capacity;

    void deleteNode(Node* node){
        if(!node) return;
        Node* prv=node->prev;
        Node* nxt=node->next;
        if(prv){
            prv->next=nxt;
        }
        else{//deleting the head
            //assign new head
            head=nxt;
        }
        if(nxt){
            nxt->prev=prv;
        }
        else{ //deleting the tail
            //assign new tail
            tail=prv;
        }
        delete(node);
        return;
    }
    void insertNodeInStart(Node* node){
        if(capacity==mp.size()){ //Capacity is full; need to remove tail
            if(tail) {
                Node* lru = tail;
                int key = lru->key;
                mp.erase(key);
                deleteNode(lru);
            }
        }
        node->prev=NULL;
        node->next=head;
        if(head) head->prev=node;
        head=node;
        if(!tail) tail=node; //If the first node is created

        return;
    }


    public:
    LRU(int capacity){
        this->capacity=capacity;
        head=NULL;
        tail=NULL;
    }

    int get(int key){
        if(mp.count(key)<=0){ //Not present
            cout<<"Node is not present"<<endl;
            return -1; 
        }
        Node* node=mp[key];
        int val=node->val;
        mp.erase(key);
        deleteNode(node);

        //Create new node
        Node* newNode=new Node(key,val);
        insertNodeInStart(newNode);
        mp[key]=newNode;
        return val;
    }
    void set(int key, int val){
        if(capacity==0) return;
        
        //Check if the node is already present
        if(mp.count(key)>0){
            //Change the value and add it to the beginning
            Node* node=mp[key];
            node->val=val;
            mp.erase(key);
            deleteNode(node);
        }

        //Create new node
        Node* newNode=new Node(key,val);
        insertNodeInStart(newNode);
        mp[key]=newNode;
        
        return;
    }
};

//Client code
int main(){
    LRU obj(2);

    obj.set(1,1);
    cout<<obj.get(2)<<endl;
    obj.set(2,2);
    obj.set(3,3);
    cout<<obj.get(3)<<endl;
    obj.set(4,4);
    cout<<obj.get(1)<<endl;
    cout<<obj.get(2)<<endl;
    cout<<obj.get(4)<<endl;
    cout<<obj.get(3)<<endl;
}