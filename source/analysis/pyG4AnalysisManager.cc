#include <pybind11/pybind11.h>

#include <G4RootAnalysisManager.hh>
#include <G4RootAnalysisReader.hh>

#include "G4CsvAnalysisManager.hh"
#include "G4CsvAnalysisReader.hh"

#include "G4XmlAnalysisManager.hh"
#include "G4XmlAnalysisReader.hh"

#include "typecast.hh"
#include "holder.hh"

namespace py = pybind11;

void export_G4AnalysisManager(py::module &m)
{
    py::class_<G4RootAnalysisManager, std::unique_ptr<G4RootAnalysisManager, py::nodelete>>(m, "G4RootAnalysisManager")

        .def(py::init<G4bool>(), py::arg("isMaster") = true)
        .def_static("Instance", &G4RootAnalysisManager::Instance, py::return_value_policy::reference)
        .def_static("IsInstance", &G4RootAnalysisManager::IsInstance, py::return_value_policy::reference);
}
