#include "hypergraph.h"
#include <iostream>

ReceptorNode* HyperGraph::addReceptor(ReceptorNode* receptor) {
  if (receptor) {
    receptors.push_back(receptor);
  }
  return receptor;
}

PumpNode* HyperGraph::addPump(PumpNode* pump) {
  if (pump) {
    pumps.push_back(pump);
  }
  return pump;
}

HyperEdge* HyperGraph::addHyperEdge(HyperEdge* edge) {
  if (edge) {
    hyperedges.push_back(edge);
  }
  return edge;
}

void HyperGraph::step() {
  for (HyperEdge* edge : hyperedges) {
    if (!edge) {
      continue;
    }

    GradientField delta;
    // read local edge state and update receptor/pump states
    for (ReceptorNode* receptor : edge->receptors) {
      if (!receptor) continue;
      receptor->updateState(edge->field);
    }
    for (PumpNode* pump : edge->pumps) {
      if (!pump) continue;
      pump->updateState(atp_available);
    }
    // get passive channel contribution to equilibrium
    for (ReceptorNode* receptor : edge->receptors) {
      if (!receptor || receptor->state != Open) continue;

      if (receptor->kind == Na_channel) {
        if (edge->field.NaDiff > 0) delta.NaDiff -= 1;
        else if (edge->field.NaDiff < 0) delta.NaDiff += 1;
      } else if (receptor->kind == K_channel) {
        if (edge->field.KDiff > 0) delta.KDiff -= 1;
        else if (edge->field.KDiff < 0) delta.KDiff += 1;
      } else if (receptor->kind == Leak) {
        if (edge->field.NaDiff > 0) delta.NaDiff -= 1;
        else if (edge->field.NaDiff < 0) delta.NaDiff += 1;

        if (edge->field.KDiff > 0) delta.KDiff -= 1;
        else if (edge->field.KDiff < 0) delta.KDiff += 1;
      }
    }
    //add active pump contribution on active edges
    if (edge->kind == ActiveEdge) {
      for (PumpNode* pump : edge->pumps) {
        if (!pump || pump->state != Active) continue;
        if (pump->kind == NaK_pump) {
          delta.NaDiff += 1;
          delta.KDiff -= 1;
        }
      }
    }
    // apply accumulated delta to this edge's field
    edge->field.NaDiff += delta.NaDiff;
    edge->field.KDiff += delta.KDiff;
    // consume ATP if an active NaK pump ran
    if (edge->kind == ActiveEdge) {
      for (PumpNode* pump : edge->pumps) {
        if (!pump) continue;
        if (pump->kind == NaK_pump && pump->state == Active && atp_available > 0) {
          atp_available -= 1;
          break;
        }
      }
    }

    edge->field.clamp();
  }
}

void HyperGraph::print(int tick_index) {
  std::cout << "tick " << tick_index;
  for (HyperEdge* edge : hyperedges) {
    if (!edge) {
      continue;
    }
    std::cout << " " << edge->id
              << " NaDiff=" << edge->field.NaDiff
              << " KDiff=" << edge->field.KDiff;
  }
  std::cout << " ATP=" << atp_available << std::endl;
}

