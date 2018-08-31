#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define SIZE 100000
typedef struct node{
	char ch;
	struct node* left,right;
}node;

void check(char exp[],int pos[],int stack[],int len){
	int counter=-1,i;
	for(i=0;i<len;i++){
		if(exp[i]=='('){
			counter++;
			stack[counter]=i;
		}
		else if(exp[i]==')'){
			pos[stack[counter]]=i;
			counter--;
		}
	}
}

node* make_node(char ch){
	node* ptr=(node*)malloc(sizeof(node));
	ptr->ch=ch;
	ptr->left=NULL;
	ptr->right=NULL;
	return ptr;
}

node* make_tree(char exp[],int pos[],int first,int last,int len){
	node* s1[len],*s2[len],*ptr;
	char op[len];
	int countop=0,counts1=0,counts2=0,i=first;
	char ch='+';
	while(i<=last){
		if(exp[i]=='('){
			s1[counts1]=make_tree(exp,pos,s1,s2,op,i+1,pos[i]-1,len);
			if(ch=='*'){
				ptr=make_node('*');
				ptr->right=s1[counts1];
				counts1--;
				ptr->left=s1[counts1];
				s1[counts1]=ptr;
				countop--;
			}
			counts1++;
			i=pos[i]+1;
		}
		else if(exp[i]=='A' || exp[i]=='B'){
			s1[counts1]=make_node(exp[i]);
			if(ch=='*'){
				ptr=make_node('*');
				ptr->right=s1[counts1];
				counts1--;
				ptr->left=s1[counts1];
				s1[counts1]=ptr;
				countop--;
			}
			counts1++;
			i++;
		}
		else if(exp[i]=='*'){
			ch='*';
			op[countop]=ch;
			countop++;
			i++;
		}
		else if(exp[i]=='+'){
			ch='+';
			op[countop]=ch;
			countop++;
			i++;
		}
		else{
			ch='-';
			op[countop]=ch;
			countop++;	
			i++;
		}
	}

}

void eval(node* currptr,int result[][],int a[][],int b[][],int n){
	if(currptr->ch=='A'){
		int i,j;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				result[i][j]=a[i][j];
			}
		}
	}
	else if(currptr->ch=='B'){
		int i,j;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				result[i][j]=b[i][j];
			}
		}
	}
	else if(currptr->ch=='*'){
		int c[n][n],d[n][n];
		eval(currptr->left,c,a,b,n);
		eval(currptr->right,d,a,b,n);
		int i,j,k,sum;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				sum=0;
				for(k=0;k<n;i++){
					sum=sum+c[i][k]*d[k][j];
				}
				result[i][j]=sum;
			}
		}
	}
	else if(currptr->ch=='+'){
		int c[n][n],d[n][n];
		eval(currptr->left,c,a,b,n);
		eval(currptr->right,d,a,b,n);
		int i,j;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				result[i][j]=c[i][j]+d[i][j];
			}
		}
	}
	else if(currptr->ch=='-'){
		int c[n][n],d[n][n];
		eval(currptr->left,c,a,b,n);
		eval(currptr->right,d,a,b,n);
		int i,j;
		for(i=0;i<n;i++){
			for(j=0;j<n;j++){
				result[i][j]=c[i][j]-d[i][j];
			}
		}
	}
}

int main(){
	int n,len;
	scanf("%d",&n);
	int a[n][n],b[n][n],result[n][n];
	int i,j;
	char exp[SIZE];
	scanf("%s",exp);
	len=strlen(exp);
	int pos[len],stack[len];
	for(i=0;i<n;i++)
		pos[i]=-1;
	check(exp,pos,stack,len);
	node* s1[len],*s2[len];
	char op[len];
	node* rootptr=make_tree(exp,pos,0,len-1,len);
	eval(rootptr,result,a,b,n);
	for(i=0;i<n;i++){
		for(j=0;j<n;j++){
			printf("%d ",result[i][j]);
		}
		printf("\n");
	}
}
