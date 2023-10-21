#include <iostream>
#include <string>
#include <sstream>
#include <time.h>

class Obj
{
public:
    int num{ 0 };
    std::string text;
    Obj() = default;
    Obj(int Num, std::string Text);
    ~Obj();
};

Obj::Obj(int Num, std::string Text) :num(Num), text(Text) {}
Obj::~Obj() {}

template <class T>
class Node
{
public:
    T value;
    Node<T>* prev{ nullptr };
    Node<T>* next{ nullptr };
};

template <class T>
class linked_list
{
public:
    Node<T>* Tail;
    Node<T>* Head;
    int Size;
    void add_beg(T* obj);
    void add_end(T* obj);
    void delete_end();
    void delete_beg();
    T* operator[](int index)
    {
        if (index < 0 || index >= this->Size)
        {
            std::cout << "Wrong index\n";
            return (nullptr);
        }
        Node<T>* Tail2 = this->Tail;
        T* object = &Tail2->value;
        for (int i = 0; i < index; ++i)
        {
            Tail2 = Tail2->next;
            object = &Tail2->value;
        }
        Tail2 = nullptr;
        delete Tail2;
        return object;
    }
    void Get(Obj* obj);
    void Change(Obj* obj, Obj* obj2);
    bool Search(Obj* obj);
    bool Compare(Obj* obj1, Obj* obj2);
    bool Search_and_delete(Obj* obj);
    void Add_Position(Obj* obj, int index);
    void Clear();
    void To_String();
};

template <class T>
void linked_list<T>::add_end(T* obj)
{
    Node<T>* node = new Node<T>();
    ++this->Size;
    if (this->Size == 1)
    {
        node->next = nullptr;
        node->prev = nullptr;
        this->Tail = node;
        this->Head = node;
    }
    else
    {
        this->Head->next = node;
        node->prev = this->Head;
        node->next = nullptr;
        this->Head = node;
    }
    node->value = *obj;
}

template<class T>
void linked_list<T>::add_beg(T* obj)
{
    Node<T>* node = new Node<T>();
    ++this->Size;
    if (this->Size == 1)
    {
        node->next = nullptr;
        node->prev = nullptr;
        this->Tail = node;
        this->Head = node;
    }
    else
    {
        this->Tail->prev = node;
        node->next = this->Tail;
        node->prev = nullptr;
        this->Tail = node;
    }
    node->value = *obj;
}

template<class T>
void linked_list<T>::delete_end()
{
    --this->Size;
    if (this->Size == 0)
    {
        delete& this->Head->value;
        this->Tail = this->Head = nullptr;
    }
    else
    {
        this->Head = this->Head->prev;
        this->Head->next->prev = nullptr;
        delete& this->Head->next->value;
        this->Head->next = nullptr;
    }
}

template<class T>
void linked_list<T>::delete_beg()
{
    --this->Size;
    if (this->Size == 0)
    {
        delete& this->Head->value;
        this->Tail = this->Head = nullptr;
    }
    else
    {
        this->Tail = this->Tail->next;
        this->Tail->prev->next = nullptr;
        delete& this->Tail->prev->value;
        this->Tail->prev = nullptr;
    }
}

template<class T>
void linked_list<T>::Get(Obj* obj)
{
    if (obj == nullptr) {}
    else
    {
        std::string str = "| Num : ";
        str += std::to_string(obj->num) + " | Text : " + obj->text + " |\n";
        std::cout << str;
    }
}

template<class T>
void linked_list<T>::Change(Obj* obj, Obj* obj2)
{
    if (obj != nullptr)
    {
        obj->num = obj2->num;
        obj->text = obj2->text;
        delete obj2;
    }
}

template<class T>
bool linked_list<T>::Compare(Obj* obj1, Obj* obj2)
{
    return (obj1->num == obj2->num && obj1->text == obj2->text) ? true : false;
}

template<class T>
bool linked_list<T>::Search(Obj* obj)
{
    for (int index = 0; index < this->Size; ++index)
    {
        if (Compare((*this)[index], obj))
        {
            std::cout << (*this)[index] << std::endl;
            return true;
        }
    }
    std::cout << "Object was not founded\n";
    return false;
}

template<class T>
bool linked_list<T>::Search_and_delete(Obj* obj)
{
    Node<T>* Tail2 = this->Tail;
    for (int index = 0; index < this->Size; ++index, Tail2 = Tail2->next)
    {
        if (Compare((*this)[index], obj))
        {
            if (this->Size != 1 && index != 0 && index != this->Size-1)
            {
                Tail2->prev->next = Tail2->next;
                Tail2->next->prev = Tail2->prev;
                Tail2->prev = Tail2->next = nullptr;
            }
            else if (this->Size != 1 && index == 0)
            {
                this->Tail = this->Tail->next;
                Tail2->next->prev = nullptr;
                Tail2->next = nullptr;
            }
            else if (this->Size != 1 && index == this->Size - 1)
            {
                this->Head = this->Head->prev;
                Tail2->prev->next = nullptr;
                Tail2->prev = nullptr;
            }
            else
            {
                delete Tail;
                this->Tail = this->Head = nullptr;
            }
            delete Tail2;
            Tail2 = nullptr;
            --this->Size;
            return true;
        }
    }
    Tail2 = nullptr;
    delete Tail2;
    return false;
}

template<class T>
void linked_list<T>::Add_Position(Obj* obj, int index)
{
    if (index < 0 && index >= this->Size)
    {
        std::cout << "Wrong index\n";
    }
    else
    {
        Node<T>* Tail2 = this->Tail;
        for (int index2 = 0; index2 < index - 1; ++index2, Tail2 = Tail2->next) {}
        Node<T>* node = new Node<T>();
        if (index > 0 && index < this->Size)
        {
            node->prev = Tail2;
            node->next = Tail2->next;
            Tail2->next->prev = node;
        }
        else if (index == this->Size)
        {
            node->next = nullptr;
            Tail2->next = node;
            node->prev = Tail2;
            this->Head = node;
        }
        else if (index == 0)
        {
            node->prev = nullptr;
            node->next = this->Tail;
            this->Tail->prev = node;
            this->Tail = node;
        }
        node->value = *obj;
        ++this->Size;
        Tail2 = nullptr;
        delete Tail2;
    }
}

template<class T>
void linked_list<T>::Clear()
{
    while (this->Tail != this->Head)
    {
        this->Tail = this->Tail->next;
        delete this->Tail->prev;
        this->Tail->prev = nullptr;
    }
    delete this->Tail;
    this->Tail = this->Head = nullptr;
    this->Size = NULL;
}

template<class T>
void linked_list<T>::To_String()
{
    std::cout << "\tList\n";
    std::cout << "\t| Address : " << this << " | Size : " << this->Size << " |\n" << "\t| Objects |\n";
    int i = 1;
    Node<T>* Tail2 = this->Tail;
    while (Tail2 != nullptr)
    {
        Obj* obj = static_cast<T*>(&Tail2->value);
        std::cout<<"\t| Object "<<i++<<" | Address of object : "<<Tail2<<" | Previous : "<<Tail2->prev<<" | Next : "<<Tail2->next<<" | (Value) Num : "<<obj->num<<" | (Value) Text : "<<obj->text<<" |\n";
        Tail2 = Tail2->next;
        obj = nullptr;
        delete obj;
    }
    Tail2 = nullptr;
    delete Tail2;
}

int main()
{
    int Num{ 0 };
    std::string Text;
    linked_list<Obj>* l1 = new linked_list<Obj>();
    const int n1 = 10;
    clock_t timer1 = clock();
    for (int i = 0; i < n1; ++i)
    {
        std::cout << "Give data for object\nNum : ";
        std::cin >> Num;
        std::cout << "Text : ";
        std::cin >> Text;
        Obj* obj = new Obj(Num, Text);
        clock_t timer3 = clock();
        l1->add_end(obj);
        clock_t timer4 = clock();
        double time1 = (timer4 - timer3) / (double)CLOCKS_PER_SEC;
        std::cout << "| Time for one object : " << time1 << std::endl;
    }
    clock_t timer2 = clock();
    l1->To_String();
    double time1 = (timer2 - timer1) / (double)CLOCKS_PER_SEC;
    std::cout << "| Full time : " << time1 << " |\n";
    const int n2 = 5;
    timer1 = clock();
    for (int j = 0; j < n2; ++j)
    {
        std::cout << "Give random data to find object by your data\nNum : ";
        std::cin >> Num;
        std::cout << "Text : ";
        std::cin >> Text;
        Obj* obj = new Obj(Num, Text);
        clock_t timer3 = clock();
        l1->Search_and_delete(obj);
        clock_t timer4 = clock();
        delete obj;
        double time2 = (timer4 - timer3) / (double)CLOCKS_PER_SEC;
        std::cout << "| Time for one object : " << time2 << std::endl;
    }
    timer2 = clock();
    l1->To_String();
    double time2 = (timer2 - timer1) / (double)CLOCKS_PER_SEC;
    std::cout << "| Full time : " << time2 << " |\n";
    l1->Clear();
    delete l1;
    return 0;
}
