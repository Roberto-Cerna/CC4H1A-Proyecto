/*
Genera un input.txt

El primer valor es el número de casos
#n

Genera múltiples casos de la siguiente estructura
#S
#a1,a2,a3,...
#C

S indica el valor objetivo
a1,a2,a3,.. representa al conjunto
C  0 si la este problema la solución es que no se encontro un 
	subconjunto de A de tal manera que su suma sea S
   1 Si ese conjunto si existe
*/



#include <bits/stdc++.h>

using namespace std;

int main(){
	srand(time(0));
	
	vector<int> all_S;
	vector<vector<int>> v; 
	vector<int> respuestas;
 	int numCasos = 60;

 
	for(int i=0; i< numCasos; i++){
		int correct;
		correct = rand()%2;
		int S = 0;
		int n = rand()%20 + 5;

		vector<int> new_vector;	
		for(int j=0; j<n; j++){
			int a = rand()%30 +2;
			new_vector.push_back(a);
		}
		v.push_back(new_vector);
		

		if(correct){
			for(auto elem : new_vector){
				int randomNumber = rand()%3;
				if( randomNumber == 0)
					S = S +elem;
			}
		}
		else{
			S = *min_element(v[i].begin(),v[i].end()) -1;
		}
		all_S.push_back(S);
		respuestas.push_back(correct);
	}


	ofstream myfile;
	myfile.open("input.txt");
		
	myfile<< numCasos<<"\n";
	for(int i=0; i< numCasos; i++){
		myfile << to_string(all_S[i])+ "\n";
		for(auto elem: v[i]){
			myfile<< to_string(elem) + " ";
		}
		myfile<<"\n";
		myfile<< to_string(respuestas[i]) + "\n";
	}
	myfile.close();
	return 0;
}