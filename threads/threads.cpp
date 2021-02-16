// Race conditions example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>

#include "account.h"

// Import things we need from the standard library
using std::cout;
using std::endl;

using std::vector;

using std::thread;
using std::mutex;
using std::unique_lock;

using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::steady_clock;
using std::condition_variable;

Account bill;
mutex bill_mutex;

condition_variable progress_cv;

#define UNIQUE_MUTEX unique_lock<mutex>
#define PRINT_TEST(x) cout << "test " << (x) << endl
#define ENDLESSLY for(;;)

void bill_add_mutex_unique() {
	for (auto i = 0; i < 1000000; ++i)
	{
		// deliberate slow down
		std::this_thread::sleep_for(milliseconds(400));
		// critical
		UNIQUE_MUTEX lock(bill_mutex);
		bill.add(17, 29);
		progress_cv.notify_one();
	}
}

void print_total()
{
	UNIQUE_MUTEX lock(bill_mutex);

	ENDLESSLY
	{
		cout << "Bill's Total: GBP" << bill.total() << endl;
		progress_cv.wait(lock);
	}
}

void unique_lock_mutex() {
	cout << "Starting unique_lock_mutex()" << endl;
	const uint8_t thread_count = 10;

	std::vector<thread> threads;

	for (auto i = 0; i < thread_count; ++i)
		threads.emplace_back(bill_add_mutex_unique);

	for (auto i = 0; i < thread_count; ++i)
		threads[i].join();

	cout << "Finished unique_lock_mutex()" << endl;
}

int main(int argc, char* argv[])
{
	unique_lock_mutex();
	return 0;
}