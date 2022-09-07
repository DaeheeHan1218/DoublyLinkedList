// implementation of the DLList class

#include "DLList.h"
#include <stdexcept>

using namespace std;


DLList::DLList(){
	DLListNode dl;
	header = dl;
	trailer = dl;
	header.next = &trailer;
	trailer.prev = &header;
}

DLList::DLList(const DLList& dll){
	if(dll.header.next == &dll.trailer){//check if empty
		DLListNode dl;
		header = dl;
		trailer = dl;
		header.next = &trailer;
		trailer.prev = &header;
	}
	else{
		header.next = new DLListNode();
		header.next->obj = dll.header.next->obj;
		header.next->prev = &header;
		DLListNode* temp = header.next;
		DLListNode* cpyTemp = dll.header.next->next;
		while(cpyTemp != &dll.trailer){
			temp->next = new DLListNode();
			temp->next->obj = cpyTemp->obj;
			temp->next->prev = temp;
			cpyTemp = cpyTemp->next;
			temp = temp->next;
		}
		trailer.prev = temp;
		temp->next = &trailer;
	}
} // copy constructor
DLList::DLList(DLList&& dll){
	DLListNode dl;
	header = dl;
	trailer = dl;
	header.next = dll.header.next;
	dll.header.next->prev = &header;
	trailer.prev = dll.trailer.prev;
	dll.trailer.prev->next = &trailer;
	dll.header.next = &dll.trailer;
	dll.trailer.prev = &dll.header;
} // move constructor
DLList::~DLList(){
	DLListNode *temp = header.next;
	while(temp != &trailer){
		DLListNode *del = temp;
		temp = temp->next;
		delete del;
	}
	DLListNode dl;
	header = dl;
	trailer = dl;
	header.next = &trailer;
	trailer.prev = &header;
}// destructor
DLList& DLList::operator=(const DLList& dll){
	if(this != &dll){
		DLListNode *temp = header.next;//delete before copy
		while(temp != &trailer){
			DLListNode *del = temp;
			temp = temp->next;
			delete del;
		}
		DLListNode dl;
		header = dl;
		trailer = dl;
		if(dll.header.next != &dll.trailer){//check if not empty
			header.next = new DLListNode();
			header.next->obj = dll.header.next->obj;
			header.next->prev = &header;
			temp = header.next;
			DLListNode* cpyTemp = dll.header.next->next;
			while(cpyTemp != &dll.trailer){
				temp->next = new DLListNode();
				temp->next->obj = cpyTemp->obj;
				temp->next->prev = temp;
				cpyTemp = cpyTemp->next;
				temp = temp->next;
			}
			trailer.prev = temp;
			temp->next = &trailer;
		}
    }
    return *this;
} // copy assignment operator
DLList& DLList::operator=(DLList&& dll){
	if(this != &dll){
		DLListNode dl;
		header = dl;
		trailer = dl;
		header.next = dll.header.next;
		dll.header.next->prev = &header;
		trailer.prev = dll.trailer.prev;
		dll.trailer.prev->next = &trailer;
		dll.header.next = &dll.trailer;
		dll.trailer.prev = &dll.header;
	}
	return * this;
} // move assignment operator
// return the pointer to the first node (header's next)
DLListNode* DLList::first_node() const{
	return header.next;
}
// return the pointer to the trailer
const DLListNode *DLList::after_last_node() const{
	return &trailer;
}
// return if the list is empty
bool DLList::is_empty() const{
	return (header.next == &trailer);
}
int DLList::first() const{
	return header.next->obj;
} // return the first object
int DLList::last() const{
	return trailer.prev->obj;
} // return the last object
void DLList::insert_first(int obj){
	DLListNode* ins = new DLListNode();
	ins->obj = obj;
	ins->prev = &header;
	header.next->prev = ins;
	ins->next = header.next;
	header.next = ins;
} // insert to the first node
int DLList::remove_first(){
	if(header.next == &trailer){
		throw std::invalid_argument( "remove called on empty list" );
	}
	DLListNode* del = header.next;
	del->next->prev = &header;
	header.next = del->next;
	int ret = del->obj;
	delete del;
	return ret;
} // remove the first node
void DLList::insert_last(int obj){
	DLListNode* ins = new DLListNode();
	ins->obj = obj;
	ins->prev = trailer.prev;
	ins->next = &trailer;
	trailer.prev->next = ins;
	trailer.prev = ins;
} // insert to the last node
int DLList::remove_last(){
	if(header.next == &trailer){
		throw std::invalid_argument( "remove called on empty list" );
	}
	DLListNode* del = trailer.prev;
	del->prev->next = &trailer;
	trailer.prev = del->prev;
	int ret = del->obj;
	delete del;
	return ret;
} // remove the last node
void DLList::insert_after(DLListNode &p, int obj){
	DLListNode* ins = new DLListNode();
	ins->obj = obj;
	ins->prev = &p;
	ins->next = p.next;
	p.next->prev = ins;
	p.next = ins;
}
void DLList::insert_before(DLListNode &p, int obj){
	DLListNode* ins = new DLListNode();
	ins->obj = obj;
	ins->next = &p;
	ins->prev = p.prev;
	p.prev->next = ins;
	p.prev = ins;
}
int DLList::remove_after(DLListNode &p){
	if(header.next == &trailer){
		throw std::invalid_argument( "remove called on empty list" );
	}
	if(&p != trailer.prev){
		DLListNode* del = p.next;
		del->next->prev = &p;
		p.next = del->next;
		int ret = del->obj;
		delete del;
		return ret;
	}
	else{
		throw std::invalid_argument( "remove_after has last node as parameter" );
	}
}
int DLList::remove_before(DLListNode &p){
	if(header.next == &trailer){
		throw std::invalid_argument( "remove called on empty list" );
	}
	if(&p != header.next){
		DLListNode* del = p.prev;
		del->prev->next = &p;
		p.prev = del->prev;
		int ret = del->obj;
		delete del;
		return ret;
	}
	else{
		throw std::invalid_argument( "remove_before has first node as parameter" );
	}
}

// output operator
ostream& operator<<(ostream& out, const DLList& dll){
	DLListNode* temp = dll.first_node();
	while(temp != dll.after_last_node()){
		out << temp->obj << ", ";
		temp = temp->next;
	}
	return out;
}