#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4CrystalAtomBase.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4CrystalAtomBase(py::module &m)
{
   py::class_<G4CrystalAtomBase>(m, "G4CrystalAtomBase")

      .def("__copy__", [](const G4CrystalAtomBase &self) { return new G4CrystalAtomBase(self); })
      .def("__deepcopy__", [](const G4CrystalAtomBase &self, py::dict) { return new G4CrystalAtomBase(self); })
      .def(py::init<>())
      .def(py::init<G4ThreeVector>(), py::arg("apos"))
      .def("AddPos", &G4CrystalAtomBase::AddPos, py::arg("a3vec"))
      .def("DelPos", &G4CrystalAtomBase::DelPos, py::arg("idx"))
      .def("GetPos", py::overload_cast<>(&G4CrystalAtomBase::GetPos))
      .def("GetPos", py::overload_cast<G4int>(&G4CrystalAtomBase::GetPos), py::arg("idx"))
      .def("SetPos", &G4CrystalAtomBase::SetPos, py::arg("a3vecvec"));
}
