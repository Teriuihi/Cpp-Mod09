#include "PmergeMe.hpp"
#include <algorithm>

void PmergeMe::merge(std::vector<int> &vector, int low, int mid, int high) {
	int left_index, right_index, temp_index;
	std::vector<int> temp(vector.size());

	left_index = low;
	temp_index = low;
	right_index = mid + 1;

	while (left_index <= mid && right_index <= high) {
		if (vector[left_index] < vector[right_index]) {
			temp[temp_index] = vector[left_index];
			temp_index++;
			left_index++;
		} else {
			temp[temp_index] = vector[right_index];
			temp_index++;
			right_index++;
		}
	}

	while (left_index <= mid) {
		temp[temp_index] = vector[left_index];
		temp_index++;
		left_index++;
	}

	while (right_index <= high) {
		temp[temp_index] = vector[right_index];
		temp_index++;
		right_index++;
	}

	for (int i = low; i < temp_index; i++) {
		vector[i] = temp[i];
	}
}


void PmergeMe::merge_insert_sort(std::vector<int> &v, int low, int high) {
	if (low >= high)
		return;
	if (high - low <= 10) {
		sort(v.begin() + low, v.begin() + high + 1);
	} else {
		int mid = (low + high) / 2;
		merge_insert_sort(v, low, mid);
		merge_insert_sort(v, mid + 1, high);
		merge(v, low, mid, high);
	}
}

PmergeMe* PmergeMe::sortData() {
	int n = (int) data.size();
	merge_insert_sort(data, 0, n - 1);
	return this;
}

const std::vector<int> &PmergeMe::getData() const {
	return data;
}

PmergeMe::PmergeMe(const std::vector<int> &vector): data(vector) {}

PmergeMe::PmergeMe(const PmergeMe& other) {
	*this = other;
}

PmergeMe& PmergeMe::operator=(const PmergeMe& other) {
	if (this != &other) {
		data = other.data;
	}
	return *this;
}

PmergeMe::~PmergeMe() {}
