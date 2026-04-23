#include <iostream>
#include <string>

#include "hypergraph.h"

int main() {
  HyperGraph sim;
  sim.atp_available = 10;

  ReceptorNode* na = sim.addReceptor(new ReceptorNode("Na_channel", Na_channel));
  ReceptorNode* k = sim.addReceptor(new ReceptorNode("K_channel",  K_channel));
  ReceptorNode* leak = sim.addReceptor(new ReceptorNode("Leak",       Leak));
  PumpNode* pump = sim.addPump(new PumpNode("NaK_pump", NaK_pump));

  HyperEdge* h0 = sim.addHyperEdge(new HyperEdge("h0_active", ActiveEdge));
  h0->receptors.push_back(na);
  h0->receptors.push_back(leak);
  h0->pumps.push_back(pump);
  h0->field.NaDiff = 3;
  h0->field.KDiff  = -3;

  HyperEdge* h1 = sim.addHyperEdge(new HyperEdge("h1_passive", PassiveEdge));
  h1->receptors.push_back(k);
  h1->receptors.push_back(leak);
  h1->field.NaDiff = 3;
  h1->field.KDiff  = -3;

  std::cout << "test 1: wiring\n";
  bool h0_has_leak = false;
  for (ReceptorNode* r : h0->receptors) {
    if (r == leak) {
      h0_has_leak = true;
      break;
    }
  }
  bool h1_has_leak = false;
  for (ReceptorNode* r : h1->receptors) {
    if (r == leak) {
      h1_has_leak = true;
      break;
    }
  }
  bool leak_wiring_ok = h0_has_leak && h1_has_leak;
  std::string leak_wiring_text;
  if (leak_wiring_ok) {
    leak_wiring_text = "yes";
  } else {
    leak_wiring_text = "no";
  }
  std::cout << "  Leak appears in h0_active and h1_passive: "
            << leak_wiring_text << "\n\n";

  std::cout << "test 2: steps\n";
  const int N = 16;
  for (int t = 0; t < N; ++t) {
    sim.print(t);
    sim.step();
  }
  sim.print(N);

  std::cout << "\ntest 3: final\n";
  std::cout << "  ATP_available=" << sim.atp_available << "\n";
  std::cout << "  h0_active  NaDiff=" << h0->field.NaDiff << " KDiff=" << h0->field.KDiff << "\n";
  std::cout << "  h1_passive NaDiff=" << h1->field.NaDiff << " KDiff=" << h1->field.KDiff << "\n";

  return 0;
}

