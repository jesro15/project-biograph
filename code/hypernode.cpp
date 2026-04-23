

#include "hypernode.h"

ReceptorNode::ReceptorNode(std::string id_in, ReceptorKind kind_in) {
  id = id_in;
  kind = kind_in;
  state = Closed;
}

void ReceptorNode::updateState(const GradientField& field) {
  if (kind == Na_channel) {
    if (field.NaDiff != 0) {
      state = Open;
    } else {
      state = Closed;
    }
  } else if (kind == K_channel) {
    if (field.KDiff != 0) {
      state = Open;
    } else {
      state = Closed;
    }
  } else if (kind == Leak) {
    state = Open;
  }
}

PumpNode::PumpNode(std::string id_in, PumpKind kind_in) {
  id = id_in;
  kind = kind_in;
  state = Inactive;
}

void PumpNode::updateState(int atp_available) {
  if (atp_available > 0) {
    state = Active;
  } else {
    state = Inactive;
  }
}
