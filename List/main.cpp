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
		Element* New = new Element(Data);
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = New;
		}
		else
		{
			//1)создаем новый элемент

			//2)Привязываем новый Элемент к концу списка
			Tail->pNext = New;
			New->pPrev = Tail;
			Tail = New;    // обновляю Tail

		}
		size++;

	}
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab<< Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке:" << size <<endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp!=Head; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов в списке:" << size << endl;
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
		list.push_front(rand() % 100);
	}
	list.print();
	cout << delimiter << endl;
	list.push_back(123);
	cout << delimiter << endl;
    list.print();
	cout << delimiter << endl;
	list.reverse_print();
}