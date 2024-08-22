#include"List.h"

//--------------------------------------------------------------//

//////////////////////////////////////////////////////
////   Class definition(определение класса)   //////

//////////////////////////////////////////////////////
////                  Element methods:
template<typename T> List<T>::Element::Element(T Data, Element* pNext, Element* pPrev) :Data(Data), pNext(pNext), pPrev(pPrev)
{
#ifdef DEBUG
	cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
}
template<typename T> List<T>::Element::~Element()
{
#ifdef DEBUG
	cout << "EDestructor:\t" << this << endl;
#endif // DEBUG

}
////                      Element methods:
/////////////////////////////////////////////////////////////

//---------------------------------------------------------//

////////////////////////////////////////////////////////////
////                      Iterators methods:

//                             Const base iterators:
//                           Comparison operators:
template<typename T>bool List<T>::ConstBaseIterator::operator == (const ConstBaseIterator& other) const
{
	return this->Temp == other.Temp;
}
template<typename T>bool List<T>::ConstBaseIterator::operator != (const ConstBaseIterator& other) const
{
	return this->Temp != other.Temp;
}
template<typename T>const T& List<T>::ConstBaseIterator:: operator*()const
{
	return Temp->Data;
}
//                        Const iterator:
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	//Prefix increment
	//BaseClass::member_variable;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator++(int)
{
	//Sufix increment
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
//                     Const Revers Iterators:
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

//                            Iterator:
template<typename T> T& List<T>::List::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

//                     ReverseIterator:
template<typename T> T& List<T>::List::ReverseIterator:: operator*()
{
	return ConstBaseIterator::Temp->Data;
}

////                      Iterators methods:
/////////////////////////////////////////////////////////////

//--------------------------------------------------------//

//////////////////////////////////////////////////////
////                           List methods:
	// ConstIterator - имя типа.
	// begin - имя функции.
	// typename указываем чтобы компилятор 

template <typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template <typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template <typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template <typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template <typename T>typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template <typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template <typename T>typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}
template <typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
template<typename T> List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T> List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
	{
		//push_front(*it);
		push_back(*it);
	}
}
template<typename T>List<T>::List(const List<T>& other) :List()
{
	*this = other;
	cout << "CopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//                                 Operators:
template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "CopyAssignment:\t" << this << endl;
	return *this;
}

//                             Adding elements:

template<typename T>void List<T>::push_front(T Data)
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
template<typename T>void List<T>::push_back(T Data)
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
template<typename T>void List<T>::insert(T Data, int Index)
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
template<typename T>void List<T>::pop_front()
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
template<typename T>void List<T>::pop_back()
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
		delete Tail->pNext; Tail->pNext = nullptr;
	}
	size--;
}
//                            Methods:
template<typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов в списке:" << size << endl;
}
template<typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов в списке:" << size << endl;
}
///////////////////           List metods
/////////////////////////////////////////////////////////////////////////

template <typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List buffer = left;
	for (List::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		buffer.push_back(*it);
		//*it *= 10;
	}
	return buffer;
}
////////  Class definition end (конец определения класса)  //////////////
/////////////////////////////////////////////////////////////////////////