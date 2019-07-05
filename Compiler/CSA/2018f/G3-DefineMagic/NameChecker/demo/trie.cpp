#include <iostream>
#include <fstream>
#include <string>
#include <string.h>
#include <algorithm>
using namespace std;

struct TrieNode{
	int child,brother;
	char c;
	bool end;		
};
TrieNode* btree;
TrieNode* ftree;
//�ַ������� 
void reverse(string* s){
	int n=s->length();
	for (int i=0;i<n/2;i++){
		char temp=(*s)[i];
		(*s)[i]=(*s)[n-1-i];
		(*s)[n-1-i]=temp;		
	}
}
//���������trie������words.txt�ж���ʵ䲢��trie���洢��trie_f.txt�� 
TrieNode* build_f(){
	TrieNode* a=new TrieNode[1000000];
	string* s=new string[140000];
	ifstream f("words.txt");
	int len=1;
	if (f.is_open()){
		int n;
		for (n=0;!f.eof();n++){
			f>>s[n];
		}//���뵥�� 
		sort(s,s+n);
		a[0]={-1,-1,'$',0};//��ʼ��� 
		for (int i=0;i<n;i++){
			int t=0;
			int m=s[i].length();
			for (int j=0;j<m;j++){
				char c=s[i][j];
				if (a[t].child==-1){
					a[t].child=len;
					//cout<<len<<"\n";
					a[len]={-1,-1,c,0};
					t=len;
					len++;
				}//���trie����һ��û�н�㣬�ʹ���һ�� 
				else {
					t=a[t].child;
					while (a[t].c!=c){
						if (a[t].brother==-1){
							a[t].brother=len;
							a[len]={-1,-1,c,0};
							t=len;
							len++;
						}//�ұ���trie������һ�㣬û���ҵ���Ӧ�Ľ�㣬�ʹ���һ�� 
						else	t=a[t].brother;//�ҵ�ǰ���ĵܵ� 
					}					
				}
			}
			a[t].end=true;//���ʽ�β�����ս���			 
		}//��ÿһ�����ʽ���trie�� 
		f.close();
		ofstream fout("trie_f.txt");
		fout<<len<<"\r\n";
		for (int i=0;i<len;i++){
			fout<<a[i].child<<" ";
			fout<<a[i].brother<<" ";
			fout<<a[i].c<<" ";
			fout<<a[i].end<<"\r\n";
		}
		fout.close();
		//��trie���洢���ļ��� 
	}
	else {
		cout<<"Input File Is Not Existed\n";
	}	
	return a;
}
//���������trie������words.txt�ж���ʵ䲢��trie���洢��trie_b.txt�� 
TrieNode* build_b(){
	TrieNode* a=new TrieNode[1000000];
	string* s=new string[140000];
	ifstream f("words.txt");
	int len=1;
	if (f.is_open()){
		int n;
		for (n=0;!f.eof();n++){
			f>>s[n];
			reverse(&(s[n]));
		}//���뵥�� 
		sort(s,s+n);
		a[0]={-1,-1,'$',0};//��ʼ��� 
		for (int i=0;i<n;i++){
			int t=0;
			int m=s[i].length();
			for (int j=0;j<m;j++){
				char c=s[i][j];
				if (a[t].child==-1){
					a[t].child=len;
					//cout<<len<<"\n";
					a[len]={-1,-1,c,0};
					t=len;
					len++;
				}//���trie����һ��û�н�㣬�ʹ���һ�� 
				else {
					t=a[t].child;
					while (a[t].c!=c){
						if (a[t].brother==-1){
							a[t].brother=len;
							a[len]={-1,-1,c,0};
							t=len;
							len++;
						}//�ұ���trie������һ�㣬û���ҵ���Ӧ�Ľ�㣬�ʹ���һ�� 
						else	t=a[t].brother;//�ҵ�ǰ���ĵܵ� 
					}					
				}
			}
			a[t].end=true;//���ʽ�β�����ս���			 
		}//��ÿһ�����ʽ���trie�� 
		f.close();
		ofstream fout("trie_b.txt");
		fout<<len<<"\r\n";
		for (int i=0;i<len;i++){
			fout<<a[i].child<<" ";
			fout<<a[i].brother<<" ";
			fout<<a[i].c<<" ";
			fout<<a[i].end<<"\r\n";
		}
		fout.close();
		//��trie���洢���ļ��� 
	}
	else {
		cout<<"Input File Is Not Existed\n";
	}	
	return a;
}
//������������ַ�������ʶ�������������������ƥ�䣬���غϷ��ı����ʽ��������������޷�ʶ��ĵ��ʣ�����nullptr 
string* fmm(TrieNode* a,string &s){	
	int n=s.length();
	string* newstr=new string(s);	
	bool flag=false;//��־��ǰ�ַ��Ƿ�Ҫ��д 
	int t=0;//����ָ�룬ָʾ��ǰ���ʵ�TrieNode 
	for (int i=0;i<n;i++){
		if (flag)	(*newstr)[i]=toupper((*newstr)[i]);
		flag=false;
		char c=s[i];
		if (a[t].child==-1){
			if (a[t].end){
				flag=true;
				i--;
				t=0;
				continue;
			}//�����trie�����Ҳ�����ǰ�ַ�����ǰһ���ַ��Ѿ�������Ϊ���ʽ�β����ô���ͽ���ǰ�ַ���д����trie�������¿�ʼ���� 
			else{
				return nullptr;
			}//���ǰһ���ַ���������Ϊ���ʽ�β����ô����Ϊ����δ֪�ĵ��� 
		}//���trie����һ��û�н��
		else {
			int p=t;//��¼trie���е�ǰһ����� 
			t=a[t].child;
			while (a[t].c!=c){
				if (a[t].brother==-1){
					if (a[p].end){
						flag=true;
						i--;
						t=0;
						break;
					}//���ǰһ���ַ��Ѿ�������Ϊ���ʽ�β����ô���ͽ���ǰ�ַ���д����trie�������¿�ʼ���� 
					else{
						return nullptr;
					}
				}//�ұ���trie������һ�㣬û���ҵ���Ӧ�Ľ��
				else	t=a[t].brother;//�ҵ�ǰ���ĵܵ� 
			}					
		}
	}
	return newstr;
}
//������ķ����ַ�������ʶ�����������÷������ƥ�䣬���غϷ��ı����ʽ��������������޷�ʶ��ĵ��ʣ�����nullptr 
string* bmm(TrieNode* a,string &s){	
	int n=s.length();
	string* newstr=new string(s);	
	int t=0;//����ָ�룬ָʾ��ǰ���ʵ�TrieNode 
	for (int i=0;i<n;i++){
		char c=s[i];
		if (a[t].child==-1){
			if (a[t].end){
				(*newstr)[i-1]=toupper((*newstr)[i-1]);
				i--;
				t=0;
				continue;
			}//�����trie�����Ҳ�����ǰ�ַ�����ǰһ���ַ��Ѿ�������Ϊ���ʽ�β����ô���ͽ�ǰһ���ַ���д����trie�������¿�ʼ���� 
			else{
				return nullptr;
			}//���ǰһ���ַ���������Ϊ���ʽ�β����ô����Ϊ����δ֪�ĵ��� 
		}//���trie����һ��û�н��
		else {
			int p=t;//��¼trie���е�ǰһ����� 
			t=a[t].child;
			while (a[t].c!=c){
				if (a[t].brother==-1){
					if (a[p].end){
						(*newstr)[i-1]=toupper((*newstr)[i-1]);
						i--;
						t=0;
						break;
					}//���ǰһ���ַ��Ѿ�������Ϊ���ʽ�β����ô���ͽ�ǰһ���ַ���д����trie�������¿�ʼ���� 
					else{
						return nullptr;
					}
				}//�ұ���trie������һ�㣬û���ҵ���Ӧ�Ľ��
				else	t=a[t].brother;//�ҵ�ǰ���ĵܵ� 
			}					
		}
	}
	reverse(newstr);//���ַ�����ת���ָ�Ϊ���� 
	(*newstr)[0]=tolower((*newstr)[0]);//����ĸСд 
	return newstr;
}
//���ļ��м���Trie�� 
TrieNode* load(string s){
	ifstream f(s);
	int n;
	f>>n;
	TrieNode* a=new TrieNode[n];
	for (int i=0;i<n;i++){
		f>>a[i].child;
		f>>a[i].brother;
		f>>a[i].c;
		f>>a[i].end;
	}
	f.close();
	return a;
}
//��������ַ�������ʶ������������˫�����ƥ��ķ�������ʹ��BMM����ʹ��FMM�������غϷ��ı����ʽ��������������޷�ʶ��ĵ��ʣ�����nullptr  
string* bm(TrieNode* ft,TrieNode* bt,string &t){
	string s=t;
	int n=s.length();
	for (int i=0;i<n;i++){
		s[i]=tolower(s[i]);
	}//תΪСд 
	reverse(&s);
	string* ans=bmm(bt,s);
	if (ans!=nullptr)	return ans;
	reverse(&s);
	return fmm(ft,s);
}
//�������ж����ַ�������ʶ�������������Ϸ���ʽ 
int main() {
	//build_b();
	//build_f();
	ftree=load("trie_f.txt");
	btree=load("trie_b.txt");
	while (true){
		string s;
		cin>>s;
		string* temp=bm(ftree,btree,s);
		if (temp!=nullptr){
			cout<<(*temp)<<"\n";
		}
		else cout<<"Unknown Expression\n";
	}
} 

