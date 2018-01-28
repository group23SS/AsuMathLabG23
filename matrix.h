
#ifndef NUM_H
#define NUM_H
#include <iostream>
#include <vector>
#include <cstdlib>
#include <string.h>

using namespace std;
 extern int flag1 ;
class matrix
{

    double** mat;
    int nrow;
    int ncolumn;
	 public:
    int getrow();
    int getcolumn();
    void create_matrix(int rows, int columns);
    void fill(double **mat, int ro, int co , double var  );
     void breakit(string input);
    void dimension ( string input );
    void print_matrix();
    void destroy();
    matrix add(matrix b  );
    matrix operator+(matrix &b);
    matrix sub(matrix b  );
    matrix operator-(matrix &b);
    void print();
    matrix getCofactor(int r, int c);
    double getDeterminant();
    double cofactorDeterminant(int r, int c);
    matrix matrixOfCofactors();
    matrix transpose ();
    matrix multiplicationofconstant (double k) ;
    matrix inverse () ;
    matrix multiplication (matrix b );
    matrix division (matrix b );
    matrix Rdivision ();
	void random(int r, int c);
    void eye(int r, int c);
    void zeros(int r, int c);
    void ones(int r, int c);
	string getstring();


	//POSTFIX
	friend matrix ConvertToMatrix (double x);
	friend double ConvertToDouble(matrix a);

	//Trigonometric
	matrix  ElementByElementMul (matrix b);
	matrix AdditionOfConstant (double k) ;
	matrix SubtractionOfConstant (double k);
	matrix ElementByElementDiv (matrix b);
	matrix ElementByEelementPower (double k);
	matrix powerMatrix (double k);
	matrix sinMatrix ();
	matrix cosMatrix ();
	matrix tanMatrix ();
	matrix logMatrix ();
	
};
int IsDouble (matrix a);
void push(char item);
char pop();
int precedence(char symbol);
int isOperator(char symbol);
void convert(char infix[],char postfix[]);
matrix evaluatePost(char *postfix);
double evaluateD (string  infix );
matrix evaluateM (string infix);
void pushMat();


void parseandprint(string input );


#endif

