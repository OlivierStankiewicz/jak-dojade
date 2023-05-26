#pragma once
#include <iostream>
using namespace std;

template <class T>
struct Node
{
	T data;
	Node* next;
	Node* prev;

    void printList()
    {
        Node* tmp = this;
        while (tmp != NULL)
        {
            cout << tmp->data << " ";
            tmp = tmp->next;
        }
        cout << endl;
    }

    int getListLen()
    {
        int count = 0;
        Node* tmp = this;
        while (tmp != NULL)
        {
            count++;
            tmp = tmp->next;
        }
        return count;
    }

    Node* getFirst()
    {
        if (this == NULL)
            return NULL;
        return this;
    }

    Node* getLast()
    {
        if (this == NULL)
            return NULL;
        Node* tmp = this;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
        }
        return tmp;
    }

    Node* getAtPos(int pos)
    {
        Node* tmp = this;
        while (tmp != NULL)
        {
            if (pos == 0)
                return tmp;
            pos--;
            tmp = tmp->next;
        }
        return NULL;
    }

    Node* addFirst(T newData)
    {
        Node* tmp = new Node();
        tmp->data = newData;
        tmp->prev = NULL;
        tmp->next = this;
        if (this != NULL)
            this->prev = tmp;
        return tmp;
    }

    Node* addLast(T newData)
    {
        Node* tmp = new Node();
        tmp->data = newData;
        tmp->next = NULL;
        Node* last = getLast();
        tmp->prev = last;
        if (last == NULL)
            return tmp;
        last->next = tmp;
        return this;
    }

    Node* insertAfter(Node* node, T newData)
    {
        Node* tmp = new Node();
        tmp->data = newData;
        if (node != NULL)
        {
            tmp->next = node->next;
            tmp->prev = node;
            if (node->next != NULL)
                node->next->prev = tmp;
            node->next = tmp;
        }

        return this;
    }

    Node* removeAfter(Node* node)
    {
        if (node != NULL && node->next != NULL)
        {
            Node* tmp = node->next;
            node->next = node->next->next;
            if (node->next != NULL)
                node->next->prev = node;
            delete tmp;
        }

        return this;
    }

    Node* insertBefore(Node* node, T newData)
    {
        if (node == NULL)
            return this;
        Node* tmp = new Node();
        tmp->data = newData;
        tmp->next = node;
        tmp->prev = node->prev;
        node->prev = tmp;
        if (tmp->prev == NULL)
            return tmp;
        tmp->prev->next = tmp;
        return this;
    }

    Node* removeNode(Node* node)
    {
        if (node == NULL)
            return this;
        if (node->next != NULL)
            node->next->prev = node->prev;
        if (node->prev == NULL)
        {
            Node* tmp = node->next;
            delete node;
            return tmp;
        }
        node->prev->next = node->next;
        delete node;
        return this;
    }

    Node* removeFirst()
    {
        return removeNode(this);
    }

    Node* removeLast()
    {
        Node* last = getLast();
        return removeNode(last);
    }
};