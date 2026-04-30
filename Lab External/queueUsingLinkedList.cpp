#include<iostream>
using namespace std;
class node{
    public:
    int data;
    node* front;
    node* rear;
    node* next;
    node(){
        data=0;
        front=NULL;
        rear=NULL;
        next=NULL;
    }
    node(int data){
        this->data=data;
        front=NULL;
        rear=NULL;
        next=NULL;
    }
    void enque(int val){
        node *t=new node;
        if(t==NULL){
            cout<<"Queue is Full"<<endl;
        }
        else{
            t->data=val;
            t->next=NULL;
            if(front==NULL){
                front=rear=t;
            }
            else{
                rear->next=t;
                rear=t;
            }
        }
        cout<<t->data<<endl;
    }
    int deque(){
        node *p;
        int x=-1;
        if(front==NULL){
            cout<<"Queue is Empty"<<endl;
        }
        else{
            p=front;
            front=front->next;
            x=p->data;
            delete p;
        }
        return x;
    }
    int size(){
        node *p=front;
          int count=0;
        for(int i=0;p!=NULL;i++ ){
            p=p->next;
            count++;
        }
        cout<<count<<endl;
    }
};
int main(){
    node n;
    cout<<"Element in queue"<<endl;
    n.enque(5);
    n.enque(6);
    cout<<"Delete element in queue"<<endl;
    cout<<n.deque()<<endl;
    cout<<"number of element in queue"<<endl;
    n.size();
    return 0;
}