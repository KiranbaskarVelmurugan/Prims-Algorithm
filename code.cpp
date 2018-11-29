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

	void addElement(int x) { //Elements only added to rear
		node *n = new node;
		n->number = x;
		if(front == NULL) {
			front = rear = n;
			n->next = NULL;
			n->prev = NULL;
		}
		else {
			node *temp = rear;
			temp->next = n;
			n->prev = temp;
			n->next = NULL;
			rear = n;
		}
		length++;
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
				cout<<"Element "<<x<<" not found!";
			}
		}
	} 
};


void main() {
}
