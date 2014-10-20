#include <iostream>
#include <sstream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <cstdlib>

#define MIN(x,y) ((x) < (y) ? (x) : (y))
#define MAX(x,y) ((x) > (y) ? (x) : (y))

using namespace std;

typedef unsigned int uint32;
typedef unsigned long long int uint64;

class BigUInt {
    vector<uint32> data;

    friend istream& operator>>(istream& is, BigUInt& bi);
    friend ostream& operator<<(ostream& os, BigUInt& bi);
    friend uint32 operator%(BigUInt& bi, uint32 v);

  public:

    BigUInt() {}

    BigUInt(string s) {
        fromstring(s);
    }

    void setzero() {
        data.clear();
    }

    void fromstring(string s) {
        setzero();
        size_t n = s.size();
        static const uint32 tens[] = {0, 10, 100, 1000, 10000, 100000,
                                      1000000, 10000000, 100000000};
        for (size_t i = 0; i < n; i += 8) {
            size_t len = MIN(8, s.size() - i);
            string part = s.substr(i, len);
            this->multiply(tens[len]);
            istringstream is(part);
            int a;
            is >> a;
            this->add(a);
        }
    }

    string tostring() {
        ostringstream os;
        os << doubleval();
        return os.str();
    }

    void add(uint32 val) {
        uint64 left = val;
        for (size_t i = 0; left; i++) {
            if (i >= data.size()) {
                data.push_back(0);
            }
            uint64 sum = data[i] + left;
            data[i] = ((uint32)sum & ~(uint32)0);
            left = sum >> (sizeof(uint32) * 8);
        }
    }

    void multiply(uint32 val) {
        uint64 mente = 0;
        for (size_t i = 0; i < data.size() || mente; i++) {
            if (i >= data.size()) {
                data.push_back(0);
            }
            uint64 product = (uint64)data[i] * (uint64)val + mente;
            data[i] = ((uint32)product & ~(uint32)0);
            mente = product >> (sizeof(uint32) * 8);
        }
    }

    static uint32 mod(BigUInt& bi, uint32 val) {
        uint64 rest = 0;
        for (int i = bi.data.size() - 1; i >= 0; i--) {
            rest = ((rest << (sizeof(uint32) * 8)) + bi.data[i]) % val;
        }
        return rest;
    }

    double doubleval() {
        double dval = 0;
        for (size_t i = 0; i < data.size(); i++) {
            dval += (double)data[i] * pow(2.0, (int)(sizeof(uint32) * 8 * i));
        }
        return dval;
    }
};

istream& operator>>(istream& is, BigUInt& bi) {
    string s;
    is >> s;
    bi.fromstring(s);
    return is;
}

ostream& operator<<(ostream& os, BigUInt& bi) {
    os << bi.tostring();
    return os;
}

uint32 operator%(BigUInt& bi, uint32 v) {
    return BigUInt::mod(bi, v);
}
