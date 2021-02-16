#include <string>

#include "account.h"

using std::string;

void Account::add(const unsigned int pounds, const unsigned int pence)
{
	pounds_ += pounds;
	pence_ += pence;

	// Ensure pence_ stays in the range 0-99.
	if (pence_ >= 100) {
		pounds_++;
		pence_ -= 100;
	}
}

double Account::total() const
{
	double total = pounds_;
	total += static_cast<double>(pence_) / 100;
	return total;
}