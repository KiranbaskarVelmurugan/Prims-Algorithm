#include <iostream.h>
#include <fstream.h>
#include <conio.h>
#include <stdio.h>
#include <string.h>

const int no_of_locations = 5;
const int size = no_of_locations;

class Location {
public:
	char name[30];
	long int least_distance_away;

	Location () {
	}

	Location(char a[]) {
		strcpy(name,a);
		least_distance_away = 9999;
	}

	void getDetails() {
		cout<<"Location name: ";
		puts(name);
	}
};

int isEqual(Location a, Location b) {
	if(strcmp(a.name, b.name) == 0) {
		return 1;
	}
	return 0;
}

void assignDetails(Location &a, Location &b) {
	strcpy(a.name, b.name);
	a.least_distance_away = b. least_distance_away;
}

struct node {
	Location location;
	node *next;
	node *prev;
};

class Doubly_Linked_list {
public:
	node *front, *rear;
	int length;
	Doubly_Linked_list() {
		front = rear = NULL;
		length = 0;
	}

	void pushBack(Location x) {
		node *n = new node;
		assignDetails(n->location, x);
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

	void pushFront(Location x) {
		node *n = new node;
		assignDetails(n->location, x);
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

	int addAfter(Location x) {
		node *search = front;
		while(search->next != NULL && !isEqual(search->location, x));
		if(!isEqual(search->location, x)) {
			cout<< "Node not found!";
			return -1;
		}
		else if(isEqual(search->location, x) && search->next == NULL) {
			pushBack(x);
		}
		else {
			node *n = new node;
			assignDetails(n->location, x);
			node *next_element = search->next; //The next node to the one with x as a member in the original linked list
			next_element->prev = n;
			search->next = n;
			n->next = next_element;
			n->prev = search;
		}
		++length;
		return 1;
	}

	int addBefore(Location x) {
		node *search = front;
		while(search->next != NULL && !isEqual(search->location, x));
		if(!isEqual(search->location, x)) {
			cout<< "Node not found!";
			return -1;
		}
		else if(isEqual(search->location, x) && search->prev == NULL) {
			pushFront(x);
		}
		else {
			node *n = new node;
			assignDetails(n->location, x);
			node *prev_element = search->prev; //The previous node to the one with x as a member in the original linked list
			prev_element->next = n;
			search->prev = n;
			n->prev = prev_element;
			n->next = search;
		}
		++length;
		return 1;
	}

	int delNode(Location x) {
		if (front == NULL) {
			cout<<"Underflow!";
			return -1;
		}
		if(strcmp(front->location.name, x.name) == 0) {
			node* temp = front;
			front = front->next;
			delete temp;
			--length;
			return 1;
		}
		if(strcmp(rear->location.name, x.name) == 0) {
			node *temp = rear;
			rear = rear->prev;
			delete temp;
			--length;
			return 1;
		}
		node *temp = front;
		while(temp->next != NULL) {
			if(isEqual(temp->location, x)) {
				node *p = temp->prev;
				node *n = temp->next;
				p->next = n;
				n->prev = p;
				delete temp;
				--length;
				return 1;
			}
			temp = temp->next;
		}
		cout<<"Node not found!";
		return -1;
	}
};

int graph[size][size];
char temp[30];
Location places[size];

int indexOfPlace(Location x) {
	for(int i = 0; i < size; i++) {
		if(strcmp(x.name, places[i].name) == 0){
			return i;
		}
	}
	return -1;
}

void getInput() {
	fstream file;
	file.open("input.txt", ios::in);
	int ch = 1;
	while(!file.eof() && ch == 1) {
		for(int i = 0; i < size; i++) {
			file.getline(temp, 30);
			Location loc(temp);//temp is global so it might not get truncated properly
			assignDetails(places[i], loc);
		}
		ch = 0;
		for(int j = 0; j < size; j++) {
			for(int k = 0; k < size; k++) {
				file>>graph[j][k];
			}
		}
	}
	file.close();
}

int isSymmetric(int arr[size][size]) {
	for(int i = 0; i < size; i++) {
		for(int j = i; j < size; j ++) {
			if(arr[i][j] != arr[j][i]) {
				return 0;
			}
		}
	}
	return 1;
}

void PrimsAlg() {
	Doubly_Linked_list list;
	for(int i = 0; i < size; i++) {
		list.pushBack(places[i]);
	}
	while(list.length != 0) {
		int row = indexOfPlace((list.front)->location);
		int indexofmin = 0;
		for(int j = 0; j < size; j++) {
			if(graph[row][j] != 0) {
				if((places[row]).least_distance_away > graph[row][j]) {
					(places[row]).least_distance_away = graph[row][j];
					if(j > 0) {
						graph[row][indexofmin] = 0;
						indexofmin = j;
					}
				}
				else {
					graph[row][j] = 0;
				}
			}
		}
		list.delNode((list.front)->location);
	}
	for(int r = 0; r < size; r++) {
		for(int c = 0; c < size; c++) {
			if(graph[r][c] != 0) {
				graph[c][r] = graph[r][c];
			}
		}
	}
}

void main() {

	getInput();
	
	cout<<"Original Graph: "<<endl<<endl;
	for(int i = 0; i < size; i++) {
		for(int j = 0; j < size; j++) {
			cout<<graph[i][j]<<" ";
		}
		cout<<endl;
	}
	
	if(!isSymmetric(graph)) {
		cout<<"\n Graph is not undirected!";
		system("pause");
		return 0;
	}

	PrimsAlg();
	
	cout<<endl<<"Minimal Spanning Tree: "<<endl<<endl;
	for(int j = 0; j < size; j++) {
		for(int k = 0; k < size; k++) {
			cout<<graph[j][k]<<" ";
		}
		cout<<endl;
	}
}
