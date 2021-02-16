#ifndef ACCOUNT_H
#define ACCOUNT_H

/** An Account keeps track of a non-negative amount of money, expressed in
pounds and pence -- e.g. the total of a restaurant bill. */
class Account
{
public:
	/** Add an amount to the total. */
	void add(unsigned int pounds, unsigned int pence);

	/** Retrieve the total, formatted as a string (e.g. "GBP 4.95"). */
	//std::string total();

	/** Retrieve the total as double */
	double total() const;

private:
	unsigned int pounds_ = 0;
	unsigned int pence_ = 0;
};

#endif