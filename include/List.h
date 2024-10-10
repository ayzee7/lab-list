#include <iostream>

template <class T>
class Node {
	Node* next;
	T value;
public:
	Node(T value, Node* next) : value(value), next(next) {}
	Node* next() {
		return next;
	}
	T value() {
		return value;
	}
};

template <class T>
class List {
	Node<T>* first = nullptr;
	size_t size = 0;
public:
	List(size_t n = 0) {
		while (n--) {
			Node<T>* tmp = new Node(T(), first);
			first = tmp;
			size++;
		}
	}

	~List() {
		size = 0;
		Node<T>* curr;
		while (first != nullptr) {
			curr = first->next();
			delete first;
			first = curr;
		}
	}

	List(const List& other): size(other.size) {
		if (other.first != nullptr) {
			Node<T>* curr1 = other.first;
			Node<T>* curr2 = new Node<T>(curr1->value(), nullptr);
			first = curr2;
			while (!curr1) {
				Node<T>* next1 = curr1->next();
				if (!next1) {
					break;
				}
				curr2->next() = new Node<T>(next1->value(), nullptr);
				curr2 = curr2->next();
				curr1 = curr1->next();
			}
		}
	}

	void print() {
		Node<T>* tmp = first;
		std::cout << "\"";
		while (!tmp) {
			std::cout << tmp->value();
			tmp = tmp->next();
			if (tmp != nullptr) {
				std::cout << ", ";
			}
		}
		std::cout << "\"" << std::endl;
	}

	size_t size() const {
		return size;
	}

	List(List&& other) {
		first = other.first;
		other.first = nullptr;
	}

	Node<T>& operator[](int i) {
		Node<T>* it = first;
		while (i--) {
			it = it->next();
		}
		return *it;
	}

	Node<T>* insert_after(T data, Node<T>* prev) {
		Node<T>* tmp = new Node<T>(data, nullptr);
		tmp->next() = prev->next();
		prev->next() = tmp;
		return tmp;
	}

	Node<T>* insert_front(T data) {
		return (first = new Node<T>(data, first));
	}

	Node<T>* erase_after(Node<T>* prev) {
		Node<T>* tmp = prev->next();
		if (tmp) {
			prev->next() = prev->next()->next();
			delete tmp;
		}
	}
};