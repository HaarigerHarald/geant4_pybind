#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RegularNavigationHelper.hh>
#include <G4AutoLock.hh>
#include <G4ThreadLocalSingleton.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4RegularNavigationHelper(py::module &m)
{
   py::class_<G4RegularNavigationHelper, py::nodelete>(m, "G4RegularNavigationHelper")

      .def("__copy__", [](const G4RegularNavigationHelper &self) { return G4RegularNavigationHelper(self); })
      .def("__deepcopy__",
           [](const G4RegularNavigationHelper &self, py::dict) { return G4RegularNavigationHelper(self); })

      .def_static("Instance", &G4RegularNavigationHelper::Instance, py::return_value_policy::reference)
      .def("ClearStepLengths", &G4RegularNavigationHelper::ClearStepLengths)
      .def("AddStepLength", &G4RegularNavigationHelper::AddStepLength, py::arg("copyNo"), py::arg("slen"))
      .def("GetStepLengths", &G4RegularNavigationHelper::GetStepLengths)
      .def_readwrite("theStepLengths", &G4RegularNavigationHelper::theStepLengths);
}
