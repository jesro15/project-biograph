#ifndef HYPERNODE_H__
#define HYPERNODE_H__

#include <string>
#include "bio_types.h"

struct ReceptorNode {
  std::string id;
  ReceptorKind kind;
  State state;

  ReceptorNode(std::string id_in, ReceptorKind kind_in);

  void updateState(const GradientField& field);
};

struct PumpNode {
  std::string id;
  PumpKind kind;
  State state;

  PumpNode(std::string id_in, PumpKind kind_in);

  void updateState(int atp_available);
};

#endif 