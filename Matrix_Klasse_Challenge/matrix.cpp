#include "matrix.h"

#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

namespace Perc
{

Matrix::Matrix(std::initializer_list<std::initializer_list<real>> list) {
    mRows = list.size();
    unsigned int cols = list.begin()->size();
    for (const auto& row : list)
    {
        if(cols != row.size())
        {
            cerr << "Error. The Matrix number if rows are not equal!" << endl;
        }
        mData.insert(mData.end(), row.begin(), row.end());
    }
    mCols = cols;
}

Matrix Matrix::setZeros(const uint rows,
                     const uint cols)
{
    mData.assign(rows*cols, 0.0);
    mRows = rows;
    mCols = cols;

    return *this;
}

void Matrix::assign(const real val)
{
    for(auto &comp : *this)
    {
        comp = val;
    }
}

Matrix Matrix::zeros(const uint rows,
                     const uint cols)
{
    Matrix m;
    return m.setZeros(rows, cols);
}


real Matrix::sum(const Matrix &input)
{
    real sum = 0.0;
    auto mat = input;
    for(auto &comp : mat)
    {
        sum += comp;
    }
    return sum;
}

uint Matrix::getDim(const uint order) const
{
    assert(order < 2);

    if(order == 0)
        return mRows;
    else
        return mCols;
}

MatrixDim Matrix::getDim() const
{
    return MatrixDim{mRows, mCols};
}

auto Matrix::setDim(const uint rows,
                    const uint cols) -> void
{
    mRows = rows;
    mCols = cols;

    mData.resize(rows*cols);
}

auto Matrix::set(const uint j,
                 const uint i,
                 const double val) -> void
{
    mData[j*mCols+i] = val;
}

real Matrix::get(const uint j,
                 const uint i) const
{
    return mData[j*mCols+i];
}



auto Matrix::transposed() const -> Matrix
{
    Matrix m;

    const auto [rows,cols] = this->getDim();

    m.setDim(cols, rows);

    for(uint j=0 ; j<rows ; j++)
    {
        for(uint i=0 ; i<cols ; i++)
        {
            const auto val = this->get(j,i);
            m.set(i, j, val);
        }
    }

    return m;
}

auto Matrix::matmul(const Matrix &other) const -> Matrix
{
    Matrix res;

    res.setDim(this->getDim(0),other.getDim(1));

    if( this->getDim(1) != other.getDim(0) )
    {
        cerr << "Cannot multiply those Matrices. Wrong Dimensions." << endl;
        return res;
    }

    const auto res_rows = this->getDim(0);
    const auto res_cols = other.getDim(1);

    const auto lines = other.getDim(0);
    for(uint j=0 ; j<res_rows ; j++)
    {
        for(uint i=0 ; i<res_cols ; i++)
        {
            auto sum = 0.0;
            for(uint k=0 ; k<lines ; k++)
            {
                const auto l = this->get(j, k);
                const auto r = other.get(k, i);
                sum += l*r;
            }

            res.set(j,i, sum);
        }
    }

    return res;
}

auto Matrix::operator-(const Matrix &other) const -> Matrix
{
    if(!dim_cmp(other))
        return *this;

    Matrix result = *this;

    for(int j=0 ; j<mRows ; j++)
    {
        for(int i=0 ; i<mCols ; i++)
        {
            auto cur = result.get(j, i) - other.get(j, i);
            result.set(j, i, cur);
        }
    }

    return result;
}

auto Matrix::operator-=(const Matrix &other) -> Matrix
{
    Matrix res = *this;
    *this = res-other;
    return *this;
}

auto Matrix::operator+(const Matrix &other) const -> Matrix
{
    if(!dim_cmp(other))
        return *this;

    Matrix result = *this;

    for(int i=0 ; i<mRows ; i++)
    {
        for(int j=0 ; j<mCols ; j++)
        {
            auto cur = result.get(i, j) + other.get(i, j);
            result.set(i, j, cur);
        }
    }

    return result;
}

auto Matrix::operator*(const real val) const -> Matrix
{
    Matrix res(*this);

    for(auto &comp : res)
    {
        comp = comp*val;
    }

    return res;
}

auto Matrix::operator*(const Matrix &other) const -> Matrix
{
    if(!dim_cmp(other))
        return *this;

    auto &l = const_cast<Matrix&>(*this);
    auto &r = const_cast<Matrix&>(other);

    auto it_left = l.begin();
    auto it_right = r.begin();

    Matrix res;
    res.setDim(this->getDim(0), this->getDim(1));

    for(auto &res_val : res)
    {
        res_val = (*it_left) * (*it_right);
        it_left++; it_right++;
    }

    return res;
}

Matrix Matrix::operator/(const real val) const
{
    Matrix res(*this);

    for(auto &comp : res)
    {
        comp = comp/val;
    }

    return res;
}

Matrix Matrix::operator==(const Matrix &other) const
{
    if(!dim_cmp(other))
        return *this;

    Matrix result = *this;

    for(int i=0 ; i<mRows ; i++)
    {
        for(int j=0 ; j<mCols ; j++)
        {
            const bool is_equal = result.get(i, j) == other.get(i, j);
            result.set(i, j, is_equal ? 1.0 : 0.0);
        }
    }

    return result;
}

bool Matrix::dim_cmp(const Matrix &other) const
{
    if(this->getDim(0) != other.getDim(0))
    {
        cerr << "Rows do not match." << endl;
        return false;
    }

    if(this->getDim(1) != other.getDim(1))
    {
        cerr << "Columns do not match." << endl;
        return false;
    }

    return true;
}

Matrix Matrix::round(const Matrix &input)
{
    auto res = input;
    for(auto &comp : res)
    {
        comp = ::round(comp);
    }
    return res;
}

real Matrix::average(const Matrix &input)
{
    real sum = 0.0;
    real numbers = 0.0;
    auto mat = input;
    for(auto &comp : mat)
    {
        sum += comp;
        numbers += 1.0;
    }
    return sum/numbers;
}

Matrix Matrix::log(const Matrix &input)
{
    auto res = input;
    for(auto &comp : res)
    {
        comp = ::log(comp);
    }
    return res;
}

auto Matrix::print() -> void
{
    for(uint i=0 ; i<mRows ; i++)
    {
        cout << "[ ";
        for(uint j=0 ; j<mCols ; j++)
        {
            cout << mData[i*mCols+j];

            // last entry ?
            if(j<mCols-1) cout << ", ";
            else cout << " ]";
        }
        cout << endl;
    }

}

///// Tests
bool Matrix::runTests()
{
    cout << "Multiplication Test1:" << endl;
    bool ok = testMultiply1();

    cout << "Multiplication Test2:" << endl;
    ok &= testMultiply2();

    cout << "Addition Test:" << endl;
    ok &= testAddition();

    return ok;
}

bool Matrix::testMultiply1()
{
    Matrix X, Y, Z_expc;

    X.setDim(3, 4);
    Y.setDim(4, 2);
    Z_expc.setDim(3, 2);

    auto createTestMat = [](Matrix &m)
    {
        const auto nums = m.getDim(0)*m.getDim(1);
        for(uint n=0 ; n<nums ; n++)
        {
            const auto r = m.getDim(0);
            const auto c = m.getDim(1);
            m.set(n/c, n%c, n);
        }
    };

    createTestMat(X);
    createTestMat(Y);

    Z_expc = {{28, 34}, {76, 98}, {124, 162}};

    // Erwartung berechnen
    auto Z = X.matmul(Y);

    Matrix boolMat = (Z == Z_expc);

    const auto numCorrect = Matrix::sum(boolMat);
    if(numCorrect == boolMat.getDim(0)*boolMat.getDim(1))
    {
        cout << "Multiplication Test passed!" << endl;
        return true;
    }
    else
    {
        cout << "Multiplication Test failed!" << endl;
        return false;
    }
}

bool Matrix::testMultiply2()
{
    Matrix A = { {1,0,0}, {0,1,0}, {0,0,1} };
    Matrix B = { {1,2,3}, {4,5,6}, {7,8,9} };
    Matrix C_expc = { {1,2,3}, {4,5,6}, {7,8,9} };

    // TODO: Schreiben einen Test, der überprüft, ob
    // Die Matrizen-Multiplikation stimmt.
}

bool Matrix::testAddition()
{
    // TODO: Schreiben einen Test, der überprüft, ob
    // Die Matrizen-Addition stimmt.
}

}
