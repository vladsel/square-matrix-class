#include "Matrix.h"

Matrix::Matrix(bool flag) {
	if (flag == true) {
		cout << "Input the size of the matrix: \n" "n = ";
		std::cin >> n;
		while (n <= 0) {
			if (n == 0) {
				matrix = nullptr;
				return;
			}
			cout << "\nerror of the size, try one more time:\nn = ";
			std::cin >> n;
		}
		cout << "\nInput values of the matrix:\n";
		matrix = new int *[n];
		for (size_t i = 0; i < n; i++) {
			matrix[i] = new int[n];
			for (size_t j = 0; j < n; j++) {
				std::cin >> matrix[i][j];
			}
			cout << "\n";
		}
		cout << "\n";
	}
	else {
		matrix = nullptr;
		n = 0;
	}	
}

Matrix::Matrix(const Matrix &arr) {
	if (arr.matrix != nullptr && arr.n > 0) {
		n = arr.n;
		matrix = new int *[n];
		for (size_t i = 0; i < n; i++) {
			if (arr.matrix[i] == nullptr)
				matrix[i] = nullptr;
			else {
				matrix[i] = new int[n];
				for (size_t j = 0; j < n; j++)
					matrix[i][j] = arr.matrix[i][j];
			}
		}
	}
	else {
		matrix = nullptr;
		n = 0;
	}
}

Matrix::~Matrix() {
	DeleteMatrix(matrix, n);
}

void Matrix::DeleteMatrix(int **&arr, size_t n) {
	if (arr != nullptr) {
		for (size_t i = 0; i < n; i++)
			if (arr[i] != nullptr)
				delete[] arr[i];
		delete[] arr;
		arr = nullptr;
	}
}

void Matrix::Output() {
	if (matrix != nullptr) {
		for (size_t i = 0; i < n; i++) {
			cout << "[ ";
			for (size_t j = 0; j < n; j++) {
				if (j != n - 1)
					cout << std::setw(10) << std::left << matrix[i][j];
				else
					cout << matrix[i][j];
			}
			cout << " ]" << "\n";
		}
		cout << "\n";
	}
}

size_t Matrix::GetN() {
	return n;
}

int **Matrix::GetMatrix() {
	return matrix;
}

void Matrix::SetN(size_t n) {
	if (n > 0) 
		this->n = n;
	else
		this->n = 0;
}

void Matrix::SetMatrix(int **matrix) {
	if (matrix != nullptr) {
		DeleteMatrix(this->matrix, n);
		this->matrix = matrix;
	}
	else
		this->matrix = nullptr;
}

int Matrix::Determinant() {
	if (matrix == nullptr)
		return -1;
	return DeterminantPrivate(matrix, n);
}

Matrix &Matrix::operator=(const Matrix &arr) {
	n = arr.n;
	if (matrix != nullptr)
		DeleteMatrix(matrix, n);
	matrix = new int *[n];
	for (size_t i = 0; i < n; i++) {
		matrix[i] = new int[n];
		for (size_t j = 0; j < n; j++)
			matrix[i][j] = arr.matrix[i][j];
	}
	return *this;
}

Matrix Matrix::operator+(const Matrix &arr) {
	if (matrix != nullptr && arr.matrix != nullptr && n == arr.n) {
		Matrix temp(*this);
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
				temp.matrix[i][j] += arr.matrix[i][j];
		return temp;
	}
}

Matrix Matrix::operator-(const Matrix &arr) {
	if (matrix != nullptr && arr.matrix != nullptr && n == arr.n) {
		Matrix temp(*this);
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
				temp.matrix[i][j] -= arr.matrix[i][j];
		return temp;
	}
}

Matrix Matrix::operator*(const Matrix &arr) {
	if (matrix != nullptr && arr.matrix != nullptr && n == arr.n) {
		Matrix temp;
		temp.SetN(n);
		temp.matrix = new int *[n];
		for (size_t i = 0; i < n; i++) {
			temp.matrix[i] = new int[n];
			for (size_t j = 0; j < n; j++) {
				temp.matrix[i][j] = 0;
				for (size_t k = 0; k < n; k++)
					temp.matrix[i][j] += this->matrix[i][k] * arr.matrix[k][j];
			}
		}
		return temp;
	}
}

Matrix Matrix::operator*=(int value) {
	if (matrix != nullptr) {
		for (size_t i = 0; i < n; i++)
			for (size_t j = 0; j < n; j++)
				matrix[i][j] *= value;
		return *this;
	}
}

int Matrix::DeterminantPrivate(int **arr, size_t n) {
	if (n == 1)
		return arr[0][0];
	else if (n == 2)
		return arr[0][0] * arr[1][1] - arr[0][1] * arr[1][0];
	else {
		int det = 0;
		for (size_t k = 0; k < n; k++) {
			int **min = new int *[n - 1];
			for (size_t i = 0; i < n - 1; i++)
				min[i] = new int[n - 1];
			for (size_t i = 1; i < n; i++) {
				size_t t = 0;
				for (size_t j = 0; j < n; j++) {
					if (j == k)
						continue;
					min[i - 1][t] = arr[i][j];
					t++;
				}
			}
			det += pow(-1, k + 2) * arr[0][k] * DeterminantPrivate(min, n - 1);
			DeleteMatrix(min, n - 1);
		}
		return det;
	}
}