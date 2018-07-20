#include <iostream>
#include <stdio.h>
#include <cstdlib>
#include <string>
#include <vector>
#include <ctype.h>
#include<stack>

using namespace std;

struct node
{
	char info;
	struct node *link;
}*Stack;

class StackList {
public:
	node * push(node *, char);
	node * pop(node *);
	char top(node *);
	void traverse(node *);
	StackList() {
		Stack = NULL;
	}
};

node *StackList::push(node *Stack, char item) {
	node *tmp;
	tmp = new (struct node);
	tmp->info = item;
	tmp->link = Stack;
	Stack = tmp;
	return Stack;
}

node * StackList::pop(node *Stack) {
	node *tmp;
	if (Stack == NULL) {
		cout << "NULL\n";
	}
	else {
		tmp = Stack;
		Stack = Stack->link;
		free(tmp);
	}
	return Stack;
}
void StackList::traverse(node *Stack) {
	node *ptr;
	ptr = Stack;
	if (Stack == NULL) {
		cout << "NULL\n";
	}
	else {
		cout << "Content: ";
		while (ptr != NULL) {
			cout << ptr->info << " - ";
			ptr = ptr->link;
		}
	}
}
char StackList::top(node *Stack) {
	return Stack->info;
}


bool isOperator(char x) {
	return x == '+' || x == '-' || x == '*' || x == '/';
}

int getPriority(char x) {
	if (x == '+' || x == '-') return 1;
	if (x == '*' || x == '/') return 2;
	return 0;
}
bool isOperand(char x) {
	if ((x > 64 && x<91) || (x>96 && x < 123) || (x>47 && x < 58)) return true;
	return false;
}

string toPostfix(vector<char> A) {
	StackList S;
	string result = "";
	for (int i = 0; i < A.size(); i++) {
		if (A[i] == '(') {
			Stack = S.push(Stack, A[i]); //them vao stack
		}
		// toan hang
		else if (isOperand(A[i])) {
			result += A[i];
		}
		// neu la toan tu thi xet do uu tien, cai nao uu tien thi lay qua bo vao result xong cai hien tai cho vao stack
		else if (isOperator(A[i])) {
			//xet do uu tien de them vao result
			// vi du
			//	a + 2 * 3
			// a23*+
			while (Stack != NULL && getPriority( S.top(Stack) ) >= getPriority(A[i]) ) {
				result += S.top(Stack);
				Stack = S.pop(Stack);
			}
			Stack = S.push(Stack, A[i]);
		}
		else if (A[i] == ')') {
			while (Stack != NULL && S.top(Stack) != '(') {
				result += S.top(Stack);
				Stack = S.pop(Stack);
			}
			Stack = S.pop(Stack);
		}
	}

	node *ptr;
	ptr = Stack;
	while (ptr != NULL) {
		result += ptr->info;
		ptr = ptr->link;
	}

	return result;
}

// make list from string
void makeList(vector<char> &A, string content) {
	for (int i = 0;i < content.size();i++) {
		if (!isspace(content[i])) {
			A.push_back(content[i]);
		}
	}
}

// link list
struct Node
{
	char data;
	Node *Left;
	Node *Right;
	Node() {
		this->Left = this->Right = NULL;
	}
};



struct CayNhiPhan
{
	Node *Root;
	CayNhiPhan() {
		this->Root = NULL;
	}
};
void showLNR(Node *&R) {
	if (R != NULL) {
		showLNR(R->Left);
		cout << R->data << " ";
		showLNR(R->Right);
	}
}
void showLRN(Node *&R) {
	if (R != NULL) {
		showLRN(R->Left);
		showLRN(R->Right);
		cout << R->data << " ";
	}
}
void showNLR(Node *&R) {
	if (R != NULL) {
		cout << R->data << " ";
		showNLR(R->Left);
		showNLR(R->Right);
	}
}

void themvaoCay(Node *&R, vector<char> input) {
	string str = toPostfix(input);
	stack<Node*> stackNode;
	for (int i = 0; i < str.size();i++) {
		//toan hạng thi tao node chua toan hang do va cho vao stack
		if (isOperand(str[i])) {
			Node*p = new Node;
			p->data = str[i];
			stackNode.push(p);
		}
		else if (isOperator(str[i])) {
			Node*p = new Node;
			p->data = str[i];
			p->Right = stackNode.top();
			stackNode.pop();
			p->Left = stackNode.top();
			stackNode.pop();
			stackNode.push(p);
		}
	}
	R = stackNode.top();
}
int main(){
	CayNhiPhan cnp;
	vector <char> bieuThuc;
	cout << "Nhap vao bieu thuc cach nhau boi space, # ket thuc:\n";
	string a = "";
	getline(cin, a);
	makeList(bieuThuc, a);
	themvaoCay(cnp.Root, bieuThuc);
	cout << toPostfix(bieuThuc);
	cout << "\n\nDuyet NLR: ";
	showNLR(cnp.Root);
	cout << "\nDuyet LRN: ";
	showLRN(cnp.Root);
	cout << "\nDuyet LNR: ";
	showLNR(cnp.Root);
	system("pause");
	return 0;
}
