#include <bits/stdc++.h>

using namespace std;

map < int, list < int > > storage; // first is the file no, second is a linked list which stores the blocks allocated to the file in linked list manner
int blocks[100]={0};


void print(int no){ // prints the blocks allocated to a file
	for(int i: storage[no])
		cout << i <<" ->";
}

int check(int no){ // checks if file is empty
	if(storage[no].empty())
		return 0;
	return 1;
}

int main(void){
	int x;
	while(1){
		cout<<"Enter 1 to continue\nEnter 2 to get the blocks index allocated to the file\nEnter 3 to exit\n";
		cin >>x;
		if(x==3)
			break;
		if(x==2){
			int no;
			cout <<"Enter the file number\n";
			cin >> no;
			print(no);
			cout << endl;
			continue;
		}
		
		cout << "Enter the file number (1 indexed)"<<endl;
		int no;
		cin >> no;
		if(check(no)==1){
			cout<<"File already exists!\n";
			continue;
		}
		cout << "Enter the starting index of the file"<<endl;
		int start;
		cin >> start;
		cout << "Enter the lenght of the file"<< endl;
		int lenght;
		cin >> lenght;
		int allocated=0;
		for(int i=start;i<100;++i){
			if(allocated==lenght)
				break;
			if(blocks[i]==0){
				storage[no].push_back(i);
				allocated++;
				blocks[i]=no;
			}
		}
		if(allocated==lenght){
			cout <<"Allocated blocks to file\n";
			print(no);	
			cout<<endl;
		}
		else{
			storage[no].clear(); // if space can't be allocated to file, remove the temporary blocks reserved for the file.
			cout <<"Can't allocate space to the file\n";
		}
	}
	
}