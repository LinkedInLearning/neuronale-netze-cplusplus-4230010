#ifndef MATRIX_H
#define MATRIX_H

#include <initializer_list>
#include <vector>
#include <cassert>
#include <functional>

typedef double real;
typedef unsigned int uint;

namespace Perc
{

struct MatrixDim
{
    uint mRows = 0;
    uint mCols = 0;
};

class Matrix
{
public:

    Matrix(){}

    /**
     * @brief splitIntoBatches
     * @param matrix
     * @param batchSize
     * @return
     */
    static std::vector<Matrix>
    splitIntoBatches(const Matrix &matrix,
                     const uint batchSize);

    /**
     * @brief setZeros Definiert eine Nullmatrix
     * @param rows
     * @param cols
     */
    Matrix setZeros(const uint rows,
                 const uint cols);

    /**
     * @brief assign Setze all Werte
     * @return
     */
    void assign(const real val);


    /**
     * @brief zeros
     * @param rows
     * @param cols
     * @return
     */
    static Matrix zeros(const uint rows,
                        const uint cols);


    /**
     * @brief prepend_bias Der ersten Spalte wird der Bias angehängt
     */
    void prepend_bias();

    /**
     * @brief sum   Summe aller Elemente der Matrix ermitteln
     * @param input
     * @return die Summe
     */
    static real sum(const Matrix &input);

    /**
     * @brief sum   Summe aller Elemente der Matrix ermitteln
     * @return die Summe
     */
    real sum() const;


    /**
     * @brief getDim    Dimensionen der Matrix zurückgeben
     * @param order 0=Zeilen, 1=Spalten
     * @return Zeilen oder Spalten
     */
    uint getDim(const uint order) const;

    /**
     * @brief getDim  Dimensionen der Matrix zurückgeben
     * @param order
     * @return Zeilen und Spalten (als Paar)
     */
    MatrixDim getDim() const;

    /**
     * @brief for_each  Für jedes Element wird operation angewandt
     * @param operation Operation as Function
     */
    void for_each(std::function<real (const real)> &&operation);

    /**
     * @brief setDim Matrix Dimensionen setzen
     * @param rows Zeilen
     * @param cols Spalten
     */
    auto setDim(const uint rows,
                const uint cols) -> void;

    /**
     * @brief set Setzen eines Wertes
     * @note inline optimiert diesen Aufruf indem keinen Aufrufstack anlegt
     * @param j Zeile
     * @param i Spalte
     * @param val Wert
     */
    inline auto set(const uint j,
             const uint i,
             const double val) -> void
    {
        mData[j*mCols+i] = val;
    }

    /**
     * @brief get Lesen eines Wertes
     * @note inline optimiert diesen Aufruf indem keinen Aufrufstack anlegt
     * @param j Zeile
     * @param i Spalte
     */
    inline real get(const uint j,
             const uint i) const
    {
        return mData[j*mCols+i];
    }

    /**
     * @brief transpose Gibt eine transponierte Matrix zurück
     */
    auto transposed() const -> Matrix;

    /**
     * @brief appendRS  Eine weitere Matrix rechts anhängen
     * @param other Matrix die annektiert wird.
     * @return
     */
    Matrix appendRS(const Matrix &other);

    /**
     * @brief slice_col Matrix an der einer gegebenen Spalte abschneiden
     * @param start
     */
    Matrix slice_col(const int start) const;

    /**
     * @brief matmul Matrix Multiplikation
     * @param other Die andere Matrix gegen die multipliziert wird.
     * @return die multiplizierte Matrix
     */
    auto matmul(const Matrix &other) const -> Matrix;

    /**
     * @brief operator - Subtraktion
     * @param other Rechte Seite die subtrahiert wird.
     * @return Ergebnis aus der Subtraktion
     */
    auto operator-(const Matrix &other) const -> Matrix;

    /**
     * @brief operator -= Subtraktion
     * @param other Rechte Seite wird direkt abgezogen
     * @return Ergebnis aus der Subtraktion
     */
    auto operator-=(const Matrix &other) -> Matrix;


    /**
     * @brief operator + Addition
     * @param other Rechte Seite die addiert wird.
     * @return Ergebnis aus der Addition
     */
    auto operator+(const Matrix &other) const -> Matrix;

    /**
     * @brief operator * Skalare Multiplikation
     * @param val der zu multipliziernder Wert
     * @return Ergebnis aus der Multiplikation
     */
    auto operator*(const real val) const -> Matrix;

    /**
     * @brief operator * Wert-für-Wert Multiplikation
     * @param other die zu multipliziernde Matrix
     * @return Ergebnis aus der Multiplikation
     */
    auto operator*(const Matrix &other) const -> Matrix;


    /**
     * @brief operator /
     * @param other Rechte Seite durch die diviert wird.
     * @return Ergebnis aus der Division
     */
    Matrix operator/(const real val) const;

    /**
     * @brief operator == Matrizenvergleich
     * @param other
     * @return
     */
    Matrix operator==(const Matrix &other) const;

    /**
     * @brief dim_cmp   Vergleichen der Dimensionen
     * @param other die zu vergleichende Matrix
     * @return true wenn die Matrizen gleich sind, ansonsten false
     */
    auto dim_cmp(const Matrix &other) const -> bool;

    /**
     * @brief argmax Gibt die Indizes als Matrix
     *               der jeweilen Spalte zurück
     * @param input
     * @return Index-Matrix
     */
    static Matrix argmax(const Matrix &input);


    /**
     * @brief round Auf/Abrunden der Matrix
     */
    static Matrix round(const Matrix &input);

    /**
     * @brief average   Mittelwert der Komponenten der Matrix berechen
     * @param input     Eingabematrix
     * @return Mittelwert
     */
    static real average(const Matrix &input);

    /**
     * @brief log   Alle Komponenten der Matrix ausgeben
     * @param input
     * @return
     */
    static Matrix log(const Matrix &input);

    /**
     * @brief print
     */
    auto print() -> void;


    /**
     * @brief The iterator class Die Iterator-Klasse ist ganz praktisch, wenn man der ganzen Matrix for-each anwenden möchte
     */
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
        self_type operator++() { self_type i = *this; ptr_++; return ptr_; }
        self_type operator++(int unused) { ptr_++; return *this; }
        reference operator*() { return *ptr_; }
        pointer operator->() { return ptr_; }
        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
    private:
        pointer ptr_;
    };

    iterator begin() {
        return iterator(mData.data());
    }

    iterator end() {
        return iterator(mData.data()+mData.size());
    }


    ///// Tests
    static bool runTests();

    static bool testMultiply();

private:

    std::vector<real> mData;

    unsigned int mCols = 0;
    unsigned int mRows = 0;

};

}

#endif // MATRIX_H
