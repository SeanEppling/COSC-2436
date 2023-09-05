#ifndef PQUEUE_H
#define PQUEUE_H
#include <iostream>
#include <vector>
using namespace std;

struct link {
	string func;
	vector<string> vals;
	int prio;
	link* next;
};

class PQueue {
private:
	link* front;
public:
	PQueue() { front = nullptr; }
	void enq(link* temp) {
		temp->next = nullptr;
		PQueue q;
		link* curr = front;
		if (front == nullptr) {
			front = temp;
		}
		else if (front->prio > temp->prio) {
			temp->next = front;
			front = temp;
		}
		else {
			while (curr->next != nullptr && curr->next->prio <= temp->prio) {
				curr = curr->next;
			}
			temp->next = curr->next;
			curr->next = temp;
		}
	}
	link* deq() {
		link* temp = front;
		front = front->next;
		return temp;
	}
	bool empty() {
		return (front == nullptr);
	}
};

#endif
