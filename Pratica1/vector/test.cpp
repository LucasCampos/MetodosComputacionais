#include "Physics/myVector.hpp"
#include <cstdlib>
#include <iostream>

using namespace std;

double uni() {return rand()/(double)RAND_MAX;}

int main() {

	bool OK = true;

	srand(time(NULL));
	int nTests = 100;
	const int D =10;
	for (int i=0; i<nTests; i++){

		cout << "Teste " << i << ": ";

		Physics::Vector<D,double> a,orto;
		std::vector<Physics::Vector<D,double> >b(D-2);
		
		for (int j=0; j<D; j++){
			a.SetElem(j,uni());
		}

		for (int k=0; k<(D-2); k++) {
			for (int j=0; j<D; j++){
				b[k].SetElem(j,uni());
			}
		}

		orto = a^b;
		std::cout << orto*a << std::endl;
		
		if ((orto*a) > 1e-10) { 
			std::cout << "Erro!\n";
			OK=false;
		} else {
			std::cout << "Ok!\n";
		}
	}

	if (OK) 
		cout << "Teste finalizado com sucesso\n";
	else
		cout << "Ocorreram erros\n";
}
