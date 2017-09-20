#ifndef H_QUEUE
#define H_QUEUE

#define MAX_QUEUE_SIZE 10

template<typename T>
class Queue {
private:
    byte currentIdx;
    byte currentCount = 0;
    byte firstIdx = 0;
    T data[MAX_QUEUE_SIZE];
public:
    void push(T item) {
        if (currentCount < MAX_QUEUE_SIZE) {
            data[currentIdx] = item;
            currentIdx++;
            if (currentIdx >= MAX_QUEUE_SIZE) {
                currentIdx = 0;
            }
            currentCount++;
        }
    }

    bool has() {
        return currentCount != 0;
    }

    T pop() {
        T ret = data[firstIdx];
        firstIdx++;
        if (firstIdx >= 100) {
            firstIdx = 0;
        }
        currentCount--;
        return ret;
    }
};

#endif