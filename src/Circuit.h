#ifndef CIRCUIT_H
#define CIRCUIT_H

extern "C" {
#include "utils/uuid.h"
}  

#include <unordered_map>
#include <unordered_set>
#include <set>
#include <vector>

class Circuit {
 public:
  enum gateType { UNDETERMINED, AND, OR, NOT, IN };
  typedef std::string uuid;

 private:
  std::vector<gateType> gates;
  std::vector<std::unordered_set<unsigned>> wires;
  std::vector<std::unordered_set<unsigned>> rwires;
  std::unordered_map<uuid, unsigned> uuid2id;
  std::vector<double> prob;
  std::set<unsigned> inputs;
  
  unsigned addGate();
  bool evaluate(unsigned g, const std::unordered_set<unsigned> &trues) const;

  std::string processGate(unsigned g);
    
 public:
  bool hasGate(const uuid &u) const;
  unsigned getGate(const uuid &u);
  Circuit::uuid findGateUuid(const unsigned g) const;
  void setGate(const uuid &u, gateType t, double p = -1);
  void addWire(unsigned f, unsigned t);

  double possibleWorlds(unsigned g) const;
  double compilation(unsigned g, std::string compiler) const;
  double monteCarlo(unsigned g, unsigned samples) const;

  double dDNNFEvaluation(unsigned g) const;

  int dotRenderer() const; 

  std::string toString(unsigned g) const;
  std::string toDot() const;
};

class CircuitException : public std::exception
{
  std::string message;

 public: 
  CircuitException(const std::string &m) : message(m) {}
  virtual char const * what() const noexcept { return message.c_str(); }
};

#endif /* CIRCUIT_H */
