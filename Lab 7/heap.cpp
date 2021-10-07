/*
Author- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 6

Compressed Tries
*/

#include <bits/stdc++.h>
using namespace std;

#define max_size 10048576

int swaps = 0;

class heap
{
    int array[max_size];
    int size;

    void heapify(int index)
    {
        int minimum = std::min(array[left(index)], array[right(index)]);
        if (array[index] > minimum)
        {
            if (array[left(index)] < array[right(index)])
            {
                int temp = array[left(index)];
                array[left(index)] = array[index];
                array[index] = temp;
                swaps++;
                heapify(left(index));
            }
            else
            {
                int temp = array[right(index)];
                array[right(index)] = array[index];
                array[index] = temp;
                swaps++;
                heapify(right(index));
            }
        }
    }
    int parent(int i)
    {
        return (i - 1) / 2;
    }
    int left(int i)
    {
        return (2 * i + 1);
    }
    int right(int i)
    {
        return (2 * i + 2);
    }

public:
    heap()
    {
        // array = new int[max_size];
        for (int i = 0; i < max_size; i++)
        {
            array[i] = 2147483647;
        }
        size = 0;
    }

    int min()
    {
        if (size > 0)
            return array[0];
        else
        {
            cout << "Heap is empty!\n";
            return -1;
        }
    }

    void insert(int k)
    {
        if (size == max_size)
        {
            cout << "Heap is full!\n";
            return;
        }
        array[size] = k;
        int index = size;
        size++;
        while (index != 0 && array[parent(index)] > array[index])
        {
            int temp = array[index];
            array[index] = array[parent(index)];
            array[parent(index)] = temp;
            index = parent(index);
            swaps++;
        }
    }

    int delete_min()
    {
        if (size == 0)
        {
            cout << "Heap is empty!\n";
            return -1;
        }
        int value = array[0];
        size--;
        if (size > 0)
        {
            array[0] = array[size];
            array[size] = 2147483647;
            heapify(0);
        }
        return value;
    }
};

int main()
{
    heap *heap_ptr = new heap();
    // cout << "FINE\n";
    char a;
    int value;
    while (true)
    {

        a = 'a';
        cin >> a;
        if (a == 'i') //insert
        {
            cin >> value;
            heap_ptr->insert(value);
        }
        else if (a == 'd') //delete_min
        {
            int i = heap_ptr->delete_min();
            if (i != -1)
                cout << i << " was deleted\n";
        }
        else if (a == 'm') //show min
        {
            int i = heap_ptr->min();
            if (i != -1)
                cout << i << " is the minimum element\n";
        }

        else if (a == 'a')
        {

            auto start = std::chrono::system_clock::now(); //timer begin
            auto now = std::chrono::system_clock::now();   //timer end

            int N = 1000;
            while (N <= 1000000)
            {
                delete heap_ptr;
                heap_ptr = new heap();
                for (int count = 0; count < N; count++)
                {
                    int a = rand();
                    heap_ptr->insert(a);
                }
                double time = 0;
                swaps = 0;
                for (int count = 0; count < N / 5; count++)
                {
                    int a = rand();
                    if (rand() % 2 == 0)
                    {
                        start = std::chrono::system_clock::now(); //timer begin
                        heap_ptr->insert(a);
                        now = std::chrono::system_clock::now(); //timer end
                        std::chrono::duration<double> diff = now - start;
                        time += diff.count();
                    }
                    else
                    {
                        start = std::chrono::system_clock::now(); //timer begin
                        heap_ptr->delete_min();
                        now = std::chrono::system_clock::now(); //timer end
                        std::chrono::duration<double> diff = now - start;
                        time += diff.count();
                    }
                }

                cout << N << "," << 5 * time / N << "," << (double)5 * swaps / N << endl;
                N *= 10;
            }
            break;
        }
        else
        {
            cin >> value;
            heap_ptr->insert(value);
            cout << "DONE";
            // break;
        }
    }
    return 0;
}