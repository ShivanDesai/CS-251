#include "clist.h"
#include <iostream>
#include <stdexcept>
using namespace std;

CircleList::CircleList() { //DONE
	header = new CNode;
	header->next = header;
	header->prev = header;
	_size = 0;
}

CircleList::~CircleList() { //DONE
	while(!empty())	removeFront();
	delete header;
}

bool
CircleList::empty() const { //DONE
	if(_size == 0)	return true;
	else		return false;
}

const Elem&
CircleList::front() const { //DONE
	if(_size == 0)	throw std::out_of_range("List is empty");
	return header->next->elem;
}

const Elem&
CircleList::back() const { //DONE
	if(_size == 0)	throw std::out_of_range("List is empty");
	CNode * cn = header;
	while(cn->next != header){
		cn = cn->next;
	}
	return cn->elem;
}

void 
CircleList::add(CNode * v, const Elem& e) { //DONE
	CNode * u = new CNode;
	u->elem = e;
	u->next = v;
	u->prev = v->prev;
	v->prev->next = u;
	v->prev = u;
	_size++;
}

void
CircleList::addFront(const Elem& e) { //DONE
	if(_size == 0){
		CNode * u = new CNode;
		u->elem = e;
		header->next = u;
		u->prev = header;
		header->prev = u;
		u->next = header;
		_size++;
		return;
	}
	add(header->next, e);
}

void
CircleList::addBack(const Elem& e) { //DONE
	if(_size == 0){
		addFront(e);
		return;
	}
	CNode * u = new CNode;
	u->elem  = e;
	CNode * cn = header->next;
	while(cn->next != header)
		cn = cn->next;
	cn->next = u;
	u->prev = cn;
	u->next = header;
	header->prev = u;
	_size++;
}

void
CircleList::remove(CNode * v) { //DONE
	if(_size == 0)	throw std::out_of_range("List is empty");
	CNode * u = v->prev;
	CNode * w = v->next;
	u->next = w;
	w->prev = u;
	_size--;
	delete v;
}

void
CircleList::removeFront() { //DONE
	if(_size == 0)	throw out_of_range("List is empty");
	remove(header->next);
}

void
CircleList::removeBack() {//DONE
	if(_size == 0)	throw out_of_range("List is empty");
	CNode * cn = header->next;
	while(cn->next != header)
		cn = cn->next;
	CNode * u = cn;
	cn->prev->next = header;
	_size--;
	delete u;

}

void
CircleList::clear() { //DONE
	CNode * cn = header->next;
	while(cn->next != header){
		CNode * u = cn;
		cn = cn->next;
		delete u;
	}
	delete cn;
	_size = 0;
}

Elem&
CircleList::operator [] (int i) const{ //DONE
	/*if(i > _size - 1)	throw out_of_range("List is empty");*/
	CNode * cn = header->next;
	int counter = 0;
	if(i >= 0){
		counter = 0;
		while(counter != i){
			cn = cn->next;
			if(cn == header)	cn = cn->next;
			counter++;
		}

		return cn->elem;
	}
	else{
		counter = -1;
		while(counter != i){
			cn = cn->prev;
			if(cn == header)	cn = cn->prev;
			counter--;
		}

		return cn->elem;
	}
}

void
CircleList::setElemAt (int i, const Elem newElem) const{ //DONE
	if(i > _size - 1)	throw out_of_range("List is empty");
	CNode * cn = header->next;
	int counter = 0;
	while(counter != i){
		cn = cn->next;
		counter++;
	}
	if(counter == i)
		cn->elem = newElem;
}

void
CircleList::print() const {
	if(_size == 0)	throw out_of_range("List is empty");
	CNode * cn = header->next;
	while(cn != header){
		cout<<cn->elem.getX()<<","<<cn->elem.getY();
		cn = cn->next;
	}
}

void
CircleList::addAt(int i, const Elem& e) {
	if(i > (_size - 1))	throw out_of_range("List is empty");
	CNode * cn = header->next;
	CNode * node = new CNode;
	node->elem = e;
	int counter = 0;
	while(counter != i){
		cn = cn->next;
		counter++;
	}
	if(counter == i){
		node->prev = cn->prev;
		node->next = cn;
		cn->prev->next = node;
		cn->prev = node;
		_size++;
	}
}

void
CircleList::removeAt(int i) {
	if(i > (_size - 1))	throw out_of_range("List is empty");
	CNode * cn = header->next;
	int counter = 0;
	while(counter != i){
		cn = cn->next;
		counter++;
	}
	if(counter == i){
		cn->next->prev = cn->prev;
		cn->prev->next = cn->next;
		delete cn;
		_size--;
	}
}
