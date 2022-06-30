#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4CrystalUnitCell.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4CrystalUnitCell(py::module &m)
{
   py::class_<G4CrystalUnitCell>(m, "G4CrystalUnitCell")

      .def("__copy__", [](const G4CrystalUnitCell &self) { return new G4CrystalUnitCell(self); })
      .def("__deepcopy__", [](const G4CrystalUnitCell &self, py::dict) { return new G4CrystalUnitCell(self); })
      .def(py::init<G4double, G4double, G4double, G4double, G4double, G4double, G4int>(), py::arg("sizeA"),
           py::arg("sizeB"), py::arg("sizeC"), py::arg("alpha"), py::arg("beta"), py::arg("gamma"),
           py::arg("spacegroup"))

      .def("ComputeCellVolume", &G4CrystalUnitCell::ComputeCellVolume)
      .def("FillAtomicPos", &G4CrystalUnitCell::FillAtomicPos, py::arg("pos"), py::arg("vecout"))
      .def("FillAtomicUnitPos", &G4CrystalUnitCell::FillAtomicUnitPos, py::arg("pos"), py::arg("vecout"))
      // .def("FillElReduced", &G4CrystalUnitCell::FillElReduced, py::arg("Cij")) TODO
      .def("GetAngle", &G4CrystalUnitCell::GetAngle)
      .def("GetBasis", &G4CrystalUnitCell::GetBasis, py::arg("idx"))
      .def("GetIntCosAng", &G4CrystalUnitCell::GetIntCosAng, py::arg("h1"), py::arg("k1"), py::arg("l1"), py::arg("h2"),
           py::arg("k2"), py::arg("l2"))

      .def("GetIntSp2", &G4CrystalUnitCell::GetIntSp2, py::arg("h"), py::arg("k"), py::arg("l"))
      .def("GetLatticeSystem", py::overload_cast<>(&G4CrystalUnitCell::GetLatticeSystem))
      .def("GetRecAngle", &G4CrystalUnitCell::GetRecAngle)
      .def("GetRecBasis", &G4CrystalUnitCell::GetRecBasis, py::arg("idx"))
      .def("GetRecIntSp2", &G4CrystalUnitCell::GetRecIntSp2, py::arg("h"), py::arg("k"), py::arg("l"))
      .def("GetRecSize", &G4CrystalUnitCell::GetRecSize)
      .def("GetRecUnitBasis", &G4CrystalUnitCell::GetRecUnitBasis, py::arg("idx"))
      .def("GetRecVolume", &G4CrystalUnitCell::GetRecVolume)
      .def("GetSize", &G4CrystalUnitCell::GetSize)
      .def("GetSpaceGroup", &G4CrystalUnitCell::GetSpaceGroup)
      .def("GetUnitBasis", &G4CrystalUnitCell::GetUnitBasis, py::arg("idx"))
      .def("GetUnitBasisTrigonal", &G4CrystalUnitCell::GetUnitBasisTrigonal)
      .def("GetVolume", &G4CrystalUnitCell::GetVolume)
      .def("SetSpaceGroup", &G4CrystalUnitCell::SetSpaceGroup, py::arg("aInt"));
}
