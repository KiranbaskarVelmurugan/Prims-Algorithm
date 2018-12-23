#include <iostream.h>
#include <fstream.h>
#include <conio.h>

struct node {
	int number;
	node *next;
	node *prev;
};

class Doubly_Linked_list {
	node *front, *rear;
	int length;
public:
	Doubly_Linked_list() {
		front = rear = NULL;
		length = 0;
	}

	void pushBack(int x) {
		node *n = new node;
		n->number = x;
		if(front == NULL) {
			front = rear = n;
			n->next = NULL;
			n->prev = NULL;
		}
		else {
			rear->next = n;
			n->prev = rear;
			n->next = NULL;
			rear = n;
		}
		++length;
	}

	void pushFront(int x) {
		node *n = new node;
		n->number = x;
		if(front == NULL) {
			front = rear = n;
			n->next = NULL;
			n->prev = NULL;
		}
		else {
			front->prev = n;
			n->next = front;
			n->prev = NULL;
			front = n;
		}
		++length;
	}

	int addAfter(int x) {
		node *search = front;
		while(search->next != NULL && search->number != x);
		if(search->number != x) {
			cout<< "Node not found!";
			return -1;
		}
		else if(search->number == x && search->next == NULL) {
			pushBack(x);
		}
		else {
			node *n = new node;
			n->number = x;
			node *next_element = search->next; //The next node to the one with x as a member in the original linked list
			next_element->prev = n;
			search->next = n;
			n->next = next_element;
			n->prev = search;
		}
		++length;
		return 1;
	}

	addBefore(int x) {
		node *search = front;
		while(search->next != NULL && search->number != x);
		if(search->number != x) {
			cout<< "Node not found!";
			return -1;
		}
		else if(search->number == x && search->prev == NULL) {
			pushFront(x);
		}
		else {
			node *n = new node;
			n->number = x;
			node *prev_element = search->prev; //The previous node to the one with x as a member in the original linked list
			prev_element->next = n;
			search->prev = n;
			n->prev = prev_element;
			n->next = search;
		}
		++length;
		return 1;
	}

	int delNode(int x) {
		if (front == NULL) {
			cout<<"Underflow!";
			return -1;
		}
		node *temp = front;
		while(temp->next != NULL) {
			if(temp->number == x) {
				cout<<"Removing "<<x;
				node *p = temp->prev;
				node *n = temp->next;
				p->next = n;
				n->prev = p;
				delete temp;
				--length;
				return 1;
			}
		}
		cout<<"Node not found!";
		return -1;
	} 
};

class Location {
	char name[30];
	int id;
	long int least_distance_away;
	static int assignid = 0;
public:
	Location(char a[]) {
		strcpy(name,a);
		least_distance_away = 9999;
		id = assignid;
		++assignid;
	}

	void getDetails() {
		cout<<"Location name: ";
		puts(name);
		cout<<"Id: "<<id;
	}
};


void main() {
}
