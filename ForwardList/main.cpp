#include<iostream>
#include<list>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
#define delimiter "\n-----------------------------------------------------\n"
class Element
{
	int Data;
	Element* pNext;
	static int count;
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList; // дружеств функция
};
int Element::count = 0;

class ForwardList
{
	Element* Head; // Голова списка, указывает на начальный элемент списка
	int size;
public:
	int get_size()const
	{
		return size;
	}
	ForwardList()
	{ //Конструктор по умолчанию который создает пустой список
		Head = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	explicit ForwardList (int size):ForwardList()
	{
		while (size--)push_front(0);
	}
	ForwardList(const ForwardList& other) : ForwardList()
	{
		*this = other;  // Повторно используем код CopyAssignment
		cout << "CopyConstructor:\t" << this << endl;
	}
	ForwardList(ForwardList&& other) :ForwardList()
	{
		*this = std::move(other); // функция std::move принудительно вызывает MoveAssignment для класса
		cout << "MoveConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	//                       Operators:
	ForwardList& operator=(const ForwardList& other)
	{
		if (this == &other)return *this; 
		this->~ForwardList();
		while (Head)pop_front();
		for (Element* Temp = other.Head;Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "CopyAssignment:\t" << this << endl;
		return *this;
	}
	ForwardList& operator=(ForwardList&& other)
	{
		if (this == &other)return *this;
		this->~ForwardList();
		this->Head = other.Head;
		this->size = other.size;
		other.Head = nullptr;
		other.size = 0;
		cout << "MoveAssignment:\t" << this << endl;
	}

	const int& operator[](int index)const
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
	}
	int& operator[](int index)
	{
		Element* Temp = Head;
		for (int i = 0; i < index; i++)Temp = Temp->pNext;
		return Temp->Data;
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
		size++;
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
		size++;


	}
	void insert(int Index, int Data)
	{
		if (Index >size)
		{
			cout << "Error: out of range" << endl;
			return;
		}
		if (Index == 0)return push_front(Data);
		//1) создаем новый элемент:
		Element* New = new Element(Data);
		//2) доходим до нужного элемента
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			//if (Temp->pNext == nullptr)break;
			Temp = Temp->pNext;
		}
		//3)Вставляем элемент в список
		New->pNext = Temp->pNext;
		Temp->pNext = New;
		size++;
	}
	//                Removing elemets:
	void pop_front()
	{
		if (Head == nullptr)return;
		//1)Запоминаем адрес удаляемого элемента
		Element* Erased = Head;
		//2)Исключаем удаляемый элемент из списка
		Head = Head->pNext;
		//3)Удалчем элемент из памяти
		delete Erased;
		size--;
		/*
		//проверяю на пустой(нулевой) список.
		if (Head == nullptr)return;
		// удаляем первый элемент списка
		Element* OldHead = Head;
		Head = Head->pNext;
		// удаляем старый первый элемент
		delete OldHead;
		------------
		new      -  создвет объект в динмич памяти
		new[]    -  создвет массив объектов в динмич памяти

		delete   - удаляет 1 объект из динамич памяти 
		delete[] - удаляет массив объектов из динамич памяти 
		delete new ....[...];  //behavior is undefined повед не определено
		delete [] new ....;  //behavior is undefined повед не определено
		
		*/
	}
	void pop_back()
	{
		if (Head->pNext == nullptr)return pop_front();
		//1)доходим до предпосл элемента
		Element* Temp = Head;
		while (Temp->pNext->pNext)Temp = Temp->pNext;
		//2)удаляем последний элемент
		delete Temp->pNext;
		//3) Обнуляем указатель на посл элемент
		Temp->pNext = nullptr;
		size--;
		/*
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
		}*/
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
		cout << "Кол-во элем-ов списка: " << size << endl;
		cout << "общее кол-во элем-ов: " << Element::count << endl;
	}
};

ForwardList operator+(const ForwardList& left, const ForwardList& right)
{
	ForwardList buffer;
	for (int i = 0; i < left.get_size(); i++) buffer.push_back(left[i]);
	for (int i = 0; i < right.get_size(); i++) buffer.push_back(right[i]);
	return buffer;

}
//#define BASE_CHECK
//#define COUNT_CHECK
//#define SIZE_CONSTRUCTOR_CHECK
void main()
{
	setlocale(LC_ALL, "Rus");
#ifdef BASE_CHECK
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
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
#endif // BASE_CHECK
#ifdef COUNT_CHECK
	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();
#endif // COUNT_CHECK
#ifdef SIZE_CONSTRUCTOR_CHECK
	ForwardList list(5);
	for (int i = 0; i < list.get_size(); i++)
	{
		list[i] = rand() % 100;
	}
	for (int i = 0; i < list.get_size(); i++)
	{
		cout << list[i] << tab;
	}
	cout << endl;
#endif // SIZE_CONSTRUCTOR_CHECK

	ForwardList list1;
	list1.push_back(3);
	list1.push_back(5);
	list1.push_back(8);
	list1.push_back(13);
	list1.push_back(21);
	list1.print();

	ForwardList list2;
	list2.push_front(34);
	list2.push_front(55);
	list2.push_front(89);
	list2.print();

	cout << delimiter << endl;
	//ForwardList list3 = list1 + list2;     // COPYCONSTRUCTOR
	cout << delimiter << endl;
	ForwardList list3;
	cout << delimiter << endl;
	list3 = list1 + list2;               // COPYASSIGNMENT
	cout << delimiter << endl;
	list3.print();
}