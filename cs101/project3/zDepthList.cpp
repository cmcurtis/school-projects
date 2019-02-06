using namespace std;
#include <iostream>

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
	zDepthList(){
		head = NULL;
		tail = NULL;
		removedNode = NULL;
	}

	zDepthList(int arr[], int length){
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
			append(arr[i]);
		}
	return;
	}

	void out(char dir='f'){
		if (dir == 'r'){
			printBackward();
		}
		else
			printForward();
	return;
	}  

	void move(int index, int dist, char dir='f'){
		int count = 0;
		node *current = new node;
		node *previous = new node;
		node *temp = new node;
		
		current = lookup[index];
		temp = current;
		current->prev->next = current->next;
		current->next->prev = current->prev;
		
		if (dir == 'r'){
			while (count != dist+1){
				if (current == head){
					temp->next = head;
					head->prev = temp;
					temp->prev = NULL;
					head = temp; 
					return;
				}
				previous = current;
				current = current->prev;
				count++;
			}
			temp->prev = current;
			current->next = temp;
			previous->prev = temp;
			temp->next = previous;
		}
		else {
			while (count != dist+1){
				if (current == tail){
					temp->prev = tail;
					tail->next = temp;
					temp->next = NULL;
					tail = temp;
					return;
				}
				previous = current;
				current = current->next;
				count++;
			}
			temp->prev = previous;
			previous->next = temp;
			current->prev = temp;
			temp->next = current;
		}
	return;
	}
	 
	void movefront(int index){
		node *current = new node;
		current = lookup[index];
		
		current->next->prev = current->prev;
		current->prev->next = current->next;
		
		current->next = head;
		head->prev = current;
		current->prev = NULL;
		head = current; 
		
	return;
	}

	void moveback(int index){
		node *current = new node;
		node *previous = new node;
		current = lookup[index];
		previous = current->prev;
		
		current->next->prev = current->prev;
		current->prev->next = current->next;
		
		current->prev = tail;
		tail->next = current;
		current->next = NULL;
		tail = current;

	return;
	}

	int at(int index){
		int count = 0;
		node *current = new node;

		while (count != index){
			current = current->next;
			count++;
		}

	return current->name;
	}

	void del(int index){
		int count = 0;
		node *current = new node;
		node *previous = new node;
		current = lookup[index];
		previous = current->prev;
		
		lookup[current->name] = NULL;
		removedNode = current;
		if (current == head){ 
			head = current->next;
		}
		else {
			current->prev->next = current->next;
		}
		if (current == tail){ 
			tail = current->prev;
		}
		else {
			current->next->prev = current->prev;
		}
	return;
	}

	int addback(){
		if (removedNode != NULL) {
			node *temp = append(removedNode->name);
			lookup[temp->name] = temp;
			removedNode = NULL;
			return temp->name;
		}
	else return -1;
	}

	node* append(int data) {
		node *newNode = new node;
		newNode->name = data;

		tail->next = newNode;
		newNode->prev = tail;

		tail = newNode;
		lookup[data] = new node;
		lookup[data] = newNode;
	return newNode;
	}
	 
	void printForward(){
		node *ptr = head;
		while(ptr != NULL){
			cout << ptr->name << " ";
			ptr = ptr->next;
		}
		cout << endl;
	return;
	} 
	
	void printBackward(){
		node *ptr = tail;
		while(ptr != NULL){
			cout << ptr->name << " ";
			ptr = ptr->prev;
		}
		cout << endl;
	return;
	}

	zDepthList split(int index, zDepthList &newList){
		node *second = new node;
		
		node** arr = new node *[size];

		second = lookup[index]->next;
		newList.head = second;
		newList.tail = tail;
		tail = second->prev;
		tail->next = NULL;
		second->prev = NULL;
		
		while (second != NULL) {
			arr[second->name] = new node;
			arr[second->name] = second;
			lookup[second->name] = NULL;
			second = second->next;	
		}

		newList.lookup = arr;
	return newList;
	}

	void combine(zDepthList list){
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
			tmp[current->name] = new node;
			tmp[current->name] = current;
			current = current->next;
		}
		while (current != NULL) {
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
	return;
	}
};
