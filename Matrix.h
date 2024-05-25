#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <iomanip>
#include <cmath>

using std::cout;
using std::endl;

class Matrix {
public:
	Matrix() : matrix(nullptr), n(0) {}
	Matrix(bool flag);
	Matrix(int **&_matrix, size_t _n) : matrix(_matrix), n(_n) { _matrix = nullptr; }
	Matrix(const Matrix &_matrix);
	~Matrix();
	void Output();
	size_t GetN();
	int **GetMatrix();
	void SetN(size_t n);
	void SetMatrix(int **matrix);
	int Determinant();
	Matrix &operator=(const Matrix &arr);
	Matrix operator+(const Matrix &arr);
	Matrix operator-(const Matrix &arr);
	Matrix operator*(const Matrix &arr);
	Matrix operator*=(int value);
private:
	void DeleteMatrix(int **&arr, size_t n);
	int DeterminantPrivate(int **arr, size_t n);
	int **matrix;
	size_t n;
};

#endif //MATRIX_H