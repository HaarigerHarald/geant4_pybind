#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4RootAnalysisManager.hh>
#include <G4RootAnalysisReader.hh>

#include <G4CsvAnalysisManager.hh>
#include <G4CsvAnalysisReader.hh>

#include <G4XmlAnalysisManager.hh>
#include <G4XmlAnalysisReader.hh>

#include <G4GenericAnalysisManager.hh>
#include <G4GenericFileManager.hh>
#include <G4HnInformation.hh>
#include <G4VNtupleFileManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4AnalysisManager(py::module &m)
{
   py::class_<G4ToolsAnalysisManager, G4VAnalysisManager, py::nodelete>(m, "G4ToolsAnalysisManager")

      //.def(py::init<const G4String &, G4bool>(), py::arg("type"), py::arg("isMaster") = true)

      .def_static("Instance", &G4ToolsAnalysisManager::Instance, py::return_value_policy::reference)
      .def_static("IsInstance", &G4ToolsAnalysisManager::IsInstance)

      .def("GetH1", &G4ToolsAnalysisManager::GetH1, py::arg("id"), py::arg("warn") = true,
           py::arg("onlyIfActive") = true, py::return_value_policy::reference_internal)

      .def("GetH2", &G4ToolsAnalysisManager::GetH2, py::arg("id"), py::arg("warn") = true,
           py::arg("onlyIfActive") = true, py::return_value_policy::reference_internal)

      .def("GetH3", &G4ToolsAnalysisManager::GetH3, py::arg("id"), py::arg("warn") = true,
           py::arg("onlyIfActive") = true, py::return_value_policy::reference_internal)

      .def("GetP1", &G4ToolsAnalysisManager::GetP1, py::arg("id"), py::arg("warn") = true,
           py::arg("onlyIfActive") = true, py::return_value_policy::reference_internal)

      .def("GetP2", &G4ToolsAnalysisManager::GetP2, py::arg("id"), py::arg("warn") = true,
           py::arg("onlyIfActive") = true, py::return_value_policy::reference_internal);

   py::class_<G4RootAnalysisManager, G4ToolsAnalysisManager, py::nodelete>(m, "G4RootAnalysisManager")

      .def_static("Instance", &G4RootAnalysisManager::Instance, py::return_value_policy::reference)
      .def_static("IsInstance", &G4RootAnalysisManager::IsInstance)

      .def("SetNtupleMerging", &G4RootAnalysisManager::SetNtupleMerging, py::arg("mergeNtuples"),
           py::arg("nofReducedNtupleFiles") = 0)

      .def("SetNtupleRowWise", &G4RootAnalysisManager::SetNtupleRowWise, py::arg("rowWise"), py::arg("rowMode") = true)

      .def("SetBasketSize", &G4RootAnalysisManager::SetBasketSize, py::arg("basketSize"))
      .def("SetBasketEntries", &G4RootAnalysisManager::SetBasketEntries, py::arg("basketEntries"));

   py::class_<G4CsvAnalysisManager, G4ToolsAnalysisManager, py::nodelete>(m, "G4CsvAnalysisManager")

      .def_static("Instance", &G4CsvAnalysisManager::Instance, py::return_value_policy::reference)
      .def_static("IsInstance", &G4CsvAnalysisManager::IsInstance);

   py::class_<G4XmlAnalysisManager, G4ToolsAnalysisManager, py::nodelete>(m, "G4XmlAnalysisManager")

      .def_static("Instance", &G4XmlAnalysisManager::Instance, py::return_value_policy::reference)
      .def_static("IsInstance", &G4XmlAnalysisManager::IsInstance);

   py::class_<G4GenericAnalysisManager, G4ToolsAnalysisManager, py::nodelete>(m, "G4GenericAnalysisManager")

      .def_static("Instance", &G4GenericAnalysisManager::Instance, py::return_value_policy::reference)
      .def_static("IsInstance", &G4GenericAnalysisManager::IsInstance)

      .def("SetNtupleMerging", &G4GenericAnalysisManager::SetNtupleMerging, py::arg("mergeNtuples"),
           py::arg("nofReducedNtupleFiles") = 0)

      .def("SetNtupleRowWise", &G4GenericAnalysisManager::SetNtupleRowWise, py::arg("rowWise"),
           py::arg("rowMode") = true)

      .def("SetBasketSize", &G4GenericAnalysisManager::SetBasketSize, py::arg("basketSize"))
      .def("SetBasketEntries", &G4GenericAnalysisManager::SetBasketEntries, py::arg("basketEntries"))

      .def("WriteH1", &G4GenericAnalysisManager::WriteH1, py::arg("id"), py::arg("fileName"),
           py::call_guard<py::gil_scoped_release>())

      .def("WriteH2", &G4GenericAnalysisManager::WriteH2, py::arg("id"), py::arg("fileName"),
           py::call_guard<py::gil_scoped_release>())

      .def("WriteH3", &G4GenericAnalysisManager::WriteH3, py::arg("id"), py::arg("fileName"),
           py::call_guard<py::gil_scoped_release>())

      .def("WriteP1", &G4GenericAnalysisManager::WriteP1, py::arg("id"), py::arg("fileName"),
           py::call_guard<py::gil_scoped_release>())

      .def("WriteP2", &G4GenericAnalysisManager::WriteP2, py::arg("id"), py::arg("fileName"),
           py::call_guard<py::gil_scoped_release>())

      .def("SetDefaultFileType", &G4GenericAnalysisManager::SetDefaultFileType, py::arg("value"))
      .def("GetDefaultFileType", &G4GenericAnalysisManager::GetDefaultFileType);
}
