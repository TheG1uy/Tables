#pragma once
#include "TArrayTable.h"


template <class TKey, class TValue>
class TScanTable :public TArrayTable<TKey, TValue> {
public:
	virtual bool Find(TKey _key) {
		for (int i = 0; i < dataCount; i++) {
			if (arr[i].key == _key) {
				curr = i;
				return true;
			}
			Eff++;
		}
		curr = dataCount;
		return false;
	}
	virtual void Insert(TRecord<TKey, TValue> record) {
		
		if (!Find(record.key)) {
			if (isFull()) return;
			arr[curr] = record;
			dataCount++;
			Eff++;
		}
		else {

		}
	}
	virtual void Delete(TKey _key) {

		if (Find(_key)) {
			arr[curr] = arr[--dataCount];
			Eff++;
		}
	}
};