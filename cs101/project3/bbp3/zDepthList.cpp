#include<iostream>
using namespace std;

struct node {
	int name;
	node *next;
	node *prev;
};

class zDepthList {
	private:
		node *head;
		node *tail;
		node *removedNode;
		node** lookup;
		int size;
		
	public:
		zDepthList() {
			head = NULL;
			tail = NULL;
			removedNode = NULL;
		}
		
		zDepthList(int arr[], int length) {
			lookup = new node *[length];
			size = length;
			
			node *first = new node;
			first->name = arr[0];
			first->next = NULL;
			first->prev = NULL;
			
			head = first;
			tail = first;
			
			lookup[first->name] = new node;
			lookup[first->name] = first;
			
			for(int i = 1; i < length; i++) {
				node *temp = new node;
				temp = append(arr[i]);
				lookup[arr[i]] = new node;
				lookup[arr[i]] = temp;
			}
			
			return;
		}
		
		node* append(int data) {
			node *newNode = new node;
			newNode->name = data;
			
			tail->next = newNode;
			newNode->prev = tail;
			
			tail = newNode;
			
			return newNode;
		}
		
		void out(char dir = 'f') {
			if (dir == 'r') {
				printBackward();
			}
			else {
				printForward();
			}
		}
		
		void move(int index, int dist, char dir = 'f') {
			int count = 0;
			node *current = new node;
			node *previous = new node;
			node *temp = new node;
			current = lookup[index];
			
			temp = current;
			current->prev->next = current->next;
			current->next->prev = current->prev;
			
			if (dir == 'r') {
				while (count != dist + 1) {
					if (current == head) {
						temp->next = head;
						temp->prev = NULL;
						head->prev = temp;
						head = temp;
						
						return;
					}
					
					previous = current;
					current = current->prev;
					count++;
				}
				
				temp->next = previous;
				temp->prev = current;
				current->next = temp;
				previous->prev = temp;
			}
			else {
				while (count != dist + 1) {
					if (current == tail) {
						temp->next = NULL;
						temp->prev = tail;
						tail->next = temp;
						tail = temp;
						
						return;
					}
					
					previous = current;
					current = current->next;
					count++;
				}
				
				temp->next = current;
				temp->prev = current->prev;
				previous->next = temp;
				current->prev = temp;
			}
			
			return;
		}
		
		void movefront(int index) {
			node *current = new node;
			current = lookup[index];
			
			current->next->prev = current->prev;
			current->prev->next = current->next;
			
			current->next = head;
			current->prev = NULL;
			head->prev = current;
			head = current;
		}
		
		void moveback(int index) {
			node *current = new node;
			current = lookup[index];
			
			current->next->prev = current->prev;
			current->prev->next = current->next;
			
			current->next = NULL;
			current->prev = tail;
			tail->next = current;
			tail = current;
		}
		
		int at(int index) {
			node *current = new node;
			current = head;
			
			int count = 0;
			while (count != index) {
				current = current->next;
				count++;
			}
			
			return current->name;
		}
		
		void del(int index) {
			node *deleted = new node;
			deleted = lookup[index];
			
			removedNode = deleted;
			
			if (deleted == head) {
				head = deleted->next;
			}
			else {
				deleted->prev->next = deleted->next;
			}
			if (deleted == tail) {
				tail = deleted->prev;
			}
			else {
				deleted->next->prev = deleted->prev;
			}
			
			lookup[index] = NULL;
			
			return;
		}
		
		int addback() {
			if (removedNode != NULL) {
				node *temp = append(removedNode->name);
				lookup[temp->name] = temp;
				removedNode = NULL;
				return temp->name;
			}
			else {
				return -1;
			}
		}
		
		void printForward() {
			node *current = head;
			while (current != NULL) {
				cout<<current->name<<" ";
				current = current->next;
			}
			cout<<endl;
			return;
		}
		
		void printBackward() {
			node *current = tail;
			while (current != NULL) {
				cout<<current->name<<" ";
				current = current->prev;
			}
			cout<<endl;
			return;
		}
		
		//no idea if this works
		zDepthList split(int index, zDepthList &list) {
			node *second = new node;
			
			node** arr = new node *[size];
			
			second = lookup[index]->next;
			list.head = second;
			list.tail = tail;
			tail = second->prev;
			tail->next = NULL;
			second->prev = NULL;
			
			while (second != NULL) {
				arr[second->name] = new node;
				arr[second->name] = second;
				lookup[second->name] = NULL;
				second = second->next;
			}
			
			list.lookup = arr;
			
			return list;
		}
		
		//no idea if this works
		void combine(zDepthList &list) {
			node *oldTail = new node;
			oldTail = tail;
			tail->next = list.head;
			list.head->prev = tail;
			tail = list.tail;
			
			delete[] lookup;
			int length = size + list.size;
			node** tmp = new node *[length];
			
			node *current = new node;
			current = head;
			
			int count = 0;
			while (current != oldTail->next) {
				cout<<"current: "<<current->name<<endl;
				tmp[current->name] = new node;
				tmp[current->name] = current;
				current = current->next;
			}
			while (current != NULL) {
				cout<<"current: "<<current->name<<endl;
				cout<<"tmp[name]: "<<tmp[current->name]<<endl;
				if (tmp[current->name] != current) {
					tmp[current->name] = new node;
					tmp[current->name] = current;
					current = current->next;
				}
				else {
					del(current->name);
				}
			}
			
			lookup = tmp;
		}
};
