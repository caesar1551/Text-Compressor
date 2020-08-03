#include <bits/stdc++.h>
using namespace std;
class TreeNode{
public:
	TreeNode* left;
	TreeNode* right;
	int freq;
	string text;
	TreeNode(string t){
		left = right = NULL;
		freq = 1;
		text = t;
	}
};
struct cmp{
	bool operator()(const TreeNode*  a, const TreeNode*  b){
		return a->freq > b->freq;
	}
};
void deleteTree(TreeNode* root){
	if(root->left == NULL && root->right == NULL){
		delete(root);
	}
	if(root->left){
		deleteTree(root->left);
	}
	if(root->right){
		deleteTree(root->right);
	}
}
string int_to_byte(unsigned int num){
	string ans = "00000000";
	for(int i = 7; i >= 0; i--){
		ans[i] = (num%2) + '0';
		num = num >> 1;
	}
	return ans;
}
void get_code(TreeNode* root, unordered_map<string,string>& dict, string s){
	if(root->left == NULL && root->right == NULL){
		dict[root->text] = s;
		return;
	}
	if(root->left){
		get_code(root->left,dict,s+"0");
	}
	if(root->right){
		get_code(root->right,dict,s+"1");
	}
	return;
}
string read_file(const string& file_name){
	string text;
	ifstream input_stream(file_name, ios::in | ios::binary);
	if(!input_stream){
		return "";
	}
	do{
		int c= input_stream.get();
		if (c==EOF){
			break;
		}
		text += (char)c;
	}
	while(!input_stream.fail());
	return text;
}
void save_text_to_file(const string& text, const string& file_name){
	ofstream OutFile;
	OutFile.open(file_name, ios::out | ios::binary);
	OutFile << text;
	OutFile.close();
}
string encode_bits(string &bits){
	string final_string;
	unsigned int sum = 0;
	for(unsigned int i=0;i<bits.size();i++) {
		sum = sum << 1;
		sum += (bits[i]  - '0');
		if((i+1)%8==0) {
			final_string += (unsigned char)sum;
			sum = 0;
		}
	}
	return final_string;
}
string marker(unordered_map<string,string>& dict) {
	string encode_help_string;
	for (auto x : dict){
		encode_help_string += x.second + '\n' + x.first + '\n';
	}
	return encode_help_string;
}
int main(int argc, char **argv){
	if(argc < 4){
		return -1;
	}
	string s = read_file(argv[1]);
	if(s == ""){
		return -1;
	}
	unordered_map<char,TreeNode*> m;
	for(auto i:s){
		if(m.count(i) > 0){
			m[i]->freq++;
		}
		else{
			string x(1,i);
			TreeNode* temp = new TreeNode(x);
			m[i] = temp;
		}
	}
	priority_queue<TreeNode*, vector<TreeNode*>, cmp> q;
	for(auto i:m){
		q.push(i.second);
	}
	while(q.size() > 1){
		TreeNode* temp1 = q.top();
		q.pop();
		TreeNode* temp2 = q.top();
		q.pop();
		TreeNode* temp = new TreeNode(s);
		temp->left = temp1;
		temp->right = temp2;
		temp->freq = temp1->freq + temp2->freq;
		temp->text = temp1->text + temp2->text;
		q.push(temp);
	}
	string codes= "";
	unordered_map<string,string> dict;
	get_code(q.top(),dict,codes);
	string final_ans = "";
	for(int i = 0; i < s.size(); i++){
		string t(1,s[i]);
		final_ans = final_ans + dict[t];
	}
	int add_zero = 8 - (final_ans.size()%8);
	for(int i = 0; i < add_zero; i++){
		final_ans = final_ans + "0";
	}
	int prefix = 8 - add_zero;
	final_ans = int_to_byte(prefix) + final_ans;
	string encoded_string = encode_bits(final_ans);
	save_text_to_file(encoded_string, argv[2]);
	string dictionary = marker(dict);
	save_text_to_file(dictionary, argv[3]);
	deleteTree(q.top());
	return 0;
}
