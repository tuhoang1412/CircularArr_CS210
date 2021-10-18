// STUDENT ORGANIC WAGYU CODE
// Author: Tu Hoang
// San Diego State University
// CS210/CS496: Data Structures
//
// File: CircularArray.h
// Defines the CircularArray collection class.

//define VERSION_CIRARRAY 0.1

// STUDENT CODE
#ifndef C210_PROGRAM1_CIRCULARARRAY_H
#define C210_PROGRAM1_CIRCULARARRAY_H

#define TEST_START_CAPACITY 10
#define TEST_START_ARRAY_SIZE 10


#include "Queue.h"
#include "List.h"
#include <cstring>

namespace sdsu {
    template<typename T>
    class CircularArray : public sdsu::Queue<T>, public sdsu::List<T> {

    private:
        // Size represents how many T items the structure holds
        int curSize{};

        // Capacity represents how many T items the structure CAN hold
        int curCapacity{};

        // todo: head and tail counters for the circular nature
        int frontIndex{}, backIndex{};

        // the array on the heap
        T *storage;


        //Check if the array is full
        bool isFull() {
            if (curSize >= 0.8 * curCapacity)
                return expandCapacity();
            else
                return false;
        }

        //Check if the array is shrinkable
        void isShrinkable() {
            if (curSize <= 0.3 * curCapacity)
                shrinkCapacity();
        }

        //Doubling the size of the array
        bool expandCapacity() {
            T *arr = storage;
            storage = new T[curCapacity * 2];
            for (int i = 0; i < curSize; i++) {
                storage[i] = arr[(i + frontIndex) % curCapacity];
            }
            frontIndex = 0;
            backIndex = curSize - 1;
            curCapacity <<= 1;
            delete[] arr;
            return false;

        }

        //Reducing the capacity by half
        void shrinkCapacity() {
            T *arr = storage;
            storage = new T[curCapacity / 2];
            for (int i = 0; i < curSize; i++) {
                storage[i] = arr[(i + frontIndex) % curCapacity];
            }
            frontIndex = 0;
            backIndex = curSize - 1;
            curCapacity >>= 1;
            delete[] arr;
        }

    public:

        // This is the default class constructor. It sets the current size to 0
        CircularArray() : curSize(0) {
            frontIndex = 0;
            backIndex = 0;
            // todo: initialize a default capacity storage array on the heap
            curCapacity = TEST_START_CAPACITY;
            storage = new T[TEST_START_ARRAY_SIZE];
        }

        //Destructor
        ~CircularArray() override {
            delete[] storage;
        }

        // The copy constructor!
        CircularArray(const CircularArray<T> &other){
            std::cout << "Copying . . .";
            curCapacity = other.curCapacity;
            curSize = other.curSize;
            storage = new T[other.curCapacity];
            memcpy(storage, other.storage, curCapacity*sizeof(T));
        }

        void clear() override {
            // size == 0, and the capacity and dynamic array should
            // shrink back to its default size. There is a potential
            // for a memory leak here.
            delete[] storage;
            curCapacity = TEST_START_CAPACITY;
            storage = new T[TEST_START_ARRAY_SIZE];
            curSize = 0;
            frontIndex = 0;
            backIndex = 0;
        }

        T dequeue() override {
            //Calling removeFirst
            return removeFirst();
        }

        bool enqueue(T t) override {
            //Calling addLast
            return addLast(t);
        }

        bool isEmpty() const override {
            return size() == 0;
        }

        T &peek() override {
            //Getting the element at the start of the array
            return get(0);
        }

        bool addFirst(T t) override {
            //Check if the array is full
            if (isFull() == true)
                return false;
            else {
                //When it is not the first element, increase the front index (CCW)
                if (frontIndex != 0 || backIndex != 0 || curSize != 0)
                    frontIndex = (frontIndex - 1 + curCapacity) % curCapacity;
                storage[frontIndex] = t;
                curSize++;
                return true;
            }

        }

        bool addLast(T t) override {
            //Check if the array is full
            if (isFull() == true)
                return false;
            else {
                //When it is not the first element, increase the back index(CW)
                if (frontIndex != 0 || backIndex != 0 || curSize != 0)
                    backIndex = ((backIndex + 1) % curCapacity);
                storage[backIndex] = t;
                curSize++;
                return true;
            }

        }

        bool insert(int idx, T t) override {

            //Checking if the index is out of range
            if (idx < 0 || idx > curSize - 1 || isFull() == true)
                throw std::out_of_range("CircularArray<T>::insert(idx,value) : index out of range.");

            //Checking if this is the first element. If so, call addLast
            if (idx == 0 && frontIndex == 0 && backIndex == 0 && curSize == 0) {
                return addLast(t);
            }

            //Closer to the front
            if (idx < curSize / 2) {
                //Shifting the other elements towards the front
                for (int i = frontIndex; i < idx + frontIndex + 1; i++) {
                    storage[(i - 1 + curCapacity) % curCapacity] = storage[i % curCapacity];
                }
                frontIndex = (frontIndex - 1 + curCapacity) % curCapacity;


            }
            //Closer to the back or in the middle
            else {
                //Shifting the other elements towards the back
                for (int i = backIndex; i > backIndex - curSize + idx; i--) {
                    storage[(i + 1 + curCapacity) % curCapacity] = storage[(i + curCapacity) % curCapacity];
                }
                backIndex = (backIndex + 1) % curCapacity;
            }
            storage[(idx + frontIndex) % curCapacity] = t;
            curSize++;
            return true;
        }

        T &get(int idx) override {
            //Checking if the index is out of range
            if (idx >= 0 && idx <= curSize - 1)
                return storage[(idx + frontIndex) % curCapacity];
            else
                throw std::out_of_range("CircularArray<T>::get(idx) : index out of range.");

        }
        T remove(int idx) override {
            int removedItem;

            //Checking if the index is out of range
            if (idx >= 0 && idx <= curSize - 1)
                removedItem = storage[(idx + frontIndex) % curCapacity];
            else
                throw std::out_of_range("CircularArray<T>::remove(idx) : index out of range. ");

            //Closer to the front
            if (idx < curSize / 2) {

                if (idx != 0) {
                    //Shifting the other elements if the idx is not at the front position
                    for (int i = frontIndex; i < idx + frontIndex + 1; i++) {
                        storage[(i + 1) % curCapacity] = storage[i % curCapacity];
                    }
                }
                frontIndex = (frontIndex + 1) % curCapacity;

            //Closer to the back or in the middle
            } else {
                if (idx != curSize - 1) {
                    //Shifting the other elements if the idx is not the back position
                    for (int i = backIndex; i > backIndex - curSize + idx; i--) {
                        storage[(i - 1 + curCapacity) % curCapacity] = storage[i % curCapacity];
                    }
                }
                backIndex = (backIndex - 1 + curCapacity) % curCapacity;
            }

            curSize--;
            isShrinkable();
            return removedItem;
        }

        T removeFirst() override {
            //If the array is not empty, call remove(0)
            return isEmpty() ? false: remove(0);

        }

        T removeLast() override {
            //If the array is not empty, call remove(curSize - 1)
            return isEmpty() ?  false : remove(curSize - 1);
        }


        void set(int idx, T value) override {

            //Checking if the index is out of range
            if (idx >= 0 && idx <= curSize - 1)
                storage[(idx + frontIndex) % curCapacity] = value;
            else
                throw std::out_of_range("CircularArray<T>::set(idx,value) : index out of range. ");
        }

        int size() const override {
            return curSize;
        }


    };
}

#endif //C210_PROGRAM1_CIRCULARARRAY_H
