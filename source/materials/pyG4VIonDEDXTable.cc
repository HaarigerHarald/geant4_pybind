#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VIonDEDXTable.hh>
#include <G4PhysicsVector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VIonDEDXTable : public G4VIonDEDXTable, public py::trampoline_self_life_support {
public:
   using G4VIonDEDXTable::G4VIonDEDXTable;

   G4bool BuildPhysicsVector(G4int arg0, G4int arg1) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VIonDEDXTable, BuildPhysicsVector, arg0, arg1);
   }

   G4bool BuildPhysicsVector(G4int arg0, const G4String &arg1) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VIonDEDXTable, BuildPhysicsVector, arg0, arg1);
   }

   G4PhysicsVector *GetPhysicsVector(G4int arg0, G4int arg1) override
   {
      PYBIND11_OVERRIDE_PURE(G4PhysicsVector *, G4VIonDEDXTable, GetPhysicsVector, arg0, arg1);
   }

   G4PhysicsVector *GetPhysicsVector(G4int arg0, const G4String &arg1) override
   {
      PYBIND11_OVERRIDE_PURE(G4PhysicsVector *, G4VIonDEDXTable, GetPhysicsVector, arg0, arg1);
   }

   G4bool IsApplicable(G4int arg0, G4int arg1) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VIonDEDXTable, IsApplicable, arg0, arg1);
   }

   G4bool IsApplicable(G4int arg0, const G4String &arg1) override
   {
      PYBIND11_OVERRIDE_PURE(G4bool, G4VIonDEDXTable, IsApplicable, arg0, arg1);
   }
};

void export_G4VIonDEDXTable(py::module &m)
{
   py::class_<G4VIonDEDXTable, PyG4VIonDEDXTable>(m, "G4VIonDEDXTable")

      .def(py::init<>())
      .def("BuildPhysicsVector", py::overload_cast<G4int, G4int>(&G4VIonDEDXTable::BuildPhysicsVector))
      .def("BuildPhysicsVector", py::overload_cast<G4int, const G4String &>(&G4VIonDEDXTable::BuildPhysicsVector))
      .def("GetPhysicsVector", py::overload_cast<G4int, G4int>(&G4VIonDEDXTable::GetPhysicsVector),
           py::return_value_policy::reference)

      .def("GetPhysicsVector", py::overload_cast<G4int, const G4String &>(&G4VIonDEDXTable::GetPhysicsVector),
           py::return_value_policy::reference)

      .def("IsApplicable", py::overload_cast<G4int, G4int>(&G4VIonDEDXTable::IsApplicable))
      .def("IsApplicable", py::overload_cast<G4int, const G4String &>(&G4VIonDEDXTable::IsApplicable));
}
