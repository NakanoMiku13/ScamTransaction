#include<iostream>
using namespace std;

#define null NULL
#define none null

template<typename T> using pointer = T*;

// Definición de la clase Pair
template<typename T1,typename T2> class Pair{
public:
    T1 first; // Primer elemento del par
    T2 second; // Segundo elemento del par
    bool hasValue; // Indicador de si el par tiene valor o no

    // Constructor con dos parámetros
    Pair(T1 first, T2 second) : first(first), second(second), hasValue(true) {}

    // Constructor con un parámetro
    Pair(T1 first) : first(first), hasValue(false) {}

    // Constructor sin parámetros
    Pair() : hasValue(false) {}

    // Función para verificar si el par tiene valor
    auto has_value(){
        return hasValue;
    }

    // Sobrecarga del operador de inserción (<<) para imprimir el par
    friend ostream& operator<<(ostream& os, const Pair<T1, T2>& val){
        os << val.first << " " << val.second << endl;
        return os;
    }
};

// Definición de la clase node
template<typename T > class node{
private:
    T _value; // Valor almacenado en el nodo
    pointer<node<T>> _position; // Posición del nodo en la lista
    pointer<node> _next, _prev; // Punteros al siguiente y anterior nodo

public:
    // Constructor de la clase node con parámetros
    node(T value = (T)null, pointer<node<T>> position = nullptr) : _value(value), _next(nullptr), _prev(nullptr), _position(position){}

    // Función para establecer el valor del nodo
    auto SetValue(T value) {
        _value = value;
    }

    // Función para establecer la posición del nodo
    auto SetPosition(pointer<node<T>> position){
        _position = position;
    }

    // Función para obtener la posición del nodo
    auto GetPosition(){
        return _position;
    }

    // Función para obtener el puntero al valor del nodo
    auto GetValue() {
        return &_value;
    }

    // Función para obtener el valor del nodo
    auto GetValuePosition(){
        return _value;
    }

    // Función para establecer el puntero al siguiente nodo
    auto SetNext(pointer<node> next)  {
        _next = next;
    }

    // Función para obtener el puntero al siguiente nodo
    auto GetNext() {
        return _next;
    }

    // Función para establecer el puntero al nodo anterior
    auto SetPrev(pointer<node> prev) {
        _prev = prev;
    }

    // Función para obtener el puntero al nodo anterior
    auto GetPrev() {
        return _prev;
    }
};

// Definición de la clase List
template<typename T> class List{
private:
    pointer<node<T>> _head, _tail; // Punteros al inicio y fin de la lista
    size_t _size; // Tamaño de la lista

    // Definición de la clase _iterator
    class _iterator{
    private:
        pointer<node<T>> _current; // Puntero al nodo actual

    public:
        // Constructor de la clase _iterator con parámetros
        _iterator(pointer<node<T>> newNode) : _current(newNode) {}

        // Sobrecarga del operador de incremento (++) prefijo
        auto& operator++(){
            _current = _current->GetNext();
            return _current;
        }

        // Sobrecarga del operador de incremento (++) sufijo
        auto operator++(int){
            auto retVal = *this;
            ++(*this);
            return retVal;
        }

        // Sobrecarga del operador de decremento (--) prefijo
        auto& operator--(){
            _current = _current->GetPrev();
            return _current;
        }

        // Sobrecarga del operador de decremento (--) sufijo
        auto operator--(int){
            auto retVal = *this;
            --(*this);
            return retVal;
        }

        // Sobrecarga del operador -> para acceder al valor del nodo actual
        auto* operator->(){
            return &_current->GetValue();
        }

        // Sobrecarga del operador * para obtener el valor del nodo actual
        auto& operator*(){
            return _current->GetValue();
        }

        // Sobrecarga del operador de igualdad (==) para comparar iteradores
        auto operator==(const pointer<node<T>>& other){
            return _current == other->_current;
        }

        // Sobrecarga del operador de desigualdad (!=) para comparar iteradores
        auto operator!=(const pointer<node<T>>& other){
            return _current != other->_current;
        }
    };

public:
    typedef _iterator iterator; // Definición del tipo de iterador

    // Constructor de la clase List con lista de inicialización
    List(initializer_list<T> ls = initializer_list<T>()) : _head(nullptr), _tail(nullptr), _size(0){
        for(auto i : ls)
            Add(i);
    }

    // Función para verificar si la lista está vacía
    auto Empty() {
        return (_size == 0) ? true : false;
    }

    // Función para obtener el primer elemento de la lista
    auto& Front() {
        return *_head->GetValue();
    }

    // Función para obtener el último elemento de la lista
    auto& Tail() {
        return *_tail->GetValue();
    }

    // Función para obtener la posición del nodo actual
    auto NodePosition() {
        return _head;
    }

    // Función para añadir un elemento a la lista
    auto Add(T value, pointer<node<T>> position = nullptr) {
        pointer<node<T>> newNode = new node<T>(value);
        if(Empty())
            _head = _tail = newNode;
        else{
            newNode->SetPrev(_tail);
            _tail->SetNext(newNode);
            _tail = newNode;
        }
        _size++;
    }

    // Función para obtener el iterador que apunta al inicio de la lista
    iterator begin(){
        return _head;
    }

    // Función para obtener el iterador que apunta al final de la lista
    iterator end(){
        return _tail;
    }

    // Sobrecarga del operador [] para acceder a un elemento de la lista mediante índice
    auto& operator[](const int index){
        auto move = _head;
        for(auto i = 0 ; i < index ; i++, move = move->GetNext());
        return *move->GetValue();
    }

    // Función para encontrar un valor en la lista
    auto Find(const T value) -> T{
        auto move = _head;
        for(auto i = 0 ; i < _size ; i++, move = move->GetNext())
            if(value == *move->GetValue())
                return value;
        return (T)null;
    }

    // Función para verificar si un valor existe en la lista
    auto Exist(T value) -> bool{
        auto move = _head;
        while(*move->GetValue() != value && move != nullptr){
            if(move->GetValue() == value)
                return true;
            move = move->GetNext();
        }
        return false;
    }

    // Función para eliminar el último elemento de la lista
    auto Remove() {
        if(Empty())
            return;
        else{
            auto temp = _tail;
            _tail = _tail->GetPrev();
            free(temp);
            _size--;
        }
    }

    // Función para obtener el tamaño de la lista
    auto Size() const {
        return _size;
    }

    // Función para obtener la longitud de la lista
    auto Length() const {
        return Size();
    }

    // Función para imprimir los elementos de la lista
    auto Print() {
        T top = *_head->GetValue();
        cout << "\nList print (" << top << "):\n";
        if(_head != nullptr && !Empty()){
            pointer<node<T>> move = _head;
            for(int i = 0 ; i < _size ; i++, move = move->GetNext())
                cout << *move->GetValue() << endl;
        }
    }
};

// Definición de la clase AdjacentList
template<typename T> class AdjacentList{
private:
    pointer<node<List<T>>> _head, _tail; // Punteros al inicio y fin de la lista
    size_t _size; // Tamaño de la lista

public:
    // Constructor de la clase AdjacentList con lista de inicialización
    AdjacentList(initializer_list<Pair<T,T>> initial = initializer_list<Pair<T,T>>()) : _head(nullptr), _tail(nullptr), _size(0){
        for(auto i : initial)
            Add(i);
    }

    // Función para verificar si la lista está vacía
    auto Empty() const{
        return _size == 0;
    }

    // Función para obtener el primer elemento de la lista
    auto Front() const {
        return _head->GetValue();
    }

    // Función para obtener el último elemento de la lista
    auto Back() const {
        return _tail->GetValue();
    }

    // Función para obtener el tamaño de la lista
    auto Size(){
        return _size;
    }

    // Función para obtener la longitud de la lista
    auto Length(){
        return Size();
    }

    // Función para encontrar un valor en la lista
    auto Find(T value) -> pointer<node<List<T>>>{
        if(Empty())
            return nullptr;
        else{
            pointer<node<List<T>>> move = _head;
            while(move != nullptr){
                List<T> val = *move->GetValue();
                if(val.Front() == value)
                    return move;
                move = move->GetNext();
            }
            return nullptr;
        }
    }

    // Función para añadir un elemento a la lista
    auto Add(Pair<T,T> value) -> void{
        if(!value.has_value()){
            return;
        }
        else{
            if(Empty()){
                pointer<node<List<T>>> newNode = new node<List<T>>({value.first, value.second});
                _head = _tail = newNode;
                _size++;
                Add(Pair<T,T>(value.second));
            }
            else{
                auto temp = Find(value.first);
                if(temp == nullptr){
                    pointer<node<List<T>>> newNode = new node<List<T>>({value.first, value.second});
                    _tail->SetNext(newNode);
                    newNode->SetPrev(_tail);
                    _tail = newNode;
                    _size++;
                    Add(Pair<T,T>(value.second));
                }
                else
                    Add(Pair<T,T>(value.second));
            }
        }
    }

    // Función para imprimir los elementos de la lista
    auto Print(){
        cout << "\nAdjacent List print (" << Size() << "):\n";
        if(_head != nullptr && !Empty()){
            pointer<node<List<T>>> move = _head;
            for(int i = 0 ; i < _size ; i++, move = move->GetNext()){
                List<T> val = *move->GetValue();
                cout << val.Front();
                for(int j = 0 ; j < val.Size() ; j++){
                    cout << " -> " << val[j];
                }
                cout << endl;
            }
        }
    }
};