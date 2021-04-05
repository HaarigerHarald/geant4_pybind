#ifndef PROCESSES_OPAQUE_TYPES_HH
#define PROCESSES_OPAQUE_TYPES_HH

#include <pybind11/pybind11.h>

#include <G4VProcess.hh>

typedef std::vector<G4VProcess *> G4ProcVector;

PYBIND11_MAKE_OPAQUE(G4ProcVector);

#endif // PROCESSES_OPAQUE_TYPES_HH
