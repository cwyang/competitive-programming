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


ll numPF(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 0;

  while (N != 1 && (PF * PF <= N)) {
    while (N % PF == 0) {
      N /= PF; ans++;
    }

    PF = primes[++PF_idx];
  }

  if (N != 1) {
    ans++;
  }

  return ans;
}

ll numDiffPF(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 0;

  while (N != 1 && (PF * PF <= N)) {
    if (N % PF == 0) {
      ans++;
    }

    while (N % PF == 0) {
      N /= PF;
    }

    PF = primes[++PF_idx];
  }

  if (N != 1) {
    ans++;
  }

  return ans;
}

ll sumPF(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 0;

  while (N != 1 && (PF * PF <= N)) {
    while (N % PF == 0) {
      N /= PF;
      ans += PF;
    }

    PF = primes[++PF_idx];
  }

  if (N != 1) {
    ans += N;
  }

  return ans;
}

ll numDiv(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 1;

  while (N != 1 && (PF * PF <= N)) {
    ll power = 0;
    while (N % PF == 0) {
      N /= PF;
      power++;
    }

    ans *= (power + 1);
    PF = primes[++PF_idx];
  }

  if (N != 1) {
    ans *= 2;
  }

  return ans;
}

ll sumDiv(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = 1;

  while (N != 1 && (PF * PF <= N)) {
    ll power = 0;
    while (N % PF == 0) {
      N /= PF;
      power++;
    }

    ans *= ((ll)pow((double)PF, power + 1.0) - 1) / (PF - 1);
    PF = primes[++PF_idx];
  }

  if (N != 1){
    ans *= ((ll)pow((double)N, 2.0) - 1) / (N - 1);
  }

  return ans;
}

ll EulerPhi(ll N) {
  ll PF_idx = 0, PF = primes[PF_idx], ans = N;
  while (N != 1 && (PF * PF <= N)) {
    if (N % PF == 0) {
      ans -= ans / PF;
    }

    while (N % PF == 0) {
      N /= PF;
    }

    PF = primes[++PF_idx];
  }

  if (N != 1){
    ans -= ans / N;
  }

  return ans;
}

int main() {
  // first part: the Sieve of Eratosthenes
  sieve(10000000);                       // can go up to 10^7 (need few seconds)
  printf("%d\n", isPrime(2147483647));                        // 10-digits prime
  printf("%d\n", isPrime(136117223861LL));        // not a prime, 104729*1299709


  // second part: prime factors
  vi res = primeFactors(2147483647);   // slowest, 2147483647 is a prime
  for (vi::iterator i = res.begin(); i != res.end(); i++) printf("> %d\n", *i);

  res = primeFactors(136117223861LL);   // slow, 2 large pfactors 104729*1299709
  for (vi::iterator i = res.begin(); i != res.end(); i++) printf("# %d\n", *i);

  res = primeFactors(142391208960LL);   // faster, 2^10*3^4*5*7^4*11*13
  for (vi::iterator i = res.begin(); i != res.end(); i++) printf("! %d\n", *i);

  //res = primeFactors((ll)(1010189899 * 1010189899)); // "error"
  //for (vi::iterator i = res.begin(); i != res.end(); i++) printf("^ %d\n", *i);


  // third part: prime factors variants
  printf("numPF(%d) = %lld\n", 50, numPF(50)); // 2^1 * 5^2 => 3
  printf("numDiffPF(%d) = %lld\n", 50, numDiffPF(50)); // 2^1 * 5^2 => 2
  printf("sumPF(%d) = %lld\n", 50, sumPF(50)); // 2^1 * 5^2 => 2 + 5 + 5 = 12
  printf("numDiv(%d) = %lld\n", 50, numDiv(50)); // 1, 2, 5, 10, 25, 50, 6 divisors
  printf("sumDiv(%d) = %lld\n", 50, sumDiv(50)); // 1 + 2 + 5 + 10 + 25 + 50 = 93
  printf("EulerPhi(%d) = %lld\n", 50, EulerPhi(50)); // 20 integers < 50 are relatively prime with 50

  return 0;
}
