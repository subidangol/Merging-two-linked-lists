//Ordering and Merging Two Lists Using Linked Lists using C++

#include<iostream>
#include<fstream>
#include<cstdlib>
using namespace std;

//class declaration
class List
{
	public:
		typedef int Item;//data type for the list elements
		List();			 //constructor that initializes the list as empty
		~List();		 //destructor
		
		void empty_list();
		//to clear a selected list
		//postcondition - selected list is empty
		
		int length();
		//to find the number of elements in the list
		//precondition - a list is selected
		//postcondition - the length of the list is returned
		
		void insert(const Item& entry);
		//to insert a given variable in the list in an ascending order without any duplicates
		//precondition - the paramter must be an integer
		//postcondition - the new item is added at an appropriate position
		
		void merge(List& l1, List& l2);
		//merges two lists in ascending order without any duplicates
		//precondition - the two parameters must objects of List class
		//postcondition - the two lists are combined
		
		friend ostream& operator << (ostream& out_s, const List& l);
		//writes elements of lists to output stream by overloading << operator
		
	private:
		struct Node    //data structure for Node
		{
			Item data;
			Node *next;
		};
		Node *first;   //declaring a Node
		
		Node* get_node(Item value, Node* link); 
		//private function to create and initialize a new Node
};

//CONSTRUCTOR
List :: List()
{
	first = NULL; //initializes list as empty
}

//DESTRUCTOR
List :: ~List()
{
	Node *temp; //declaring a Node
	while(first != NULL) //if the first has a node it is pointing to
	{
		temp = first; //temp points to that node
		first = first->next; //first points to the next node
		delete temp; //makes the node unaccessible
	}
}

//MODIFICATION MEMBER FUNCTIONS
void List::empty_list( ) //makes selected list empty
{
	Node* temp;
	while (first != NULL)
	{
		temp = first;
		first = first -> next;
		delete temp;
	}
}

void List :: insert(const Item& entry)
{
	Node *prev, *r; //declare two Nodes
	bool repeated = false; //initialize a bool variable to false
	if(first==NULL || entry < first->data) 
	//if the list is empty or the first element is larger than the entry
		first = get_node(entry, first); //create a Node for that entry in the beginning
	else
	{
		prev = first; //otherwise prev points to where first is pointing
		if(prev->next != NULL) //if we are not in the last node
			if(prev->data == entry || prev->next->data == entry)
			//and if the current or next item is equal to entry
				repeated = true; //assign bool variable as true
		while(prev->next !=NULL && prev->next->data < entry)
		//while we are not in the last node 
		//and next item in smaller than entry
		{
			prev = prev->next; //go to next Node
			if(prev->next != NULL) //if we are not in the last node
				if(prev->next->data == entry) //and if next item is equal to entry
					repeated = true; 
					//assign bool variable as true 
					//so that this item is not repeated again
		}		
		if(!repeated) //if this item is not previously in the list 
			prev->next = get_node(entry, prev->next); 
			//then insert the item before the larger value
	}
}

void List :: merge(List& l1, List& l2)
{
	empty_list(); //clear the pre-existing list
	Node *p1, *p2;; //new Nodes
	p1 = l1.first; //p1 point to the first list
	p2 = l2.first; //p2 points to the second list
	if(l1.first!=NULL) //if the first list is not empty
	{
		for (int i = 0; i < l1.length(); i++) 
		{
			insert(p1->data);  //insert the element into the new list
			if(p1->next!=NULL) //if it is not the final element
				p1 = p1->next; //move the pointer to the next element
		}
	}
	if(l2.first!=NULL) //if second list is not empty
	{
		for (int i = 0; i < l2.length(); i++)
		{
			insert(p2->data);  //insert the element at appropriate position
			if(p2->next!=NULL) //if it is not the final element
				p2 = p2->next; //move the pointer to the next element
		}
	}	
}
	
int List :: length()
{
 	Node *l;   //pointer to track the number of items
	int count; //to count number of items present in a list
	l = first; //points to the first element
	count = 0; //initializing count to zero
	while(l!=NULL) //while the pointer is pointing to a Node
	{
		++count;   //count the node
		l = l -> next; //move to the next node
	}
	return count;      //return total count
}



List :: Node* List :: get_node(Item entry, Node* link)
{
	Node *temp;        //pointer to create and attach a new Node
	temp = new Node;   //points to the the new Node
	temp->data = entry;//assigns value
	temp->next = link; //links the Node to next node
	return temp;       //return the address of new Node
}

ostream& operator << (ostream& out_s, const List& l)
{
    List :: Node *p;
	p = l.first;  
	while(p != NULL) //till we get to the end
	{
		out_s << p->data << ' '; //prints the item of the list
		p = p->next; //move to next Node
	}
    return out_s;
 }
  
int main()
{
	List f1, f2, result; //create three new objects
	ifstream fin; //to read contents of file
	string f1name, f2name; //variables for filenames
	int elem; //for items in the file
	
    cout << "Enter name of the first file: ";
    cin >> f1name;           //gets the filename
	fin.open(f1name.c_str());//opening the file
	if (fin.fail())          //if the file does not exist or is not acceptable
	{
		cout << "Invalid input. Unable to open the file." << endl;
		exit(EXIT_FAILURE);  //stops the program
	}
	if(!fin.isEmpty())
	{
	while(!fin.eof())     
	{
		fin >> elem;
		f1.insert(elem);     
		//inserts all the items of the file in object f1 as a list   
	}
	}
	fin.close();             //closes the file

	cout << "Enter name of the second file: ";
    cin >> f2name;
	fin.open(f2name.c_str());//opening the file
	if (fin.fail())          //if the file does not exist or is not acceptable
	{
		cout << "Invalid input. Unable to open the file." << endl;
		exit(EXIT_FAILURE);  //stops the program
	}
 	while(!fin.eof())
	{
		fin >> elem;
		f2.insert(elem);
		//inserts all the items of the file in object f1 as a list   
	}
	fin.close(); 		     //closes the file

	cout << "There are " << f1.length() << " values in the first list: " << endl << f1 << endl;
    cout << "There are " << f2.length() << " values in the second list: " << endl << f2 << endl;
	//displays the sorted lists
	result.merge(f1, f2); //calls merge function to combine the two lists
	cout << "The merged list contains " << result.length() << " values: " << endl << result << endl;
	//prints out the merged list
}
