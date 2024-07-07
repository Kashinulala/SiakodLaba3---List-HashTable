#pragma once
#include "Elem_list.h"
#include <iostream>

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
		N = lt.N;
		head = nullptr;
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

	//Добавляет элемент в список;
	//0 - элемент добавлен
	int add(int data, int count) {
		if (N == 0) {
			head = new elem(data, count);
			N++;
			return 0;
		}
		else {
			elem* cur = head;
			if (cur->data > data) {                  //Добавление в начало списка
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

			//Добавление со 2-го до n-1;
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

			//Добавление в конец
			cur->next = new elem(data, count);
			cur->next->prev = cur;
			N++;
			return 0;
		}
	}

	//Удаляет элемент из списка;
	//0 - элемент удален
	//1 - элемент не найден
	int erase(int data, int count) {
		if (N == 0) {
			return 1;
		}
		else {
			elem* cur = head;
			//Удаление первого
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

			//Удаление со 2-го до n-1
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
		}
	}



	void listPrint() {
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

};