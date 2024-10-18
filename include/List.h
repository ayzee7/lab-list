#include <iostream>

template <class T>
class List;

template <class T>
class Node {
protected:
	Node* next;
	
public:
	T value;
	Node(T value, Node* next) : value(value), next(next) {}

	friend class List<T>;
};

template <class T>
class List {
	Node<T>* first = nullptr;
	size_t sz = 0;

public:
	List(size_t n = 0) {
		if (n > INT_MAX) {
			throw "Invalid list size";
		}
		while (n--) {
			Node<T>* tmp = new Node<T>(T(), first);
			first = tmp;
			sz++;
		}
	}

	~List() {
		sz = 0;
		Node<T>* curr;
		while (first != nullptr) {
			curr = first->next;
			delete first;
			first = curr;
		}
	}

	List(const List& other): sz(other.sz) {
		if (other.first != nullptr) {
			Node<T>* curr1 = other.first;
			Node<T>* curr2 = new Node<T>(curr1->value, nullptr);
			first = curr2;
			while (curr1 != nullptr) {
				Node<T>* next1 = curr1->next;
				if (next1 == nullptr) {
					break;
				}
				curr2->next = new Node<T>(next1->value, nullptr);
				curr2 = curr2->next;
				curr1 = curr1->next;
			}
		}
	}

	struct Iterator {
		Iterator(Node<T>* pointer) : ptr(pointer) {}

		Node<T>& operator*() const { return *ptr; }
		Node<T>* operator->() { return ptr; }

		Iterator& operator++() { 
			ptr = ptr->next;
			return *this; 
		}

		Iterator operator++(int) {
			Iterator tmp = *this;
			++(*this);
			return tmp;
		}

		Iterator next() {
			return ptr->next;
		}

		friend bool operator== (const Iterator& a, const Iterator& b) { return a.ptr == b.ptr; };
		friend bool operator!= (const Iterator& a, const Iterator& b) { return a.ptr != b.ptr; };

	private:
		Node<T>* ptr;
	};

	Iterator begin() { return Iterator(first); }
	Iterator end() { return Iterator(nullptr); }

	void print() {
		std::cout << "(";
		for (Iterator i = this->begin();  i != this->end(); ++i) {
			std::cout << i->value;
			if (i.next() != this->end()) {
				std::cout << ", ";
			}
		}
		std::cout << ")" << std::endl;
	}

	size_t size() const {
		return sz;
	}

	List(List&& other) noexcept {
		first = other.first;
		other.first = nullptr;
	}

	Node<T>& operator[](size_t ind) {
		Iterator it = this->begin();
		for (size_t i = 0; i < ind; ++i, ++it);
		return *it;
	}

	Node<T>* insert_after(T data, Node<T>* prev) {
		if (prev == nullptr) {
			throw "Invalid node pointer";
		}
		Node<T>* tmp = new Node<T>(data, nullptr);
		tmp->next = prev->next;
		prev->next = tmp;
		sz++;
		return tmp;
	}

	Node<T>* insert_front(T data) {
		sz++;
		return (first = new Node<T>(data, first));
	}

	Node<T>* erase_after(Node<T>* prev) {
		if (prev == nullptr) {
			throw "Invalid node pointer";
		}
		Node<T>* tmp = prev->next;
		Node<T>* tmp_copy(tmp);
		if (tmp) {
			sz--;
			prev->next = prev->next->next;
			delete tmp;
		}
		return tmp_copy;
	}

	Node<T>* erase_front() {
		sz--;
		Node<T>* front_copy = first;
		first = first->next;
		return front_copy;
	}

	Node<T>* GetHead() {
		return first;
	}

	Iterator find(T val) {
		for (auto& node : *this) {
			if (node.value == val) {
				return Iterator(&node);
				break;
			}
		}
		return this->end();
	}
};