/**
 * pre-order
 *  1
 * 2 3
 * in-order
 *  2
 * 1 3
 * post-order
 *  3
 * 1 2
 * level-order
 *   1
 *  2 3
 * 4 5 6
**/

#include <iostream>
#include <vector>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x): val(x), left(NULL), right(NULL){}
};

class Solution {
public:
	vector<int> preorderTraversal(TreeNode *root){
		vector<int> output;
		if (root){
			output.push_back(root->val);
			vector<int> output_left = this->preorderTraversal(root->left);
			vector<int> output_right = this->preorderTraversal(root->right);
			output.insert(output.end(), output_left.begin(), output_left.end());
			output.insert(output.end(), output_right.begin(), output_right.end());
		}
		return output;
	}
};

int main(int argc, char *argv[]){
	TreeNode tree1(1);
	TreeNode tree2(2);
	TreeNode tree3(3);

	tree1.right = &tree2;
	tree2.left = &tree3;

	Solution solution;
	vector<int> test_result = solution.preorderTraversal(&tree1);
	cout<<"Test pre-order:"<<endl;
	for (vector<int>::iterator it = test_result.begin(); it != test_result.end(); it++){
		cout<<*it<<endl;
	}
	
	return 0;
}


