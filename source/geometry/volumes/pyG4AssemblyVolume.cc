#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4AssemblyVolume.hh>
#include <G4LogicalVolume.hh>
#include <G4VPhysicalVolume.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AssemblyVolume(py::module &m)
{
   py::class_<G4AssemblyVolume>(m, "G4AssemblyVolume")

      .def(py::init<>())
      .def(py::init<G4LogicalVolume *, G4ThreeVector &, G4RotationMatrix *>(), py::arg("volume"),
           py::arg("translation"), py::arg("rotation"))

      .def("__copy__", [](const G4AssemblyVolume &self) { return G4AssemblyVolume(self); })
      .def("__deepcopy__", [](const G4AssemblyVolume &self, py::dict) { return G4AssemblyVolume(self); })
      .def(
         "AddPlacedVolume",
         py::overload_cast<G4LogicalVolume *, G4ThreeVector &, G4RotationMatrix *>(&G4AssemblyVolume::AddPlacedVolume),
         py::arg("pPlacedVolume"), py::arg("translation"), py::arg("rotation"))

      .def("AddPlacedVolume", py::overload_cast<G4LogicalVolume *, G4Transform3D &>(&G4AssemblyVolume::AddPlacedVolume),
           py::arg("pPlacedVolume"), py::arg("transformation"))

      .def("AddPlacedAssembly",
           py::overload_cast<G4AssemblyVolume *, G4Transform3D &>(&G4AssemblyVolume::AddPlacedAssembly),
           py::arg("pAssembly"), py::arg("transformation"))

      .def("AddPlacedAssembly",
           py::overload_cast<G4AssemblyVolume *, G4ThreeVector &, G4RotationMatrix *>(
              &G4AssemblyVolume::AddPlacedAssembly),
           py::arg("pAssembly"), py::arg("translation"), py::arg("rotation"))

      .def("MakeImprint",
           py::overload_cast<G4LogicalVolume *, G4ThreeVector &, G4RotationMatrix *, G4int, G4bool>(
              &G4AssemblyVolume::MakeImprint),
           py::arg("pMotherLV"), py::arg("translationInMother"), py::arg("pRotationInMother"),
           py::arg("copyNumBase") = 0, py::arg("surfCheck") = false)

      .def("MakeImprint",
           py::overload_cast<G4LogicalVolume *, G4Transform3D &, G4int, G4bool>(&G4AssemblyVolume::MakeImprint),
           py::arg("pMotherLV"), py::arg("transformation"), py::arg("copyNumBase") = 0, py::arg("surfCheck") = false)

      .def(
         "GetVolumesIterator",
         [](G4AssemblyVolume &self) {
            auto begin = self.GetVolumesIterator();
            auto end   = begin + self.TotalImprintedVolumes();

            return py::make_iterator(begin, end);
         },
         py::keep_alive<0, 1>())

      .def("TotalImprintedVolumes", &G4AssemblyVolume::TotalImprintedVolumes)
      .def("GetImprintTransformation", &G4AssemblyVolume::GetImprintTransformation, py::arg("imprintID"))
      .def(
         "GetTripletsIterator",
         [](G4AssemblyVolume &self) {
            auto begin = self.GetTripletsIterator();
            auto end   = begin + self.TotalTriplets();

            return py::make_iterator(begin, end);
         },
         py::keep_alive<0, 1>())

      .def("TotalTriplets", &G4AssemblyVolume::TotalTriplets)
      .def("GetImprintsCount", &G4AssemblyVolume::GetImprintsCount)
      .def("GetInstanceCount", &G4AssemblyVolume::GetInstanceCount)
      .def("GetAssemblyID", &G4AssemblyVolume::GetAssemblyID);
}
