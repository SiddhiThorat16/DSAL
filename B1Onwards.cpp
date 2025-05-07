/*
================================================================================================================================================================
B1) Beginning with an empty binary search tree, Construct binary search tree by inserting the values in the order given. After constructing a binary tree -
                -> Insert new node
                -> Find number of nodes in longest path.
                -> Minimum data value found in the tree
                -> Change a tree so that the roles of the left and right pointers are swapped at every node
                -> Search a value
                
                
Sample Output : 10, 8, 2, 9, 15
================================================================================================================================================================
*/

#include<iostream>
using namespace std;
struct node
{
	int data;
	node *L;
	node *R;
};
node *root,*temp;
int count,key;

class bst
{
public:
	void create();
	void insert(node*,node*);
	void disin(node*);
	void dispre(node*);
	void dispost(node*);
	void search(node*,int);
	int height(node*);
	void mirror(node*);
	void min(node*);
	bst()
	{
		root=NULL;
		count=0;
	}
};

void bst::create()
{
	char ans;
	do
	{
		temp=new node;
		cout<<"Enter the data : ";
		cin>>temp->data;
		temp->L=NULL;
		temp->R=NULL;
		if(root==NULL)
		{
			root=temp;
		}
		else
			insert(root,temp);
		cout<<"Do you want to insert more value : "<<endl;
		cin>>ans;
		count++;
		cout<<endl;
	} while(ans=='y');
	cout<<"The Total no.of nodes are:"<<count;
}
void bst::insert(node *root,node* temp)
{
	if(temp->data>root->data)
	{
		if(root->R==NULL)
		{
			root->R=temp;
		}
		else
			insert(root->R,temp);
	}
	else
	{
		if(root->L==NULL)
		{
			root->L=temp;
		}
		else
			insert(root->L,temp);
	}
}

void bst::disin(node *root)
{
	if(root!=NULL)
	{
		disin(root->L);
		cout<<root->data<<"\t";
		disin(root->R);
		count++;
	}
}

void bst::dispre(node *root)
{
	if(root!=NULL)
	{
		cout<<root->data<<"\t";
		dispre(root->L);
		dispre(root->R);
	}
}

void bst::dispost(node *root)
{
	if(root!=NULL)
	{
		dispost(root->L);
		dispost(root->R);
		cout<<root->data<<"\t";
	}
}

void bst::search(node *root, int key)
{
    cout << "\nEnter your key: ";
    cin >> key;

    node* temp = root;
    bool found = false;

    while (temp != NULL)
    {
        if (key == temp->data)
        {
            cout << "           KEY FOUND           \n";
            found = true;
            break;
        }
        else if (key < temp->data)
        {
            temp = temp->L;
        }
        else
        {
            temp = temp->R;
        }
    }

    if (!found)
    {
        cout << "           KEY NOT FOUND           \n";
    }
}

int bst::height(node *root)
{
	int hl,hr;
	if(root==NULL)
	{
		return 0;

	}
	else if(root->L==NULL && root->R==NULL)
	{
		return 1;
	}
	cout<<endl;
	hr=1+height(root->R);
	hl=1+height(root->L);
	if(hr>hl)
	{
		return(hr);
	}
	else
	{
		return(hl);
	}
}

void bst::min(node *root)
{
	temp=root;
	cout<<endl;
	while(temp->L!=NULL)
	{
		temp=temp->L;
	}
	cout<<temp->data;
}

void bst::mirror(node *root)
{
	temp=root;
	if(root!=NULL)
	{
		mirror(root->L);
		mirror(root->R);
		temp=root->L;
		root->L=root->R;
		root->R=temp;
	}
}

int main()
{
	bst t;
	int ch;
	char ans;
	do
	{
		cout<<"\n1) Insert new node 2)number of nodes in longest path 3) minimum 4) mirror 5) search 6) inorder 7) preorder 8) postorder"<<endl;
		cin>>ch;
		switch(ch)
		{
		case 1:
			t.create();
			break;
		case 2:
			cout<<"\n Number of nodes in longest path:"<<t.height(root);
			break;
		case 3:
			cout<<"\nThe min element is:";
			t.min(root);
			break;
		case 4:
			t.mirror(root);
			cout<<"\nThe mirror of tree is: ";
			t.disin(root);
			break;
		case 5:
			t.search(root,key);
			break;
		case 6:
			cout<<"\n***************INORDER**************"<<endl;
			t.disin(root);
			break;
		case 7:
			cout<<"\n***************PREORDER**************"<<endl;
			t.dispre(root);
			break;
		case 8:
			cout<<"\n*******************POSTORDER**************"<<endl;
			t.dispost(root);
			break;
		}
		cout<<"\nDo you want to continue : ";
		cin>>ans;
	} while(ans=='y');
	return 0;
}



/*
========================================================================================
B2) For given expression eg. a-b*c-d/e+f construct & display expression tree

Sample Output 1 : (a+b)*c
Sample Output 2 : a-b*c-d/e+f
========================================================================================
*/

#include <iostream> 
#include <stack> 
using namespace std; 
struct Node {
    char data;
    Node* left;
    Node* right;
    Node(char val) {
    	data = val;
    	left = NULL;
    	right = NULL;
    }
};

int precedence(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

string infixToPostfix(string infix) {
	stack<char> s;
	string postfix = "";
	for (char ch : infix) {
		if (isalnum(ch)) postfix += ch;
		else if (ch == '(') s.push(ch);
		else if (ch == ')') {
			while (!s.empty() && s.top() != '(') {

				postfix += s.top();
				s.pop();
			}
			s.pop();
		}

		else {
			while (!s.empty() && precedence(ch) <= precedence(s.top())) {
				postfix += s.top();
				s.pop();
			}

			s.push(ch);
		}
	}

	while (!s.empty()) {
		postfix += s.top();
		s.pop();
	}
	return postfix;
}

Node* constructExpressionTree(string postfix) {
	stack<Node*> s;
	for (char ch : postfix) {

		Node* newNode = new Node(ch);
		if (isalnum(ch)) s.push(newNode);
		else {
			newNode->right = s.top();
			s.pop();
			newNode->left = s.top();
			s.pop();
			s.push(newNode);
		}
	}
	return s.top();
}

void displayTree(Node* root, int space = 0, int height = 5) {
	if (!root) return;
	space += height;
	displayTree(root->right, space);
	cout << endl;
	for (int i = height; i < space; i++) cout << " ";
	cout << "[" << root->data << "]" << endl;
	displayTree(root->left, space);
}

void inorderTraversal(Node* root) {
	stack<Node*> s;
	Node* current = root;

	cout << "Inorder Traversal: ";
	while (current || !s.empty()) {
		while (current) {
			s.push(current);
			current = current->left;
		}

		current = s.top();
		s.pop();
		cout << current->data << " ";
		current = current->right;
	}

	cout << endl;

}

void preorderTraversal(Node* root) {
	if (!root) return;
	stack<Node*> s;
	s.push(root);
	cout << "Preorder Traversal: ";
	while (!s.empty()) {
		Node* current = s.top();
		s.pop();

		cout << current->data << " ";

		if (current->right) s.push(current->right);
		if (current->left) s.push(current->left);
	}

	cout << endl;

}

void postorderTraversal(Node* root) {
	stack<Node*> s;
	Node* current = root;

	cout << "Postorder Traversal: ";
	while (current || !s.empty()) {
		if (current) {

			if (current->right) s.push(current->right);
			s.push(current);
			current = current->left;

		} else {

			current = s.top();
			s.pop();

			if (!s.empty() && current->right == s.top()) {
				s.pop();
				s.push(current);

				current = current->right;

			} else {

				cout << current->data << " ";
				current = NULL;
			}

		}

	}

	cout << endl;
}

int main() {
	int choice;
	string expression;
	Node* root = NULL;
	do {
		cout << "\n^^^^^^^^^^ MENU ^^^^^^^^^^\n";
		cout << "1. Convert Infix to Postfix\n";
		cout << "2. Construct and Display Expression Tree\n";
		cout << "3. Inorder Traversal\n";
		cout << "4. Preorder Traversal\n";
		cout << "5. Postorder Traversal\n";
		cout << "6. Exit\n";
		cout << "	\n";
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "Enter infix expression: ";
			cin >> expression;
			cout << "Postfix Expression: " << infixToPostfix(expression) << endl;
			break;
		case 2:

			cout << "Enter infix expression: ";
			cin >> expression;
			root = constructExpressionTree(infixToPostfix(expression));
			cout << "Expression Tree:\n";
			displayTree(root);
			break;
		case 3:

			if (root) inorderTraversal(root);

			else cout << "Tree not constructed." << endl;

			break;
		case 4:
			if (root) preorderTraversal(root);

			else cout << "Tree not constructed." << endl;
			break;
		case 5:

			if (root) postorderTraversal(root);

			else cout << "Tree not constructed." << endl;
			break;
		}

	} while (choice != 6);
	return 0;
}


/*
=======================================================================================================================================
B2) For given expression eg. a-b*c-d/e+f construct inorder sequence and traverse it using postorder traversal(non recursive).

Sample Output : a-b*c-d/e+f
=======================================================================================================================================
*/

#include <iostream>
#include <stack>
using namespace std;

struct Node {
	char data;
	Node* left;
	Node* right;
	Node(char val) {
		data = val;
		left = NULL;
		right = NULL;
	}
};

int precedence(char op) {
	if (op == '+' || op == '-') return 1;
	if (op == '*' || op == '/') return 2;
	return 0;
}

bool isOperand(char ch) {
	return (ch >= 'a' && ch <= 'z') ||
	       (ch >= 'A' && ch <= 'Z') ||
	       (ch >= '0' && ch <= '9');
}

string infixToPostfix(string infix) {
	stack<char> s;
	string postfix = "";
	for (char ch : infix) {
		if (isOperand(ch)) {
			postfix += ch;
		} else if (ch == '(') {
			s.push(ch);
		} else if (ch == ')') {
			while (!s.empty() && s.top() != '(') {
				postfix += s.top();
				s.pop();
			}
			if (!s.empty()) s.pop(); // remove '('
		} else {
			while (!s.empty() && precedence(ch) <= precedence(s.top())) {
				postfix += s.top();
				s.pop();
			}
			s.push(ch);
		}
	}
	while (!s.empty()) {
		postfix += s.top();
		s.pop();
	}
	return postfix;
}

Node* constructExpressionTree(string postfix) {
	stack<Node*> s;
	for (char ch : postfix) {
		Node* newNode = new Node(ch);
		if (isOperand(ch)) {
			s.push(newNode);
		} else {
			newNode->right = s.top();
			s.pop();
			newNode->left = s.top();
			s.pop();
			s.push(newNode);
		}
	}
	return s.top();
}

void inorderExpression(Node* root) {
	stack<Node*> s;
	Node* curr = root;
	cout << "Inorder Expression: ";
	while (curr || !s.empty()) {
		while (curr) {
			s.push(curr);
			curr = curr->left;
		}
		curr = s.top();
		s.pop();
		cout << curr->data << " ";
		curr = curr->right;
	}
	cout << endl;
}

void postorderTraversal(Node* root) {
	stack<Node*> s;
	Node* curr = root;
	cout << "Postorder Traversal (Non-Recursively) : ";
	while (curr || !s.empty()) {
		if (curr) {
			if (curr->right) s.push(curr->right);
			s.push(curr);
			curr = curr->left;
		} else {
			curr = s.top();
			s.pop();
			if (!s.empty() && curr->right == s.top()) {
				Node* rightChild = s.top();
				s.pop();
				s.push(curr);
				curr = rightChild;
			} else {
				cout << curr->data << " ";
				curr = nullptr;
			}
		}
	}
	cout << endl;
}

int main() {
	string infix;
	cout << "Enter infix expression : ";
	cin >> infix;

	string postfix = infixToPostfix(infix);
	Node* root = constructExpressionTree(postfix);

	inorderExpression(root);
	postorderTraversal(root);

	return 0;
}



/*
=======================================================================================================================================
B3) Convert given binary tree into threaded binary tree. Analyze time and space complexity of the algorithm.
=======================================================================================================================================
*/

#include <iostream>
using namespace std;
struct Node {
	int key;
	Node *left, *right;
	bool isThreaded;
};
Node *createThreaded(Node *root) {
	if (root == NULL)
		return NULL;
	if (root->left == NULL && root->right == NULL)
		return root;
	if (root->left != NULL) {
		Node* l = createThreaded(root->left);
		l->right = root;
		l->isThreaded = true;
	}
	if (root->right == NULL)
		return root;
	return createThreaded(root->right);
}
Node *leftMost(Node *root) {
	while (root != NULL && root->left != NULL)
		root = root->left;
	return root;
}
void inOrder(Node *root) {
	if (root == NULL) return;
	Node *cur = leftMost(root);
	while (cur != NULL) {
		cout << cur->key << " ";
		if (cur->isThreaded)
			cur = cur->right;
		else
			cur = leftMost(cur->right);
	}
}
Node *newNode(int key) {
	Node *temp = new Node;
	temp->left = temp->right = NULL;
	temp->key = key;
	return temp;
}
int main() {
	Node *root = newNode(1);
	root->left = newNode(2);
	root->right = newNode(3);
	root->left->left = newNode(4);
	root->left->right = newNode(5);
	root->right->left = newNode(6);
	root->right->right = newNode(7);
	createThreaded(root);
	cout << "Inorder traversal of created threaded tree is\n";
	inOrder(root);
	return 0;
}



/*
=================================================================================================================================================================
C1) There are flight paths between cities. If there is a flight between city A and city B then there is an edge between the cities. The cost of the edge can be the time that flight take to reach city B from A, or the amount of fuel used for the journey. Represent this as a graph. The node can be represented by airport name or name of the city. Use adjacency list representation of the graph or use adjacency matrix representation of the graph. Check whether the graph is connected or not.Justify the storage representation used.
=================================================================================================================================================================
*/

#include<iostream>
using namespace std;
struct node {
	string vertex;
	int time;
	node *next;
};
class adjmatlist {
	int m[5][5] = {
		{0, 90, 120, 60, 0},
		{90, 0, 150, 0, 300},
		{120, 150, 0, 110, 0},
		{60, 0, 110, 0, 250},
		{0, 300, 0, 250, 0}
	};
	string v[5] = {"Pune", "Delhi", "Chennai", "Mumbai", "Kashmir"};
	node *head[5];
	node *temp = NULL;

public:
	adjmatlist() {
		for (int i = 0; i < 5; i++) head[i] = NULL;
		adjlist();
	}
	void adjlist();
	void displaym();
	void displaya();
};
void adjmatlist::adjlist() {
	for (int i = 0; i < 5; i++) {
		node *p = new node;
		p->next = NULL;
		p->vertex = v[i];
		head[i] = p;
	}

	for (int i = 0; i < 5; i++) {
		for (int j = 0; j < 5; j++) {
			if (m[i][j] != 0) {
				node *p = new node;
				p->vertex = v[j];
				p->time = m[i][j];
				p->next = NULL;

				if (head[i]->next == NULL) {
					head[i]->next = p;
				} else {
					temp = head[i];
					while (temp->next != NULL) temp = temp->next;
					temp->next = p;
				}
			}
		}
	}
}
void adjmatlist::displaym() {
	cout << "\nAdjacency Matrix:";
	cout << "\n\t\t";
	for (int j = 0; j < 5; j++) cout << v[j] << "\t\t";

	for (int i = 0; i < 5; i++) {
		cout << "\n" << v[i] << "\t\t";
		for (int j = 0; j < 5; j++) cout << m[i][j] << "\t\t";
		cout << "\n";
	}
}
void adjmatlist::displaya() {
	cout << "\nAdjacency List:";
	for (int i = 0; i < 5; i++) {
		cout << "\n" << head[i]->vertex;
		temp = head[i]->next;
		while (temp != NULL) {
			cout << " -> " << temp->vertex << " [" << temp->time << " min]";
			temp = temp->next;
		}
	}
}
int main() {
	adjmatlist a;
	int choice;
	while (1) {
		cout << "\n\n1. Display Adjacency Matrix";
		cout << "\n2. Display Adjacency List";
		cout << "\n3. Exit";
		cout << "\nEnter your choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			a.displaym();
			break;
		case 2:
			a.displaya();
			break;
		case 3:
			return 0;
		default:
			cout << "\nInvalid choice";
		}
	}
}




/*
=================================================================================================================================================================
C2) You have a business with several offices; you want to lease phone lines to connect them up with each other; and the phone company charges different amounts of money to connect different pairs of cities. You want a set of lines that connects all your offices with a minimum total cost. Solve the problem by suggesting appropriate data structures.
=================================================================================================================================================================
*/

#include <iostream>
using namespace std;
class Tree {
	int cost[20][20], start, end, weight, i, j, numBranches, numConnections, visited[20];
public:
	void input();
	void display();
	void minimum();
};
void Tree::input() {
	cout << "Enter the number of branches: ";
	cin >> numBranches;
	for (i = 0; i < numBranches; i++) {
		visited[i] = 0;
		for (j = 0; j < numBranches; j++) {
			cost[i][j] = 999; // Initialize adjacency matrix with high values
		}
	}
	cout << "\nEnter the number of connections: ";
	cin >> numConnections;
	for (i = 0; i < numConnections; i++) {
		cout << "Enter the connected branches: ";
		cin >> start >> end;
		cout << "Enter the phone company charges for this connection: ";
		cin >> weight;
		cost[start - 1][end - 1] = cost[end - 1][start - 1] = weight;
	}
}
void Tree::display() {
	cout << "\nAdjacency Matrix:";
	for (i = 0; i < numBranches; i++) {
		cout << endl;
		for (j = 0; j < numBranches; j++) {
			cout << cost[i][j] << " ";
		}
		cout << endl;
	}
}
void Tree::minimum() {
	int src = 0, dest = 0, totalCost = 0, minCost;
	visited[1] = 1;
	for (int count = 0; count < (numBranches - 1); count++) {
		minCost = 999;
		for (i = 0; i < numBranches; i++) {
			if (visited[i] == 1) {
				for (j = 0; j < numBranches; j++) {
					if (visited[j] != 1) {
						if (minCost > cost[i][j]) {
							minCost = cost[i][j];
							src = i;
							dest = j;
						}
					}
				}
			}
		}
		visited[src] = 1;
		visited[dest] = 1;
		totalCost += minCost;
		cout << "Minimum cost connection is " << (src + 1) << " -> " << (dest + 1) << " with charge: " << minCost << endl;
	}
	cout << "The minimum total cost of connections of all branches is: " << totalCost << endl;
}
int main() {
	int choice;
	Tree t;
	do {
		cout << "^^^^^^^^^^^^^^ MINIMUM COST FINDER ^^^^^^^^^^^^^^" << endl;
		cout << "\n1. INPUT\n2. DISPLAY\n3. MINIMUM\n" << endl;
		cout << "Enter your choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			cout << "___________ INPUT YOUR VALUES ___________" << endl;
			t.input();
			break;
		case 2:
			cout << "___________ DISPLAY THE CONTENTS ___________" << endl;
			t.display();
			break;
		case 3:
			cout << "___________ FIND MINIMUM COST ___________" << endl;
			t.minimum();
			break;
		}
	} while (choice != 4);
	return 0;
}



/*
=================================================================================================================================================================
D1) Given sequence k = k1 <k2 < … < kn of n sorted keys, with a search probability pi for each key ki . Build the Binary search tree that has the least search cost given the access probability for each key.

Sample Output : 
                How many elements are there in the tree? : 6
                Enter 6 elements (keys) :50 44 19 66 51 64
                Enter 6 their Successful probabilities : 0.10 0.15 0.05 0.10 0.20 0.10
                Enter 7 failure probabilities : 0.05 0.10 0.05 0.05 0.10 0.15 0.05
=================================================================================================================================================================
*/

#include <iostream>
#include <algorithm>
using namespace std;

class obst {
	int a[10], r[10][10], n;
	float p[10], q[10], w[10][10], c[10][10];

public:
	void accept();
	void cons_obst();
	int find_min(int, int);
	void tree(int i, int j);
	void sort_keys();  // Added function to sort keys and adjust probabilities
};

void obst::accept() {
	int i;
	cout << "\nHow many elements are there in the tree? : ";
	cin >> n;

	cout << "\nEnter " << n << " elements (keys) :";
	for (i = 1; i <= n; i++) {
		cin >> a[i];
	}

	cout << "\nEnter " << n << " their Successful probabilities : ";
	for (i = 1; i <= n; i++) {
		cin >> p[i];
	}

	cout << "\nEnter " << n + 1 << " failure probabilities : ";
	for (i = 0; i <= n; i++) {
		cin >> q[i];
	}

	sort_keys();  // Sort keys and adjust the probabilities
}

void obst::sort_keys() {
	// Sorting keys and adjusting probabilities
	pair<int, float> keys[n];  // Pair of key and success probability
	for (int i = 1; i <= n; i++) {
		keys[i-1] = {a[i], p[i]};
	}

	sort(keys, keys + n);  // Sort based on keys (first element)

	// Reassign sorted values back
	for (int i = 1; i <= n; i++) {
		a[i] = keys[i-1].first;
		p[i] = keys[i-1].second;
	}

	// Ensure failure probabilities (q) are unchanged
}

void obst::cons_obst() {
	int i, m, j, k;
	for (i = 0; i < n; i++) {  // Initialize the weight and cost matrices when j-i = 0 and j-i=1
		w[i][i] = q[i];
		r[i][i] = c[i][i] = 0;
		w[i][i + 1] = q[i] + q[i + 1] + p[i + 1];
		r[i][i + 1] = i + 1;
		c[i][i + 1] = w[i][i + 1];
	}

	w[n][n] = q[n];
	r[n][n] = c[n][n] = 0;

	for (m = 2; m <= n; m++) {
		for (i = 0; i <= n - m; i++) {
			j = i + m;
			w[i][j] = w[i][j - 1] + p[j] + q[j];
			k = find_min(i, j);  // Find minimum value in the range r[i-1][j] to r[i][j-1]
			c[i][j] = w[i][j] + c[i][k - 1] + c[k][j];
			r[i][j] = k;
		}
	}

	cout << "\n\nRoot node is " << a[r[0][n]];
	cout << "\n Left child of " << a[r[0][n]] << " is ";
	tree(0, r[0][n] - 1);
	cout << "\n Right child of " << a[r[0][n]] << " is ";
	tree(r[0][n], n);
}

int obst::find_min(int i, int j) {
	int min = 999, k, z;
	for (k = r[i][j - 1]; k <= r[i + 1][j]; k++) {
		if (min > c[i][k - 1] + c[k][j]) {
			min = c[i][k - 1] + c[k][j];
			z = k;
		}
	}
	return z;
}

void obst::tree(int i, int j) {
	if (r[i][j] == 0) {
		cout << " NULL\n";
		return;
	}
	cout << " :: " << a[r[i][j]];
	cout << "\n Left child of is ::" << a[r[i][j]];
	tree(i, r[i][j] - 1);
	cout << "\n Right child of is :: " << a[r[i][j]];
	tree(r[i][j], j);
}

int main() {
	obst o;
	o.accept();
	o.cons_obst();
	return 0;
}



/*
================================================================================================================================================================
D2) A Dictionary stores keywords & its meanings. Provide facility for adding new keywords, deleting keywords, updating values of any entry. Provide facility to display whole data sorted in ascending/ Descending order. Also find how many maximum comparisons may require for finding any keyword. Use Height balance tree and find the complexity for finding a keyword.


-> AVL tree has worst-case search complexity = O(log n).
================================================================================================================================================================
*/
#include <iostream>
#include <string>
using namespace std;
struct Node {
	string keyword, meaning;
	Node* left;
	Node* right;
	int height;
};
Node* createNode(string keyword, string meaning) {
	Node* node = new Node();
	node->keyword = keyword;
	node->meaning = meaning;
	node->left = node->right = nullptr;
	node->height = 1;
	return node;
}
int getHeight(Node* node) {
	return node ? node->height : 0;
}
int getBalanceFactor(Node* node) {
	return node ? getHeight(node->left) - getHeight(node->right) : 0;
}
Node* rightRotate(Node* y) {
	Node* x = y->left;
	Node* T2 = x->right;
	x->right = y;
	y->left = T2;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	return x;
}
Node* leftRotate(Node* x) {
	Node* y = x->right;
	Node* T2 = y->left;
	y->left = x;
	x->right = T2;
	x->height = max(getHeight(x->left), getHeight(x->right)) + 1;
	y->height = max(getHeight(y->left), getHeight(y->right)) + 1;
	return y;
}
Node* insert(Node* root, string keyword, string meaning) {
	if (!root) return createNode(keyword, meaning);
	if (keyword < root->keyword)
		root->left = insert(root->left, keyword, meaning);
	else if (keyword > root->keyword)
		root->right = insert(root->right, keyword, meaning);
	else {
		root->meaning = meaning;
		return root;
	}
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	int balance = getBalanceFactor(root);
	if (balance > 1 && keyword < root->left->keyword)
		return rightRotate(root);
	if (balance < -1 && keyword > root->right->keyword)
		return leftRotate(root);
	if (balance > 1 && keyword > root->left->keyword) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (balance < -1 && keyword < root->right->keyword) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}
Node* minValueNode(Node* node) {
	while (node->left)
		node = node->left;
	return node;
}
Node* deleteNode(Node* root, string keyword) {
	if (!root) return root;
	if (keyword < root->keyword)
		root->left = deleteNode(root->left, keyword);
	else if (keyword > root->keyword)
		root->right = deleteNode(root->right, keyword);
	else {
		if (!root->left || !root->right) {
			Node* temp = root->left ? root->left : root->right;
			if (!temp) {
				temp = root;
				root = nullptr;
			} else
				*root = *temp;
			delete temp;
		} else {
			Node* temp = minValueNode(root->right);
			root->keyword = temp->keyword;
			root->meaning = temp->meaning;
			root->right = deleteNode(root->right, temp->keyword);
		}
	}
	if (!root) return root;
	root->height = max(getHeight(root->left), getHeight(root->right)) + 1;
	int balance = getBalanceFactor(root);
	if (balance > 1 && getBalanceFactor(root->left) >= 0)
		return rightRotate(root);
	if (balance > 1 && getBalanceFactor(root->left) < 0) {
		root->left = leftRotate(root->left);
		return rightRotate(root);
	}
	if (balance < -1 && getBalanceFactor(root->right) <= 0)
		return leftRotate(root);
	if (balance < -1 && getBalanceFactor(root->right) > 0) {
		root->right = rightRotate(root->right);
		return leftRotate(root);
	}
	return root;
}
bool search(Node* root, string keyword, int depth = 0) {
	if (!root) return false;
	if (keyword == root->keyword) {
		cout << "Found at depth: " << depth << endl;
		return true;
	}
	return keyword < root->keyword ? search(root->left, keyword, depth + 1) : search(root->right,
	        keyword, depth + 1);
}
void inorder(Node* root) {
	if (root) {
		inorder(root->left);
		cout << root->keyword << " : " << root->meaning << endl;
		inorder(root->right);
	}
}
void reverseInorder(Node* root) {
	if (root) {
		reverseInorder(root->right);
		cout << root->keyword << " : " << root->meaning << endl;
		reverseInorder(root->left);
	}
}
int main() {
	Node* root = nullptr;
	int choice;
	string keyword, meaning;
	do {
		cout << "\nMenu:\n1. Insert\n2. Delete\n3. Search\n4. Display Ascending\n5. Display Descending\n6. Exit\nEnter your choice: ";
		     cin >> choice;
		switch (choice) {
		case 1:
			cout << "Enter keyword: ";
			cin >> keyword;
			cout << "Enter meaning: ";
			cin.ignore();
			getline(cin, meaning);
			root = insert(root, keyword, meaning);
			break;
		case 2:
			cout << "Enter keyword to delete: ";
			cin >> keyword;
			root = deleteNode(root, keyword);
			break;
		case 3:
			cout << "Enter keyword to search: ";
			cin >> keyword;
			if (!search(root, keyword))
				cout << "Not Found" << endl;
			break;
		case 4:
			cout << "\nDictionary (Ascending Order):\n";
			inorder(root);
			break;
		case 5:
			cout << "\nDictionary (Descending Order):\n";
			reverseInorder(root);
			break;
		}
	} while (choice != 6);
	return 0;
}



/*
=======================================================================================================================
E1) Read the marks obtained by students of second year in an online examination of particular subject. 
    Find out maximum and minimum marks obtained in that subject using heap data structure. Analyze the algorithm.

    Time Complexity:
        - Build Heap: O(n)
        - Access min/max: O(1) from a[1] after building heap

    Space Complexity:
        - O(n) for storing student marks in array
=======================================================================================================================
*/

#include <iostream>
using namespace std;

void min_heapify(int *a, int i, int n)
{
    int j, temp;
    temp = a[i];
    j = 2 * i;
    while (j <= n)
    {
        if (j < n && a[j + 1] < a[j])
            j = j + 1;
        if (temp < a[j])
            break;
        else if (temp >= a[j])
        {
            a[j / 2] = a[j];
            j = 2 * j;
        }
    }
    a[j / 2] = temp;
}

void max_heapify(int *a, int i, int n)
{
    int j, temp;
    temp = a[i];
    j = 2 * i;
    while (j <= n)
    {
        if (j < n && a[j + 1] > a[j])
            j = j + 1;
        if (temp > a[j])
            break;
        else if (temp <= a[j])
        {
            a[j / 2] = a[j];
            j = 2 * j;
        }
    }
    a[j / 2] = temp;
    return;
}

void build_minheap(int *a, int n)
{
    int i;
    for (i = n / 2; i >= 1; i--)
    {
        min_heapify(a, i, n);
    }
}

void build_maxheap(int *a, int n)
{
    int i;
    for (i = n / 2; i >= 1; i--)
    {
        max_heapify(a, i, n);
    }
}

int main()
{
    int n, i, ch;
    cout << "\nEnter number of students: ";
    cin >> n;
    int a[100]; // increase array size to handle up to 99 students
    for (i = 1; i <= n; i++)
    {
        cout << "Enter mark of student " << i << ": ";
        cin >> a[i];
    }

    do
    {
        cout << "\n1. MIN Heap \n2. MAX Heap \n3. Exit";
        cout << "\nEnter the choice: ";
        cin >> ch;
        switch (ch)
        {
        case 1:
            build_minheap(a, n);
            cout << "Min Heap:\n";
            for (i = 1; i <= n; i++)
            {
                cout << a[i] << endl;
            }
            cout << "Minimum mark is: " << a[1] << endl;
            break;

        case 2:
            build_maxheap(a, n);
            cout << "Max Heap:\n";
            for (i = 1; i <= n; i++)
            {
                cout << a[i] << endl;
            }
            cout << "Maximum mark is: " << a[1] << endl;
            break;

        case 3:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }
    } while (ch != 3);

    return 0;
}


/*
================================================================================================================================================================
F1) Department maintains a student information. The file contains roll number, name, and division and address. Allow user to add, delete information of student. Display information of particular employee. If record of student does not exist an appropriate message is displayed. If it is, then the system displays the student details. Use sequential file to main the data.
================================================================================================================================================================
*/

#include<iostream>
#include<fstream>
#include<string.h>
using namespace std;
class student
{
	typedef struct stud
	{
		int roll;
		char name[10];
		char div;
		char add[10];
	} stud;
	stud rec;
public:
	void create();
	void display();
	int search();
	void Delete();
};
void student::create()
{
	char ans;
	ofstream fout;
	fout.open("stud.txt",ios::out|ios::binary);
	do
	{
		cout<<"\n\tEnter Roll No of Student    : ";
		cin>>rec.roll;
		cout<<"\n\tEnter a Name of Student     : ";
		cin>>rec.name;
		cout<<"\n\tEnter a Division of Student : ";
		cin>>rec.div;
		cout<<"\n\tEnter a Address of Student  : ";
		cin>>rec.add;
		fout.write((char *)&rec,sizeof(stud))<<flush;
		cout<<"\n\tDo You Want to Add More Records: ";
		cin>>ans;
	} while(ans=='y'||ans=='Y');
	fout.close();
}
void student::display()
{
	ifstream fin;
	fin.open("stud.txt",ios::in|ios::binary);
	fin.seekg(0,ios::beg);
	cout<<"\n\tThe Content of File are:\n";
	cout<<"\n\tRoll\tName\tDiv\tAddress";
	while(fin.read((char *)&rec,sizeof(stud)))
	{
		if(rec.roll!=-1)
			cout<<"\n\t"<<rec.roll<<"\t"<<rec.name<<"\t"<<rec.div<<"\t"<<rec.add;
	}
	fin.close();
}
int student::search()
{
	int r,i=0;
	ifstream fin;
	fin.open("stud.txt",ios::in|ios::binary);
	fin.seekg(0,ios::beg);
	cout<<"\n\tEnter a Roll No: ";
	cin>>r;
	while(fin.read((char *)&rec,sizeof(stud)))
	{
		if(rec.roll==r)
		{
			cout<<"\n\tRecord Found...\n";
			cout<<"\n\tRoll\tName\tDiv\tAddress";
			cout<<"\n\t"<<rec.roll<<"\t"<<rec.name<<"\t"<<rec.div<<"\t"<<rec.add;
			return i;
		}
		i++;
	}
	fin.close();
	return 0;
}
void student::Delete()
{
	int pos;
	pos=search();
	fstream f;
	f.open("stud.txt",ios::in|ios::out|ios::binary);
	f.seekg(0,ios::beg);
	if(pos==0)
	{
		cout<<"\n\tRecord Not Found";
		return;
	}
	int offset=pos*sizeof(stud);
	f.seekp(offset);
	rec.roll=-1;
	strcpy(rec.name,"NULL");
	rec.div='N';
	strcpy(rec.add,"NULL");
	f.write((char *)&rec,sizeof(stud));
	f.seekg(0);
	f.close();
	cout<<"\n\tRecord Deleted";
}

int main()
{
	student obj;
	int ch,key;
	char ans;
	do
	{
		cout<<"\n\t***** Student Information *****";
		cout<<"\n\t1. Create\n\t2. Display\n\t3. Delete\n\t4. Search";
		cout<<"\n\t..... Enter Your Choice: ";
		cin>>ch;
		switch(ch)
		{
		case 1:
			obj.create();
			break;
		case 2:
			obj.display();
			break;
		case 3:
			obj.Delete();
			break;
		case 4:
			key=obj.search();
			if(key==0)
				cout<<"\n\tRecord Not Found...\n";
			break;
		}
		cout<<"\n\t..... Do You Want to Continue in Main Menu: ";
		cin>>ans;
	} while(ans=='y'||ans=='Y');
	return 1;
}


/*
================================================================================================================================================================
F2) Company maintains employee information as employee ID, name, designation and salary. Allow user to add, delete information of employee. Display information of particular employee. If employee does not exist an appropriate message is displayed. If it is, then the system displays the employee details. Use index sequential file to maintain the data.
================================================================================================================================================================
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
using namespace std;

struct Employee {
	int emp_id;
	string name;
	int salary;
};

struct IndexEntry {
	int emp_id;
	int position;  // Line number in EMP.txt
};

class EMP_CLASS {
	vector<IndexEntry> index;

public:
	void Create();
	void Display();
	void Update();
	void Delete();
	void Append();
	void Search();
	void LoadIndex();
};

void EMP_CLASS::LoadIndex() {
	index.clear();
	ifstream idx("IND.txt");
	IndexEntry entry;
	while (idx >> entry.emp_id >> entry.position) {
		index.push_back(entry);
	}
	idx.close();
}

void EMP_CLASS::Create() {
	ofstream emp("EMP.txt");
	ofstream idx("IND.txt");
	char ch = 'y';
	int position = 0;
	while (ch == 'y') {
		Employee e;
		cout << "Enter Emp_ID: ";
		cin >> e.emp_id;
		cout << "Enter Name: ";
		cin >> e.name;
		cout << "Enter Salary: ";
		cin >> e.salary;

		emp << e.emp_id << " " << e.name << " " << e.salary << endl;
		idx << e.emp_id << " " << position++ << endl;

		cout << "Add more? (y/n): ";
		cin >> ch;
	}
	emp.close();
	idx.close();
}

void EMP_CLASS::Display() {
	LoadIndex();
	ifstream emp("EMP.txt");
	string line;
	int line_no = 0;
	cout << "\nEmployee Records:\n";
	while (getline(emp, line)) {
		istringstream iss(line);
		Employee e;
		iss >> e.emp_id >> e.name >> e.salary;
		if (e.emp_id != -1) {
			cout << "Emp_ID: " << e.emp_id << ", Name: " << e.name << ", Salary: " << e.salary << endl;
		}
		line_no++;
	}
	emp.close();
}

void EMP_CLASS::Update() {
	LoadIndex();
	int id;
	cout << "Enter Emp_ID to update: ";
	cin >> id;
	int pos = -1;
	for (auto &entry : index) {
		if (entry.emp_id == id) {
			pos = entry.position;
			break;
		}
	}
	if (pos == -1) {
		cout << "Record not found.\n";
		return;
	}

	vector<string> lines;
	ifstream emp("EMP.txt");
	string line;
	while (getline(emp, line)) {
		lines.push_back(line);
	}
	emp.close();

	Employee e;
	cout << "Enter new Name: ";
	cin >> e.name;
	cout << "Enter new Salary: ";
	cin >> e.salary;
	e.emp_id = id;

	lines[pos] = to_string(e.emp_id) + " " + e.name + " " + to_string(e.salary);
	ofstream out("EMP.txt");
	for (auto &l : lines)
		out << l << endl;
	out.close();
	cout << "Record updated.\n";
}

void EMP_CLASS::Delete() {
	LoadIndex();
	int id;
	cout << "Enter Emp_ID to delete: ";
	cin >> id;
	int pos = -1;
	for (auto &entry : index) {
		if (entry.emp_id == id) {
			pos = entry.position;
			entry.emp_id = -1;  // mark in index too
			break;
		}
	}
	if (pos == -1) {
		cout << "Record not found.\n";
		return;
	}

	vector<string> lines;
	ifstream emp("EMP.txt");
	string line;
	while (getline(emp, line)) {
		lines.push_back(line);
	}
	emp.close();

	lines[pos] = "-1 DELETED -1";  // mark as logically deleted

	ofstream out("EMP.txt");
	for (auto &l : lines)
		out << l << endl;
	out.close();

	ofstream idxout("IND.txt");
	for (auto &entry : index)
		idxout << entry.emp_id << " " << entry.position << endl;
	idxout.close();

	cout << "Record deleted.\n";
}

void EMP_CLASS::Append() {
	LoadIndex();
	ofstream emp("EMP.txt", ios::app);
	ofstream idx("IND.txt", ios::app);
	Employee e;
	cout << "Enter Emp_ID: ";
	cin >> e.emp_id;
	cout << "Enter Name: ";
	cin >> e.name;
	cout << "Enter Salary: ";
	cin >> e.salary;

	emp << e.emp_id << " " << e.name << " " << e.salary << endl;
	idx << e.emp_id << " " << index.size() << endl;

	emp.close();
	idx.close();
	cout << "Record appended.\n";
}

void EMP_CLASS::Search() {
	LoadIndex();
	int id;
	cout << "Enter Emp_ID to search: ";
	cin >> id;
	int pos = -1;
	for (auto &entry : index) {
		if (entry.emp_id == id) {
			pos = entry.position;
			break;
		}
	}
	if (pos == -1) {
		cout << "Record not found.\n";
		return;
	}

	ifstream emp("EMP.txt");
	string line;
	int curr = 0;
	while (getline(emp, line)) {
		if (curr == pos) {
			istringstream iss(line);
			Employee e;
			iss >> e.emp_id >> e.name >> e.salary;
			if (e.emp_id == -1) {
				cout << "Record was deleted.\n";
			} else {
				cout << "Emp_ID: " << e.emp_id << ", Name: " << e.name << ", Salary: " << e.salary << endl;
			}
			break;
		}
		curr++;
	}
	emp.close();
}

// ----------------- Main ------------------
int main() {
	EMP_CLASS e;
	int choice;
	do {
		cout << "\n1. Create\n2. Display\n3. Update\n4. Delete\n5. Append\n6. Search\n7. Exit\nEnter choice: ";
		cin >> choice;
		switch (choice) {
		case 1:
			e.Create();
			break;
		case 2:
			e.Display();
			break;
		case 3:
			e.Update();
			break;
		case 4:
			e.Delete();
			break;
		case 5:
			e.Append();
			break;
		case 6:
			e.Search();
			break;
		case 7:
			cout << "Exiting...\n";
			break;
		default:
			cout << "Invalid choice!\n";
		}
	} while (choice != 7);

	return 0;
}
