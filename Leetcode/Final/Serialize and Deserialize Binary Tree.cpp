/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Codec {
public:
    string serialize(TreeNode* root) {
        if (!root) {
            return "";
        }
        string output;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            TreeNode* node = q.front();
            q.pop();
            if (node) {
                output.append(to_string(node->val));
                output.push_back(',');
                q.push(node->left);
                q.push(node->right);
            } else {
                output.append("#,");
            }
        }
        if (!output.empty()) {
            output.pop_back();
        }
        return output;
    }

    TreeNode* deserialize(string data) {
        if (data.empty()) {
            return nullptr;
        }
        vector<string> tokens;
        string token;
        for (char c : data) {
            if (c == ',') {
                tokens.push_back(token);
                token.clear();
            } else {
                token.push_back(c);
            }
        }
        tokens.push_back(token);
        queue<TreeNode*> q;
        TreeNode* root = new TreeNode(stoi(tokens[0]));
        q.push(root);
        int index = 1;
        while (!q.empty() && index < static_cast<int>(tokens.size())) {
            TreeNode* node = q.front();
            q.pop();
            if (tokens[index] != "#") {
                node->left = new TreeNode(stoi(tokens[index]));
                q.push(node->left);
            }
            ++index;
            if (index >= static_cast<int>(tokens.size())) {
                break;
            }
            if (tokens[index] != "#") {
                node->right = new TreeNode(stoi(tokens[index]));
                q.push(node->right);
            }
            ++index;
        }
        return root;
    }
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode* ans = deser.deserialize(ser.serialize(root));

