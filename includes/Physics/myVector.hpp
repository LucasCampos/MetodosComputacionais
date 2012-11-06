/*
 * Class: N-Dimensional Vector 
 * Author: Lucas Costa Campos
 * Date: 05/09/2012
 * This template requires an integer to define the dimension, and a 
 * type, to define its entries
 */

#ifndef MYVECTOR_HPP
#define MYVECTOR_HPP
#include <iostream>
#include <cmath>
#include <vector>

namespace Physics {
	

	//Returns a new matrix without the a1 line and a2 column
	template <class T> std::vector< std::vector<T> > Minor(const std::vector< std::vector<T> > &v, int a1, int a2);
	//Determinant of the matrix
	template <class T> T  Det(const std::vector< std::vector<T> > &v);

	//N determines the dimension of the vector, whereas T define the entries
	template<unsigned int N, typename T> class Vector {
		public:
			T comp[N];

		public:
			Vector();
			Vector(const T newComp[N]);
			~Vector(){};

			inline void SetElem(int i, T a);
			inline T GetElem(int i) const;

			//Calculates the magnitude of the vector, squared
			inline T MagnitudeSquared() const ;
			//Calculates the magnitude of the vector
			inline T Magnitude() const ;
			//Rescales the vector such as the norm is one
			inline void Normalize() ;

			inline Vector<N,T> MultiScalar(T a) const;
			inline T DotProduct( const Vector<N,T>& v) const ;
			//General, N dimensional extenal product. CAUTION: It uses a high amount of stack
			inline Vector<N,T> CrossProduct(const std::vector< Vector<N,T> >& v) const;
			//3 dimensional external product
			inline Vector<N,T> CrossProduct(const Vector<N,T>& v) const ;
			//Add two vectors
			inline Vector<N,T> AddVector(const Vector<N,T>& v) const ;

			//Negation Operator. Inverts the direction of the vector
			Vector<N,T> operator-() const ;

			Vector<N,T> operator+(const Vector<N,T> & v) const ;
			Vector<N,T> operator-(const Vector<N,T> & v) const ;

			//Multiplication with a scalar
			Vector<N,T> operator*(T a) const ;
			//Dot product. NOT element-wise
			T operator*(const Vector<N,T> & v) const;
			//3D external product
			Vector<N,T> operator^(const Vector<N,T> & v) const ;
			//General, N dimensional extenal product. CAUTION: It uses a high amount of stack
			Vector<N,T> operator^(const std::vector <Vector<N,T> >& v) const ;
			Vector<N,T> & operator=(const Vector<N,T> & v) ;
			Vector<N,T> & operator+=(const Vector<N,T> & v);
			Vector<N,T> & operator-=(const Vector<N,T> & v);
			Vector<N,T> & operator*=(T a);

			//Converts the algebric vector to a C++ vector
			std::vector<T> ToStdVector() const;
			//Writes our vector into a stream
			friend std::ostream& operator<<(std::ostream& stream,const Vector<N,T>& v){

				for (int i=0; i<N; i++) {
					stream << v.GetElem(i) << "\t";
				}
				return stream;
			}

	};

	/////////////////////////////////////////////////METHODS IMPLEMENTATION\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	//Default vector is just a bunch of zeros
	template <unsigned int N, class T> Vector<N,T>::Vector(){
		for (int i=0; i<N; i++) {
			comp[i] = 0;
		}
	}

	template <unsigned int N, class T>  Vector<N,T>::Vector(const T newComp[N]){
		for (int i=0; i<N; i++) {
			comp[i] = newComp[i];
		}
	}

	//Define #DEBUG or use the -D DEBUG flag at the compiler to turn bound-checking
	template <unsigned int N, class T> void Vector<N,T>::SetElem(int i, T a){
#ifdef DEBUG
		if ((i >= N) || (i<0))
			std::cout << "Tentando colocar o " << i << " elemento de um array de apenas " << N << std::endl;
#endif
		comp[i] =a;
	}

	//Define #DEBUG or use the -D DEBUG flag at the compiler to turn bound-checking
	template <unsigned int N, class T> T Vector<N,T>::GetElem(int i) const{
#ifdef DEBUG
		if ((i >= N) || (i<0))
			std::cout << "Tentando ler o " << i << " elemento de um array de apenas " << N << std::endl;
#endif
		return comp[i];
	}

	template <unsigned int N, class T>  T Vector<N,T>::MagnitudeSquared() const {
		return (*this)*(*this);
	}

	template <unsigned int N, class T>  T Vector<N,T>::Magnitude() const {
		return sqrt((*this)*(*this));
	}

	template <unsigned int N, class T>  void Vector<N,T>::Normalize() {
		T norm = Magnitude();
		if (norm == T(0))
			return;
		for (int i=0; i<N; i++) {
			comp[i]/=norm;
		}
	}

	template <unsigned int N, class T> Vector<N,T> Vector<N,T>::MultiScalar(T a) const {
		T newComp[N];
		for (int i=0; i<N; i++) {
			newComp[i] = comp[i] * a;
		}
		return Vector<N,T> (newComp);
	}

	template <unsigned int N, class T>  T Vector<N,T>::DotProduct( const Vector<N,T>& v) const {

		T summer = 0;
		for (int i=0; i<N; i++) {
			summer+= v.GetElem(i)*comp[i];
		}
		return summer;

	}

	//General external product. Det is recursive, and might take a lot of stack space
	template <unsigned int N, class T>  Vector<N,T> Vector<N,T>::CrossProduct(const std::vector< Vector<N,T> >& vV) const {

#ifdef DEBUG
		if(vV.size() != (N-2)){
			std::cout << "Aviso: para se estabelecer o produto vetorial no espaço " << N << "dimensional é necessário entrar com " << N-2 << " vetores" << std::endl;
			std::cout << "Foram fornecidos " << vV.size() << std::endl;
		}
#endif

		std::vector<std::vector<T> > v;
		v.push_back(ToStdVector());//This vector is copied only for padding purposes
		v.push_back(ToStdVector());
		for (int i=0; i<vV.size(); i++)
			v.push_back(vV[i].ToStdVector());

		T newComp[N];
		int i=0;

		for (int j=0; j<v[i].size(); j++) {
			T term = ( (i+j)%2 == 0? 1: -1)*Det(Minor(v,i,j));
			newComp[j] = term;
		}

		return Vector<N,T>(newComp);

	}

	//3D external product. Answer is the same as on the general function, but is cheaper
	template <unsigned int N, class T>  Vector<N,T> Vector<N,T>::CrossProduct(const Vector<N,T>& v) const {
#ifdef DEBUG
		if (N=!3)
			std::cout << "Função CrossProduct<Vector v> espera ser tridimensional, não "<< N << "dimensional. Use CrossProduct(std::Vector)." << std::endl;
#endif

		T newComp[N];
		newComp[0] = comp[1]*v.GetElem(2) - comp[2]*v.GetElem(1);
		newComp[1] = comp[2]*v.GetElem(0) - comp[0]*v.GetElem(2);
		newComp[2] = comp[0]*v.GetElem(1) - comp[1]*v.GetElem(0);

		return Vector<N,T>(newComp);

	}

	template <unsigned int N, class T>  Vector<N,T> Vector<N,T>::AddVector(const Vector<N,T>& v) const {
		T newComp[N];
		for (int i=0; i<N; i++) {
			newComp[i] = comp[i]+ v.GetElem(i);
		}
		return Vector<N,T>(newComp);

	}

	template <unsigned int N, class T> Vector<N,T> Vector<N,T>::operator-() const {
		T newComp[N];
		for (int i=0; i<N; i++) {
			newComp[i] = -comp[i];
		}
		return Vector<N,T> (newComp);

	}

	template <unsigned int N, class T> Vector<N,T> Vector<N,T>::operator+(const Vector<N,T> & v) const {
		return AddVector(v);
	}

	template <unsigned int N, class T> Vector<N,T> Vector<N,T>::operator-(const Vector<N,T> & v) const {
		return AddVector(-v);
	}

	template <unsigned int N, class T> Vector<N,T> Vector<N,T>::operator*(T a) const {
		return MultiScalar(a);
	}

	template <unsigned int N, class T> T Vector<N,T>::operator*(const Vector<N,T> & v) const {
		return DotProduct(v);
	}

	template <unsigned int N, class T> Vector<N,T> Vector<N,T>::operator^(const std::vector< Vector<N,T> > & v) const {
		return CrossProduct(v);
	}

	template <unsigned int N, class T> Vector<N,T> Vector<N,T>::operator^(const Vector<N,T> & v) const {
		return CrossProduct(v);
	}

	template <unsigned int N, class T> Vector<N,T> & Vector<N,T>::operator=(const Vector<N,T> & v) {
		for (int i=0; i<N; i++) {
			comp[i] = v.GetElem(i);
		}
		return (*this);
	}

	template <unsigned int N, class T> Vector<N,T> & Vector<N,T>::operator*=(T a){
		for (int i=0; i<N; i++) {
			comp[i]*= a;
		}
		return (*this);
	}

	template <unsigned int N, class T> Vector<N,T> & Vector<N,T>::operator+=(const Vector<N,T> & v){
		for (int i=0; i<N; i++) {
			comp[i]+= v.GetElem(i);
		}
		return (*this);
	}

	template <unsigned int N, class T> Vector<N,T> & Vector<N,T>::operator-=(const Vector<N,T> & v){
		for (int i=0; i<N; i++) {
			comp[i]-= v.GetElem(i);
		}
		return (*this);
	}

	template <unsigned int N, class T> std::vector<T> Vector<N,T>::ToStdVector() const {
		std::vector<T> temp(N);
		for (int i=0; i<N; i++)
			temp[i] = comp[i];

		return temp;
	}

	////////////////////////////////////////////////HELPER FUNCTIONS\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\

	//Returns a new matrix, without line a1 and column a2. It's used to calculate the determinant
	template <class T> std::vector< std::vector<T> > Minor(const std::vector< std::vector<T> > &v, int a1, int a2) {

		int N=v.size();

		std::vector<std::vector<T> > ret(N-1);
		for (int i=0; i<N-1; i++)
			ret[i].resize(N-1);

		for (int i=0; i<a1; i++) {
			for (int j=0; j<a2; j++) 
				ret[i][j] = v[i][j];
			for (int j=a2+1; j<N; j++) 
				ret[i][j-1] = v[i][j];
		}

		for (int i=a1; i<(N-1); i++) {
			for (int j=0; j<a2; j++) 
				ret[i][j] = v[i+1][j];
			for (int j=a2+1; j<N; j++) 
				ret[i][j-1] = v[i+1][j];
		}

		return ret;
	}

	//Prints a vector of vector. Useful for debugging
	template <class T>
		void PrintMatrix(const std::vector< std::vector<T> > &v) {
			for (int i=0; i<v.size(); i++){
				for (int j=0; j<v[i].size(); j++)
					std::cout << v[i][j] << "\t";
				std::cout << std::endl;
			}
		}

	//returns the determinant, using Laplace's formula. Notice that, as it is recursive, it might take a lot of stack
	template <class T> T  Det(const std::vector< std::vector<T> > &v) {
		if (v.size() == 1) 
			return v[0][0];
		int i=0;
		T sum = 0;
		for (int j=0; j<v.size(); j++) {
			T term = ( (i+j)%2 == 0? 1: -1)*v[i][j]*Det(Minor(v,i,j));
			sum += term;
		}
#ifdef DEBUG
		PrintMatrix(v);
		std::cout <<sum << std::endl << std::endl;
#endif 
		return sum;
	}

	typedef Vector<3,double> Vector3D; 
}
#endif
