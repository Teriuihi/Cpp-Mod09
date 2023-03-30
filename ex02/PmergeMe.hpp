#ifndef P_MERGE_ME_HPP
#define P_MERGE_ME_HPP

#include <vector>

class PmergeMe {
public:
	PmergeMe(const std::vector<int>& v);
	PmergeMe(const PmergeMe& other);
	PmergeMe& operator=(const PmergeMe& other);
	~PmergeMe();
	PmergeMe* sortData();

	const std::vector<int> &getData() const;

private:

	void merge(std::vector<int>& v, int low, int mid, int high);
	void merge_insert_sort(std::vector<int>& v, int low, int high);
	std::vector<int> data;
};

#endif
