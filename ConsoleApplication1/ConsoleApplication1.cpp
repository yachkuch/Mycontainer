#include <iostream>

template<typename MyClass , typename MyAllocator= std::allocator<MyClass>>
class Ar {
public:
    Ar() { size = 0, start = new MyClass; };
    Ar(std::initializer_list<MyClass> init) {
        this->size = init.size();
        capacity = size;
        start = alloc.allocate(capacity);
        int counter = 0;
        for (const MyClass a : init) {
            *start = a;
            start++;
        }
        start = start - size;
    };

    Ar(int size) {
        this->size = size;
        capacity = size;
        start = new MyClass[this->size * sizeof(MyClass)];
    };

    Ar(Ar&& data) noexcept {
        this->start = data.start;
        this->size = data.size;
        this->capacity = data.capacity;
        data.size = 0;
        data.start = nullptr;
    }

    Ar(Ar& data) {
        this->size = data.size;
        this->capacity = data.capacity;
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

    void push_back(const MyClass &val) {
        
        if (size == capacity) {
            recalculate_capacity(capacity);
            MyClass* buff = alloc.allocate(capacity);
            memcpy(buff,start, size*sizeof(MyClass));
            std::swap(start, buff);
            alloc.deallocate(buff);
        }
        alloc.construct(start+size, val);
        this->size += 1;
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
    int size = 0; // число элементов
    MyClass* start = nullptr;
    int capacity = 0; // число элементов которые контейнер потенциально заложил
    MyAllocator alloc;

    void Free() {
        this->size = 0;
        delete[] this->start;
    }

    void recalculate_capacity(int& val) {
        val = val + 10;
    }

};

template <typename Myal>
struct CustomAl {
    typedef Myal value_type;
    typedef Myal* pointer;
    typedef const Myal* const_pointer;
    typedef Myal& reference;
    typedef const Myal& const_reference;
    
    CustomAl() {};
    template<class U>CustomAl(const CustomAl<U>& data) { this = data; }
    template<class U>CustomAl(const CustomAl<U>&& data) { this = data; data = nullptr; }

    Myal* allocate(int size) {
        return static_cast<Myal*>(operator new(size * sizeof(Myal)));
    }
    void deallocate(Myal* poin) {  // деалокатор определил по своему
        ::operator delete(poin);
    }

    template <class Up, class... Args>
    void construct(Up* p, Args&&... args) {
        ::new ((void*)p) Up(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

};

using std::cout;
using std::move;
using std::endl;


int main()
{
    Ar<int, CustomAl<int>> a = {0,1,2,3,4,5,6,7,8,9};
    a.push_back(10);
    a.push_back(11);
    a.push_back(12);
    cout << a.at(0);
    return 0;    
}

