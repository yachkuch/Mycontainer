#include <iostream>
#include <map>

template<typename ValueType>
class OwnIterator : public std::iterator<std::input_iterator_tag, ValueType> {

private:
    ValueType* val;

public:
    OwnIterator(ValueType* first) :val(first) {};

    ValueType* operator ++(int size) { return val++; };
    ValueType* operator --(int size) { return val--; };
    ValueType* operator -(int size) { return val -size; };
    ValueType* operator +(int size) { return val+size; };
    bool operator ==(const OwnIterator& data) { return val == data.val; };
    bool operator !=(const OwnIterator& data) { return val != data.val; };

    ValueType& operator *() { return  *val; };

};


template<typename MyClass , typename MyAllocator= std::allocator<MyClass>>
class Ar {
public:

    typedef OwnIterator<MyClass> iterator;
    typedef OwnIterator<const MyClass> const_iterator;

    iterator begin() {
        return start;
    };

    iterator end() {
        return start + Size;
    };

    const_iterator cbegin() const {
        return start;
    };

    const_iterator cend() const {
        return start + Size;
    };


    Ar() {  };
    Ar(std::initializer_list<MyClass> init) {
        this->Size = init.size();
        capacity = 2*Size;
        start = alloc.allocate(capacity);
        int counter = 0;
        for (const MyClass a : init) {
            *start = a;
            start++;
        }
        start = start - Size;
    };

    Ar(int size) {
        this->Size = size;
        capacity = 2*size;
        start = alloc.allocate(capacity);
    };

    Ar(Ar&& data) noexcept {
        this->start = data.start;
        this->Size = data.Size;
        this->capacity = data.capacity;
        data.Size = 0;
        data.start = nullptr;
    }

    Ar(const Ar& data) {
        this->Size = data.Size;
        this->capacity = data.capacity;
        start = alloc.allocate(capacity);
        memcpy(start,data.start, data.Size * sizeof(MyClass));
    }

    Ar& operator = (const Ar& data) {
        this->Size = data.Size;
        start = alloc.allocate(capacity);
        memcpy(start, data.start, data.Size *sizeof(MyClass));
        return *this;
    }

    Ar& operator = ( Ar&& data) noexcept {
        Free();
        Size = data.Size;
        start = data.start;
        data.Size = 0;
        data.start = nullptr;
        return *this;
    }

    ~Ar() {
        Size = 0;
        alloc.deallocate(start);
    }

    void push_back(const MyClass &val) {
        
        if (Size == capacity) {
            recalculate_capacity(capacity);
            MyClass* buff = alloc.allocate(capacity);
            if (buff != start) {
                memcpy(buff, start, Size * sizeof(MyClass));
                std::swap(start, buff);
                alloc.deallocate(buff);
            }
        }
        alloc.construct(start+Size, val);
        this->Size += 1;
    }

    MyClass at(int number) {
        if (number > Size) {
            return MyClass();
        }
        else {
            return  start[number];
        }
    }

    bool isEmpty() {
        return Size > 0 ;
    }

    int size() {
        return this->size();
    }

private:
    int Size = 0; // число элементов
    MyClass* start = nullptr;
    int capacity = 0; // число элементов которые контейнер потенциально заложил
    MyAllocator alloc;

    void Free() {
        this->Size = 0;
        alloc.deallocate(this->start);
    }

    void recalculate_capacity(int& val) {
        val = val + 1;
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
        if (size > capasity) {
            capasity = 2 * size;
            buff = static_cast<Myal*>(operator new(capasity * sizeof(Myal)));
            std::cout << "Make new memory"<<std::endl<<"capas" << capasity<<std::endl;
            return buff;
        }
        else {
            std::cout << "Give save memory" << std::endl;
            return buff;
        }
    }
    void deallocate(Myal* poin, std::size_t size =NULL) {  
        ::operator delete(poin);
    }

    template <class Up, class... Args>
    void construct(Up* p, Args&&... args) {
        ::new ((void*)p) Up(std::forward<Args>(args)...);
    }

    void destroy(pointer p) {
        p->~T();
    }

    int get_capasity() const{
        return capasity;
    }

private:
   int capasity = 0;
   Myal* buff = nullptr;

};


using std::cout;
using std::move;
using std::endl;

class MycontainClass {
public: 
    int a;
};


int main()
{
    Ar<int, CustomAl<int>> a = {0,1};
    a.push_back(10);
    a.push_back(10);
    a.push_back(10);
    a.push_back(10);
    a.push_back(10);
    a.push_back(11);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    a.push_back(12);
    auto it = a.begin();
    while (it != a.end())
    {
        cout << *it << endl;
        it++;
    }
    cout << a.at(0)<<endl;

    // auto addd = std::map<int, int, CustomAl<std::pair<int, int>>>();
    //addd.insert(std::make_pair(2, 3));
    //addd.insert(std::make_pair(3, 3));
    //addd.insert(std::make_pair(4, 4));
    //addd.insert(std::make_pair(5, 5));
    //addd.insert(std::make_pair(6, 6));
    //cout << "map" << endl;
    //cout << addd.at(3);
    return 0;    
}

