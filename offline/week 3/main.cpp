#include <iostream>
#include <vector>
#include "queue.h"
using namespace std;
// g++ -std=c++11 main.cpp arrayqueue.cpp listqueue.cpp -o main
/********************************* RANDOM ************************************/
#define LCG_MULTIPLIER (1103515245)
#define LCG_INCREMENT (12345)
#define LCG_MODULUS ((unsigned)~0 >> 1)
static unsigned int lcg_seed = 1;
void custom_srand(unsigned int seed)
{
    lcg_seed = seed;
}
int custom_rand()
{
    lcg_seed = (LCG_MULTIPLIER * lcg_seed + LCG_INCREMENT) % (LCG_MODULUS + 1);
    return lcg_seed;
}
int randomQueue(int seed = -1)
{
    static bool initialized = false;
    if (seed != -1 && !initialized)
    {
        custom_srand(seed);
        initialized = true;
        return -1;
    }
    cout << "randomQueue() called"<<endl;
    return (custom_rand() % 2) + 1;
}
/*****************************************************************************/

int main()
{
     freopen("test_input_1.txt", "r", stdin); // Test Case 1
   // freopen("test_input_2.txt", "r", stdin); // Test Case 2
    freopen("output.txt", "w", stdout);
    // Initialize the random generator with a fixed seed

    // You should set the seed only once at the beginning of your program
    // NOTE: Do not modify the following lines.
    randomQueue(42);

    Queue *Q1 = new ListQueue();
    Queue *Q2 = new ListQueue();
    Queue *Q = new ArrayQueue();

    int N;
    cin >> N;
    int time[10001] = {0};
    bool mergeActivated = false;
    for (int i = 1; i <= N; i++)
    {
        // TODO: Edit here to add your own logic
        int oper, id, timestamp;
        cin >> oper;
        if (oper == 1 || oper == 2)
        {
            cin >> id >> timestamp;
            // cout<<oper<<" "<<id<<" "<<timestamp<<endl;
        }

        if (oper == 1)
        {
            cout << "Operation " << i << " (Arrival " << id << " " << timestamp << "): ";
            if (Q1->size() == 0 && Q2->size() == 0)
            {
                if (mergeActivated == true)
                {
                    Q->enqueue(id);
                    time[id] = timestamp;
                    cout<<endl;
                }
                else
                {
                    int ran = randomQueue();
                    // cout<<ran<<endl;
                    if (ran == 1)
                    {
                        Q1->enqueue(id);
                        time[id] = timestamp;
                    }
                    else
                    {
                        Q2->enqueue(id);
                        time[id] = timestamp;
                    }
                }
            }
            else if (Q1->size() == 0)
            {
                Q1->enqueue(id);
                time[id] = timestamp;
                cout<<endl;
            }
            else if (Q2->size() == 0)
            {
                Q2->enqueue(id);
                time[id] = timestamp;
                cout<<endl;
            }
            else if (Q1->size() != 0 && Q2->size() != 0)
            {
                if (time[Q1->back()] > time[Q2->back()])
                {
                    Q2->enqueue(id);
                    time[id] = timestamp;
                }
                else
                {
                    Q1->enqueue(id);
                    time[id] = timestamp;
                }
                cout<<endl;
            }
        }
        else if (oper == 2)
        {
            int temp = 0;
            int sz1 = Q1->size();
            int sz2 = Q2->size();
            int sz_of_Q = Q->size();

            if (mergeActivated)
            {
                for (int i = 0; i < sz_of_Q; i++)
                {
                    int person = Q->front();
                    Q->dequeue();
                    if (person == id)
                    {
                        time[id] = 0;
                    }
                    else
                    {
                        Q->enqueue(person);
                    }
                }
    
            }
            else
            {
                {
                    for (int i = 0; i < sz1; i++)
                    {
                        int person = Q1->front();
                        Q1->dequeue();
                        if (person == id)
                        {
                            time[id] = 0;
                            temp = 1;
                        }
                        else
                        {
                            Q1->enqueue(person);
                        }
                    }
                }
                if (temp == 0)
                {
                    for (int i = 0; i < sz2; i++)
                    {
                        int person = Q2->front();
                        Q2->dequeue();
                        if (person == id)
                        {
                            time[id] = 0;
                            temp = 1;
                        }
                        else
                        {
                            Q2->enqueue(person);
                        }
                    }
                }
            }
            cout << "Operation " << i << " (Leave " << id << " " << timestamp << "): ";
            cout<<endl;
        }
        else if (oper == 3)
        {
            mergeActivated = true;
            int total = Q1->size() + Q2->size();
            int sz1 = Q1->size();
            int sz2 = Q2->size();
            if (sz1 != 0 && sz2 != 0)
            {
                for (int i = 0; i < total; i++)
                {
                    if (Q1->size() == 0)
                    {
                        Q->enqueue(Q2->front());
                        Q2->dequeue();
                    }
                    else if (Q2->size() == 0)
                    {
                        Q->enqueue(Q1->front());
                        Q1->dequeue();
                    }
                    else if (time[Q1->front()] < time[Q2->front()])
                    {
                        Q->enqueue(Q1->front());
                        Q1->dequeue();
                    }
                    else
                    {
                        Q->enqueue(Q2->front());
                        Q2->dequeue();
                    }
                }
            }
            else if (Q1->size() != 0)
            {
                for (int i = 0; i < sz1; i++)
                {
                    Q->enqueue(Q1->front());
                    Q1->dequeue();
                }
            }
            else if (Q2->size() != 0)
            {
                for (int i = 0; i < sz2; i++)
                {
                    Q->enqueue(Q2->front());
                    Q2->dequeue();
                }
            }
            cout << "Operation " << i << " (Merge):";
            cout<<endl;
        }
        else if (oper == 4)
        {
            int size_Q = Q->size();
            for (int i = 0; i < size_Q; i++)
            {
                int person = Q->front();
                Q->dequeue();
                if (i % 2 == 0)
                {
                    Q1->enqueue(person);
                }
                else
                {
                    Q2->enqueue(person);
                }
            }
            cout << "Operation " << i << "(Split):";
            mergeActivated = false;
            cout<<endl;
        }
        else if (oper == 5)
        {
            if (mergeActivated)
            {
                if (Q->size() != 0)
                {
                    Q->dequeue();
                    cout << "Operation " << i << " (Departure):";
                }
                cout<<endl;
            }
            else
            {
                if (Q1->size() != 0 && Q2->size() != 0)
                {
                    cout << "Operation " << i << " (Departure): ";
                    int random = randomQueue();
                    if (random == 1)
                    {
                        Q1->dequeue();
                    }
                    else
                        Q2->dequeue();
                }
                else if (Q1->size() == 0 && Q2->size() == 0)
                {
                }
                else if (Q1->size() != 0)
                {
                    Q1->dequeue();
                    cout << "Operation " << i << " (Departure):";
                    cout<<endl;
                }
                else if (Q2->size() != 0)
                {
                    Q2->dequeue();
                    cout << "Operation " << i << " (Departure):";
                    cout<<endl;
                }
            }
        }
        
        cout << "Q1 : " << Q1->toString() << endl;
        cout << "Q2 : " << Q2->toString() << endl;
        cout << "Q  : " << Q->toString() << endl;

        // After each operation, we will check the queue's size and capacity
        // NOTE: Do not modify the following lines.
        int capacity = ((ArrayQueue *)Q)->getCapacity();
        if ((Q->size() < capacity / 4 && capacity > 2))
        {
            cout << "Error: Queue size is less than 25% of its capacity." << endl;
        }
        else if (capacity < 2)
        {
            cout << "Error: Queue capacity is less than 2." << endl;
        }
    }

    return 0;
}