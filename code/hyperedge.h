#ifndef HYPEREDGE_H__
#define HYPEREDGE_H__

#include <string>
#include <vector>
#include "bio_types.h"
#include "hypernode.h"

struct HyperEdge {
  std::string id; 
  EdgeKind kind;

  std::vector<ReceptorNode*> receptors;
  std::vector<PumpNode*> pumps;

  GradientField field; // each edge gets its own gradient differential

  // initialized
  HyperEdge(std::string id_in, EdgeKind k_in) {
    id = id_in;
    kind = k_in;
  }
};

#endif 
