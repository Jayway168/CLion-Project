//
// Created by Jayway Tung on 2022/10/01
//
#include <iostream>
#include <thread>
#include <vector>
#include <list>
#include <mutex>
#include <algorithm>

using namespace std;

void hello(unsigned i) {
    cout << "i = " << i << endl;
}

void helolo() {
    cout << "do_something_in_current_thread()" << endl;
}

struct func {
    int& i;
    explicit func(int& i_) : i(i_) {}
    void operator() () {
        for (unsigned j=0; j<100; ++j) {
            hello(++i);
        }
    }
};

void oops() {
    int local_state = 0;
    func my_func(local_state);
    std::thread my_thread(my_func);
    if (my_thread.joinable()) {
        my_thread.detach();
    }
    //my_thread.detach();
    //my_thread.join();
}

class thread_guard {
    std::thread& t;
  public:
    explicit thread_guard(std::thread& t_): t(t_) {}
    ~thread_guard() {
        if (t.joinable()) {
            t.join();
        }
    }
    thread_guard(thread_guard const&) = delete;
    thread_guard& operator=(thread_guard const&) = delete;
};

void f() {
    int local_state = 0;
    func my_func(local_state);
    std::thread t(my_func);
    thread_guard g(t);
    helolo();
}

void ff(int i, std::string const& s) {
    cout << "i = " << i << " string = " << s;
}

void oopss(int value) {
    char buffer[1024];
    sprintf(buffer, "%i", value);
    std::thread t(ff, 3, std::string(buffer));
    t.join();
    //t.detach();
}

class X {
  public:
    /*static*/ void do_lengthy_work(int);
};


void X::do_lengthy_work(int num) {
    cout << "do_lengthy_work int = " << num << endl;
}

class scoped_thread {
    std::thread t;
  public:
    explicit scoped_thread(std::thread t_): t(std::move(t_)) {
        if(!t.joinable()) {
            throw std::logic_error("No thread");
        }
    }
    ~scoped_thread() {
        t.join();
    }
    scoped_thread(scoped_thread const&) = delete;
    scoped_thread& operator=(scoped_thread const&) = delete;
};

void do_something_in_current_thread() {
    cout << "do_something_in_current_thread()" << endl;
}

void f1() {
    std::vector<std::thread> threads;
    for (unsigned i =0; i < 20; ++i) {
        threads.emplace_back(hello, i);
    }

    for (auto& entry : threads) {
        entry.join();
    }
}

void foo() {
    std::thread::id tid = std::this_thread::get_id();
    cout << "foo thread id : " << tid << "\n";
}

int main() {

    //f1();

    unsigned numcpu = std::thread::hardware_concurrency();
    cout << "Number of Threads = " << numcpu << endl;

    //unsigned long thread_id = std::thread::id;
    std::thread::id my_id = std::this_thread::get_id();

    cout << "thread::id = " << my_id << endl;

    std::thread t1(foo);

    std::thread::id tid = t1.get_id();
    std::thread::id mainTid = std::this_thread::get_id();

    if (t1.joinable())
        t1.join();

    cout << "t1 tid: " << tid << endl;
    cout << "main tid: " << mainTid << endl;

    return 0;
}
