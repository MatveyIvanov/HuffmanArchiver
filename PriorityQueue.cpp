#include "PriorityQueue.h"

bool PriorityQueue::isEmpty() { return this->cur_size == 0; }

int PriorityQueue::PARENT(int i) { return (i - 1) / 2; }

int PriorityQueue::LEFT(int i) { return (2 * i + 1); }

int PriorityQueue::RIGHT(int i) { return (2 * i + 2); }

void PriorityQueue::heapify_down(int i) {
	int smallest = i;
	int left = LEFT(i);
	int right = RIGHT(i);

	if (left < this->cur_size && this->heap[left]->get_freq() < this->heap[i]->get_freq())
		smallest = left;
	if (right < this->cur_size && this->heap[right]->get_freq() < this->heap[smallest]->get_freq())
		smallest = right;

	if (smallest != i) {
		swap(this->heap[i], this->heap[smallest]);
		this->heapify_down(smallest);
	}
}

void PriorityQueue::heapify_up(int i) {
	if (i && this->heap[this->PARENT(i)]->get_freq() > this->heap[i]->get_freq()) {
		swap(this->heap[i], this->heap[this->PARENT(i)]);
		this->heapify_up(this->PARENT(i));
	}
}

void PriorityQueue::push(BinaryTree::Node* elem) {
	if (this->cur_size == -1)
		cur_size = 0;
	this->heap[this->cur_size++] = elem;
	int index = this->cur_size - 1;
	this->heapify_up(index);
}

void PriorityQueue::pop() {
	if (this->isEmpty() || this->cur_size == -1)
		throw exception("Priority queue is empty");
	this->heap[0] = this->heap[cur_size - 1];
	cur_size--;
	this->heapify_down(0);
}

BinaryTree::Node* PriorityQueue::top() {
	if (this->isEmpty())
		throw exception("Priority queue is empty");
	return this->heap[0];
}