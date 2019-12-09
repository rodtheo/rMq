#include <iostream>
#include <vector>
#include <limits>

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

unsigned int create_min() {
	return 0;
}

struct RMQ {
	vint& v;
	vector<vint> A;
	vint block;
	
	RMQ(vint& v): v(v), block((int)(v.size()/ceil_log2(v.size())), create_min()) {
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

			if (block[blk_idx] < v[i]){
				block[blk_idx] = v[i];
			}
		}

		for(int j=0; j < block.size(); j++)
			cout << block[j] << " ";
		cout << endl;
	}

	int query(int l, int r){
		int b = ceil_log2(v.size());

		int res = create_min();

		int blk_idx_l = (int)(l/b);
		int blk_idx_r = (int)(r/b);

		while ((l < r) && ((l%b) != 0) && (l != 0)){
			if (v[l] > res)
				res = v[l];
			l ++;
		}
		while ((l + b) <= r){
			if (block[(int)(l/b)] > res)
				res = block[(int)(l/b)];
			l = l + b;
		}
		while (l <= r){
			if(v[l] > res)
				res = v[l];
			l ++;
		}

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
