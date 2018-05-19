#pragma once
#pragma once
#include "TArrayTable.h"


template <class TKey, class TValue>
class TSortTable : public TArrayTable<TKey, TValue> {
	virtual bool Find(TKey _key) {
		int left = 0, right = dataCount, middle;		
		while(left <= right){
			Eff++;
			middle = (left + right) / 2;

			if (arr[middle].key == _key) {
				curr = middle;
				return true;
			}

			if (arr[middle].key < _key) left = middle + 1;
			else right = middle - 1;
		}
		curr = left;
		return false;
	}
	virtual void Insert(TRecord<TKey, TValue> record) {

		if (!Find(record.key)) {
			if (isFull()) return;
			for (int i = dataCount; i > curr; i--) {
				arr[i] = arr[i - 1];
				Eff++;
			}
			record.periodicity = 1;
			arr[curr] = record;			
			dataCount++;
		}
		else {
			arr[curr].periodicity++;
		}
	}
	virtual void Delete(TKey _key) {
		if (Find(_key)) {
			for (int i = curr; i < dataCount - 1; i++) {
				arr[i] = arr[i + 1];
				Eff++;
			}
			dataCount--;
		}
	}
	void QuickSort(int left, int right) {
		int middle = (left + right) / 2;
		TKey x = arr[middle].key;
		TRecord<TKey, TValue> tmp;
		int i = left, j = right;

		while (i <= j) {
			while (arr[i].key < x) {
				i++;
				Eff++;
			}
			while (arr[j].key > x) {
				j--;
				Eff++;
			}

			if (i <= j) {
				tmp = arr[i];
				arr[i] = arr[j];
				arr[j] = tmp;
				i++;
				j--;
			}

			if (j > left) {
				QuickSort(left, j);
			}
			if (i < right) {
				QuickSort(i, right);
			}
		}
	}
};