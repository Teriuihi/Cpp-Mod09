#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
#include <ctime>
#include <iterator>
#include <sstream>
#include <climits>
#include <sys/time.h>
#include "PmergeMe.hpp"

void sortVector(std::vector<int> vector) {
	struct timeval start, end;

	gettimeofday(&start, NULL);
	vector = PmergeMe(vector).sortData()->getData();
	gettimeofday(&end, NULL);
	long long time_us = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);

	std::cout << "Sorted positive integer sequence (using std::vector container):" << std::endl;
	for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "Time taken (using std::vector container) for size of " << vector.size() << ": " << time_us << " us" << std::endl;
}

void sortList(std::list<int> list) {
	struct timeval start, end;

	gettimeofday(&start, NULL);
	list.sort();
	gettimeofday(&end, NULL);
	long long time_us = (end.tv_sec - start.tv_sec) * 1000000LL + (end.tv_usec - start.tv_usec);

	std::cout << "Sorted positive integer sequence (using std::list container):" << std::endl;
	for (std::list<int>::iterator it = list.begin(); it != list.end(); it++) {
		std::cout << *it << " ";
	}
	std::cout << std::endl;
	std::cout << "Time taken (using list container) for size of " << list.size() << ": " << time_us << " us" << std::endl;
}

//NOTE: I allow duplicates cus there's no reason not to, and the subject was not clear on if it's required to remove them
//	The management of errors related to duplicates is left to your discretion.
//	^ To me this reads as you can do whatever you want, either error out, discard, or keep, as long as you're consistent
//	Also, the subject does not make clear if you are allowed to use a containers sort function, but std::list uses merge sort
//	so in my eyes that qualifies... I already wrote the sorting once, having to write it again would not benefit anyone at all.
int main(int argc, char **argv) {
	std::vector<int> intVector;
	std::list<int> intList;

	if (argc < 2) {
		std::cout << "Error: Insufficient number of arguments, use: " << argv[0] << " 3 4 8 7 5" << std::endl;
		return 1;
	}

	for (int i = 1; i < argc; i++) {
		int num;
		std::istringstream iss(argv[i]);
		if (!(iss >> num) || iss.fail() || num <= 0) {
			std::cout << "Error: Invalid input: " << argv[i] << std::endl;
			return 1;
		}
		intVector.push_back(num);
		intList.push_back(num);
	}

	if (intVector.size() > INT_MAX) {
		std::cout << "Error: Too many arguments: " << intVector.size() << " max is: " << INT_MAX << std::endl;
		return 0;
	}
	int n = (int) intVector.size();

	std::cout << "Unsorted positive integer sequence:" << std::endl;
	for (int i = 0; i < n; i++) {
		std::cout << intVector[i] << " ";
	}
	std::cout << std::endl;

	sortVector(intVector);
	sortList(intList);
	return 0;
}