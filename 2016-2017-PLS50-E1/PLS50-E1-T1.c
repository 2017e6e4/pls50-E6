// This is a very basic calculator

#include <stdio.h>
#include <stdlib.h>

int main(){
    // Variables Declarations
    float a, b, result;
    char oper;

    printf("Please insert a number then one of the 4 following operators +,-,*,/ and then a second number all separated by spaces:\n");
    scanf("%f %c %f", &a,&oper,&b);

    if (oper == "+"){
        result = a+b;
    }
    else if (oper == "-"){
        result = a-b;
        printf("The result is:", result);
    }
    else if (oper == "*"){
        result = a*b;
        printf("The result is:", result);
    }
    else if ((oper == "/") && (b != 0)){
        result = a/b;
        printf("The result of adding is:", result);
    }
    else if ((oper == "/") && (b == 0)){
        printf("You are trying to divide by zero. You know this is not possible. Please try again");
    }
    else {
        printf("Error. The operator you used is not among the 4 suggested operators. Please insert exclusively one of the following 4 operators: +, -, *, / \n");
    }
    return 0;
}
