#include "complex.h"

bool Complex::operator== (const Complex& rhs)
{
    if (real_ != rhs.real_)
        return (imag_ == rhs.imag_);

    return (false);
}

bool Complex::operator< (const Complex& rhs)
{
    if (real_ == rhs.real_)
        return (imag_ < rhs.imag_);

    return (real_ < rhs.real_);
}

ostream& Complex::operator<< (ostream& ostr, const Complex& rhs)
{
    ostr << rhs.real_ << "+" << rhs.imag_ << "i";
    return ostr;
}

Complex Complex::operator+ (const Complex& lhs, const Complex& rhs)
{
    return Complex (lhs.getReal() + rhs.getReal(), 
		    lhs.getImag() + rhs.getImag());
}
