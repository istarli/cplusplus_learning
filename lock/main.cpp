#include <iostream>
#include <vector>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <unistd.h>
using namespace std;

/* recursive_mutex */
class RecursiveLock{
public:
    RecursiveLock() : num_of_lock(0) {}

    void lock(){
        if(num_of_lock == 0 || tid != this_thread::get_id()){
            mt.lock();
            num_of_lock++;
            tid = this_thread::get_id();
        }
        else
            num_of_lock++;
    }

    void unlock(){
        if(tid == this_thread::get_id()){
            if(num_of_lock > 1)
                num_of_lock--;
            else{
                num_of_lock = 0;
                mt.unlock();
            }
        }
    }

private:
    mutex mt;
    thread::id tid;
    int num_of_lock;
};
RecursiveLock rcslock;

/*
    shared_mutex smt;
    for reader : shared_lock<shared_mutex> lkg(smt);
    for writer : unique_lock<shared_mutex> lkg(smt); // or lock_guard<>... 
*/
class ReadWriteLock {
public:
    void RL(){
        unique_lock<mutex> ulk(mt);
        cv.wait(ulk,[this]{
            return !writing;
        });
        reader_num++;
    }

    void RUL(){
        lock_guard<mutex> lkg(mt);
        if(reader_num > 0)
            reader_num--;
        cv.notify_one();        
    }

    void WL(){
        unique_lock<mutex> ulk(mt);
        cv.wait(ulk,[this]{
            return !writing && reader_num == 0;
        });
        writing = true;
    }

    void WUL(){
        lock_guard<mutex> lkg(mt);
        writing = false;
        cv.notify_one();
    }

private:
    bool writing;
    int reader_num;
    mutex mt;
    condition_variable cv;
};
ReadWriteLock rwlock;

void test_RecursiveLock()
{
    auto th1 = thread([]{
        lock_guard<RecursiveLock> lkg(rcslock);
        thread::id this_id = this_thread::get_id();
        cout << "thread " << this_id << " start" << endl;
        []{
            lock_guard<RecursiveLock> lkg(rcslock);
            cout << "son thread" << endl;
        }();
        sleep(2);
        cout << "thread " << this_id << " end" << endl;
    });

    auto th2 = thread([]{
        lock_guard<RecursiveLock> lkg(rcslock);
        thread::id this_id = this_thread::get_id();
        cout << "thread " << this_id << " start" << endl;
        sleep(3);
        cout << "thread " << this_id << " end" << endl;
    });

    th1.join();
    th2.join();   
}

void test_ReadWriteLock()
{
    auto new_reader = [](int x){
        rwlock.RL();
        cout << "reader" << endl;
        sleep(x);
        rwlock.RUL();
    };
    auto new_writer = [](int x){
        rwlock.WL();
        cout << "writer" << endl;
        sleep(x);
        rwlock.WUL();
    };
    
    thread th1 = thread([=]{
        new_writer(2);
    });
    thread th2 = thread([=]{
        new_reader(4);
    });
    thread th3 = thread([=]{
        new_writer(2);
    });
    thread th4 = thread([=]{
        new_writer(2);
    });
    thread th5 = thread([=]{
        sleep(5);
        new_reader(2);
    });

    vector<thread*> v = {&th1, &th2, &th3, &th4, &th5};
    for(auto th_ptr : v){
        th_ptr->join();
    }
}

int main(int argc, char* argv[])
{
    // test_RecursiveLock();
    test_ReadWriteLock();
    return 0;
}