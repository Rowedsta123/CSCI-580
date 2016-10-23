#include<iostream>
#include<cstdio>
#include<string>
#include"matrix.h"
using namespace std;

	//CONSTRUCTOR:
Matrix::Matrix(int cols, int rows)
{
	if(cols < 0 || rows < 0)
	{
		cols = rows = 0;
	}
	m_matrix = new long double*[cols];
	for(int i = 0; i < cols; ++i)
	{
		*(m_matrix+i) = new long double[rows];
	}
	m_cols = cols;
	m_rows = rows;
}

	//DESTRUCTOR
Matrix::~Matrix()
{
	for(int i = 0; i < m_cols; ++i)
	{
		delete *(m_matrix+i);
	}
	delete m_matrix;
}

	//Functions

  /*\ populate
  \*\   Takes( nothing )
  \*\   Retruns( nothing )
  \*\ Procedurally fills in each element of a matrix.
  \*/
void Matrix::populate()
{
	long double in;
	for(int i = 0; i < m_rows; ++i)
	{
		for(int j = 0; j < m_cols; ++j)
		{
			printf("\n\n");
			print(j,i);
			printf("Input value for \"THIS ONE\" element:");
			cin>>in;
			set(j,i,in);
		}
	}
}


	/*\ product
	\*\		Takes( Matrix object )
	\*\		Retruns( pointer to an array of arrays of doubles [NULL] if failure )
	\*\ Takes the dot product (Matrix X Matrix passed in) and returns the result.
	\*/
Matrix* Matrix::product(const Matrix &b)
{
	if(m_cols != b.GetNRows())
	{
		printf("ERROR, bad matrix dimensions for multiplication.");
		return NULL;
	}
	Matrix* temp = new Matrix(b.GetNCols(), m_rows);
	for(int i = 0; i < m_rows; ++i)
	{
		for(int j = 0; j < b.GetNCols(); ++j)
		{
			long double sum = 0;
			for(int k = 0; k < m_cols; ++k)
			{
				sum += (get(k,i) * b.get(j,k));
			}
			temp->set(j,i,sum);
		}
	}
	return temp;
}
	/*\ set
	\*\		Takes( Int left to right pos, int up to down pos, double value )
	\*\		Retruns( bool value of secess [0] or failure [1] )
x to given value.
	\*/
bool Matrix::set(int col, int row, long double value)
{
	if(col>=0 && row>=0 && col<m_cols && row<m_rows)
	{
		*(*(m_matrix+col)+row) = value;
		return 0;
	}
	printf("Can not set element outside of matrix boundary.\n");
	return 1;
}

	/*\ get
	\*\		Takes( Int left to right pos, int up to down pos )
	\*\		Retruns( Double value at the given value )
	\*\ Retrieves the value at a given position in the matrix.
	\*/
long double Matrix::get(int col, int row) const
{
	if(col>=0 && row>=0 && col<m_cols && row<m_rows)
	{
		return *(*(m_matrix+col)+row);
	}
	//printf("Can not reach element. Outside matrix boundary.\n[%d][%d]\t[%d][%d]\n", col, row, m_cols, m_rows);
	return 0;
}

	/*\ GetNCols
	 * 		Takes( Nothing )
	 * 		Retruns( Int value :: number of columns in matrix )
	 *  Retrieves the matrix length.
	\*/
int Matrix::GetNCols() const
{
	return m_cols;
}
		
	/*\ GetNRows
	 * 		Takes( nothing )
	 * 		Retruns( Int value :: number of rows in matrix )
	 * Retrieves the matrix height.
	\*/
int Matrix::GetNRows() const
{
	return m_rows;
}
		
	/*\ print
	 * 		Takes( Nothing )
	 * 		Retruns( Nothing )
	 *  Prints a representation of the matrix to standard out.
	\*/
void Matrix::print() const
{
	for(int i = 0; i < m_rows; ++i)
	{
		for(int j = 0; j < m_cols; ++j)
		{
			printf(" [%Lf]", *(*(m_matrix+j)+i));
		}
		printf("\n");
	}
}
/*{
	for(int i = 0; i < m_rows; ++i)
	{
		for(int j = 0; j < m_cols; ++j)
		{
			printf(" [%p]", (*(m_matrix+j)+i));
		}
		printf("\n");
	}
}*/
/*{
	for(int i = 0; i < m_rows; ++i)
	{
		for(int j = 0; j < m_cols; ++j)
		{
			printf(" [%p]", *(m_matrix+j));
		}
		printf("\n");
	}
}*/
		
	/*\ print
	 * 		Takes( Int column, int row )
	 * 		Retruns( prints the matrix with the given col and row highlighted )
	 *  Prints a representation of the matrix to standard out, marking an element.
	\*/
void Matrix::print(int col, int row) const
{
	printf("   ");
	for(int i = 0; i < m_cols; ++i)
	{
		printf("     %-2d   ", i);
	}
	for(int i = 0; i < m_rows; ++i)
	{		 
		printf("\n%2d ", i);
		for(int j = 0; j < m_cols; ++j)
		{
			if(i==row && j==col)
			{
				printf("[THIS ONE]");
			}
			else 
			{
				if(i<row || (j<col && i==row))
				{
					printf("[%08.4Lf]", *(*(m_matrix+j)+i));
				}
				else
				{
					printf("[XXXXXXXX]");
				}
			}
		}
	}
	printf("\n");
}
