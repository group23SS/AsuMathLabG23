#include "iostream"
#include <vector>
#include <cstdlib>
#include <string>
#include <fstream>
#include "matrix.h"

using namespace std;
int main(int argc, char * argv[])
{
	//char **command;
	ifstream infile ;
	istream * in = &cin;

    int xx=2;
	if (argc>1){

 infile.open(argv[1]);
    in = &infile ;
	}
	//string s;
	//getline(cin,s);
	//*in.open(s);
	int number = 0 ;
	string s ;
    string input[2];
	bool flag3 = 0 ;
	while ( getline ( *in , s ) ){
            if ( flag3 ==0 ){
            input[number] = s;
            flag3 =1 ;
            }
            else input[number]= input[number]+s ;
            	//int find1=0;1
//find1=input[number].find('\r');
if ( input[number].find('\n')!=-1)
	input[number].erase(input[number].length()-1);
	if (input[number].find('\r') != -1) {

	input[number].erase(input[number].length()-1);

	}

	if ( input[number].find(']')!= -1){
	number ++ ;
	flag3 = 0 ;
	}
	if ( number ==2 )
        break;
	}



    vector<string> matrixName(2);
    vector<matrix> matrices(2);
        matrix a;
    matrix b ;
    matrix c;

    //getline (cin , input);
    //getline (cin , input2);
	//while (getline(*in,input[i]))
	if ( input[0][input[0].length()-1] == ';' )
	{input[0][input[0].length()-1]=' ';

	}
	if ( input[1][input[1].length()-1] == ';' )
	{input[1][input[1].length()-1]=' ';

	}



	for ( long long i = input[0].length () - 1 ; i >input[0].length()-5 ; i --) {
	if ( input[0][i] == ']' && input[0][i-1] ==';' )
	{
		input[0].replace(i-1,1,"]");

	}
	}
	for (long long i = input[1].length () - 1 ; i >input[1].length()-5 ; i --) {
	if ( input[1][i] == ']' && input[1][i-1] ==';' )
	{
		input[1].replace(i-1,1,"]");

	}
	}
    a.dimension(input[0]);
    b.dimension(input[1]);



    a.create_matrix(a.getrow() , a.getcolumn() );
    b.create_matrix(b.getrow() , b.getcolumn() ) ;
    matrixName[0]=input[0].substr(0,1);
    matrixName[1]=input[1].substr(0,1);

    a.breakit(input[0]);
    b.breakit(input[1]);
      matrices[0].create_matrix(a.getrow() , a.getcolumn());
    matrices[1].create_matrix(b.getrow() , b.getcolumn());
    matrices[0]=a;
    matrices[1]=b;

    int op,op1,op2;
    int result=0;
    bool check=0;


    string operation;
    while (1){
    getline(*in,operation);
  // matrices[0].print();
    int find2=0;
    find2=operation.find('\r');
    if (find2+1)
	operation.erase(find2,1);
				if (infile.eof())
		break;
    if (operation.length()>=5){
        for (int i=0;i<matrixName.size();i++){
            if (matrixName[i]==operation.substr(4,1)){
                op1=i;
                result++;
            }
            if (operation.length()>6)
             if (matrixName[i]==operation.substr(8,1)){
                op2=i;
                result++;
            }
             if (matrixName[i]==operation.substr(0,1)){
                 check=1;
                 op=i;
             }
             if (operation.length()>6)
            if (matrixName[i]==operation.substr(9,1)){
            op2=i;
            result=2;
            }


        }
    if (operation.substr(6,1) == "+")
            c= matrices[op1] + matrices[op2];
    else if (operation.substr(6,1) == "-")
            c= matrices[op1] - matrices[op2];
    else if (operation.substr(6,1) == "*")
        c= matrices[op1].multiplication( matrices[op2]);
    else if (operation.substr(6,1) == "/")
            c= matrices[op1].division(matrices[op2]);
    else if (operation.substr(6,2) == "./"){
          //  matrices[op2].print();
        c=matrices[op2].Rdivision();
    result =2;
    }
    else if (operation.substr(5,1)=="'"){
        c=matrices[op1].transpose();
        result=2;
    }
    else
        cout<<"Invalid operation"<<endl;
        if (result != 2)
            cout<<"matrix undefined"<<endl;

        else if (result == 2) {
            if (check==0){
        matrixName.push_back(operation.substr(0,1));
        matrices.push_back(c);
            }
            else
                matrices[op]=c;


		if ( flag1 == 0 ) {
			cout<<operation.substr(0,1)<<" = ";
			c.print();
		}
        }
        result=0;
        check=0;

    }
    else
continue;
    }

    for (int i=0;i<matrices.size();i++)
        matrices[i].destroy();
	system("pause");
  return 0;
}


