// STUDENT ORGANIC WAGYU CODE
// Author: Maron Vincent Ejanda
// San Diego State University
// CS210/CS496: Data Structures
//
// File: CircularArray.h
// Defines the CircularArray collection class.

#define VERSION_CIRARRAY 0.1

// STUDENT CODE
#ifndef PROG1_CIRCULARARRAY_H
#define PROG1_CIRCULARARRAY_H

#define DEFAULT_CAPACITY 10

#include "Queue.h"
#include "List.h"

namespace sdsu 
{
    template<typename T>
    class CircularArray : public sdsu::Queue<T>, public sdsu::List<T> 
    {

    private:
        // Size represents how many T items the structure holds
        int curSize;

        // Capacity represents how many T items the structure CAN hold
        int curCapacity;

        // todo: head and tail counters for the circular nature
        int head {};
        int tail {};

        // the array on the heap
        T *storage;

        //Boolean to check if the size is full

        bool changeCap (bool status)
        {
            T *temp = storage;
            int newCapacity;

            if(status)
                newCapacity = curCapacity << 1;
            else 
                newCapacity = curCapacity >> 1;

            storage = new T[newCapacity];
            for(int x = 0; x < curSize; x++)
                storage[x] = temp[(x + head) % curCapacity];

            tail = curSize -1;
            head = 0;
            curCapacity = newCapacity;
            delete[] temp;
            return false;

        }

        //------------
        bool full()
        {
            if(curSize == curCapacity)
                return changeCap(1);
            else
                return false;
        }
        //------------
        void half()
        {
            if(curSize == (curCapacity / 2))
                changeCap(0);
        
        }
    public:

        // This is the default class constructor. It sets the current size to 0
        CircularArray() : curSize(0)
        {
        // todo: initialize a default capacity storage array on the heap
        curCapacity = DEFAULT_CAPACITY;
        storage = new T[DEFAULT_CAPACITY];
        head = 0;
        tail =0;

        }

        // DO THIS ---------------------------------------------------------------------
        // The copy constructor!
        CircularArray(const CircularArray<T> &other) : CircularArray() 
        {
            std::cout << "Copying . . .";

            curCapacity = other.curCapacity;
            curSize = other.curSize;
            storage = new T[other.curCapacity];

            head = other.head;
            tail = other.tail;
            //For loop to traverse the circulararray and copy
            for(int x = head; x < head + curSize; x++)
                storage[ x % curCapacity] = other.storage[x % curCapacity];
        }


        ~CircularArray() override 
        {
            delete[] storage;
        }

        // DO THIS ---------------------------------------------------------------------
        void clear() override 
        {
            // size == 0, and the capacity and dynamic array should
            // shrink back to its default size. There is a potential
            // for a memory leak here.

            //deleteing the current storage to reset and to override
            delete [] storage;
            curCapacity = DEFAULT_CAPACITY;
            storage = new T[curCapacity];

            //Variables are now reset
            curSize =0;
            head = 0;
            tail = 0;

        }


        // DO THISS --------------------------------------------------------------------
        T dequeue() override 
        {
          
            return removeFirst();
        }

        // DO THIS ---------------------------------------------------------------------
        bool enqueue(T t) override 
        {
            
                
            return addLast(t);
        }

        // DO THIS ---------------------------------------------------------------------
        bool isEmpty() const override 
        {
            return size() == 0;
        }

        // DO THIS ---------------------------------------------------------------------
        T& peek() override 
        {
            // todo: this is here to make it compile, but it is wrong.
            return get(0);
        }

        // DO THIS ---------------------------------------------------------------------
        bool addFirst(T t) override 
        {
            if (full() == false)
            {
                if (tail != 0 || head != 0 || curSize !=0)
                    head = ((head  - 1 + curCapacity) % curCapacity);
                storage[head] = t;
                curSize++;
                return true;
            }
            else
                return false;


        }

        // DO THIS ---------------------------------------------------------------------
        bool addLast(T t) override 
        {
            if(full () == false) {
                if (head != 0 || tail != 0 || curSize != 0)
                    tail = ((tail + 1) % curCapacity);
                storage[tail] = t;
                curSize++;
                return true;
            }
             return false;
        }

        // DO THIS ---------------------------------------------------------------------
        T& get(int idx) override 
        {
            // todo: we need idx range checking. In C++, this is dangerous.
            if(idx < 0 || idx > curSize - 1)
                std::out_of_range("CircularArray<T>::get(idx) : index out of range.");
            return storage[(idx + head) % curCapacity];
        }

        // DO THIS ---------------------------------------------------------------------
        bool insert(int idx, T t) override 
        {
            // if you figure out if you are closer to the head or tail, you can
            // minimize the amount of array manipulation you need to perform.

            

            return true;
        }

        // DO THIS ---------------------------------------------------------------------
        T remove(int i) override
        {
            // Figure out if the target index is closer to the front or back
            // and then shuffle from that index (tail or head).
            if(i < 0 || i > curSize - 1)
                throw std::out_of_range("CircularArray<T>::remove(i) : index out of range.");
            return false;

        }

        // DO THIS ---------------------------------------------------------------------
        T removeFirst() override 
        {
            // If you wrote remove correctly, this can be a single line.
            // you *might* want to clean up any exception handling though . . . .
            if(isEmpty() == false) {
                int item = storage[head];
                head = ((head + 1) % curCapacity);
                curSize--;
                return item;
            }
            return false;
        }

        // DO THIS ---------------------------------------------------------------------
        T removeLast() override 
        {
            // If you wrote remove correctly, this can be a single line.
            // you *might* want to clean up any exception handling though . . . .

            return false;
        }

        // DO THIS ---------------------------------------------------------------------
        void set(int idx, T value) override 
        {
            if(idx < 0 || idx > curSize - 1)
                 std::out_of_range("CircularArray<T>::set(idx,value) : index out of range.");
            storage[(idx + head) % curCapacity] = value;
        }

        // DO THIS ---------------------------------------------------------------------
        int size() const override 
        {
            return curSize;
        }
    };
}

#endif //PROG1_CIRCULARARRAY_H
