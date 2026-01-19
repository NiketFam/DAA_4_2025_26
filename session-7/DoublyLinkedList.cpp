#include <iostream>
using namespace std;
class Node {
public:
    int data;
    Node* next;
    Node* prev;
    Node() {
        data = 0;
        next = nullptr;
        prev = nullptr;
    }
};
class DoublyLinkedList {
private:
    Node* head;
    Node* tail;
public:
    DoublyLinkedList() {
        head = nullptr;
        tail = nullptr;
    }
    void insertAtTail(int val) {
        Node* newNode = new Node(); 
        newNode->data = val;
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        tail->next = newNode;
        newNode->prev = tail;
        tail = newNode;
    }
    void insertAtHead(int val) {
        Node* newNode = new Node();
        newNode->data = val;
        if (head == nullptr) {
            head = tail = newNode;
            return;
        }
        newNode->next = head;
        head->prev = newNode;
        head = newNode;
    }
    void deleteNode(int val) {
        if (head == nullptr) return;
        Node* curr = head;
        while (curr != nullptr && curr->data != val) {
            curr = curr->next;
        }
        if (curr == nullptr) return; 
        if (curr == head && curr == tail) {
            head = tail = nullptr;
        }
        else if (curr == head) {
            head = head->next;
            head->prev = nullptr;
        }
        else if (curr == tail) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            curr->prev->next = curr->next;
            curr->next->prev = curr->prev;
        }
        delete curr; 
    }
    void display() {
        Node* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " <-> ";
            temp = temp->next;
        }
        cout << "NULL" << endl;
    }
};
int main() {
    DoublyLinkedList list;
    list.insertAtTail(10);
    list.insertAtTail(20);
    list.insertAtTail(30);
    list.insertAtHead(5);
    cout << "Current List: ";
    list.display(); 
    list.deleteNode(20);
    cout << "After deleting 20: ";
    list.display(); 
    return 0;
}