#pragma once

struct elem {

	int data;
	int count;
	elem* next;
	elem* prev;

	elem() {
		data = 0;
		count = 0;
		next = prev = nullptr;
	}

	elem(int _data) {
		data = _data;
		count = 1;
		next = prev = nullptr;
	}

	elem(int _data, int _count) {
		data = _data;
		count = _count;
		next = prev = nullptr;
	}
};