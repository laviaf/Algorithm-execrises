#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include<time.h>

double find_Pi(int n){
    int incircle = 0, i = 0;
    for(i=0;i<n;i++){
        double x = (double)(rand() << 16 | rand())/(double)(RAND_MAX << 16 | RAND_MAX);
        double y = (double)(rand() << 16 | rand())/(double)(RAND_MAX << 16 | RAND_MAX);
        // if(i < 10){
        //     printf("%.12lf ",pow(x,2));
        //     printf("%.12lf\n", pow(y,2));
        // }
        if(pow(x-0.5,2) + pow(y-0.5,2) < 0.25){
            incircle++;
        }
    }
    double res = 4*(double)incircle/(double)n;
    return res;
}

int main(){
    long long n = 10000000;
    double delta = 0.0001;
    double error = 1;
    double mean = 0;
    int repeat = 10;
    srand(time(0));
    while(error > delta){
        n = n*10;
        printf("restart\n");
        // repeat = repeat * 10;
        mean = 0;
        double Pi_list[repeat];
        for(int i=0;i<repeat;i++){
            double Pi = find_Pi(n);
            Pi_list[i] = Pi;
            mean += Pi;
            printf("%.12lf\n",Pi);
        }
        mean = mean/(double)repeat;
        error = 0;
        for(int i=0;i<repeat;i++){
            if(abs(Pi_list[i] - mean) > error){
                error = abs(Pi_list[i] - mean);
            }
        }
        printf("%.12f\n",error);
        printf("%.12f\n",mean);
    }
    printf("The real pi is\n");
    printf("%.12f\n",mean);
}