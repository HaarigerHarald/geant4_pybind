#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4ExtDEDXTable.hh>
#include <G4PhysicsVector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4ExtDEDXTable : public G4ExtDEDXTable, public py::trampoline_self_life_support {
public:
   using G4ExtDEDXTable::G4ExtDEDXTable;

   G4bool BuildPhysicsVector(G4int ionZ, const G4String &matName) override
   {
      PYBIND11_OVERRIDE(G4bool, G4ExtDEDXTable, BuildPhysicsVector, ionZ, matName);
   }

   G4bool BuildPhysicsVector(G4int ionZ, G4int matZ) override
   {
      PYBIND11_OVERRIDE(G4bool, G4ExtDEDXTable, BuildPhysicsVector, ionZ, matZ);
   }

   G4PhysicsVector *GetPhysicsVector(G4int atomicNumberIon, G4int atomicNumberElem) override
   {
      PYBIND11_OVERRIDE(G4PhysicsVector *, G4ExtDEDXTable, GetPhysicsVector, atomicNumberIon, atomicNumberElem);
   }

   G4PhysicsVector *GetPhysicsVector(G4int atomicNumberIon, const G4String &matIdenfier) override
   {
      PYBIND11_OVERRIDE(G4PhysicsVector *, G4ExtDEDXTable, GetPhysicsVector, atomicNumberIon, matIdenfier);
   }

   G4bool IsApplicable(G4int atomicNumberIon, G4int atomicNumberElem) override
   {
      PYBIND11_OVERRIDE(G4bool, G4ExtDEDXTable, IsApplicable, atomicNumberIon, atomicNumberElem);
   }

   G4bool IsApplicable(G4int atomicNumberIon, const G4String &matIdentifier) override
   {
      PYBIND11_OVERRIDE(G4bool, G4ExtDEDXTable, IsApplicable, atomicNumberIon, matIdentifier);
   }
};

void export_G4ExtDEDXTable(py::module &m)
{
   py::class_<G4ExtDEDXTable, PyG4ExtDEDXTable, G4VIonDEDXTable>(m, "G4ExtDEDXTable")

      .def(py::init<>())
      .def("AddPhysicsVector", &G4ExtDEDXTable::AddPhysicsVector, py::arg("physicsVector"), py::arg("atomicNumberIon"),
           py::arg("matIdenfier"), py::arg("atomicNumberElem") = 0)

      .def("BuildPhysicsVector", py::overload_cast<G4int, const G4String &>(&G4ExtDEDXTable::BuildPhysicsVector),
           py::arg("ionZ"), py::arg("matName"))

      .def("BuildPhysicsVector", py::overload_cast<G4int, G4int>(&G4ExtDEDXTable::BuildPhysicsVector), py::arg("ionZ"),
           py::arg("matZ"))

      .def("ClearTable", &G4ExtDEDXTable::ClearTable)
      .def("DumpMap", &G4ExtDEDXTable::DumpMap)
      .def("GetDEDX", py::overload_cast<G4double, G4int, G4int>(&G4ExtDEDXTable::GetDEDX),
           py::arg("kinEnergyPerNucleon"), py::arg("atomicNumberIon"), py::arg("atomicNumberElem"))

      .def("GetDEDX", py::overload_cast<G4double, G4int, const G4String &>(&G4ExtDEDXTable::GetDEDX),
           py::arg("kinEnergyPerNucleon"), py::arg("atomicNumberIon"), py::arg("matIdenfier"))

      .def("GetPhysicsVector", py::overload_cast<G4int, G4int>(&G4ExtDEDXTable::GetPhysicsVector),
           py::arg("atomicNumberIon"), py::arg("atomicNumberElem"), py::return_value_policy::reference)

      .def("GetPhysicsVector", py::overload_cast<G4int, const G4String &>(&G4ExtDEDXTable::GetPhysicsVector),
           py::arg("atomicNumberIon"), py::arg("matIdenfier"), py::return_value_policy::reference)

      .def("IsApplicable", py::overload_cast<G4int, G4int>(&G4ExtDEDXTable::IsApplicable), py::arg("atomicNumberIon"),
           py::arg("atomicNumberElem"))

      .def("IsApplicable", py::overload_cast<G4int, const G4String &>(&G4ExtDEDXTable::IsApplicable),
           py::arg("atomicNumberIon"), py::arg("matIdentifier"))

      .def("RemovePhysicsVector", &G4ExtDEDXTable::RemovePhysicsVector, py::arg("atomicNumberIon"),
           py::arg("matIdentifier"))

      .def("RetrievePhysicsTable", &G4ExtDEDXTable::RetrievePhysicsTable, py::arg("fileName"))
      .def("StorePhysicsTable", &G4ExtDEDXTable::StorePhysicsTable, py::arg("fileName"));
}
