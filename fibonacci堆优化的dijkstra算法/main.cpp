#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdlib.h>
#include "fibonacci_heap.h"
#include "fibonacci_heap.cpp"
#include<algorithm>
using namespace std;

bool cmp(int a[2], int b[2]){
	return a[0] <= b[0];
}

template <typename T>
void do_operation(char opt, int node, int value, FibHeap<T>* Tree, T* min_value){
    if(opt == 'I'){
        Tree->insert(value,node);
    }
    else if(opt == 'D'){
        Tree->update(node,value);
    }
    else if(opt == 'E'){
        Tree->extractMin(min_value);
    }
    else{
        cout << "Error! invalid operation." << endl;
    }
}

int main(){
    FibHeap<int>* Tree = new FibHeap<int>{};
    //读入文件
    ifstream in("man_seq.txt");
	string filename;
	string line;
    //储存结果
    int ** fib_res = new int*[200000];
    for(int i=0;i<200000;i++){
        fib_res[i] = new int[2];
    }
    int count = 0;
 
	if(in) // 有该文件，使用fibonacci堆操作
	{
		while (getline (in, line)) // line中不包括每行的换行符
		{ 
            //储存最终分割而得字符串
            vector<string> res;
            string result;
            stringstream input(line);
            while(input>>result){
                res.push_back(result);
            }
			char opt = res[0].c_str()[0];
            int node,value;
            if(opt == 'E'){
                node = 0;
                value = 0;
            }
            else{
                node = atoi(res[1].c_str());
                value = atoi(res[2].c_str());
            }

            //储存结果
            int min_value[2];
            do_operation(opt,node,value,Tree,min_value);
            if(opt == 'E'){
                fib_res[count][0] = min_value[0];
                fib_res[count][1] = min_value[1];
                count += 1;
                cout<<count<<endl;
            }
		}
	}
	else // 没有该文件
	{
		cout <<"no such file" << endl;
	}

    //将结果排序
    sort(fib_res,fib_res+200000,cmp);

    //写入文件
    fstream outfile;
    outfile.open("./fibonacci_res.txt",ios::out);
    if(!outfile){
        cout<<"file can not open"<<endl;
        abort();
    }
    for(int i=0;i<200000;i++){
        outfile<< fib_res[i][0] << " " << fib_res[i][1] << endl;
    }

    outfile.close();
}