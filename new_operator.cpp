// C++ program to illustrate the placement new operator 
#include<iostream> 
namespace jly_tutorials
{
    using namespace std;

    class car
    {
        string name;
        int num;

    public:

        car(string a, int n)
        {
            cout << "Constructor called" << endl;
            this->name = a;
            this->num = n;
        }

        void display()
        {
            cout << "Name: " << name << endl;
            cout << "Num: " << num << endl;
        }

        void* operator new(size_t size)
        {
            cout << "new operator overloaded" << endl;
            void* p = malloc(size);
            return p;
        }

        void operator delete(void* ptr)
        {
            cout << "delete operator overloaded" << endl;
            free(ptr);
        }
    };

    int main_new_operator()
    {
        car* p = new car("HYUNDAI", 2012);
        p->display();
        delete p;

        car c = car("vw", 1969);
        c.display();

        return 0;
    }

    /*
    Before placement new :
    X : 10
    &X : 004FFC54

    After placement new :
    X : 100
    mem : 004FFC54
    &X : 004FFC54
    */
    int main_new_placement()
    {
        // initial value of X 
        int X = 10;

        cout << "Before placement new :" << endl;
        cout << "X : " << X << endl;
        cout << "&X : " << &X << endl;

        // Placement new changes the value of X to 100 
        int* mem = new (&X) int(100);

        cout << "\nAfter placement new :" << endl;
        cout << "X : " << X << endl;
        cout << "mem : " << mem << endl;
        cout << "&X : " << &X << endl;

        // https://www.youtube.com/watch?v=IAdLwUXRUvg @ 21.13
        // allocate a buffer for ints
        byte* buf = new byte[sizeof(int)];
        //int *pbuf = new(buf) int(5);
        // initial the buffer to int(5) 
        new(buf) int(5);
        // recast buf as pointer to int
        int* pbuf = reinterpret_cast<int*>(buf);
        cout << "*buf = " << pbuf[0] << endl;


        // allocate, initialize memory, get pointer
        int* p = new int(3);
        cout << "*p = " << *p << endl;
        return 0;
    }
}