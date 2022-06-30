#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SurfaceProperty.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4SurfaceProperty : public G4SurfaceProperty, public py::trampoline_self_life_support {
public:
   using G4SurfaceProperty::G4SurfaceProperty;

   void SetType(const G4SurfaceType &type) override { PYBIND11_OVERRIDE(void, G4SurfaceProperty, SetType, type); }
};

void export_G4SurfaceProperty(py::module &m)
{
   py::enum_<G4SurfaceType>(m, "G4SurfaceType")
      .value("dielectric_metal", dielectric_metal)
      .value("dielectric_dielectric", dielectric_dielectric)
      .value("dielectric_LUT", dielectric_LUT)
      .value("dielectric_LUTDAVIS", dielectric_LUTDAVIS)
      .value("dielectric_dichroic", dielectric_dichroic)
      .value("firsov", firsov)
      .value("x_ray", x_ray)
      .export_values();

   py::class_<G4SurfaceProperty, PyG4SurfaceProperty, py::nodelete>(m, "G4SurfaceProperty")

      .def("__copy__", [](const PyG4SurfaceProperty &self) { return new PyG4SurfaceProperty(self); })
      .def("__deepcopy__", [](const PyG4SurfaceProperty &self, py::dict) { return new PyG4SurfaceProperty(self); })
      .def("__copy__", [](const G4SurfaceProperty &self) { return new G4SurfaceProperty(self); })
      .def("__deepcopy__", [](const G4SurfaceProperty &self, py::dict) { return new G4SurfaceProperty(self); })
      .def(py::init<const G4String &, G4SurfaceType>(), py::arg("name"), py::arg("type") = x_ray)
      .def(py::init<>())
      .def_static("CleanSurfacePropertyTable", &G4SurfaceProperty::CleanSurfacePropertyTable)
      .def_static("DumpTableInfo", &G4SurfaceProperty::DumpTableInfo)
      .def("GetName", &G4SurfaceProperty::GetName)
      .def_static("GetNumberOfSurfaceProperties", &G4SurfaceProperty::GetNumberOfSurfaceProperties)
      .def_static("GetSurfacePropertyTable", &G4SurfaceProperty::GetSurfacePropertyTable,
                  py::return_value_policy::reference)
      .def("GetType", &G4SurfaceProperty::GetType)
      .def("SetName", &G4SurfaceProperty::SetName, py::arg("name"))
      .def("SetType", &G4SurfaceProperty::SetType, py::arg("type"));
}
