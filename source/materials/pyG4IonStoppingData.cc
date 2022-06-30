#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4IonStoppingData.hh>
#include <G4PhysicsVector.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4IonStoppingData : public G4IonStoppingData, public py::trampoline_self_life_support {
public:
   using G4IonStoppingData::G4IonStoppingData;

   G4bool BuildPhysicsVector(G4int ionZ, const G4String &matName) override
   {
      PYBIND11_OVERRIDE(G4bool, G4IonStoppingData, BuildPhysicsVector, ionZ, matName);
   }

   G4bool BuildPhysicsVector(G4int ionZ, G4int matZ) override
   {
      PYBIND11_OVERRIDE(G4bool, G4IonStoppingData, BuildPhysicsVector, ionZ, matZ);
   }

   G4PhysicsVector *GetPhysicsVector(G4int atomicNumberIon, G4int atomicNumberElem) override
   {
      PYBIND11_OVERRIDE(G4PhysicsVector *, G4IonStoppingData, GetPhysicsVector, atomicNumberIon, atomicNumberElem);
   }

   G4PhysicsVector *GetPhysicsVector(G4int atomicNumberIon, const G4String &matIdenfier) override
   {
      PYBIND11_OVERRIDE(G4PhysicsVector *, G4IonStoppingData, GetPhysicsVector, atomicNumberIon, matIdenfier);
   }

   G4bool IsApplicable(G4int atomicNumberIon, G4int atomicNumberElem) override
   {
      PYBIND11_OVERRIDE(G4bool, G4IonStoppingData, IsApplicable, atomicNumberIon, atomicNumberElem);
   }

   G4bool IsApplicable(G4int atomicNumberIon, const G4String &matIdentifier) override
   {
      PYBIND11_OVERRIDE(G4bool, G4IonStoppingData, IsApplicable, atomicNumberIon, matIdentifier);
   }
};

void export_G4IonStoppingData(py::module &m)
{
   py::class_<G4IonStoppingData, PyG4IonStoppingData, G4VIonDEDXTable>(m, "G4IonStoppingData")

      .def(py::init<const G4String &, G4bool>(), py::arg("dir"), py::arg("icru"))
      .def("AddPhysicsVector",
           py::overload_cast<G4PhysicsVector *, G4int, const G4String &>(&G4IonStoppingData::AddPhysicsVector),
           py::arg("physicsVector"), py::arg("atomicNumberIon"), py::arg("matIdentifier"))

      .def("AddPhysicsVector", py::overload_cast<G4PhysicsVector *, G4int, G4int>(&G4IonStoppingData::AddPhysicsVector),
           py::arg("physicsVector"), py::arg("atomicNumberIon"), py::arg("atomicNumberElem"))

      .def("BuildPhysicsVector", py::overload_cast<G4int, const G4String &>(&G4IonStoppingData::BuildPhysicsVector),
           py::arg("ionZ"), py::arg("matName"))

      .def("BuildPhysicsVector", py::overload_cast<G4int, G4int>(&G4IonStoppingData::BuildPhysicsVector),
           py::arg("ionZ"), py::arg("matZ"))

      .def("ClearTable", &G4IonStoppingData::ClearTable)
      .def("DumpMap", &G4IonStoppingData::DumpMap)
      .def("GetDEDX", py::overload_cast<G4double, G4int, G4int>(&G4IonStoppingData::GetDEDX),
           py::arg("kinEnergyPerNucleon"), py::arg("atomicNumberIon"), py::arg("atomicNumberElem"))

      .def("GetDEDX", py::overload_cast<G4double, G4int, const G4String &>(&G4IonStoppingData::GetDEDX),
           py::arg("kinEnergyPerNucleon"), py::arg("atomicNumberIon"), py::arg("matIdentifier"))

      .def("GetPhysicsVector", py::overload_cast<G4int, G4int>(&G4IonStoppingData::GetPhysicsVector),
           py::arg("atomicNumberIon"), py::arg("atomicNumberElem"), py::return_value_policy::reference_internal)

      .def("GetPhysicsVector", py::overload_cast<G4int, const G4String &>(&G4IonStoppingData::GetPhysicsVector),
           py::arg("atomicNumberIon"), py::arg("matIdenfier"), py::return_value_policy::reference_internal)

      .def("IsApplicable", py::overload_cast<G4int, G4int>(&G4IonStoppingData::IsApplicable),
           py::arg("atomicNumberIon"), py::arg("atomicNumberElem"))

      .def("IsApplicable", py::overload_cast<G4int, const G4String &>(&G4IonStoppingData::IsApplicable),
           py::arg("atomicNumberIon"), py::arg("matIdentifier"))

      .def("RemovePhysicsVector", py::overload_cast<G4int, const G4String &>(&G4IonStoppingData::RemovePhysicsVector),
           py::arg("atomicNumberIon"), py::arg("matIdentifier"))

      .def("RemovePhysicsVector", py::overload_cast<G4int, G4int>(&G4IonStoppingData::RemovePhysicsVector),
           py::arg("atomicNumberIon"), py::arg("atomicNumberElem"));
}
