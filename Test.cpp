/**
 *
 * IMPORTANT: Please write more tests - the tests here are only for example and are not complete.
 *
 * AUTHORS: Dan "Sylbris" Davydov
 *
 * Date: 2021-04
 */

#include "doctest.h"
#include "Matrix.hpp"
#include <iostream>
#include <algorithm>
#include <cstdlib>
using namespace zich;
#include <vector>
#include <sstream>

/////////////////////////////////////DEFINITIONS & Functions
const int SUBCASE_TEST_NUM = 10;
Matrix create_matrix(int rows, int cols); 
vector<double> create_random_vector(int size);
vector<int> create_size_and_divisors();
int random(int from, int to);
////////////////////////////////////

/*
    mostly testing the constructor.
*/
TEST_CASE("Creating new matrix")
{
    //Create matrix a.
    std::vector<double> identity = {1, 0, 0, 0, 1, 0, 0, 0, 1};
    Matrix a{identity, 3, 3};  // constructor taking a vector and a matrix size

    //bad parameters.
    CHECK_THROWS(Matrix b(identity, -1, 3));
    CHECK_THROWS(Matrix b(identity, 3, -1));
    CHECK_THROWS(Matrix b(identity, -1, -1));
    CHECK_THROWS(Matrix b(identity, 0, 0));

    /* 
    Create a matrix size 8, and create all possible
    Matrices from it. this is done by going over all of 8 devisors and trying it out.
    */
    std::vector<double> identity_s = {1, 0, 0, 0, 1, 0, 0, 0};
    CHECK_NOTHROW(Matrix b(identity_s, 2, 4));
    CHECK_NOTHROW(Matrix b(identity_s, 4, 2));
    CHECK_NOTHROW(Matrix b(identity_s, 8, 1));
    CHECK_NOTHROW(Matrix b(identity_s, 1, 8));

}

TEST_CASE("Testing bool operators")
{
    std::vector<double> a = {1, 0, 0, 0, 1, 0, 0, 0};
    std::vector<double> b = {1, 0, 0, 0, 1, 0, 0, 1};

    Matrix mat_a{a, 4, 2};
    Matrix mat_b{b, 4, 2};

    CHECK(mat_a < mat_b); //a<b
    CHECK(mat_a <= mat_b); //a<=b
    CHECK(mat_a != mat_b); //a!=b
    CHECK(mat_b >= mat_a); //b>=a
    CHECK(mat_b > mat_a); //b>a
    CHECK(mat_a == mat_a); //a==a

    //Creating matrices C,D : 1x8 , 2x4, 8x1 and checking you can't use bool operators with A : 4x2.
    const int vector_size = 8;
    std::vector<int> divisors = {1, 2, 4, 8};

    for(size_t i=0; i < divisors.size() ;i++){
        int val = divisors.at(i);
        Matrix mat_c{b, val, vector_size/val};
        Matrix mat_d{b, vector_size/val, val};
        bool a;

        /*
        Comparing different size matrices.
        */
        if(!check_order(mat_a, mat_c)){

            CHECK_THROWS(a = (mat_c > mat_a));
            CHECK_THROWS(a = (mat_a > mat_c));
            CHECK_THROWS(a = (mat_d > mat_a));

            CHECK_THROWS(a = (mat_c < mat_a));
            CHECK_THROWS(a = (mat_a < mat_c));
            CHECK_THROWS(a = (mat_d < mat_a));

            CHECK_THROWS(a = (mat_c == mat_a));
            CHECK_THROWS(a = (mat_a == mat_c));
            CHECK_THROWS(a = (mat_d == mat_a));

            CHECK_THROWS(a = (mat_c >= mat_a));
            CHECK_THROWS(a = (mat_a >= mat_c));
            CHECK_THROWS(a = (mat_d >= mat_a));

            CHECK_THROWS(a = (mat_c <= mat_a));
            CHECK_THROWS(a = (mat_a <= mat_c));
            CHECK_THROWS(a = (mat_d <= mat_a));
            
            CHECK_THROWS(a = (mat_c != mat_a));
            CHECK_THROWS(a = (mat_a != mat_c));
            CHECK_THROWS(a = (mat_d != mat_a));
        }
    }

}

TEST_CASE("Testing * , 5*a or a*5, or a*b")
{
    std::vector<double> a = {1, 2, 3, 4, 5, 6};
    std::vector<double> b = {7, 8, 9, 10, 11, 12};

    std::vector<double> c = {5, 10, 15, 20, 25, 30}; //5*a or a*5
    std::vector<double> d = {58, 64, 139, 154}; //a*b

    Matrix mat_a{a, 2, 3};
    Matrix mat_b{b, 3, 2};
    Matrix mat_c{c, 3, 2};
    Matrix mat_d{d, 2, 2};

    CHECK(5*mat_a == mat_c);
    CHECK(mat_a*5 == mat_c);
    CHECK(mat_a*mat_b == mat_d);

    //Check multiplication of different sizes matrixes.
    for(int i=1; i<5;i++){
        Matrix mat_a1 = create_matrix(3,i);
        Matrix mat_a2 = create_matrix(i,2);
        CHECK_NOTHROW(mat_a1*mat_a2); // 3xi * ix2
        CHECK_THROWS(mat_a2*mat_a1); // ix3 * 2*i
        Matrix mat_a3 = create_matrix(3, 2);

        //Check the new matrix is the correct order.
        CHECK(check_order(mat_a3, mat_a1*mat_a2));
    }
}

TEST_CASE("input, output")
{   
    std::vector<double> a = {1, 2, 3, 4, 5, 6};
    std::vector<double> b = {7, 8, 9, 10, 11, 12};
    Matrix mat_a{a, 3, 2};

    istringstream input{"1 2 3"};

    //test input.
    CHECK_NOTHROW(input >> mat_a);
    CHECK(mat_a == (Matrix{b, 3, 2}));

    ostringstream output;
    ostringstream mat_a_print;

    CHECK_NOTHROW(output << mat_a);
    mat_a_print << "" ;
    CHECK(mat_a_print.str() == output.str());
}

TEST_CASE("x= operators , += , -=, *=")
{
    SUBCASE("+="){
        
        for(int i=0; i< SUBCASE_TEST_NUM; i++){
            /*Create a vector containing (vector_size, divisor, other divisor)
            This will be used to create the random vector and matrix sizes */

            std::vector<int> size_and_divisors = create_size_and_divisors();
            int vector_size = size_and_divisors[0];
            int rows = size_and_divisors[1];
            int colums = size_and_divisors[2];

            //create random vector a, and the same vector multiplied by -1.
            std::vector<double> a = create_random_vector(vector_size);
            std::vector<double> b = create_random_vector(vector_size);
            std::vector<double> sum_ab(a.size());

            std::transform (a.begin(), a.end(), b.begin(), sum_ab.begin(), std::plus<int>());

            Matrix mat_a{a, rows, colums};
            Matrix mat_b{b, rows, colums};
            //Should work.
            CHECK(Matrix{sum_ab, rows, colums} == (mat_a += mat_b));
            //Can't use operand on different size vectors.
            CHECK_THROWS((Matrix{a, rows, colums} += Matrix{a, colums, rows}));
        }
    }
    SUBCASE("-="){
        for(int i=0; i< SUBCASE_TEST_NUM; i++){
            /*Create a vector containing (vector_size, divisor, other divisor)
            This will be used to create the random vector and matrix sizes */

            std::vector<int> size_and_divisors = create_size_and_divisors();
            int vector_size = size_and_divisors[0];
            int rows = size_and_divisors[1];
            int colums = size_and_divisors[2];

            //create random vector a, and the same vector multiplied by -1.
            std::vector<double> a = create_random_vector(vector_size);
            std::vector<double> b = create_random_vector(vector_size);
            std::vector<double> sub_ab(a.size());

            std::transform (a.begin(), a.end(), b.begin(), sub_ab.begin(), std::minus<int>());

            Matrix mat_a{a, rows, colums};
            Matrix mat_b{b, rows, colums};

            //Should work.
            CHECK(Matrix{sub_ab, rows, colums} == (mat_a -= mat_b));
            //Can't use operand on different size vectors.
            CHECK_THROWS((Matrix{a, rows, colums} -= Matrix{a, colums, rows}));
        }
    }
    /*
    SUBCASE("*="){
        
        for(int i=0; i< SUBCASE_TEST_NUM; i++){
            //random double between -100 and 100.
            const double scalar = (0 + rand() % (200 - 0 + 1)) -100;
            Create a vector containing (vector_size, divisor, other divisor)
            This will be used to create the random vector and matrix sizes 

            std::vector<int> size_and_divisors = create_size_and_divisors();
            int vector_size = size_and_divisors[0];
            int rows = size_and_divisors[1];
            int colums = size_and_divisors[2];

            
            //create random vector a, and the same vector multiplied by -1.
            std::vector<double> a = create_random_vector(vector_size);
            std::vector<double> b = create_random_vector(vector_size);

            //should work
            CHECK_NOTHROW((Matrix{a, rows, colums} *= Matrix{b, colums, rows}));
            //bad size matrices.
            CHECK_THROWS((Matrix{a, rows, colums} *= Matrix{b, rows, colums}));
            
        }
    */    
    
}

TEST_CASE("pre inc, post inc (++,--) ")
{   
    //prefix ++
    std::vector<double> a = {1, 2, 3, 4, 5, 6};
    std::vector<double> c = {2, 3, 4, 5, 6, 7};

    Matrix mat_a{a, 2, 3};
    Matrix mat_c{c, 2, 3};
    Matrix mat_b = mat_a++;

    CHECK(mat_a != mat_b);
    CHECK(mat_a == mat_c);

    //postfix ++
    mat_a = Matrix{a, 2, 3};
    mat_b = ++mat_a;
    CHECK(mat_a == mat_b);
    CHECK(mat_a == mat_c);

    //prefix --
    mat_a = Matrix{a, 2, 3};
    mat_b = mat_c--;
    CHECK(mat_a != mat_b);
    CHECK(mat_a == mat_c);

    //postfix --
    mat_a = Matrix{a, 2, 3};
    mat_b = --mat_c;
    CHECK(mat_a == mat_b);
    CHECK(mat_a == mat_c);

}

TEST_CASE("+ -")
{
    SUBCASE("Unary +/-"){
        const double scale = -1;
        for(int i=0; i< SUBCASE_TEST_NUM; i++){
            /*Create a vector containing (vector_size, divisor, other divisor)
                This will be used to create the random vector and matrix sizes */

            std::vector<int> size_and_divisors = create_size_and_divisors();
            int vector_size = size_and_divisors[0];
            int rows = size_and_divisors[1];
            int colums = size_and_divisors[2];

            //create random vector a, and the same vector multiplied by -1.
            std::vector<double> a = create_random_vector(vector_size);
            std::vector<double> neg_a(a.size());
            std::transform(a.begin(), a.end(), neg_a.begin(),
                   [&scale](double element) { return element *= scale; });

            Matrix mat_a{a, rows, colums};
            Matrix mat_a_neg{neg_a, rows, colums};

            CHECK(Matrix{a, rows, colums} == +mat_a);
            CHECK(mat_a_neg == -mat_a);
            CHECK(-mat_a_neg == mat_a);
            CHECK(+mat_a_neg == +mat_a_neg);
        }
    }
    SUBCASE("Regular +/-"){
        for(int i=0; i < SUBCASE_TEST_NUM; i++){
            /*Create a vector containing (vector_size, divisor, other divisor)
            This will be used to create the random vector and matrix sizes */

            std::vector<int> size_and_divisors = create_size_and_divisors();
            int vector_size = size_and_divisors[0];
            int rows = size_and_divisors[1];
            int colums = size_and_divisors[2];

            //Create 2 vectors to test.
            std::vector<double> a = create_random_vector(vector_size);
            std::vector<double> b = create_random_vector(vector_size);
            std::vector<double> sum_ab(a.size());
            std::vector<double> sub_ab(a.size());

            //add 2 vectors.
            std::transform (a.begin(), a.end(), b.begin(), sum_ab.begin(), std::plus<int>());
            std::transform (a.begin(), a.end(), b.begin(), sub_ab.begin(), std::minus<int>());

            //check +/-
            CHECK(Matrix{sum_ab, rows, colums} == (Matrix{a, rows, colums} + Matrix{b, rows, colums}));
            CHECK(Matrix{sub_ab, rows, colums} == (Matrix{a, rows, colums} - Matrix{b, rows, colums}));
            
            //Testing vs +/- with different size matrices.
            CHECK_THROWS((Matrix{a, rows, colums} + Matrix{b, colums, rows}));
            CHECK_THROWS((Matrix{a, rows, colums} - Matrix{b, colums, rows}));

        }
    }
}
/**
 * @brief Create a matrix object
 * 
 * @param rows 
 * @param cols 
 * @return Matrix 
 */
Matrix create_matrix(int rows, int cols){

    std::vector<double> a;  

    for (int i =0; i < rows*cols ; i++){
        int b = rand() % 10 + 1;
        a.push_back(b);
    }

    Matrix mat{a, rows, cols};
    return mat;
}
/**
 * @brief Create a random vector object with numbers from 1 to 10.
 * 
 * @param size 
 * @return Vector<double> 
 */
vector<double> create_random_vector(int size){

    std::vector<double> a;  

    for (int i =0; i < size ; i++){
        int b = rand() % 10 + 1;
        a.push_back(b);
    }

    return a;
}
/**
 * @brief Create a size and get 2 random divisors.
 * 
 * @param size 
 * @return vector<int> 
 */
vector<int> create_size_and_divisors(){

    std::vector<int> divisors;  
    int random_size = random(2,100);
    random_size*=2; //ensuring random size is not prime.
    for (int i =2; i <= random_size/2 ; i++){
        //found a divisor of random_size, add it.
        if(random_size%i == 0){
            divisors.push_back(i);
        }
        
    }
    //Get a random index from the vector.
    int get_random_divisor_post = random(0,divisors.size()-1);
    //Get the divisor of the random index.
    int get_random_divisor = divisors.at((size_t)get_random_divisor_post);
    //Create the result.
    std::vector<int> result = {random_size, get_random_divisor, random_size/get_random_divisor}; 
    return result;
}
/**
 * @brief Create a random number between a range.
 * 
 * @param from 
 * @param to 
 * @return int 
 */
int random(int from, int to)
{
    return from + rand() % (to - from + 1);
}


