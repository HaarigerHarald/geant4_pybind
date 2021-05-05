#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ParticleDefinition(py::module &);
void export_G4DynamicParticle(py::module &);
void export_G4ParticleTable(py::module &);
void export_G4DecayTable(py::module &);
void export_G4PrimaryParticle(py::module &);
void export_G4PrimaryVertex(py::module &);
void export_PyG4ParticleList(py::module &);
void export_G4Adjoint(py::module &);
void export_G4Barions(py::module &);
void export_G4Bosons(py::module &);
void export_G4Ions(py::module &);
void export_G4Leptons(py::module &);
void export_G4Mesons(py::module &);
void export_G4IonTable(py::module &);

void export_modG4particles(py::module &m)
{
   export_G4ParticleDefinition(m);
   export_G4DynamicParticle(m);
   export_G4ParticleTable(m);
   export_G4DecayTable(m);
   export_G4PrimaryParticle(m);
   export_G4PrimaryVertex(m);
   export_PyG4ParticleList(m);
   export_G4Adjoint(m);
   export_G4Barions(m);
   export_G4Bosons(m);
   export_G4Ions(m);
   export_G4Leptons(m);
   export_G4Mesons(m);
   export_G4IonTable(m);
}
