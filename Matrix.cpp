#include "Matrix.h"
#include <iostream>
#include <cmath>

Matrix::Matrix(int rows, int cols): rows(rows), cols(cols)
{
	values = new double* [rows];
	for (int i = 0; i < rows; i++) {
		values[i] = new double[cols];
	}

	clearValues();
}

Matrix::~Matrix() {
	for (int i = 0; i < rows; i++) {
		delete [] values[i];
	}
	delete[] values;
}

void Matrix::print() const
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			std::cout << values[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;
}

void Matrix::setValue(int row, int col, int value)
{
	values[row][col] = value;
}

int Matrix::getValue(int row, int col) const
{
	return values[row][col];
}

void Matrix::setDiags(int offset, int value)
{
	if (rows != cols)
		throw "matrix is not square!";

	for (int i = 0; i < rows - offset; i++) {
		values[i + offset][i] = value;
		values[i][i + offset] = value;
	}
}

void Matrix::setValues(int value)
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			this->values[i][j] = value;
		}
	}
}

Matrix Matrix::solve(Matrix vector) const
{
	Matrix result(1, this->cols);

	result.values[0][0] = vector.values[0][0];

	for (int i = 1; i < this->rows; i++) {
		result.values[0][i] = vector.values[0][i];
		for (int j = 0; j < i; j++) {
			result.values[0][i] -= result.values[0][j] * this->values[i][j];
		}
		result.values[0][i] /= this->values[i][i];
	}

	return result;*/
	if (this->rows != this->cols)
		throw "invalid parameters";

	Matrix result(this->rows, 1);

	result.values[0][0] = vector.values[0][0];

	for (int i = 1; i < this->rows; i++) {
		result.values[i][0] = vector.values[i][0];
		for (int j = 0; j < i; j++) {
			result.values[i][0] -= result.values[0][j] * this->values[i][j];
		}
		result.values[i][0] /= this->values[i][i];
	}

	return result;
}

void Matrix::clearValues()
{
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			values[i][j] = 0;
		}
	}
}

double Matrix::norm2() const
{
	if (this->rows != 1 && this->cols != 1)
		throw "it is not a vector!";

	double norm = 0;

	for (int i = 0; i < this->cols; i++) {
		norm += values[0][i] * values[0][i];
	}

	norm = sqrt(norm);

	return norm;
}

Matrix Matrix::diag() const
{
	if (rows != cols) // jezeli macierz nie jest kwadratowa, wyrzuc wyjatek
		throw "matrix is not square!";

	Matrix result(rows, cols);

	for (int i = 0; i < rows; i++) {
			result.values[i][i] = this->values[i][i];
	}

	return result;
}

Matrix Matrix::tril() const
{
	if (rows != cols) // jezeli macierz nie jest kwadratowa, wyrzuc wyjatek
		throw "matrix is not square!";

	Matrix result(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i > j)
				result.values[i][j] = this->values[i][j];
		}									
	} 

	return result;
}

Matrix Matrix::triu() const
{
	if (rows != cols) // jezeli macierz nie jest kwadratowa, wyrzuc wyjatek
		throw "matrix is not square!";

	Matrix result(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			if (i < j)
				result.values[i][j] = this->values[i][j];
		}								
	}

	return result;
}

Matrix Matrix::transpose() const
{
	Matrix result(cols, rows);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.values[j][i] = this->values[i][j];
		}
	}

	return result;
}

Matrix Matrix::jacobi(Matrix const &b) const
{
	Matrix r(this->rows, 1);
	r.setValues(1);

	Matrix res(this->rows, 1);
	res.setValues(1);

	Matrix D = this->diag();
	Matrix L = this->tril();
	Matrix U = this->triu();

	this->print();


	while (res.norm2() > 0.000001) {
		L.print();
		U.print();
		Matrix LU = L + U;
		LU.print();
		Matrix LUr = LU * r;
		LUr.print();
		Matrix minusD = -D;
		minusD.print();
		r = minusD.solve(LUr);
		r.print();
		//r = r.transpose();

		res = (*this) * r;
		res.print();
		res = res - b;


		res.print();
	}



	return r;
}

Matrix Matrix::operator-() const
{
	Matrix result(rows, cols);
	
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.values[i][j] = -1 * values[i][j];
		}
	}

	return result;
}

Matrix Matrix::operator-(Matrix const& second) const
{
	if (this->cols != second.cols || this->rows != second.rows)
		throw "matrix that were given have different dimensions";

	Matrix result(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < rows; j++) {
			result.values[i][j] = this->values[i][j] - second.values[i][j];
		}
	}

	return result;
}

Matrix Matrix::operator=(const Matrix& second)
{
	Matrix result(second.rows, second.cols);

	for (int i = 0; i < second.rows; i++) {
		for (int j = 0; j < second.cols;j++) {
			result.values[i][j] = second.values[i][j];
		}
	}


	return result;
}

Matrix Matrix::operator+(Matrix const& second) const
{
	if (this->cols != second.cols || this->rows != second.rows)
		throw "matrix that were given have different dimensions";

	Matrix result(rows, cols);

	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++) {
			result.values[i][j] = this->values[i][j] + second.values[i][j];
		}
	}

	return result;
}

Matrix Matrix::operator*(Matrix const& second) const
{
	if (this->cols != second.rows)
		throw "cannot multiply";

	Matrix result(this->rows, second.cols);

	for (int i = 0; i < this->rows; i++) {
		for (int j = 0; j < second.cols; j++) {
			for (int k = 0; k < second.rows; k++) {
				result.values[i][j] += this->values[i][k] * second.values[k][j];
			}
		}
	}

	return result;
}
