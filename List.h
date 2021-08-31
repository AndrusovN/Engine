
#include <windows.h>
#include <ctime>
#include <cmath>
#pragma warning(disable:4700)

#ifndef List_H
#define List_H

template <class type>
class ListE {
public:
	type value;
	ListE *_next_e;
	ListE *_prev_e;
	ListE<type>() {}
	ListE<type>(type val, ListE<type> next, ListE<type> prev) {
		_prev_e = &prev;
		_next_e = &next;
		value = val;
	}
	bool operator==(const ListE<type>& a) {
		return ((a.value == this->value) && (a._next_e == this->_next_e) && (a._prev_e == this->_prev_e));
	}
	bool operator!=(const ListE<type>& a) {
		return ((a.value != this->value) || (a._next_e != this->_next_e) || (a._prev_e != this->_prev_e));
	}

	bool operator==(ListE<type>& a) {
		return ((a.value == this->value) && (a._next_e == this->_next_e) && (a._prev_e == this->_prev_e));
	}
	bool operator!=(ListE<type>& a) {
		return ((a.value != this->value) || (a._next_e != this->_next_e) || (a._prev_e != this->_prev_e));
	}

};

template <class Type>
class List {
public:
	List<Type>() {
		_first = new ListE<Type>;
		_first->value = Type();
		_first->_next_e = _first;
		_first->_prev_e = _first;
	}


	void append(Type element) {
		
		ListE<Type> *n = (ListE<Type>*)malloc(sizeof(ListE<Type>));
		n->value = element;
		n->_next_e = _first;
		n->_prev_e = _first->_prev_e;
		_first->_prev_e->_next_e = n;
		_first->_prev_e = n;

	}

	Type get(int num) {
		return(get_(num)->value);
	}
	ListE<Type> * get_(int num) {
		ListE<Type> *cur;
		cur = _first;
		for (int i = 0; i <= num; i++)
		{
				cur = cur->_next_e;
		}
		return(cur);
	}

	bool pop(int num) {
		ListE<Type> *cur = get_(num);
		if (cur == _first) {
			return(false);
		}
		cur->_prev_e->_next_e = cur->_next_e;
		cur->_next_e->_prev_e = cur->_prev_e;
		delete(cur);
		
		return(true);
	}

	bool insert(int num, Type element) {
		
		ListE<Type> *cur = get_(num - 1);
		if (cur == _first) {
			return(false);
		}
		ListE<Type> *n = (ListE<Type>*)malloc(sizeof(ListE<Type>));
		n->value = element;
		cur->_next_e->_prev_e = n;
		n->_next_e = (cur->_next_e);
		cur->_prev_e->_next_e->_next_e = n;
		n->_prev_e = cur->_prev_e->_next_e;

		return(true);
	}

	int length() {
		ListE<Type> cur = *_first;
		int res = 0;
		while (true)
		{

			if (cur._next_e == _first) {
				break;
			}
			cur = *cur._next_e;
			res++;
		}
		return(res);
	}

	bool includes(Type value) {
		ListE<Type> cur = *_first;
		bool res = false;
		while (true)
		{
			if (cur._next_e == _first) {
				break;
			}
			if (cur._next_e->value == value) {
				res = true;
				break;
			}
			cur = *cur._next_e;
			//res++;
		}
		return(res);
	}

	bool set(int number, Type value) {
		ListE<Type> *cur = get_(number);
		if (cur == _first) {
			return(false);
		}
		cur->_next_e->_prev_e->value = value;
		return(true);
	}

	bool operator==(const List<Type>&a) {
		ListE<Type> cur_a = *a._first;
		ListE<Type> cur = *_first;
		bool res = true;
		while (true)
		{
			if ((cur._next_e == _first) && (cur_a._next_e == a._first)) {
				break;
			}
			if ((cur._next_e == _first) || (cur_a._next_e == a._first)) {
				res = false;
				break;
			}
			if (cur._next_e->value != cur_a._next_e->value) {
				res = false;
				break;
			}
			cur = *cur._next_e;
			cur_a = *cur_a._next_e;
			//res++;
		}
		return(res);
	}

	bool operator!=(const List<Type>&a) {
		return(!(this == &a));
	}

	bool operator==(List<Type>&a) {
		ListE<Type> cur_a = *a._first;
		ListE<Type> cur = *_first;
		bool res = true;
		while (true)
		{
			if ((cur._next_e == _first) && (cur_a._next_e == a._first)) {
				break;
			}
			if ((cur._next_e == _first) || (cur_a._next_e == a._first)) {
				res = false;
				break;
			}
			if (cur._next_e->value != cur_a._next_e->value) {
				res = false;
				break;
			}
			cur = *cur._next_e;
			cur_a = *cur_a._next_e;
			//res++;
		}
		return(res);
	}

	bool operator!=(List<Type>&a) {
		return(!(this == &a));
	}
	/*bool operator=(const List<Type>&a) {

	}*/
	int index_of(Type value) {
		ListE<Type> cur = *_first;
		int res = -1;
		if (!includes(value)) {
			return(-1);
		}
		while (true)
		{
			if (cur._next_e == _first) {
				break;
			}
			if (cur._next_e->value == value) {
				res ++;
				break;
			}
			cur = *cur._next_e;
			res++;
		}
		return(res);
	}

	/*bool operator = (List<Type> a) {
		this = new List<Type>();
		for (int i = 0; i < a.length(); i++)
		{
			this->append(a.get(i));
		}
	}
	*/
	ListE<Type>* _first;
	//ListE<Type>* _last;
private:
	//ListE<Type>* _null;
	//int len;
	//ListE<Type> *elements;
};

/*int random(int size, int ofset) {
	int *a = (int*)malloc(4);
	//int sysTime = round(time(0)*1000);
	//cout << *a;
	int b = *a;
	free(a);
	return((b%size)+ofset);
}*/

#endif