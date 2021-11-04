#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4LocatorChangeRecord.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4LocatorChangeRecord(py::module &m)
{
   py::class_<G4LocatorChangeRecord> mG4LocatorChangeRecord(m, "G4LocatorChangeRecord");

   py::enum_<G4LocatorChangeRecord::EChangeLocation>(mG4LocatorChangeRecord, "EChangeLocation")
      .value("kInvalidCL", G4LocatorChangeRecord::kInvalidCL)
      .value("kUnknownCL", G4LocatorChangeRecord::kUnknownCL)
      .value("kInitialisingCL", G4LocatorChangeRecord::kInitialisingCL)
      .value("kIntersectsAF", G4LocatorChangeRecord::kIntersectsAF)
      .value("kIntersectsFB", G4LocatorChangeRecord::kIntersectsFB)
      .value("kNoIntersectAForFB", G4LocatorChangeRecord::kNoIntersectAForFB)
      .value("kRecalculatedB", G4LocatorChangeRecord::kRecalculatedB)
      .value("kInsertingMidPoint", G4LocatorChangeRecord::kInsertingMidPoint)
      .value("kRecalculatedBagn", G4LocatorChangeRecord::kRecalculatedBagn)
      .value("kLevelPop", G4LocatorChangeRecord::kLevelPop)
      .export_values();

   mG4LocatorChangeRecord
      .def(py::init<G4LocatorChangeRecord::EChangeLocation, G4int, unsigned int, const G4FieldTrack &>(),
           py::arg("codeLocation"), py::arg("iter"), py::arg("count"), py::arg("fieldTrack"))

      .def("__copy__", [](const G4LocatorChangeRecord &self) { return G4LocatorChangeRecord(self); })
      .def("__deepcopy__", [](const G4LocatorChangeRecord &self, py::dict) { return G4LocatorChangeRecord(self); })
      .def_static("GetNameChangeLocation", &G4LocatorChangeRecord::GetNameChangeLocation,
                  py::return_value_policy::reference)

      .def("GetLocation", &G4LocatorChangeRecord::GetLocation)
      .def("GetCount", &G4LocatorChangeRecord::GetCount)
      .def("GetIteration", &G4LocatorChangeRecord::GetIteration)
      .def("GetLength", &G4LocatorChangeRecord::GetLength)
      .def("StreamInfo", &G4LocatorChangeRecord::StreamInfo, py::arg("os"))
      .def_static("ReportVector", &G4LocatorChangeRecord::ReportVector, py::arg("os"), py::arg("nameOfRecord"),
                  py::arg("lcr"))

      .def_static("ReportEndChanges", &G4LocatorChangeRecord::ReportEndChanges, py::arg("os"), py::arg("startA"),
                  py::arg("endB"))

      .def(
         "__str__",
         [](const G4LocatorChangeRecord &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}