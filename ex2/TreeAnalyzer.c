#ifndef HEADERS
#include "headers.h"
#endif

int main(int argc, char const *argv[]) {


  if ( argc > 1 ) {

     Node** graph = parsing_file( argv[1] );
     Node * root = getRoot(graph[0]);
     printf("root-key : %i\n", root->key);

     int u , v;

     sscanf(argv[2], "%d", &u);
     sscanf(argv[3], "%d", &v);
     // printf("u: : %i\n", u);
     // printf("v: : %i\n", v);
     print_path(graph[u], graph[v], 8);
     printf(" max height -> %i \n", maxHeight(root));
     printf(" min height -> %i \n", minHeight(root));
     printf(" number of vertax -> %i\n", getNodes(root));
     printf(" number of edges -> %i\n", getNodes(root) - 1);
     printf(" diameter of the tree -> %i\n", getDiameter(root));
  }




  return 0;
}
