#pragma once
#include "TTable.h"



template <class TKey, class TValue>
class TArrayTable : public TTable<TKey, TValue> {
protected:
	TRecord <TKey, TValue> *arr;
	int maxSize;
	int curr;
public:
	TArrayTable(int _maxSize = 1000) {
		maxSize = _maxSize;
		arr = new TRecord<TKey, TValue>[maxSize];
		curr = 0;
	}
	~TArrayTable() { delete[] arr; }
	virtual bool isFull() const { return dataCount == maxSize; }
	virtual TRecord<TKey, TValue> getCurr() { return arr[curr]; }
	virtual void Reset() { curr = 0; }
	virtual bool isEnd() { return curr == dataCount; }
	virtual void goNext() { curr++; }
};