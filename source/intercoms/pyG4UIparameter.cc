#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UIparameter.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UIparameter(py::module &m)
{
   py::class_<G4UIparameter>(m, "G4UIparameter", "UI parameter")

      .def(py::init<>())
      .def(py::init<char>())
      .def(py::init<const char *, char, G4bool>())

      .def("List", &G4UIparameter::List)
      .def("GetDefaultValue", &G4UIparameter::GetDefaultValue)
      .def("GetParameterType", &G4UIparameter::GetParameterType)
      .def("GetParameterRange", &G4UIparameter::GetParameterRange)
      .def("GetParameterName", &G4UIparameter::GetParameterName)
      .def("GetParameterCandidates", &G4UIparameter::GetParameterCandidates)
      .def("IsOmittable", &G4UIparameter::IsOmittable)
      .def("GetCurrentAsDefault", &G4UIparameter::GetCurrentAsDefault)
      .def("GetParameterGuidance", &G4UIparameter::GetParameterGuidance);
}
