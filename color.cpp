#include<stdio.h>
#include<stdlib.h>
#include<iostream>
using namespace std;
typedef struct Node{
	int num;
	int list[10];
}node;

int main(){
	node *n1;
	n1 = (node *)malloc(sizeof(node));
	n1->num = 5;
	for (int i=0;i<10;i++){
		n1->list[i] = i;
	}

	cout << n1->num << "\n";
	for (int i=0;i<10;i++)
		cout << n1->list[i] << "\n";
	free(n1);
	return 0;
}
