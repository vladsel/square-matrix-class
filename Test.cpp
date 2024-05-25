#include "Matrix.h"

int main() {
	size_t n = 3;

	int **A = new int *[n];
	int **B = new int *[n];
	int **C = new int *[n];

	for (int i = 0; i < n; i++) {
		A[i] = new int[n];
		B[i] = new int[n];
		C[i] = new int[n];
		for (int j = 0; j < n; j++) {
			A[i][j] = (i + j) * (i + j) * (i + j);
			B[i][j] = (i + j) * (-(i + j));
			C[i][j] = (i + j) * (i + j);
		}
	}

	Matrix mat1(A, n);
	Matrix mat2(B, n);
	Matrix mat3(C, n);
	Matrix mat4(mat1);
	Matrix mat5;
	Matrix mat6;
	mat5 = mat4 + mat1;
	mat6 = mat2 - mat3;
	mat3 = mat1 * mat3;
	mat2 *= 3;

	mat1.Output();
	mat2.Output();
	mat3.Output();
	mat4.Output();
	mat5.Output();
	mat6.Output();

	cout << "\n mat3 determinant = " << mat3.Determinant() << "\n";
	cout << "\n mat1 determinant = " << mat1.Determinant() << "\n\n\n";

	return 0;
}