/*
Author- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 5

QuickSort
*/
#include <bits/stdc++.h>
#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <chrono>
using namespace std;

int comparisons;


int partition(double *a, int l, int r)
{
    double x = a[l];
    int i = l - 1;
    int j = r + 1;

    while (true)
    {
        j--;
        i++;
        while (a[j] > x)
        {
            j--;
        }
        while (a[i] < x)
        {
            i++;
        }
        if (i < j)
        {
            double temp = a[i];
            a[i] = a[j];
            a[j] = temp;
            comparisons++;
        }
        else
        {
            return j;
        }
    }
}

int random_partition(double *a, int l, int r)
{

    int i = rand() / (RAND_MAX / (r - l)) + l;
    double temp = a[r];
    a[r] = a[i];
    a[i] = temp;
    comparisons++;
    return partition(a, l, r);
}

void Quicksort(double *a, int l, int r, bool randomize)
{

    if (l < r)
    {
        int q;
        if (!randomize)
        {
            q = partition(a, l, r);
        }
        else
        {
            q = random_partition(a, l, r);
        }
        Quicksort(a, l, q, randomize);
        Quicksort(a, q + 1, r, randomize);
    }
}

void bubbleSort(double *a, int n)
{
    int i, j;
    for (i = 0; i < n - 1; i++)
    {
        for (j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                double temp = a[j + 1];
                a[j + 1] = a[j];
                a[j] = temp;
                comparisons++;
            }
        }
    }
}

int main()
{
    int size = 10;
    while (size < 80000)
    {
        cout << endl
             << size;

        //random array generation
        double random_BuSo[size], random_QSP1[size], random_QSRP[size];

        double increasing_BuSo[size], increasing_QSP1[size], increasing_QSRP[size];
        double decreasing_BuSo[size], decreasing_QSP1[size], decreasing_QSRP[size];

        for (int i = 0; i < size; i++)
        {

            double d = (double)rand() / RAND_MAX;
            // cout << d << " ";
            random_BuSo[i] = d;
            random_QSP1[i] = d;
            random_QSRP[i] = d;
            increasing_BuSo[i] = d;
            increasing_QSP1[i] = d;
            increasing_QSRP[i] = d;
            decreasing_BuSo[i] = d;
            decreasing_QSP1[i] = d;
            decreasing_QSRP[i] = d;
        }
        sort(increasing_BuSo, increasing_BuSo + size * 9 / 10);
        sort(increasing_QSP1, increasing_BuSo + size * 9 / 10);
        sort(increasing_QSRP, increasing_BuSo + size * 9 / 10);

        sort(decreasing_BuSo, decreasing_BuSo + size * 9 / 10, greater<double>());
        sort(decreasing_QSP1, decreasing_BuSo + size * 9 / 10, greater<double>());
        sort(decreasing_QSRP, decreasing_BuSo + size * 9 / 10, greater<double>());

        cout << endl
             << endl;
        double time = 0;
        /////////////////////////////////////////////////////////////////////////////////////////
        //BuSo: Bubble Sort
        bubbleSort(random_BuSo, size);

        cout << "Bubble Sort, "
             << "Random, " << comparisons << endl;
        comparisons=0;
        //QSP1: Quick Sort with 1st element as Pivot
        Quicksort(random_QSP1, 0, size - 1, false);
        cout << "Quick Sort Fixed, "
             << "Random, " << comparisons << endl;
        comparisons=0;

        //QSRP: Quick Sort with Random Pivot
        Quicksort(random_QSRP, 0, size - 1, true);
        cout << "Quick Sort Random, "
             << "Random, " << comparisons << endl;
        comparisons=0;

        /////////////////////////////////////////////////////////////////////////////////////////
        //BuSo: Bubble Sort
        bubbleSort(increasing_BuSo, size);
        cout << "Bubble Sort, "
             << "90\% increasing, " << comparisons << endl;
        comparisons=0;

        //QSP1: Quick Sort with 1st element as Pivot
        Quicksort(increasing_QSP1, 0, size - 1, false);
        cout << "Quick Sort Fixed, "
             << "90\% increasing, " << comparisons << endl;
        comparisons=0;

        //QSRP: Quick Sort with Random Pivot
        Quicksort(increasing_QSRP, 0, size - 1, true);
        cout << "Quick Sort Random, "
             << "90\% increasing, " << comparisons << endl;
        comparisons=0;

        /////////////////////////////////////////////////////////////////////////////////////////
        //BuSo: Bubble Sort
        bubbleSort(decreasing_BuSo, size);
        cout << "Bubble Sort, "
             << "90\% decreasing, " << comparisons << endl;
        comparisons=0;

        //QSP1: Quick Sort with 1st element as Pivot
        Quicksort(decreasing_QSP1, 0, size - 1, false);
        cout << "Quick Sort Fixed, "
             << "90\% decreasing, " << comparisons << endl;
        comparisons=0;

        //QSRP: Quick Sort with Random Pivot
        Quicksort(decreasing_QSRP, 0, size - 1, true);
        cout << "Quick Sort Random, "
             << "90\% decreasing, " << comparisons << endl;
        comparisons=0;

        /////////////////////////////////////////////////////////////////////////////////////////
        //     for (int i = 0; i < size; i++)
        //     {
        //         cout << random_BuSo[i] << " ";
        //     }
        //     cout << endl;
        //     for (int i = 0; i < size; i++)
        //     {
        //         cout << random_QSP1[i] << " ";
        //     }
        //     cout << endl;
        //     for (int i = 0; i < size; i++)
        //     {
        //         cout << random_QSRP[i] << " ";
        //     }
        //     cout << endl;
        // /////////////////////////////////////////////////////////////////////////////////////////

        //     for (int i = 0; i < size; i++)
        //     {
        //         cout << increasing_BuSo[i] << " ";
        //     }
        //     cout << endl;
        //     for (int i = 0; i < size; i++)
        //     {
        //         cout << increasing_QSP1[i] << " ";
        //     }
        //     cout << endl;
        //     for (int i = 0; i < size; i++)
        //     {
        //         cout << increasing_QSRP[i] << " ";
        //     }
        //     cout << endl;
        // /////////////////////////////////////////////////////////////////////////////////////////

        //     for (int i = 0; i < size; i++)
        //     {
        //         cout << decreasing_BuSo[i] << " ";
        //     }
        //     cout << endl;
        //     for (int i = 0; i < size; i++)
        //     {
        //         cout << decreasing_QSP1[i] << " ";
        //     }
        //     cout << endl;
        //     for (int i = 0; i < size; i++)
        //     {
        //         cout << decreasing_QSRP[i] << " ";
        //     }
        //     cout << endl;
        size *= 2;
    }
}
