#pragma once
#include "TTable.h"



template <class TKey, class TValue>
class TArrayTable :public TTable<TKey, TValue> {
protected:
	TRecord <TKey, TValue> *arr;
	int maxsize;
	int curr;
public:
	TArrayTable(int _maxsize = 100) {
		maxsize = _maxsize;
		arr = new TRecord<TKey, TValue>[maxsize];
		curr = 0;
	}
	~TArrayTable() { delete[] arr; }
	virtual void Reset() { curr = 0; }
	virtual bool isEnd() { return curr == datacount; }
	virtual void goNext() { curr++; }
};