#include<iostream>
#include<algorithm> 
#include<vector> //vector
#include <time.h> //edited by chenjb
using namespace std;

int is_great(string a,string b){ //a>,=,<b ? 1:0:-1
	if(a.size()>b.size()) return 1;
	else if(a.size()<b.size()) return -1;
	else{
		for(int i=0;i<a.size();i++){
			if(a[i]>b[i]) return 1;
			if(a[i]<b[i]) return -1;
		}
	}
	return 0;
}

string sub(string a,string b){ //a-b
    if(a==b) return "0";
	string d="";
	int flag=0; //借位标记
	int l=a.size()-b.size();
	for(int i=a.size()-1;i>=0;i--){
		char c;
		if(flag==1){
			if(a[i]=='0') a[i]='9';
			else{
				a[i]=a[i]-1; flag=0;
		    }
		}
		if(i>=l){
			if(a[i]>=b[i-l]) c=(a[i]-b[i-l])+'0';
			else{
				c=(a[i]+10-b[i-l])+'0';
				flag=1;
			}
			d+=c;
		}
		else d+=a[i];
	}
	reverse(d.begin(),d.end());
	int k=0;
	while(d[k]=='0') k++;
	return d.substr(k,d.size()-k);
}

string add(string a,string b){ //a+b
	string s="";
	if(a.size()<b.size()){
		string tmp=a;
		a=b;
		b=tmp;
	}
	int l=a.size()-b.size();
	int f=0; //进位 
	for(int i=a.size()-1;i>=0;i--){
		if(i>=l){
			int t=a[i]-'0'+b[i-l]-'0'+f;
			if(t>9){
				s+=(t-10+'0');
				f=1;
			}
			else{
				s+=(t+'0');
				f=0;
			}
		}
		else{
			if(f==1){
				if(a[i]-'0'+f>9) s+=(a[i]+f-10);
				else{
					s+=(a[i]+f); f=0;
				}
			}
			else s+=a[i];
		}
	}
	if(f==1) s+='1';
	reverse(s.begin(),s.end());
	int k=0;
	while(s[k]=='0') k++;
	return s.substr(k,s.size()-k);
}

string mul_n(string a,string b,string n){ //a*b mod n
	string p="";
	for(int i=b.size()-1;i>=0;i--){
		string p1="";
		int f=0,tb; //进位 
		tb=b[i]-'0';
		for(int j=a.size()-1;j>=0;j--){ //a的每一位和b的各位相乘 
			int tmp=tb*(a[j]-'0')+f;
			p1+=(tmp%10+'0');
			f=tmp/10;
		}
		if(f!=0) p1+=(f+'0');
		reverse(p1.begin(),p1.end());
		int k=0;
	    while(p1[k]=='0') k++;
	    p1=p1.substr(k,p1.size()-k);
	    for(int j=0;j<b.size()-1-i;j++) //左移相应位 
	        p1+='0';
	    p=add(p,p1);
	}
	int t=1;
	while(is_great(p,n)>=0){ //p mod n
		t++;
		n+='0';
	}
	while(t--){
		while(is_great(p,n)>=0)
	    	p=sub(p,n);
	    n.pop_back();
	}
	return p;
}

int main(){
	string a,n;
	cin>>a>>n;
	cout<<mul_n(a,a,n);
}
