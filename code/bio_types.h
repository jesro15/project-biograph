#ifndef BIO_TYPES_H__
#define BIO_TYPES_H__


enum ReceptorKind {
  Na_channel,
  K_channel,
  Leak
};

enum PumpKind {
  NaK_pump
};

enum State {
  Closed,
  Open,
  Inactive,
  Active
};

enum EdgeKind {
  ActiveEdge, // for a hyperedge with a pump
  PassiveEdge // for a hyperedge without a pump
};

// the gradient state that lives on a hyperedge (like a microdomain).
// every hyperedge owns one 
struct GradientField {
  int NaDiff = 0;  //if positive -> Na tends inward
  int KDiff  = 0;  // if negative -> K tends outward


  void clamp(int lo = -3, int hi = 3) {
    if (NaDiff < lo) NaDiff = lo;
    else if (NaDiff > hi) NaDiff = hi;
    if (KDiff < lo) KDiff = lo;
    else if (KDiff > hi) KDiff = hi;
  }
};

#endif 
