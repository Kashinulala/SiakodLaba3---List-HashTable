#pragma once
#include "Elem_list.h"

class list {

private:

	elem* head;
	int N;

public:

	list() {
		N = 0;
		head = nullptr;
	}

	~list() {
		elem* cur = head;
		while (cur->next != nullptr) {
			cur = cur->next;
		}
		cur = cur->prev;
		while (cur->prev != nullptr) {
			delete cur->next;
			cur = cur->prev;
		}
		delete cur;
	}

	//��������� ������� � ������;
	//0 - ������� ��������
	int add(int data, int count) {
		elem el(data, count);
		if (N == 0) {
			head = new elem(el);
			N++;
			return 0;
		}
		else {
			elem* cur = head;
			if (cur->data > el.data) {                  //���������� � ������ ������
				cur->prev = new elem(el);
				cur->prev->next = cur;
				head = cur->prev;
				N++;
				return 0;
			}

			if (cur->data == el.data) {
				cur->count += el.count;
				return 0;
			}

			//���������� �� 2-�� �� n-1;
			do {
				cur = cur->next;
				if (cur->data == el.data) {
					cur->count += el.count;
					return 0;
				}
				if (cur->data > el.data) {
					elem* prev = cur->prev;
					cur->prev = new elem(el);
					cur->prev->next = cur;
					cur->prev->prev = prev;
					prev = cur->prev;
					N++;
					return 0;
				}
			} while (cur->next != nullptr);

			//���������� � �����
			cur->next = new elem(el);
			cur->next->prev = cur;
			N++;
			return 0;
		}
	}

	//������� ������� �� ������;
	//0 - ������� ������
	//1 - ������� �� ������
	int erase(int data, int count) {
		if (N == 0) {
			return 1;
		}
		else {
			elem* cur = head;
			//�������� �������
			if (cur->data == data) {
				cur->count -= count;
				if (cur->count <= 0) {
					head = cur->next;
					head->prev = nullptr;
					delete cur;
				}
				return 0;
			}






		}
	}

};