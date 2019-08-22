#include <stdio.h>

class Mchar
{
public:
    char value;

    Mchar(char _value)
    {
        value = _value;
    }

    Mchar operator+(Mchar _mchar)
    {
        char _value = _mchar.value;

        while (_value != 0)
        {
            char carry = value & _value;
            char sum = value ^ _value;

            _value = carry << 1;
            value = sum;
        }

        return Mchar(value);
    }

    Mchar operator-(Mchar _mchar)
    {

        // compute two complement of _mchar
        Mchar one(1);
        Mchar flip(~_mchar.value);
        Mchar twoComplement = flip + one;

        return (*this) + twoComplement;
    }

    Mchar operator*(Mchar _mchar)
    {
        Mchar result(0);
        Mchar one(1);
        for (Mchar i = 0; i.value < value; i = i + one)
        {
            result = result + _mchar;
        }

        return result;
    }

    // https : //www.quora.com/How-do-I-divide-two-numbers-using-only-bit-operations-in-Java
    Mchar operator/(Mchar _mchar)
    {
        bool negative = false;
        Mchar one(1);
        if ((value & (1 << 7)) == (1 << 7))
        { // Check for signed bit
            negative = !negative;
            Mchar flip(~value);
            (*this) = flip + one;
        }
        if ((_mchar.value & (1 << 31)) == (1 << 31))
        {
            negative = !negative;
            Mchar flip(~_mchar.value);
            _mchar = flip + one;
        }
        char quotient = 0;
        char r;
        for (Mchar i = 6; i.value >= 0; i = i - one)
        {
            r = (_mchar.value << i.value);
            // Left shift divisor until it's smaller than dividend
            if ((char)r < (char)127 && (char)r >= (char)0)
            { // Avoid cases where comparison between long and int doesn't make sense
                if (r <= value)
                {
                    quotient |= (1 << i.value);
                    Mchar tmpR = r;

                    (*this) = (*this) - tmpR;
                }
            }
        }
        _mchar.value = quotient;

        if (negative)
        {
            Mchar flip(~quotient);
            _mchar = flip + one;
        }
        return _mchar;
    }

    void Print()
    {
    }
};

int main()
{
    FILE *fp;

    char charList[3];

    Mchar mchar = 10;
    Mchar mchar1 = 3;

    Mchar e = mchar / mchar1;

    printf("%d", e.value);

    // fp = fopen("file.txt", "w");
    // fwrite(charList, 1, sizeof(charList), fp);

    // fclose(fp);

    return (0);
}
