#include<iostream>
#include <limits>

#define DEFAULT_SIZE 0
#define RESIZE_FACTOR 2
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

int main() {
    /**
     * Driver code
     */
    vector v = vector();

    cout << "\nSize of blank vector: " << v.size() << endl;

    v = vector(10, 40);

    cout << "\nSize of new vector with default value of 40: " << v.size() << endl;

    cout << "\nValue at index 5: " << v[5];

    cout << "\nPushing values 1,2,4,5 at the end";
    v.push_back(1);
    v.push_back(2);
    v.push_back(4);
    v.push_back(5);

    cout << "\nVector contents after push_back():-\n";
    v.print_data();

    cout << "\nPoping twice from back";
    v.pop_back();
    v.pop_back();

    cout << "\nVector contents after pop_back():-\n";
    v.print_data();

    cout << "\nInserting 10 at index 0\n";
    v.insert(0, 10);

    cout << "\nInserting 20 at index 2\n";
    v.insert(2, 20);

    cout << "\nVector contents before erase():-\n";
    v.print_data();

    cout << "\nErasing item at index 2\n";
    v.erase(2);

    cout << "\nVector content after erase():-\n";
    v.print_data();

    cout << "\nElement at front:" << v.front();
    cout << "\nElement at back:" << v.back();
    return 0;
}