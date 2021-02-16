// Simple threading example
// Adam Sampson <a.sampson@abertay.ac.uk>

#include <chrono>
#include <iostream>
#include <thread>

// Import things we need from the standard library
using std::chrono::seconds;
using std::cout;
using std::endl;
using std::ofstream;
using std::this_thread::sleep_for;
using std::thread;

void myThreadFunc()
{
	sleep_for(seconds(3));
	cout << "I am myThreadFunc\n";
}

int main(int argc, char* argv[])
{
	// At the moment our program is only running one thread (the initial one the operating system gave us).

	thread myThread(myThreadFunc);

	// Now our program is running two threads in parallel (the initial one, and myThread).

	cout << "I am main\n";

	// Wait for myThread to finish.
	myThread.join();

	// Now we just have the initial thread. So it's safe to exit.

	cout << "All done\n";
	sleep_for(seconds(3));

	return 0;
}