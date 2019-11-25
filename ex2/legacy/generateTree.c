#ifndef HEADERS
#include "headers.h"
#endif

char peek_file(FILE *fp) {
		char ret = getc(fp);
		ungetc(ret, fp);
		return ret;
}

int connectable(int perent, int children, int n){
	return children < n && children >= 0 && children != perent;
}


Node ** parsing_file(const char * path) {
   FILE *fp;
   char buff[255];

   fp = fopen(path, "r");

   int n;
   fscanf (fp, "%i", &n);

   Node ** nodes = malloc( sizeof(Node *) * n );
   for (int i = 0 ; i < n; i++) {
      nodes[i] = allocNode(i);
   }
	getc(fp);
	int perent = 0 , children;
	while(peek_file(fp) != EOF) {
		while(peek_file(fp) != '\n' && peek_file(fp) != '-') {
			fscanf (fp, "%i", &children);
			if (connectable( perent, children, n))
				connectEdge(nodes[perent], nodes[children]);
		}
		if (peek_file(fp) == '-')
			getc(fp);
		getc(fp);
		perent++;
   }

   // for (List * ptr = nodes[0]->edges; ptr->next != NULL; ptr= ptr->next) {
	// 	printf("%i\n",ptr->node->key);
	// }

   fclose (fp);

	return nodes;
}
