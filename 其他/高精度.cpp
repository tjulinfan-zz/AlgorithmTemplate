#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <iostream>
using namespace std;

const int MAXLENGTH = 2000;

class Bigint
{
public:
    //构造函数
    Bigint();
    Bigint(const Bigint&);
    Bigint(int);
    Bigint(const char *);

    int oper, length;
    int a[MAXLENGTH];
    //赋值
    Bigint& operator = (const Bigint&);
    Bigint& operator = (int);
    Bigint& operator = (char *);
    //比较
    bool operator < (const Bigint&) const;
    bool operator <= (const Bigint&) const;
    bool operator > (const Bigint&) const;
    bool operator >= (const Bigint&) const;
    bool operator == (const Bigint&) const;
    bool operator != (const Bigint&) const;
    //其他运算
    Bigint operator - () const;
    Bigint operator + (const Bigint&);
    Bigint operator - (const Bigint&);
    Bigint operator * (const Bigint&);
    Bigint operator * (int);
    Bigint operator / (const Bigint&);
    Bigint operator / (int);
    Bigint operator % (const Bigint&);
    Bigint operator % (int);
};

//其他操作
Bigint abs(const Bigint&);
bool read(Bigint&);
void write(const Bigint&);
Bigint sqr(const Bigint&);
Bigint sqrt(const Bigint&);
Bigint gcd(const Bigint&, const Bigint&);
Bigint lcm(const Bigint&, const Bigint&);

//---------------------------------------------------------------------------

Bigint::Bigint()
{
    length = 0;
    memset(a, 0, sizeof(a));
}

Bigint::Bigint(const Bigint& rhf)
{
    (*this) = rhf;
}

Bigint::Bigint(int m)
{
    (*this) = m;
}

Bigint::Bigint(const char *s)
{
    (*this) = s;
}

Bigint& Bigint::operator = (const Bigint& m)
{
    if (this != &m)
    {
        oper = m.oper;
        length = m.length;
        memcpy(a, m.a, MAXLENGTH * sizeof(int));
    }
    return *this;
}

Bigint& Bigint::operator = (int m)
{
    oper = (m < 0 ? -1 : 1);
    m = abs(m);
    memset(a, 0, sizeof(a));
    for (length = 0; m; m /= 10000)
        a[length ++] = m % 10000;
    return *this;
}

Bigint& Bigint::operator = (char *s)
{
    if (s[0] == '-' || s[0] == '+')
    {
        oper = (s[0] == '-' ? -1 : 1);
        s ++;
    }
    int L = strlen(s);
    length = (L + 3) / 4;
    memset(a, 0, sizeof(a));
    for (int i = 0; i < L; ++ i)
        a[(L - i) / 4] = a[(L - i) / 4] * 10 + s[i] - '0';
    return *this;
}

bool Bigint::operator < (const Bigint& rhf) const
{
    if (oper != rhf.oper)
        return oper < rhf.oper;
    if (length != rhf.length)
        return oper * length < rhf.oper * rhf.length;
    for (int i = length - 1; i >= 0; -- i)
        if (a[i] != rhf.a[i])
            return oper * a[i] < rhf.oper * rhf.a[i];
    return false;
}

bool Bigint::operator <= (const Bigint& rhf) const
{
    return !(rhf < (*this));
}

bool Bigint::operator > (const Bigint& rhf) const
{
    return rhf < (*this);
}

bool Bigint::operator >= (const Bigint& rhf) const
{
    return !((*this) < rhf);
}

bool Bigint::operator == (const Bigint& rhf) const
{
    return !(rhf < (*this) || (*this) < rhf);
}

bool Bigint::operator != (const Bigint& rhf) const
{
    return rhf < (*this) || (*this) < rhf;
}

Bigint Bigint::operator - () const
{
    Bigint t = (*this);
    t.oper = -t.oper;
    return t;
}

Bigint Bigint::operator + (const Bigint& rhf) const
{
    if (m.length == 0) return *this;
    if (length == 0) return rhf;
    if (oper == rhf.oper)
    {
        Bigint t;
        t.oper = oper;
        t.length = max(length, rhf.length) + 1;
        for (int i = 0; i < )
    }
}

int main()
{
    return 0;
}
