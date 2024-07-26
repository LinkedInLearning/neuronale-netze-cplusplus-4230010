#include "matrix.h"
#include <cassert>
#include <cmath>
#include <iostream>

using namespace std;

namespace Perc
{

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

real Matrix::sum() const
{
    return Matrix::sum(*this);
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

Matrix Matrix::appendRS(const Matrix &other)
{
    Matrix res;

    if(this->getDim(0) != other.getDim(0))
    {
        cerr << "Matrices number of rows do not match." << endl;
        return res;
    }

    const auto res_rows = this->getDim(0);
    const auto res_cols = this->getDim(1) + other.getDim(1);
    res.setDim(res_rows, res_cols);

    for(uint j=0 ; j<res_rows ; j++)
    {
        for(uint i=0 ; i<res_cols ; i++)
        {
            real val = 0.0;
            if(i < this->getDim(1))
            {
                val = this->get(j, i);
            }
            else
            {
                val = other.get(j, i-this->getDim(1));
            }
            res.set(j, i, val);
        }
    }
    *this = res;
    return *this;
}

auto Matrix::matmul(const Matrix &other) const -> Matrix
{
    Matrix res;

    const auto this_rows = this->getDim(0);
    const auto this_cols = this->getDim(1);
    const auto other_rows = other.getDim(0);
    const auto other_cols = other.getDim(1);

    if( this_cols != other_rows )
    {
        cerr << "Diese Matrizen können nicht miteinander multipliziert werden. Falsche Dimensionen." << endl;
        return res;
    }

    res.setDim(this_rows, other_cols);

    const auto res_rows = this_rows;
    const auto res_cols = other_cols;

    // Folgender Code nutzt Zeiger und durchdachte Schleifen
    // um die Multiplication so schnell wie möglich abzuwicklen
    auto *p_res_start = (res.mData.data());

    for(uint j=0 ; j<res_rows ; j++)
    {
        auto *p_res_stride = &(p_res_start[j*res_cols]);
        for(uint k=0 ; k<other_rows ; k++)
        {
            const auto l = this->get(j, k);
            for(uint i=0 ; i<res_cols ; i++)
            {
                const auto r = other.get(k, i);
                p_res_stride[i] = p_res_stride[i] + (l*r);
            }
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

Matrix Matrix::argmax(const Matrix &input)
{
    const auto rows = input.getDim(0);
    const auto cols = input.getDim(1);

    Matrix res = Matrix::zeros(rows, 1);
    res.setDim(rows, 1);
    for(int j=0 ; j<rows ; j++)
    {
        real maxVal = input.get(j, 0);
        uint idx = 0;
        for(int i=1 ; i<cols ; i++)
        {
            if(maxVal < input.get(j, i))
            {
                idx = i;
                maxVal = input.get(j, i);
            }
        }
        res.set(j, 0, idx);
    }
    return res;
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
    return testMultiply();
}

bool Matrix::testMultiply()
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

    Z_expc.set(0,0, 28);
    Z_expc.set(0,1, 34);
    Z_expc.set(1,0, 76);
    Z_expc.set(1,1, 98);
    Z_expc.set(2,0, 124);
    Z_expc.set(2,1, 162);

    // Erwartung berechnen
    auto Z = X.matmul(Y);

    Matrix boolMat = (Z == Z_expc);

    const auto numCorrect = Matrix::sum(boolMat);
    if(numCorrect == boolMat.getDim(0)*boolMat.getDim(1))
    {
        cout << "Test passed!" << endl;
        return true;
    }
    else
    {
        cout << "Test failed!" << endl;
        return false;
    }
}

}
