#ifndef MATHVECTOR_H
#define MATHVECTOR_H

#include <initializer_list>
#include <vector>
#include <cassert>

typedef double real;

namespace Perc
{

class Vector
{
public:

    Vector(){}

    Vector(std::initializer_list<real> l) : baseVec(l) {}

    void append(std::initializer_list<real> l) {
        baseVec.insert(baseVec.end(), l.begin(), l.end());
    }

    class iterator
    {
    public:
        typedef iterator self_type;
        typedef real value_type;
        typedef real& reference;
        typedef real* pointer;
        typedef std::forward_iterator_tag iterator_category;
        typedef int difference_type;
        iterator(pointer ptr) : ptr_(ptr) { }
        self_type operator++() { self_type i = *this; ptr_++; return i; }
        self_type operator++(int junk) { ptr_++; return *this; }
        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
    private:
        pointer ptr_;
    };

    Vector operator=(Vector &other) {
        baseVec.clear();
        baseVec.insert(baseVec.end(), other.begin(), other.end());
        return *this;
    }

    real& operator[](const unsigned int idx) {
        return baseVec[idx];
    }

    const real& operator[](const unsigned int idx) const {
        return baseVec[idx];
    }

    iterator begin() {
        return iterator(baseVec.data());
    }

    iterator end() {
        return iterator(baseVec.data()+baseVec.size());
    }

    unsigned int size() const {
        return baseVec.size();
    }

    real dot(const Vector &other) const {

        assert(baseVec.size() == other.size());

        real sum = 0.0;
        const auto numElem = this->size();
        for(unsigned int i = 0 ; i<numElem ; i++)
        {
            sum = sum + (baseVec[i]*other[i]);
        }
        return sum;
    }

private:
    std::vector<real> baseVec;
};

}

#endif // MATHVECTOR_H
