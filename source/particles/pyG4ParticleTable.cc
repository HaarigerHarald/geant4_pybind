#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ParticleTable.hh>
#include <G4IonTable.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4ParticleTable(py::module &m)
{
   py::class_<G4ParticleTable, py::nodelete>(m, "G4ParticleTable", "particle table")

      .def_static("GetParticleTable", &G4ParticleTable::GetParticleTable, py::return_value_policy::reference)
      .def("contains", py::overload_cast<const G4String &>(&G4ParticleTable::contains, py::const_))
      .def("contains", py::overload_cast<const G4ParticleDefinition *>(&G4ParticleTable::contains, py::const_))
      .def("entries", &G4ParticleTable::entries)
      .def("size", &G4ParticleTable::size)

      .def("GetParticle", &G4ParticleTable::GetParticle, py::return_value_policy::reference)
      .def("GetParticleName", &G4ParticleTable::GetParticleName)
      .def("FindParticle", py::overload_cast<G4int>(&G4ParticleTable::FindParticle), py::return_value_policy::reference)
      .def("FindParticle", py::overload_cast<const G4String &>(&G4ParticleTable::FindParticle),
           py::return_value_policy::reference)

      .def("FindParticle", py::overload_cast<const G4ParticleDefinition *>(&G4ParticleTable::FindParticle),
           py::return_value_policy::reference)

      .def("FindAntiParticle", py::overload_cast<G4int>(&G4ParticleTable::FindAntiParticle),
           py::return_value_policy::reference)

      .def("FindAntiParticle", py::overload_cast<const G4String &>(&G4ParticleTable::FindAntiParticle),
           py::return_value_policy::reference)

      .def("FindAntiParticle", py::overload_cast<const G4ParticleDefinition *>(&G4ParticleTable::FindAntiParticle),
           py::return_value_policy::reference)

      .def("DumpTable", &G4ParticleTable::DumpTable, py::arg("particle_name") = "ALL")
      .def("GetIonTable", &G4ParticleTable::GetIonTable, py::return_value_policy::reference_internal)

      .def("SetVerboseLevel", &G4ParticleTable::SetVerboseLevel)
      .def("GetVerboseLevel", &G4ParticleTable::GetVerboseLevel)
      .def("SetReadiness", &G4ParticleTable::SetReadiness)
      .def("GetReadiness", &G4ParticleTable::GetReadiness)

      .def("GetParticleList", [](const G4ParticleTable &self) {
         py::list                            particleList;
         G4ParticleTable::G4PTblDicIterator *theParticleIterator = self.GetIterator();
         theParticleIterator->reset();
         while ((*theParticleIterator)()) {
            G4ParticleDefinition *particle = theParticleIterator->value();
            particleList.append(particle);
         }

         return particleList;
      });
}
