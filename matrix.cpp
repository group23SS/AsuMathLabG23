#include "matrix.h"
int flag1 =0 ;
int flag2 ;
int matrix::getrow()
{
    return nrow;
}

int matrix::getcolumn()
{
    return ncolumn;
}

void matrix::create_matrix(int rows, int columns)
{
    nrow=rows;
        ncolumn =columns;
        /*
        A dynamic 2D array is basically an array of pointers to arrays.
        First, we will allocate memory for an array which contains a set of pointers.
        Next, we will allocate memory for each array which is pointed by the pointers.
        The deallocation of memory is done in the reverse order of memory allocation.
        */
        this->mat = new double* [rows];

        for (int i = 0; i < rows; i++)
        {
            mat[i] = new double[columns];
        }

}

void matrix::fill(double **mat, int ro, int co, double var)
{
    mat[ro][co]=var;
}

void matrix::breakit(string input)
{
//char* buffer = new char[input.length()+1];
//strncpy(buffer, input.c_str(),input.length()+1);
   input = input.substr(input.find('[')+1);

            for(int i=0;i<this->nrow;i++)
            {
                if ( input[0]==' ')
                    input=input.substr(1);

                for(int j=0;j<this->ncolumn;j++)
                {

                string s = input;
                    if ( j == this->ncolumn -1 )
                    {
                        if ( i == this->nrow-1 )
                        {
                            s = s.substr(0,s.find(']'));
                            //cout<<"hena"<<endl;
                        }
                        else
                        {
                            s = s.substr(0,s.find(';'));
                           // cout<<" s == "<<s<<endl;
                        }
                    }

                    else{
                   s = s.substr(0,s.find(' '));
                   //cout<<" s == "<<s<<endl;
                    }

                    this->mat[i][j]= atof(s.c_str());
                    //this->fill(this->mat , i , j , atof(token)) ;
                    if ( j != ncolumn-1)
                    input = input.substr(input.find(' ')+1);
                   // cout<<endl<<input<<endl;
                }
                input = input.substr(input.find(';')+1);

                }



   /* input = input.substr(input.find('[')+1);

            for(int i=0;i<this->nrow;i++)
            {

                if ( i > 0 )
                {

                    input = input.substr(input.find(';')+1);
                    //cout<<"helo"<<input<<endl;
                    if(input[0]==' ')
                input = input.substr(input.find(' '));
                  //cout<<"helo"<<input<<endl;

                }
                //cout<<input<<endl;

                for(int j=0;j<this->ncolumn;j++)
                {
                 char *token;
                    char *text;
                    text=&input[0];

                   //  buffer=&input[0];
                    //if ( i >0 )
                        //text=&input[1];
                    if ( j==0 ){
                            //cout<<"ididtthat"<<endl;
                    token= strtok(text, " ");
                    }

                    else if ( j == this->ncolumn -1 ) {
                    if ( i == this->nrow-1 ) {
                    token=strtok(NULL ,  "]" );
                    }
                    else
                    {


                    token=strtok(NULL ,  ";" );
                    }
                    }

                    else{
                    token=strtok(NULL , " ");

                    }
                   // cout<<"row"<<i<<endl;
                     //cout<<"column"<<j<<endl;
                    //cout<<token<<endl;

                    this->mat[i][j]= atof(token);
                    //this->fill(this->mat , i , j , atof(token)) ;
                }

                }*/


            }


void matrix::dimension(string input)
{
    this->nrow=1;
            this->ncolumn=1;
            for ( int i =0 ; i<input.length(); i++)
            {

                if (input [i] == ';')
                    this->nrow++;
            }
            for ( int i =0 ; i<input.length(); i++)
            {
                int start = input.find('[');

                if ( (input[i] == ' ') && (i >start))
                    this->ncolumn++;
                    if ( (input[i]==';')|| (input[i] == ']'))
                    break;

            }
}

void matrix::print_matrix()
{
    for (int i = 0; i < this->nrow; i++)
        {
            for (int j = 0; j < this->ncolumn; j++)
            {
                cout<<this->mat[i][j]<<"\t";
            }
            cout << endl;
        }
}

void matrix::destroy()
{
    for (int i = 0; i < this->nrow; i++)
        {
            delete[] this->mat[i]; //deletes an inner array of integer;
        }

        delete[] this->mat; //delete pointer holding array of pointers;
}

matrix matrix::add(matrix b)
{
	flag1 =0 ;
    if(this->nrow != b.nrow || this->ncolumn != b.ncolumn){
            cout<<"Invalid matrix dimension "<<endl;
			flag1=1;
        }

        else
        {
            matrix c;
            c.create_matrix(b.nrow,b.ncolumn);
        for(int iR=0;iR<b.nrow;iR++)
            for(int iC=0;iC<b.ncolumn;iC++)
                c.mat[iR][iC]= (this->mat[iR][iC] + b.mat[iR][iC]);
        return c;
        }
}

matrix matrix::operator+(matrix &b)
{
    return add(b);
}

matrix matrix::sub(matrix b)
{
	flag1=0 ;
    if(this->nrow != b.nrow || this->ncolumn != b.ncolumn){
            cout<<"Invalid matrix dimension "<<endl;
			flag1 = 1;
        }
        else
        {
            matrix c;
            c.create_matrix(b.nrow,b.ncolumn);
        for(int iR=0;iR<b.nrow;iR++)
            for(int iC=0;iC<b.ncolumn;iC++)
                c.mat[iR][iC]= (this->mat[iR][iC] - b.mat[iR][iC]);
        return c;
        }
}

matrix matrix::operator-(matrix &b)
{
    return sub(b);
}

void matrix::print()
{
    cout<<'[';
        for(int ir=0;ir<nrow;ir++){
            for(int ic=0;ic<ncolumn;ic++){

            cout<< this ->mat [ir][ic];
            if(ic!=ncolumn-1)
            cout<<' ';
            }

            if(ir!=nrow-1)
            cout<<"; ";

        }
    cout<<']'<<endl;
}

matrix matrix::getCofactor(int r, int c)
{
	flag1 =0 ;
    if((nrow<=1 && ncolumn<=1)||(nrow!=ncolumn)){
            cout<<"Invalid matrix dimension "<< endl;
			flag1 =1 ;
	}
            else
        {
        matrix m;
        m.create_matrix(nrow-1 ,ncolumn-1 );
        for(int iR=0;iR<m.nrow;iR++)
            for(int iC=0;iC<m.ncolumn;iC++){
                int sR = (iR<r)?iR:iR+1;
                int sC = (iC<c)?iC:iC+1;
                m.mat[iR][iC] = mat[sR][sC];
            }return m;
        }
}





int LUPDecompose(double **A, int N, double Tol, int *P) {

    int i, j, k, imax;
    double maxA, *ptr, absA;

    for (i = 0; i <= N; i++)
        P[i] = i; //Unit permutation matrix, P[N] initialized with N

    for (i = 0; i < N; i++) {
        maxA = 0.0;
        imax = i;

        for (k = i; k < N; k++)
            if ((absA = fabs(A[k][i])) > maxA) {
                maxA = absA;
                imax = k;
            }

        if (maxA < Tol) return 0; //failure, matrix is degenerate

        if (imax != i) {
            //pivoting P
            j = P[i];
            P[i] = P[imax];
            P[imax] = j;

            //pivoting rows of A
            ptr = A[i];
            A[i] = A[imax];
            A[imax] = ptr;

            //counting pivots starting from N (for determinant)
            P[N]++;
        }

        for (j = i + 1; j < N; j++) {
            A[j][i] /= A[i][i];

            for (k = i + 1; k < N; k++)
                A[j][k] -= A[j][i] * A[i][k];
        }
    }

    return 1;  //decomposition done
}

/* INPUT: A,P filled in LUPDecompose; N - dimension.
 * OUTPUT: Function returns the determinant of the initial matrix
 */
double LUPDeterminant(double **A, int *P, int N) {

    double det = A[0][0];

    for (int i = 1; i < N; i++)
        det *= A[i][i];

    if ((P[N] - N) % 2 == 0)
        return det;
    else
        return -det;
}

	double matrix::getDeterminant ()
{
	double result=0;
	int *p = new int [nrow+1];
		matrix copy = *this;
		 if(LUPDecompose(copy.mat,nrow,0.001,p)){
			 result= LUPDeterminant(copy.mat,p,nrow);
			 return result;
		 }


}



double matrix::cofactorDeterminant(int r, int c)
{
    return this->getCofactor(r,c).getDeterminant();

}

matrix matrix::matrixOfCofactors()
{
    matrix h;
        int m=1;
        h.create_matrix(this->nrow,this->ncolumn);
        for(int i=0;i<nrow;i++){
            for(int j=0;j<ncolumn;j++){
                h.mat[i][j]=m*(this->cofactorDeterminant(i,j));
                m*=-1;
            }
        }
        return h;
}

matrix matrix::transpose()
{
	flag1 =0 ;
    matrix c ;
        int k = 0 ;
        int l = 0 ;
        if (this->ncolumn != this->nrow)
		{flag1 = 1 ;
            cout<<"Invalid matrix dimension  "<<endl;
			flag2 = 1;

		}else {
        c.create_matrix(this->ncolumn , this->nrow);
        for ( int i = 0 ; i <nrow ; i ++ ) {
            if ( k == ncolumn) k=0 ;
            if ( l == nrow) l =0 ;
            for ( int j =0 ; j <ncolumn ; j ++ ) {

                c.fill (c.mat , k , l , this -> mat [i][j] );
                k ++ ;

            }

            l++;
        }
        }
    return c;

}

matrix matrix::multiplicationofconstant(double k)
{
    matrix c ;
        c.create_matrix(this->nrow, this->ncolumn) ;
        for ( int i = 0 ; i <this->nrow ; i ++ )
        {
            for ( int j =0 ; j <this -> ncolumn ; j ++ ) {
                c.mat[i][j] = k * this->mat[i][j];
            }
        }
        return c ;
}

matrix matrix::inverse()
{
	flag1 =0 ;
    matrix c ;

        double det = this->getDeterminant();
        if(det==0)
		{
            cout<<"Invalid to get the inverse of the second matrix "<< endl;
			flag2 = 1;
			flag1 =1 ;
		} else
        {


        c.create_matrix(this->nrow, this->ncolumn);
        c = this->matrixOfCofactors() ;

            c = c.transpose() ;
            c= c.multiplicationofconstant(((double)1/det)) ;
        return c ;
        }

}

matrix matrix::multiplication(matrix b)
{ flag1 =0 ;
    matrix c ;
          if (this->getcolumn()!=b.getrow()){
            cout<<" invalid multiplication "<< endl ;
			flag1=1 ;
		  } else
          {
          c.create_matrix(this->getrow(), b.getcolumn());
          for (int i = 0 ; i <c.getrow() ; i ++ ){
              for (int j =0 ; j <c.getcolumn() ; j ++ ) {
                  for ( int k =0 ; k  <b.getrow() ; k ++ ) {
                      if (k==0) c.mat[i][j]=0;

                  c.mat[i][j]=c.mat[i][j]+((this->mat [i][k])* (b.mat[k][j]));
                  }

          }
          }
          return c ;
          }


}

matrix matrix::division(matrix b)
{
	flag1 =0 ;
	//cout<<getDeterminant()<<endl;
    if ((this->getcolumn()!=b.getrow())||(getDeterminant()==0)){
                cout<<"Invalid operation "<< endl;
				flag1 =1 ;
	}else
        {


        matrix c ;
		matrix inverse ;
        c.create_matrix(this->nrow, b.ncolumn);
		inverse.create_matrix( b.nrow , b.ncolumn);
        inverse =b.inverse() ;
        c =this->multiplication(inverse) ;

        return c ;
         }

}

matrix matrix::Rdivision()
{
    matrix c;
	flag1=0;
	int flag=0 ;
    c.create_matrix(this->nrow , this->ncolumn);

    for (int i=0; i<this->nrow;i++)
	{
        for (int j=0;j<this->ncolumn;j++)
        {
            if (this->mat[i][j]==0)
			{
				cout<<"Invalid operation  "<<endl;
				flag1=1 ;
				flag = 1  ;
				c.destroy();
				break ;

			}

			c.mat[i][j]=(float)1/mat[i][j];

		}
		if (flag) break ;

        }


		return c;
      }


matrix matrix:: ElementByElementMul (matrix b){
	flag1 =0 ;
    if(this->nrow != b.nrow || this->ncolumn != b.ncolumn){
            cout<<"Invalid matrix dimension "<<endl;
			flag1=1;
        }

        else
        {
            matrix c;
            c.create_matrix(b.nrow,b.ncolumn);
        for(int iR=0;iR<b.nrow;iR++)
            for(int iC=0;iC<b.ncolumn;iC++)
                c.mat[iR][iC]= (this->mat[iR][iC] * b.mat[iR][iC]);
        return c;
        }
}
matrix matrix::AdditionOfConstant(double k)
{
    matrix c ;
        c.create_matrix(this->nrow, this->ncolumn) ;
        for ( int i = 0 ; i <this->nrow ; i ++ )
        {
            for ( int j =0 ; j <this -> ncolumn ; j ++ ) {
				c.mat[i][j] =  this->mat[i][j] +k;
            }
        }
        return c ;
}

matrix matrix::SubtractionOfConstant (double k) {
	 matrix c ;
        c.create_matrix(this->nrow, this->ncolumn) ;
        for ( int i = 0 ; i <this->nrow ; i ++ )
        {
            for ( int j =0 ; j <this -> ncolumn ; j ++ ) {
				c.mat[i][j] =  this->mat[i][j] - k;
            }
        }
        return c ;
}
matrix matrix:: ElementByElementDiv (matrix b){
	flag1 =0 ;
    if(this->nrow != b.nrow || this->ncolumn != b.ncolumn){
            cout<<"Invalid matrix dimension "<<endl;
			flag1=1;
			matrix c;
            c.create_matrix(b.nrow,b.ncolumn);
			return c;
        }

        else
        {
            matrix c;
            c.create_matrix(b.nrow,b.ncolumn);
        for(int iR=0;iR<b.nrow;iR++)
            for(int iC=0;iC<b.ncolumn;iC++){
				if(b.mat[iR][iC]==0){
					cout<< "Invalid division"<<endl;
					flag1=1;
					return c;
				}

					c.mat[iR][iC]= (this->mat[iR][iC] / b.mat[iR][iC]);}
        return c;
        }
}



matrix matrix::ElementByEelementPower (double k)
{
    matrix c ;
        c.create_matrix(this->nrow, this->ncolumn) ;
        for ( int i = 0 ; i <this->nrow ; i ++ )
        {
            for ( int j =0 ; j <this -> ncolumn ; j ++ ) {
                c.mat[i][j] = pow(( this->mat[i][j]),k);
            }
        }
        return c ;
}


matrix matrix:: powerMatrix (double k){
	 matrix c ;
        c.create_matrix(this->nrow, this->ncolumn) ;
		c=*this;
		for ( int i = 1 ; i <k ; i ++ )
        {

                c =c.multiplication(*this) ;

        }
        return c ;
}




matrix matrix::sinMatrix ()
{
    matrix c ;
        c.create_matrix(this->nrow, this->ncolumn) ;
        for ( int i = 0 ; i <this->nrow ; i ++ )
        {
            for ( int j =0 ; j <this -> ncolumn ; j ++ ) {
                c.mat[i][j] = sin( (this->mat[i][j])/*3.14159265/180*/);

            }
        }
        return c ;
}
matrix matrix::cosMatrix ()
{
    matrix c ;
        c.create_matrix(this->nrow, this->ncolumn) ;
        for ( int i = 0 ; i <this->nrow ; i ++ )
        {
            for ( int j =0 ; j <this -> ncolumn ; j ++ ) {
                c.mat[i][j] = cos( (this->mat[i][j])*3.14159265/180);
            }
        }
        return c ;
}
matrix matrix::tanMatrix ()
{
    matrix c ;
        c.create_matrix(this->nrow, this->ncolumn) ;
        for ( int i = 0 ; i <this->nrow ; i ++ )
        {
            for ( int j =0 ; j <this -> ncolumn ; j ++ ) {
                c.mat[i][j] = tan( (this->mat[i][j])*3.14159265/180);
            }
        }
        return c ;
}
matrix matrix::logMatrix ()
{
    matrix c ;
        c.create_matrix(this->nrow, this->ncolumn) ;
        for ( int i = 0 ; i <this->nrow ; i ++ )
        {
            for ( int j =0 ; j <this -> ncolumn ; j ++ ) {
                c.mat[i][j] = log10( this->mat[i][j]);
            }
        }
        return c ;
}
	void pushMat(){
	matrix c;
	c.create_matrix(2,2);
	c.breakit("[2 2; 2 2]");
	matrixName.push_back('C');
	matrices.push_back(c);
	}

matrix ConvertToMatrix (double x){
	matrix a;
	a.create_matrix(1,1);
	a.mat[0][0]=x;
	return a;
}

double ConvertToDouble (matrix a){
	double x=0;
	if (a.ncolumn==1 && a.nrow==1){
		x=a.mat[0][0];
	}
	return x;
}

int IsDouble (matrix a){
	if (a.getrow()==1 && a.getcolumn()==1)
		return 1;
	else
		return 0;

}



char stack[70];
char stack_dot[70];
int top = -1;
int top_dot=-1;

void push(char item) {
   stack[++top] = item;
}

char pop() {
   return stack[top--];
}

void push_dot(char item) {
   stack_dot[++top_dot] = item;
}

char pop_dot() {
   return stack_dot[top_dot--];
}


//returns precedence of operators
int precedence(char symbol) {

   switch(symbol) {
      case '+':
      case '-':
         return 2;
         break;
      case '*':
      case '/':

         return 3;
         break;
      case '^':
	  case '.':
	  case 'i':
	  case 'a':
	  case 'c':
	  case 'q':
	  case 'g':
         return 4;
         break;
      case '(':
      case ')':
      case '#':
         return 1;
         break;
   }
}

//check whether the symbol is operator?
int isOperator(char symbol) {

   switch(symbol) {
      case '+':
      case '-':
      case '*':
      case '/':
      case '^':
      case '(':
      case ')':
	  case '.':
	  case 'i':
	  case 'a':
	  case 'c':
	  case 'q':
	  case 'g':

         return 1;
      break;
         default:
         return 0;
   }
}


double flag10 [100];
int flagint=0;
char postfix_dot[100];

int matrixIndex;
bool existed=0;
bool isMatrix=0;
//converts infix expression to postfix


void convert(char infix[],char postfix[]) {

	for (int a=0;a<100;a++)
		flag10[a]=0;


	isMatrix=0;
   int i,symbol,j = 0;
   stack[++top] = '#';

   for(i = 0;i<strlen(infix);i++) {
      symbol = infix[i];

	 if ( (i==0) && (symbol>=65 && symbol<=90) ){
		  isMatrix=1;
		  for (int a=0;a<matrixName.size();a++){
			  if (matrixName[a] == infix[0]){
				  matrixIndex=a;
			  existed=1;
			 break;
			  }
			  else
				  existed=0;
		  }
		  if (existed==0)
			  matrixName.push_back(symbol);


		  continue;
	  }



	 if ((isOperator(symbol)==0) && ( !isdigit(symbol)) && !(symbol>=65 && symbol<=90) )
		  continue;

	  if (symbol=='.' && isOperator(infix[i+1]))
		  continue;


	  else if (symbol=='n' || symbol=='o' || symbol=='s' || symbol=='r' || symbol=='t' || symbol=='l' )
		  continue;
	  else if (symbol=='-'){
		  if ( (j==0)|| (infix[i-1] != ' ' && !isdigit(infix[i-1]) && infix[i-1] != '.' && !(infix[i-1]>=65 && infix[i-1]<=90)) ||  (infix[i-1]==' ' && (!isdigit(infix[i-2])) && infix[i-2] != '.' && !(infix[i-1]>=65 && infix[i-1]<=90)) ){
		  postfix[j]='0';
		  j++;

	  }

	  }
      if(isOperator(symbol) == 0) {
         postfix[j] = symbol;

		 flag10[j]=symbol;



		 flagint++;

		 j++;

      } else {
		  if (flagint==1)
			  flag10[j-1]=0;

		  flagint=0;
         if(symbol == '(') {
            push(symbol);
			push_dot(symbol);
         }else {
            if(symbol == ')') {

               while(stack[top] != '(') {

				   postfix[j] = pop();
				   if (pop_dot() == '.' )
					   postfix_dot[j]='.';
				   else
					   postfix_dot[j]=postfix[j];


                  j++;
               }
			   pop_dot();
               pop();//pop out (.
            } else {
               if(precedence(symbol)>precedence(stack[top])) {
				   if (infix[i-1]=='.')
					   push_dot('.');
				   else
					   push_dot(symbol);
                  push(symbol);
               }else {

                  while(precedence(symbol)<=precedence(stack[top])) {

					   postfix[j] = pop();

				   if (pop_dot() == '.' )
					   postfix_dot[j]='.';
				   else
					   postfix_dot[j]=postfix[j];

                     j++;
                  }
			   if (infix[i-1]=='.')
					   push_dot('.');
			   else
				   push_dot(symbol);

			   push(symbol);
               }
            }
         }
      }
   }

   while(stack[top] != '#') {
      postfix[j] = pop();

				   if (pop_dot() == '.' )
					   postfix_dot[j]='.';
				   else
					   postfix_dot[j]=postfix[j];
      j++;
   }

   postfix[j]='\0';//null terminate string.
   postfix_dot[j]='\0';
top = -1;
top_dot=-1;
flagint=0;



}
//evaluates postfix expression
matrix evaluatePost(char *postfix){

int top_matrix = -1;
matrix stack_matrix[100];
int currentMatrix;


   char ch;
   int i = 0;
   matrix operand1,operand2;


	   while( (ch = postfix[i]) != '\0') {


		   if (flag10[i] !=0 && flag10[i+1] !=0 ){

			   double x=(double)(((flag10[i]-'0')*10)+flag10[i+1]-'0');
			   stack_matrix[++top_matrix] =  ConvertToMatrix(x);

			   i+=2;
			   continue;
		   }


		   else  if( isdigit(ch) ) {

		 stack_matrix[++top_matrix] = ConvertToMatrix(ch-'0');

	  }
		   else if (ch>=65 && ch<=90){

			   for (int a=0;a<matrixName.size();a++){
				   if (matrixName[a]==ch){
					   currentMatrix=a;
					   break;
				   }

			   }
			   stack_matrix[++top_matrix]= matrices[currentMatrix];
		   }


	  else {
         //Operator,pop two  operands
         operand2 = stack_matrix[top_matrix--];
		 if (ch != 'c' && ch !='i' && ch !='a' && ch != 'g' && ch !='q')
         operand1 = stack_matrix[top_matrix--];
		 if ( ch=='/' && IsDouble(operand2) && ConvertToDouble(operand2)==0)
				 throw("Infinity");


		 switch(ch) {

            case '+':
				if (postfix_dot[i]=='.' && IsDouble(operand2)){

					stack_matrix[++top_matrix]=( operand1.AdditionOfConstant(ConvertToDouble(operand2)) );
				}
				else{
               stack_matrix[++top_matrix]=(operand1+operand2);

				}
               break;
            case '-':
			if (postfix_dot[i]=='.' && IsDouble(operand2)){

					stack_matrix[++top_matrix]=( operand1.SubtractionOfConstant(ConvertToDouble(operand2)) );
				}
				else{
               stack_matrix[++top_matrix]=(operand1-operand2);

				}
               break;
            case '*':
				if (postfix_dot[i]=='.'){
					if (IsDouble(operand2))
						stack_matrix[++top_matrix]=( operand1.multiplicationofconstant( ConvertToDouble(operand2) ) );
					else if (IsDouble(operand1))
						stack_matrix[++top_matrix]=( operand2.multiplicationofconstant( ConvertToDouble(operand1) ) );
					else
						stack_matrix[++top_matrix]=(operand1.ElementByElementMul(operand2) );

				}
				else
					stack_matrix[++top_matrix]=(operand1.multiplication(operand2));
               break;
            case '/':
				if (postfix_dot[i]=='.'){
					if (IsDouble(operand2))
						stack_matrix[++top_matrix]=( operand1.multiplicationofconstant( 1/( ConvertToDouble(operand2)) ) );
					else if (IsDouble(operand1)){
						if (ConvertToDouble(operand1)== 1)
						stack_matrix[++top_matrix]=( operand2.Rdivision() );
						else
							stack_matrix[++top_matrix]=( operand2.Rdivision().multiplicationofconstant( ConvertToDouble(operand1) ) );
					}
					else
						stack_matrix[++top_matrix]=(operand1.ElementByElementDiv(operand2) );


				}
				else if (IsDouble(operand2))
					stack_matrix[++top_matrix]=(operand1.ElementByElementDiv(operand2) );

				else
					stack_matrix[++top_matrix]= operand1.division(operand2);
               break;
			case '^':

				 if (postfix_dot[i]=='.' || IsDouble(operand1)){
					stack_matrix[++top_matrix]=operand1.ElementByEelementPower (ConvertToDouble(operand2));

				}
				else{
					stack_matrix[++top_matrix]=operand1.powerMatrix( ConvertToDouble(operand2) );

		 }

				break;

			case '.':
				if (ConvertToDouble(operand2)<10)
				stack_matrix[++top_matrix]=ConvertToMatrix ( (ConvertToDouble(operand1) + (ConvertToDouble(operand2)/10)) );
				else
					stack_matrix[++top_matrix]=ConvertToMatrix ( (ConvertToDouble(operand1) + (ConvertToDouble(operand2)/100)) );
				break;
			case 'i':
		            stack_matrix[++top_matrix]=operand2.sinMatrix();

				break;
			case 'a':
					stack_matrix[++top_matrix]=operand2.tanMatrix();
				break;
			case'c':
				stack_matrix[++top_matrix]=operand2.cosMatrix();
				break;
			case 'q':
				stack_matrix[++top_matrix]=operand2.powerMatrix(0.5);
				break;
			case 'g':
				stack_matrix[++top_matrix]=operand2.logMatrix();
				break;


         }
      }
	  i++;

   }
   if (isMatrix==1){
   if (existed==0)
	   matrices.push_back(stack_matrix[top_matrix]);
   else
	  matrices[matrixIndex]= stack_matrix[top_matrix];
   }

  // existed=0;
   return stack_matrix[top_matrix];


}



matrix evaluateM (string infix){
    char buffer [100];
	strcpy(buffer,infix.c_str());


	char postfix[100];
	convert(buffer,postfix);

	return evaluatePost(postfix);
}

double evaluateD (string infix){
	char buffer [100];
	strcpy(buffer,infix.c_str());

	return ConvertToDouble(evaluateM(buffer));
}


