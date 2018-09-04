#ifndef APS_ASSIGNMENT_1_VECTOR_H
#define APS_ASSIGNMENT_1_VECTOR_H

#define DEFAULT_SIZE 0
#define RESIZE_FACTOR 2

#include <iostream>

using namespace std;


class vector {
private:
    int *arr{};
    int length = 0;                 // tells the number of items currently stored
    int capacity = DEFAULT_SIZE;    // how much can we fill the current vector without any resize

    void resize(int new_capacity) {
        int *temp = new int[new_capacity];  // create an array of new capacity

        // Copy all existing elements
        for (int i = 0; i < this->capacity; i++) {
            temp[i] = arr[i];
        }

        delete[] arr;   // delete old array
        arr = temp;     // point to new array

        this->capacity = new_capacity; // update the variable capacity
    }

public:
    vector() = default;

    vector(int n, int x) {
        resize(n);          // create an array of supplied size

        // set default value on each item
        for (int i = 0; i < n; i++) {
            arr[i] = x;
            length += 1;
        }
    }

    int size() {
        return this->length;
    }

    int &operator[](int);

    int get(int index) {
        return arr[index];
    }

    // TODO: handle shrinking as well
    void push_back(int x) {
        if (length == capacity) {  // current array is full
            resize(RESIZE_FACTOR * capacity); // make a new array of twice the size
        }

        arr[length] = x;
        length += 1;
    }

    void pop_back() {
        length -= 1;    // just decrease the length; effectively removing the last element
    }

    // Allows inserting at index = length by resizing array.
    // Done to imitate vector implementation of STL
    // so for eg a user can insert values into an empty vector by using insert instead of push_back()
    // but only from the 0th index; incrementing index by one at a time.
    void insert(int index, int x) {
        if (index > length) {
            throw "Index out of bounds.";
        }

        if (length == capacity) {
            resize(RESIZE_FACTOR * capacity);
        }

        // copy right
        for (int i = length; i > index; i--)
            arr[i] = arr[i - 1];

        // insert at given index
        arr[index] = x;
        length += 1;    // One more item added now
    }

    void erase(int index) {
        for (int i = index; i < length - 1; i++)
            arr[i] = arr[i + 1];

        length -= 1;    // decrease number of elements by 1
    }

    int front() {
        return arr[0];
    }

    int back() {
        return arr[length - 1];
    }

    void print_data() {
        cout << endl;
        for (int i = 0; i < this->length; i++)
            cout << arr[i] << " ";
    }
};

int &vector::operator[](int index) {
    if (index >= length or index < 0)
        throw "Index out of bounds.";

    return arr[index];
}

#endif //APS_ASSIGNMENT_1_VECTOR_H
