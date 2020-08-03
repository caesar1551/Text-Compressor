#include <bits/stdc++.h>
using namespace std;
class TreeNode{
public:
	TreeNode* left;
	TreeNode* right;
	string text;
	TreeNode(){
		left = right = NULL;
	}
};
TreeNode* HuffmanConstruct(const string& mapped_values){
	/*
		"\n" -> "" + "" in two new lines
		"\t" -> "	" (tab)
		" " -> " " (space)
	*/
	TreeNode *root = new TreeNode();
	TreeNode *temp = root;
	istringstream f(mapped_values);
	string bit;
	string char_line;
	char character;
    while (getline(f, bit) && getline(f, char_line)){
		if(char_line == ""){
			getline(f, char_line);
			char_line = "\n";
		}
		character = char_line[0];
		for(unsigned int i = 0; i < bit.size(); i++){
			if(bit[i] == '0'){
				if(temp->left == NULL){
					TreeNode *new_left = new TreeNode();
					temp->left = new_left;
				}
				temp = temp->left;
			}
			else if(bit[i] == '1'){
				if(temp->right == NULL){
					TreeNode *new_right = new TreeNode();
					temp->right = new_right;
				}
				temp = temp->right;
			}
			temp->text.push_back(character);
		}
		temp = root;
	}
	return root;
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
string int_to_byte(unsigned int num){
	string ans = "00000000";
	for(int i = 7; i >= 0; i--){
		ans[i] = (num%2) + '0';
		num = num >> 1;
	}
	return ans;
}
string decoder_helper(const string& str) {
	string final_ans = "";
	for(unsigned int i = 0; i < str.size(); i++) {
		unsigned int x = str[i];
		final_ans += int_to_byte(x);
	}
	return final_ans;
}
int byte_to_int(const string& byte) {
    int sum = 0;
    for(unsigned int i=0; i<8; i++) {
		sum = sum << 1;
		sum += (byte[i]  - '0');
	}
    return sum;
}
string remove_unwanted(string bits) {
	string prefix_byte = bits.substr(0,8);
	int suffix_used = byte_to_int(prefix_byte);
	while(suffix_used%8 != 0) {
		bits.pop_back();
		suffix_used++;
	}
	return bits.substr(8);
}

string decodeHuffmanData(const string& real_string, TreeNode* root){
	string ans;
	TreeNode* temp = root;
	for(int i = 0; i <= real_string.size(); i++){
		if(temp->left == NULL && temp->right == NULL){
			ans.push_back(temp->text[0]);
			temp = root;
			i--;
		}
		else if(real_string[i] == '0'){
			temp = temp->left;
		}
		else if(real_string[i] == '1'){
			temp = temp->right;
		}
	}
	return ans;
}
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
int main(int argc, char** argv){
	if(argc < 4){
		return -1;
	}
	string to_decode = read_file(argv[1]);
	if(to_decode == ""){
		return -1;
	} 
	string decoded = decoder_helper(to_decode);
	string real_string = remove_unwanted(decoded);
	string mapped_values = read_file(argv[2]);
	if(mapped_values == ""){
		return -1;
	}
	TreeNode* root = HuffmanConstruct(mapped_values);
	string final_ans = decodeHuffmanData(real_string,root);
	save_text_to_file(final_ans,argv[3]);
	deleteTree(root);
	return 0;
}