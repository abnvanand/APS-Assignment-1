#ifndef APS_ASSIGNMENT_1_HEAP_H
#define APS_ASSIGNMENT_1_HEAP_H

#include <iostream>
#include <vector>

#define PARENT(i) (i-1)/2
#define LEFT_CHILD(i) (2 * i) + 1
#define RIGHT_CHILD(i) (2 * i) + 2

#define MIN_HEAP 1
#define MAX_HEAP 2

using namespace std;

/**
 * A min heap implementation
 * if index of parent == i
 * the two children are at 2i+1 and 2i+2
 *
 * if index of child = j
 * then parent is (j-1)/2
 */
class heap {
    // TODO : use custom vector implementation as underlying DS
    vector<int> arr;
    int type = MIN_HEAP;

public:
    heap() = default;

    heap(int type) {
        this->type = type;
    }

    unsigned long size() {
        return arr.size();
    }

    void swap(int &a, int &b) {
        int temp = a;
        a = b;
        b = temp;
    }

    int get_heap_aware_number(int x) {
        if (type == MAX_HEAP)
            return -x;
        else
            return x;
    }

    void heapify_bottom() {
        int i = static_cast<int>(this->size() - 1);

        while (i > 0) {
            if (arr[i] < arr[PARENT(i)]) {
                swap(arr[i], arr[PARENT(i)]);
                i = PARENT(i);
            } else
                break;
        }
    }

    void heapify_top() {
        if (this->size() <= 1)
            return;

        int i = 0;
        // start from root
        while (i < this->size()) {
            if (RIGHT_CHILD(i) >= this->size()) {
                // right child does not exist
                // test with left child only
                if (LEFT_CHILD(i) >= this->size())
                    return;

                // only left child exists
                if (arr[i] > arr[LEFT_CHILD(i)])
                    swap(arr[i], arr[LEFT_CHILD(i)]);
                return;
            }
            // both children exist


            if (arr[i] > arr[LEFT_CHILD(i)] || arr[i] > arr[RIGHT_CHILD(i)]) {
                // if parent is greater than any of its child,
                // then swap the minimum to the top
                if (arr[LEFT_CHILD(i)] < arr[RIGHT_CHILD(i)]) {
                    // swap left with parent
                    swap(arr[i], arr[LEFT_CHILD(i)]);
                    i = LEFT_CHILD(i);
                } else {
                    // swap right with parent
                    swap(arr[i], arr[RIGHT_CHILD(i)]);
                    i = RIGHT_CHILD(i);
                }
            } else {
                // root is already smaller than both its children
                break;
            }
        }
    }

    bool empty() {
        return arr.empty();
    }

    int top() {
        return get_heap_aware_number(arr[0]);
    }

    void pop() {
        arr[0] = arr[arr.size() - 1];
        arr.pop_back(); // decrease size of underlying ds

        heapify_top();
    }

    void push(int x) {
        arr.push_back(get_heap_aware_number(x));
        heapify_bottom();
    }
};


#endif //APS_ASSIGNMENT_1_HEAP_H
