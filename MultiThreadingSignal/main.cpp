#include <iostream>
#include <thread>
#include <future>
#include <chrono>

using namespace std;

template<typename E>
class blocking_queue {
public:
    void push(E e) {
        cout << "push " << e << endl;
    }

    void pop() {
        cout << "pop " << endl;
    }
};

int main() {
    blocking_queue<int> qu;
    thread t1(&blocking_queue<int>::push, &qu, 3); // function_ptr, associated object address
    thread t2(&blocking_queue<int>::pop, &qu);

    t1.join();
    t2.join();

    /* 16. Condition Variables */
//    condition_variable condition;
//    mutex mtx;
//    bool ready = false;
//
//    thread t1([&]() {
//        this_thread::sleep_for(chrono::milliseconds(2000));
//        cout << "t1 acquiring lock" << endl;
//        unique_lock<mutex> locker(mtx);
//        cout << "t1 acquired lock" << endl;
//        ready = true;
//        locker.unlock();
//        cout << "t1 released lock; notifying" << endl;
//        condition.notify_one(); // 2. release lock. Let waiting thread to acquire the released lock
//    });
//
//    cout << "main thread acquiring lock" << endl;
//    unique_lock<mutex> locker(mtx);
//    cout << "main thread acquired lock; waiting" << endl;
//    // 1. condition.wait releases the lock. main thread sleep. Wait won't return until t1 calls notify_one.
//    condition.wait(locker, [&]() { return ready; });
//    // 3. notify_one => wait return. get the lock back..
//    cout << "main thread finishes waiting" << endl;
//
//    cout << "ready " << ready << endl;
//    t1.join();
    return 0;
}
