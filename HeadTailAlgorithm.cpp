#include <iostream>
#include <ctime>
#include <stdlib.h>

using namespace std;

class Queue
{
private:
    struct queue
    {
        int value;
        queue* next;
    };
    queue* head;
    int count = 0;

public:
    unsigned long long int iter = 0;
    Queue();
    ~Queue();
    void Add(int v);
    int Del();
    void ShowAll();
    int ShowHead();
    bool Empty();
    void sort_LS();
};

Queue::Queue()
{
    head = NULL;
}

Queue::~Queue()
{
    queue* tmp;
    while (head != NULL)
    {
        tmp = head;
        head = head->next;
        delete tmp;
    }
    delete head;
}

void Queue::Add(int v)//1+3+1+2+2+1+2+2n+2+2+2=2n+18
{
    queue* tmp = new(queue); iter += 3;//3
    if (tmp == NULL) { cout << "Очередь пуста (Push)..." << endl; return; }; iter += 1;//1
    tmp->next = NULL; iter += 2;//2
    tmp->value = v; iter += 2;//2
    iter++;
    if (head == NULL) //1
    {
        head = tmp; iter += 1;//1
    }
    else
    {
        queue* curr = head; iter += 2;//2
        while (curr->next != NULL)//sum(1,n)[2] = 2n
        {
            //iter += 2;
            curr = curr->next; iter += 2;//2
        }
        curr->next = tmp; iter += 2;//2
    }
    count++; iter += 2;//2
}

int Queue::Del()//1+2+2+2+1+2+1=11
{
    if (Empty())//1
    {
    
        cout << "Очередь пуста (Pop)..." << endl; iter++; return -1;
    }
    queue* tmp = head; iter += 2;//2
    head = head->next; iter += 2;//2
    int ret = tmp->value; iter += 2;//2
    delete tmp; iter++;//1
    count--; iter += 3;//2
    return ret;//1
}

void Queue::ShowAll()//1+2+3n=3n+3
{
    
    if (Empty())//1
    {
        cout << "Очередь пуста (ShowAll)..." << endl; iter++; return;
    }
    queue* tmp = head; iter += 2;//2
    while (tmp)//sum(1,n)[3]=3n
    {
        iter += 3;
        cout << tmp->value << "\n";//1
        tmp = tmp->next;//2
    }
    cout << endl;
}

int Queue::ShowHead()//1
{
    return head->value; iter++;//1
}

int Get(Queue* b, int index)//3+3+5+9n+2+2+3+7n+3+7n+1+1=23n+23
{
    int i;
    Queue* c = new Queue(); b->iter += 3;//3
    b->iter += 5;
    for (i = 0; ((!b->Empty()) && (i < index)); i++)//1+4+sum(1,n)[3+4+2]=5+9n
    {
        b->iter += 9;
        c->Add(b->Del());//3
    }
    int ret = b->Del(); b->iter += 2;//2
    c->Add(ret); b->iter += 2;//2

    b->iter += 3;
    for (i = 0; !b->Empty(); i++)//3+sum(1,n)[2+2+3]=3+7n
    {
        b->iter += 7;
        c->Add(b->Del());//3
    }

    b->iter += 3;
    for (i = 0; !c->Empty(); i++)//3+sum(1,n)[3+2+2]=3+7n
    {
        b->iter += 7;
        b->Add(c->Del());//3
    }

    delete c; b->iter += 2;//1
    return ret;//1
}

void Set(int x, Queue* b, int index)//4+3+5+9n+2+2+2+5n+3+7n+1=21n+22
{
    int i;
    Queue* c = new Queue(); b->iter += 3;//3
    b->iter += 5;
    for (i = 0; ((!b->Empty()) && (i < index)); i++)//5+sum(1,n)[4+2+3]=5+9n
    {
        b->iter += 9;
        c->Add(b->Del());//3
    }
    int ret = b->Del(); b->iter += 2;//2
    c->Add(x); b->iter += 2;//2
    b->iter += 2;
    for (; !b->Empty();)//2+sum(1,n)[2+3]=2+5n
    {
        b->iter += 5;
        c->Add(b->Del());//3
    }

    b->iter += 3;
    for (i = 0; !c->Empty(); i++)//1+2+sum(1,n)[2+2+3]=3+7n
    {
        b->iter += 7;
        b->Add(c->Del());//3
    }

    delete c; b->iter++;//1
}

void Queue::sort_LS()
{
    int cnt = 0;
    iter += 2;
    for (int i = 0; i < count; i++)//2+sum(1,n)[3+23n+26+2+67n^2+81n+21n+26]=2+125n^2+67n^3+57n
    {
        cnt++;
        int x = Get(this, i); iter += 3;//23n+23+3=23n+26
        int j = i - 1; iter += 2;//2
        
        while (j >= 0 && Get(this, j) > x)//sum(1,n)[1+23n+23+2+1+1+44n+51+2]=67n^2+81n
        {
            
            Set(Get(this, j), this, j + 1); iter += 6;//23n+23+21n+22+2+3+1=44n+51
            j--; iter += 2;//2
        }
        
        Set(x, this, j + 1); iter += 4;//21n+22+4=21n+26
    }
}

bool Queue::Empty()//1
{
    iter++;
    return head == NULL ? true : false;//1
}





int main()
{
    setlocale(LC_ALL, "Russian");


    int N = 50;
    for (int j = 0; j < 10; j++)
    {
        Queue stack;
        for (int i = 0; i < N; i++)
        {
            stack.Add(rand() % 100);
        }
        unsigned long long int g = 67 * N * N * N + 125 * N * N + 57 * N + 2;
        int start_time = clock();
        stack.sort_LS();
        int end_time = clock();
        double total_time = double(end_time - start_time) / 1000;
        cout << "Кол-во элементов: " << N;
        cout << " Посчитанное кол-во: " << stack.iter;
        cout << " Асимптотическая оценка: " << (int)N * N * N;
        cout << " Теоретическое кол-во: " << g;
        cout << " Время: " << total_time << "\n";
        N += 50;
    }
    //cout << "yyy";
}



