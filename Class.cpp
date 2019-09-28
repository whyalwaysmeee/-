#include <iostream>
#include "utility.h"
#include "Class.h"
#include "copyright1.h"

using namespace std;


Train::Train()
{
    train_id = 0;
	route = new List<int*>();
	arriving_time = new List<int*>();
	request_list = new List<Request*>();
}

void Train::set_request_list(Request* r)
{
	request_list->Append(r);
}

List<Request*>* Train::get_request_list()
{
	return request_list;
}

List<Bitmap*>* Train::get_bseat()
{
	return business_seat;
}

List<Bitmap*>* Train::get_cseat()
{
	return coach_seat;
}

void Train::generate_bseat(int i)
{  
	List<Bitmap*>* a = new List<Bitmap*>();
	for (int j = 0; j < i; j++)
	{
		Bitmap *b = new Bitmap(20);
		a->Append(b);
	}
	business_seat = a;
}

void Train::generate_cseat(int i)
{
	List<Bitmap*>* a = new List<Bitmap*>();
	for (int j = 0; j < i; j++)
	{
		Bitmap* b = new Bitmap(40);
		a->Append(b);
	}
	coach_seat = a;
}

List<int*>*Train::get_route()
{
	return route;
}

void Train::build_route(int *a)
{
	route->Append(a);
}


void Train::set_train_id(int i)
{
	train_id = i;
}
int Train::get_train_id()
{
	return train_id;
}


List<int*>*Train::get_arriving_time()
{
	return arriving_time;
}

void Train::insert_arriving_time(int* i)
{
	arriving_time->Append(i);
}


Request::Request()
{
	 request_id = 0;
	 numberofpassenger = 0;
	 request_class = 0;
	 departure_time = 0;
	 destination_station = 0;
	 departure_station = 0;
	 request_status = 0;
	 selected_train_id = 0;
}
int Request::get_selected_train_id()
{
	return selected_train_id;
}
void Request::set_train_id(int i)
{
	selected_train_id = i;
}

void Request::set_request_class(int c)
{
	request_class = c;
}
void Request::set_request_id(int i)
{
	request_id = i;
}

void Request::set_number(int n)
{
	numberofpassenger = n;
}

void Request::set_departure_time(int d)
{
	departure_time = d;
}

void Request::set_destination_station(int d)
{
	destination_station = d;
}

void Request::set_departure_station(int d)
{
	departure_station = d;
}

void Request::set_request_status(int s)
{
	request_status = s;
}
int Request::get_request_id()
{
	return request_id;
}

int Request::get_numberofpassenger()
{
	return numberofpassenger;
}

int Request::get_departure_time()
{
	return departure_time;
}

int Request::get_departure_station()
{
	return departure_station;
}

int Request::get_destination_station()
{
	return destination_station;
}

int Request::get_request_status()
{
	return request_id;
}

int Request::get_request_class()
{
	return request_class;
};

Stats::Stats()
{

}

void Stats::get_granted_request(int c)
{
	cout << "The number of granted requests is: " << c << endl;
}

void Stats::get_refused_request(int c)
{
	cout << "The number of refused requests is: " << c << endl;
}

void Stats::get_all_requests(int c)
{
	cout << "The number of all the requests is : " << c << endl;
}

void Stats::get_all_granted_requests(int c)
{
	cout << "The number of all the granted requests is: " << c << endl;
}

void Stats::get_number_of_passengers(List<Request*>* a)
{
	int total_passengers = 0;
	ListIterator<Request*> iter(a);
	for (; !iter.IsDone(); iter.Next())
	{
		total_passengers = total_passengers + iter.Item()->get_numberofpassenger();
	}
	cout << "The total number of passengers is: " << total_passengers << endl;

}

