#pragma once
#include <iostream>
using namespace std;
template <class TKey, class TValue>
struct TRecord {
	TKey key;
	TValue value;
};


template <class TKey, class TValue>
class TTable {
protected:
	int dataCount;
	int Eff;
public:
	TTable() {
		dataCount = Eff = 0;
	}

	bool isEmpty() const {
		return (dataCount == 0);
	}

	int getDataCount() const {
		return dataCount;
	}

	int getEff() const {
		return Eff;
	}

	void incEff() {
		Eff++;
	}
	virtual bool isFull() const = 0;
	virtual bool Find(TKey _key) = 0;
	virtual void Insert(TRecord<TKey, TValue> record) = 0;
	virtual void Delete(TKey _key) = 0;
	virtual void Reset() = 0;
	virtual bool isEnd() = 0;
	virtual void goNext() = 0;
	virtual TRecord<TKey, TValue> getCurr() = 0;
	virtual void Print() {
		TRecord<TKey, TValue> tmp;
		for (Reset(); !isEnd(); goNext()) {
			cout << tmp.key << " Val :" << tmp.value<<endl;
		}
	}
};