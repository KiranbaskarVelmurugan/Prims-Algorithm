#include<iostream.h>
#include<conio.h>

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
			return 1;
		}
		else {
			node *n = new node;
			n->number = x;
			node *next_element = n->next; //The next node to the one with x as a member in the original linked list
			next_element->prev = n;
			search->next = n;
			n->next = next_element;
			n->prev = search;
			return 1;
		}
	}

	int delElement(int x) {
		if (front == NULL) {
			cout<<"Underflow!";
			return -1;
		}

		node *temp = front;
		while(temp->next != NULL) {
			if(temp->number == x) {
				cout<<"Removing "<<x;
				node *d = temp;
				node *p = temp->prev;
				node *n = temp->next;
				p->next = n;
				n->prev = p;
				delete temp;
				length--;
				break;
			}
			else {
				cout<<"Element "<< x <<" not found!";
			}
		}
	} 
};


void main() {
}
