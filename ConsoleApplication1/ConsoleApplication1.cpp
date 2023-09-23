#include <iostream>

template<typename MyClass >
class Ar {
public:
    Ar() { size = 0, start = new MyClass; };
    Ar(std::initializer_list<MyClass> init) {
        this->size = init.size();
        start = new MyClass[this->size * sizeof(MyClass)];
        int counter = 0;
        for (const MyClass a : init) {
            *start = a;
            start++;
        }
        start = start - size;
    };

    Ar(int size) {
        this->size = size;
        start = new MyClass[this->size * sizeof(MyClass)];
    };

    Ar(Ar&& data) noexcept {
        this->start = data.start;
        this->size = data.size;
        data.size = 0;
        data.start = nullptr;
    }

    Ar(Ar& data) {
        this->size = data.size;
        start = new MyClass[this->size * sizeof(MyClass)];
        memcpy(start,data.start, data.size * sizeof(MyClass));
    }

    Ar& operator = (const Ar& data) {
        this->size = data.size;
        start = new MyClass[this->size * sizeof(MyClass)];
        memcpy(start, data.start, data.size *sizeof(MyClass));
        return *this;
    }

    Ar& operator = ( Ar&& data) noexcept {
        Free();
        size = data.size;
        start = data.start;
        data.size = 0;
        data.start = nullptr;
        return *this;
    }

    ~Ar() {
        size = 0;
        delete []start;
    }

    void push_back(MyClass val) {
        this->size += 1;
        MyClass* buff = new MyClass[this->size *sizeof(MyClass)];
        memcpy(buff, this->start, size * sizeof(MyClass));
        delete[]  this->start;
        this->start = buff;
        start[size - 1] = val;
    }

    MyClass at(int number) {
        if (number > size) {
            return '\n';
        }
        else {
            return  start[number];
        }
    }

    bool isEmpty() {
        return size > 0 ? true:false;
    }

private:
    int size = 0;
    MyClass* start = nullptr;

    void Free() {
        this->size = 0;
        delete[] this->start;
    }

};

using std::cout;
using std::move;
using std::endl;


int main()
{
    Ar<int> a = {0,1,2,3,4,5,6,7,8,9};
    
    

    return 0;    
}

