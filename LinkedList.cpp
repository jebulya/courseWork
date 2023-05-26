#include <iostream>
#include <initializer_list>

template <class T>
class LinkedList {
	class Node;

	Node* head;
	Node* tail;
	size_t len;

public:
	LinkedList() : head(nullptr), tail(nullptr), len(0) {};

	// Copy constructor
	LinkedList(LinkedList<T> const& other) : LinkedList() {
		for (auto i = other.begin(); i != other.end(); i++) {
			this->push_back(new T(*i));
		}
	};

	// Usage: LinkedList<int> = { 1, 2, 3 };
	LinkedList(std::initializer_list<T> list) : LinkedList() {
		for (auto i = list.begin(); i != list.end(); i++) {
			this->push_back(new T(*i));
		}
	}

	~LinkedList() { this->clear(); };

	size_t length() { return this->len; };
	bool is_empty() { return this->len == 0; }

	// Moves `value` into new last element
	void push_back(T* value) {
		Node* new_node = new Node(value, nullptr);

		if (this->tail == nullptr) {
			push_first(new_node);
			return;
		}

		this->tail->next = new_node;
		this->tail = new_node;
		this->len++;
	};

	// Moves `value` into new first element
	void push_front(T* value) {
		this->insert(value, this->len);
	};

	// Moves `value` into new element at `index`
	// Returns `-1` if index is out of bounds
	int insert(T* value, size_t index) {
		Node** prev_ptr;
		Node* next;

		if (index > this->len) {
			return -1;
		} if (index == this->len) {
			this->push_back(value);
			return 0;
		}

		if (index == 0) {
			prev_ptr = &this->head;
			next = this->head;
		} else {
			Node* prev = std::next(this->begin(), index - 1).node;
			prev_ptr = &prev->next;
			next = prev->next;
		}

		Node* inserted = new Node(value, next);

		(*prev_ptr) = inserted;
		this->len++;

		return 0;
	}

	// Copies `value` into new last element
	void push_back(T const& value) {
		this->push_back(new T(value));
	};

	// Copies `value` into new first element
	void push_front(T const& value) {
		this->push_front(new T(value));
	};

	// Copies `value` into new element at `index`
	// Returns `-1` if index is out of bounds
	int insert(T const& value, size_t index) {
		return this->insert(new T(value), index);
	}

	// Transfers ownership of value at `index` from list to user
	// Returns `nullptr` if `index` is out of bounds or list is empty
	T* pop(size_t index) {
		if ((index >= this->len) || (this->len == 0)) {
			return nullptr;
		}

		Node** prev_ptr;
		Node* to_pop;

		if (index == 0) {
			prev_ptr = &this->head;
			to_pop = this->head;
		} else {
			Node* prev = std::next(this->begin(), index - 1).node;
			prev_ptr = &prev->next;
			to_pop = prev->next;
		}

		Node* next = to_pop->next;

		T* value = to_pop->value;
		to_pop->value = nullptr;
		delete to_pop;

		(*prev_ptr) = next;
		this->len--;

		return value;
	}

	// Transfers ownership of first value from list to user
	// Returns `nullptr` if list is empty
	T* pop_front() {
		return this->pop(0);
	}

	void remove(size_t index) {
		delete pop(index);
	}

	void clear() {
		for (auto itr = this->begin(); itr != this->end(); delete (itr++).node) {}

		this->len = 0;
		this->head = this->tail = nullptr;
	}

public:
	struct iterator : std::iterator<std::forward_iterator_tag, T> {
		Node* node;

		iterator() = delete;
		iterator(const iterator&) = default;
		iterator(Node* node) : node(node) {}

		iterator& operator++() { node = node->next; return *this; }
		iterator operator++(int) { iterator copy(*this); ++(*this); return copy; }

		bool operator==(iterator other) { return node == other.node; }
		bool operator!=(iterator other) { return node != other.node; }
		T& operator*() { return *(node->value); }
	};

	iterator begin() { return iterator(this->head); }
	iterator end() { return nullptr; }

	T& operator[](size_t index) {
		return *std::next(this->begin(), index);
	}

private:
	class Node {
	public:
		T* value;
		Node* next;

		Node(T* value, Node* next) : value(value), next(next) {};
		~Node() { delete value; }
	};

	void push_first(Node* first_node) {
		this->head = first_node;
		this->tail = first_node;
		this->len = 1;
	}

	T* pop_last() {
		T* value = this->head->value;

		this->head->value = nullptr;
		delete this->head;

		this->head = this->tail = nullptr;
		this->len = 0;

		return value;
	}
};