#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4LocatorChangeLogger.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4LocatorChangeLogger(py::module &m)
{
   py::class_<G4LocatorChangeLogger>(m, "G4LocatorChangeLogger")

      .def(py::init<const std::string>(), py::arg("name"))
      .def("__copy__", [](const G4LocatorChangeLogger &self) { return G4LocatorChangeLogger(self); })
      .def("__deepcopy__", [](const G4LocatorChangeLogger &self, py::dict) { return G4LocatorChangeLogger(self); })
      .def("AddRecord", py::overload_cast<const G4LocatorChangeRecord &>(&G4LocatorChangeLogger::AddRecord),
           py::arg("chngRecord"))

      .def("AddRecord",
           py::overload_cast<G4LocatorChangeRecord::EChangeLocation, G4int, unsigned int, const G4FieldTrack &>(
              &G4LocatorChangeLogger::AddRecord),
           py::arg("codeLocation"), py::arg("iter"), py::arg("count"), py::arg("fieldTrack"))

      .def("StreamInfo", &G4LocatorChangeLogger::StreamInfo, py::arg("os"))
      .def_static("ReportEndChanges", &G4LocatorChangeLogger::ReportEndChanges, py::arg("os"), py::arg("startA"),
                  py::arg("endB"))

      .def(
         "__str__",
         [](const G4LocatorChangeLogger &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
