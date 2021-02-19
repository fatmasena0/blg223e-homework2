#include <iostream>
#include <cstdlib>
#include <fstream>

using namespace std;

struct resistor{
	char group;
	float value;
	int quantity;
    resistor* next;
};

struct circuit{
	struct resistor *head;
	void create();
	void add_resistor(char, float);
	void remove_resistor(char, float);
	void delete_resistor(struct resistor*);
	float total_resistance();
	void clear();
};

void circuit::create(){
	head = NULL;
}

void circuit::add_resistor(char group, float value){
	resistor* point = head;
	resistor* new_node = new resistor;
	new_node->next = NULL;

	if (head == NULL)
	{
		new_node->group = group;
		new_node->value = value;
		new_node->quantity = 1;
		head = new_node;
	}
	else if (point->group > group)
		{
		new_node->next = point;
		new_node->value = value;
		new_node->quantity = 1;
		new_node->group = group;
        head = new_node;
		}
	else if (point->group == group){
		point->quantity++;
	}
    else if(point->next == NULL && point->group<group)
    {
        point->next = new_node;
        new_node->group = group;
        new_node->value = value;
		new_node->quantity = 1;
    }
    else {
        while (point->next != NULL)
        {
            if (point->next->group > group)
            {
                new_node->next = point->next;
                point->next = new_node;
                new_node->value = value;
                new_node->quantity = 1;
                new_node->group = group;
                break;
            }
            else if (point->next->group == group)
            {
                point->next->quantity++;
                break;
            }
            point = point->next;

            if (point->next == NULL && point->group<group)
            {
            point->next = new_node;
            new_node->group = group;
            new_node->value = value;
            new_node->quantity = 1;
            break;

            }
        }
    }
}

void circuit::remove_resistor(char group, float value){

	resistor* point = head;

	if (head == NULL){
		cout<<"NO_RESISTOR"<<endl;
		return;
	}
	else if (point->group == group)
	{
		if (point->quantity == 1)
		{
			head = point->next;
            circuit del;
            del.delete_resistor(point);
			return;
		}
		else
		{
			point->quantity--;
			return;
		}
	}
	if (point->next == NULL)
    {
		cout<<"NO_RESISTOR"<<endl;
		return;
    }
    resistor* tail = point->next;

	while ((tail->next != NULL) && (tail->group != group))
	{
		tail = tail->next;
		point = point->next;
	}
	if (tail->group != group)
	{
		cout<<"NO_RESISTOR"<<endl;
	}
	else if (tail->group == group && tail->quantity == 1)
	{
		point->next = tail->next;
        circuit del;
        del.delete_resistor(tail);
	}
	else
	{
		tail->quantity--;
	}
}

void circuit::delete_resistor(struct resistor* point){
    delete point;
}

float circuit::total_resistance(){        //to calculate total resistance
    resistor* point = head;
    float total = 0;
	while (point != NULL)
	{
        total = total + (point->value / point->quantity);
        point = point->next;
	}
	return total;
}

void circuit::clear(){
	resistor* point;
	while(head){
		point = head;
		head = head->next;
		delete point;
	}
}


struct values{
    float value;
    int quantity;
    values* next;
};

struct list2{                            //second linked list in order to calculate total resistance
    struct values *head_value;
    void create();
    void add_value(float);
    void remove_value(float);
	void circuit_info();                    			//workflow 3
	void clear();                           		 	//workflow 4
};

void list2::create(){
	head_value = NULL;
}

void list2::add_value(float value){     //the function adds to list according to resistors' value

    values * point = head_value;
	values * new_node = new values;
	new_node->next = NULL;

    if (head_value == NULL)
    {
        new_node->value = value;
		new_node->quantity = 1;
		head_value = new_node;
    }
    else if (point->value > value)
    {
		new_node->next = head_value;
		head_value = new_node;
		new_node->value = value;
		new_node->quantity = 1;
    }
	else if (point->value == value)
    {
		point->quantity++;
    }
    else if(point->next == NULL && point->value < value)
    {
        head_value->next = new_node;
        new_node->value = value;
		new_node->quantity = 1;
    }
    else{
        while (point->next != NULL)
            {
            if (point->next->value > value)
                {
                new_node->next = point->next;
                point->next = new_node;
                new_node->value = value;
                new_node->quantity = 1;
                break;
                }
            else if (point->next->value == value)
                {
                point->next->quantity++;
                break;
                }
            point = point->next;
            if (point->next == NULL && point->value<value)
                {
                point->next = new_node;
                new_node->value = value;
                new_node->quantity = 1;
                break;
                }
            }

        }
}

void list2::remove_value(float value){
	values * point = head_value;

    if (point->value == value)
	{
		if (point->quantity == 1)
		{
        head_value = point->next;
			delete point;
			return;
		}
		else
		{
			point->quantity--;
			return;
		}
	}
	values * tail = point->next;

	while ((tail->next != NULL) && (tail->value != value))
	{
	    tail = tail->next;
		point = point->next;
	}
    if (tail->value != value && tail->next == NULL){
        return;
    }
	else if (tail->value == value && tail->quantity == 1)
	{
        point->next = tail->next;
		delete tail;
	}
	else
	{
		tail->quantity--;
	}
}

void list2::circuit_info(){             //value of resistors and number of resistors
	values * point = head_value;
	while (point != NULL)
	{
		cout<<point->value<<":"<<point->quantity<<endl;
		point = point->next;
	}
}

void list2::clear(){
	values * point;
	while(head_value){
		point = head_value;
		head_value = head_value->next;
		delete point;
	}
}


int main(int argc, char **argv){
	circuit resistor_circuit;
	list2 resistor_value;
	resistor_circuit.create();
	resistor_value.create();

	ifstream input(argv[1]);
    if(!input.is_open()){
		cerr<<"failed to open file"<<endl;
	}
	char g;
	float v;

	while (input>>g>>v)
    {
        if (g=='A' && v==0)
        {
            resistor_value.circuit_info();
            cout << "Total resistance=" <<resistor_circuit.total_resistance()<<" ohm"<<endl;
        }
        else if (v > 0)
        {
            resistor_circuit.add_resistor(g, v);
            resistor_value.add_value(v);
        }
        else if (v < 0)
        {
            resistor_circuit.remove_resistor(g, -v);
            resistor_value.remove_value(-v);
        }
    }

    resistor_circuit.clear();
    resistor_value.clear();
    input.close();

    return 0;
}



