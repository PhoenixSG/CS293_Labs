/*
Author- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 1

Implement Dynamic Dequeue using a circular array.
*/

#include <iostream>
#include "DynamicDequeue.cpp"
#include <chrono>

using namespace std;

int main()
{
    double time = 0;
    int avg_count = 10;
    int number_of_elements = 100;
    int LIMIT = 200000;
    while (number_of_elements < LIMIT)
    {
        for (int g = 0; g < avg_count; g++)
        {
            auto start = std::chrono::system_clock::now(); //timer begin

            DynamicDequeue test;

            for (int i = 0; i < number_of_elements; i++)
            {
                test.insertFront(i);
            }

            auto now = std::chrono::system_clock::now(); //timer end
            std::chrono::duration<double> diff = now - start;
            time += diff.count();
        }
        //Print average time!
        cout << time / avg_count << " seconds taken for inserting " << number_of_elements << " elements" << endl;
        number_of_elements *= 1.5;
    }
    //The linear plot was getting "killed" above 2,00,000 elements, thus I put a limit of 2,00,000 items to be inserted

    //For graph excel sheet, you can have a look at the following
    // https://docs.google.com/spreadsheets/d/1qlRaYpGeyXoC9RVFiN_VI9IUS03jRiBzYKE_jlzHpNk/edit?usp=sharing

    cout << endl
         << endl;

    cout << "Beginning with the demo of the queue" << endl
         << endl;

    cout << "Please see the code for insertion order of elements\n\n";

    DynamicDequeue demo;
    double f = 6;
    double *show = new double();

    demo.insertFront(1);
    demo.insertFront(2);
    demo.insertFront(3);
    demo.insertRear(4);
    demo.insertRear(5);
    demo.insertRear(6);

    cout << "Order of removing from front is as follows\n";
    while (demo.removeFront(show))
    {
        cout << *show << endl;
    }
    cout << endl
         << endl;

    demo.insertFront(1);
    demo.insertFront(2);
    demo.insertFront(3);
    demo.insertRear(4);
    demo.insertRear(5);
    demo.insertRear(6);

    cout << "Order of removing from rear is as follows\n";
    while (demo.removeRear(show))
    {
        cout << *show << endl;
    }
    cout << endl;
    demo.insertFront(1);
    demo.insertFront(2);
    demo.insertFront(3);
    demo.insertRear(4);
    demo.insertRear(5);
    demo.insertRear(6);

    cout << "Getting front without removing\n";

    if (demo.front(show))
    {
        cout << *show << endl;
    }

    cout << "Getting rear element without removing\n";

    if (demo.rear(show))
    {
        cout << *show << endl;
    }

    cout << endl;
    cout << "End of demo! Thank you for your time!!\n\n";
    cout << "By Shashwat Garg, 200050130" << endl;
}