#include "qrsaencryption.h"
//#include "BigInt.hpp"

template<class INT>
INT eulerFunc(INT p, INT q) {
    return (p - 1) * (q - 1);
}

template<class INT>
INT mul(INT a, INT b, INT m){
    if(b==1)
        return a;
    if(b%2==0){
        INT t = mul(a, b/2, m);
        return (2 * t) % m;
    }
    return (mul(a, b-1, m) + a) % m;
}

template<class INT>
INT pows(INT a, INT b, INT m){
    if(b==0)
        return 1;
    if(b%2==0){
        INT t = pows(a, b/2, m);
        return mul(t , t, m) % m;
    }
    return ( mul(pows(a, b-1, m) , a, m)) % m;
}

template<class INT>
bool gcd(INT a, INT b) {
    INT c;
    while ( a != 0 ) {
      c = a;
      a = b % a;
      b = c;
    }
    return b;
}

template<class INT>
INT randNumber() {
    srand(static_cast<unsigned int>(time(nullptr)));

    int longDiff = 1;
    INT minVal = 0;

    if (typeid (INT).hash_code() == typeid (uint64_t).hash_code()) {
        longDiff = 1;
        minVal = 0x10000000;
    } else if (typeid (INT).hash_code() == typeid (unsigned __int128).hash_code()) {
        longDiff = 2;
        minVal = 0x1000000000000000;

    }/* else if (typeid (INT).hash_code() == typeid (uint256_t).hash_code()) {
        longDiff = 8;
        minVal = "0x1000000000000000000000000000000000000000000000000000000000000000";
    }*/

    INT res = 1;

    while (longDiff > 0 || minVal > res) {
        longDiff--;
        res *= static_cast<unsigned int>(rand());
    }

    return res;
}

template<class INT>
bool ferma(INT x){
    if(x == 2)
        return true;


    for(int i = 0; i < 100; i++){
        INT a = (randNumber<INT>() % (x - 2)) + 2;
        if (gcd<INT>(a, x) != 1)
            return false;
        if( pows(a, x-1, x) != 1)
            return false;
    }
    return true;
}

template<class INT>
bool isPrime(INT n) {
    if(n < 2)
        return false;

    if(n == 2)
        return true;

    if(n % 2 == 0)
        return false;

    for(INT i = 3; (i * i) <= n; i+=2) {
        if(n % i == 0 ) return false;
    }

    return true;
}

// to du
template<class INT>
INT randPrimeNumber(INT no = 0) {
    INT n = randNumber<INT>();
    while (n == no) {
        n = randNumber<INT>();
    };

    while (!ferma(n)) {
       n++;
    }

    return n;
}



template<class INT>
INT ExtEuclid(INT a, INT b)
{
    INT x = 0, y = 1, u = 1, v = 0, gcd = b, m, n, q, r;
    while (a != 0) {
        q = gcd / a;
        r = gcd % a;
        m = x - u * q;
        n = y - v * q;
        gcd = a;
        a = r;
        x = u;
        y = v;
        u = m;
        v = n;
    }
    return y;
}

//// Calling this function will generate a public and private key and store them in the pointers
//// it is given.
//void rsa_gen_keys(struct public_key_class *pub, struct private_key_class *priv, char *PRIME_SOURCE_FILE)
//{
//  FILE *primes_list;
//  if(!(primes_list = fopen(PRIME_SOURCE_FILE, "r"))){
//    fprintf(stderr, "Problem reading %s\n", PRIME_SOURCE_FILE);
//    exit(1);
//  }

//  // count number of primes in the list
//  long long prime_count = 0;
//  do{
//    int bytes_read = fread(buffer,1,sizeof(buffer)-1, primes_list);
//    buffer[bytes_read] = '\0';
//    for (i=0 ; buffer[i]; i++){
//      if (buffer[i] == '\n'){
//	prime_count++;
//      }
//    }
//  }
//  while(feof(primes_list) == 0);


//  // choose random primes from the list, store them as p,q

//  long long p = 0;
//  long long q = 0;

//  long long e = powl(2, 8) + 1;
//  long long d = 0;
//  char prime_buffer[MAX_DIGITS];
//  long long max = 0;
//  long long phi_max = 0;

//  srand(time(NULL));

//  do{
//    // a and b are the positions of p and q in the list
//    int a =  (double)rand() * (prime_count+1) / (RAND_MAX+1.0);
//    int b =  (double)rand() * (prime_count+1) / (RAND_MAX+1.0);

//    // here we find the prime at position a, store it as p
//    rewind(primes_list);
//    for(i=0; i < a + 1; i++){
//    //  for(j=0; j < MAX_DIGITS; j++){
//    //	prime_buffer[j] = 0;
//    //  }
//      fgets(prime_buffer,sizeof(prime_buffer)-1, primes_list);
//    }
//    p = atol(prime_buffer);

//    // here we find the prime at position b, store it as q
//    rewind(primes_list);
//    for(i=0; i < b + 1; i++){
//      for(j=0; j < MAX_DIGITS; j++){
//	prime_buffer[j] = 0;
//      }
//      fgets(prime_buffer,sizeof(prime_buffer)-1, primes_list);
//    }
//    q = atol(prime_buffer);

//    max = p*q;
//    phi_max = (p-1)*(q-1);
//  }
//  while(!(p && q) || (p == q) || (gcd(phi_max, e) != 1));

//  // Next, we need to choose a,b, so that a*max+b*e = gcd(max,e). We actually only need b
//  // here, and in keeping with the usual notation of RSA we'll call it d. We'd also like
//  // to make sure we get a representation of d as positive, hence the while loop.
//  d = ExtEuclid(phi_max,e);
//  while(d < 0){
//    d = d+phi_max;
//  }

//  printf("primes are %lld and %lld\n",(long long)p, (long long )q);
//  // We now store the public / private keys in the appropriate structs
//  pub->modulus = max;
//  pub->exponent = e;

//  priv->modulus = max;
//  priv->exponent = d;
//}

template<class INT>
bool keyGenerator(QByteArray &pubKey,
                 QByteArray &privKey) {

    INT p = randPrimeNumber<INT>();
    INT q = randPrimeNumber<INT>(p);

    INT modul = p * q;
    INT eilor = eulerFunc(p, q);
    INT e;

    do {
        e = randPrimeNumber<INT>();

    } while((gcd<INT>(eilor, e) != 1) || eilor < e);

    INT d = randPrimeNumber<INT>();

    d = ExtEuclid(eilor, e);
    while(d < 0) {
        d = d + eilor;
    }

    if (typeid (INT).hash_code() == typeid (uint64_t).hash_code()) {
       pubKey.append(reinterpret_cast<char*>(&e), sizeof(e));
       pubKey.append(reinterpret_cast<char*>(&modul), sizeof(modul));
       privKey.append(reinterpret_cast<char*>(&d), sizeof(d));
       privKey.append(reinterpret_cast<char*>(&modul), sizeof(modul));

    }

    return false;

}

QRSAEncryption::QRSAEncryption()
{

}

QByteArray QRSAEncryption::encode(const QByteArray &rawData, const QByteArray &pubKey)
{

}

QByteArray QRSAEncryption::decode(const QByteArray &rawData, const QByteArray &privKey)
{

}


bool QRSAEncryption::generatePairKey(QByteArray &pubKey,
                                     QByteArray &privKey,
                                     QRSAEncryption::Rsa rsa)
{
    switch (rsa) {
    case RSA_128: {
        if (!keyGenerator<uint64_t>(pubKey, privKey)) {
            return false;
        }
        break;
    }
    case RSA_256: {
        if (!keyGenerator<unsigned __int128>(pubKey, privKey)) {
            return false;
        }
        break;
    }
//    case RSA_512: {
//        using INT = uint256_t;
//        break;
//    }
    default: return false;
    }


    return true;
}


