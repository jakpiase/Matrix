#pragma once
class Matrix
{
private:
	const int rows;
	const int cols;
	double** values;
	void clearValues();
		
public:
	Matrix(int rows,int cols);
	~Matrix();
	void print() const;
	void setValue(int row, int col, int value);
	int getValue(int row, int col) const;
	void setDiags(int offset, int value);
	void setValues(int value);
	
	Matrix solve(Matrix values) const;

	double norm2() const;
	Matrix diag() const;
	Matrix tril() const;
	Matrix triu() const;
	Matrix transpose() const;

	Matrix jacobi(Matrix const& b) const;

	Matrix operator - () const;
	Matrix operator - (Matrix const& obj) const;
	Matrix operator = (const Matrix& second);
	Matrix operator + (Matrix const& obj) const;
	Matrix operator * (Matrix const& obj) const;
};

