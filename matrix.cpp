#include "matrix.h"
#include <math.h>
#include <cstdlib>
int flag1 =0 ;
int flag2 ;
vector<char> matrixName;
vector<matrix> matrices;



matrix matrix::division(matrix b)
{
     matrix c ;
     c.create_matrix(this->nrow, b.ncolumn);
	//flag1 =0 ;
	matrix X ;
	X.copymatrix(*this);
	//cout<<getDeterminant()<<endl;
    if ((this->getcolumn()!=b.getrow())||(X.getDeterminant()==0)){
                cout<<"Invalid operation "<< endl;
				flag1 =1 ;
				return c ;
	}else
        {
  
        c.copymatrix(this->multiplication(b.inverse())) ;

        return c ;
         }

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
             m*=-1;
        }
        return h;
}




matrix matrix::transpose()
{
	//flag1 =0 ;
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
                //cout<<this->mat[i][j]<<endl<<k<<"    "<<l<<endl;

                c.fill ( k , l , mat [i][j] );
                k++ ;

            }

            l++;
        }
        }
        //c.print();
    return c;

}


void matrix::copymatrix(matrix a)
{
    this->nrow=a.nrow;
    this->ncolumn=a.ncolumn;

    mat= new double *[nrow];

    for(int i =0 ; i <nrow ; i ++ )
    {
        mat[i] = new double [ncolumn];
        for ( int j =0 ; j <ncolumn ; j ++ )
            {
            mat[i][j] = a.mat[i][j];
            }
    }
}


matrix matrix::inverse()
{
	//flag1 =0 ;
    matrix c ;
    //print();
    matrix B ;
    B.copymatrix(*this);


        double det = this->getDeterminant();
        //B.print();
       // cout<<det<<endl;
        if(det==0)
		{
            cout<<"Invalid to get the inverse of the second matrix "<< endl;
			flag2 = 1;
			flag1 =1 ;
			return c ;
		} else
        {


        c.create_matrix(this->nrow, this->ncolumn);
       // B.transpose().print();
        c.copymatrix(B.matrixOfCofactors()) ;


        c.copymatrix(c.transpose()) ;
        c.copymatrix(c.multiplicationofconstant(((double)1/det))) ;
        

        return c ;
        }

}





void matrix::create_matrixandfill(int nrow,int ncolumn,vector <double> myelements, vector<int> row, vector <int> column)
{
    //flag1=0;
    this->nrow=nrow;
    this->ncolumn =ncolumn;
        /*
        A dynamic 2D array is basically an array of pointers to arrays.
        First, we will allocate memory for an array which contains a set of pointers.
        Next, we will allocate memory for each array which is pointed by the pointers.
        The deallocation of memory is done in the reverse order of memory allocation.
        */
        this->mat = new double* [nrow];

        for (int i = 0; i <nrow; i++)
        {
            mat[i] = new double[ncolumn];
        }
        if ( myelements.size() != nrow*ncolumn){
        cout<<"invalid dimensions "<<endl;
        flag1=1;
        return ;
        }

        for(int i =0 ; i <myelements.size() ; i ++ ){
               // cout<<myelements[i]<<endl;
               // cout<<row[i]<<"      "<<column[i]<<endl;
        mat[row[i]][column[i]]=myelements[i];
        }

}


string matrix::getstring()
{
    char buffer[100];
    if ( nrow==1&&ncolumn==1){
         sprintf(buffer,"%g", mat[0][0]);
         return buffer;
    }
    string s="";
    s+="[";
    for(int i=0 ;i<nrow;i++)
    {
        for(int j=0;j<ncolumn;j++)
        {

            sprintf(buffer,"%g", mat[i][j]);
            s+=buffer;
             if(j!=ncolumn-1)
            s+=" ";
        }



            if(i!=nrow-1)
            s+=";";
    }
    s+="]";
    return s;
}

void matrix:: Build_matrix(string input)
{
	int counter=0,insidebracket=0 , sizecolumn=1 ,fillingcolumn=0 ,sizerow=1,fillingrow=0,saverow=0,savecolumn=0,aftercomma=0,semicoloncounter=0;
     matrix put_element_into_matrix;
     bool numeric =0 ;

	vector <int>row;
	vector <int>column;
	vector<double>myelements;
	string s=input.substr(input.find('[')+1),element;
     for(int i=0;i<matrices.size();i++)
     {
         int pos=s.find(matrixName[i]);
         if(pos!=-1)
         {

            s.replace(pos,1,matrices[i].getstring());
           // cout<<endl<<input<<endl;
         }

     }
     //cout<<s<<endl;

     //string s=input.substr(input.find('[')+1),element;
     //s=input.substr(input.find('[')+1),element;
     int length=s.length();

     for(int h=0; h<s.length();h++)
     {
         if(s[h]==';' && s[h+1]==' ')
            s.erase(h+1,1);
     }
      for(int h=0; h<s.length();h++)
     {
         if(s[h]==',' && s[h+1]==' ')
            s.erase(h+1,1);
     }
      for(int h=0; h<s.length();h++)
     {
         if(s[h]==' ' && s[h+1]==' '){
            s.erase(h,1);
            h--;
         }
     }

     if ( s[s.length()-1]==';')
        s.erase(s.length()-1,1);

     length=s.length();
//cout<<endl<<s<<endl;

	while(counter<length)
	{
	    //cout<<"             "<<s[counter]<<"  "<<length<<"   "<<counter<<endl;
	if(s[counter]==']')
	{
			if(numeric){
                //matrix
                /*if(element[0]>='A' && element[0]<='Z')
                {

                    int index;
                    for(int i =0 ; i <= matrixName.size() ; i ++ ){

                    if(element[0]==matrixName[i])
                    index=i ;

                     break;
                    }


                    for(int i = 0 ; i <=matrices[index].getrow() ; i ++ )
                        for ( int j = 0 ; j <matrices[index].getcolumn () ; j ++ ){

                    myelements.push_back(matrices[index].mat[i][j]);

                    row.push_back(fillingrow+i);
                    column.push_back(fillingcolumn+j);
                        }
                        fillingrow+=matrices[index].getrow()-1;
                        fillingcolumn+=matrices[index].getcolumn()-1;

                }*/


                row.push_back(fillingrow);
				column.push_back(fillingcolumn);
                //cout<<element<<endl;
               // cout<<fillingrow<<"	  "<<fillingcolumn<<endl;
               myelements.push_back(evaluateD(element));

				//myelements.push_back(atof(element.c_str()));



				//	cout<<element<<endl;
				//	cout<<sizerow<<"	  "<<sizecolumn<<endl;
				//  cout<<fillingrow<<"	  "<<fillingcolumn<<endl;
			//create w ektb
		}
		insidebracket=0;
		counter++;
		numeric =0;
		element="";
		continue;

	}
		else if(s[counter]=='[')
	{
		//this for the semicolon that comes after a bracket
		//don't forget to turn it to 0
		if(s[counter-1]!=';' && fillingrow) {

				//cout<<endl<<saverow<<"           "<<savecolumn<<endl;
		fillingrow=saverow ;
        fillingcolumn=savecolumn+1;
		if(saverow==0)
		 sizecolumn++;
		insidebracket=0;
		aftercomma=1;
		numeric =0;
		element="";

		}
		insidebracket=1;

		counter++;
		continue;

	}
	else if ( s[counter]==' ')
	{
	    /*if ( (numeric ==0 ) && s[counter+1]==' '){
                s.erase(counter ,1);
                length--;
            counter++ ;
            continue;
	    }*/
		if(numeric){
               /* if(element[0]>='A' && element[0]<='Z')
                {

                    int index;
                    f
                    or(int i =0 ; i <= matrixName.size() ; i ++ ){
                    if(element[0]==matrixName[i]){
                    index=i ;
                    break;
                    }


                    }


                    for(int i = 0 ; i <matrices[index].getrow() ; i ++ ){
                        for ( int j = 0 ; j <matrices[index].getcolumn () ; j ++ ){
                    myelements.push_back(matrices[index].mat[i][j]);


                    row.push_back(fillingrow+i);
                    column.push_back(fillingcolumn+j);
                        }
                    }
                    //fillingrow+=matrices[index].getrow();
                    fillingcolumn+=matrices[index].getcolumn();
                    //cout<<"lll"<<fillingrow<<" "<<fillingcolumn<<endl;

                }*/

                 //cout<<atof(element.c_str())<<endl;
                row.push_back(fillingrow);
				column.push_back(fillingcolumn);
				//cout<<fillingrow<<"	  "<<fillingcolumn<<endl;
				//cout<<element<<endl;


				myelements.push_back(evaluateD(element));

			/*row.push_back(fillingrow);
				column.push_back(fillingcolumn);
				myelements.push_back(atof(element.c_str()));*/
				//cout<<element<<endl;
				//cout<<sizerow<<"	  "<<sizecolumn<<endl;
				//cout<<fillingrow<<"	  "<<fillingcolumn<<endl;
			//create w ektb
		}
		if (s[counter-1]==']' && s[counter+1]!='[')
		{
		   // cout<<"hii";
            fillingcolumn=0;
            fillingrow++;
            sizerow++;
        }
        else
            fillingcolumn++;
		if(fillingrow==0)
		sizecolumn++;
		numeric =0;
		element="";
	}
		else if ( s[counter]==';')
	{

		if(numeric){
               /* if(element[0]>='A' && element[0]<='Z')
                {

                    int index;
                    for(int i =0 ; i <= matrixName.size() ; i ++ ){
                    if(element[0]==matrixName[i]){
                    index=i ;
                    break;
                    }

                    }
                    for(int i = 0 ; i <=matrices[index].getrow() ; i ++ )
                        for ( int j = 0 ; j <matrices[index].getcolumn () ; j ++ ){
                    myelements.push_back(matrices[index].mat[i][j]);

                    row.push_back(fillingrow+i);
                    column.push_back(fillingcolumn+j);
                        }
                        fillingrow+=matrices[index].getrow()-1;
                        fillingcolumn+=matrices[index].getcolumn()-1;
                }
                else *//* numeric with or without operation */

                         //cout<<"problem " <<endl;
                row.push_back(fillingrow);
				column.push_back(fillingcolumn);
				//  cout<<atof(element.c_str())<<endl;
				//  cout<<fillingrow<<"	  "<<fillingcolumn<<endl;
				//cout<<element<<endl;
				myelements.push_back(evaluateD(element));

				//myelements.push_back(atof(element.c_str()));


			//cout<<element<<endl;
				//cout<<sizerow<<"	  "<<sizecolumn<<endl;
				//cout<<fillingrow<<"	  "<<fillingcolumn<<endl;
			//create w ektb
		}
		if(aftercomma)
		{
            fillingrow++;

		}

		else if(insidebracket){
                 semicoloncounter++;
		    if(semicoloncounter==1)
		    {
		       saverow=fillingrow;
		    }
			savecolumn=fillingcolumn;
			fillingrow++;
			sizerow++;
			fillingcolumn=0;
		}
		else{

			sizerow++;
			fillingrow++;
			fillingcolumn=0;

		}

		if(fillingrow==sizerow)
        {

        //cout<<endl<<"kay"<<fillingrow<<endl<<sizerow<<endl;
		aftercomma=0;
	}
		numeric =0;
		element="";
	}
	/*else if ( s[counter]==',')
	{
		//cout<<endl<<saverow<<"           "<<savecolumn<<endl;
		fillingrow = saverow ;
        fillingcolumn=savecolumn+1;
		if(saverow==0)
		sizecolumn++;
		insidebracket=0;
		aftercomma=1;
		numeric =0;
		element="";
	}*/
	else {
		element+=s[counter];
		numeric =1 ;
	}


	   counter++;
	}


	create_matrixandfill(sizerow,sizecolumn,myelements,row,column);


}
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

void matrix::fill( int ro, int co, double var)
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
     matrix c;
            c.create_matrix(b.nrow,b.ncolumn);
	//flag1 =0 ;
    if(this->nrow != b.nrow || this->ncolumn != b.ncolumn){
            cout<<"Invalid matrix dimension "<<endl;
			flag1=1;
			return c ;
        }

        else
        {

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
    matrix c;
            c.create_matrix(b.nrow,b.ncolumn);
	//flag1=0 ;
    if(this->nrow != b.nrow || this->ncolumn != b.ncolumn){
            cout<<"Invalid matrix dimension "<<endl;
			flag1 = 1;
			return c;
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

    //cout<<'[';
    printf("\n");
        for(int ir=0;ir<nrow;ir++){
            for(int ic=0;ic<ncolumn;ic++){
            if (ic==0)
                printf("     ");
            printf("%g",mat[ir][ic]);

            //cout<< this ->mat [ir][ic];
            if(ic!=ncolumn-1)
                printf("     ");

            //cout<<' ';
            }

            if(ir!=nrow-1)
             printf("\n");

            //cout<<"; ";

        }
        printf("\n");
    //cout<<']'<<endl;
}

matrix matrix::getCofactor(int r, int c)
{
	//flag1 =0 ;
        matrix m;
        m.create_matrix(nrow-1 ,ncolumn-1 );
    if((nrow<=1 && ncolumn<=1)||(nrow!=ncolumn)){
            cout<<"Invalid matrix dimension "<< endl;
			flag1 =1 ;
return m;
	}
            else
        {

        for(int iR=0;iR<m.nrow;iR++)
            for(int iC=0;iC<m.ncolumn;iC++){
                int sR = (iR<r)?iR:iR+1;
                int sC = (iC<c)?iC:iC+1;
                m.mat[iR][iC] = mat[sR][sC];
            }return m;
        }
}


/* INPUT: A - array of pointers to rows of a square matrix having dimension N
 *        Tol - small tolerance number to detect failure when the matrix is near degenerate
 * OUTPUT: Matrix A is changed, it contains both matrices L-E and U as A=(L-E)+U such that P*A=L*U.
 *        The permutation matrix is not stored as a matrix, but in an integer vector P of size N+1
 *        containing column indexes where the permutation matrix has "1". The last element P[N]=S+N,
 *        where S is the number of row exchanges needed for determinant computation, det(P)=(-1)^S
 */
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


matrix matrix::multiplication(matrix b)
{ 
//flag1 =0 ;
    matrix c ;
    c.create_matrix(this->getrow(), b.getcolumn());
          if (this->getcolumn()!=b.getrow()){
            cout<<" invalid multiplication "<< endl ;
			flag1=1 ;
			return c ;
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





matrix matrix::Rdivision()
{
    matrix c;
	//flag1=0;
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




/*
***********************************************************************************************************
***********************************************************************************************************
******************************************* Trigonometric *************************************************
***********************************************************************************************************
***********************************************************************************************************
*/





matrix matrix:: ElementByElementMul (matrix b){
            matrix c;
            c.create_matrix(b.nrow,b.ncolumn);
    if(this->nrow != b.nrow || this->ncolumn != b.ncolumn){
            cout<<"Invalid matrix dimension "<<endl;
			flag1=1;
return c;
        }

        else
        {

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
	            matrix c;
            c.create_matrix(b.nrow,b.ncolumn);
    if(this->nrow != b.nrow || this->ncolumn != b.ncolumn){
            cout<<"Invalid matrix dimension "<<endl;
			flag1=1;
                          return c;
        }

        else
        {

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



matrix matrix:: DivisionByConst(double k){
matrix c;
c.create_matrix(this->nrow,this->ncolumn);

if(k!=0){
for(int i=0;i<nrow;i++){
for(int j=0;j<ncolumn;j++){
c.mat[i][j]=this->mat[i][j] / k;
}
}
}
else {
cout<< "Invalid Division"<<endl;
flag1=1;
}
return c;
}
matrix matrix::sinMatrix ()
{
    matrix c ;
        c.create_matrix(this->nrow, this->ncolumn) ;
        for ( int i = 0 ; i <this->nrow ; i ++ )
        {
            for ( int j =0 ; j <this -> ncolumn ; j ++ ) {
                c.mat[i][j] = sin( (this->mat[i][j]));

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
                c.mat[i][j] = cos( (this->mat[i][j]));
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
                c.mat[i][j] = tan( (this->mat[i][j]));
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


/*
***********************************************************************************************************
***********************************************************************************************************
************************************************* POSTFIX *************************************************
***********************************************************************************************************
***********************************************************************************************************
*/

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
		  if ( (j==0)|| (infix[i-1] != ' ' && !isdigit(infix[i-1]) && infix[i-1] != '.' && !(infix[i-1]>=65 && infix[i-1]<=90) && (infix[i-1] != ')'))  ||  (infix[i-1]==' ' && (!isdigit(infix[i-2])) && infix[i-2] != '.' && !(infix[i-2]>=65 &&
                                                                                                                                                                                                                           infix[i-2]<=90) && (infix[i-2] != ')')) ){
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
						stack_matrix[++top_matrix]= operand1.DivisionByConst(ConvertToDouble (operand2) );
					else if (IsDouble(operand1)){
						if (ConvertToDouble(operand1)== 1)
						stack_matrix[++top_matrix]=( operand2.Rdivision() );
						else
							stack_matrix[++top_matrix]=( operand2.Rdivision().multiplicationofconstant( ConvertToDouble(operand1) ) );
					}
					else{

						stack_matrix[++top_matrix]=(operand1.ElementByElementDiv(operand2) );
					}


				}

				else if (IsDouble(operand2))
					stack_matrix[++top_matrix]= operand1.DivisionByConst( ConvertToDouble(operand2) );

				else{
					stack_matrix[++top_matrix]= operand1.division(operand2);
				//cout<<"entered here "<<endl;
				}
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

if (  ( isOperator(infix[infix.length()-1]) && infix[infix.length()-1]!=')') || ( isOperator(infix[infix.length()-2]) && (infix[infix.length()-2]!= ')') && !isdigit(infix[infix.length()-1]) && !(infix[infix.length()-1] >=65 && infix[infix.length()-1] <=90)  )      ) {
flag1=1;
cout<<"Invalid operation"<<endl;
return ConvertToMatrix(0);
}

	char postfix[100];
	convert(buffer,postfix);

	return evaluatePost(postfix);
}

double evaluateD (string infix){
	char buffer [100];
	bool flagOp=0;
	strcpy(buffer,infix.c_str());
	for (int i=0;i<infix.length();i++){
        if (infix[i] != '.' && !isdigit(infix[i]) && infix[i] != ' '){
            flagOp=1;
            break;
        }

	}
if (flagOp==0)
    return atof(buffer);

	return ConvertToDouble(evaluateM(buffer));
}



void parseandprint( string input)
{
    bool error =0 ;
    static int counter =0 ;
    bool ola =0 ;
 bool newmatrix=1 ;
 matrix a ;
int parameter1 , parameter2 ;
 if ( input.find("[")!=-1)
 {

     a.Build_matrix(input);
    // cout<<a.getstring()<<endl;
 }
 else if ( input.find("rand")!=-1){
        for(int h=0; h<input.length();h++)
     {
         if(input[h]==' ')
            input.erase(h,1);
     }
        parameter1=atoi(input.substr(input.find("(")+1,input.find(",")-input.find("(")-1).c_str());
        parameter2=atoi(input.substr(input.find(",")+1,input.find(")")-input.find(",")-1).c_str());
       a.random(parameter1,parameter2);

 }
 else if ( input.find("eye")!=-1){
          for(int h=0; h<input.length();h++)
     {
         if(input[h]==' ')
            input.erase(h,1);
     }

         parameter1=atoi(input.substr(input.find("(")+1,input.find(",")-input.find("(")-1).c_str());
        parameter2=atoi(input.substr(input.find(",")+1,input.find(")")-input.find(",")-1).c_str());
       // cout<<parameter1<<"n"<<parameter2<<"n"<<endl;
        a.eye(parameter1,parameter2);

 }
 else if ( input.find("ones")!=-1){
          for(int h=0; h<input.length();h++)
     {
         if(input[h]==' ')
            input.erase(h,1);
     }

         parameter1=atoi(input.substr(input.find("(")+1,input.find(",")-input.find("(")-1).c_str());
        parameter2=atoi(input.substr(input.find(",")+1,input.find(")")-input.find(",")-1).c_str());
        a.ones(parameter1,parameter2);

 }
 else if ( input.find("zeros")!=-1){
          for(int h=0; h<input.length();h++)
     {
         if(input[h]==' ')
            input.erase(h,1);
     }

         parameter1=atoi(input.substr(input.find("(")+1,input.find(",")-input.find("(")-1).c_str());
        parameter2=atoi(input.substr(input.find(",")+1,input.find(")")-input.find(",")-1).c_str());
        a.zeros(parameter1,parameter2);

 }
 else if ( input.length () ==1 )
 {
     for ( int i =0 ; i <matrixName.size(); i++ )
{


    if ( matrixName[i]==input[0])
    {
        a=matrices[i];
	error=0;
	break;
    }
	else{
	
	 error =1 ;
		}
	
}

 }
 else
 {

     a = evaluateM(input);
     ola = 1 ;
 }
//cout<<endl<<input<<endl;
if ( ola==0 ){
for ( int i =0 ; i <matrixName.size(); i++ )
{
    if ( matrixName[i]==input[0])
    {

        matrices[i]=a;
         newmatrix=0 ;

    }
}
if(newmatrix){
matrixName.push_back(input[0]);
matrices.push_back(a);
}
}
//cout<<counter<<endl;
if(input[input.length()-1]!=';')
{
    if ( flag1 ==0 ){
	if ( error ==0){
    cout<<input[0]<<" = ";
    a.print() ;
}
 else {
cout<<"Error: matrix not defined"<<endl;
}

    }
else flag1=0;

}


counter ++ ;
}
void matrix::zeros(int r, int c)
{
	create_matrix( r, c);

	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		this->mat[i][j]=0;
	}
}
void matrix::ones(int r, int c)
{
	create_matrix( r, c);

	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		this->mat[i][j]=1;
	}
}

void matrix::eye(int r, int c)
{
    create_matrix(r,c);
	if( r!=c)
	{
	cout<<"Invalid Dimension";
	flag1=1;
	return ;
    }
	for(int i=0;i<r;i++)
	  for(int j=0;j<c;j++)
	  {
	     this->mat[i][j]=0;
	     if(i==j)
	     {
	     	this->mat[i][i]=1;
		 }
		 //cout<<mat[i][j];
}
}
void matrix::random(int r, int c)
{
	create_matrix( r, c);

	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		this->mat[i][j]=((double) rand() / (RAND_MAX ));
	}
}


