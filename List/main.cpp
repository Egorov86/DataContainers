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
		int Data; // �������� ��������
		Element* pNext; //��������� �� ���� �������
		Element* pPrev; //��������� �� ���� �������
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
	}*Head, * Tail; // ������� ������ ����� ��������� ��������������� ����� ��� ��������.
	//Element* Head;
	//Element* Tail;
	size_t size;     // size_t - ��� typedef �� 'unsigned int'
	// ���������  'typedef' ������� ��������� ��� ������������� ���� ������.
	//"typedef" ����� ��������� ���������:
	//                  typedef ����������_���_������ ���������
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
			//1)������� ����� �������
			Element* New = new Element(Data);

			//2)����������� ����� �������� � ������ ������
			New->pNext = Head; Head = New;

			//3)����������� �������� ������� ������ � ������ ��������
			//Head->pPrev = New;
			//4)������� ������ �� ����� �������
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
			//1)������� ����� �������

			//2)����������� ����� ������� � ����� ������
			Tail->pNext = New;
			New->pPrev = Tail;
			Tail = New;    // �������� Tail

		}
		size++;

	}
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab<< Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� � ������:" << size <<endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp!=Head; Temp = Temp->pNext)
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "���������� ��������� � ������:" << size << endl;
	}
};

void main()
{
	setlocale(LC_ALL, "Rus");
	int n;
	cout << "������� ������ ������\t"; cin >> n;
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