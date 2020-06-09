#include <iostream>
#include "include/cal.h"
#include <cmath>
#include <vector>
//#include <cal.h>
using namespace std;
#define MAX_ERROR 0.00001
// Object Constructor
// 객체 생성자
MyCal::MyCal()
{
    // initialize variables.
    // 내부적으로 사용할 각 멤버변수의 값을 초기화한다.
    //TO DO

    m_data1 = 0;
    m_data2 = 0;
    m_result = 0;
    temp = 0;
    order=0;
    d_data.resize(0,1);
    ch_poly.resize(0,1);
    ch_poly.resize(0,1);

}

double MyCal::f(double x)
{
    //make return value = a_n*x^n+a_n-1*x^n-1+....+a_1*x+a_0 .
    //(consider d_data[n] as a_n)
    double ans=0;
    for (int i = d_data.size()-1; i>=0;i--)
    { 
        ans += pow(x,i)*d_data[i];
    }

    //TODO
    return ans;
}
double MyCal::fdash(double x)
{
    //make return value = n*a_n*x^n-1+(n-1)*a_n-1*x^n-2+....+a_1 .
    //(consider d_data[n] as a_n)
    double ans=0;
    for (int i = d_data.size()-1;i>=1;i--)
    {
        ans += pow(x,i-1)*d_data[i]*i;
    }

    //TODO
    return ans;
}


// Functions to start
// 계산기 프로그램을 시작시키는 함수

void MyCal::Start()
{
    cout << "Calculator starts." << endl;
    cout << "quit to press 'q'." << endl;
    // cout << "계산기 프로그램을 시작합니다." << endl;
    // cout << "q을 입력하면 프로그램을 종료합니다." << endl;

    while(1) {
        // get operators first.
        // 두수를 연산할 연산자를 입력받는다.
        InputOpType();
        // if 'q', quit
        // 사용자가 q을 입력했다면 종료한다.
        if(m_op_type == 'q'){
          break;
        }
        //if 'n', do solve equation.
        if(m_op_type == 'n'){
          InputDataDer();
          ResultDer();
        }
        else if(m_op_type == 'k'){
          mat = InputMatrix();
          Decomposition();
        }
        else if (m_op_type == 'e'){
          Eigen();
          reverse();
          Eigenvector();
        }
        // if others such as + - * /, do the below statements.
        else
        {
          // get first number22
          // 첫번째 숫자값을 입력받는다.
          InputData1();
          // get second number
          // 두번째 숫자값을 입력받는다.
          InputData2();
          // print results of calculation.
          // 입력받은 두 값과 연산자를 이용하여 결과를 출력한다.
          Result();
        }

    }

    cout << "Quit." << endl;
    // cout << "계산기 프로그램을 종료합니다." << endl;
}

// function to get the first number
// 첫번째 숫자를 입력받을 함수
void MyCal::InputData1()
{

    do {
      cout << "first number : ";
      // cout << "첫번째 숫자 : ";
      cin >> m_data1;
      cond=cin.fail();
      cin.clear();
      cin.ignore(100,'\n');
    } while(cond);

}
// function to get the second number
// 두번째 숫자를 입력받을 함수
void MyCal::InputData2()
{
  do {
      cout << "second number : ";
      // cout << "두번째 숫자 : ";
      cin >> m_data2;
      cond=cin.fail();
      cin.clear();
      cin.ignore(100,'\n');
    } while(cond);
}
void MyCal::InputDeg()
{
  do {
      cout << "Degree of Polynomial? : ";
      // cout <<"다항식의 차수: ";
      cin >> order;
      cond=cin.fail();
      cin.clear();
      cin.ignore(100,'\n');
    } while(cond);
}

void MyCal::InputCoeff(int i)
{
  do {
      cout << "coefficient of x^"<<i<<": ";
      // cout << "x^"<<i<<" 계수: ";
      cin >> d_data[i];
      cond=cin.fail();
      cin.clear();
      cin.ignore(100,'\n');
    } while(cond);
}


// function to get the operation type
// 연산자를 입력받을 함수
void MyCal::InputOpType()
{
    while(1) {
        cout << "operation type ( +, -, *, /, n, k, e ) : ";
        // cout << "연산방법 ( +, -, *, /,n ) : ";

        // get operation type with 'cin'
        // 연산에 사용할 연산자를 입력받는다.
        cin >> m_op_type;

        // if the input was wrong, get again.
        // check m_op_type is one of  +, -, *, /,n .
        // 연산자를 제대로 입력하지 않았다면 다시 입력받는다.

        if(m_op_type == 'q' || m_op_type == '+' || m_op_type == '-' || m_op_type == '*' || m_op_type == '/' || m_op_type == 'n' || m_op_type == 'k' || m_op_type == 'e') {
            break;
        }
        else{
            cout << "Wrong operation type." << endl;
        }
        // else cout << "잘못 입력했습니다." << endl;
    }
}
void MyCal::InputDataDer()
{
  cout <<"solve the equation polynomial f(x)=0 with Newton-Rapson method" <<endl;
  // cout <<"다항식 f(x)=0 의 해를 Newton-Rapson법으로 구하는 과정입니다." <<endl;
  InputDeg();
  d_data.resize(order+1);
  for(int i=order;i>=0;i--)
  {
      InputCoeff(i);
  }
}

// function to show the result
// 결과를 출력하기 위한 함수
void MyCal::Result()
{
    // use chosen operator.
    // 사용자가 선택한 연산자에 따라서 계산을 수행한다.
    switch(m_op_type){
        case '+' :
            m_result = AddData();
            break;
        case '-' :
            m_result = SubData();
            break;
        case '*' :
            m_result = MulData();
            break;
        case '/' :
            m_result = DivData();
            break;
    }

    // print results.
    // 계산된 결과값을 출력한다.
    cout << " --> " << m_result << endl;
}
void MyCal::ResultDer(){
    double x,x_new,root,f_val,fdash_val,diff;
    cout<<"initial x: ";
    cin>>x;
    while(1)
    {
        f_val = f(x);
        fdash_val = fdash(x);
        x_new = x - (f_val/fdash_val);
        diff = x_new - x;

        cout<<"f(x) ="<<f_val<<endl;
        cout<<"f'(x) ="<<fdash_val<<endl;
        cout<<"New x: "<<x_new<<endl<<endl<<endl;

        if(f_val == 0.0)
        {
            root = x_new;
            break;
        }

        if(abs(diff)<2*MAX_ERROR)
        {
            root = (x_new + x)/2;
            break;
        }

        x = x_new;

    }
    cout <<"--> Root of f(x)=0  "<<root<<endl;
    // cout <<"--> f(x)=0의 해:  "<<root<<endl;
}

// 덧셈 연산을 수행할 함수
double MyCal::AddData()
{
    return m_data1 + m_data2;
}

// 뺄셈 연산을 수행할 함수
double MyCal::SubData()
{
    return m_data1 - m_data2;
}

// 곱셈 연산을 수행할 함수
double MyCal::MulData()
{
    return m_data1 * m_data2;
}

// 나눗셈 연산을 수행할 함수
double MyCal::DivData()
{
    return m_data1 / m_data2;
}


////////////////////////////LU Decomposition////////////////////////////////////
std::vector< std::vector<int> > MyCal::InputMatrix() {
    do {
      cout << "size of matrix : ";
      // cout << "x^"<<i<<" 계수: ";
      cin >> n_size;
      cond=cin.fail();
      cin.clear();
      cin.ignore(100,'\n');
    } while(cond);

    std::vector< std::vector<int> > mat( n_size , std::vector<int> (n_size));

    for (int i = 0; i < n_size; i++) {
        for (int j = 0; j < n_size; j++) {
            do {
              cout << "element of (" << i+1 << "," << j+1 << ") : ";
              // cout << "x^"<<i<<" 계수: ";
              cin >> element_value;
              cond=cin.fail();
              cin.clear();
              cin.ignore(100,'\n');
            } while(cond);
            mat[i][j] = element_value;
        }
    }

    for (int i = 0; i < n_size; i++) {
        for (int j = 0; j < n_size; j++) {
            cout << mat[i][j] << " ";
        }
        cout << endl;
    }

return mat;
}

void MyCal::Decomposition() {
    std::vector< std::vector<float> > L_Decomposition( n_size , std::vector<float> (n_size));
    std::vector< std::vector<float> > U_Decomposition( n_size , std::vector<float> (n_size));

    // Initializing L- and U- matrices with 0.

    for (int i = 0; i < n_size; i++) {
        for (int j = 0; j < n_size; j++) {
            L_Decomposition[i][j] = 0;
            U_Decomposition[i][j] = 0;
        }
    }

    // Making LU_Decomposition. In order to create each row of upper triangular matrix, 
    // corresponding row of lower triangular matrix must be created first. For example, to
    // construct 2nd row of the upper triangular matrix, (2,1) component of the lower 
    // triangular matrix should be known before hand. To carry out such procedure, I use if 
    // condition (i > j). To sum up, in if condition of (j >= i), upper triangular matrix is
    // created, and in if condition of (i > j), lower triangular matrix is created.

    for (int i = 0; i < n_size; i++) {
        L_Decomposition[i][i] = 1; // Assign 1 to diagonal of L-matrix
        for (int j = 0; j < n_size; j++) {
            // Making U-matrix.
            if (j >= i) {
                U_Decomposition[i][j] = mat[i][j];
                for (int k = 0; k < i; k++) {
                    U_Decomposition[i][j] = U_Decomposition[i][j] - U_Decomposition[k][j]*L_Decomposition[i][k];
                }
            }
            // Making L-matrix
            if (i > j) {
                L_Decomposition[i][j] = mat[i][j];
                for (int k = 0; k < j; k++) {
                    L_Decomposition[i][j] = L_Decomposition[i][j] - U_Decomposition[k][j]*L_Decomposition[i][k];
                L_Decomposition[i][j] = L_Decomposition[i][j] / U_Decomposition[j][j];
                }
            }
        }
    }


    // Printing L_Decomposition
    cout << "L Decomposition is as follows..." << endl;
    for (int i = 0; i < n_size; i++) {
        for (int j = 0; j < n_size; j++) {
            cout << L_Decomposition[i][j] << " ";
        }
        cout << endl;
    }

    // Printing U_Decomposition
    cout << "U Decomposition is as follows..." << endl;
    for (int i = 0; i < n_size; i++) {
        for (int j = 0; j < n_size; j++) {
            cout << U_Decomposition[i][j] << " ";
        }
        cout << endl;
    }
}

////////////////////////////Eigenvalues & Eigenvectors////////////////////////////////////
void MyCal::Eigen() {
    //Matrix Input
    do {
      cout << "size of matrix : ";
      // cout << "x^"<<i<<" 계수: ";
      cin >> n_size;
      cond=cin.fail();
      cin.clear();
      cin.ignore(100,'\n');
    } while(cond);

    double eigen_mat[10][10];

    for (int i = 0; i < n_size; i++) {
        for (int j = 0; j < n_size; j++) {
            do {
              cout << "element of (" << i+1 << "," << j+1 << ") : ";
              // cout << "x^"<<i<<" 계수: ";
              cin >> element_value;
              cond=cin.fail();
              cin.clear();
              cin.ignore(100,'\n');
            } while(cond);
            eigen_mat[i][j] = element_value;
        }
    }
    
    for (int i = 0; i < n_size; i++) {
        for (int j = 0; j < n_size; j++) {
            cout << eigen_mat[i][j] << " ";
        }
        cout << endl;
    }

    //Start constructing characteristic polynomial
    double ch_mat[10][10];
    double ch_det[10][10];

    ch_poly.resize(n_size+1);

    //Characteristic Polynomial
    double temp_coefficient;
    ch_poly[0] = 1;
    for (int k = 1; k < n_size+1; k++) {
        if (k > 1) {
            for (int i = 0; i < n_size; i++) {
                for (int j = 0; j < n_size; j++) {
                    if (i == j) {
                        ch_det[i][j] = ch_mat[i][j] + temp_coefficient;
                    }
                    else {
                        ch_det[i][j] = ch_mat[i][j];
                    }
                }
            }
            for (int x = 0; x < n_size; x++) {
                for (int y = 0; y < n_size; y++) {
                    int element = 0;
                    for (int z = 0; z < n_size; z++) {
                        element += eigen_mat[x][z]*ch_det[z][y];
                    ch_mat[x][y] = element;
                    }
                }
            }
        }

        else {
            for (int i = 0; i < n_size; i++) {
                for (int j = 0; j < n_size; j++) {
                    ch_mat[i][j] = eigen_mat[i][j];
                }
            }
        }

        double trace = 0;
        
        for (int i = 0; i < n_size; i++) {
            for (int j = 0; j < n_size; j++) {
                if (i == j) {
                    trace += ch_mat[i][j];
                }
            }
        }

        temp_coefficient = -trace/k;
        if (fabs(temp_coefficient) < 0.001) {
            ch_poly[k] = 0;
        }
        else {
            ch_poly[k] = temp_coefficient;
        }
    }

    cout << "Characteristic Polynomial : ";

    for (int i = 0; i < ch_poly.size(); i++) {
        cout << ch_poly[i] << " ";
    }
    
    cout << "\n";
}

void MyCal::reverse() {
    int a = 0;
    ch_poly_rev.resize(n_size+1);
    for (int i = ch_poly_rev.size()-1; i >= 0; i--) {
        ch_poly_rev[i] = ch_poly[a];
        a += 1;
    }
}

double MyCal::Eigen_f(double x)
{
    //make return value = a_n*x^n+a_n-1*x^n-1+....+a_1*x+a_0 .
    //(consider d_data[n] as a_n)
    double ans=0;
    for (int i = ch_poly_rev.size()-1; i>=0;i--)
    { 
        ans += pow(x,i)*ch_poly_rev[i];
    }

    //TODO
    return ans;
}
double MyCal::Eigen_fdash(double x)
{
    //make return value = n*a_n*x^n-1+(n-1)*a_n-1*x^n-2+....+a_1 .
    //(consider d_data[n] as a_n)
    double ans=0;
    for (int i = ch_poly_rev.size()-1;i>=1;i--)
    {
        ans += pow(x,i-1)*ch_poly_rev[i]*i;
    }

    //TODO
    return ans;
}

void MyCal::Eigenvector(){
    vector<double> roots;
    roots.resize(n_size);
    int index = 0;
    double x,x_new,root,f_val,fdash_val,diff;
    x = 10;
    while(1)
    {
        f_val = Eigen_f(x);
        fdash_val = Eigen_fdash(x);
        if (fdash_val == 0.0) {
            roots[index] = x;
            index++;
        }
        else {
        x_new = x - (f_val/fdash_val);
        diff = x_new - x;
        }
        
        if(f_val == 0.0)
        {
            root = x_new;
            break;
        }

        if(abs(diff)<2*MAX_ERROR)
        {
            root = (x_new + x)/2;
            break;
        }

        x = x_new;

    }
    
    cout <<"--> Eigenvalue of the matrix  "<< root << endl;

    // cout <<"--> f(x)=0의 해:  "<<root<<endl;
}


