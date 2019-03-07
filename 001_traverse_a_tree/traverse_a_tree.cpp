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
#include <queue>

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

	vector<int> inorderTraversal(TreeNode* root) {
        vector<int> output;
		if (root){
			vector<int> output_left = this->inorderTraversal(root->left);
			vector<int> output_right = this->inorderTraversal(root->right);
			output.insert(output.end(), output_left.begin(), output_left.end());
			output.push_back(root->val);
			output.insert(output.end(), output_right.begin(), output_right.end());
		}
		return output;
    }

	vector<int> postorderTraversal(TreeNode* root) {
        vector<int> output;
		if (root){
			vector<int> output_left = this->postorderTraversal(root->left);
			vector<int> output_right = this->postorderTraversal(root->right);
			output.insert(output.end(), output_left.begin(), output_left.end());
			output.insert(output.end(), output_right.begin(), output_right.end());
			output.push_back(root->val);
		}
		return output;
    }

	vector<vector<int> > levelOrder(TreeNode* root) {
        vector<vector<int> > output;
		if (root){
			vector<int> current_level;
			current_level.push_back(root->val);
			output.push_back(current_level);
			vector<vector<int> > output_left = this->levelOrder(root->left);
			vector<vector<int> > output_right = this->levelOrder(root->right);
			for (int i = 0; ; i++){
				vector<int> son_level;
				if (i < output_left.size()){
					son_level.insert(son_level.end(), output_left[i].begin(), output_left[i].end());
				}
				if (i < output_right.size()){
					son_level.insert(son_level.end(), output_right[i].begin(), output_right[i].end());
				}
				if (son_level.size()){
					output.push_back(son_level);
				}
				else {
					break;
				}
			}
		}
		return output;
    }

	int maxDepth(TreeNode* root) {
        if (root){
			return (max(this->maxDepth(root->left), this->maxDepth(root->right)) + 1);
        }
		else {
			return 0;
		}
    }

	bool isSymmetric(TreeNode* root) {
        if (!root){
			return true;
        }
		TreeNode *left = NULL;
		TreeNode *right = NULL;
		queue<TreeNode *> queue_left, queue_right;
		queue_left.push(root->left);
		queue_right.push(root->right);
		while (!queue_left.empty() && !queue_right.empty()){
			left = queue_left.front();
			right = queue_right.front();
			queue_left.pop();
			queue_right.pop();
			if (!left && !right){
				continue;
			}
			if (left && right){
				if (left->val != right->val){
					return false;
				}
				queue_left.push(left->left);
				queue_right.push(right->right);
				queue_left.push(left->right);
				queue_right.push(right->left);
				continue;
			}
			return false;
		}
		return true;
    }

	bool hasPathSum(TreeNode* root, int sum) {
		if (root){
			sum -= root->val;
			if (sum == 0){
				if (!root->left && !root->right){
					return true;
				}
			}
			return (this->hasPathSum(root->left, sum) || this->hasPathSum(root->right, sum));
		}
		else {
			return false;
		}
    }
};

int main(int argc, char *argv[]){
	TreeNode node1(1);
	TreeNode node2(2);
	TreeNode node3(3);

	node1.right = &node2;
	node2.left = &node3;

	Solution solution;
	vector<int> test_result = solution.preorderTraversal(&node1);
	cout<<"Test pre-order:"<<endl;
	for (vector<int>::iterator it = test_result.begin(); it != test_result.end(); it++){
		cout<<*it<<endl;
	}
	
	test_result = solution.inorderTraversal(&node1);
	cout<<"Test in-order:"<<endl;
	for (vector<int>::iterator it = test_result.begin(); it != test_result.end(); it++){
		cout<<*it<<endl;
	}

	test_result = solution.postorderTraversal(&node1);
	cout<<"Test post-order:"<<endl;
	for (vector<int>::iterator it = test_result.begin(); it != test_result.end(); it++){
		cout<<*it<<endl;
	}

	TreeNode node9(9);
	TreeNode node20(20);
	TreeNode node15(15);
	TreeNode node7(7);

	node3.left = &node9;
	node3.right = &node20;
	node20.left = &node15;
	node20.right = &node7;

	vector<vector<int> > test_result_level = solution.levelOrder(&node3);
	cout<<"Test level-order:"<<endl;
	for (vector<vector<int> >::iterator it = test_result_level.begin(); it != test_result_level.end(); it++){
		for (vector<int>::iterator it_sub = it->begin(); it_sub != it->end(); it_sub++){
			cout<<*it_sub<<" ";
		}
		cout<<endl;
	}

	cout<<"Test max depth:"<<endl;
	cout<<solution.maxDepth(&node3)<<endl;

	cout<<"Test symmetric:"<<endl;
	TreeNode symmetric_tree[7](0);
	symmetric_tree[0] = 1;
	symmetric_tree[1] = 2;
	symmetric_tree[2] = 2;
	symmetric_tree[3] = 3;
	symmetric_tree[4] = 4;
	symmetric_tree[5] = 4;
	symmetric_tree[6] = 3;
	symmetric_tree[0].left = &symmetric_tree[1];
	symmetric_tree[0].right = &symmetric_tree[2];
	symmetric_tree[1].left = &symmetric_tree[3];
	symmetric_tree[1].right = &symmetric_tree[4];
	symmetric_tree[2].left = &symmetric_tree[5];
	symmetric_tree[2].right = &symmetric_tree[6];
	if (solution.isSymmetric(symmetric_tree)){
		cout<<"yes"<<endl;
	}
	else {
		cout<<"no"<<endl;
	}
	TreeNode unsymmetric_tree[5](0);
	unsymmetric_tree[0] = 1;
	unsymmetric_tree[1] = 2;
	unsymmetric_tree[2] = 2;
	unsymmetric_tree[3] = 3;
	unsymmetric_tree[4] = 3;
	unsymmetric_tree[0].left = &unsymmetric_tree[1];
	unsymmetric_tree[0].right = &unsymmetric_tree[2];
	unsymmetric_tree[1].right = &unsymmetric_tree[3];
	unsymmetric_tree[2].right = &unsymmetric_tree[4];
	if (solution.isSymmetric(unsymmetric_tree)){
		cout<<"yes"<<endl;
	}
	else {
		cout<<"no"<<endl;
	}

	cout<<"Test has path sum:"<<endl;
	TreeNode sum_tree[9](0);
	sum_tree[0] = 5;
	sum_tree[1] = 4;
	sum_tree[2] = 8;
	sum_tree[3] = 11;
	sum_tree[4] = 13;
	sum_tree[5] = 4;
	sum_tree[6] = 7;
	sum_tree[7] = 2;
	sum_tree[8] = 1;
	sum_tree[0].left = &sum_tree[1];
	sum_tree[0].right = &sum_tree[2];
	sum_tree[1].left = &sum_tree[3];
	sum_tree[2].left = &sum_tree[4];
	sum_tree[2].right = &sum_tree[5];
	sum_tree[3].left = &sum_tree[6];
	sum_tree[3].right = &sum_tree[7];
	sum_tree[5].right = &sum_tree[8];
	if (solution.hasPathSum(sum_tree, 22)){
		cout<<"yes"<<endl;
	}
	else {
		cout<<"no"<<endl;
	}
	
	return 0;
}


