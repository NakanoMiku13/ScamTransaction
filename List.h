#include<iostream>
using namespace std;
#define null NULL
#define none null
template<typename T> using pointer = T*;
template<typename T1,typename T2> class Pair{
    public:
        T1 first;
        T2 second;
        Pair(T1 first = (T1)null, T2 second = (T2)null): first(first), second(second) {}
};
template<typename T > class node{
    private:
        T _value;
        pointer<node<T>> _position;
        pointer<node> _next, _prev;
    public:
        node(T value = (T)null, pointer<node<T>> position = nullptr) : _value(value), _next(nullptr), _prev(nullptr), _position(position){}
        auto SetValue(T value) {
            _value = value;
        }
        auto SetPosition(pointer<node<T>> position){
            _position = position;
        }
        auto GetPosition(){
            return _position;
        }
        auto GetValue() {
            return &_value;
        }
        auto GetValuePosition(){
            return _value;
        }
        auto SetNext(pointer<node> next)  {
            _next = next;
        }
        auto GetNext() {
            return _next;
        }
        auto SetPrev(pointer<node> prev) {
            _prev = prev;
        }
        auto GetPrev() {
            return _prev;
        }
};
template<typename T> class List{
    private:
        pointer<node<T>> _head, _tail;
        size_t _size;
        class _iterator{
            private:
                pointer<node<T>> _current;
            public:
                _iterator(pointer<node<T>> newNode): _current(newNode) {}
                auto &operator++(){
                    _current = _current->GetNext();
                    return _current;
                }
                auto operator++(int){
                    auto retVal = *this;
                    ++(*this);
                    return retVal;
                }
                auto &operator--(){
                    _current = _current->GetPrev();
                    return _current;
                }
                auto operator--(int){
                    auto retVal = *this;
                    --(*this);
                    return retVal;
                }
                auto *operator->(){
                    return &_current->GetValue();
                }
                auto &operator*(){
                    return _current->GetValue();
                }
                auto operator==(const auto& other){
                    return _current == other->_current;
                }
                auto operator!=(const auto& other){
                    return _current != other->_current;
                }
        };
    public:
        typedef _iterator iterator;
        List(initializer_list<T> ls = initializer_list<T>()) : _head(nullptr), _tail(nullptr), _size(0){ for(auto i : ls) Add(i);}
        auto Empty() { return (_size == 0) ? true : false; }
        auto &Front() { return *_head->GetValue(); }
        auto &Tail() { return *_tail->GetValue(); }
        auto NodePosition() { return _head; }
        auto Add(T value, pointer<node<T>> position = nullptr) {
            pointer<node<T>> newNode = new node<T>(value);
            //newNode->SetPosition(position);
            if(Empty()) _head = _tail = newNode;
            else{
                if(value == (T)null) return;
                newNode->SetPosition(position);
                newNode->SetPrev(_tail);
                _tail->SetNext(newNode);
                _tail = newNode;
            }
            _size++;
        }
        iterator begin(){
            return _head;
        }
        iterator end(){
            return _tail;
        }
        auto &operator[](const int index){
            auto move = _head;
            for(auto i = 0 ; i < index ; i++, move = move->GetNext());
            return *move->GetValue();
        }
        auto Exist(T value)->bool{
            auto move = _head;
            while(*move->GetValue() != value && move != nullptr){
                if(move->GetValue() == value) return true;
                move = move->GetNext();
            }
            return false;
        }
        auto Remove() {
            if(Empty()) return;
            else{
                auto temp = _tail;
                _tail = _tail->GetPrev();
                free(temp);
                _size--;
            }
        }
        auto Size() const { return _size; }
        auto Length() const { return Size();}
        auto Print() {
            T top = *_head->GetValue();
            cout<<"\nList print ("<<top<<"):\n";
            if(_head != nullptr and !Empty()){
                pointer<node<T>> move = _head;
                for(int i = 0 ; i < _size ; i++, move = move->GetNext()) cout<<*move->GetValue()<<endl;
            }
        }
};
template<typename T> class AdjacentList{
    private:
        pointer<node<List<T>>> _head, _tail;
        size_t _size;
    public:
        AdjacentList(initializer_list<Pair<T,T>> initial = initializer_list<Pair<T,T>>()): _head(nullptr), _tail(nullptr), _size(0){ for(auto i : initial) Add(i);}
        auto Empty() const{
            return _size == 0;
        }
        auto Front() const {
            return _head->GetValue();
        }
        auto Back() const {
            return _tail->GetValue();
        }
        auto Size(){
            return _size;
        }
        auto Length(){
            return Size();
        }
        auto Find(T value)->pointer<node<List<T>>>{
            if(Empty()) return nullptr;
            else{
                pointer<node<List<T>>> move = _head;
                while(move != nullptr){
                    List<T> val = *move->GetValue();
                    if(val.Front() == value) return move;
                    move = move->GetNext();
                }
                return nullptr;
            }
        }
        auto Add(Pair<T,T> value)->void{
            if(value.first == (T)null) return;
            else{
                if(Empty()){
                    pointer<node<List<T>>> newNode = new node<List<T>>({value.first, value.second});
                    _head = _tail = newNode;
                    _size++;
                    Add({value.second,(T)null});
                }
                else{
                    auto temp = Find(value.first);
                    if(temp == nullptr){
                        pointer<node<List<T>>> newNode = new node<List<T>>({value.first, value.second});
                        newNode->SetPrev(_tail);
                        _tail->SetNext(newNode);
                        _tail = newNode;
                        _size++;
                        Add({value.second,(T)null});
                    }else{
                        temp->GetValue()->Add(value.second);
                    }
                    //Setting the memory values
                    pointer<node<List<T>>> move = _head;
                    while(move != nullptr){
                        auto listHead = move->GetValue()->NodePosition();
                        while(listHead->GetNext() != nullptr){
                            listHead->SetPosition(Find(*listHead->GetValue())->GetValue()->NodePosition());
                            listHead = listHead->GetNext();
                        }
                        move = move->GetNext();
                    }
                }
            }
        }
        auto Print(){
            auto move = _head;
            while(move != nullptr){
                move->GetValue()->Print();
                cout<<endl;
                move = move->GetNext();
            }
        }
};