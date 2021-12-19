#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VAnalysisManager.hh>

#include <G4AnalysisMessenger.hh>
#include <G4NtupleBookingManager.hh>
#include <G4HnManager.hh>
#include <G4VH1Manager.hh>
#include <G4VH2Manager.hh>
#include <G4VH3Manager.hh>
#include <G4VP1Manager.hh>
#include <G4VP2Manager.hh>
#include <G4VNtupleManager.hh>
#include <G4VFileManager.hh>
#include <G4PlotManager.hh>

#include <tools/histo/hmpi>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VAnalysisManager(py::module &m)
{
   py::class_<G4VAnalysisManager, py::nodelete>(m, "G4VAnalysisManager")

      //.def(py::init<const G4String &, G4bool>())

      .def("OpenFile", &G4VAnalysisManager::OpenFile, py::arg("fileName") = "",
           py::call_guard<py::gil_scoped_release>())

      .def("Write", &G4VAnalysisManager::Write, py::call_guard<py::gil_scoped_release>())
      .def("CloseFile", &G4VAnalysisManager::CloseFile, py::arg("reset") = true,
           py::call_guard<py::gil_scoped_release>())

      .def("Merge", &G4VAnalysisManager::Merge) // TODO
      .def("Plot", &G4VAnalysisManager::Plot)
      .def("IsOpenFile", &G4VAnalysisManager::IsOpenFile)

      .def("SetFileName", &G4VAnalysisManager::SetFileName)
      .def("SetHistoDirectoryName", &G4VAnalysisManager::SetHistoDirectoryName)
      .def("SetNtupleDirectoryName", &G4VAnalysisManager::SetNtupleDirectoryName)
      .def("SetCompressionLevel", &G4VAnalysisManager::SetCompressionLevel)

      .def("GetFileName", &G4VAnalysisManager::GetFileName)
      .def("GetHistoDirectoryName", &G4VAnalysisManager::GetHistoDirectoryName)
      .def("GetNtupleDirectoryName", &G4VAnalysisManager::GetNtupleDirectoryName)
      .def("GetCompressionLevel", &G4VAnalysisManager::GetCompressionLevel)

      .def("CreateH1",
           py::overload_cast<const G4String &, const G4String &, G4int, G4double, G4double, const G4String &,
                             const G4String &, const G4String &>(&G4VAnalysisManager::CreateH1),
           py::arg("name"), py::arg("title"), py::arg("nbins"), py::arg("xmin"), py::arg("xmax"),
           py::arg("unitName") = "none", py::arg("fcnName") = "none", py::arg("binSchemeName") = "linear")

      .def("CreateH1",
           py::overload_cast<const G4String &, const G4String &, const std::vector<G4double> &, const G4String &,
                             const G4String &>(&G4VAnalysisManager::CreateH1),
           py::arg("name"), py::arg("title"), py::arg("edges"), py::arg("unitName") = "none",
           py::arg("fcnName") = "none")

      .def("CreateH2",
           py::overload_cast<const G4String &, const G4String &, G4int, G4double, G4double, G4int, G4double, G4double,
                             const G4String &, const G4String &, const G4String &, const G4String &, const G4String &,
                             const G4String &>(&G4VAnalysisManager::CreateH2),
           py::arg("name"), py::arg("title"), py::arg("nxbins"), py::arg("xmin"), py::arg("xmax"), py::arg("nybins"),
           py::arg("ymin"), py::arg("ymax"), py::arg("xunitName") = "none", py::arg("yunitName") = "none",
           py::arg("xfcnName") = "none", py::arg("yfcnName") = "none", py::arg("xbinSchemeName") = "linear",
           py::arg("ybinSchemeName") = "linear")

      .def("CreateH2",
           py::overload_cast<const G4String &, const G4String &, const std::vector<G4double> &,
                             const std::vector<G4double> &, const G4String &, const G4String &, const G4String &,
                             const G4String &>(&G4VAnalysisManager::CreateH2),
           py::arg("name"), py::arg("title"), py::arg("xedges"), py::arg("yedges"), py::arg("xunitName") = "none",
           py::arg("yunitName") = "none", py::arg("xfcnName") = "none", py::arg("yfcnName") = "none")

      .def("CreateH3",
           py::overload_cast<const G4String &, const G4String &, G4int, G4double, G4double, G4int, G4double, G4double,
                             G4int, G4double, G4double, const G4String &, const G4String &, const G4String &,
                             const G4String &, const G4String &, const G4String &, const G4String &, const G4String &,
                             const G4String &>(&G4VAnalysisManager::CreateH3),
           py::arg("name"), py::arg("title"), py::arg("nxbins"), py::arg("xmin"), py::arg("xmax"), py::arg("nybins"),
           py::arg("ymin"), py::arg("ymax"), py::arg("nzbins"), py::arg("zmin"), py::arg("zmax"),
           py::arg("xunitName") = "none", py::arg("yunitName") = "none", py::arg("zunitName") = "none",
           py::arg("xfcnName") = "none", py::arg("yfcnName") = "none", py::arg("zfcnName") = "none",
           py::arg("xbinSchemeName") = "linear", py::arg("ybinSchemeName") = "linear",
           py::arg("zbinSchemeName") = "linear")

      .def("CreateH3",
           py::overload_cast<const G4String &, const G4String &, const std::vector<G4double> &,
                             const std::vector<G4double> &, const std::vector<G4double> &, const G4String &,
                             const G4String &, const G4String &, const G4String &, const G4String &, const G4String &>(
              &G4VAnalysisManager::CreateH3),
           py::arg("name"), py::arg("title"), py::arg("xedges"), py::arg("yedges"), py::arg("zedges"),
           py::arg("xunitName") = "none", py::arg("yunitName") = "none", py::arg("zunitName") = "none",
           py::arg("xfcnName") = "none", py::arg("yfcnName") = "none", py::arg("zfcnName") = "none")

      .def("SetH1",
           py::overload_cast<G4int, G4int, G4double, G4double, const G4String &, const G4String &, const G4String &>(
              &G4VAnalysisManager::SetH1),
           py::arg("id"), py::arg("nbins"), py::arg("xmin"), py::arg("xmax"), py::arg("unitName") = "none",
           py::arg("fcnName") = "none", py::arg("binSchemeName") = "linear")

      .def("SetH1",
           py::overload_cast<G4int, const std::vector<G4double> &, const G4String &, const G4String &>(
              &G4VAnalysisManager::SetH1),
           py::arg("id"), py::arg("edges"), py::arg("unitName") = "none", py::arg("fcnName") = "none")

      .def("SetH2",
           py::overload_cast<G4int, G4int, G4double, G4double, G4int, G4double, G4double, const G4String &,
                             const G4String &, const G4String &, const G4String &, const G4String &, const G4String &>(
              &G4VAnalysisManager::SetH2),
           py::arg("id"), py::arg("nxbins"), py::arg("xmin"), py::arg("xmax"), py::arg("nybins"), py::arg("ymin"),
           py::arg("ymax"), py::arg("xunitName") = "none", py::arg("yunitName") = "none", py::arg("xfcnName") = "none",
           py::arg("yfcnName") = "none", py::arg("xbinSchemeName") = "linear", py::arg("ybinSchemeName") = "linear")

      .def("SetH2",
           py::overload_cast<G4int, const std::vector<G4double> &, const std::vector<G4double> &, const G4String &,
                             const G4String &, const G4String &, const G4String &>(&G4VAnalysisManager::SetH2),
           py::arg("id"), py::arg("xedges"), py::arg("yedges"), py::arg("xunitName") = "none",
           py::arg("yunitName") = "none", py::arg("xfcnName") = "none", py::arg("yfcnName") = "none")

      .def("SetH3",
           py::overload_cast<G4int, G4int, G4double, G4double, G4int, G4double, G4double, G4int, G4double, G4double,
                             const G4String &, const G4String &, const G4String &, const G4String &, const G4String &,
                             const G4String &, const G4String &, const G4String &, const G4String &>(
              &G4VAnalysisManager::SetH3),
           py::arg("id"), py::arg("nxbins"), py::arg("xmin"), py::arg("xmax"), py::arg("nybins"), py::arg("ymin"),
           py::arg("ymax"), py::arg("nzbins"), py::arg("zmin"), py::arg("zmax"), py::arg("xunitName") = "none",
           py::arg("yunitName") = "none", py::arg("zunitName") = "none", py::arg("xfcnName") = "none",
           py::arg("yfcnName") = "none", py::arg("zfcnName") = "none", py::arg("xbinSchemeName") = "linear",
           py::arg("ybinSchemeName") = "linear", py::arg("zbinSchemeName") = "linear")

      .def("SetH3",
           py::overload_cast<G4int, const std::vector<G4double> &, const std::vector<G4double> &,
                             const std::vector<G4double> &, const G4String &, const G4String &, const G4String &,
                             const G4String &, const G4String &, const G4String &>(&G4VAnalysisManager::SetH3),
           py::arg("id"), py::arg("xedges"), py::arg("yedges"), py::arg("zedges"), py::arg("xunitName") = "none",
           py::arg("yunitName") = "none", py::arg("zunitName") = "none", py::arg("xfcnName") = "none",
           py::arg("yfcnName") = "none", py::arg("zfcnName") = "none")

      .def("ScaleH1", &G4VAnalysisManager::ScaleH1)
      .def("ScaleH2", &G4VAnalysisManager::ScaleH1)
      .def("ScaleH3", &G4VAnalysisManager::ScaleH1)

      .def("CreateP1",
           py::overload_cast<const G4String &, const G4String &, G4int, G4double, G4double, G4double, G4double,
                             const G4String &, const G4String &, const G4String &, const G4String &, const G4String &>(
              &G4VAnalysisManager::CreateP1),
           py::arg("name"), py::arg("title"), py::arg("nbins"), py::arg("xmin"), py::arg("xmax"), py::arg("ymin") = 0,
           py::arg("ymax") = 0, py::arg("xunitName") = "none", py::arg("yunitName") = "none",
           py::arg("xfcnName") = "none", py::arg("yfcnName") = "none", py::arg("xbinScheme") = "linear")

      .def("CreateP1",
           py::overload_cast<const G4String &, const G4String &, const std::vector<G4double> &, G4double, G4double,
                             const G4String &, const G4String &, const G4String &, const G4String &>(
              &G4VAnalysisManager::CreateP1),
           py::arg("name"), py::arg("title"), py::arg("edges"), py::arg("ymin") = 0, py::arg("ymax") = 0,
           py::arg("xunitName") = "none", py::arg("yunitName") = "none", py::arg("xfcnName") = "none",
           py::arg("yfcnName") = "none")

      .def("CreateP2",
           py::overload_cast<const G4String &, const G4String &, G4int, G4double, G4double, G4int, G4double, G4double,
                             G4double, G4double, const G4String &, const G4String &, const G4String &, const G4String &,
                             const G4String &, const G4String &, const G4String &, const G4String &>(
              &G4VAnalysisManager::CreateP2),
           py::arg("name"), py::arg("title"), py::arg("nxbins"), py::arg("xmin"), py::arg("xmax"), py::arg("nybins"),
           py::arg("ymin"), py::arg("ymax"), py::arg("zmin") = 0, py::arg("zmax") = 0, py::arg("xunitName") = "none",
           py::arg("yunitName") = "none", py::arg("zunitName") = "none", py::arg("xfcnName") = "none",
           py::arg("yfcnName") = "none", py::arg("zfcnName") = "none", py::arg("xbinScheme") = "linear",
           py::arg("ybinScheme") = "linear")

      .def("CreateP2",
           py::overload_cast<const G4String &, const G4String &, const std::vector<G4double> &,
                             const std::vector<G4double> &, G4double, G4double, const G4String &, const G4String &,
                             const G4String &, const G4String &, const G4String &, const G4String &>(
              &G4VAnalysisManager::CreateP2),
           py::arg("name"), py::arg("title"), py::arg("xedges"), py::arg("yedges"), py::arg("zmin") = 0,
           py::arg("zmax") = 0, py::arg("xunitName") = "none", py::arg("yunitName") = "none",
           py::arg("zunitName") = "none", py::arg("xfcnName") = "none", py::arg("yfcnName") = "none",
           py::arg("zfcnName") = "none")

      .def("SetP1",
           py::overload_cast<G4int, G4int, G4double, G4double, G4double, G4double, const G4String &, const G4String &,
                             const G4String &, const G4String &, const G4String &>(&G4VAnalysisManager::SetP1),
           py::arg("id"), py::arg("nbins"), py::arg("xmin"), py::arg("xmax"), py::arg("ymin") = 0, py::arg("ymax") = 0,
           py::arg("xunitName") = "none", py::arg("yunitName") = "none", py::arg("xfcnName") = "none",
           py::arg("yfcnName") = "none", py::arg("xbinScheme") = "linear")

      .def("SetP1",
           py::overload_cast<G4int, const std::vector<G4double> &, G4double, G4double, const G4String &,
                             const G4String &, const G4String &, const G4String &>(&G4VAnalysisManager::SetP1),
           py::arg("id"), py::arg("edges"), py::arg("ymin") = 0, py::arg("ymax") = 0, py::arg("xunitName") = "none",
           py::arg("yunitName") = "none", py::arg("xfcnName") = "none", py::arg("yfcnName") = "none")

      .def("SetP2",
           py::overload_cast<G4int, G4int, G4double, G4double, G4int, G4double, G4double, G4double, G4double,
                             const G4String &, const G4String &, const G4String &, const G4String &, const G4String &,
                             const G4String &, const G4String &, const G4String &>(&G4VAnalysisManager::SetP2),
           py::arg("id"), py::arg("nxbins"), py::arg("xmin"), py::arg("xmax"), py::arg("nybins"), py::arg("ymin"),
           py::arg("ymax"), py::arg("zmin") = 0, py::arg("zmax") = 0, py::arg("xunitName") = "none",
           py::arg("yunitName") = "none", py::arg("zunitName") = "none", py::arg("xfcnName") = "none",
           py::arg("yfcnName") = "none", py::arg("zfcnName") = "none", py::arg("xbinScheme") = "linear",
           py::arg("ybinScheme") = "linear")

      .def("SetP2",
           py::overload_cast<G4int, const std::vector<G4double> &, const std::vector<G4double> &, G4double, G4double,
                             const G4String &, const G4String &, const G4String &, const G4String &, const G4String &,
                             const G4String &>(&G4VAnalysisManager::SetP2),
           py::arg("id"), py::arg("xedges"), py::arg("yedges"), py::arg("zmin") = 0, py::arg("zmax") = 0,
           py::arg("xunitName") = "none", py::arg("yunitName") = "none", py::arg("zunitName") = "none",
           py::arg("xfcnName") = "none", py::arg("yfcnName") = "none", py::arg("zfcnName") = "none")

      .def("ScaleP1", &G4VAnalysisManager::ScaleP1, py::arg("id"), py::arg("factor"))
      .def("ScaleP2", &G4VAnalysisManager::ScaleP2, py::arg("id"), py::arg("factor"))

      .def("CreateNtuple", &G4VAnalysisManager::CreateNtuple, py::arg("name"), py::arg("title"))

      .def("CreateNtupleIColumn", py::overload_cast<const G4String &>(&G4VAnalysisManager::CreateNtupleIColumn),
           py::arg("name"))

      .def("CreateNtupleFColumn", py::overload_cast<const G4String &>(&G4VAnalysisManager::CreateNtupleFColumn),
           py::arg("name"))

      .def("CreateNtupleDColumn", py::overload_cast<const G4String &>(&G4VAnalysisManager::CreateNtupleDColumn),
           py::arg("name"))

      .def("CreateNtupleSColumn", py::overload_cast<const G4String &>(&G4VAnalysisManager::CreateNtupleSColumn),
           py::arg("name"))

      // TODO maybe reference to std::vector reference to py lists do not work
      //  .def("CreateNtupleIColumn",
      //       py::overload_cast<const G4String &, std::vector<int> &>(&G4VAnalysisManager::CreateNtupleIColumn),
      //       py::arg("name"), py::arg("vector"))

      //  .def("CreateNtupleFColumn",
      //       py::overload_cast<const G4String &, std::vector<float> &>(&G4VAnalysisManager::CreateNtupleFColumn),
      //       py::arg("name"), py::arg("vector"))

      //  .def("CreateNtupleDColumn",
      //       py::overload_cast<const G4String &, std::vector<double> &>(&G4VAnalysisManager::CreateNtupleDColumn),
      //       py::arg("name"), py::arg("vector"))

      .def("FinishNtuple", py::overload_cast<>(&G4VAnalysisManager::FinishNtuple),
           py::call_guard<py::gil_scoped_release>())

      .def("CreateNtupleIColumn", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::CreateNtupleIColumn),
           py::arg("ntupleId"), py::arg("name"), py::call_guard<py::gil_scoped_release>())

      .def("CreateNtupleFColumn", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::CreateNtupleFColumn),
           py::arg("ntupleId"), py::arg("name"), py::call_guard<py::gil_scoped_release>())

      .def("CreateNtupleDColumn", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::CreateNtupleDColumn),
           py::arg("ntupleId"), py::arg("name"), py::call_guard<py::gil_scoped_release>())

      .def("CreateNtupleSColumn", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::CreateNtupleSColumn),
           py::arg("ntupleId"), py::arg("name"), py::call_guard<py::gil_scoped_release>())

      // TODO maybe reference to std::vector reference to py lists do not work
      //  .def("CreateNtupleIColumn",
      //       py::overload_cast<G4int, const G4String &, std::vector<int> &>(&G4VAnalysisManager::CreateNtupleIColumn),
      //       py::arg("ntupleId"), py::arg("name"), py::arg("vector"))

      //  .def("CreateNtupleFColumn",
      //       py::overload_cast<G4int, const G4String &, std::vector<float>
      //       &>(&G4VAnalysisManager::CreateNtupleFColumn), py::arg("ntupleId"), py::arg("name"), py::arg("vector"))

      //  .def("CreateNtupleDColumn",
      //       py::overload_cast<G4int, const G4String &, std::vector<double>
      //       &>(&G4VAnalysisManager::CreateNtupleDColumn), py::arg("ntupleId"), py::arg("name"), py::arg("vector"))

      .def("FinishNtuple", py::overload_cast<G4int>(&G4VAnalysisManager::FinishNtuple),
           py::call_guard<py::gil_scoped_release>())

      .def("SetNtupleMerging", &G4VAnalysisManager::SetNtupleMerging, py::arg("mergeNtuples"),
           py::arg("nofReducedNtupleFiles") = 0)

      .def("SetNtupleRowWise", &G4VAnalysisManager::SetNtupleRowWise, py::arg("rowWise"), py::arg("rowMode") = true)
      .def("SetBasketSize", &G4VAnalysisManager::SetBasketSize, py::arg("basketSize"))
      .def("SetBasketEntries", &G4VAnalysisManager::SetBasketEntries, py::arg("basketEntries"))

      .def("SetFirstHistoId", &G4VAnalysisManager::SetFirstHistoId, py::arg("firstId"))
      .def("SetFirstH1Id", &G4VAnalysisManager::SetFirstH1Id, py::arg("firstId"))
      .def("SetFirstH2Id", &G4VAnalysisManager::SetFirstH2Id, py::arg("firstId"))
      .def("SetFirstH3Id", &G4VAnalysisManager::SetFirstH3Id, py::arg("firstId"))
      .def("SetFirstProfileId", &G4VAnalysisManager::SetFirstProfileId, py::arg("firstId"))
      .def("SetFirstP1Id", &G4VAnalysisManager::SetFirstP1Id, py::arg("firstId"))
      .def("SetFirstP2Id", &G4VAnalysisManager::SetFirstP2Id, py::arg("firstId"))
      .def("SetFirstNtupleId", &G4VAnalysisManager::SetFirstNtupleId, py::arg("firstId"))
      .def("SetFirstNtupleColumnId", &G4VAnalysisManager::SetFirstNtupleColumnId, py::arg("firstId"))

      .def("FillH1", &G4VAnalysisManager::FillH1, py::arg("id"), py::arg("value"), py::arg("weight") = 1.0,
           py::call_guard<py::gil_scoped_release>())

      .def("FillH2", &G4VAnalysisManager::FillH2, py::arg("id"), py::arg("xvalue"), py::arg("yvalue"),
           py::arg("weight") = 1.0, py::call_guard<py::gil_scoped_release>())

      .def("FillH3", &G4VAnalysisManager::FillH3, py::arg("id"), py::arg("xvalue"), py::arg("yvalue"),
           py::arg("zvalue"), py::arg("weight") = 1.0, py::call_guard<py::gil_scoped_release>())

      .def("FillP1", &G4VAnalysisManager::FillP1, py::arg("id"), py::arg("xvalue"), py::arg("yvalue"),
           py::arg("weight") = 1.0, py::call_guard<py::gil_scoped_release>())

      .def("FillP2", &G4VAnalysisManager::FillP2, py::arg("id"), py::arg("xvalue"), py::arg("yvalue"),
           py::arg("zvalue"), py::arg("weight") = 1.0, py::call_guard<py::gil_scoped_release>())

      .def("FillNtupleIColumn", py::overload_cast<G4int, G4int>(&G4VAnalysisManager::FillNtupleIColumn), py::arg("id"),
           py::arg("value"), py::call_guard<py::gil_scoped_release>())

      .def("FillNtupleFColumn", py::overload_cast<G4int, G4float>(&G4VAnalysisManager::FillNtupleFColumn),
           py::arg("id"), py::arg("value"), py::call_guard<py::gil_scoped_release>())

      .def("FillNtupleDColumn", py::overload_cast<G4int, G4double>(&G4VAnalysisManager::FillNtupleDColumn),
           py::arg("id"), py::arg("value"), py::call_guard<py::gil_scoped_release>())

      .def("FillNtupleSColumn", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::FillNtupleSColumn),
           py::arg("id"), py::arg("value"), py::call_guard<py::gil_scoped_release>())

      .def("AddNtupleRow", py::overload_cast<>(&G4VAnalysisManager::AddNtupleRow),
           py::call_guard<py::gil_scoped_release>())

      .def("FillNtupleIColumn", py::overload_cast<G4int, G4int, G4int>(&G4VAnalysisManager::FillNtupleIColumn),
           py::arg("ntupleId"), py::arg("columnId"), py::arg("value"), py::call_guard<py::gil_scoped_release>())

      .def("FillNtupleFColumn", py::overload_cast<G4int, G4int, G4float>(&G4VAnalysisManager::FillNtupleFColumn),
           py::arg("ntupleId"), py::arg("columnId"), py::arg("value"), py::call_guard<py::gil_scoped_release>())

      .def("FillNtupleDColumn", py::overload_cast<G4int, G4int, G4double>(&G4VAnalysisManager::FillNtupleDColumn),
           py::arg("ntupleId"), py::arg("columnId"), py::arg("value"), py::call_guard<py::gil_scoped_release>())

      .def("FillNtupleSColumn",
           py::overload_cast<G4int, G4int, const G4String &>(&G4VAnalysisManager::FillNtupleSColumn),
           py::arg("ntupleId"), py::arg("columnId"), py::arg("value"), py::call_guard<py::gil_scoped_release>())

      .def("AddNtupleRow", py::overload_cast<G4int>(&G4VAnalysisManager::AddNtupleRow), py::arg("ntupleId"),
           py::call_guard<py::gil_scoped_release>())

      .def("SetActivation", &G4VAnalysisManager::SetActivation, py::arg("activation"))
      .def("GetActivation", &G4VAnalysisManager::GetActivation)
      .def("IsActive", &G4VAnalysisManager::IsActive)

      .def("IsAscii", &G4VAnalysisManager::IsAscii)
      .def("IsPlotting", &G4VAnalysisManager::IsPlotting)

      .def("GetFirstH1Id", &G4VAnalysisManager::GetFirstH1Id)
      .def("GetFirstH2Id", &G4VAnalysisManager::GetFirstH2Id)
      .def("GetFirstH3Id", &G4VAnalysisManager::GetFirstH3Id)
      .def("GetFirstP1Id", &G4VAnalysisManager::GetFirstP1Id)
      .def("GetFirstP2Id", &G4VAnalysisManager::GetFirstP2Id)
      .def("GetFirstNtupleId", &G4VAnalysisManager::GetFirstNtupleId)
      .def("GetFirstNtupleColumnId", &G4VAnalysisManager::GetFirstNtupleColumnId)

      .def("GetNofH1s", &G4VAnalysisManager::GetNofH1s)
      .def("GetNofH2s", &G4VAnalysisManager::GetNofH2s)
      .def("GetNofH3s", &G4VAnalysisManager::GetNofH3s)
      .def("GetNofP1s", &G4VAnalysisManager::GetNofP1s)
      .def("GetNofP2s", &G4VAnalysisManager::GetNofP2s)
      .def("GetNofNtuples", &G4VAnalysisManager::GetNofNtuples)

      .def("GetH1Id", &G4VAnalysisManager::GetH1Id, py::arg("name"), py::arg("warn") = true)
      .def("GetH2Id", &G4VAnalysisManager::GetH2Id, py::arg("name"), py::arg("warn") = true)
      .def("GetH3Id", &G4VAnalysisManager::GetH3Id, py::arg("name"), py::arg("warn") = true)
      .def("GetP1Id", &G4VAnalysisManager::GetP1Id, py::arg("name"), py::arg("warn") = true)
      .def("GetP2Id", &G4VAnalysisManager::GetP2Id, py::arg("name"), py::arg("warn") = true)

      .def("SetH1Activation", py::overload_cast<G4bool>(&G4VAnalysisManager::SetH1Activation), py::arg("activation"))

      .def("SetH1Activation", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetH1Activation), py::arg("id"),
           py::arg("activation"))

      .def("SetH1Ascii", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetH1Ascii), py::arg("id"),
           py::arg("ascii"))

      .def("SetH1Plotting", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetH1Plotting), py::arg("id"),
           py::arg("plotting"))

      .def("SetH1FileName", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::SetH1FileName),
           py::arg("id"), py::arg("fileName"))

      .def("SetH2Activation", py::overload_cast<G4bool>(&G4VAnalysisManager::SetH2Activation), py::arg("activation"))

      .def("SetH2Activation", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetH2Activation), py::arg("id"),
           py::arg("activation"))

      .def("SetH2Ascii", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetH2Ascii), py::arg("id"),
           py::arg("ascii"))

      .def("SetH2Plotting", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetH2Plotting), py::arg("id"),
           py::arg("plotting"))

      .def("SetH2FileName", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::SetH2FileName),
           py::arg("id"), py::arg("fileName"))

      .def("SetH3Activation", py::overload_cast<G4bool>(&G4VAnalysisManager::SetH3Activation), py::arg("activation"))

      .def("SetH3Activation", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetH3Activation), py::arg("id"),
           py::arg("activation"))

      .def("SetH3Ascii", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetH3Ascii), py::arg("id"),
           py::arg("ascii"))

      .def("SetH3Plotting", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetH3Plotting), py::arg("id"),
           py::arg("plotting"))

      .def("SetH3FileName", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::SetH3FileName),
           py::arg("id"), py::arg("fileName"))

      .def("SetP1Activation", py::overload_cast<G4bool>(&G4VAnalysisManager::SetP1Activation), py::arg("activation"))

      .def("SetP1Activation", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetP1Activation), py::arg("id"),
           py::arg("activation"))

      .def("SetP1Ascii", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetP1Ascii), py::arg("id"),
           py::arg("ascii"))

      .def("SetP1Plotting", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetP1Plotting), py::arg("id"),
           py::arg("plotting"))

      .def("SetP1FileName", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::SetP1FileName),
           py::arg("id"), py::arg("fileName"))

      .def("SetP2Activation", py::overload_cast<G4bool>(&G4VAnalysisManager::SetP2Activation), py::arg("activation"))

      .def("SetP2Activation", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetP2Activation), py::arg("id"),
           py::arg("activation"))

      .def("SetP2Ascii", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetP2Ascii), py::arg("id"),
           py::arg("ascii"))

      .def("SetP2Plotting", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetP2Plotting), py::arg("id"),
           py::arg("plotting"))

      .def("SetP2FileName", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::SetP2FileName),
           py::arg("id"), py::arg("fileName"))

      .def("SetNtupleActivation", py::overload_cast<G4bool>(&G4VAnalysisManager::SetNtupleActivation),
           py::arg("activation"))

      .def("SetNtupleActivation", py::overload_cast<G4int, G4bool>(&G4VAnalysisManager::SetNtupleActivation),
           py::arg("id"), py::arg("activation"))

      .def("SetNtupleFileName", py::overload_cast<const G4String &>(&G4VAnalysisManager::SetNtupleFileName),
           py::arg("fileName"))

      .def("SetNtupleFileName", py::overload_cast<G4int, const G4String &>(&G4VAnalysisManager::SetNtupleFileName),
           py::arg("id"), py::arg("fileName"))

      .def("GetH1Nbins", &G4VAnalysisManager::GetH1Nbins, py::arg("id"))
      .def("GetH1Xmin", &G4VAnalysisManager::GetH1Xmin, py::arg("id"))
      .def("GetH1Xmax", &G4VAnalysisManager::GetH1Xmax, py::arg("id"))
      .def("GetH1Width", &G4VAnalysisManager::GetH1Width, py::arg("id"))

      .def("GetH2Nxbins", &G4VAnalysisManager::GetH2Nxbins, py::arg("id"))
      .def("GetH2Xmin", &G4VAnalysisManager::GetH2Xmin, py::arg("id"))
      .def("GetH2Xmax", &G4VAnalysisManager::GetH2Xmax, py::arg("id"))
      .def("GetH2XWidth", &G4VAnalysisManager::GetH2XWidth, py::arg("id"))
      .def("GetH2Nybins", &G4VAnalysisManager::GetH2Nybins, py::arg("id"))
      .def("GetH2Ymin", &G4VAnalysisManager::GetH2Ymin, py::arg("id"))
      .def("GetH2Ymax", &G4VAnalysisManager::GetH2Ymax, py::arg("id"))
      .def("GetH2YWidth", &G4VAnalysisManager::GetH2YWidth, py::arg("id"))

      .def("GetH3Nxbins", &G4VAnalysisManager::GetH3Nxbins, py::arg("id"))
      .def("GetH3Xmin", &G4VAnalysisManager::GetH3Xmin, py::arg("id"))
      .def("GetH3Xmax", &G4VAnalysisManager::GetH3Xmax, py::arg("id"))
      .def("GetH3XWidth", &G4VAnalysisManager::GetH3XWidth, py::arg("id"))
      .def("GetH3Nybins", &G4VAnalysisManager::GetH3Nybins, py::arg("id"))
      .def("GetH3Ymin", &G4VAnalysisManager::GetH3Ymin, py::arg("id"))
      .def("GetH3Ymax", &G4VAnalysisManager::GetH3Ymax, py::arg("id"))
      .def("GetH3YWidth", &G4VAnalysisManager::GetH3YWidth, py::arg("id"))
      .def("GetH3Nzbins", &G4VAnalysisManager::GetH3Nzbins, py::arg("id"))
      .def("GetH3Zmin", &G4VAnalysisManager::GetH3Zmin, py::arg("id"))
      .def("GetH3Zmax", &G4VAnalysisManager::GetH3Zmax, py::arg("id"))
      .def("GetH3ZWidth", &G4VAnalysisManager::GetH3ZWidth, py::arg("id"))

      .def("GetP1Nbins", &G4VAnalysisManager::GetP1Nbins, py::arg("id"))
      .def("GetP1Xmin", &G4VAnalysisManager::GetP1Xmin, py::arg("id"))
      .def("GetP1Xmax", &G4VAnalysisManager::GetP1Xmax, py::arg("id"))
      .def("GetP1XWidth", &G4VAnalysisManager::GetP1XWidth, py::arg("id"))
      .def("GetP1Ymin", &G4VAnalysisManager::GetP1Ymin, py::arg("id"))
      .def("GetP1Ymax", &G4VAnalysisManager::GetP1Ymax, py::arg("id"))

      .def("GetP2Nxbins", &G4VAnalysisManager::GetP2Nxbins, py::arg("id"))
      .def("GetP2Xmin", &G4VAnalysisManager::GetP2Xmin, py::arg("id"))
      .def("GetP2Xmax", &G4VAnalysisManager::GetP2Xmax, py::arg("id"))
      .def("GetP2XWidth", &G4VAnalysisManager::GetP2XWidth, py::arg("id"))
      .def("GetP2Nybins", &G4VAnalysisManager::GetP2Nybins, py::arg("id"))
      .def("GetP2Ymin", &G4VAnalysisManager::GetP2Ymin, py::arg("id"))
      .def("GetP2Ymax", &G4VAnalysisManager::GetP2Ymax, py::arg("id"))
      .def("GetP2YWidth", &G4VAnalysisManager::GetP2YWidth, py::arg("id"))
      .def("GetP2Zmin", &G4VAnalysisManager::GetP2Zmin, py::arg("id"))
      .def("GetP2Zmax", &G4VAnalysisManager::GetP2Zmax, py::arg("id"))

      .def("GetH1Name", &G4VAnalysisManager::GetH1Name, py::arg("id"))
      .def("GetH1Unit", &G4VAnalysisManager::GetH1Unit, py::arg("id"))
      .def("GetH1Activation", &G4VAnalysisManager::GetH1Activation, py::arg("id"))
      .def("GetH1Ascii", &G4VAnalysisManager::GetH1Ascii, py::arg("id"))
      .def("GetH1Plotting", &G4VAnalysisManager::GetH1Plotting, py::arg("id"))
      //.def("GetH1FileName", &G4VAnalysisManager::GetH1FileName, py::arg("id")) -> no implementation

      .def("GetH2Name", &G4VAnalysisManager::GetH2Name, py::arg("id"))
      .def("GetH2XUnit", &G4VAnalysisManager::GetH2XUnit, py::arg("id"))
      .def("GetH2YUnit", &G4VAnalysisManager::GetH2YUnit, py::arg("id"))
      .def("GetH2Activation", &G4VAnalysisManager::GetH2Activation, py::arg("id"))
      .def("GetH2Ascii", &G4VAnalysisManager::GetH2Ascii, py::arg("id"))
      .def("GetH2Plotting", &G4VAnalysisManager::GetH2Plotting, py::arg("id"))

      .def("GetH3Name", &G4VAnalysisManager::GetH3Name, py::arg("id"))
      .def("GetH3XUnit", &G4VAnalysisManager::GetH3XUnit, py::arg("id"))
      .def("GetH3YUnit", &G4VAnalysisManager::GetH3YUnit, py::arg("id"))
      .def("GetH3ZUnit", &G4VAnalysisManager::GetH3ZUnit, py::arg("id"))
      .def("GetH3Activation", &G4VAnalysisManager::GetH3Activation, py::arg("id"))
      .def("GetH3Ascii", &G4VAnalysisManager::GetH3Ascii, py::arg("id"))
      .def("GetH3Plotting", &G4VAnalysisManager::GetH3Plotting, py::arg("id"))

      .def("GetP1Name", &G4VAnalysisManager::GetP1Name, py::arg("id"))
      .def("GetP1XUnit", &G4VAnalysisManager::GetP1XUnit, py::arg("id"))
      .def("GetP1YUnit", &G4VAnalysisManager::GetP1YUnit, py::arg("id"))
      .def("GetP1Activation", &G4VAnalysisManager::GetP1Activation, py::arg("id"))
      .def("GetP1Ascii", &G4VAnalysisManager::GetP1Ascii, py::arg("id"))
      .def("GetP1Plotting", &G4VAnalysisManager::GetP1Plotting, py::arg("id"))

      .def("GetP2Name", &G4VAnalysisManager::GetP2Name, py::arg("id"))
      .def("GetP2XUnit", &G4VAnalysisManager::GetP2XUnit, py::arg("id"))
      .def("GetP2YUnit", &G4VAnalysisManager::GetP2YUnit, py::arg("id"))
      .def("GetP2ZUnit", &G4VAnalysisManager::GetP2ZUnit, py::arg("id"))
      .def("GetP2Activation", &G4VAnalysisManager::GetP2Activation, py::arg("id"))
      .def("GetP2Ascii", &G4VAnalysisManager::GetP2Ascii, py::arg("id"))
      .def("GetP2Plotting", &G4VAnalysisManager::GetP2Plotting, py::arg("id"))

      .def("GetNtupleActivation", &G4VAnalysisManager::GetNtupleActivation, py::arg("id"))
      //.def("GetNtupleFileName", &G4VAnalysisManager::GetNtupleFileName, py::arg("id")) -> no implementation

      .def("SetH1Title", &G4VAnalysisManager::SetH1Title, py::arg("id"), py::arg("title"))
      .def("SetH1XAxisTitle", &G4VAnalysisManager::SetH1XAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetH1YAxisTitle", &G4VAnalysisManager::SetH1YAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetH1XAxisIsLog", &G4VAnalysisManager::SetH1XAxisIsLog, py::arg("id"), py::arg("isLog"))
      .def("SetH1YAxisIsLog", &G4VAnalysisManager::SetH1YAxisIsLog, py::arg("id"), py::arg("isLog"))

      .def("SetH2Title", &G4VAnalysisManager::SetH2Title, py::arg("id"), py::arg("title"))
      .def("SetH2XAxisTitle", &G4VAnalysisManager::SetH2XAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetH2YAxisTitle", &G4VAnalysisManager::SetH2YAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetH2ZAxisTitle", &G4VAnalysisManager::SetH2ZAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetH2XAxisIsLog", &G4VAnalysisManager::SetH2XAxisIsLog, py::arg("id"), py::arg("isLog"))
      .def("SetH2YAxisIsLog", &G4VAnalysisManager::SetH2YAxisIsLog, py::arg("id"), py::arg("isLog"))
      .def("SetH2ZAxisIsLog", &G4VAnalysisManager::SetH2ZAxisIsLog, py::arg("id"), py::arg("isLog"))

      .def("SetH3Title", &G4VAnalysisManager::SetH3Title, py::arg("id"), py::arg("title"))
      .def("SetH3XAxisTitle", &G4VAnalysisManager::SetH3XAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetH3YAxisTitle", &G4VAnalysisManager::SetH3YAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetH3ZAxisTitle", &G4VAnalysisManager::SetH3ZAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetH3XAxisIsLog", &G4VAnalysisManager::SetH3XAxisIsLog, py::arg("id"), py::arg("isLog"))
      .def("SetH3YAxisIsLog", &G4VAnalysisManager::SetH3YAxisIsLog, py::arg("id"), py::arg("isLog"))
      .def("SetH3ZAxisIsLog", &G4VAnalysisManager::SetH3ZAxisIsLog, py::arg("id"), py::arg("isLog"))

      .def("SetP1Title", &G4VAnalysisManager::SetP1Title, py::arg("id"), py::arg("title"))
      .def("SetP1XAxisTitle", &G4VAnalysisManager::SetP1XAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetP1YAxisTitle", &G4VAnalysisManager::SetP1YAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetP1XAxisIsLog", &G4VAnalysisManager::SetP1XAxisIsLog, py::arg("id"), py::arg("isLog"))
      .def("SetP1YAxisIsLog", &G4VAnalysisManager::SetP1YAxisIsLog, py::arg("id"), py::arg("isLog"))

      .def("SetP2Title", &G4VAnalysisManager::SetP2Title, py::arg("id"), py::arg("title"))
      .def("SetP2XAxisTitle", &G4VAnalysisManager::SetP2XAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetP2YAxisTitle", &G4VAnalysisManager::SetP2YAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetP2ZAxisTitle", &G4VAnalysisManager::SetP2ZAxisTitle, py::arg("id"), py::arg("title"))
      .def("SetP2XAxisIsLog", &G4VAnalysisManager::SetP2XAxisIsLog, py::arg("id"), py::arg("isLog"))
      .def("SetP2YAxisIsLog", &G4VAnalysisManager::SetP2YAxisIsLog, py::arg("id"), py::arg("isLog"))
      .def("SetP2ZAxisIsLog", &G4VAnalysisManager::SetP2ZAxisIsLog, py::arg("id"), py::arg("isLog"))

      .def("GetH1Title", &G4VAnalysisManager::GetH1Title, py::arg("id"))
      .def("GetH1XAxisTitle", &G4VAnalysisManager::GetH1XAxisTitle, py::arg("id"))
      .def("GetH1YAxisTitle", &G4VAnalysisManager::GetH1YAxisTitle, py::arg("id"))
      .def("GetH1XAxisIsLog", &G4VAnalysisManager::GetH1XAxisIsLog, py::arg("id"))
      .def("GetH1YAxisIsLog", &G4VAnalysisManager::GetH1YAxisIsLog, py::arg("id"))

      .def("GetH2Title", &G4VAnalysisManager::GetH2Title, py::arg("id"))
      .def("GetH2XAxisTitle", &G4VAnalysisManager::GetH2XAxisTitle, py::arg("id"))
      .def("GetH2YAxisTitle", &G4VAnalysisManager::GetH2YAxisTitle, py::arg("id"))
      .def("GetH2ZAxisTitle", &G4VAnalysisManager::GetH2ZAxisTitle, py::arg("id"))
      .def("GetH2XAxisIsLog", &G4VAnalysisManager::GetH2XAxisIsLog, py::arg("id"))
      .def("GetH2YAxisIsLog", &G4VAnalysisManager::GetH2YAxisIsLog, py::arg("id"))
      .def("GetH2ZAxisIsLog", &G4VAnalysisManager::GetH2ZAxisIsLog, py::arg("id"))

      .def("GetH3Title", &G4VAnalysisManager::GetH3Title, py::arg("id"))
      .def("GetH3XAxisTitle", &G4VAnalysisManager::GetH3XAxisTitle, py::arg("id"))
      .def("GetH3YAxisTitle", &G4VAnalysisManager::GetH3YAxisTitle, py::arg("id"))
      .def("GetH3ZAxisTitle", &G4VAnalysisManager::GetH3ZAxisTitle, py::arg("id"))
      .def("GetH3XAxisIsLog", &G4VAnalysisManager::GetH3XAxisIsLog, py::arg("id"))
      .def("GetH3YAxisIsLog", &G4VAnalysisManager::GetH3YAxisIsLog, py::arg("id"))
      .def("GetH3ZAxisIsLog", &G4VAnalysisManager::GetH3ZAxisIsLog, py::arg("id"))

      .def("GetP1Title", &G4VAnalysisManager::GetP1Title, py::arg("id"))
      .def("GetP1XAxisTitle", &G4VAnalysisManager::GetP1XAxisTitle, py::arg("id"))
      .def("GetP1YAxisTitle", &G4VAnalysisManager::GetP1YAxisTitle, py::arg("id"))
      .def("GetP1XAxisIsLog", &G4VAnalysisManager::GetP1XAxisIsLog, py::arg("id"))
      .def("GetP1YAxisIsLog", &G4VAnalysisManager::GetP1YAxisIsLog, py::arg("id"))

      .def("GetP2Title", &G4VAnalysisManager::GetP2Title, py::arg("id"))
      .def("GetP2XAxisTitle", &G4VAnalysisManager::GetP2XAxisTitle, py::arg("id"))
      .def("GetP2YAxisTitle", &G4VAnalysisManager::GetP2YAxisTitle, py::arg("id"))
      .def("GetP2ZAxisTitle", &G4VAnalysisManager::GetP2ZAxisTitle, py::arg("id"))
      .def("GetP2XAxisIsLog", &G4VAnalysisManager::GetP2XAxisIsLog, py::arg("id"))
      .def("GetP2YAxisIsLog", &G4VAnalysisManager::GetP2YAxisIsLog, py::arg("id"))
      .def("GetP2ZAxisIsLog", &G4VAnalysisManager::GetP2ZAxisIsLog, py::arg("id"))

      .def("SetVerboseLevel", &G4VAnalysisManager::SetVerboseLevel, py::arg("verboseLevel"))
      .def("GetVerboseLevel", &G4VAnalysisManager::GetVerboseLevel)
      .def("GetType", &G4VAnalysisManager::GetType)
      .def("GetFileType", &G4VAnalysisManager::GetFileType);
}
