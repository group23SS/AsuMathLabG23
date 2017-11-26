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






	double matrix :: getDeterminant(){
		matrix c;
		c.create_matrix(nrow,ncolumn);
		for (int i=0;i<nrow;i++)
			for (int j=0;j<ncolumn;j++)
				c.mat[i][j]=mat[i][j];
				//cout<<endl<<nrow<<endl<<ncolumn<<endl;

	if(nrow!=ncolumn)
        cout<<"Invalid matrix dimension ";
        else
        {
	if(nrow==1&&ncolumn==1)
		return mat[0][0];
	double value = 0, m = 1;
	for(int i=0;i<nrow;i++){
		for(int j=0;j<ncolumn;j++){
			value=0;

		{if(j<i){
		    if ( c.mat[j][j]==0)
                return 0 ;


         value=c.mat[i][j]/c.mat[j][j];
		 for(int k=0;k<ncolumn;k++){

			 c.mat[i][k]=c.mat[i][k]-(value*c.mat[j][k]);}
		 }
		}
		}
	m=m*c.mat[i][i];
	}
	return m;


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



