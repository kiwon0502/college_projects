#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <vector>
using namespace std;

struct dentry {
	string name;									// dentry name
	int d_num = 0;									// number of directories
	int i_num = 0;									// number of inodes

	struct dentry *parent;							// pointer of parent dentry
	struct dentry *d_dentry[64];					// pointer of children dentries
	struct inode *d_inode[128];						// pointer of inodes
};

struct inode {
	int id;											// inode ID (0~127)
	string name;									// inode name
	int size;										// file size

	int direct_block;
	int single_indirect;
	int double_indirect;
};

// global variables
const unsigned int ID = 2015147531;
struct dentry root;
struct dentry* curr_dir;
int inode_table[128] = {0,};
int block_size = 973;
int db, si, di;
string root_path = "/";
string current_path = "/";

// fucntion prototype
int find_elements_num(string str, int len);
int get_instruction(string str);
int check_inode_id();
int find_block_size(unsigned int size);
void print_remain();
void LS();
void CD(string str);
void MKDIR(string* str, int num);
void RMDIR(string* str, int num);
void RM(dentry* dentry);
void MKFILE(string str, int size);
void RMFILE(string* str, int num);
void INODE(string str);

int main() {
	string input;
	int input_len, element_num, inst;

	// initialize root directory
	root.parent = &root;

	// object to point current directory
	// set to root initially
	curr_dir = &root;

	while (true) {
		cout<<ID<<":"<<current_path<<"$ ";
		getline(cin, input);										// get instruction inputs
		if (input == "exit") break;
		input_len = input.length();									// input length
		element_num = find_elements_num(input, input_len);
		string* elements = new string[element_num];
		inst = get_instruction(input);
		size_t prev, curr;
		prev = input.find(' ');
		input = input.substr(prev+1);
		for (int i=0; i<element_num; i++) {
			prev=0;
			curr = input.find(' ');
			string substring = input.substr(prev, curr-prev);
			elements[i] = substring;
			input = input.substr(curr+1);
		}												// store elements in the string array
		switch (inst) {
			case 0:
				if (element_num!=0) {
					cout<<"error"<<endl;
					break;
				}
				LS(); 
				break;
			case 1:
				if (element_num!=1) {
					cout<<"error"<<endl;
					break;
				}
				CD(elements[0]);
				break;
			case 2:
				if (element_num==0) {
					cout<<"error"<<endl;
					break;
				}
				MKDIR(elements, element_num);
				break;
			case 3:
				if (element_num==0) {
					cout<<"error"<<endl;
					break;
				}
				RMDIR(elements, element_num);
				print_remain();
				break;
			case 4:
				if (element_num==0) {
					cout<<"error"<<endl;
					break;
				}
				// if the file size is not int
				else if (atoi(elements[1].c_str()) == 0) {
					cout<<"error"<<endl;
					break;
				}
				else if (atoi(elements[1].c_str()) < 0) {
					cout<<"error"<<endl;
					break;
				}
				MKFILE(elements[0], atoi(elements[1].c_str()));
				break;
			case 5:
				if (element_num==0) {
					cout<<"error"<<endl;
					break;
				}
				RMFILE(elements, element_num);
				break;
			case 6:
				if (element_num==0) {
					cout<<"error"<<endl;
					break;
				}
				INODE(elements[0]);
				break;
			case -1:
				cout<<"error"<<endl;
				break;
		}
	}
	return 0;
}
// Getting inputs
// -----------------------------------------------------------------
int find_elements_num(string str, int len) {			// len = str.len()
	int num = 0;
	for (int i=0; i<len; i++) {
		if(str[i] == ' ') num++;
	}
	return num;
}
int get_instruction(string str) {
	int num;
	size_t prev=0, curr;
	curr = str.find(' ');
	string substring = str.substr(prev, curr-prev);
	if (substring == "ls") num = 0;
	else if (substring == "cd") num = 1;
	else if (substring == "mkdir") num = 2;
	else if (substring == "rmdir") num = 3;
	else if (substring == "mkfile") num = 4;
	else if (substring == "rmfile") num = 5;
	else if (substring == "inode") num = 6;
	else num = -1;
	return num;
}
int check_inode_id() {
	for (int i=0; i<128; i++) {
		if (inode_table[i] == 0) return i;
	}
	return -1;
}
int find_block_size(unsigned int size) {
	// calculate the number of blocks needed
	int direct_b = 0, single_id = 0, double_id = 0;
	int num = (size / 1024);
	if (size%1024 != 0) num++;
	if (num < 13) {
		direct_b = num;
	}
	else {
		direct_b = 12;
		single_id = num-12;
		single_id++;										// for pointer block
		if (single_id > 257) {
			double_id = single_id - 257;
			single_id = 257;
			double_id+=2;									// for pointer block 1, block2
			if (double_id > 258) double_id++;				// for pointer block 3
		}
	}
	db = direct_b; si = single_id; di = double_id;
	return (direct_b + single_id + double_id);
}
void print_remain() {
	cout<<"Now you have ..."<<endl;
	cout<<block_size<<" / 973 (blocks)"<<endl;
}
// Instructions
// ------------------------------------------------------------------
void LS() {
	if (curr_dir->d_num!=0) {
		for (int i=0; i<curr_dir->d_num; i++) {
			if (curr_dir->d_dentry[i] != NULL) {
				cout<<curr_dir->d_dentry[i]->name<<" ";
			}
		}
	}
	if (curr_dir->i_num!=0) {
		for (int i=0; i<128; i++) {
			if (inode_table[i] == 1) {
				for (int j=0; j<curr_dir->i_num; j++) {
					if (curr_dir->d_inode[j] != NULL && curr_dir->d_inode[j]->id == i) {
						cout<<curr_dir->d_inode[j]->name<<" ";
					}
				}
			}
		}
	}
	cout<<endl;
}
void CD(string str) {
	int len = str.length();
	int num = 0;
	bool first_start = false;
	vector<string> directories;															// get into these directories
	// check the number of '/'
	for (int i=0; i<len; i++) {
		if(str[i] == '/') num++;
	}
	// slice it by '/'
	//if (str[0] == '/') directories.push_back("Root"); first_start = true;
	size_t prev=0, curr;
	for (int i=0; i<num; i++) {
		curr = str.find('/');
		string substring = str.substr(prev, curr-prev);
		int index = curr-prev+1;
		prev = 0;
		str = str.substr(index);
		directories.push_back(substring);
	}
	if (str != "") directories.push_back(str);
	int go = 0; bool flag = true;
	bool valid =false;
	while (go != directories.size()) {
		if (directories[0] == "" && flag) {
			curr_dir = &root; go++; flag = false;
			current_path = root_path;
			valid = true;
		}
		else if (directories[go] == "..") {
			int curr_length = curr_dir->name.length();
			int path_length = current_path.length();
			if (curr_dir->parent->name == "") current_path = root_path;
			else current_path = current_path.substr(0,path_length-curr_length-1);
			curr_dir = curr_dir->parent; go++;
			valid = true;
		}
		else if (directories[go] == ".") {
			curr_dir = curr_dir; go++;
		}
		for (int i=0; i<curr_dir->d_num; i++) {
			if (curr_dir->d_dentry[i]->name == directories[go]) {
				if (current_path == root_path) current_path = current_path + directories[go];
				else current_path = current_path + "/" + directories[go];
				curr_dir = curr_dir->d_dentry[i];
				go++;
				valid = true;
			}
		}
		if (!valid) {
			cout<<"error"<<endl;
			return;
		}
	}
}
void MKDIR(string* str, int num) {
	for (int i=0; i<num; i++) {
		bool valid = true;
		// if the directory has the same name, do not make it
		for (int j=0; j<curr_dir->d_num; j++) {
			if (curr_dir->d_dentry[j]->name == str[i]) {
				cout<<"error"<<endl;
				valid = false;
				return;
			}
		}
		// no same name of directories
		if (valid) {
			dentry* new_d = new dentry;
			new_d->name = str[i];
			new_d->parent = curr_dir;
			curr_dir->d_dentry[curr_dir->d_num] = new_d;
			curr_dir->d_num++;
		}
	}
}
void RMDIR(string* str, int num) {
	// check if the file is exisitng
	for (int i=0; i<num; i++) {
		bool valid = false;
		for (int j=0; j<curr_dir->d_num; j++) {
			if (curr_dir->d_dentry[j]->name == str[i]) {
				valid = true;
			}
		}
		if (!valid) {
			cout<<"error"<<endl;
			return;
		}
	}
	// remove the directories
	for (int i=0; i<num; i++) {
		for (int j=0; j<curr_dir->d_num; j++) {
			if (curr_dir->d_dentry[j]->name == str[i]) {
				RM(curr_dir->d_dentry[j]);
				curr_dir->d_dentry[j] = NULL;
				for (int k=j; k<(curr_dir->d_num-1); k++) {
					curr_dir->d_dentry[k] = curr_dir->d_dentry[k+1];
				}
				curr_dir->d_num--;
			}
		}
	}
}
void RM(dentry* dentry) {
	// remove files
	for (int i=0; i<dentry->i_num; i++) {
		inode_table[dentry->d_inode[i]->id] = 0;
		int b_size = find_block_size(dentry->d_inode[i]->size);
		block_size += b_size;
		dentry->d_inode[i] = NULL;
	}
	dentry->i_num = 0;
	// remove directories
	for (int i=0; i<dentry->d_num; i++) {
		RM(dentry->d_dentry[i]);
		dentry->d_dentry[i] = NULL;	
	}
	dentry->d_num = 0;
}

void MKFILE(string str, int size) {
	// if the directory has the same name of file, do not make it
	for (int i=0; i<curr_dir->i_num; i++) {
		if (curr_dir->d_inode[i]->name == str) {
			cout<<"error"<<endl;
			return;
		}
	}
	// calculate the number of blocks needed
	int total = find_block_size(size);
	// check if the remaining memory is big enough
	if (total > block_size) {
		cout<<"error"<<endl;
		return;
	}
	// no same name of files and enough blocks
	// new inode
	inode* new_i = new inode;
	int id = check_inode_id();
	if (id != -1) {
		new_i->id = id;
		inode_table[id] = 1;
	}
	new_i->name = str;
	new_i->size = size;
	new_i->direct_block = db;
	new_i->single_indirect = si;
	new_i->double_indirect = di;
	// reduce block size
	block_size -= total;
	curr_dir->d_inode[curr_dir->i_num] = new_i;
	curr_dir->i_num++;
	print_remain();
}
void RMFILE(string* str, int num) {
	// check if the file is exisitng
	for (int i=0; i<num; i++) {
		bool valid = false;
		for (int j=0; j<curr_dir->i_num; j++) {
			if (curr_dir->d_inode[j]->name == str[i]) {
				valid = true;
			}
		}
		if (!valid) {
			cout<<"error"<<endl;
			return;
		}
	}
	// remove the files
	for (int i=0; i<num; i++) {
		for (int j=0; j<curr_dir->i_num; j++) {
			if (curr_dir->d_inode[j]->name == str[i]) {
				inode_table[curr_dir->d_inode[j]->id] = 0;
				int b_size = find_block_size(curr_dir->d_inode[j]->size);
				block_size += b_size;
				for (int k=j; k<(curr_dir->i_num-1); k++) {
					curr_dir->d_inode[k] = curr_dir->d_inode[k+1];
				}
				curr_dir->i_num--;
			}
		}
	}
	print_remain();
}
void INODE(string str) {
	// find the inode
	int index;
	bool valid = false;
	for (int i=0; i<curr_dir->i_num; i++) {
		if (curr_dir->d_inode[i]->name == str) {
			index = i;
			valid = true;
		}
	}
	if (!valid) {
		cout<<"error"<<endl;
		return;
	}
	cout<<"ID: "<<curr_dir->d_inode[index]->id<<endl;
	cout<<"Name: "<<curr_dir->d_inode[index]->name<<endl;
	cout<<"Size: "<<curr_dir->d_inode[index]->size<<" (bytes)"<<endl;
	cout<<"Direct blocks: "<<curr_dir->d_inode[index]->direct_block<<endl;
	cout<<"Single indirect blocks: "<<curr_dir->d_inode[index]->single_indirect<<endl;
	cout<<"Double indirect blocks: "<<curr_dir->d_inode[index]->double_indirect<<endl;
}