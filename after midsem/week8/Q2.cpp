#include <bits/stdc++.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

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

//function which calculates the faults and maintains the frame request table
void find_faults( vector < vector < int > > a){

	int number_of_faults=0;
	int q_no=0;
	for(int i=0;i<requests.size();++i){
		int request = requests[i];
		if(i!=0 && check_present(a, i-1, request, number_frames)){
			copy(a, i, number_frames);

		}
		else{
			if (i!=0){
				copy(a,i,number_frames);
			}
			a[q_no][i]=request;
			number_of_faults++;
			q_no++;
			q_no = q_no%number_frames;
		}
	}
	// to print the output
	print(a, number_frames);
	cout <<endl;
	printf("Using %d frames, the reference string yielded:\n", number_frames);
	printf("Scheme                #Faults\n");
	printf("FIFO                  %d\n\n", number_of_faults);
}


int main (void){
	ifstream infile;
	string line;
	infile.open("page.txt");
	
	int i=0;
	// reading the input from file
	while(getline(infile, line)){
		i++;
		string temp;
		istringstream iss(line);
		if (i%2==1){
			iss>> number_frames;

			cout << "FIFO:"<<endl;		
		}

		else{
			int temp;
			iss >> temp;
			requests.push_back(temp);
			cout << temp << " ";
			while (1){
				iss >> temp;
				if (temp==-1)
					break;
				requests.push_back(temp);
				cout << temp << " ";
			}
			cout << endl<<"___________________________________________________________________"<<endl;
			vector < vector < int > > matrix(number_frames, vector < int >(requests.size())) ;
			find_faults(matrix);
			requests.clear();
		}

		
	}

}


