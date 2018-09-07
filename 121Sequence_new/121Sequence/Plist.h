#pragma once
#include<stdexcept>
template<typename T>
class Plist
{
public:
	class ListNode
	{
	public:
		T data;
		ListNode *prev;
		ListNode *next;
		ListNode(){};
		ListNode(T t, ListNode *pre, ListNode *nex) :data(t), prev(pre), next(nex){};
		~ListNode(){};
	};
	Plist();
	~Plist();
	bool insert(T t);
	bool insert(T t, ListNode *re);
	bool del(int pos);
	bool del(ListNode *re);
	T& getAt(int index);
	bool empty();
	int getlength();
	ListNode *head;
	ListNode *tail;
	ListNode *refer;
	ListNode *refer1;
	ListNode *refer2;
	ListNode *refer3;
	Plist<T>& operator =(Plist& a);
	int len = 0;
};
template<typename T>
Plist<T>::~Plist()
{
	ListNode *ptnode;
	for (ptnode = head; ptnode != NULL; ptnode = ptnode->next)
	{
		ptnode->data.~T();
	}
	len = 0;
	head = tail = NULL;
}
template<typename T>
Plist<T>::Plist() :len(0)
{
	head = tail = NULL;
}
template<typename T>
bool Plist<T>::insert(T t, ListNode * re)
{
	ListNode *temp = new ListNode();
	temp->prev = NULL;
	temp->next = NULL;
	temp->data = t;
	if (re == head)
	{
		temp->next = head;
		head->prev = temp;
		head = temp;
		len++;
		//cout << "加入头" << endl;
		return true;
	}
	else
	{
		re->prev->next = temp;
		temp->next = re;
		temp->prev = re->prev;
		re->prev = temp;
		len++;
		//cout << "加入中间" << endl;
		return true;


	}

}
template<typename T>
bool Plist<T>::insert(T t)
{

	//如果长度为0，换为头结点

	/*ListNode *temp = new ListNode();
	temp->next = head;
	head->prev = temp;
	head = temp;
	len++;
	*/
	ListNode *temp = new ListNode();
	temp->prev = NULL;
	temp->next = NULL;
	temp->data = t;
	if (tail != NULL)
	{
		tail->next = temp;
		temp->prev = tail;
		tail = temp;
		len++;
		return true;
	}
	else
	{
		tail = temp;
		head = temp;
		len++;
		return true;
	}

	//////////////////////////////


}
template<typename T>
bool Plist<T>::del(ListNode *re)
{
	if (re == NULL)
	{
		return false;
	}
	else
	{
		if (re == head)
		{
			if (head == tail)
			{
				ListNode *temp = head;
				head = NULL;
				tail = NULL;
				delete temp;
				len--;
				return true;

			}

			ListNode *temp = head;
			head->next->prev = NULL;
			head = head->next;
			head->prev = NULL;
			delete temp;
			len--;
			return true;
		}
		else
		{
			if (re->next == NULL)
			{
				//cout << "栓出尾"<<endl;
				ListNode *temp = tail;
				temp->prev->next = NULL;
				tail = temp->prev;
				delete temp;
				len--;
				return true;
			}
			else
			{
				//cout << "栓出中间"<<endl;
				ListNode *temp = re;
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				len--;
				return true;

			}
		}
	}
}
template<typename T>
bool Plist<T>::del(int pos)
{
	if (pos < 0 || pos >= len)
	{
		return false;
	}
	else
	{
		if (pos == 0)
		{
			if (len != 1)
			{
				ListNode *temp = head;
				head = head->next;
				head->prev = NULL;
				delete temp;
				len--;
				return true;

			}

			else
			{
				head = NULL;
				tail = NULL;
				len--;
				return true;
					
			}
		}
		else
		{
			if (pos == len - 1)
			{
				ListNode *temp = head;
				for (int i = 0; i < pos; i++)
				{
					temp = temp->next;
				}
				temp->prev->next = NULL;
				delete temp;
				len--;
				return true;

			}
			else
			{
				ListNode *temp = head;
				for (int i = 0; i < pos; i++)
				{
					temp = temp->next;
				}
				temp->prev->next = temp->next;
				temp->next->prev = temp->prev;
				delete temp;
				len--;
				return true;

			}

		}

	}
}
template<typename T>
T& Plist<T>::getAt(int pos)
{
	if (pos < 0 || pos >= len)
	{
		throw out_of_range("out of range");
	}
	else
	{
		ListNode *temp = head;
		for (int i = 0; i < pos; i++)
		{
			temp = temp->next;
		}
		return temp->data;

	}
}
template<typename T>
Plist<T>& Plist<T>::operator=(Plist<T>& a)
{
	while (head != NULL)
	{
		ListNode *temp = head;
		head = head->next;
		head->prev = NULL;
		delete temp;
		len--;

	}
	if (a.head != NULL)
	{
		Plist<T>;

		for (a.refer = a.head; a.refer != NULL; a.refer = a.refer->next)
		{
			this->insert(a.refer->data);
		}
	}
	return *this;
}
