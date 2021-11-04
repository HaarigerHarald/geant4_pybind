#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4DriverReporter.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4DriverReporter(py::module &m)
{
   py::class_<G4DriverReporter>(m, "G4DriverReporter")

      .def(py::init<>())
      .def("__copy__", [](const G4DriverReporter &self) { return G4DriverReporter(self); })
      .def("__deepcopy__", [](const G4DriverReporter &self, py::dict) { return G4DriverReporter(self); })

      .def_static("PrintStatus",
                  py::overload_cast<G4double const *, G4double, G4double const *, G4double, G4double, unsigned int,
                                    unsigned int>(&G4DriverReporter::PrintStatus),
                  py::arg("StartArr"), py::arg("xstart"), py::arg("CurrentArr"), py::arg("xcurrent"),
                  py::arg("requestStep"), py::arg("subStepNo"), py::arg("noIntegrationVariables"))

      .def_static("PrintStatus",
                  py::overload_cast<G4FieldTrack const &, G4FieldTrack const &, G4double, unsigned int>(
                     &G4DriverReporter::PrintStatus),
                  py::arg("StartFT"), py::arg("CurrentFT"), py::arg("requestStep"), py::arg("subStepNo"))

      .def_static("PrintStat_Aux", &G4DriverReporter::PrintStat_Aux, py::arg("aFieldTrack"), py::arg("requestStep"),
                  py::arg("actualStep"), py::arg("subStepNo"), py::arg("subStepSize"), py::arg("dotVelocities"));
}
