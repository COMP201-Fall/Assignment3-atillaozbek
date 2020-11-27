/* This is a code for COMP 201 assignment 3.
 * In this code, Floyd-Warshall algorithm is implemented
 * to find the shortest paths between any two cities
 * in a given graph of cities.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int INF = 1e7;  
int insert_to_cities(char str[30]);
int lookup_string(char str[30]);

/* Array of vertices. 
 * Each element of the str array contains a city name and 
 * its index in str becomes the city's numeric id.
 */
typedef struct vertices 
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of cities in the array
	int city_count;
	// This attribute is the array of city names
	char (* str)[30];
} 
vertices;

/* Array of edges. 
 * Each element of the edge array contains the ids of two cities 
 * connected directy by a road and the length of the road.
 */
typedef struct edges 
{
	// This attribute shows the size of dynamically allocated memory
	int size;
	// This attribute shows the number of roads in the array
	int edge_count;
	// This attribute is the array of road information
	int (* edge)[3];
} 
edges;

vertices cities;

edges roads;

/* A two-dimensional array that shows 
 * the length of the shortest path connecting 
 * any two cities.
 */
int **city_graph;

/* A two-dimensional array that shows the direction 
 * to the shortest path between any two cities.
 */
int **shortest_paths;

/* A function that implements Floyd-Warshall algorithm. 
 * This algorithm finds the shortest path between 
 * any two vertices in a given graph.
 */
void floydWarshall()  
{  
	for (int k = 0; k < cities.city_count; k++) 
	{  
		for (int i = 0; i < cities.city_count; i++) 
		{  
			for (int j = 0; j < cities.city_count; j++) 
			{  
				// We cannot cross a road that doesn't exist  
				if ((city_graph[i][k] == INF) || (city_graph[k][j] == INF))  
				{
					continue;
				}  
				if (city_graph[i][j] > (city_graph[i][k] + city_graph[k][j])) 
				{  
					city_graph[i][j] = city_graph[i][k] + city_graph[k][j];  
					shortest_paths[i][j] = shortest_paths[i][k];  
				}  
			}  
		}  
		
	}  
	
} 

/* A function that initializes the values in 
 * city_graph and shortest_paths arrays.
 */
void initialise()  
{  
	for (int i = 0; i < cities.city_count; i++) 
	{  
		for (int j = 0; j < cities.city_count; j++) 
		{    

			// No edge between node i and j  
			if (city_graph[i][j] == INF)  
			{
				shortest_paths[i][j] = -1;
			}  
			else
			{
				shortest_paths[i][j] = j;
			}  
		}  
	}  
}

/* A function that inserts the name of a new city 
 * to the cities array.
 */
int insert_to_cities(char str[30]) 
{
	int isExist = lookup_string(str);  
	if(isExist == -1){				
		if(cities.city_count == 0){		
			strcpy(cities.str[0],str);		
			cities.city_count++;
			return (cities.city_count)-1;
		}
		else{						
			if(cities.size == cities.city_count){		
				cities.size = cities.size*2;		
				cities.str = realloc(cities.str, cities.size*sizeof(*cities.str));
				strcpy(cities.str[cities.city_count],str);	
				cities.city_count++;
				return (cities.city_count)-1;
			}
			else{				
				strcpy(cities.str[cities.city_count],str);
				cities.city_count++;
				return (cities.city_count)-1;
			}
		}
	}
	else{		
		return isExist;		
	}
	
	// Write your code here
	// Check if the city name already exists in the array 
	// If it does, return the array index of the city 

	// If the city name doesn't exist, it is inserted to the vertex array, and
	// return the array index of the city

	// If the dynamically allocated size of vertex_array is not large enough, 
	// vertex_array is enlarged and the city name is inserted 
	// to the newly added region

	// Return the array index of the city.
	return 0;
}

/* A function that looks up if a city name
 * is already in the cities array. 
 */
int lookup_string(char str[30]) 
{
	for(int i = 0; i < cities.city_count; i++) {
		if(strncmp(str, cities.str[i], 30) == 0)
			return i;
	}
	printf("city %s is not found\n", str);
	return -1;
}



/*
* This function prints shortest path lenght between taken any city, and also prints shortest path
* If there is no path between taken cities, function prints NO PATH***
* If user gives same cities, function prints same cities with lenght 0
* @int u = First city
* @int v = Second city
*/


void printPath(int u, int v)  
{  
	printf("Output:\n");
	int temp = city_graph[u][v];
	if(city_graph[u][v] == INF){
		printf("***NO PATH***\n");
	}
	else if(u == v){
		printf("same cities, 0\n");
	}
	else{   
		if(u>v){  
			printf("%s ",cities.str[u]);
			int tempU = u;
			if(shortest_paths[u][v] != v){  
				while(shortest_paths[u][v] != shortest_paths[v][tempU]){ 
					printf("%s ",cities.str[shortest_paths[u][v]]);
					u = shortest_paths[u][v];
				}
				printf("%s %s",cities.str[shortest_paths[u][v]],cities.str[v]);
			}
			else{   
				printf("%s",cities.str[v]);
			}
		}
		else{
			printf("%s ",cities.str[u]);
			int tempU = u;
			if(shortest_paths[u][v] != v){ 
				while(shortest_paths[u][v] != shortest_paths[v][tempU]){  
					printf("%s ",cities.str[shortest_paths[u][v]]);
					u = shortest_paths[u][v];
				}
				printf("%s %s",cities.str[shortest_paths[u][v]],cities.str[v]);
			}
			else{    
				printf("%s",cities.str[v]);
			}
				
			
		}
		
		printf("\n");
		printf("%d\n",temp);
	}
	
	
} 

int main(int argc, char *argv[])
{

	FILE *fp = fopen(argv[1], "r");  
	char city1[20];				
	char city2[20];              
	int lenght;					
	cities.size = 2;			
	roads.size = 1;				
	int cityId1;				
	int cityId2;
	
	// dynamicly allocating array of cities.str with size of cities.size which will be reallocated once there will be more cities to handle
	cities.str = malloc(cities.size*sizeof(*cities.str));
	// dynamicly allocating array of roads.edge with size of roads.size which will be reallocated once there will be more cities to handle
	roads.edge = malloc(roads.size*sizeof(*roads.edge));
	cities.city_count = 0;    
	roads.edge_count = 0;		
	
	while(fscanf(fp,"%s %s %d",city1,city2,&lenght)>0){
		cityId1=insert_to_cities(city1);		
     	cityId2=insert_to_cities(city2);		
     	if(roads.edge_count == 0){  
     		roads.edge[0][0] = cityId1; 
     		roads.edge[0][1] = cityId2;
     		roads.edge[0][2] = lenght;
     		roads.edge_count++;
		}
		else{
			if(roads.size == roads.edge_count){   
				roads.size = roads.size*2;
				roads.edge = realloc(roads.edge, roads.size*sizeof(*roads.edge));
				roads.edge[roads.edge_count][0] = cityId1;
				roads.edge[roads.edge_count][1] = cityId2;
				roads.edge[roads.edge_count][2] = lenght;
				roads.edge_count++;
			}
			else{                                  
				roads.edge[roads.edge_count][0] = cityId1;
				roads.edge[roads.edge_count][1] = cityId2;
				roads.edge[roads.edge_count][2] = lenght;
				roads.edge_count++;
			}
		 	
		}
	}

	


	int i = 0; 
	city_graph = malloc(cities.city_count*sizeof(int*));
	for(i = 0;i<cities.city_count;i++){
		city_graph[i] = malloc(cities.city_count*sizeof(int));
	}
	i = 0;
	int j = 0;
	for(i=0;i<cities.city_count;i++){
		for(j=0;j<cities.city_count;j++){
			city_graph[i][j] = 0;
		}
	}
	
	
	for(i = 0;i<roads.edge_count;i++){
		int tempi = roads.edge[i][0];
		int tempy = roads.edge[i][1];
		city_graph[tempi][tempy] = roads.edge[i][2];
	}

	for(i=0;i<cities.city_count;i++){
		for(j=0;j<cities.city_count;j++){
			if(city_graph[i][j]>0){
				city_graph[j][i] = city_graph[i][j];
			}
		}
	}
    	
	
	for(i = 0;i<cities.city_count;i++){
		for(j=0;j<cities.city_count;j++){
			if(city_graph[i][j] == 0){
				city_graph[i][j] = INF;
			}
		}
	}
	
	for(i=0;i<cities.city_count;i++){
		city_graph[i][i] = 0;
	}
	
	shortest_paths = malloc(cities.city_count*sizeof(int*));
	for(i = 0;i<cities.city_count;i++){
		shortest_paths[i] = malloc(cities.city_count*sizeof(int));
	}
	
	
	
	initialise();
	
	
	floydWarshall();

	// taking inputs from user
	while(1) {
		char cityInput1[30];
		char cityInput2[30];
		int tempId1=-5;
		int tempId2=-5;
		printf("Enter the cities:\n");
		scanf("%s %s",cityInput1,cityInput2); 
		int i=0;		
		for(i=0;i<cities.city_count;i++){	
			if(strncmp(cityInput1, cities.str[i], 30) == 0){
				tempId1 = i;
			}
		}
		for(i=0;i<cities.city_count;i++){  
			if(strncmp(cityInput2, cities.str[i], 30) == 0){
				tempId2 = i;
			}
		}		
		
		if((tempId1 == -5) | (tempId2 == -5)){

			printf("invalid city or cities\n");
		}
		else{	
			printPath(tempId1,tempId2);
		}
	}
	
	// freeing memory
	free(shortest_paths);
	free(city_graph);
	free(roads.edge); 
	free(cities.str);
	fclose(fp);  
	return 0;	
}
