#include <stdio.h>

int main(int argc, char** argv){
  int i = 1; 
  for(; i < argc; i++)
    unlink(argv[i]);
}