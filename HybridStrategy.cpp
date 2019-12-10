#include <iostream>
#include <vector>
// #include <limits>

using namespace std;

typedef vector<int> vint;

int ceil_log2(int x) {
  return 32 - __builtin_clz(x - 1);
}

unsigned int create_max() {
	unsigned int max = 0;

        // computing NOT of 0
        max = ~max;

        // now max has all bits equal 1, including the sign bit
        // therefore its a negative number
        // to fix we right shift max to produce 01111...
        max = max >> 1;

	return max;
}

struct RMQ {
	vint& v;
	vector<vint> A;
	vint block;

	RMQ(vint& v): v(v), block((int)(v.size()/ceil_log2(v.size())), create_max()), A((int)(v.size()/ceil_log2(v.size())), vint(ceil_log2((int)(v.size()/ceil_log2(v.size()))) + 1, 0)) {
		int b = ceil_log2(v.size());

		cout << b << endl;

		int blk_idx = -1;

		int blk_sz = b;
	
		cout << "block size=" << block.size() << endl;	
		for(int j=0; j < block.size(); j++)
                        cout << block[j] << " ";
                cout << endl;

		// iterate over the n elements in v and create the block summary above
		for(int i=0; i < v.size(); i++){
			if ((i % b) == 0){
				blk_idx ++;
				cout << "blok_idx=" << blk_idx << endl;
			}

			if (block[blk_idx] > v[i]){
				block[blk_idx] = v[i];
			}
		}

		// take the array of the block minima and construct a SPARSE TABLE structure
		// over the block minima
		// toplevel(block);
		int n_toplevel = block.size();
		int i,j,k;
		for (i=0; i < n_toplevel; i++){
			A[i][0] = i;
		}
		j = 1;
		k = 1;
		do {
			for (i=0; i + k < n_toplevel; ++i){
				if (block[A[i][j-1]] < block[A[i+k][j-1]]){
					A[i][j] = A[i][j-1];
				} else {
					A[i][j] = A[i+k][j-1];
				}
			}
			k <<=1 ;
			++j;
		} while (k < n_toplevel);
		
		for(int j=0; j < block.size(); j++)
			cout << block[j] << " ";
		cout << endl;
	}

	int queryST(int i, int j) {
   		 int k = ceil_log2(j - i + 1) - 1;
		    if (block[A[i][k]] < block[A[j - (1 << k) + 1][k]]) {
		      return A[i][k];
		    } else {
		      return A[j - (1 << k) + 1][k];
		    }
	  }

	int query(int l, int r){
		int b = ceil_log2(v.size());

		int res = create_max();

		int blk_idx_l = (int)(l/b);
		int blk_idx_r = (int)(r/b);
		int minima_toplevel;



		while ((l < r) && ((l%b) != 0) && (l != 0)){
			if (v[l] < res)
				res = v[l];
			l ++;
		}
		blk_idx_l = (int)(l/b);

		blk_idx_r = (int)(r/b);
		int r_idx = r;
		while ( (l < r_idx) && ((r_idx%b) != 0) && (r_idx != 0) ){
			r_idx = r_idx - 1;
		}
		blk_idx_r = (int)((r_idx)/b);
		bool keep_r = false;
		if (blk_idx_l < blk_idx_r){
			blk_idx_r --;
			keep_r = true;
		}
		cout << "LEFT = " << blk_idx_l << " RIGHT = " << blk_idx_r << endl;
		minima_toplevel = queryST(blk_idx_l, blk_idx_r);
		cout << "QUERY ST = " << block[minima_toplevel] << endl;
		if (block[minima_toplevel] < res)
			res = block[minima_toplevel];
		while ((r_idx < r) && keep_r){
			if (v[r_idx] < res)
				res = v[r_idx];
			r_idx++;
		}
		/*while ((l + b) <= r){
			if (block[(int)(l/b)] < res)
				res = block[(int)(l/b)];
			l = l + b;
		}
		while (l <= r){
			if(v[l] < res)
				res = v[l];
			l ++;
		}*/
		return res;
	}

};

int main(){

	vint v = {31, 41, 59, 26, 53, 58, 97, 93, 23, 84, 62, 64, 33, 83, 27};

	RMQ solver(v);

	cout << "SOLVING" << endl;
	cout << "SOLVING RMQ(1,13) = " << solver.query(1,13) << endl;
	cout << "SOLVING RMQ(2,7) = " << solver.query(2,7) << endl;
	cout << "SOLVING RMQ(4,5) = " << solver.query(4,5) << endl;

}
