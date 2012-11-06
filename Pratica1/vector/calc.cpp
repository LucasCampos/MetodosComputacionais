#include "Physics/myVector.hpp"
#include <iostream>

using namespace std;

int main() {

	int N=3;

	Physics::Vector<3,double> a,b,c;
	for (int i=0; i<N; i++) {
		cout << "Escolha o valor " << i << " do primeiro vetor: ";
		double temp;
		cin >> temp;
		a.SetElem(i,temp);
	}

	for (int i=0; i<N; i++) {
		cout << "Escolha o valor " << i << " do segundo vetor: ";
		double temp;
		cin >> temp;
		b.SetElem(i,temp);
	}

	cout << "Você criou os vetores " << a << " e " << b << endl;

	cout << "1 - Soma" << endl;
	cout << "2 - Subtração" << endl;
	cout << "3 - Produto Interno" << endl;
	cout << "4 - Produto Vetorial" << endl;
	cout << "5 - Produto Vetorial Geral" << endl;
	cout << "6 - Normalização" << endl;

	cout << "Escolha a operação: ";
	int operacao;
	cin >> operacao;
	switch(operacao){

		case 1:{
			       Physics::Vector<3,double> c = a+b;
			       cout << a+b; 
			       break;
		       }
		case 2:{
			       Physics::Vector<3,double> d = a-b;
			       cout << a-b ; 
			       break;
		       }
		case 3:{
			       double e = a*b;
			       cout << a*b << endl; 
			       break;
		       }
		case 4:{
			       Physics::Vector<3,double> f = a^b;
			       cout << f; 
			       break;
		       }
		case 5:{
			       vector< Physics::Vector<3,double> > v;
			       v.push_back(b);
			       cout << (a^v); 
			       cout << (a^b); 
			       break;
		       }
		case 6:
		       a.Normalize();
		       b.Normalize();
		       cout << a << "  " << b; 
		       break;
	}

	a+= b;
	a*= 5;
	a-= b;
	if ((a^b)*a == 0) 
		cout <<"OK\n";



}
