#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VisManager.hh>
#include <G4TrajectoryModelFactories.hh>
#include <G4VSolid.hh>
#include <G4VPhysicalVolume.hh>
#include <G4LogicalVolume.hh>
#include <G4VDigi.hh>
#include <G4Text.hh>
#include <G4Circle.hh>
#include <G4Polyhedron.hh>
#include <G4Polymarker.hh>
#include <G4Polyline.hh>
#include <G4Square.hh>
#include <G4VHit.hh>
#include <G4VTrajectory.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VisManager(py::module &m)
{
   py::class_<G4VisManager, G4VVisManager> vismanager(m, "G4VisManager", "visualization manager");

   py::enum_<G4VisManager::Verbosity>(vismanager, "Verbosity")
      .value("quiet", G4VisManager::quiet)
      .value("startup", G4VisManager::startup)
      .value("errors", G4VisManager::errors)
      .value("warnings", G4VisManager::warnings)
      .value("confirmations", G4VisManager::confirmations)
      .value("parameters", G4VisManager::parameters)
      .value("all", G4VisManager::all)
      .export_values();

   vismanager
      .def_static("GetInstance", &G4VisManager::GetInstance, py::return_value_policy::reference)

      .def("Initialize", &G4VisManager::Initialize)
      .def("Initialise", &G4VisManager::Initialise)
      .def("SetVerboseLevel", py::overload_cast<G4int>(&G4VisManager::SetVerboseLevel))
      .def("SetVerboseLevel", py::overload_cast<const G4String &>(&G4VisManager::SetVerboseLevel))
      //.def("SetVerboseLevel", py::overload_cast<G4VisManager::Verbosity>(&G4VisManager::SetVerboseLevel))
      .def_static("GetVerbosity", &G4VisManager::GetVerbosity)
      .def("RegisterGraphicsSystem",
           [](G4VisManager &self, py::disown_ptr<G4VGraphicsSystem> graphicssystem) {
              return self.RegisterGraphicsSystem(graphicssystem);
           })

      .def("Draw", py::overload_cast<const G4Circle &, const G4Transform3D &>(&G4VisManager::Draw), py::arg("circle"),
           py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4Polyhedron &, const G4Transform3D &>(&G4VisManager::Draw),
           py::arg("polyhedron"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4Polyline &, const G4Transform3D &>(&G4VisManager::Draw),
           py::arg("polyline"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4Polymarker &, const G4Transform3D &>(&G4VisManager::Draw),
           py::arg("polymarker"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4Square &, const G4Transform3D &>(&G4VisManager::Draw), py::arg("square"),
           py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4Text &, const G4Transform3D &>(&G4VisManager::Draw), py::arg("text"),
           py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Circle &, const G4Transform3D &>(&G4VisManager::Draw2D),
           py::arg("circle"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Polyhedron &, const G4Transform3D &>(&G4VisManager::Draw2D),
           py::arg("polyhedron"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Polyline &, const G4Transform3D &>(&G4VisManager::Draw2D),
           py::arg("polyline"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Polymarker &, const G4Transform3D &>(&G4VisManager::Draw2D),
           py::arg("polymarker"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Square &, const G4Transform3D &>(&G4VisManager::Draw2D),
           py::arg("square"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Text &, const G4Transform3D &>(&G4VisManager::Draw2D), py::arg("text"),
           py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4VTrajectory &>(&G4VisManager::Draw))

      .def("Draw", py::overload_cast<const G4VHit &>(&G4VisManager::Draw))

      .def("Draw", py::overload_cast<const G4VDigi &>(&G4VisManager::Draw))

      .def("Draw",
           py::overload_cast<const G4LogicalVolume &, const G4VisAttributes &, const G4Transform3D &>(
              &G4VisManager::Draw),
           py::arg("logVol"), py::arg("visAttr"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw",
           py::overload_cast<const G4VPhysicalVolume &, const G4VisAttributes &, const G4Transform3D &>(
              &G4VisManager::Draw),
           py::arg("physVol"), py::arg("visAttr"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw",
           py::overload_cast<const G4VSolid &, const G4VisAttributes &, const G4Transform3D &>(&G4VisManager::Draw),
           py::arg("solid"), py::arg("visAttr"), py::arg("objectTransformation") = G4Transform3D())

      .def("CreateSceneHandler", &G4VisManager::CreateSceneHandler, py::arg("name") = "")
      .def("CreateViewer", &G4VisManager::CreateViewer, py::arg("name") = "", py::arg("XGeometry") = "");
}
