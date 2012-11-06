#ifndef LATTICE_HPP
#define LATTICE_HPP
#include "cell.hpp"
#include <cmath>
#include <GL/glfw.h>
#include <vector>

class Lattice {
	public:
		int L;
		int N;
		std::vector<Cell> cells1; 
		std::vector<Cell> cells2; 
		Lattice(int _L=100) {
			N=_L*_L;
			L=_L;
			cells1.resize(N);
			cells2.resize(N);
			MakeTriangularLatticeIdx();
			MakeTriangularLatticePos();
		}
		~Lattice() {
	//		delete cells2;
	//		delete cells1;
		}

		inline int DealWithBoundaries(int a)const {
			if (a < 0) return a+N;
			else return a;
		}
		/*
		 * Indexes:
		 * RIGHT 0
		 * RIGHT_DOWN 1
		 * LEFT_DOWN 2
		 * LEFT 3
		 * LEFT_UP 4
		 * RIGHT_UP 5
		 */
		void MakeTriangularLatticeIdx() {
			for (int i=0; i<N; i++) {
				cells1[i].neighIdx[0] = DealWithBoundaries((i+1)%N);
				cells1[i].neighIdx[1] = DealWithBoundaries((i+L)%N);
				cells1[i].neighIdx[2] = DealWithBoundaries((i+L-1)%N);
				cells1[i].neighIdx[3] = DealWithBoundaries((i-1)%N);
				cells1[i].neighIdx[4] = DealWithBoundaries((i-L)%N);
				cells1[i].neighIdx[5] = DealWithBoundaries((i-L+1)%N);
			}
			for (int i=0; i<N; i++) {
				for (int j=0; j<6; j++)
					cells2[i].neighIdx[j] = cells1[i].neighIdx[j];
			}
		};

		void MakeTriangularLatticePos() {
			int n =L;
			double ybox=1;

			if (n%2 != 0)
			{
				std::cout << "Tente um número multiplo de 4 para o lattice\n";
			}

			double dx, dy=0, del = ybox/n;

			dx = del/2;

			for (int i=0; i<n; i+=2)
			{
				dy = del/4;
				for (int j = 0; j<n; j++)
				{
					cells1[i*n+j].x = dy;
					cells1[i*n+j].y = dx;
					dy += del;
				}
				dx += del*sqrt(3.0f)/2;
				dy = del/2 + del/4;
				for (int j = 0; j<n; j++)
				{
					cells1[(i+1)*n+j].x = dy;
					cells1[(i+1)*n+j].y = dx;
					dy += del;
				}
				dx += del*sqrt(3.0f)/2;
			}

			for (int i=0; i<N; i++){
				cells2[i].x = cells1[i].x;
				cells2[i].y = cells1[i].y;
			}

		};

		void UpdateLattice1() {
#pragma omp parallel
			for (int i=0; i<N; i++) {
				//std::cout << i << std::endl;
				cells1[i].current = cells2[i].Update(cells2);
			}
		}

		void UpdateLattice2() {
#pragma omp parallel
			for (int i=0; i<N; i++) {
				//std::cout << i << std::endl;
				cells2[i].current = cells1[i].Update(cells1);
			}
		}
		void FullUpdate() {
			//std::cout << "here" << std::endl;
			UpdateLattice2();
			UpdateLattice1();
		}

		static void RetanguloCentrado(double xcentro, double ycentro, double b, double h) {

			glBegin(GL_QUADS);
			glVertex2d(xcentro-0.5*b, ycentro+0.5*h);
			glVertex2d(xcentro+0.5*b, ycentro+0.5*h);
			glVertex2d(xcentro+0.5*b, ycentro-0.5*h);
			glVertex2d(xcentro-0.5*b, ycentro-0.5*h);
			glEnd();
		}

		static void CentredHexagon(double xcentre, double ycentre, double radius) {
			glBegin(GL_TRIANGLE_FAN);
			glVertex2d(xcentre, ycentre);
			const double angleLa = 2.0*M_PI/6.0;
			for (int i=0; i<7; i++) {
				const double angle = i*angleLa;
				glVertex2d(xcentre+cos(angle)*radius, ycentre+sin(angle)*radius);
			}
			glEnd();
		}

		void Draw() const {
			const double size = 1.0/L;
			for (int i=0; i<N; i++) {
				const float color = cells1[i].TotalDensity()/8.0;
				glColor3f(color,0,0);
				RetanguloCentrado(cells1[i].x, cells1[i].y , size, size);
			}
		}

		int TotalMass() const {
			int tot=0;
			for (int i=0; i<N; i++)
				tot+=cells1[i].TotalDensity();
			return tot;
		}
	
		double TotalMomentumX() const {
			double tot=0;
			for (int i=0; i<N; i++){
				tot+=cells1[i].MomentumX();
			}
			return tot;
		}

		double TotalMomentumY() const {
			double tot=0;
			for (int i=0; i<N; i++)
				tot+=cells1[i].MomentumY();
			return tot;
		}

		friend std::ostream& operator<<(std::ostream& stream,const Lattice& c){


			for (int i=0; i<c.N; i++) {
				stream << c.cells1[i] << std::endl;
			}
			return stream;
		}
};

#endif
