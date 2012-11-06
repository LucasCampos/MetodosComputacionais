#ifndef CELL_HPP
#define CELL_HPP
#include "rules.hpp"
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <vector>
class Cell {
	private:
		int nNeighbors;
	public: 
		int neighIdx[6];
		int current;
		double x,y;
		Cell(int _current=0):nNeighbors(6), current( _current){
		}
		~Cell() {
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
		int Update(const std::vector<Cell>& lattice) const {
			int newCurr = current & (BARRIER|STATIONARY);
			newCurr |= lattice[neighIdx[0]].current & RIGHT;
			newCurr |= lattice[neighIdx[1]].current & RIGHT_DOWN;
			newCurr |= lattice[neighIdx[2]].current & LEFT_DOWN;
			newCurr |= lattice[neighIdx[3]].current & LEFT;
			newCurr |= lattice[neighIdx[4]].current & LEFT_UP;
			newCurr |= lattice[neighIdx[5]].current & RIGHT_UP;
			return rules[newCurr];
		}
		Cell& operator=(const Cell& c) {
			current = c.current;
			return (*this);
		}

		int TotalDensity() const {
			int den=0;
			int curr = current;
			while (curr > 0) {
				den += curr&1;
				curr = curr >> 1;
			}
			return den;
		}

		int isThere(int cond)const {
			return ((current&cond)/cond);
		}

		double MomentumX() const {
			double momentum=0;
			momentum +=  isThere(RIGHT);
			momentum += -isThere(LEFT);

			momentum +=  cos(M_PI/3.0)*isThere(RIGHT_UP);
			momentum += -cos(M_PI/3.0)*isThere(LEFT_UP);

			momentum +=  cos(M_PI/3.0)*isThere(RIGHT_DOWN);
			momentum += -cos(M_PI/3.0)*isThere(LEFT_DOWN);
			return momentum;
		}

		double MomentumY() const {
			double momentum =0;
			momentum += sin(M_PI/3.0)*isThere(RIGHT_UP);
			momentum += sin(M_PI/3.0)*isThere(LEFT_UP);

			momentum += -sin(M_PI/3.0)*isThere(RIGHT_DOWN);
			momentum += -sin(M_PI/3.0)*isThere(LEFT_DOWN);
			return momentum;
		}




		friend std::ostream& operator<<(std::ostream& stream,const Cell& c){

			stream << c.x << "   " << c.y << "   " << c.TotalDensity() << "\t";
			return stream;
		}
};

#endif
