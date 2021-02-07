#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#define SIZE 100



typedef struct Graph {
	int num;
	int** matrix;
	int* visited;

}Graph;

typedef struct Queue {
	int items[SIZE];
	int  front;
	int rear;
}Queue;

Queue* Make_Queue() {
	Queue* new = (Queue*)malloc(sizeof(Queue));
	new->front = -1;
	new->rear = -1;
	return new;
}

void inQueue(Queue* queue, int data) {
	if (isFull(queue)) {
		return;
	}
	else {
		if (queue->front == -1) {
			queue->front = 0;
		}
		queue->rear++;
		queue->items[queue->rear] = data;
	}

}

int outQueue(Queue* queue) {
	int item = 0;
	if (isEmpty(queue)) 
	return;
	
	else
	{
		
		item = queue->items[queue->front];
		
		queue->front++;

		if (queue->front > queue->rear) {
			queue->front = -1;
			queue->rear = -1;

		}
		
	}
	

	return item;
}

int isEmpty(Queue* queue) {
	if (queue->rear == -1)
		return 1;
	else
		return 0;
}

int isFull(Queue* queue) {
	if (queue->front == 0 && queue->rear == SIZE - 1)
		return 1;
	else
		return 0;
}


void DFS(Graph* graph, int vertex) {

	graph->visited[vertex] = 1;
	printf("%d", vertex + 1);
	
	
	for (int i = 0; i < graph->num; i++) {
		if (graph->matrix[vertex][i] == 1 && graph->visited[i] == 0) {
			printf(" -> ");
			DFS(graph, i);
		}
	}
}

void returnvisitedzero(Graph* graph) {
	for (int i = 0; i < graph->num; i++) {
		graph->visited[i] = 0;
	}
}

void BFS(Graph* graph, int vertex) {
	

	Queue* queue = Make_Queue();
	int i = 0;

	inQueue(queue, vertex);
	
	printf("%d", vertex + 1);
	graph->visited[vertex] = 1;
	

	while (!isEmpty(queue)) {
		vertex = outQueue(queue);
		
		

		for (i = 0; i < graph->num; i++) {   
			
			if (!graph->visited[i] && graph->matrix[vertex][i] == 1) {
				graph->visited[i] = 1;
				inQueue(queue, i);
				printf(" -> %d", i + 1);
			}
		}
	}
}



Graph* Make_Graph(int num) {
	
	Graph* graph = (Graph*)malloc(sizeof(Graph) * num);
	graph->matrix = (int**)malloc(sizeof(int*) * num);
	graph->visited = (int*)malloc(sizeof(int) * num);
	
	graph->num = num;

	for (int i = 0; i < num; i++) {
		graph->matrix[i] = (int*)malloc(sizeof(int) * num);
		memset(graph->matrix[i], 0, sizeof(int) * num);
		graph->visited[i] = 0;

	}

	return graph;
}

void Add_Edge(Graph* graph, int start, int end) {
	

	graph->matrix[start][end] = 1;

}

int main() {
	
	int number;
	char buffer[100];
	Graph* graph[10];
	int n;
	int graphnumber = 0;

	FILE* fp = fopen("input.txt", "r");

	

	while (!feof(fp)) {
		int start = 1;

		fscanf(fp, "%d", &number);
		fgets(buffer, sizeof(buffer), fp);
		
		graph[graphnumber] = Make_Graph(number);

		

			while (number) {
				
				fgets(buffer, sizeof(buffer), fp);


				n = 2;

				while (buffer[n] != NULL) {
					
					Add_Edge(graph[graphnumber], start - 1, atoi(&buffer[n]) - 1);
					n += 2;
				}
				

				


				number--;
				start++;

			}
			

			

			graphnumber++;

		

		}

	for (int i = 0; i < graphnumber - 1 ; i++) {
		printf("±×·¡ÇÁ [%d]\n", i + 1);
		printf("====================\n±íÀÌ ¿ì¼± Å½»ö\n");
		DFS(graph[i], 0);
		printf("\n");
		returnvisitedzero(graph[i]);
		printf("³Êºñ ¿ì¼± Å½»ö\n");
		BFS(graph[i], 0);
		printf("\n====================\n\n");
		
	}

	

	
	

	

	fclose(fp);

	return 0;

	}

