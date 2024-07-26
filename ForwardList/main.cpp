#include<iostream>
#include<list>
using namespace std;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"
class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList; // дружеств функция
};

class ForwardList
{
	Element* Head; // Голова списка, указывает на начальный элемент списка
public:
	ForwardList()
	{ //Конструктор по умолчанию который создает пустой список
		Head = nullptr;
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	//        Adding elements;
	void push_front(int Data)
	{
		//1) Создаем новый элемент
		Element* New = new Element(Data);

		//2) Пристыковываем новый элемент к началу списка
		New->pNext = Head;
		//3) Голову перенаправляем на новый элемент
		Head = New;
	}
	void push_back(int Data)
	{
		//поскольку push_back() не умеет работать с пустым списком мы проверяем и если список пуст вызываем метод push_front, который умеет работать с пустым списком
		if (Head == nullptr)return push_front(Data);
		//1) Создаем новый элемент
		Element* New = new Element(Data);
		
		//2) Доходим до конца списка:
		Element* Temp = Head;
		//while ((*Temp).pNext)
		while (Temp->pNext)Temp = Temp->pNext;
		//3) После того как мы оказались в конце списка, можно добавлять значения в конец.
		
		Temp->pNext = New;


	}
	void pop_front()
	{
		//проверяю на пустой(нулевой) список.
		if (Head == nullptr)return;
		// удаляем первый элемент списка
		Element* OldHead = Head;
		Head = Head->pNext;
		// удаляем старый первый элемент
		delete OldHead;      
	}
	void pop_back()
	{
		//1)проверяю на пустой(нулевой) список.
		if (Head == nullptr)return;
		//2) Доходим до конца списка:
		Element* The_end = Head;
		while (The_end->pNext)The_end = The_end->pNext;    //запись (The_end->pNext) равносильна (The_end->pNext!=nullptr)
		//3) Удаляем последний элемент и голову направляем на nullptr
		if (The_end == Head)
		{
			delete Head; Head = nullptr; // если список был из одного элеимента
		}
		//4) Удаляем последний элемент и направляем указатель предыдущего на nullptr
		else
		{
			Element* Pred = Head;
			while (Pred->pNext != The_end)
			{
				Pred = Pred->pNext; 
			}
			Pred->pNext = nullptr;
			delete The_end;
		}
	}


	//                       Metods:
	void print()const
	{
		Element* Temp = Head; // TEMP это итератор, итератор - это указатель, при помощи которого можно получить доступ к элементам структуры данных.
		// Temp - указатель Temp;
		// Temp-> - элемент Temp;
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext; // переход на следующий элемент.
		}
	}
};

void main()
{
	setlocale(LC_ALL, "Rus");
	int n;
	cout << "Введите кол-во элементов списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	cout << delimiter << endl;
	list.push_back(123);
	list.print();
	cout << delimiter << endl;
	list.pop_front();
	list.print();
	cout << delimiter << endl;
	list.pop_back();
	list.print();
	cout << delimiter << endl;
}