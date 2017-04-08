#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <immintrin.h>

#include "pagerank.h"

//Index is j, check if a page has j as inlink
bool check_link(node* nodelist, int index) {
	node* tempNode = nodelist->page->inlinks;

	//Iterate over the inlinks list
	while (tempNode != NULL) {
		//Check the pages of the inlinks list, if its the same as j, means that there is an inlink
		if (tempNode->page->index == index) {
			return true;
		}

		tempNode = tempNode->next;
	}
	return false;
}


void pagerank(node* list, size_t npages, size_t nedges, size_t nthreads, double dampener) {

	double* p_matrix = (double*) calloc(npages, sizeof(double));
	double* p_new_matrix = (double*) calloc(npages, sizeof(double));
	double* matrix = (double*) calloc(npages*npages, sizeof(double));
	double* hat_matrix = (double*) calloc(npages*npages, sizeof(double));

	for (int i = 0; i < npages; i++) {
		p_matrix[i] = 1.0/(double)npages;
	}


	//Row major ftw
	node* tempNode = list;
	double value = (1.0 / (double) npages);
	for (int i = 0; i < npages; i++) {
		node* tempNode2 = list; //Compare current page (column) to the list of pages, check for inlinks
		for (int j = 0; j < npages; j++) {
			if (tempNode2->page->noutlinks == 0) {
				matrix[i*npages + j] = value;
			}
			//Check if current page (page with j index) has inlink with the other pages (from tempNode2)
			else if (check_link(tempNode, j) == true) {
				matrix[i*npages + j] = 1.0 / (double) tempNode2->page->noutlinks;
			}
			else {
				matrix[i*npages + j] = 0.0;
			}
			tempNode2 = tempNode2->next;
		}
		tempNode = tempNode->next;
	}


	//Initialise hat matrix
	for (int i = 0; i < npages*npages; i++) {
		hat_matrix[i] = dampener * matrix[i] + ((1.0 - dampener)/(double) npages);
	}

	while (1) {
		//Calculate p_new_matrix
		for (int i = 0; i < npages; i++) {
			p_new_matrix[i] = 0.0; //Reset value
			for (int j = 0; j < npages; j++) {
				p_new_matrix[i] += hat_matrix[i*npages+j] * p_matrix[j];
			}
		}

		double vector_norm = 0.0;

		//Calculate vector norm
		for (int i = 0; i < npages; i++) {
			vector_norm += pow((p_new_matrix[i] - p_matrix[i]), 2);
		}

		tempNode = list;
		if (sqrt(vector_norm) <= EPSILON) {
			for (int i = 0; i < npages; i++) {
				printf("%s %.8lf\n", tempNode->page->name, p_new_matrix[i]);
				//fprintf(stderr, "%s %.8lf\n", tempNode->page->name, p_new_matrix[i]);
				tempNode = tempNode->next;
			}
			free(p_new_matrix);
			free(p_matrix);
			free(hat_matrix);
			free(matrix);
			return;
		}

		//If its not lower than convergence, keep repeating, so save the new values of p new matrix into the old p matrix
		for (int i = 0; i < npages; i++) {
			p_matrix[i] = p_new_matrix[i];
		}
	}
}

/*
######################################
### DO NOT MODIFY BELOW THIS POINT ###
######################################
*/

int main(int argc, char** argv) {

	/*
	######################################################
	### DO NOT MODIFY THE MAIN FUNCTION OR HEADER FILE ###
	######################################################
	*/

	config conf;

	init(&conf, argc, argv);

	node* list = conf.list;
	size_t npages = conf.npages;
	size_t nedges = conf.nedges;
	size_t nthreads = conf.nthreads;
	double dampener = conf.dampener;

	pagerank(list, npages, nedges, nthreads, dampener);

	release(list);

	return 0;
}
