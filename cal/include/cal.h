#ifndef CAL_H
#define CAL_H
#include <vector>
class MyCal
{
private:
    // 2 variables which will be used for calculation
    // 계산에 사용할 두 값을 입력받을 두 변수
    double m_data1, m_data2;

    // variable which will save the results of calculation
    // 계산된 결과값을 저장할 변수
    double m_result;
    bool cond;

    // variable which will save the operation type
    // 계산에 사용할 연산자를 저장할 변수 ( +, -, *, / )
    char m_op_type;
    char temp;
    int order;
    std::vector<double> d_data;

    // size of the matrix
    int n_size;

    // matrix container for InputMatrix()
    std::vector< std::vector<int> > mat;

    // element value of the matrix
    int element_value;

    // function to get the first number
    // 첫번째 숫자를 입력받을 함수
    void InputData1();

    // function to get the second number
    // 두번째 숫자를 입력받을 함수
    void InputData2();

    // function to get the operation type
    // 연산자를 입력받을 함수
    void InputOpType();

    // function to get the coefficient for solving eq with Newton-Rapson method
    // 계수 입력받게 해주는 함수
    void InputDataDer();
    void ResultDer();
    void InputDeg();
    void InputCoeff(int);

    // function for add
    // 덧셈 연산을 수행할 함수
    double AddData();

    // function for subtract
    // 뺄셈 연산을 수행할 함수
    double SubData();

    // function for multiply
    // 곱셈 연산을 수행할 함수
    double MulData();

    // function for division
    // 나눗셈 연산을 수행할 함수
    double DivData();

    double f(double x);
    double fdash(double x);

    // initialize matrix with the user input
    std::vector< std::vector<int> > InputMatrix();

    // LU Decomposition
    void Decomposition();

    // Eigenvalues and corresponding eigenvectors
    std::vector<double> ch_poly;
    std::vector<double> ch_poly_rev;
    double Eigen_f(double x);
    double Eigen_fdash(double x);
    void Eigen();
    void reverse();
    void Eigenvector();

    // function to show the result
    // 결과를 출력하기 위한 함수
    void Result();

public:

    // Object Constructor
    // 객체 생성자
    MyCal();

    // function to start calculator
    // 계산기 프로그램을 시작시키는 함수
    void Start();

};
#endif
