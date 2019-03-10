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
#include <sstream>
#include <vector>
#include <queue>
#include <deque>
#include <string>

using namespace std;

struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x): val(x), left(NULL), right(NULL){}
};

class Node {
public:
    int val;
    Node* left;
    Node* right;
    Node* next;

    Node() {}

    Node(int _val, Node* _left, Node* _right, Node* _next) {
        val = _val;
        left = _left;
        right = _right;
        next = _next;
    }
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

	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        return this->buildTreeWithInAndPostOrder(inorder.begin(), inorder.end(), postorder.begin(), postorder.end());
    }

	TreeNode *buildTreeWithInAndPostOrder(		vector<int>::iterator inorder_begin, vector<int>::iterator inorder_end,
		vector<int>::iterator postorder_begin, vector<int>::iterator postorder_end){
		TreeNode *node = NULL;

		if (postorder_begin != postorder_end){
			node = new TreeNode(*(postorder_end-1));
			vector<int>::iterator it_inorder = inorder_begin, it_postorder = postorder_begin;
			for (; it_inorder != inorder_end; it_inorder++, it_postorder++){
				if (*it_inorder == *(postorder_end-1)){
					break;
				}
			}
			node->left = buildTreeWithInAndPostOrder(inorder_begin, it_inorder, postorder_begin, it_postorder);
			node->right = buildTreeWithInAndPostOrder(it_inorder+1, inorder_end, it_postorder, postorder_end-1);
		}
		
		return node;
	}

	TreeNode* buildTree_1(vector<int>& preorder, vector<int>& inorder) {
        return this->buildTreeWithPreAndInOrder(preorder.begin(), preorder.end(), inorder.begin(), inorder.end());
    }

	TreeNode *buildTreeWithPreAndInOrder(vector<int>::iterator preorder_begin, vector<int>::iterator preorder_end,
		vector<int>::iterator inorder_begin, vector<int>::iterator inorder_end){
		TreeNode *node = NULL;

		if (preorder_begin != preorder_end){
			node = new TreeNode(*preorder_begin);
			vector<int>::iterator it_inorder = inorder_begin, it_preorder = preorder_begin+1;
			for (; it_inorder != inorder_end; it_inorder++, it_preorder++){
				if (*it_inorder == *preorder_begin){
					break;
				}
			}
			node->left = buildTreeWithPreAndInOrder(preorder_begin+1, it_preorder, inorder_begin, it_inorder);
			node->right = buildTreeWithPreAndInOrder(it_preorder, preorder_end, it_inorder+1, inorder_end);
		}
		
		return node;
	}

	Node* connect(Node* root) {
        if (root){
			if (root->left){
				root->left->next = root->right;
				if (root->next){
					root->right->next = root->next->left;
				}
				this->connect(root->left);
				this->connect(root->right);
			}
        }
		return root;
    }

	Node* connect1(Node* root) {
        if (root){
			if (root->left && root->right){
				root->left->next = root->right;
				Node *next = root->next;
				while (next){
					if (next->left){
						root->right->next = next->left;
						break;
					}
					else if (next->right){
						root->right->next = next->right;
						break;
					}
					next = next->next;
				}
				// We must recurse on right child first.
				this->connect(root->right);
				this->connect(root->left);
			}
			else if (root->left){
				Node *next = root->next;
				while (next){
					if (next->left){
						root->left->next = next->left;
						break;
					}
					else if (next->right){
						root->left->next = next->right;
						break;
					}
					next = next->next;
				}
				this->connect(root->left);
			}
			else if (root->right){
				Node *next = root->next;
				while (next){
					if (next->left){
						root->right->next = next->left;
						break;
					}
					else if (next->right){
						root->right->next = next->right;
						break;
					}
					next = next->next;
				}
				this->connect(root->right);
			}
        }
		return root;
    }

	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        TreeNode *node = root;
		if (!root){
			return NULL;
		}
		if (root->val == p->val){
			return root;
		}
		if (root->val == q->val){
			return root;
		}
		TreeNode *left = this->lowestCommonAncestor(root->left, p, q);
		TreeNode *right = this->lowestCommonAncestor(root->right, p, q);
		if (left && right){
			return root;
		}
		else if (left){
			return left;
		}
		else if (right){
			return right;
		}
		else {
			return NULL;
		}
    }

	// Encodes a tree to a single string.
    string serialize(TreeNode* root) {
        stringstream output, ss;
		output<<"[";
		deque<TreeNode *> nodes;
		if (root){
			output<<root->val;
			nodes.push_back(root->left);
			nodes.push_back(root->right);
			while (!nodes.empty()){
				TreeNode *node = nodes.front();
				nodes.pop_front();
				if (node){
					output<<ss.str();
					ss.str("");
					output<<","<<node->val;
					nodes.push_back(node->left);
					nodes.push_back(node->right);
				}
				else {
					ss<<",null";
				}
			}
		}
		output<<"]";
		return output.str();
    }

    // Decodes your encoded data to tree.
    TreeNode* deserialize(string data) {
		data.back() = ',';
    	if (data.length() == 2){
			return NULL;
    	}
		data = data.substr(1);
		size_t pos = data.find(",");
		TreeNode *root = new TreeNode(stoi(data.substr(0, pos)));
		deque<TreeNode *> nodes;
		TreeNode *node = root;
		int flag = 0;
		while (true){
			data = data.substr(pos+1);
			pos = data.find(",");
			if (pos == string::npos){
				break;
			}
			if (!node){
				node = nodes.front();
				nodes.pop_front();
			}
			TreeNode *new_node = NULL;
			if (data.substr(0, pos).compare("null")){
				new_node = new TreeNode(stoi(data.substr(0, pos)));
				nodes.push_back(new_node);
			}
			if (flag == 0){
				node->left = new_node;
				flag = 1;
			}
			else {
				node->right = new_node;
				flag = 0;
				node = NULL;
			}
		}
        return root;
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

	cout<<"Test serialize:"<<endl;
	TreeNode tree[5](0);
	tree[0].val = 1;
	tree[1].val = 2;
	tree[2].val = 3;
	tree[3].val = 4;
	tree[4].val = 5;
	tree[0].left = &tree[1];
	tree[0].right = &tree[2];
	tree[2].left = &tree[3];
	tree[2].right = &tree[4];
	cout<<solution.serialize(tree)<<endl;
	cout<<solution.serialize(NULL)<<endl;
	cout<<solution.serialize(solution.deserialize("[1,2,3,null,null,4,5]"))<<endl;
	cout<<solution.serialize(solution.deserialize("[]"))<<endl;
	
	return 0;
}


