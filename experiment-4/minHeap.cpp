#include <bits/stdc++.h>
using namespace std;

#define MAX 100

int heapSize = 0;
int heap[MAX];

void heapifyUp(int i) {
    while (i > 0 && heap[(i - 1) / 2] > heap[i]) {
        swap(heap[i], heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void insert(int val) {
    if (heapSize == MAX) {
        cout << "Heap full"<<endl;
        return;
    }
    heap[heapSize] = val;
    heapSize++;
    heapifyUp(heapSize - 1);
}

void heapifyDown(int i) {
    int smallest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < heapSize && heap[left] < heap[smallest]) {
        smallest = left;
    }
    if (right < heapSize && heap[right] < heap[smallest]) {
        smallest = right;
    }

    if (smallest != i) {
        swap(heap[i], heap[smallest]);
        heapifyDown(smallest);
    }
}

void deleteMin() {
    if (heapSize == 0) {
        cout << "Heap empty"<<endl;
        return;
    }
    heap[0] = heap[heapSize - 1];
    heapSize--;
    heapifyDown(0);
}
void deleteAtany(int i){
    if(i<0 || i>=heapSize){
        cout<<"Invalid syntax"<<endl;
    }
    heap[i]=heap[heapSize-1];
    heapSize--;
    if(i>0 && heap[(i-1)/2]>heap[i]){
        heapifyUp(i);
    }
    else{
        heapifyDown(i);
    }
}
int main() {
    insert(10);
    insert(20);
    insert(1);
    insert(0);

    cout << "Heap before deletion: "<<endl;
    for (int i = 0; i < heapSize; i++) {
        cout << heap[i] << " ";
    }

    deleteMin();

    cout << "Heap after deleting first element of heap: "<<endl;
    for (int i = 0; i < heapSize; i++) {
        cout << heap[i] << " ";
    }
    deleteAtany(1);
    cout<<"Heap after deleting at any position: "<<endl;
    for(int i=0;i<heapSize;i++){
        cout<<heap[i]<<" ";
    }
    return 0;
}