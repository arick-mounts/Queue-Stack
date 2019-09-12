#include <iostream>
#include<string>
#include <fstream>

/*
 *This program reads data from a .csv and loads it into two linked list of 'product' structs, 
 *organized as a queue and a stack
 *
 *Data Structures @ TCC
 *
 *Arick Mounts
 */

using namespace std;
//defining struts
struct product {
  string name;
  double price;
  int amount;
};

struct node{
  product item;
  node* next;
};


void printList(struct node * n);
string printNode(struct node * n);
struct node * createNode(string name, double price, int num);
struct node * pop(struct node * list);
struct node * push(struct node * list, struct node* new_node);
struct node * enqueue(struct node * list, struct node* new_node);
struct node * dequeue(struct node * list);
product createProduct (string name, double price, int num);


int main() {
  struct node * list = NULL;
  string name;
  double price;
  int num;
  fstream inputF("project_04_data.csv", fstream::in);
  getline(inputF, name);

  cout <<endl<<  "1. Reading fle and populating stack:" <<endl << endl;
  while(getline(inputF ,name, ',')){
      string inS;
      getline(inputF,inS, ',');
      price = stod(inS);
      getline(inputF, inS, '\n');
      num = stoi(inS);
      struct node * n = createNode(name, price, num);
      list = push(list, n);
    }
  cout <<endl <<"2. Printing full stack: " << endl;
  printList(list);

  cout << endl << "3. Pop from stack: " << endl <<endl;
  while (list != NULL){
    list = pop(list);
  }

  cout <<endl<<  "4. Printing stack after popping: " << endl;
  printList(list);
  inputF.close();
  fstream inputFtwo("project_04_data.csv", fstream::in);
  getline(inputFtwo, name);
  
  cout << endl << "5. Read file and populating queue" << endl;;
  while(getline(inputFtwo ,name, ',')){
      string inS;
      getline(inputFtwo,inS, ',');
      price = stod(inS);
      getline(inputFtwo, inS, '\n');
      num = stoi(inS);
      struct node * n = createNode(name, price, num);
      list = enqueue(list, n);
    }

  cout <<endl<<  "6. Printing full queue: " << endl;
  printList(list);

  cout << endl << "7. Dequeue: " << endl;
  while (list!=NULL){
    list = dequeue(list);

  }
   cout << endl << "8. Queue after dequeueing: " << endl;
  printList(list);

  inputFtwo.close();
}

//Iterates through a linked list and prints the name variable of the node's item structure.
void printList(struct node * n){
  
  
    cout << endl << "Position        Name" << endl;

  if (n != NULL){
    int num =0;
    while (n){  
      
      cout << num << ":     " << n->item.name << endl;
      num++;
      n = n->next;
    }
  }else{
    cout << "List is empty" << endl;
  }
}

//Adds node's to the linked list queue
struct node * enqueue(struct node * list, struct node* new_node){
  cout << "Enqueue: " << new_node->item.name<< endl;
  new_node->next = list;
  return new_node;
}

//Removes nodes from the linked list queue
struct node * dequeue(struct node * list){
  struct node* start_of_list = list;
  struct node* previous_node = NULL;
  if(!list){
    return NULL;
  }else{
    if (list->next == NULL){
      
    cout << "Dequeue: " << list->item.name << endl;
      delete(list);
      return NULL;
    }else{
      while (list->next){
        previous_node = list;
        list = list->next;
      }
      previous_node->next = NULL;
      cout << "Dequeue: " << list->item.name << endl;
      delete( list);
      return start_of_list;
    }

  }
}

//Pushes nodes onto the linked list stack
struct node * push(struct node * list, struct node* new_node){
  cout << "Push: " << new_node->item.name<< endl;
  new_node->next = list;
  return new_node;
}

//Pops nodes off of the linked list stack
struct node * pop(struct node * list){
  if(!list){
    return NULL;
  }else{
    cout << "Pop: " << list->item.name << endl;
    if (list->next == NULL){
      delete(list);
      return NULL;
    }else{
      struct node * temp = list->next;
      delete( list);
      return temp;
    }

  }
}

//Creates node, and takes values with which to build the associated product
struct node * createNode(string name, double price, int num){
  struct node * new_node = (struct node *) new(struct node);
  struct product pro ={ name, price, num};
  new_node->item =  pro;
  new_node->next = NULL;
  return new_node;
}
