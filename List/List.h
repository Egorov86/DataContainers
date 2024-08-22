#pragma once
#include<iostream>
#include<string>
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-------------------------------------\n"

//Class
//Class<type>
//Class<T>

//////////////////////////////////////////////////////
////   Class declaration(объявление класса)   //////

template <typename T> class List
{
	class Element
	{
		T Data; // значение элемента
		Element* pNext; //указатель на след элемент
		Element* pPrev; //указатель на пред элемент
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List;
	}*Head, * Tail; // Объекты класса можно объявлять непосредственно после его описания.
	//Element* Head;
	//Element* Tail;
	size_t size;     // size_t - это typedef на 'unsigned int'
	// Директива  'typedef' создает псевдоним для существующего типа данных.
	//"typedef" имеет следующий синтаксис:
	//                  typedef существует_тип_данных псевдоним
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) : Temp(Temp) {}
		~ConstBaseIterator() {}

		//                          Comparison operators:
		bool operator == (const ConstBaseIterator& other) const;
			bool operator != (const ConstBaseIterator& other) const;

			const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstIterator() {}

		ConstIterator& operator++();
		ConstIterator& operator++(int);
		ConstIterator& operator--();
		ConstIterator& operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr) :ConstBaseIterator(Temp) {}
		~ConstReverseIterator() {}

		//                  Increment/Decrement:
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:

		Iterator(Element* Temp = nullptr) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};

	ConstIterator begin()const;
	Iterator begin();

	ConstIterator end()const;
	Iterator end();

	ConstReverseIterator rbegin()const;
	ReverseIterator rbegin();

	ConstReverseIterator rend()const;
	ReverseIterator rend();

	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();
	//                                Operators:
	List<T>& operator=(const List<T>& other);
	//                          Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);

	//                         Removing alements:
	void pop_front();
	void pop_back();

	//                                   Methods:
	void print()const;
	void reverse_print()const;
};

////  Class declaration end(конец объявления класса):  ////
///////////////////////////////////////////////////////////