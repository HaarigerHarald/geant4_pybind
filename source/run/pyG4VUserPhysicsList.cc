#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VUserPhysicsList.hh>
#include <G4ProcessManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VUserPhysicsList : public G4VUserPhysicsList, public py::trampoline_self_life_support {

public:
   using G4VUserPhysicsList::G4VUserPhysicsList;

   void ConstructParticle() override { PYBIND11_OVERRIDE_PURE(void, G4VUserPhysicsList, ConstructParticle, ); }

   void ConstructProcess() override { PYBIND11_OVERRIDE_PURE(void, G4VUserPhysicsList, ConstructProcess, ); }

   void SetCuts() override { PYBIND11_OVERRIDE_PURE(void, G4VUserPhysicsList, SetCuts, ); }
};

void export_G4VUserPhysicsList(py::module &m)
{
   py::class_<G4VUserPhysicsList, PyG4VUserPhysicsList>(m, "G4VUserPhysicsList", "base class of user physics list")

      .def(py::init<>())

      .def("ConstructParticle", &G4VUserPhysicsList::ConstructParticle)
      .def("ConstructProcess", &G4VUserPhysicsList::ConstructProcess)
      .def("SetCuts", &G4VUserPhysicsList::SetCuts)

      .def("SetDefaultCutValue", &G4VUserPhysicsList::SetDefaultCutValue)
      .def("GetDefaultCutValue", &G4VUserPhysicsList::GetDefaultCutValue)

      .def("BuildPhysicsTable", py::overload_cast<>(&G4VUserPhysicsList::BuildPhysicsTable))
      .def("PreparePhysicsTable", &G4VUserPhysicsList::PreparePhysicsTable)
      .def("BuildPhysicsTable", py::overload_cast<G4ParticleDefinition *>(&G4VUserPhysicsList::BuildPhysicsTable))
      .def("StorePhysicsTable", &G4VUserPhysicsList::StorePhysicsTable, py::arg("directory") = ".")
      .def("IsPhysicsTableRetrieved", &G4VUserPhysicsList::IsPhysicsTableRetrieved)
      .def("IsStoredInAscii", &G4VUserPhysicsList::IsStoredInAscii)
      .def("GetPhysicsTableDirectory", &G4VUserPhysicsList::GetPhysicsTableDirectory)
      .def("SetStoredInAscii", &G4VUserPhysicsList::SetStoredInAscii)
      .def("ResetStoredInAscii", &G4VUserPhysicsList::ResetStoredInAscii)

      .def("DumpList", &G4VUserPhysicsList::DumpList)

      .def("DumpCutValuesTable", &G4VUserPhysicsList::DumpCutValuesTable, py::arg("flag") = 1)
      .def("DumpCutValuesTableIfRequested", &G4VUserPhysicsList::DumpCutValuesTableIfRequested)
      .def("SetCutValue", py::overload_cast<G4double, const G4String &>(&G4VUserPhysicsList::SetCutValue))
      .def("SetCutValue",
           py::overload_cast<G4double, const G4String &, const G4String &>(&G4VUserPhysicsList::SetCutValue))

      .def("SetParticleCuts",
           py::overload_cast<G4double, G4ParticleDefinition *, G4Region *>(&G4VUserPhysicsList::SetParticleCuts),
           py::arg("cut"), py::arg("particle"), py::arg("region") = static_cast<G4Region *>(nullptr))

      .def("SetParticleCuts",
           py::overload_cast<G4double, const G4String &, G4Region *>(&G4VUserPhysicsList::SetParticleCuts),
           py::arg("cut"), py::arg("particle"), py::arg("region") = static_cast<G4Region *>(nullptr))

      .def("SetVerboseLevel", &G4VUserPhysicsList::SetVerboseLevel)
      .def("GetVerboseLevel", &G4VUserPhysicsList::GetVerboseLevel)
      .def("SetCutsWithDefault", &G4VUserPhysicsList::SetCutsWithDefault)
      .def("SetCutsForRegion", &G4VUserPhysicsList::SetCutsForRegion)
      .def("GetApplyCuts", &G4VUserPhysicsList::GetApplyCuts)
      .def("AddProcessManager", &G4VUserPhysicsList::AddProcessManager, py::arg("newParticle"),
           py::arg("newManager") = static_cast<G4ProcessManager *>(nullptr), py::keep_alive<1, 3>());
}
