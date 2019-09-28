#pragma once
#ifndef CLASS_H
#define CLASS_H

#include "copyright1.h"
#include "header1.h"
#include "utility.h"
#include "header2.h"

class Request
{
private:
	int request_id;
	int request_class;
	int numberofpassenger;
	int departure_time;
	int destination_station;
	int departure_station;
	int request_status;
	int selected_train_id;
public:
	Request();
	void set_train_id(int i);
	int get_selected_train_id();
	void set_request_class(int c);
	void set_request_id(int i);
	void set_number(int n);
	void set_departure_time(int t);
	void set_destination_station(int d);
	void set_departure_station(int d);
	void set_request_status(int s);
	int get_request_id();
	int get_numberofpassenger();
	int get_departure_time();
	int get_destination_station();
	int get_departure_station();
	int get_request_status();
	int get_request_class();
};

class Train
{
private:
	List<int*>* route;
	int train_id;
	List<Bitmap*> *business_seat;
	List<Bitmap*> *coach_seat;
	List<int*>* arriving_time;
	List<Request*> *request_list;
public:
	Train();
	void set_request_list(Request* r);
	List<Request*> *get_request_list();
	List<Bitmap*> *get_bseat();
	List<Bitmap*> *get_cseat();
	void generate_bseat(int i);
	void generate_cseat(int i);
	List<int*>* get_route();
	void build_route(int *a);
	void set_train_id(int i);
	void insert_arriving_time(int* i);
	int get_train_id();
	List<int*>* get_arriving_time();
};

class Stats
{
public:
	Stats();
	void get_granted_request(int c);
    void get_refused_request(int c);
	void get_all_requests(int c);
	void get_all_granted_requests(int c);
	void get_number_of_passengers(List<Request*>* a);
};
#endif

