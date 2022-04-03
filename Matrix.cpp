#include <string>
#include <iostream>
#include <vector>
#include "Matrix.hpp"
using namespace std;

namespace zich
{
    /**
     * @brief Construct a new Matrix:: Matrix object
     * 
     * @param input_v 
     * @param rows 
     * @param cols 
     */
    Matrix::Matrix(const std::vector<double>& input_v, int rows, int cols){};
    /**
     * @brief Check if two matrices are of the same order.
     * 
     * @param m1 
     * @param m2 
     * @return true 
     * @return false 
     */
    bool check_order(const Matrix& m1, const Matrix& m2){
        return (m1._rows==m2._rows && m1._cols==m2._cols);
    }

    //+
    Matrix Matrix::operator +(const Matrix& other){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return b;
        };
    Matrix Matrix::operator +(){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return b;
        };
    //-
    Matrix Matrix::operator -(const Matrix& other){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return b;
        };
    Matrix Matrix::operator -(){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return b;
    };
    //++
    Matrix& Matrix::operator ++(){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return *this;
    }; //pre increment ++x
    Matrix Matrix::operator ++(int){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return b;
    }; //post increment x++
    //--
    Matrix& Matrix::operator --(){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return *this;
    }; //pre increment --x
    Matrix Matrix::operator --(int){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return b;
    }; //post increment x--
    //x=
    Matrix& Matrix::operator +=(const Matrix& other){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return *this;
    };
    Matrix& Matrix::operator -=(const Matrix& other){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return *this;
    };
    Matrix& Matrix::operator *=(const double scalar){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return *this;
    };
    //*
    /* Here we use friend because of the symmetry of the * operator,
    a*b is the same is b*a.
    */
    Matrix operator *(const double scalar, const Matrix& other){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return b;
    };
    Matrix operator *(const Matrix& other, const double scalar){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return b;
    };

    Matrix operator *(const Matrix& m1, const Matrix& m2){
        std::vector<double> arr = {3, 0, 0, 0, 3, 0, 0, 0, 3};
        Matrix b{arr,0,0};
        return b;
    }
            
    // bool operators will be defined as friends 
    bool operator>(const Matrix& m1, const Matrix& m2){return true;};
    bool operator<(const Matrix& m1, const Matrix& m2){return true;};
    bool operator==(const Matrix& m1, const Matrix& m2){return true;};
    bool operator>=(const Matrix& m1, const Matrix& m2){return true;};
    bool operator<=(const Matrix& m1, const Matrix& m2){return true;};
    bool operator!=(const Matrix& m1, const Matrix& m2){return true;};

    // input, output
    std::istream& operator>>(istream& in, Matrix& matrix){
        return in;
    };
    std::ostream& operator<<(ostream& out, const Matrix& matrix){
        out << "hello" ;
        return out;
    };
};       


