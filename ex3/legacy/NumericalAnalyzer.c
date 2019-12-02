#include <stdlib.h>
#include <stdio.h>
#include "infi.h"


double f1(double x ) {
    return (double) pow(x , 2) / 4 ;
}

double f2(double x) {
  return (-pow(x,3) + 3*pow(x,2) + x - 4*sqrt(x))/(2*x*sqrt(x));
}

double f3(double x) {
  return pow(sin(x), 2) - pow(cos(x), 2);
}

double f4(double x) {
  return sin(x) / ( 1 + cos(2*x));
}

double f5(double x) {
  return exp(x);
}

double f6(double x) {
  return sinh(2*x) /( M_E * pow(x,2));
}

int main(int argc, char const *argv[]) {

  double start, end, position, eps;
  int func, parts;
  RealFunction functions[6] = { &f1, &f2, &f3, &f4, &f5, &f6 };

  if ( argc >= 7 ) {
      sscanf(argv[1], "%i",     &func);
      sscanf(argv[2], "%f",     &start);
      sscanf(argv[3], "%f",     &end);
      sscanf(argv[4], "%i",     &parts);
      sscanf(argv[5], "%f",     &position);
      sscanf(argv[6], "%f",     &eps);
      printf(" %f \n " ,  end);
      //printf("integration -> %d\n", integration(functions[func], start, end, parts));
      printf("derivative -> %d\n",  derivative(functions[func], position, eps));
  }
  /* code */
  return 0;
}
