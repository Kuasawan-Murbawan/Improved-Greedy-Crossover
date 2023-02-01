void improvedGreedyCrossover(const Solution &p1, const Solution &p2, Solution &o) {
  greedyCrossover(p1, p2, o);
  int numImprovements = 0;
  double currentFitness = o.fitness;
  while (numImprovements < MAX_IMPROVEMENTS) {
    int i = rand() % NUM_CITIES;
    int j = rand() % NUM_CITIES;
    std::swap(o.route[i], o.route[j]);
    o.fitness = calculateFitness(o.route);
    if (o.fitness < currentFitness) {
      numImprovements++;
      currentFitness = o.fitness;
    } else {
      std::swap(o.route[i], o.route[j]);
    }
  }
}

