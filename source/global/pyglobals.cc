#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <G4ThreeVector.hh>
#include <G4TwoVector.hh>
#include <vector>

#include "typecast.hh"

namespace py = pybind11;

typedef std::vector<G4int>         G4intVector;
typedef std::vector<G4double>      G4doubleVector;
typedef std::vector<G4String>      G4StringVector;
typedef std::vector<G4ThreeVector> G4ThreeVectorVector;
typedef std::vector<G4TwoVector>   G4TwoVectorVector;

PYBIND11_MAKE_OPAQUE(G4intVector);
PYBIND11_MAKE_OPAQUE(G4doubleVector);
PYBIND11_MAKE_OPAQUE(G4StringVector);
PYBIND11_MAKE_OPAQUE(G4ThreeVectorVector);
PYBIND11_MAKE_OPAQUE(G4TwoVectorVector);

void export_globals(py::module &m)
{
   py::bind_vector<G4intVector>(m, "G4intVector");
   py::bind_vector<G4doubleVector>(m, "G4doubleVector");
   py::bind_vector<G4StringVector>(m, "G4StringVector");
   py::bind_vector<G4ThreeVectorVector>(m, "G4ThreeVectorVector");
   py::bind_vector<G4TwoVectorVector>(m, "G4TwoVectorVector");
}
