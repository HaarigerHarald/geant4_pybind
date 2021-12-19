#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4TScoreNtupleWriter.hh>

#include <tools/wroot/ntuple>
#include <tools/rroot/ntuple>
#include <G4RootAnalysisManager.hh>
#include <G4RootAnalysisReader.hh>

#include <tools/wcsv_ntuple>
#include <G4CsvAnalysisManager.hh>
#include <G4CsvAnalysisReader.hh>

#include <tools/waxml/ntuple>
#include <G4XmlAnalysisManager.hh>
#include <G4XmlAnalysisReader.hh>

#include <G4GenericFileManager.hh>
#include <G4HnInformation.hh>
#include <G4VNtupleFileManager.hh>
#include <G4GenericAnalysisManager.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TScoreNtupleWriter(py::module &m)
{
   // py::class_<G4TScoreNtupleWriter<G4RootAnalysisManager>>(m, "G4RootScoreNtupleWriter")

   //    .def(py::init<>())
   //    .def("Book", &G4TScoreNtupleWriter<G4RootAnalysisManager>::Book)
   //    .def("OpenFile", &G4TScoreNtupleWriter<G4RootAnalysisManager>::OpenFile)
   //    .def("Fill", &G4TScoreNtupleWriter<G4RootAnalysisManager>::Fill)
   //    .def("Write", &G4TScoreNtupleWriter<G4RootAnalysisManager>::Write)

   //    .def("SetFileName", &G4TScoreNtupleWriter<G4RootAnalysisManager>::SetFileName)
   //    .def("SetVerboseLevel", &G4TScoreNtupleWriter<G4RootAnalysisManager>::SetVerboseLevel)
   //    .def("GetFileName", &G4TScoreNtupleWriter<G4RootAnalysisManager>::GetFileName)
   //    .def("GetVerboseLevel", &G4TScoreNtupleWriter<G4RootAnalysisManager>::GetVerboseLevel);

   // py::class_<G4TScoreNtupleWriter<G4CsvAnalysisManager>>(m, "G4CsvScoreNtupleWriter")

   //    .def(py::init<>())
   //    .def("Book", &G4TScoreNtupleWriter<G4CsvAnalysisManager>::Book)
   //    .def("OpenFile", &G4TScoreNtupleWriter<G4CsvAnalysisManager>::OpenFile)
   //    .def("Fill", &G4TScoreNtupleWriter<G4CsvAnalysisManager>::Fill)
   //    .def("Write", &G4TScoreNtupleWriter<G4CsvAnalysisManager>::Write)

   //    .def("SetFileName", &G4TScoreNtupleWriter<G4CsvAnalysisManager>::SetFileName)
   //    .def("SetVerboseLevel", &G4TScoreNtupleWriter<G4CsvAnalysisManager>::SetVerboseLevel)
   //    .def("GetFileName", &G4TScoreNtupleWriter<G4CsvAnalysisManager>::GetFileName)
   //    .def("GetVerboseLevel", &G4TScoreNtupleWriter<G4CsvAnalysisManager>::GetVerboseLevel);

   // py::class_<G4TScoreNtupleWriter<G4XmlAnalysisManager>>(m, "G4XmlScoreNtupleWriter")

   //    .def(py::init<>())
   //    .def("Book", &G4TScoreNtupleWriter<G4XmlAnalysisManager>::Book)
   //    .def("OpenFile", &G4TScoreNtupleWriter<G4XmlAnalysisManager>::OpenFile)
   //    .def("Fill", &G4TScoreNtupleWriter<G4XmlAnalysisManager>::Fill)
   //    .def("Write", &G4TScoreNtupleWriter<G4XmlAnalysisManager>::Write)

   //    .def("SetFileName", &G4TScoreNtupleWriter<G4XmlAnalysisManager>::SetFileName)
   //    .def("SetVerboseLevel", &G4TScoreNtupleWriter<G4XmlAnalysisManager>::SetVerboseLevel)
   //    .def("GetFileName", &G4TScoreNtupleWriter<G4XmlAnalysisManager>::GetFileName)
   //    .def("GetVerboseLevel", &G4TScoreNtupleWriter<G4XmlAnalysisManager>::GetVerboseLevel);

   py::class_<G4TScoreNtupleWriter<G4GenericAnalysisManager>>(m, "G4GenericScoreNtupleWriter")

      .def(py::init<>())
      .def("Book", &G4TScoreNtupleWriter<G4GenericAnalysisManager>::Book, py::call_guard<py::gil_scoped_release>())
      .def("OpenFile", &G4TScoreNtupleWriter<G4GenericAnalysisManager>::OpenFile,
           py::call_guard<py::gil_scoped_release>())

      .def("Fill", &G4TScoreNtupleWriter<G4GenericAnalysisManager>::Fill, py::call_guard<py::gil_scoped_release>())
      .def("Write", &G4TScoreNtupleWriter<G4GenericAnalysisManager>::Write, py::call_guard<py::gil_scoped_release>())

      .def("SetFileName", &G4TScoreNtupleWriter<G4GenericAnalysisManager>::SetFileName)
      .def("SetVerboseLevel", &G4TScoreNtupleWriter<G4GenericAnalysisManager>::SetVerboseLevel)
      .def("GetFileName", &G4TScoreNtupleWriter<G4GenericAnalysisManager>::GetFileName)
      .def("GetVerboseLevel", &G4TScoreNtupleWriter<G4GenericAnalysisManager>::GetVerboseLevel);
}
