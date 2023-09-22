#include <iostream>

class Ar {
public:
    Ar() { size = 0, start = new char; };
    Ar(std::initializer_list<char> init) { 
        this->size = init.size();
        start = new char[size];
        int counter = 0;
        for (const char a : init) {
            *start = a;
            start++;
        }
        start = start - size;
    };

    Ar(int size) {
        this->size = size;
        start = new char[size];
    };

    Ar(Ar&& data) noexcept {
        this->start = data.start;
        this->size = data.size;
        data.size = 0;
        data.start = nullptr;
    }

    Ar(Ar& data) {
        this->size = data.size;
        start = new char[this->size];
        memcpy(start,data.start,data.size);
    }

    Ar& operator = (const Ar& data) {
        this->size = data.size;
        start = new char[this->size];
        memcpy(start, data.start, data.size);
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

    void push_back(char val) {
        this->size += 1;
        char* buff = new char[this->size];
        memcpy(buff, this->start, size - 1);
        delete[]  this->start;
        this->start = buff;
        start[size - 1] = val;
    }

    char at(int number) {
        if (number > size) {
            return '\n';
        }
        else {
            return  start[number];
        }
    }

private:
    int size = 0;
    char* start = nullptr;

    void Free() {
        this->size = 0;
        delete[] this->start;
    }

};

using std::cout;
using std::move;
using std::endl;

void operation_with_array(std::unique_ptr<Ar> data) {
    cout << data->at(2)<<endl;
}
void operation_with_array_pointer(std::unique_ptr<Ar>& data) {
    cout << data->at(2) << endl;
}

int main()
{
    std::unique_ptr<Ar> pointer(new Ar);
    std::shared_ptr<Ar> pointer2(new Ar);
    std::shared_ptr<Ar> pointer3(pointer2);
    (*pointer).push_back('a');
    (*pointer).push_back('c');
    (*pointer).push_back('d');
    operation_with_array_pointer((pointer));
    cout << (*pointer).at(2)<<endl;
    return 0;    
}
