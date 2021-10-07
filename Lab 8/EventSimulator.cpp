/*
Author- Shashwat Garg
Roll no.- 200050130

CS 293, 2021 Lab 8

Event Driven Simulator using Priority Queue
*/

//Time least count is 0.01 second. The fastest a packet travels is 0.05 seconds, so 0.01 is a reasonable least count.

#include <bits/stdc++.h>
using namespace std;

#define max_size 10048576
#define network_speed 1000
#define propagation_delay 0
#define ll long long

double VIRTUAL_TIME = 0.0;
int success = 0;
int failure = 0;

class Packet;
class heap
{
    Packet *packet_array[max_size];
    double array[max_size];
    int size;

    void heapify(int index)
    {
        int minimum = std::min(array[left(index)], array[right(index)]);
        if (array[index] > minimum)
        {
            if (array[left(index)] < array[right(index)])
            {
                double temp = array[left(index)];
                array[left(index)] = array[index];
                array[index] = temp;
                Packet *temp2 = packet_array[left(index)];
                packet_array[left(index)] = packet_array[index];
                packet_array[index] = temp2;
                heapify(left(index));
            }
            else
            {
                double temp = array[right(index)];
                array[right(index)] = array[index];
                array[index] = temp;
                Packet *temp2 = packet_array[right(index)];
                packet_array[right(index)] = packet_array[index];
                packet_array[index] = temp2;
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

    Packet *min()
    {
        if (size > 0)
            return packet_array[0];
        else
        {
            cout << "Time finished\n";
            return nullptr;
        }
    }

    void insert(Packet *a);
    double delete_min()
    {
        if (size == 0)
        {
            cout << "Heap is empty!\n";
            return -1;
        }
        double value = array[0];
        size--;
        if (size > 0)
        {
            packet_array[0] = packet_array[size];
            array[0] = array[size];
            array[size] = 2147483647;
            heapify(0);
        }
        return value;
    }
};

class Node;
class on_air;
class Packet
{

    Node *source;
    Node *destination;
    double size_in_bytes;
    double time_of_departure;
    double time_of_arrival;
    bool corrupted;
    int name;
    bool done;

public:
    Packet(Node *source, Node *destination, double size, double time, int i)
    {
        this->destination = destination;
        this->source = source;
        this->size_in_bytes = size;
        this->time_of_departure = time;
        this->time_of_arrival = time + size / network_speed;
        // cout<<size/network_speed<<" ";
        corrupted = false;
        name = i;
        done = false;
    }

    int get_name()
    {
        return name;
    }

    double get_time()
    {
        return time_of_departure;
    }
    double get_finishing_time()
    {
        return time_of_arrival;
    }

    void corrupt()
    {
        corrupted = true;
    }

    bool status()
    {
        return corrupted;
    }

    void packet_transmit(on_air *transmission_line);
    void packet_reception();
};

void heap::insert(Packet *a)
{
    if (size == max_size)
    {
        cout << "Heap is full!\n";
        return;
    }
    array[size] = a->get_time();
    packet_array[size] = a;
    int index = size;
    size++;
    while (index != 0 && array[parent(index)] > array[index])
    {
        double temp = array[index];
        array[index] = array[parent(index)];
        array[parent(index)] = temp;

        Packet *temp2 = packet_array[index];
        packet_array[index] = packet_array[parent(index)];
        packet_array[parent(index)] = temp2;

        index = parent(index);
    }
}

class Node
{
    int index_name;
    set<Packet *> sitting_on_source;
    set<Packet *> sitting_on_destination;

public:
    Node(int name)
    {
        index_name = name;
    }
    int get_name()
    {
        return index_name;
    }
    void setSource(Packet *p)
    {
        sitting_on_source.insert(p);
    }

    void setDest(Packet *p)
    {
        sitting_on_destination.insert(p);
    }
};

class on_air
{

    set<Packet *> packets_on_air;
    int number;
    double line_busy_till_time;

public:
    on_air()
    {
        number = 0;
        line_busy_till_time = 0;
    }

    void insert(Packet *packet_ptr)
    {
        // cout<<"YES\n";
        for (auto ptr : packets_on_air)
        {
            if (ptr->get_finishing_time() < VIRTUAL_TIME)
            {
                // cout<<"NDUENIUEH"<<endl;
                // packets_on_air.erase(ptr);
                ptr->packet_reception();
                number--;
            }
        }

        packets_on_air.insert(packet_ptr);
        if (packet_ptr->get_time() < line_busy_till_time)
        {
            number++;
            for (auto ptr : packets_on_air)
            {
                ptr->corrupt();
            }
            line_busy_till_time = max(line_busy_till_time, packet_ptr->get_finishing_time());
        }
        else
        {
            line_busy_till_time = packet_ptr->get_finishing_time();
            number++;
        }
    }
    void empty()
    {
        for (auto ptr : packets_on_air)
        {
            // packets_on_air.erase(ptr);
            ptr->packet_reception();
            number--;
        }
    }
};

void Packet::packet_transmit(on_air *transmission_line)
{
    transmission_line->insert(this);
}
void Packet::packet_reception()
{
    // cout<<"HELLO";
    if (done)
    {
        return;
    }
    if (!corrupted)
    {
        cout << "Packet " << name << " transferred successfully from node " << this->source->get_name() << " to node " << this->destination->get_name() << endl;
        success++;
    }
    else
    {
        cout << "Packet " << name << " corrupted. Starting time was " << get_time() << " and finishing time was " << get_finishing_time() << endl;
        failure++;
    }
    done = true;
}

void create_packet(heap *heap_ptr, Node** node_list,int T,int N,int i){
    int source = (rand() * N / RAND_MAX);
    int destination = (rand() * N / RAND_MAX);
    Packet * packet = new Packet(node_list[source], node_list[destination], 50 + (rand() * 950 / RAND_MAX), double(T) / 100 * rand() / RAND_MAX, i);
    node_list[source]->setSource(packet);
    node_list[destination]->setDest(packet);
    heap_ptr->insert(packet);
}

int main(int argc, char **argv)
{
    srand(0);
    if (argc < 4)
    {
        cout << "Please give number of nodes, time of simulation and number of packets!\n";
        return -1;
    }
    int N = atoi(argv[1]);
    int T = atoi(argv[2]);
    int number_of_packets = atoi(argv[3]);
    // cout << N << endl;
    Node *node_list[N];
    for (int i = 0; i < N; i++)
    {
        node_list[i] = new Node(i);
    }

    Packet *packet_list[number_of_packets];
    heap *heap_ptr = new heap();
    on_air *tranmission = new on_air();
    for (int i = 0; i < number_of_packets; i++)
    {
        int source = (rand() * N / RAND_MAX);
        int destination = (rand() * N / RAND_MAX);
        packet_list[i] = new Packet(node_list[source], node_list[destination], 50 + (rand() * 950 / RAND_MAX), double(T) / 100 * rand() / RAND_MAX, i);
        node_list[source]->setSource(packet_list[i]);
        node_list[destination]->setDest(packet_list[i]);
        heap_ptr->insert(packet_list[i]);
    };
    int extra = 0;
    while (VIRTUAL_TIME < T)
    {
        Packet *ptr = heap_ptr->min();

        double t = ptr->get_time();
        while (t < VIRTUAL_TIME)
        {
            ptr->packet_transmit(tranmission);
            heap_ptr->delete_min();
            ptr = heap_ptr->min();
            if (ptr == nullptr)
            {
                cout << "TIME FINISHED!!\n\n\n";
                break;
            }
            t = ptr->get_time();
        }
        if (ptr == nullptr)
        {
            break;
        }
        if(extra<atoi(argv[4])){
            create_packet(heap_ptr,node_list,T,N,number_of_packets++);
            extra++;
        }


        // cout<<VIRTUAL_TIME<<endl;
        VIRTUAL_TIME += 0.01;
    }
    cout << "The following results are if the server was allowed to run without any new requests\n\n";
    tranmission->empty();
    cout << endl
         << endl;
    cout << "The number of successful transfers are " << success<<endl;
    cout << "The number of corrupted transfers are " << failure<<endl;
    cout<<endl;
    return 0;
}