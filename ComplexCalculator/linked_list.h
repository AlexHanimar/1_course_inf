#pragma once

#ifndef LINKED_LIST
#define LINKED_LIST

#include <string>
#include <iostream>

template<typename T>
struct Node
{
	Node<T>* prev, * next;
	T val;
	Node(void) : prev{ nullptr }, next{ nullptr } {}
	Node(T _val) : prev{ nullptr }, next{ nullptr }, val{ _val } {}
};

template<typename T>
class LinkedList
{
private:
	Node<T>* head, * tail;
public:
	LinkedList(void)
	{
		head = new Node<T>;
		tail = new Node<T>;
		head->next = tail;
		tail->prev = head;
	}
	LinkedList(Node<T>* begin, Node<T>* end)
	{
		head = new Node<T>;
		tail = new Node<T>;
		head->next = begin;
		begin->prev = head;
		tail->prev = end;
		end->next = tail;
	}
	bool empty(void)
	{
		return (head->next == tail);
	}
	void insertAfter(Node<T>* node, T _val)
	{
		Node<T>* tmp = new Node<T>(_val);
		tmp->next = node->next;
		tmp->prev = node;
		node->next->prev = tmp;
		node->next = tmp;
	}
	void insertBefore(Node<T>* node, T _val)
	{
		Node<T>* tmp = new Node<T>(_val);
		tmp->next = node;
		tmp->prev = node->prev;
		node->prev->next = tmp;
		node->prev = tmp;
	}
	void pushFront(T _val)
	{
		insertAfter(head, _val);
	}
	void pushBack(T _val)
	{
		insertBefore(tail, _val);
	}
	void popFront(void)
	{
		if (empty())
			throw std::string("List empty");
		head->next = head->next->next;
		delete head->next->prev;
		head->next->prev = head;
	}
	void popBack(void)
	{
		if (empty())
			throw std::string("List empty");
		tail->prev = tail->prev->prev;
		delete tail->prev->next;
		tail->prev->next = tail;
	}
	T front(void)
	{
		if (empty())
			throw std::string("List empty");
		return head->next->val;
	}
	T back(void)
	{
		if (empty())
			throw std::string("List empty");
		return tail->prev->val;
	}
	LinkedList cut(Node<T>* begin, Node<T>* end)
	{
		if (begin->prev == nullptr || end->next == nullptr)
			throw std::string("Invalid cut");
		Node<T>* cutFront = begin->prev;
		Node<T>* cutBack = end->next;
		cutFront->next = cutBack;
		cutBack->prev = cutFront;
		return LinkedList(begin, end);
	}
	void printList(std::ostream &out)
	{
		Node<T>* cur = head->next;
		while (cur != tail) {
			out << cur->val << " ";
			cur = cur->next;
		}
		out << std::endl;
	}
	Node<T>* at(int id)
	{
		if (id < 0)
			throw std::string("List index out of range");
		Node<T>* res = head;
		for (int i = 0; i < id; i++) {
			if (res->next == nullptr)
				throw std::string("List index out of range");
			res = res->next;
		}
		return res;
	}
	const Node<T>* begin(void)
	{
		return head;
	}
	const Node<T>* end(void)
	{
		return tail;
	}
	void deleteNode(Node<T>* node)
	{
		if (node == head || node == tail)
			throw std::string("Can't delete head/tail of list");
		cut(node, node);
	}
};

#endif LINKED_LIST