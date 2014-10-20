#include <bitset>
#include <cmath>
#include <cstdio>
#include <map>
#include <vector>
using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef map<int, int> mii;

ll _sieve_size;
bitset<10000010> bs;
vi primes;

void sieve(ll upperbound) {
  _sieve_size = upperbound + 1;
  bs.set();
  bs[0] = bs[1] = 0;

  for (ll i = 2; i <= _sieve_size; i++) {
    if (bs[i]) {
      for (ll j = i * i; j <= _sieve_size; j += i) {
        bs[j] = 0;
      }
      primes.push_back((int)i);
    }
  }
}

bool isPrime(ll N) {
  if (N <= _sieve_size) {
    return bs[N];
  }

  for (int i = 0; i < (int)primes.size(); i++) {
    if (N % primes[i] == 0) {
      return false;
    }
  }

  return true;
}

vi primeFactors(ll N) {
  vi factors;
  ll PF_idx = 0, PF = primes[PF_idx];

  while (N != 1 && (PF * PF <= N)) {
    while (N % PF == 0) {
      N /= PF; factors.push_back(PF);
    }
    PF = primes[++PF_idx];
  }

  if (N != 1) {
    factors.push_back(N);
  }

  return factors;
}

int main() {
  // first part: the Sieve of Eratosthenes
  sieve(10000000);                     // can go up to 10^7 (need few seconds)
  printf("%d\n", isPrime(2147483647)); // 10-digits prime
  printf("%d\n", isPrime(136117223861LL)); // not a prime, 104729*1299709

  vi res = primeFactors(2147483647);
}
