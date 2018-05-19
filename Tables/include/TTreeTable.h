#pragma once
#include "TTable.h"
#include "TStack.h"
template <class TKey, class TValue>
struct TNode {
	int bal;
	TRecord<TKey, TValue> record;
	TNode *pLeft, *pRight;
};

template <class TKey, class TValue>
class TTreeTable : public TTable<TKey, TValue> {
protected:
	TNode<TKey, TValue> *pRoot;
	TNode<TKey, TValue> *pCurr;
	TStack<TNode<TKey,TValue>*> stack;
	TNode<TKey, TValue> **pRes;
	int pos;

public:
	TTreeTable() {
		pRoot = pCurr = NULL;
	}

	bool Find(TKey _key) {
		pRes = &pRoot;
		while (*pRes != NULL) {
			Eff;
			if ((*pRes)->record.key == _key)
				return true;
			if ((*pRes)->record.key < _key)
				pRes = &(*pRes)->pRight;
			else pRes = &(*pRes)->pLeft;
		}
		return false;
	}

	void Insert(TRecord<TKey, TValue> _record) {
		if (!Find(_record.key)) {
			*pRes = new TNode<TKey, TValue>();
			(*pRes)->record = _record;
			(*pRes)->record.periodicity = 1;
		}
		else (*pRes)->record.periodicity++;
	}

	void Delete(TKey _key) {
		if (!Find(_key)) return;
		TNode<TKey, TValue> *tmp = *pRes;
		if (!tmp->pLeft)
			*pRes = tmp->pRight;
		else if (!tmp->pRight)
			*pRes = tmp->pLeft;

		else {
			TNode<TKey, TValue> *find = tmp->pLeft;
			TNode<TKey, TValue> **iter;
			iter = &(*pRes)->pLeft;
			while (find->pRight) {
				iter = &(*iter)->pRight;
				find = find->pRight;
			}
			tmp->record = find->record;
			tmp = find;
			*iter = find->pLeft;
		}
		delete tmp;
	}

	void Reset() {
		stack.clear();
		pos = 0;
		pCurr = pRoot;
		while (pCurr->pLeft != NULL) {
			stack.push(pCurr);
			pCurr = pCurr->pLeft;
		}
		
	}
	bool isEnd() {
		return pos == dataCount;
	}

	void goNext() {
		stack.pop();
		pos++;
		if (pCurr->pRight != NULL) {
			pCurr = pCurr->pRight;
			while (pCurr->pLeft != NULL) {
				stack.push(pCurr);
				pCurr = pCurr->pLeft;
			}
			stack.push(pCurr);
		}
		else if (!stack.isEmpty()) pCurr = stack.top();
	}

	bool isFull() const {
		return false;
	}

	TRecord<TKey, TValue> getCurr() { return pCurr->record; }
};
