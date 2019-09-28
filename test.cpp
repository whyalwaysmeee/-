#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include "Cashier.h"
using namespace std;

int main()
{
	List<Request*> requestlist;
	List<Request*>* all_accepted_request = new List<Request*>();
	List<Request*>* all_rejected_request = new List<Request*>();
	List<Train*>* TrainList = new List<Train*>();                     //create a list for storing the trains
	//start to simulate
	for (int t = 0; t < 96; t++)                      //960min from 6am to 10pm, divide it into 96 (10min)s
	{
		if(t==0 or t==1 or t==2 or t==3 or t==4)
		{
			Train* train = new Train();                  //create a new train
			train->set_train_id((t+1) * 1000);                      //give the train an id
			train->generate_bseat(t + 16);                         //generate a list of bitmaps to record the condition of business seats for each interval
			train->generate_cseat(t + 16);                         //generate a list of bitmaps to record the condition of coach seats for each interval
			for (int i = 0; i < t + 16; i++)               
			{
				int* n_num = new int(i);
				train->build_route(n_num);                //give the train a route 
				int* m_num = new int(4 * (*n_num) + t);
				train->insert_arriving_time(m_num);      //give the train a list of arriving time
			}
			TrainList->Append(train);                     //put the train into the train list
		}

		List<Request*>* rejected_request = new List<Request*>();                      //rejected requests list for every 10 minutes
		List<Request*> *accepted_request = new List<Request*>();                      //accepted requests list for every 10 minutes

		for (int i = 0; i < 5; i++)                       //generate 5 new requests
		{
			Request* request = new Request();
			request->set_request_id(t * 1000 + i);           //set a request id
			request->set_number(rand() % 8 + 1);             //set a number of passengers for each request
			int q = rand() % 20 + 0;
			request->set_departure_station(q);                //set a random departure station
			int p = rand() % (21 - q) + (q + 1);
			request->set_destination_station(p);         //set a random destination station
			request->set_departure_time(rand() % (96 - t) + (t + 1));              //set a random departure time
			request->set_request_class(rand() % 2 + 0);                       //set a class of seat,'1' means 'coach' and '0' means 'business'
			requestlist.Append(request);                                      //put the request into a list
			List<Train*> *available_train = new List<Train*>();
			bool accepted_or_rejected = false;                              //set a sign which is used to decide whether a request is accepted or rejected
			ListIterator<Train*> iter1(TrainList);                      //iterate the train list to see which train is available for the request
			for (; !iter1.IsDone(); iter1.Next())
			{
				ListIterator<int*> iter13(iter1.Item()->get_route());
				int s = 0;
				for (; !iter13.IsDone(); iter13.Next())
				{
					if (*iter13.Item() == request->get_departure_station())
					{
						s = s + 1;
					}
					if (*iter13.Item() == request->get_destination_station())
					{
						s = s + 1;
					}
				}
				if (s == 2)                                                             //check if the departure station and destination station are both in the train's route
				{
					ListIterator<int*> iter7(iter1.Item()->get_arriving_time());
					int index = 0;
					int d_time = 0;
					for (; !iter7.IsDone(); iter7.Next())                                       //find the arriving time for the corresponding station
					{
						if (index == q)
						{
							d_time = *iter7.Item();
							break;
						}
						else
						{
							index = index + 1;
						}
					}
					if (d_time > request->get_departure_time())                              //check if the arriving time is later than the request's departure time
					{
						if (request->get_request_class() == 1)                                     //check if required class of the request is coach
						{
							List<Bitmap*>* temp = iter1.Item()->get_cseat();
							ListIterator<Bitmap*> iter2(temp);
							int index = 0;
							for (; !iter2.IsDone(); iter2.Next())                                  //find the corresponding bitmaps of seats 
							{
								if (index >=q and index<p)
								{
									if (iter2.Item()->NumClear() >= request->get_numberofpassenger())
									{
										index = index + 1;
										continue;
									}
									else
									{
										break;
									}
								}
								else {
									if (index == p)
									{
										accepted_or_rejected = true;
										break;
									}
									else
									{
										index = index + 1;
									}
								}
							}
						}
						else                                                                      //check if required class of the request is business
						{
							List<Bitmap*>* temp = iter1.Item()->get_bseat();
							ListIterator<Bitmap*> iter2(temp);
							int index = 0;
							for (; !iter2.IsDone(); iter2.Next())                                  //find the corresponding bitmaps of seats 
							{
								if (index >= q and index < p)
								{
									if (iter2.Item()->NumClear() >= request->get_numberofpassenger())
									{
										index = index + 1;
										continue;
									}
									else
									{
										break;
									}
								}
								else
									if (index == p)
									{
										accepted_or_rejected = true;
										break;
									}
									else
									{
										index = index + 1;
									}
							}
						}
					}
					{
						available_train->Append(iter1.Item());
					}
				}
			}
			if (accepted_or_rejected == true)                      //if there is at least one train available for the request
			{                         
				accepted_request->Append(request);                  //the request is accepted
				all_accepted_request->Append(request);                  //the request is accepted
			}
			else                                                   
			{ 
				rejected_request->Append(request);
				all_rejected_request->Append(request);                  //the request is rejected                 
			}
			int granted_request = accepted_request->NumInList();
			int refuse_request = rejected_request->NumInList();
			int available_train_number = available_train->NumInList();
			if(available_train_number != 0)
			{
			int a = rand() % (available_train_number) + 0;                  //pick up a random train from the available train list
			ListIterator<Train*> iter3(available_train);  
			int index = 0;
			for (; !iter3.IsDone(); iter3.Next())
			{
				if (index == a)
				{
					request->set_train_id(iter3.Item()->get_train_id());
					break;
				}
				else
				{
					index = index + 1;
				}
			}
			int number = request->get_numberofpassenger();             //get the request's number of passengers 
			int departure_station = request->get_departure_station();       //get the request's departure station
			int seat_class = request->get_request_class();               //get the request's seat class
			int departure_time = request->get_departure_time();               //get the request's departure time
			ListIterator<Train*> iter4(TrainList);                      //iterate the trainlist to find the selected train
			for (; !iter4.IsDone(); iter4.Next())
			{
				if (iter4.Item()->get_train_id() == request->get_selected_train_id())
				{
					if (seat_class == 1)                                      //if the required class is coach
					{
						ListIterator<Bitmap*>iter5(iter4.Item()->get_cseat());        //iterate the train's list of coach bitmaps to find the bitmaps in the range
						int index = 0;
						for (; !iter5.IsDone(); iter5.Next())                                  //find the corresponding bitmaps of seats 
						{
							if (index >= q and index < p)
							{
								int n = request->get_numberofpassenger();
								for (int g = 0; g < n; g++)                 //mark the seats that are reserved for the request
								{
									iter5.Item()->FindAndSet();
								}
								index = index + 1;
								continue;
							}
							else
								if (index == p)
								{
									break;
								}
								else
								{
									index = index + 1;
								}
						}
					}
					else                                                      //if the required class is business
					{
						ListIterator<Bitmap*>iter5(iter4.Item()->get_bseat());        //iterate the train's list of coach bitmaps to find the bitmaps in the range
						int index = 0;
						for (; !iter5.IsDone(); iter5.Next())                                  //find the corresponding bitmaps of seats 
						{
							if (index >= q and index < p)
							{
								int n = request->get_numberofpassenger();
								for (int g = 0; g < n; g++)                 //mark the seats that are reserved for the request
								{
									iter5.Item()->FindAndSet();
								}
								index = index + 1;
								continue;
							}
							else
								if (index == p)
								{
									break;
								}
								else
								{
									index = index + 1;
								}
						}
					}
				}
				}
			}
		}     //end of requests
			//statistics
					Stats s;
					cout << "From " << 10*t << " to " << 10 * t + 10<< " minutes: " << endl;
					s.get_granted_request(accepted_request->NumInList());
					s.get_refused_request(rejected_request->NumInList());
	}
	Stats s;
	s.get_all_requests(requestlist.NumInList());
	s.get_all_granted_requests(all_accepted_request->NumInList());
	s.get_number_of_passengers(all_accepted_request);
}