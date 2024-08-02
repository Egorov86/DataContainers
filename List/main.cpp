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
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;
	}*Head, * Tail; // Объекты класса можно объявлять непосредственно после его описания.
	//Element* Head;
	//Element* Tail;
	size_t size;     // size_t - это typedef на 'unsigned int'
	// Директива  'typedef' создает псевдоним для существующего типа данных.
	//"typedef" имеет следующий синтаксис:
	//                  typedef существует_тип_данных псевдоним
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
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
			Element* New = new Element(Data);

			//2)Привязываем новый Элеимент к началу списка
			New->pNext = Head; Head = New;

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
			//1)создаем новый элемент
			Element* New = new Element(Data);
			//2)Привязываем новый Элемент к концу списка
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;         // cмещаем хвост на новый элемент.

		}
		size++;

	}
	//                        Methods;
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab<< Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке:" << size <<endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке:" << size << endl;
	}


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
		Element* New = new Element(Data);
		// вместо нулей элемента меняем указатели pNext и pPrev
		New->pNext = Temp;   //указывает на 8
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
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
			delete Head->pPrev;
			//3)Зануляем указатель 'Head->pPrev'
			Head->pPrev = nullptr;
		}
		size--;
	}
	void pop_back()
	{
		/*if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
		}*/
		if (Head == Tail)return pop_front();
		else
		{
			Tail = Tail->pPrev;
			delete Tail->pNext;
			Tail->pNext = nullptr;
		}
		size--;
	}
};
void main()
{
	setlocale(LC_ALL, "Rus");
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
}