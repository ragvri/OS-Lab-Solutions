#include <bits/stdc++.h>

using namespace std;

int blocks[100]={0};


map < int , vector < int > > storage; // first is the file index, second is the vector which stores the indexes allocated to the file
 
void print(int no){ // prints the blocks allocated to a file
	for(int i=0;i<storage[no].size();++i){
		cout << storage[no][i]<<" ->";
	}
}

int check(int no){ // checks if file already exits
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
			cout<<"Enter the file no\n";
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
		else{ // if file can't be allocated space, delete the values in the linked list of the file which stores the blocks given to a file.
			storage[no].clear();
			cout <<"Can't allocate space to the file\n";
		}
	}
	
}