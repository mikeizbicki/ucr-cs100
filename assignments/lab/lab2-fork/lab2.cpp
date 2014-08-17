
#include<iostream>

using namespace std;

struct Node{
	Node* next;
	int value;
};

class List{

	public:

		List(): head(0) {}

		void add(int value){
			Node* toAdd = new Node();
			toAdd->value = value;
			if(head == NULL){
				head = toAdd;
				tail = toAdd;
			} else {
				tail->next = toAdd;
				tail = toAdd;
			}
		}

		int removeHead(){

			Node* tmp = head;
			//head = NULL;
			head = head->next;
			int value = tmp->value;
			delete tmp;
			return value;
		}

		int removeTail(){

			if(tail == NULL || head == NULL){
				return 0;	
			}
			
			for(Node* toCheck = head; toCheck->next != NULL; toCheck = toCheck->next){
				if(toCheck->next = tail){
					int num = tail->value;
					delete tail;
					tail = toCheck;
					return num;
				}	

			}
		}

		int getNumNodes(){
			int number = 0; //initialized to zero

			for(Node* toCheck = head; toCheck == tail; toCheck = toCheck->next){
				++number;
			}

			return number;
		}
		
		//added two get functions
		int getHead()
		{
			if (head == NULL)
			{
				return 0;
			}
			return head->value;
		}
		int getTail()
		{
			if (tail == NULL)
			{
				return 0;
			}
			return tail->value;
		}
		
		void printNodes(){			
			for(Node* toCheck = head; toCheck != NULL; toCheck = toCheck->next){
				cout << toCheck->value << endl;
				//changed toCheck != tail to != NULL
			}

		}
		
		int totalValue(){
			int total = 0; //initialize to zero
			for(Node* toCheck = head; toCheck != NULL; toCheck = toCheck->next){
				total += toCheck->value;
			}

			return total;

		}

		void condense(){
			int total = totalValue();
			Node* totalNode = new Node(); //added this
			totalNode->value = total;
			Node* tmp;
			while(head != NULL){
				tmp = head;
				head = head->next;
				
				delete tmp;
			}
			tail = totalNode;
			head = totalNode;	
		}
		
		~List(){

			Node* tmp;
			while(head != NULL){
				tmp = head;
				head = head->next;
				delete tmp;
			}

			tail = NULL;
			head = NULL;		
		}

		Node* head;
		Node* tail;
};


int main(){
	START:
		cout << "Have Fun Debugging!" << endl;
	//goto START; removed this;
	
	int  value;
	cout << "Enter an int:" << endl;
	cin >> value;

	List* l = new List();

	for(int k = 0; k< value; ++k){
		l->add(k);
	}
	
	cout << "Printing!: " << endl;

	l->printNodes();
	
	cout << "Total is: " << l->totalValue() << endl; //changed punctuation

	cout << "Head is: " << l->getHead() << endl;
	
	cout << "Tail is: " << l->getTail() << endl;
	
	cout << "Condensing..." << endl;

	l->condense();

	cout << "Printing!: " << endl;

	l->printNodes();

	return 0;
}
