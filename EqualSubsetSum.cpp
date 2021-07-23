#include <bits/stdc++.h>
using namespace std;

#include <chrono>
using namespace std::chrono;
  


void getAllSums(vector<int> &myVector, int l, int n, int currentSum, vector<int> &allSums){
	
	
	if(l >= n){
		allSums.push_back(currentSum);
		return;
	}		
	getAllSums(myVector, l+1, n , currentSum , allSums);
	getAllSums(myVector, l+1, n , currentSum + myVector[l], allSums);
	
	
	 
}


int naiveSol(int S, vector<int> myVector){
	vector<int> allSums;
	
	getAllSums(myVector,0, myVector.size(), 0, allSums);
	
	sort(allSums.begin(), allSums.end());
	/*
	for(auto elem : allSums){
		cout<<elem<<" ";
	}
	*/
	bool flag = false;
	for(auto elem : allSums){
		if(elem == S){
			flag = true;
			break;
		}
	}
	if(flag)
		return 1;
	else
		return 0;
}

int MITMsol(int S, vector<int> myVector){
	vector<int> allSumsX;
	vector<int> allSumsY;
	
	int half = myVector.size()/2;
	
	vector<int> X(myVector.begin(), myVector.begin() + half);
	vector<int> Y(myVector.begin() + half, myVector.end());
	
	getAllSums(X, 0 , X.size(), 0, allSumsX);
	getAllSums(Y, 0 , Y.size(), 0, allSumsY);
	
	unordered_set<int> allSumsSetY;
	for(int i=0; i< allSumsY.size(); i++)
		allSumsSetY.insert(S- allSumsY[i]);
	
	for(int i=0; i< allSumsX.size(); i++){
		unordered_set<int>::const_iterator it = allSumsSetY.find(allSumsX[i]);
		if( it != allSumsSetY.end()){
			return 1;
			break;
		}
	}
	return 0;

}



int main(){

	vector<int> all_S;
	vector<vector<int>> v; 
	vector<int> respuestas;
	int numberCases;

	string line;
	ifstream myfile ("input.txt");
	if (myfile.is_open())
	{	
		getline(myfile,line);
		numberCases= stoi(line);
		for(int i=0; i<numberCases;i++){
			getline(myfile,line);
			all_S.push_back(stoi(line));
			
			vector<int> new_v;
			getline(myfile,line);
			stringstream ss(line);
			int num;
			while(ss >> num){
				new_v.push_back(num);
			}
			v.push_back(new_v);

			getline(myfile,line);
			respuestas.push_back(stoi(line));
		}
		myfile.close();		
	}
	else{
		cout<<"error al abrir";
		return 0;
	}

	ofstream myoutputfile("output.txt");
	myoutputfile<<"tiempo naive    tiempo MITM\n";
	vector<int> mis_respuesta_naive;
	vector<int> mis_respuesta_mitm;
	

	int sol;
	//Solución Naive
	high_resolution_clock::time_point start;
	high_resolution_clock::time_point stop;
	microseconds duration;

	for(int i=0; i<numberCases;i++){
		start = high_resolution_clock::now();
		sol = naiveSol(all_S[i],v[i]);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);
		myoutputfile<<setw(10)<<to_string(duration.count());
		mis_respuesta_naive.push_back(sol);

		start = high_resolution_clock::now();
		sol = MITMsol(all_S[i],v[i]);
		stop = high_resolution_clock::now();
		duration = duration_cast<microseconds>(stop - start);
		myoutputfile<<setw(10)<<to_string(duration.count())<<setw(10)<<"Ms\n";
	}
}