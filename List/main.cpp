#include<iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"
class List
{
	class Element
	{
		int Data; // значение элемента
		Element* pNext; //указатель на след элемент
		Element* pPrev; //указатель на пред элемент
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr) :Data(Data), pNext(pNext), pPrev(pPrev)
		{
#ifdef DEBUG
			cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
		}
		~Element()
		{
#ifdef DEBUG
			cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

		}
		friend class List;
	}*Head, *Tail; // Объекты класса можно объявлять непосредственно после его описания.
	//Element* Head;
	//Element* Tail;
	size_t size;     // size_t - это typedef на 'unsigned int'
	// Директива  'typedef' создает псевдоним для существующего типа данных.
	//"typedef" имеет следующий синтаксис:
	//                  typedef существует_тип_данных псевдоним

	class ConstBaseIterator
	{
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr) : Temp(Temp)
		{
			cout << " CBItConstructor:\t" << this << endl;
		}
		~ConstBaseIterator()
		{
			cout << " CBItDestructor:\t" << this << endl;
		}
		//                          Comparison operators:
		bool operator == (const ConstBaseIterator& other) const
		{
			return this->Temp == other.Temp;
		}
		bool operator != (const ConstBaseIterator& other) const
		{
			return this->Temp != other.Temp;
		}
		const int& operator*()const // конст для конси объекта
		{
			return Temp->Data;
		}
		int& operator*()            // неконст для неконст объекта, который можно изменить
		{
			return Temp->Data;
		}
	};
public:
	
	class Iterator
	{
		Element* Temp;
	public:
	
		Iterator(Element* Temp = nullptr) :Temp(Temp)
		{
#ifdef DEBUG
			cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG

		}
		~Iterator()
		{
#ifdef DEBUG
			cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG

		}
		Iterator& operator++()
		{
			//Prefix increment
			Temp = Temp->pNext;
			return *this;
		}
		Iterator operator++(int)
		{   //Suffix increment
			Iterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		Iterator& operator--()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		Iterator operator--(int)
		{
			Iterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		
	};
	class ReverseIterator: public ConstBaseIterator
	{
		Element* Temp;
	public:
		ReverseIterator(Element* Temp = nullptr) : ConstBaseIterator(Temp)
       ~ReverseIterator() {}

		//                 Increment/Decrement:
		ReverseIterator& operator++()
		{
			Temp = Temp->pPrev;
			return *this;
		}
		ReverseIterator& operator++(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pPrev;
			return old;
		}
		ReverseIterator& operator--()
		{
			Temp = Temp->pNext;
			return *this;
		}
		ReverseIterator& operator--(int)
		{
			ReverseIterator old = *this;
			Temp = Temp->pNext;
			return old;
		}
		//                Comparison operators:
		bool operator==(const ReverseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ReverseIterator& other)const
		{
			return this->Temp != other.Temp;
		}
		//        Dereference operators (операторы разыменования)
		const int& operator*()const
		{
			return Temp->Data;
		}
		int& operator*()
		{
			return Temp->Data;
		}
	};
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	Iterator begin()const
	{
		return Head;
	}
	Iterator end()const
	{
		return nullptr;
	}
	ReverseIterator rbegin()
	{
		return Tail;
	}
	ReverseIterator rend()
	{
		return nullptr;
	}
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	List(const std::initializer_list<int>& il) :List()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
		{
			//push_front(*it);
			push_back(*it);
		}
	}
	List(const List& other) :List()
	{
		*this = other;
		cout << "CopyConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	//                      Operators:
	List& operator=(const List& other)
	{
		if (this == &other)return *this;
		while (Head)pop_front();
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	//     Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			//1)создаем новый элемент
			//Element* New = new Element(Data, Head);

			//2)Привязываем новый Элеимент к началу списка
		    Head = Head->pPrev = new Element(Data, Head);

			//3)Привязываем головной элемент списка к новому элементу
			//Head->pPrev = New;
			//4)Смещаем голову на новый элемент
			//Head = New;
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
			/*//1)создаем новый элемент
			Element* New = new Element(Data);
			//2)Привязываем новый Элемент к концу списка
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;   // cмещаем хвост на новый элемент.*/
		}
		size++;

	}
	//                        Methods;
	void insert(int Data, int Index)
	{
		if (Index > size)return;
		if (Index == 0)return push_front(Data);
		if (Index == size)return push_back(Data);
		Element* Temp;
		if (Index < size / 2)
		{
			Temp = Head;
			for (int i = 0; i < Index; i++)Temp = Temp->pNext;
		}
		else
		{
			Temp = Tail;
			for (int i = 0; i < size - Index - 1; i++) Temp = Temp->pPrev;
		}
		Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
		
		/*Element* New = new Element(Data);
		// вместо нулей элемента меняем указатели pNext и pPrev
		New->pNext = Temp;   //указывает на 8
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;*/
		size++;
	}
	//                         Removing alements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		else
		{
			//1)смещаем голову на следующий элемент
			Head = Head->pNext;
			//2)удаляем элемент Head->pPrev из памяти
			delete Head->pPrev; Head->pPrev = nullptr;
			//3)Зануляем указатель 'Head->pPrev'
		}
		size--;
	}
	void pop_back()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}
		//if (Head == Tail)return pop_front();
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;Tail->pNext = nullptr;
		}
		size--;
	}
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке:" << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке:" << size << endl;
	}
};
List operator+(const List& left, const List& right)
{
	List buffer = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		*it *= 10;
	}
	return buffer;
}
//#define BASE_CHECK
//#define ITERATORS_CHECK
#define OPERATOR_PLUS_CHECK

void main()
{
	setlocale(LC_ALL, "Rus");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка\t"; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	cout << delimiter << endl;
	list.reverse_print();
	cout << delimiter << endl;
	list.push_back(123);
	cout << delimiter << endl;
	list.print();
	cout << delimiter << endl;
	list.pop_front();
	cout << delimiter << endl;
	list.print();
	cout << delimiter << endl;
	list.pop_back();
	cout << delimiter << endl;
	list.print();
	int Index;
	int value;
	cout << " Введите индекс добавляемого элемента: "; cin >> Index;
	cout << " Введите значение добавляемого элемента: "; cin >> value;
	list.insert(value, Index);
	list.print();
	cout << delimiter << endl;
	list.reverse_print();
#endif // BASE_CHECK

#ifdef ITERATORS_CHECK
	List list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list) cout << i << tab; cout << endl;

	//List::Iterator it;
	//const int jt = *it;
	for (List::Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
	for (List::ReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
#endif // ITERATORS_CHECK

	List list1 = { 3, 5, 8, 13, 21 };
	List list2 = { 34, 55, 89 };
	List list3 = list1 + list2;
	for (int i : list1)cout << i << tab; cout << endl;
	for (int i : list2)cout << i << tab; cout << endl;
	for (int i : list3)cout << i << tab; cout << endl;
}