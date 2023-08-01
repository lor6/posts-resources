/* 
 * simple univariate linear regression model in C++ 
 */

// This header file contains all C++ libraries needed for stdio i/o and bit operation
//#include <bits/stdc++.h>  
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

// Defining native  namespace 
using namespace std;

struct error_storage{
    double error;
    double bias;
    double slope;
 
    /*bool operator>(const error_storage& err){
        return error>err.error;
    }
    bool operator<(const error_storage& err){
        return error<err.error;
    }*/
};

/* This function sorts a, and b based on the MAD (minimal absolute difference) */
bool sort_by_mad(error_storage a, error_storage b){
    double a1=abs(a.error-0);
    double b1=abs(b.error-0);
    if (a1<b1)
        return true;
    else 
        return false;
}


int main(){
    /* Input Dataset X */
    double x[] = {1, 2, 3, 4, 5};   
    /* Input Target Y */
    double y[] = {1, 3, 3, 2, 5};    

    // array to store all error values
    vector<error_storage>errors;   
    //error deviation equivalent to gradient          
    double error=0.0;

    //initializing bias
    double bias = 0; 
    //initializing intercept                  
    double slope = 0;  
    //initializing learning rate                 
    double learn_rate = 0.01;             
    
    //Initialise number of epoch
    int epoch = 20;

    /* We train our model by fitting our input set - Training Phase*/
    for (int i = 0; i < epoch; i++) {
        int x_size = sizeof(x)/sizeof(x[0]);
        for (int j = 0; j < x_size; j++) {   
            cout<<"Epoch: "<<i+1<<" Input sample: "<<j+1<<"/"<<x_size<<" Before update "<<"Bias="<<bias<<" "<<"Slope="<<slope<<" "<<"Error="<<error<<endl;
            int index = j % x_size;            
            
            // Pedict target 
            double y_pred = bias + slope * x[index];  
            
            // Calcaulte error
            error = y_pred - y[index];              
            
            // Update bias
            bias = bias - learn_rate * error;         
            
            // Update slope
            slope = slope - learn_rate * error * x[index];

            //get absolute value
            error = fabs(error);
            cout<<"Epoch: "<<i+1<<" Input sample: "<<j+1<<"/"<<x_size<<" After update "<<"Bias="<<bias<<" "<<"Slope="<<slope<<" "<<"Error="<<error<<endl;            

            // Store eror, bias and slope     
            error_storage tmp = {error, bias, slope}; 
            errors.push_back(tmp);
        }
        cout<<endl;
    }

    // sort the error, bias, and slope to get optimal value for prediction
    sort(errors.begin(),errors.end(), sort_by_mad);
    double error_opt = errors[0].error;
    double bias_opt = errors[0].bias;
    double slope_opt = errors[0].slope;

    cout<<"Optimal end values are: "<<"Bias="<<bias_opt<<" "<<"Slope="<<slope_opt<<" "<<"error="<<error_opt<<endl;

    /* Test the model on an unseen data point - Testing Phase*/
    cout<<"Enter a test x value: ";
    double x_test;
    cin>>x_test;
    double y_pred=bias_opt+slope_opt*x_test;
    cout<<endl;
    cout<<"The value predicted by the model for " <<x_test<<" = "<<y_pred;
}
