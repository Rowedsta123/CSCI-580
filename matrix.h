#ifndef MATRIX
#define MATRIX

class Matrix
{
	public:
	//CONSTRUCTOR:
		Matrix(int cols, int rows);
	//DESTRUCTOR
		~Matrix();
	//Functions

		/*
		**void populate();
		**Matrix product(Matrix b);
		**bool set(int col, int row, double value);
	 	**double get(int col, int row);
		**int GetNCols();
		**int GetNRows();
		**void print();
		**void print(int col, int row);
		**/
 
 		/*\ populate
  	\*\   Takes( nothing )
  	\*\   Retruns( nothing )
  	\*\ Procedurally fills in each element of a matrix.
  	\*/
		void populate();

		/*\ product
		 *		Takes( Matrix object )
		 *		Retruns( Matrix object :: result of dot product, empty on failure. )
		 * Takes the dot product (Matrix X Matrix passed in) and returns the result.
		\*/
		Matrix* product(const Matrix &b);

		/*\ set
		 *		Takes( Int left to right pos, int up to down pos, double value )
		 *		Retruns( bool value of secess [0] or failure [1] )
		 * Sets element in Matrix to given value.
		\*/
		bool set(int col, int row, long double value);

		/*\ get
		 *		Takes( Int left to right pos, int up to down pos )
		 *		Retruns( Double value at the given value )
		 * Retrieves the value at a given position in the matrix.
		\*/
		long double get(int col, int row) const;

		/*\ GetNCols
		 * 		Takes( Nothing )
		 * 		Retruns( Int value :: number of columns in matrix )
		 *  Retrieves the matrix length.
		\*/
		int GetNCols() const;
		
		/*\ GetNRows
		 * 		Takes( nothing )
		 * 		Retruns( Int value :: number of rows in matrix )
		 *  Retrieves the matrix height.
		\*/
		int GetNRows() const;
		
		/*\ print
		 * 		Takes( Nothing )
		 * 		Retruns( Nothing )
		 *  Prints a representation of the matrix to standard out.
		\*/
		void print() const;
		
		/*\ print
		 * 		Takes( Int column, int row )
	 	 * 		Retruns( prints the matrix with the given col and row highlighted )
		 *  Prints a representation of the matrix to standard out, marking an element.
		\*/
		void print(int col, int row) const;

	private:
		int m_cols;
		int m_rows;
		long double** m_matrix;
};

#endif
