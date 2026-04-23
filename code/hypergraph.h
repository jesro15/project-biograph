#ifndef HYPERGRAPH_H__
#define HYPERGRAPH_H__

#include <vector>
#include "hypernode.h"
#include "hyperedge.h"

class HyperGraph {
public:
  std::vector<ReceptorNode*> receptors;
  std::vector<PumpNode*> pumps;
  std::vector<HyperEdge*> hyperedges;

  int atp_available = 50;

  ReceptorNode* addReceptor(ReceptorNode* receptor);
  PumpNode* addPump(PumpNode* pump);
  HyperEdge* addHyperEdge(HyperEdge* edge);

  void step();
  void print(int tick_index);
};

#endif

