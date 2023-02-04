#include <iostream>
#include <vector>
#include <random>
#include <algorithm>

 const int NUM_CITIES = 5;

const int NUM_ITERATIONS = 100;

const float MUTATION_RATE = 0.1;

 
struct Solution
{
  
std::vector < int >path;
   
int fitness;
 
};

 
// Calculate the fitness of a solution (the total distance of the path)
  int
calculateFitness (const Solution & s,
		  const std::vector < std::vector < int >>&distances)
{
  
int fitness = 0;
  
for (int i = 0; i < NUM_CITIES - 1; i++)
    {
      
fitness += distances[s.path[i]][s.path[i + 1]];
    
} 
fitness += distances[s.path[NUM_CITIES - 1]][s.path[0]];
  
return fitness;

}


 
// Generate a random initial solution
  Solution generateInitialSolution (std::mt19937 & rng)
{
  
Solution s;
  
std::vector < int >cities (NUM_CITIES);
  
std::iota (cities.begin (), cities.end (), 0);
  
std::shuffle (cities.begin (), cities.end (), rng);
  
s.path = cities;
  
return s;

}


 
// Select two solutions from a population
  void
selectSolutions (const std::vector < Solution > &population, Solution & s1,
		 Solution & s2)
{
  
std::uniform_int_distribution < int >dist (0, NUM_CITIES - 1);
  
int i1 = dist (rng);
  
int i2 = dist (rng);
  
while (i2 == i1)
    {
      
i2 = dist (rng);
    
}
  
s1 = population[i1];
  
s2 = population[i2];

}


 
// Generate two offspring from two solutions using improved greedy crossover
  void
improvedGreedyCrossover (const Solution & s1, const Solution & s2,
			 Solution & o1, Solution & o2,
			 const std::vector < std::vector < int >>&distances)
{
  
    // Copy the paths from the parents
    o1.path = s1.path;
  
o2.path = s2.path;
  
    // Choose two random cities
  std::uniform_int_distribution < int >dist (0, NUM_CITIES - 1);
  
int c1 = dist (rng);
  
int c2 = dist (rng);
  
while (c2 == c1)
    {
      
c2 = dist (rng);
    
}
  
    // Swap the cities in the offspring paths
    std::swap (o1.path[c1], o1.path[c2]);
  
std::swap (o2.path[c1], o2.path[c2]);
  
    // Evaluate the fitness of the offspring
    o1.fitness = calculateFitness (o1, distances);
  
o2.fitness = calculateFitness (o2, distances);
  
 
 
 
    // Use improved greedy crossover to improve the offspring solutions
    for (int i = 0; i < NUM_CITIES; i++)
    {
      
if (o1.path[i] == s1.path[c1])
	{
	  
int j = (i + 1) % NUM_CITIES;
	  
while (o1.path[j] != s2.path[c2])
	    {
	      
int k = (j + 1) % NUM_CITIES;
	      
if (distances[o1.path[i]][o1.path[j]] +
		   distances[o1.path[j]][o1.path[k]] -
		   distances[o1.path[i]][o1.path[k]] < 0)
		{
		  
std::swap (o1.path[j], o1.path[k]);
		  
j = k;
		
}
	      else
		{
		  
break;
		
}
	    
}
	
}
      
if (o2.path[i] == s2.path[c2])
	{
	  
int j = (i + 1) % NUM_CITIES;
	  
while (o2.path[j] != s1.path[c1])
	    {
	      
int k = (j + 1) % NUM_CITIES;
	      
if (distances[o2.path[i]][o2.path[j]] +
		   distances[o2.path[j]][o2.path[k]] -
		   distances[o2.path[i]][o2.path[k]] < 0)
		{
		  
std::swap (o2.path[j], o2.path[k]);
		  
j = k;
		
}
	      else
		{
		  
break;
		
}
	    
}
	
}
    
}
  
    // Recalculate the fitness of the offspring
    o1.fitness = calculateFitness (o1, distances);
  
o2.fitness = calculateFitness (o2, distances);

}


 
// Mutate a solution by swapping two random cities
  void
mutate (Solution & s)
{
  
std::uniform_int_distribution < int >dist (0, NUM_CITIES - 1);
  
int c1 = dist (rng);
  
int c2 = dist (rng);
  
while (c2 == c1)
    {
      
c2 = dist (rng);
    
}
  
std::swap (s.path[c1], s.path[c2]);

}


 
int
main ()
{
  
    // Seed the random number generator
    std::mt19937 rng (std::random_device
		      {
		      } ());
  
    // Initialize the population
    std::vector < Solution > population (NUM_CITIES);
  
for (int i = 0; i < NUM_CITIES; i++)
    {
      
population[i] = generateInitialSolution (rng);
      
population[i].fitness = calculateFitness (population[i], distances);
    
} 
    // Run the IGC algorithm
    for (int iteration = 0; iteration < NUM_ITERATIONS; iteration++)
    {
      
Solution s1, s2, o1, o2;
      
selectSolutions (population, s1, s2);
      
improvedGreedyCrossover (s1, s2, o1, o2, distances);
      
if (o1.fitness < s1.fitness)
	{
	  
mutate (o1);
	}
      
if (o2.fitness < s2.fitness)
	{
	  
mutate (o2);
	
}
      
	// Replace the worst solutions in the population with the offspring
	std::sort (population.begin (), population.end (),
		   [](const Solution & a, const Solution & b)
		   {
		   
return a.fitness < b.fitness;
		   
}
      );
      
population[NUM_CITIES - 1] = o1;
      
population[NUM_CITIES - 2] = o2;
    
}
  
// Print the best solution
    Solution best = population[0];
  
for (int i = 1; i < NUM_CITIES; i++)
    {
      
if (population[i].fitness < best.fitness)
	{
	  
best = population[i];
	
}
    
}
  
std::
    cout << "Best solution found after " << NUM_ITERATIONS << " iterations: "
    << best.fitness << std::endl;
  
return 0;

}


 
 
