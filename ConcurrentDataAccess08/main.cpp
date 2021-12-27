#include <iostream>
#include <vector>
#include <thread>

using namespace std;
using namespace std::chrono_literals;

void atomics() {
    std::atomic<int> i = 0;
    std::thread t1([&i]() {
        i += 3;
    });
    std::thread t2([&i]() {
        i += 3;
    });
    t1.join();
    t2.join();
    cout << "i: " << i << endl;
}

void dataAccessMode() {
    vector<double> daily_price = {100.3, 101.5, 99.2, 105.1, 101.93, 96.7, 97.6, 103.9, 105.8, 101.2};
    std::atomic<double> average = 0.0;
    std::atomic_flag still_busy = true; // atomic<bool>

    // Calculate average in a separate thread
    std::thread thread([&daily_price, &average, &still_busy]() {
        auto avg = average.load();
        // Passing a lambda to constructor will start the thread automatically
        for (auto p : daily_price) {
            std::this_thread::sleep_for(2ms);
            avg += p;
        }
        avg /= daily_price.size();
        average.store(avg);
        still_busy.clear(); // false
        this_thread::sleep_for(2s);
    });

    assert(thread.joinable());

    // main thread
    while (still_busy.test_and_set()) {
        cout << "..."; // progress bar
        std::this_thread::sleep_for(1ms);
    }
    cout << "Average value: " << average << endl;
    // Blocks execution until the thread finishes. You can only call join() once
    // You must call join or detach on every thread you create (or thread destructor will call std::terminate)
    thread.join(); // wait until the thread finishes
    cout << "Worker has finished working" << endl;
}

int main() {
    //atomics();
    dataAccessMode();
    return 0;
}
