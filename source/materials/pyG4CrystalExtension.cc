#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4CrystalExtension.hh>
#include <G4DensityEffectData.hh>
#include <G4DensityEffectCalculator.hh>
#include <G4NistMessenger.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4CrystalExtension : public G4CrystalExtension, public py::trampoline_self_life_support {
public:
   using G4CrystalExtension::G4CrystalExtension;

   void Print() const override { PYBIND11_OVERRIDE(void, G4CrystalExtension, Print, ); }
};

void export_G4CrystalExtension(py::module &m)
{
   py::class_<G4CrystalExtension, PyG4CrystalExtension, G4VMaterialExtension>(m, "G4CrystalExtension")

      .def("__copy__", [](const PyG4CrystalExtension &self) { return new PyG4CrystalExtension(self); })
      .def("__deepcopy__", [](const PyG4CrystalExtension &self, py::dict) { return new PyG4CrystalExtension(self); })
      .def("__copy__", [](const G4CrystalExtension &self) { return new G4CrystalExtension(self); })
      .def("__deepcopy__", [](const G4CrystalExtension &self, py::dict) { return new G4CrystalExtension(self); })
      .def(py::init<G4Material *, const G4String &>(), py::arg("arg0"), py::arg("name") = "crystal")
      .def("AddAtomBase", py::overload_cast<const G4Element *, G4CrystalAtomBase *>(&G4CrystalExtension::AddAtomBase),
           py::arg("anElement"), py::arg("aBase"))

      .def("AddAtomBase", py::overload_cast<G4int, G4CrystalAtomBase *>(&G4CrystalExtension::AddAtomBase),
           py::arg("anElIdx"), py::arg("aLattice"))

      .def("AddAtomicBond", &G4CrystalExtension::AddAtomicBond, py::arg("aBond"))
      .def("ComputeStructureFactor", &G4CrystalExtension::ComputeStructureFactor, py::arg("kScatteringVector"),
           py::arg("h"), py::arg("k"), py::arg("l"))

      .def("ComputeStructureFactorGeometrical", &G4CrystalExtension::ComputeStructureFactorGeometrical, py::arg("h"),
           py::arg("k"), py::arg("l"))

      .def("GetAtomBase", py::overload_cast<const G4Element *>(&G4CrystalExtension::GetAtomBase), py::arg("anElement"),
           py::return_value_policy::reference)

      .def("GetAtomBase", py::overload_cast<G4int>(&G4CrystalExtension::GetAtomBase), py::arg("anElIdx"),
           py::return_value_policy::reference)

      .def("GetAtomPos",
           py::overload_cast<const G4Element *, std::vector<G4ThreeVector> &>(&G4CrystalExtension::GetAtomPos),
           py::arg("anEl"), py::arg("vecout"))

      .def("GetAtomPos", py::overload_cast<std::vector<G4ThreeVector> &>(&G4CrystalExtension::GetAtomPos),
           py::arg("vecout"))

      .def("GetAtomPos", py::overload_cast<G4int, std::vector<G4ThreeVector> &>(&G4CrystalExtension::GetAtomPos),
           py::arg("anElIdx"), py::arg("vecout"))

      .def("GetAtomicBond", &G4CrystalExtension::GetAtomicBond, py::arg("idx"), py::return_value_policy::reference)
      .def("GetAtomicBondVector", &G4CrystalExtension::GetAtomicBondVector)
      .def("GetCijkl", &G4CrystalExtension::GetCijkl, py::arg("i"), py::arg("j"), py::arg("k"), py::arg("l"))
      .def("GetCpq", &G4CrystalExtension::GetCpq, py::arg("p"), py::arg("q"))
      //.def("GetElReduced", &G4CrystalExtension::GetElReduced) TODO
      //.def("GetElasticity", &G4CrystalExtension::GetElasticity) TODO
      .def("GetMaterial", &G4CrystalExtension::GetMaterial, py::return_value_policy::reference)
      .def("GetUnitCell", &G4CrystalExtension::GetUnitCell, py::return_value_policy::reference)
      .def("Print", &G4CrystalExtension::Print)
      .def("SetCpq", &G4CrystalExtension::SetCpq, py::arg("p"), py::arg("q"), py::arg("value"))
      //.def("SetElReduced", &G4CrystalExtension::SetElReduced, py::arg("mat"))
      .def("SetMaterial", &G4CrystalExtension::SetMaterial, py::arg("aMat"))
      .def("SetUnitCell", &G4CrystalExtension::SetUnitCell, py::arg("aUC"));
}
