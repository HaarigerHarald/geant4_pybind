#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VGCellFinder.hh>
#include <G4VPhysicalVolume.hh>
#include <G4Step.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4VGCellFinder : public G4VGCellFinder, public py::trampoline_self_life_support {
public:
   using G4VGCellFinder::G4VGCellFinder;

   G4GeometryCell GetPreGeometryCell(const G4Step &aStep) const override
   {
      PYBIND11_OVERRIDE_PURE(G4GeometryCell, G4VGCellFinder, GetPreGeometryCell, aStep);
   }

   G4GeometryCell GetPostGeometryCell(const G4Step &aStep) const override
   {
      PYBIND11_OVERRIDE_PURE(G4GeometryCell, G4VGCellFinder, GetPostGeometryCell, aStep);
   }
};

void export_G4VGCellFinder(py::module &m)
{
   py::class_<G4VGCellFinder, PyG4VGCellFinder>(m, "G4VGCellFinder")

      .def(py::init<>())
      .def("__copy__", [](const PyG4VGCellFinder &self) { return PyG4VGCellFinder(self); })
      .def("__deepcopy__", [](const PyG4VGCellFinder &self, py::dict) { return PyG4VGCellFinder(self); })
      .def("GetPreGeometryCell", &G4VGCellFinder::GetPreGeometryCell, py::arg("aStep"))
      .def("GetPostGeometryCell", &G4VGCellFinder::GetPostGeometryCell, py::arg("aStep"));
}
