void greedyCrossover(const Solution &p1, const Solution &p2, Solution &o) {
  int currentCity = 0;
  std::vector<bool> assigned(NUM_CITIES, false);
  for (int i = 0; i < NUM_CITIES; i++) {
    if (i % 2 == 0) {
      o.route[i] = p1.route[currentCity];
    } else {
      o.route[i] = p2.route[currentCity];
    }
    assigned[o.route[i]] = true;
    int nextCity = -1;
    for (int j = 0; j < NUM_CITIES; j++) {
      if (!assigned[j]) {
        if (nextCity == -1) {
          nextCity = j;
        } else {
          double d1 = distance(o.route[i], j);
          double d2 = distance(o.route[i], nextCity);
          if (d1 < d2) {
            nextCity = j;
          }
        }
      }
    }
    currentCity = nextCity;
  }
}