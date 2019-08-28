#include <iostream>
#include <vector>
#include <fstream>
#include <ctime>
#include <cmath>
#include <map>
#include <cassert>
#include "mersenne.h"

using namespace std;

#define ARRAYELEMCOUNT(x) sizeof(x) / sizeof(x[0])

#define TAB "\t"

//Rand01IE: Get random number from [0,1)
#define Rand01IE() mersenne()
#define SeedRand(x) seed_mersenne(x)

class FCLoopUpdatefunc
//====================
{
public:
	FCLoopUpdatefunc(double* arr, const double h) : m_Array(arr), m_h(h) {}
	void operator()(const vector<int>& indeces, const int index)
	{
		m_Array[index] = (indeces[index]+0.5) * m_h;
	}
private:
	double* m_Array;
	double m_h;
};

typedef FCLoopUpdatefunc INDEXCHANGEEVENT;


//Points in midpoint method for higher than one dimensions can for example
//be generated with nested for loops, but that's not very nice way to do it
//if there are many dimensions or if the dimension count is not known beforehand.
//This class is used to get somewhat similar behavior without the need to write
//the for loops.
class CNestedForLoops
//===================
{
public:
	CNestedForLoops(int size, int endindex, INDEXCHANGEEVENT func) :
		m_IndexArray(size, 0), m_EndIndex(endindex), m_Counter(0), m_fOnIndexChange(func)
		{}
	void operator++()
	//---------------
	{
		m_Counter++;
		for(int j = 0; j+1<m_IndexArray.size(); j++)
		{
			m_IndexArray[j] = (m_IndexArray[j]+1 >= m_EndIndex) ? 0 : m_IndexArray[j]+1;
			m_fOnIndexChange(m_IndexArray, j);
			if(m_IndexArray[j] != 0) return;
		}
		m_IndexArray.back()++;
		m_fOnIndexChange(m_IndexArray, m_IndexArray.size()-1);
	}
	operator bool()
	{
		return (m_IndexArray.back() < m_EndIndex);
	}
	int GetCounter() {return m_Counter;}

private:
	vector<int> m_IndexArray;
	int m_EndIndex;
	int m_Counter;
	INDEXCHANGEEVENT m_fOnIndexChange;
};

inline double f(const double* const arr, const int size)
//--------------------------------------------------------
{
	double f = 1;
	for(int i = 0; i<size; i++) f *= 1.5*(1-arr[i]*arr[i]);
	return f;
}



int main()
//--------
{
	const int seed = time(0);
	SeedRand(seed);

	//Open file for output.
	ofstream fout("hw2extra.txt", ios::trunc);
	if(fout.fail()) {cerr << "Open failure" << endl;}
	ostream& oStrm = fout;
	oStrm.precision(12);

	oStrm << "#seed: " << seed << endl;

	//dimNMap[x] should return the number of intervals with dimension x.
	map<int,int> dimNMap;
	dimNMap[3] = 100; //When doing calculation in 3D, using 100 intervals per dimension.
	dimNMap[6] = 10;  //With 6 dims, using 10 intervals per dimension.
	dimNMap[10] = 4;
	dimNMap[13] = 3;

	//Going through chosen dimensions.
	for(map<int,int>::const_iterator iter = dimNMap.begin(); iter != dimNMap.end(); iter++)
	{
		const int dim = iter->first;
		const int Nval = iter->second;
		const double h = 1.0/Nval;
		
		oStrm << "#dim = " << dim << ", N = " << Nval
			  << ", terms in sums = " << pow(double(Nval), double(dim)) << endl;

		vector<double> x(dim, 0.5*h);
		double sum = 0;
		CNestedForLoops nfor(dim, Nval, FCLoopUpdatefunc(&x[0], h));
		for(;nfor; ++nfor)
		{
			sum += f(&x[0], x.size());
		} 
		
		const double sumblockVolume = pow(h, double(dim)); 
		sum *= sumblockVolume;

		oStrm << sum << TAB << fabs(sum-1.0);

		sum = 0;
		const int counter = nfor.GetCounter();
		assert(counter == static_cast<int>(pow(double(Nval), double(dim))+0.5));
		double sum2 = 0; //Used for calculating <f^2>
		for(int j = 0; j<counter; j++)
		{
			//Generate random vector by assigning random number to every coordinate.
			for(int k = 0; k<x.size(); k++) {x[k] = Rand01IE();}

			//Calculate function value at that point.
			double temp = f(&x[0], x.size());
			sum += temp;
			sum2 += temp*temp;
		}
		sum *= 1.0 / counter;
		sum2 *= 1.0 / counter;
		double error = fabs(sum-1.0);
		double errorOneSigma = 1.0 * sqrt((sum2 - sum*sum)/ (counter-1));
		oStrm << TAB << sum << TAB << error << TAB << errorOneSigma << endl;


	}
	return 0;
}

