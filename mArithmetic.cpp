#include<bits/stdc++.h>

using namespace std;
const int mod = 1e9 + 7;
const int MaxN = 1e3;
vector<long long> fact(MaxN + 1, 1LL);
vector<long long> inv(MaxN + 1, 1LL);
int modpow(int a, int n){
	int res = 1;
	while(n > 0){
		if(n & 1 == 1){ //si bit prendido
			res =( 1LL * res * a) % mod;
		}
		a = (1LL * a * a) % mod;
		n >>= 1;
	}
	return res;
}
void factorial(){
	for(int i=1; i<= MaxN; i++){
		fact[i] = (i * fact[i - 1]) % mod;
	}
}

void inverse(){
	for(int i=1; i<= MaxN; i++){
		inv[i] = modpow(fact[i], mod - 2);
	}
}
long long  C(int n , int k){
	if(k > n) return 0;
	long long pr1 = (1LL * fact[n] * inv[k]) % mod;
	pr1 = ( 1LL * pr1 * inv[n - k ]) % mod;
	return pr1;
}

int main(){
	ios_base::sync_with_stdio(0); cin.tie(0);
	factorial();
	inverse();
	cout << C(6,2) << "\n";

	return 0;
}
