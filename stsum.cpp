
#include<bits/stdc++.h>

using namespace std;

typedef vector<int> vi;

struct SegmentTree{
	int n;
	vi A, st, lazy;

	int l(int p){return p << 1;}
	int r(int p){return (p << 1) + 1;}

	int operacion(int a, int b){
		return a + b; // mas si es suma max si es maximo etc.
	}

	void build(int p, int L, int R){
		if(L == R){
			st[p] = A[L];
		}else{
			int m = (L + R) / 2;
			build(l(p), L, m);
			build(r(p),m+1,R);
			st[p] = operacion(st[l(p)],st[r(p)]);
		}
//		for(auto x: st){
//			cout << x << " " ;
//		}
//		cout << "\n";
	}

	void propagate(int p, int L, int R){
		if(lazy[p] != -1){
			st[p] = (R - L + 1) * lazy[p];
			printf("propagamos lazy de %d con %d\n",p,lazy[p]);
			if(L != R){
				lazy[l(p)] = lazy[p];
				lazy[r(p)] = lazy[p];
				printf("propagamos a los hijos %d %d por %d\n",l(p), r(p), lazy[p]);
			}else{
				A[L] = lazy[p];
				printf("Llegamos a un cao baje %d == L == R en %d actualizamos por %d\n", L, p, lazy[p]);
			}
			lazy[p] = -1; // ya nada mas que propagar en este nodo
		}
	}

	int RMQ(int p, int L, int R, int i, int j){
		propagate(p, L, R);
		if(i > j) return 0; // caso no posible
		if((L >= i) && (R <= j)) return st[p]; // cae completamente en el rango, ademas que ya esta propagado la lazy flag
		int m = (L + R) / 2; 
		return operacion(RMQ(l(p),L,m,i, min(m,j)), RMQ(r(p), m + 1, R, max(i, m + 1), j)); // los minimos y maximos para que sean disjuntos
	}

	void update(int p, int L, int R, int i, int j, int val){
		propagate(p, L, R);
		if(i > j) return;
		if((L >= i) && (R <= j)){
			lazy[p] =  val; // añadimos lazy flag
			cout << "LAZY FLAG DE " << lazy[p] <<" En "<< p << "\n";
			propagate(p, L, R);
		}else{
			int m = (L + R) / 2;
			update(l(p), L, m ,i ,min(m,j), val);
			update(r(p), m + 1, R, max(i, m + 1), j , val);
			int lsubtree = (lazy[l(p)] != -1) ? lazy[l(p)] : st[l(p)];
			int rsubtree = (lazy[r(p)] != -1) ? lazy[r(p)] : st[r(p)];
			if(lazy[l(p)] != -1) lsubtree *= (m - L + 1);
			if(lazy[r(p)] != -1) rsubtree *= (R - (m + 1) + 1);
		       // st[p] = (lsubtree <= rsubtree) ? st[l(p)] : st[r(p)]; //checar aqui	
			st[p] = lsubtree + rsubtree;
			printf("Actualizamos %d por la suma %d + %d\n",p,lsubtree, rsubtree);
		}
	}
	SegmentTree(const vi &Ai){
		A = Ai;
		n = (int)A.size();
		st.assign(4 * n, 0);
		lazy.assign(4 * n, -1);
		build(1, 0, n - 1);
	}
	void update(int i, int j, int val){
		update(1, 0, n - 1, i, j , val);
	}
	int RMQ(int i, int j){
		return RMQ(1, 0, n - 1, i,j);
	}
};

int main(){
	//ios_base::sync_with_stdio(0); cin.tie(0);
	int k;
	cin >> k;
	vector<int> B(k);
	for(auto &it: B) cin >> it;
	int t = 5;
	SegmentTree A(B);
	while(t--){
		int u, v, w;
		cin >> u >> v;
		u--,v--;
		cout << A.RMQ(u, v) << "\n";
		cin >> u >> v >> w;
		u--,v--;
		A.update(u, v, w);

	}
	return 0;
}
