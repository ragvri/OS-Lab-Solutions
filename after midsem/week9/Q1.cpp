#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;
int recent[100]={0};
int frequency[100]={0};

vector < int > requests;
int number_frames;

// checks if the page is already present in some frame
int check_present(vector < vector < int > > a, int pos, int request, int number_frames){
	for(int i=0;i<number_frames;++i)
		if (a[i][pos]==request)
			return 1;
	return 0;
}

//copying the values of the frames of previous timestamp to current timestamp
void copy(vector < vector < int > >& a, int pos, int number_frames){
	for(int i=0;i<number_frames;++i)
		a[i][pos]=a[i][pos-1];
	return;
}


//to print the frame requests table
void print(vector < vector < int > > a, int number_frames){
	for(int i=0;i<number_frames;++i){
		for(int j=0;j<a[i].size();++j){
			cout << a[i][j] <<" ";
		}
		cout << endl;
	}
}

// function for lru
void lru(vector < vector < int > > a){
	int number_of_faults=0;
	for(int i=0;i<requests.size();++i){
		int request= requests[i];
		recent[request]=i+1; // updating value of recent for the request
		if(i!=0 && check_present(a, i-1, request, number_frames)) //checking if already present
			copy(a,i,number_frames);
		else{
			if(i!=0)
				copy(a,i,number_frames);
			int temp=recent[a[0][i]];
			int index = 0;
			for(int j=0;j<number_frames;++j){
				if( temp > recent[a[j][i]]){
					temp = recent[a[j][i]];
					index = j;
				}
			}
			a[index][i]=request;
			number_of_faults++;
		}
	}
	
	cout << endl<<"LRU:" << endl;
	for(int i=0;i<requests.size();++i)
		cout << requests[i] <<" ";
	cout << endl;
	cout <<"___________________________________________"<< endl;
	print(a, number_frames);
	cout << "Number of faults "<< number_of_faults << endl;
}

// function for lfu
void lfu(vector < vector < int > >a){
	int number_of_faults=0;
	for(int i=0;i<requests.size();++i){
		
		int request = requests[i];
		frequency[request]++;// updating the frequency of a page
		if(i!=0 && check_present(a,i-1, request, number_frames)) // checking if page already preset in the frame
			copy(a, i, number_frames);
		else{
			number_of_faults++;
			if(i!=0)
				copy(a, i, number_frames);
			int temp= frequency[a[0][i]];
			int index=0;
			for(int j=0;j<number_frames;++j){
				if(temp>frequency[a[j][i]]){
					temp = frequency[a[j][i]];
					index = j;
				}
			}
			a[index][i]=request;
		}
	}
	cout << endl<<"LFU:" << endl;

	for(int i=0;i<requests.size();++i)
		cout << requests[i] <<" ";
	cout << endl;
	cout <<"___________________________________________"<< endl;
	print(a, number_frames);
	cout << "Number of faults "<< number_of_faults << endl;
}

//function for optimal
void optimal(vector < vector < int > >a){
	int number_of_faults=0;
	for(int i=0;i<requests.size();++i){
		int request = requests[i];
		if(i!=0 && check_present(a,i-1,request, number_frames))
			copy(a, i, number_frames);
		else{
			number_of_faults++;
			if(i!=0)
				copy(a,i,number_frames);
			int temp=-1;
			int index=0;
			
			for(int j=0;j<number_frames;++j){ // finding which page to replace 
				int flag=0;
				int page =a[j][i];
				if (page==0){
					index=j;
					break;
				}
				for(int x=i+1;x<requests.size();++x){
					if(requests[x]==page){
						flag=1;
						if(temp<x){
							temp = x;
							index = j;
						}
						break;
					}
				}
				if(flag==0){
					index=j;
				}
			}
			a[index][i]=request;
		}
	}
	cout << endl<<"Optimal:" << endl;
	for(int i=0;i<requests.size();++i)
		cout << requests[i] <<" ";
	cout << endl;
	cout <<"___________________________________________"<< endl;
	print(a, number_frames);
	cout << "number of faults "<< number_of_faults<<endl;


}

int main (void){
	ifstream infile;
	string line;
	infile.open("pages.txt");
	
	int i=0;
	// reading the input from file
	while(getline(infile, line)){
		i++;
		string temp;
		istringstream iss(line);
		if (i%2==1){
			iss>> number_frames;
		}

		else{
			int temp;
			iss >> temp;
			requests.push_back(temp);
			while (1){
				iss >> temp;
				if (temp==-1)
					break;
				requests.push_back(temp);
			}
			vector < vector < int > > matrix(number_frames, vector < int >(requests.size())) ;
			lru(matrix);
			vector < vector < int > > temp1(number_frames, vector < int >(requests.size())) ;
			matrix = temp1;
			lfu(matrix);
			vector < vector < int > > temp2(number_frames, vector < int >(requests.size())) ;
			matrix =temp2;
			optimal(matrix);

			requests.clear();
		}
		
	}
}


