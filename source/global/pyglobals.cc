#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/stl_bind.h>

#include <G4ThreeVector.hh>
#include <G4TwoVector.hh>
#include <vector>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_globals(py::module &m)
{
   py::bind_vector<G4intVector>(m, "G4intVector");
   py::bind_vector<G4doubleVector>(m, "G4doubleVector");
   py::bind_vector<G4StringVector>(m, "G4StringVector");
   py::bind_vector<G4ThreeVectorVector>(m, "G4ThreeVectorVector");
   py::bind_vector<G4TwoVectorVector>(m, "G4TwoVectorVector");
}
