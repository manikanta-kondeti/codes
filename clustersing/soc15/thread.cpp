#include<iostream>
#include<thread>

using namespace std;

void thread_function(){
	cout << "Thread Function\n";
}
int main(){
	thread t(&thread_function); 
	cout << "Main thread\n";
	t.join();
	return 0;
}
