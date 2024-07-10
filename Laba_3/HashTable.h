#pragma once
#include "List.h"

class hashTable {
	
private:

	list* arr;
	int N;
	int minN;
	int listN;
	int elemAmount;

public:

	hashTable(int _N) {
		if (_N >= 3) {
			N = _N;
		}
		else {
			N = 3;
		}
		minN = N;
		listN = 2 * N;
		elemAmount = 0;
		arr = new list[N];
	}

	hashTable(const hashTable& ht) {
		N = ht.minN;
		minN = ht.minN;
		listN = N * 2;
		elemAmount = 0;
		arr = new list[N];
		elem* cur;
		for (int i = 0; i < ht.N; i++) {
			cur = ht.arr[i].getHead();
			while (cur != nullptr) {
				add(cur->data, cur->count);
				cur = cur->next;
			}
		}
	}

	~hashTable() {
		delete[] arr;
	}

	int hashFunc(int data) const{
		return std::abs(data % N);
	}

	//n - номер листа
	list* getListAdr(int n) {
		if ((n >= 0) && (n <= N)) {
			return &arr[n];
		}
		return nullptr;
	}

	int add(int data, int count) {

		int addListNum = hashFunc(data);
		if (resize(addListNum) == 0) {
			addListNum = hashFunc(data);
		};
		int res = arr[addListNum].add(data, count);
		if (res == 0) {
			elemAmount++;
		}
		return res;

	}

	int del(int data, int count) {

		int delListNum = hashFunc(data);
		int res = arr[delListNum].erase(data, count);
		if (res == 0) {
			elemAmount--;
		}
		resize(delListNum);
		return res;

	}

	int resize(int addListNum) {
		bool up = false, down = false;

		if (elemAmount < (listN / 2)) {
			down = true;
		}
		if (arr[addListNum].getSize() == listN) {
			up = true;
		}

		if (up) {
			N = N * 2;
			listN = N * 2;
			list* prevArr = arr;
			list* newArr = new list[N];
			arr = newArr;
			elem* cur;
			int prevElemAmount = elemAmount;
			for (int i = 0; i < N / 2; i++) {
				cur = prevArr[i].getHead();
				while (cur != nullptr) {
					add(cur->data, cur->count);
					cur = cur->next;
				}
			}
			elemAmount = prevElemAmount;
			delete[] prevArr;
			return 0;
		}
		
		if (down) {
			if (N == minN) {
				return 1;
			}
			else {
				N = N / 2;
				listN = N * 2;
				list* prevArr = arr;
				list* newArr = new list[N];
				arr = newArr;
				elem* cur;
				for (int i = 0; i < N * 2; i++) {
					cur = prevArr[i].getHead();
					while (cur != nullptr) {
						add(cur->data, cur->count);
						cur = cur->next;
					}
				}
				delete[] prevArr;
				return 0;
			}
		}
		return 1;
	}

	int getPower() const {
		int res = 0;
		for (int i = 0; i < N; i++) {
			res += arr[i].getPower();
		}
		return res;
	}

	int subset(const hashTable& ht) const {
		elem* curLt;
		elem* cur;
		bool subset;
		int ListNum;
		for (int i = 0; i < ht.N; i++) {
			curLt = ht.arr[i].getHead();
			while (curLt != nullptr) {
				subset = false;
				ListNum = hashFunc(curLt->data);
				cur = arr[ListNum].getHead();
				while (cur != nullptr) {
					if ((cur->data == curLt->data) && (curLt->count <= cur->count)) {
						subset = true;
						break;
					}
					cur = cur->next;
				}
				if (!subset) {
					return -1;
				}
				curLt = curLt->next;
			}
		}
		return 0;
	}

	hashTable& operator=(const hashTable& ht) {
		if (&ht != this)
		{
			this->~hashTable();
			new (this) hashTable(ht);
		}
		return *this;
	}

	hashTable operator+(const elem& el) {

		int addListNum = hashFunc(el.data);
		if (resize(addListNum) == 0) {
			addListNum = hashFunc(el.data);
		};
		int res = arr[addListNum].add(el.data, el.count);
		if (res == 0) {
			elemAmount++;
		}
		return *this;
	}

	hashTable operator+(const list& b) {

		elem* cur = b.getHead();
		while (cur != nullptr) {
			int addListNum = hashFunc(cur->data);
			if (resize(addListNum) == 0) {
				addListNum = hashFunc(cur->data);
			};
			int res = arr[addListNum].add(cur->data, cur->count);
			if (res == 0) {
				elemAmount++;
			}
			cur = cur->next;
		}
		return *this;
	}

	hashTable operator+(const hashTable& b) {

		for (int i = 0; i < b.N; i++) {
			elem* cur = b.arr[i].getHead();
			while (cur != nullptr) {
				int addListNum = hashFunc(cur->data);
				if (resize(addListNum) == 0) {
					addListNum = hashFunc(cur->data);
				};
				int res = arr[addListNum].add(cur->data, cur->count);
				if (res == 0) {
					elemAmount++;
				}
				cur = cur->next;
			}
		}
		return *this;
	}

	hashTable operator-(const elem& el) {

		int delListNum = hashFunc(el.data);
		int res = arr[delListNum].erase(el.data, el.count);
		if (res == 0) {
			elemAmount--;
		}
		resize(delListNum);
		return *this;
	}

	hashTable operator-(const list& lt) {

		elem* cur = lt.getHead();
		while (cur != nullptr) {
			int delListNum = hashFunc(cur->data);
			int res = arr[delListNum].erase(cur->data, cur->count);
			if (res == 0) {
				elemAmount--;
			}
			resize(delListNum);
			cur = cur->next;
		}
		return *this;
	}

	hashTable operator-(const hashTable& ht) {

		for (int i = 0; i < ht.N; i++) {
			elem* cur = ht.arr[i].getHead();
			while (cur != nullptr) {
				int delListNum = hashFunc(cur->data);
				int res = arr[delListNum].erase(cur->data, cur->count);
				if (res == 0) {
					elemAmount--;
				}
				resize(delListNum);
				cur = cur->next;
			}
		}
		return *this;
	}

	hashTable operator*(const elem& el) {

		int ListNum = hashFunc(el.data);
		elem* cur = arr[ListNum].getHead();
		hashTable res = hashTable(3);
		while (cur != nullptr) {
			if (cur->data == el.data) {
				res.add(el.data, std::min(cur->count, el.count));
				return res;
			}
			cur = cur->next;
		}
		return res;
	}

	hashTable operator*(const list& lt) {

		elem* curLt = lt.getHead();
		elem* cur;
		hashTable res = hashTable(3);
		int ListNum;
		while (curLt != nullptr) {
			ListNum = hashFunc(curLt->data);
			cur = arr[ListNum].getHead();
			while (cur != nullptr) {
				if (cur->data == curLt->data) {
					res.add(curLt->data, std::min(curLt->count, cur->count));
					break;
				}
				cur = cur->next;
			}
			curLt = curLt->next;
		}
		return res;
	}

	hashTable operator*(const hashTable& ht) {

		elem* curLt;
		elem* cur;
		int ListNum;
		hashTable res = hashTable(3);
		for (int i = 0; i < ht.N; i++) {
			curLt = ht.arr[i].getHead();
			while (curLt != nullptr) {
				ListNum = hashFunc(curLt->data);
				cur = arr[ListNum].getHead();
				while (cur != nullptr) {
					if (cur->data == curLt->data) {
						res.add(curLt->data, std::min(curLt->count, cur->count));
						break;
					}
					cur = cur->next;
				}
				curLt = curLt->next;
			}
		}
		return res;
	}

	friend std::ostream& operator <<(std::ostream& os, const hashTable& ht) {
		
		for (int i = 0; i < ht.N; i++) {
			os << "[" << i + 1 << "] ";
			os << ht.arr[i];
		}

		return os << "";
	}
};