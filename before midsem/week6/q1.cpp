#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

int last_time_used;
int current_time;
int finish_time;
int number_lines=0;
struct Process{
	string id;
	int arrival_time;
	int burst_time;
	int queue_no;
	int last_time_used;

};
pair< int, int > temp;


deque < pair<int, int> > rr;
priority_queue<pair< int, int>,vector<pair<int, int> > ,greater<pair<int,int> > > sjf;


void add_to_queue(int a, int b,struct Process* x){
	for(int i=0;i<number_lines-1;++i){
		if (x[i].arrival_time>=a && x[i].arrival_time<b){
			if(x[i].queue_no==1)
				sjf.push(make_pair(x[i].burst_time, i));
			else
				rr.push_back(make_pair(x[i].burst_time, i));
		}
	}
}



int main(void){ // to read from file and output to a struct
	ifstream infile;
	string line;
	infile.open("input.txt");
	
	while(getline(infile, line))
		number_lines++;
	infile.close();
	struct Process processes[number_lines];

	infile.open("input.txt");
	int i=0;
	int count=0;
	while(getline(infile, line)){
		string temp;
		i++;
		if(i==1)
			continue;
		count=i - 2;
		istringstream iss(line);
		iss>>processes[count].id;
		iss>>temp;
		processes[count].arrival_time=atoi(temp.c_str());
		iss>>temp;
		processes[count].burst_time=atoi(temp.c_str());
		iss>>temp;
		processes[count].queue_no=atoi(temp.c_str());
		
	}


	int current_time;
	int latest_arrival_time=0;
	int rr_time=1;

	i=0;
	current_time = processes[i].arrival_time;
	cout << "The gant chart is: " <<endl << current_time <<" ";
	add_to_queue(current_time, current_time+1, processes);
	while (i< number_lines-1){
		while(!sjf.empty()){ //cheking if any process in sjf queue
			temp = sjf.top();
			cout<<"P"<<(temp.second+1)<<" ";
			sjf.pop();
			i++;
			last_time_used = processes[temp.second].arrival_time;
			finish_time = current_time+temp.first;
			cout << finish_time << " ";
			processes[temp.second].last_time_used=finish_time;
			add_to_queue(current_time+1,finish_time,processes);
			current_time=finish_time;
		}
		if(!rr.empty()){ // for round robin queue
			temp = rr[0];
			
			cout<<"P"<<(temp.second+1)<<" ";
			rr.pop_front();
			current_time++;
			cout << current_time <<" ";
			add_to_queue(current_time, current_time+1, processes);
			processes[temp.second].last_time_used=current_time;
			temp.first--;
			if(temp.first!=0)
				rr.push_back(temp);
			else{
				last_time_used = processes[temp.second].arrival_time;
				i++;
			}
		}
		else{
			current_time++;
			add_to_queue(current_time,current_time+1, processes);
		}
		
	}

	// waiting time = turnaround time - burst time;	
	int turnaround_time = 0;
	int total_burst_time=0;
	for(int i=0;i<number_lines-1;++i){
		turnaround_time+=(processes[i].last_time_used- processes[i].arrival_time);
		total_burst_time+=(processes[i].burst_time);
	}

	cout <<endl<<  "average turnaround time is:  " << turnaround_time*1.0/(number_lines-1) << endl << "average waiting time is: "<< (turnaround_time - total_burst_time)*1.0/(number_lines-1)<<endl;
}
