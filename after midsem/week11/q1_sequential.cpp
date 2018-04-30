#include <bits/stdc++.h>

using namespace std;

int blocks[100]={0};

vector<pair < int , pair < int, int > > > storage; // stores the file name, starting index and length


void print(int no){      // prints the blocks allocated to the file
	int start,size;
	for(int i=0;i<storage.size();++i)
		if(storage[i].first==no){
			start = storage[i].second.first;
			size = storage[i].second.second;
			break;
		}
	for(int i=start;i<start+size;++i)
			cout <<i<<" ->";
}
int check(int no){ // checks if file already exits
	for(int i=0;i<storage.size();++i)
		if(storage[i].first==no)
			return 1;
	return 0;
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
				allocated++;
				blocks[i]=no;
			}
			else if(blocks[i]!=0 && allocated!=lenght){
				break;
			}
		}
		if(allocated==lenght){ // if allocated the required space to file, print the blocks allocated.
			cout <<"Allocated blocks to file\n";
			storage.push_back(make_pair(no, make_pair(start,lenght)));
			print(no);	
			cout<<endl;
		}

		else{ 
			cout <<"Can't allocate space to the file\n";
		}
	}
	
}