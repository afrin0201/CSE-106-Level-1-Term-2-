#ifndef HEAP_H
#define HEAP_H
#include <vector>
#include <iostream>
using namespace std;
class Heap
{
private:
    vector<int> heap;
    int capacity;
    void heapUp(int index)
    {
        while (index > 0 && heap[index] > heap[(index - 1) / 2])
        {
            swap(heap[index], heap[(index - 1) / 2]);
            index = (index - 1) / 2;
        }
    }
    void heapDown(int index)
    {
        int largest = index;
        int left = 2 * index + 1;
        int right = 2 * index + 2;
        if (left < heap.size() && heap[left] > heap[largest])
            largest = left;
        if (right < heap.size() && heap[right] > heap[largest])
            largest = right;
        if (largest != index)
        {
            swap(heap[index], heap[largest]);
            heapDown(largest);
        }
    }
    public:
        Heap(int max_size)
        {
            capacity = max_size;
            // heap.reserve(capacity);
        }
       Heap(const vector<int>& v){
        capacity=v.size();
        heap=v;
        for(int i=heap.size()/2-1;i>=0;i--){
            heapDown(i);
        }
       }
       void insert(int key){
        if (heap.size()>=capacity){
          cout<<"Heap is full!"<<endl;
        }
        else {
            heap.push_back(key);
            heapUp(heap.size()-1);
        }
       }
       int getMax(){
        if (!heap.empty()){
            return heap[0];
        }
       }
       void deleteKey(){
        if (!heap.empty()){
            heap[0]=heap.back();
            heap.pop_back();
            heapDown(0);
        }
       }
       int size(){
        return heap.size();
       }
       vector<int> getheap(){
        return heap;
       }
};
void heapsort(vector<int>&v){
    Heap h(h.size());
    for(int i=0;i<v.size();i++){
        h.insert(v[i]);
    }
    for(int i=0;i<v.size();i++){
        v[i]=h.getMax();
        h.deleteKey();
    }
}
#endif