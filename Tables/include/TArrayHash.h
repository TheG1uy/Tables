#pragma once
#include "THashTable.h"

template <class TKey, class TValue>
class TArrayHash : public THashTable <TKey, TValue> {
private :
	int maxSize;
	int step;
	int curr;
	TRecord<TKey, TValue> *arr;

public:
	TArrayHash(int _maxSize = 1000, int _step = 17) {
		maxSize = _maxSize;
		step = _step;
		arr = new TRecord<TKey, TValue>[maxSize];
		for (int i = 0; i < maxSize; i++)
			arr[i].key = "";
	}
	~TArrayHash() { delete[] arr; }

	bool isFull() const { return dataCount == maxSize; }

	bool Find(TKey _key) {
		curr = HashFunc(_key) % maxSize;
		int freepos = -1;

		for (int i = 0; i < maxSize; i++) {
			Eff++;

			if (arr[curr].key == "") 
				if (freepos == -1)  return false;
				
				else {
					curr = freepos;
					return false;
				}
			

			if (arr[curr].key == _key)  return true;
			

			if ((freepos == -1) && (arr[curr].key == "&")) 
				freepos = curr;
			

			curr = (curr + step) % maxSize;
		}
		return false;
	}

	void Delete(TKey key) {
		if (!Find(key)) return;
		arr[curr].key = "&";
		dataCount--;
	}

	void Insert(TRecord < TKey, TValue> record) {
		if (!Find(record.key)) {
			arr[curr] = record;
			dataCount++;
		}
	}

	void Reset() {
		curr = 0;
		while (((arr[curr].key == "&") || (arr[curr].key == "")) && (curr < maxSize)) {
			curr++;
		}
	}
	bool isEnd() {
		return curr >= maxSize;
	}

	void goNext() {
		while ((++curr < maxSize)) {
			if (((arr[curr].key != "&") && (arr[curr].key != "")))
				break;
		}
	}
	TRecord<TKey, TValue> getCurr() { return arr[curr]; }
};