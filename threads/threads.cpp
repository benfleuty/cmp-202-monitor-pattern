// Race conditions example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <iostream>
#include <iomanip>
#include <thread>
#include <vector>
#include <chrono>
#include <mutex>
#include <string>

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
bool progress_ready = false;

#define UNIQUE_MUTEX unique_lock<mutex>
#define PRINT_TESTT cout << "test" << endl
#define PRINT_TEST(x) cout << "test " << (x) << endl
#define ENDLESSLY for(;;)

void bill_add_mutex_unique() {
	for (auto i = 0; i < 1000000; ++i)
	{
		// deliberate slow down
		//std::this_thread::sleep_for(milliseconds(400));
		// critical
		UNIQUE_MUTEX lock(bill_mutex);
		bill.add(17, 29);
		progress_ready = true;
		progress_cv.notify_one();
	}
}

void print_total()
{
	UNIQUE_MUTEX lock(bill_mutex);

	ENDLESSLY
	{
		while (!progress_ready)
			progress_cv.wait(lock);

		progress_ready = false;
		const auto progress = bill.total() / 172900000.0 * 100.0;
		cout << "Adding to Bill's total. Progress: " << progress << "%     \r" << std::flush;
		if (progress == 100.0) break;
	}
}

void unique_lock_mutex() {
	const uint8_t thread_count = 10;

	std::vector<thread> threads;

	for (auto i = 0; i < thread_count; ++i)
		threads.emplace_back(bill_add_mutex_unique);

	for (auto i = 0; i < thread_count; ++i)
		threads[i].join();

	// clear line
	cout << "\33[2K" << std::flush;
	cout << "\rBill's total is now GBP " << std::fixed << std::setprecision(2) << bill.total() << endl;
}

int main(int argc, char* argv[])
{
	thread t1(unique_lock_mutex);
	thread t2(print_total);
	//print_total();
	t1.join();
	PRINT_TESTT;
	t2.join();
	//t2.detach();
	return 0;
}