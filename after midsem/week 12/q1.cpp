#include <bits/stdc++.h>
using namespace std;

int work_q[] = {95, 180, 34, 119, 11, 123, 62, 64};
int num_cylinders =200;



int fcfs(int start_pos){ //fcfs 
	int result=0;
	cout << 50<<"-> ";
	for(int i=0;i<sizeof(work_q)/sizeof(*work_q);++i){
		result+=abs(work_q[i]-start_pos);
		start_pos = work_q[i];
		cout<<start_pos<<"-> ";
	}

	return result;
}

int in(int start_pos){ // checks if a value is in the queue
	for(int i=0;i<sizeof(work_q)/sizeof(*work_q);++i)
		if(work_q[i]==start_pos)
			return 1;
	return 0;
}

int scan(int start_pos){ // scan moves to left first
	cout <<50<<"-> ";
	int result =0;
	int max = INT_MIN;
	for(int start_pos= 50;start_pos>=0;--start_pos){
		if(in(start_pos))
			cout << start_pos <<"-> ";

	}
	for(int start_pos=51;start_pos<200;++start_pos)
		if (in(start_pos))
			cout << start_pos <<"-> ";

	for(int i=0;i<sizeof(work_q)/sizeof(*work_q);++i)
		if(work_q[i]>max)
			max = work_q[i];

	result = abs(start_pos - 0) + (max-0);
	return result;
}

int cscan(int start_pos){ // cscan moves to right first
	int result=0;
	int max_less_than_start = INT_MIN;
	cout <<50<<"-> ";
	for(int start_pos=50;start_pos<200;++start_pos)
		if (in(start_pos))
			cout <<start_pos <<"-> ";
	for(int start_pos=0;start_pos<50;++start_pos)
		if (in(start_pos))
			cout << start_pos <<"-> ";

	for(int i=0;i<sizeof(work_q)/sizeof(*work_q);++i){
		if((work_q[i]<start_pos) && (work_q[i]>max_less_than_start))
			max_less_than_start = work_q[i];
	}

	result= abs(num_cylinders-1-start_pos) + (max_less_than_start - 0);
	return result;
}

int find_sst(int pos, vector< int > &q){ // finds the value that is closest to the current value and returns the index.
	int min_distance = INT_MAX;
	int index;
	for(int i=0;i<q.size();++i){
		if(abs(q[i]-pos)<min_distance){
			index = i;
			min_distance = abs(q[i]-pos);
		}
	}
	return index;
}
int sstf(int start_pos){ // sstf function. calls find_sstf at every step
	int result = 0;
	vector< int > q;
	for(int i=0;i<sizeof(work_q)/sizeof(*work_q);++i){
		q.push_back(work_q[i]);
	}
	cout <<start_pos<<"-> ";
	while(1){
		if(q.empty())
			break;
		int index = find_sst(start_pos, q);
		cout<<q[index]<<"-> ";
		result+=abs(q[index]-start_pos);
		start_pos= q[index];
		q.erase(q.begin()+index);

	}
	return result;

}

int main(void){
	int start_pos=50;
	cout<< "FCFS "<<endl;
	cout <<endl <<"Seek time " << fcfs(start_pos)*5<<"ms\n\n";
	cout <<"SCAN (going left first) "<<endl;
	cout << endl<<"Seek time "<< scan(start_pos)*5<< "ms\n\n";
	cout <<"CSCAN (going right first)"<< endl;
	cout << endl<< "Seek time "<< cscan(start_pos)*5<< "ms\n\n";
	cout <<"SSTF " << endl;
	cout <<endl <<"Seek time " <<sstf(start_pos)*5 <<"ms\n\n";
}