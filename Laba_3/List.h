#pragma once
#include "Elem_list.h"
#include <iostream>
#include <algorithm>

class list {

private:

	elem* head;
	int N;

public:

	list() {
		N = 0;
		head = nullptr;
	}

	list(const list &lt) {
		N = 0;
		if (lt.N == 0) {
			head = nullptr;
			return;
		}
		elem* cur = lt.head;
		head = new elem(cur->data, cur->count);
		N++;
		if (lt.N == 1) {
			return;
		}
		cur = cur->next;
		while (cur != nullptr) {
			add(cur->data, cur->count);
			cur = cur->next;
		}
	}

	~list() {
		elem* cur = head;
		if (head != nullptr) {
			while (cur->next != nullptr) {
				cur = cur->next;
			}
			if (cur->prev != nullptr) {
				cur = cur->prev;
				while (cur->prev != nullptr) {
					delete cur->next;
					cur = cur->prev;
				}
				delete cur;
			}
			else {
				delete cur;
			}
		}
	}

	//Возвращает мощность мн-ва;
	int getPower() {
		int power = 0;
		if (N == 0) {
			return power;
		}
		elem* cur = head;
		while (cur != nullptr) {
			power += cur->count;
			cur = cur->next;
		}
		return power;
	}

	//Äîáàâëÿåò ýëåìåíò â ñïèñîê;
	//0 - ýëåìåíò äîáàâëåí
	int add(int data, int count) {
		if (N == 0) {
			head = new elem(data, count);
			N++;
			return 0;
		}
		else {
			elem* cur = head;
			if (cur->data > data) {                  //Äîáàâëåíèå â íà÷àëî ñïèñêà
				cur->prev = new elem(data, count);
				cur->prev->next = cur;
				head = cur->prev;
				N++;
				return 0;
			}

			if (cur->data == data) {
				cur->count += count;
				return 0;
			}

			//Äîáàâëåíèå ñî 2-ãî äî n-1;
			while (cur->next != nullptr) {
				cur = cur->next;
				if (cur->data == data) {
					cur->count += count;
					return 0;
				}
				if (cur->data > data) {
					elem* newEl = new elem(data, count);
					newEl->next = cur;
					newEl->prev = cur->prev;
					cur->prev->next = newEl;
					cur->prev = newEl;
					N++;
					return 0;
				}
			} 

			//Äîáàâëåíèå â êîíåö
			cur->next = new elem(data, count);
			cur->next->prev = cur;
			N++;
			return 0;
		}
	}

	//Óäàëÿåò ýëåìåíò èç ñïèñêà;
	//0 - ýëåìåíò óäàëåí
	//1 - ýëåìåíò íå íàéäåí
	int erase(int data, int count) {
		if (N == 0) {
			return 1;
		}
		else {
			elem* cur = head;
			//Óäàëåíèå ïåðâîãî
			if (cur->data == data) {
				cur->count -= count;
				if (cur->count <= 0) {
					if (N != 1) {
						head = cur->next;
						head->prev = nullptr;
						N--;
						delete cur;
					}
					else {
						head = nullptr;
						N--;
						delete cur;
					}
				}
				return 0;
			}

			//Óäàëåíèå ñî 2-ãî äî n-1
			while (cur->next != nullptr) {
				if (cur->data == data) {
					cur->count -= count;
					if (cur->count <= 0) {
						cur->prev->next = cur->next;
						cur->next->prev = cur->prev;
						delete cur;
					}
					N--;
					return 0;
				}
				cur = cur->next;
			}

			if (cur->data == data) {
				cur->count -= count;
				if (cur->count <= 0) {
					cur->prev->next = nullptr;
					delete cur;
					N--;
				}
				return 0;
			}
			return 1;
		}
	}



	void print() {
		elem* cur = head;
		if (N != 0) {
			while (cur != nullptr) {
				std::cout << "(" << cur->data << ";" << cur->count << ")";
				cur = cur->next;
			}
		}
		else {
			std::cout << "List empty!";
		}
	}

	int subset(list b) {
		elem* curA = head;
		elem* curB = b.head;
		while (curA != nullptr) {
			if (curA->data == curB->data) {
				break;
			}
			curA = curA->next;
		}
		while ((curB != nullptr) && (curA != nullptr)) {
			if ((curA->data == curB->data) && (curA->count >= curB->count)) {
				curA = curA->next;
				curB = curB->next;
			}
			else {
				return 1;
			}
		}
		if (curB == nullptr) {
			return 0;
		}
		else {
			return 1;
		}
	}

	list& operator=(const list& lt) {
		if (&lt != this)
		{
			this->~list();
			new (this) list(lt);
		}
		return *this;
	}

	//Объединение
	list operator+(const list& b) {
		if ((this->head == nullptr) && (b.head == nullptr)) {
			return list();
		}
		if (this->head == nullptr) {
			return list(b);
		}
		if (b.head == nullptr) {
			return list(*this);
		}
		list result = list(*this);

		elem* curRes = result.head;
		elem* curB = b.head;

		if (curRes->data > curB->data) {
			curRes->prev = new elem(curB->data, curB->count);
			curRes->prev->next = curRes;
			result.head = curRes->prev;
			curB = curB->next;
			result.N++;
			if (curB == nullptr) {
				return result;
			}
		}

		elem* prev = curRes;

		if (curRes->data == curB->data) {
			curRes->count = std::max(curRes->count, curB->count);
			curRes = curRes->next;
			curB = curB->next;
			if (curB == nullptr) {
				return result;
			}
		}

		while (curRes != nullptr)
		{
			while (curRes->data > curB->data) {
				elem* newEl = new elem(curB->data, curB->count);
				newEl->next = curRes;
				newEl->prev = curRes->prev;
				curRes->prev->next = newEl;
				curRes->prev = newEl;
				result.N++;
				curB = curB->next;
				if (curB == nullptr) {
					return result;
				}
			}
			if (curRes->data == curB->data) {
				curRes->count = std::max(curRes->count, curB->count);
				curB = curB->next;
				if (curB == nullptr) {
					return result;
				}
			}
			prev = curRes;
			curRes = curRes->next;
		}
		curRes = prev;
		
		while (curB != nullptr) {
			curRes->next = new elem(curB->data, curB->count);
			curRes->next->prev = curRes;
			result.N++;
			curRes = curRes->next;
			curB = curB->next;
		}
		return result;
	}

	//Пересечение мн-в
	list operator*(const list& b) {

		if ((this->head == nullptr) || (b.head == nullptr)) {
			return list();
		}
		list result = list();

		elem* curA = this->head;
		elem* curB = b.head;

		while (curA != nullptr) {
			while (curA->data > curB->data) {
				curB = curB->next;
				if (curB == nullptr) {
					return result;
				}
			}
			if (curA->data == curB->data) {
				result.add(curA->data, std::min(curA->count, curB->count));
			}
			curA = curA->next;
		}
		return result;
	}

	//разность мн-в
	list operator-(const list& b) {
		if (this->head == nullptr) {
			return list();
		}
		if (b.head == nullptr) {
			return list(*this);
		}
		list result = list(*this);
		
		elem* curA = this->head;
		elem* curB = b.head;

		while (curA != nullptr) {
			while (curA->data > curB->data) {
				curB = curB->next;
				if (curB == nullptr) {
					return result;
				}
			}
			if (curA->data == curB->data) {
				result.erase(curB->data, curB->count);
			}
			curA = curA->next;
		}
		return result;
	}

	friend std::ostream& operator <<(std::ostream& os, const list& lt) {
		elem* cur = lt.head;
		if (lt.N != 0) {
			while (cur != nullptr) {
				os << "(" << cur->data << ";" << cur->count << ")";
				cur = cur->next;
			}
		}
		else {
			os << "List empty!";
		}
		return os << '\n';
	}
};