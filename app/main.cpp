#include <iostream>
#include "../code/hypergraph.h"

int main() {
  HyperGraph sim;
  sim.atp_available = 10;

  ReceptorNode* na = sim.addReceptor(new ReceptorNode("Na_channel", Na_channel));
  ReceptorNode* k  = sim.addReceptor(new ReceptorNode("K_channel", K_channel));
  ReceptorNode* leak = sim.addReceptor(new ReceptorNode("Leak", Leak));
  PumpNode* pump = sim.addPump(new PumpNode("NaK_pump", NaK_pump));

  HyperEdge* h0 = sim.addHyperEdge(new HyperEdge("h0_active", ActiveEdge));
  h0->receptors.push_back(na);
  h0->receptors.push_back(leak);
  h0->pumps.push_back(pump);
  h0->field.NaDiff = 3;
  h0->field.KDiff = -3;

  HyperEdge* h1 = sim.addHyperEdge(new HyperEdge("h1_passive", PassiveEdge));
  h1->receptors.push_back(k);
  h1->receptors.push_back(leak);
  h1->field.NaDiff = 3;
  h1->field.KDiff = -3;

  const int N = 16;
  for (int t = 0; t < N; ++t) {
    sim.print(t);
    sim.step();
  }
  sim.print(N);

  return 0;
}
