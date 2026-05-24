#ifndef ARRAY_LIST_H
#define ARRAY_LIST_H

class arrayList
{
private:
    int data[1000];
    int size;

public:
    arrayList() { size = 0; }
    int getSize() const { return size; }
    void insertItem (int item) { data[size++] = item; }
    int getItem(int i)  const { return data[i]; }
    void removeEdge(int v)
    {
        int index=-1;
        for (int i = 0; i < size; i++)
        {
            if (data[i] == v)
            {
                index = i;
                break;
            }
        }
        for (int i = index; i < size - 1; i++)
        {
            data[i] = data[i + 1];
        }
        size--;
    }
};

#endif
