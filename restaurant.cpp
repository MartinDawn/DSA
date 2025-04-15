#include "main.h"
int MAXSIZE;
// template <typename E, typename T>
// E Search(E begin, E end, T value) {
//   E i=begin;
//   E j=end-1;
//   while (j-i >= 1) {
//     E m = i + (j - i) / 2;
//     if ((*m)->value > value->value) {
//       i = m+1 ;
//     } else {
//       j = m;
//     }
//   }
//   return j;
// }
// template<typename E>
// class new_structure
// {
// 	public:
// 	vector<E> myVector;
// 	void insert(E data)
// 	{
// 		if(!myVector.empty()){
// 		auto it=Search(myVector.begin(),myVector.end(),data);
// 		//auto it=upper_bound(myVector.begin(),myVector.end(),data,greater<E>());
// 		myVector.insert(it,data);
// 		}
// 		else myVector.insert(myVector.begin(),data);
// 	}
// 	void push(E data)
// 	{
// 		myVector.insert(myVector.begin(),data);
// 	}
// 	E pop()
// 	{
// 		E last_element=myVector.back();
// 		myVector.pop_back();
// 		return last_element;
// 	}
// 	bool empty()
// 	{
// 		return myVector.empty();
// 	}
// 	int size()
// 	{
// 		return myVector.size();
// 	}
// 	void print()
// 	{
// 		for(auto &v: myVector)
// 		{
// 			solution<<*v<<" ";
// 		}
// 		solution<<endl;
// 	}
// };
vector<vector<int>> DP(200,vector<int>(200, 0));
template< typename E>
E C(E m,E n)
{
	if(m==0)return 1;
	if(m==n)return 1;
	if(DP[m][n]>0)return DP[m][n];
	DP[m][n]=(C(m-1,n-1)%MAXSIZE+C(m-1,n)%MAXSIZE)%MAXSIZE;
	return DP[m][n];
}
class Customer{
	public:
	int result;
	string name;
	string C_name="";
	string binary_name="";
	unordered_map<char,string> dp;
	int count;
	// cay huffman
	class Huffman_tree{
		public:
		int value,ID;
		char id;
		Huffman_tree* left;
		Huffman_tree* right;
		Huffman_tree(int value,char id,int ID):
		value(value),
		id(id),
		ID(ID),
		left(nullptr),right(nullptr){};
		// bool operator >(const Huffman_tree *&a)const
		// {
		// 	if(this->value!=a->value)
		// 	return this->value>a->value;
		// 	return this->ID>a->ID;
		// }
		// bool operator <(const Huffman_tree *&a)const
		// {
		// 	if(this->value!=a->value)
		// 	return this->value < a->value;
		// 	return this->ID < a->ID;
		// }
		// bool operator ==(const Huffman_tree *&a)const{
		// 	return this->value==a->value;
		// }
		// bool operator >=(const Huffman_tree *&a)const
		// {
		// 	return this->value>= a->value;
		// }
		// bool operator <=(const Huffman_tree *&a)const
		// {
		// 	return this->value<= a->value;
		// }
		friend ostream& operator <<(ostream &os,const Huffman_tree huff)
		{
			os<<huff.value<<huff.id<<"*";
			return os;
		}
	};
	Huffman_tree * huffman;
	// khoi tao customer
	Customer(string name):
	name(name),
	result(0),
	count(0),
	huffman(nullptr){
		unordered_map<char,int> myMap;
		for(char c:name)
		{
			if(myMap.find(c)==myMap.end())
			{
				myMap[c]=1;
			}
			else {
				myMap[c]+=1;
			}
		}
		unordered_map <char,char> transform;
		vector<pair<char,int>> myVector(myMap.begin(),myMap.end());
		unordered_map<char,int> myMap2;
		for(auto &v:myVector){
			int tmp=v.second;
			if(v.first-'a'>=0){
				tmp=tmp+v.first-'a';
				transform[v.first]='a'+tmp%26;
				v.first='a'+tmp%26;
			}
			else{
				tmp+=v.first-'A';
				transform[v.first]='A'+tmp%26;
				v.first='A'+tmp%26;
			}
			if(myMap2.find(v.first)==myMap2.end())
			{
				myMap2[v.first]=v.second;
			}
			else{
				myMap2[v.first]+=v.second;
			}
		}
		for(int i=0;i<name.size();i++)
		{
			C_name=C_name+transform[name[i]];
		}
		vector<pair<char,int>> myVector2(myMap2.begin(),myMap2.end());
		sort(myVector2.begin(),myVector2.end(),
		[](auto &a,auto &b){
			if(a.second!=b.second)return a.second<b.second;
			else{
				if(a.first<='Z'&&a.first>='A'&&b.first<='z'&&b.first>='a')return false;
				if(a.first<='z'&&a.first>='a'&&b.first<='Z'&&b.first>='A')return true;
				return a.first<b.first;
			}
		}
		);
		// for(auto &v :myVector2){
		// 	solution<<v.first<<" "<<v.second<<endl;
		// }
		make_tree(myVector2);
		convert(huffman);
		convert_name();
	};
	Huffman_tree* Rotate_left(Huffman_tree* Node)
	{
		Huffman_tree* current= Node->right;
		if(!current)return nullptr;
		Node->right=current->left;
		current->left=Node;
		return current;

	}
	Huffman_tree* Rotate_right(Huffman_tree*Node)
	{
		Huffman_tree* current= Node->left;
		if(!current)return nullptr;
		Node->left=current->right;
		current->right=Node;
		return current;
	}
	int Get_height(Huffman_tree * Node)//get height of tree
	{
		if(Node==nullptr)return 0;
		int l=Get_height(Node->left);
		int r=Get_height(Node->right);
		return 1+max(l,r);
	}
	Huffman_tree* Rotate(Huffman_tree* huff_3,int &i)
	{
		if(huff_3==nullptr)return nullptr;
		Huffman_tree* huff_1=huff_3->left;
		Huffman_tree* huff_2=huff_3->right;
		int balance=Get_height(huff_1)-Get_height(huff_2);
		if(balance>1)
		{
			int balance2=Get_height(huff_1->left)-Get_height(huff_1->right);
			if(balance2<0){
				huff_1=Rotate_left(huff_1);
				huff_3->left=huff_1;
			}
			huff_3=Rotate_right(huff_3);
			huff_3->ID=huff_3->right->ID;
			i++;
		}
		else if(balance<-1)
		{			
			int balance3=Get_height(huff_2->left)-Get_height(huff_2->right);
			if(balance3>0){
				huff_2=Rotate_right(huff_2);
				huff_3->right=huff_2;
			}
			huff_3=Rotate_left(huff_3);
			huff_3->ID=huff_3->left->ID;
			i++;
		}
		else{
		int I=i;
		huff_3->left=Rotate(huff_3->left,i);
		if(I==i)
		huff_3->right=Rotate(huff_3->right,i);
		}
		return huff_3;
	}
	Huffman_tree* combine_tree(Huffman_tree* huff_1,Huffman_tree* huff_2)
	{
		Huffman_tree* huff_3=new Huffman_tree(huff_1->value+huff_2->value,' ',++count);
		huff_3->left=huff_1;
		huff_3->right=huff_2;
		int i=0;
		huff_3=Rotate(huff_3,i);
		huff_3=Rotate(huff_3,i);
		huff_3=Rotate(huff_3,i);
		return huff_3;
	}
	void printTree(Huffman_tree* root, int level = 0, const string& prefix = "Root: ") {
    if (root != nullptr) {
        solution << string(level * 4, ' ') << prefix ;
		if(root->id!=' ')solution<<root->id<<root->value<<endl;
		else solution<<root->value<<endl;

        if (root->left != nullptr || root->right != nullptr) {
            printTree(root->left, level + 1, "L--- ");
            printTree(root->right, level + 1, "R--- ");
        }
    }
}
	void make_tree(vector<pair<char,int>> &myVector){
		//new_structure<Huffman_tree*> *structure= new new_structure<Huffman_tree*>;
		auto compare=[](auto &a, auto &b)
		{
			if(a->value!=b->value)return a->value>b->value;
			return a->ID>b->ID;
		};
		std::priority_queue<Huffman_tree*,vector<Huffman_tree*>,decltype(compare)> PQ(compare);	
		for(auto &v: myVector)
		{
			Huffman_tree * new_huff= new Huffman_tree(v.second,v.first,++count);
			PQ.push(new_huff);
		}
		while(PQ.size()>1)
		{
			Huffman_tree* huff_1=PQ.top();
			//solution<<huff_1->value<<" "<<huff_1->ID<<endl;
			// printTree(huff_1);
			PQ.pop();
			Huffman_tree* huff_2=PQ.top();
			//solution<<huff_2->value<<" "<<huff_2->ID<<endl;
			// printTree(huff_2);
			PQ.pop();
			Huffman_tree* huff_3=combine_tree(huff_1,huff_2);
			// printTree(huff_3);
			if(huff_3->id!=' ')return;
			//structure->insert(huff_3);
			//structure->print();
			PQ.push(huff_3);
			//solution<<huff_3->value<<" "<<huff_3->ID<<endl<<endl;
			// solution<<endl;
		}
		huffman=PQ.top();
	}
	void convert(Huffman_tree* Node,string s="")
	{
		if(!Node)return;
		if(Node->id!=' ')dp[Node->id]=s;
		convert(Node->left,s+'0');
		convert(Node->right,s+'1');
	}
	void convert_name()
	{
		//solution<<dp['Z']<<endl;
		int i=C_name.size()-1;
		while(i>=0&&binary_name.size()<10)
		{
			binary_name=dp[C_name[i]]+binary_name;
			i--;
		}
		int t=binary_name.size()>=10?binary_name.size()-10:0;
		for(int j=binary_name.size()-1;j>=t;j--)
		{
			result=result*2+binary_name[j]-'0';
		}
	}
	void print(Huffman_tree* huff)
	{
		if(huff==nullptr)return;
		print(huff->left);
		if(huff->id!=' ')
		{
			solution<<huff->id<<'\n';
		}
		else
		{
			solution<<huff->value<<'\n';
		}
		print(huff->right);
	}
	~Customer(){
		delete huffman;
	}
};
class Gojo_restaurant
{
	public:
	int time=0;
	class BST
	{
		public:
		int id, result, left_count, right_count;
		BST* left;
		BST* right;
		BST(int id,int result):
		result(result),
		id(id),
		left(nullptr),
		right(nullptr),
		left_count(0),
		right_count(0){};
		BST* insert(BST* root,BST* Node)
		{
			if(root==nullptr)return Node;
			if(Node->result<root->result)
			{
				root->left=insert(root->left,Node);
				root->left_count++;
			}
			else
			{
				root->right=insert(root->right,Node);
				root->right_count++;
			}
			return root;
		}
		void insert(BST* Node)
		{
			insert(this,Node);
		}
		BST* findMin(BST* Node)
		{
			while(Node->left!=nullptr){
				Node=Node->left;
			}
			return Node;
		}
		BST* remove(int id,int result,BST* root)
		{
			if(id==root->id&&result==root->result)
			{
				if(root->left==nullptr){
					BST* temp=	root->right;
					delete root;
					return temp;
				}
				else if(root->right==nullptr){
					BST* temp= root->left;
					delete root;
					return temp;
				}
				BST* temp= findMin(root->right);
				root->id=temp->id;
				root->result=temp->result;
				root->right_count--;
				root->right=remove(root->id,root->result,root->right);
			}
			else if(result<root->result)
			{
				root->left=remove(id,result,root->left);
				root->left_count--;
			}
			else if(result>=root->result)
			{
				root->right=remove(id,result,root->right);
				root->right_count--;
			}
		}
		// void remove(int id,int result,BST* root)
		// {
		// 	root=remove(id,result,this);
		// }
	};
	unordered_map<int,BST*> Map;
	unordered_map<int,queue<pair<int,int>>> Map2;
	void insert(Customer* customer)
	{
		int index= customer->result%MAXSIZE+1;
		BST *newBST=new BST(++time,customer->result);
		if(Map.find(index)==Map.end()||Map[index]==nullptr){
			Map[index]=newBST;
		}
		else{
			Map[index]->insert(newBST);
		}
		Map2[index].push(std::make_pair(newBST->id,newBST->result));
	}
	int findY(BST* current)
	{
		if(current==nullptr)return 1;
		return (findY(current->left)*findY(current->right)*C(current->left_count,current->left_count+current->right_count))%MAXSIZE;
	}
	int findY(int index)
	{
		if(Map.find(index)==Map.end()||Map[index]==nullptr)return 0;
		return findY(Map[index]);
	}
	void KOKUSEN()
	{
		for(int i=1;i<=MAXSIZE;i++)
		{
			int y=findY(i);
			if(y>0)
			while(y>0&&!Map2[i].empty()){
				Map[i]=Map[i]->remove(Map2[i].front().first,Map2[i].front().second,Map[i]);
				Map2[i].pop();
				y--;
			}
		}
	}
	void print(BST* Node)
	{
		if(!Node)return;
		print(Node->left);
		solution<<Node->result<<'\n';
		print(Node->right);
	}
	void print(int index)
	{
		print(Map[index]);
	}
};
class Sukuma_restaurant
{
	public:
	int time;
	Sukuma_restaurant():
	time(0){};
	class Min_heap
	{
		public:
		struct Obj
		{
			int id,count,time;
		};
		vector<Obj> heap;
		void reHeapUp(int index)
		{
			while(index>0){
				int parent=(index-1)/2;
				if(heap[index].count<heap[parent].count||(heap[index].count==heap[parent].count&&heap[index].time>heap[parent].time))
				{
					std::swap(heap[index].id,heap[parent].id);
					std::swap(heap[index].count,heap[parent].count);
					std::swap(heap[index].time,heap[parent].time);
					index=parent;
				}
				else break;
			}
		}
		void reHeapDown(int index)
		{
			int	leftChild=2*index+1;
			int rightChild=2*index+2;
			int smallest=index;
			if(leftChild<heap.size())
			{
				if(heap[leftChild].count<heap[smallest].count||(heap[leftChild].count==heap[smallest].count&&heap[leftChild].time>heap[smallest].time))
				smallest=leftChild;
			}
			if(rightChild<heap.size())
			{
				if(heap[rightChild].count<heap[smallest].count||(heap[rightChild].count==heap[smallest].count&&heap[rightChild].time>heap[smallest].time))
				smallest=rightChild;
			}
			if(smallest!=index)
			{
				std::swap(heap[index].count,heap[smallest].count);
				std::swap(heap[index].id,heap[smallest].id);
				std::swap(heap[index].time,heap[smallest].time);
				reHeapDown(smallest);
			}
		}
		void insert(int id,int count,int time)
		{
			Obj newObj{id,count,time};
			heap.push_back(newObj);
			reHeapUp(heap.size()-1);
		}
		void remove(int index)
		{
			std::swap(heap[index].count,heap[heap.size()-1].count);
			std::swap(heap[index].id,heap[heap.size()-1].id);
			std::swap(heap[index].time,heap[heap.size()-1].time);
			heap.pop_back();
			if(index<heap.size())
			{
				reHeapUp(index);
				reHeapDown(index);
			}
		}
		void Up(int id,int time)
		{
			for(int i=0;i<heap.size();i++)
			{
				if(heap[i].id==id)
				{
					heap[i].time=time;
					heap[i].count++;
					reHeapDown(i);
					break;
				}
			}
		}
		void Down(int id,int time)
		{
			for(int i=0;i<heap.size();i++)
			{
				if(heap[i].id==id)
				{
					heap[i].time=time;
					heap[i].count--;
					if(heap[i].count==0){
						remove(i);
						break;
					}
					reHeapUp(i);
					break;
				}
			}
		}
	};
	unordered_map<int,list<pair<int,int>>> count;
	Min_heap min_heap;
	void insert(Customer* customer){
		int index=customer->result%MAXSIZE+1;
		if(count.find(index)==count.end()||count[index].size()==0){
			min_heap.insert(index,1,++time);
		}
		else
		{
			min_heap.Up(index,++time);
		}
		count[index].push_back(make_pair(time,customer->result));
	}
	Min_heap operator=(Min_heap a)
	{
		Min_heap b;
		for(int i=0;i<a.heap.size();i++)
		{
			b.heap[i].count=a.heap[i].count;
			b.heap[i].id=a.heap[i].id;
			b.heap[i].time=a.heap[i].time;
		}
		return b;
	}
	void KEITEIKEN(int num)
	{
		int num1=num;
		Min_heap temp=min_heap;
		for(int i=0;i<num;i++)
		{
			int p=temp.heap[0].id;
			while(num1>0&&count[p].size()>0)
			{
				min_heap.Down(p,++time);
				count[p].pop_back();
				num1--;
			}
			temp.remove(p);
		}
	}
	void print(int id, int num)
	{
		if(id>=min_heap.heap.size())return;
		int i=min_heap.heap[id].id;
		int Num=num;
		stack<pair<int,int>> Stack;
		while(Num>0&&!count[i].empty())
		{
			Num--;
			solution<<i<<"-"<<count[i].back().second<<'\n';
			Stack.push(count[i].back());
			count[i].pop_back();
		}
		while(!Stack.empty())
		{
			count[i].push_back(Stack.top());
			Stack.pop();
		}
		print(id*2+1,num);
		print(id*2+2,num);
	}
};
class RESTAURANT
{
	public:
	Gojo_restaurant* G=new Gojo_restaurant;
	Sukuma_restaurant* S= new Sukuma_restaurant;
	Customer* current;
	int check(string &s)
	{
		unordered_map<char,int>myMap;
		for(char c:s)
		{
			if(myMap.find(c)==myMap.end())
			{
				myMap[c]=1;
			}
			else
			{
				myMap[c]+=1;
			}
		}
	return myMap.size();
	}
	void LAPSE(string &s)
	{
		if(check(s)<=2)return;
		Customer* customer= new Customer(s);
		current=customer;
		// solution<<customer->C_name<<" "<<customer->binary_name<<endl;
		solution<<"result = "<<customer->result<<endl;
		if(customer->result%2==1)G->insert(customer);
		else S->insert(customer);
	}
	void KOKUSEN(){
		//solution<<endl;
		solution<<"result = ";
		G->KOKUSEN();
		
	}
	void KEITEIKEN(int num){}
	void HAND(){
		current->print(current->huffman);
	}
	void LIMITLESS(int num){
		//solution<<endl;
		G->print(num);
	}
	void CLEAVE(int num){
		S->print(0,num);
	}
};
void simulate(string filename)
{
	ifstream ss(filename);
	string str;
	string num;
	RESTAURANT*restaurant=new RESTAURANT;
	int i=-1;
	while(ss>>str){
		//solution<<++i<<endl;
		i++;
		if(str=="MAXSIZE")
		{
			ss>>num;
			solution<<"MAXSIZE : "<<num<<'\n';
			MAXSIZE=stoi(num);
		}
		else if(str=="LAPSE")
		{
			ss>>num;
			//solution<<num<<" "<<str<<endl;
			solution<<"LAPSE : LINE "<<i<<'\n';
			restaurant->LAPSE(num);
		}
		else if(str=="KOKUSEN")
		{
			solution<<"KOKUSEN : LINE "<<i<<'\n';
			restaurant->KOKUSEN();
		}
		else if(str=="KEITEIKEN")
		{
			ss>>num;
			restaurant->KEITEIKEN(stoi(num));
		}
		else if(str=="HAND")
		{
			restaurant->HAND();
		}
		else if(str=="LIMITLESS")
		{
			ss>>num;
			restaurant->LIMITLESS(stoi(num));
		}
		else if(str=="CLEAVE")
		{
			ss>>num;
			restaurant->CLEAVE(stoi(num));
		}
	}
}