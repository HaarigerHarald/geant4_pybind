#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4UCNMicroRoughnessHelper.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4UCNMicroRoughnessHelper(py::module &m)
{
   py::class_<G4UCNMicroRoughnessHelper, py::nodelete>(m, "G4UCNMicroRoughnessHelper")

      .def(
         "__copy__", [](const G4UCNMicroRoughnessHelper &self) { return new G4UCNMicroRoughnessHelper(self); },
         py::return_value_policy::reference)

      .def(
         "__deepcopy__",
         [](const G4UCNMicroRoughnessHelper &self, py::dict) { return new G4UCNMicroRoughnessHelper(self); },
         py::return_value_policy::reference)

      .def("Fmu", &G4UCNMicroRoughnessHelper::Fmu)
      .def("FmuS", &G4UCNMicroRoughnessHelper::FmuS)
      .def_static("GetInstance", &G4UCNMicroRoughnessHelper::GetInstance, py::return_value_policy::reference)
      .def("IntIminus",
           [](const G4UCNMicroRoughnessHelper &self, G4double arg0, G4double arg1, G4double arg2, G4int arg3,
              G4int arg4, G4double arg5, G4double arg6, G4double *arg7, G4double arg8) {
              return std::make_tuple(self.IntIminus(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8), arg7);
           })

      .def("IntIplus",
           [](const G4UCNMicroRoughnessHelper &self, G4double arg0, G4double arg1, G4double arg2, G4int arg3,
              G4int arg4, G4double arg5, G4double arg6, G4double *arg7, G4double arg8) {
              return std::make_tuple(self.IntIplus(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8), arg7);
           })

      .def("ProbIminus", &G4UCNMicroRoughnessHelper::ProbIminus)
      .def("ProbIplus", &G4UCNMicroRoughnessHelper::ProbIplus)
      .def("S2", &G4UCNMicroRoughnessHelper::S2)
      .def("SS2", &G4UCNMicroRoughnessHelper::SS2);
}
