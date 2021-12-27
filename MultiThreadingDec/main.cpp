#include <iostream>
#include <thread>
#include <mutex>
#include <cmath>
#include <iomanip>
#include <future>
#include <exception>
#include <chrono>

using namespace std;

class App { // Callable object, overload () in the class
public:
    void operator()() {
        for (int i = 0; i < 1E6; i++) {
            lock_guard<mutex> guard(mtx);
            ++count;
        }
    }
    int getCount() {
        return count;
    }
private:
    mutex mtx;
    int count = 0;
};

double calculate_pi(int terms) {
    double sum = 0.0;
    if (terms < 1) {
        throw runtime_error("Terms cannot be less than 1");
    }
    for (int i = 0; i < terms; i++) {
        int sign = pow(-1, i);
        double term = 1.0 / (i * 2 + 1);
        sum += sign * term;
    }
    return sum * 4;
}

int main() {
    /* 14. Package task */
    packaged_task<double(int)> task1(calculate_pi); // task1 returns the value and stores in promise.
    future<double> future = task1.get_future();

    thread pkgThread(move(task1), 1E6);

    cout << setprecision(15) << future.get() << endl;
    pkgThread.join();

    /* 12. Future and Promise */
//    // producer
//    promise<double> promise;
//    auto do_calculation = [&](int terms) {
//        try {
//            auto result = calculate_pi(terms);
//            promise.set_value(result);
//        } catch (...) {
//            promise.set_exception(current_exception());
//        }
//    };
//    thread piThread(do_calculation, 1E4);
//    // consumer
//    future<double> future = promise.get_future();
//    try {
//        cout << setprecision(15) << future.get() << endl;
//    } catch (const std::exception& e) {
//        cout << e.what() << "\n";
//    }
//
//    piThread.join();

    /* Callable object */
//    App app;  //app();
//    thread t1(ref(app));
//    thread t2(ref(app));
//    t1.join();
//    t2.join();
//    cout << "count " << app.getCount();
    return 0;
}

void addCount(int& count, mutex& mtx) {
    //thread t1(addCount, ref(count), ref(mtx)); // reference_wrapper
    //thread t2(addCount, ref(count), ref(mtx));
    for (int i = 0; i < 1E6; i++) {
        unique_lock<mutex> guard(mtx);
        ++count;
    }
}
