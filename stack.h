#ifndef STACK_H
#define STACK_H

#include <vector>

template <typename T>
class Stack{

public:

    void push(const T& value){
        elements.push_back(value);
    }

    void pop(){
        elements.pop_back();
    }

    T& top(){
        return elements.back();
    }

    bool empty(){
        return elements.size() == 0;
    }


private:
    std::vector<T> elements{};

};

#endif // !STACK_H