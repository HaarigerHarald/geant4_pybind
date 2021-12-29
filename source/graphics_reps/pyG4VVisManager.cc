#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4VVisManager.hh>
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
#include <G4VisAttributes.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4VVisManager(py::module &m)
{
   py::class_<G4VVisManager>(m, "G4VVisManager")

      .def_static("GetConcreteInstance", &G4VVisManager::GetConcreteInstance, "Get an instance of G4VVisManager",
                  py::return_value_policy::reference)

      .def("Draw", py::overload_cast<const G4Circle &, const G4Transform3D &>(&G4VVisManager::Draw), py::arg("circle"),
           py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4Polyhedron &, const G4Transform3D &>(&G4VVisManager::Draw),
           py::arg("polyhedron"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4Polyline &, const G4Transform3D &>(&G4VVisManager::Draw),
           py::arg("polyline"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4Polymarker &, const G4Transform3D &>(&G4VVisManager::Draw),
           py::arg("polymarker"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4Square &, const G4Transform3D &>(&G4VVisManager::Draw), py::arg("square"),
           py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4Text &, const G4Transform3D &>(&G4VVisManager::Draw), py::arg("text"),
           py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Circle &, const G4Transform3D &>(&G4VVisManager::Draw2D),
           py::arg("circle"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Polyhedron &, const G4Transform3D &>(&G4VVisManager::Draw2D),
           py::arg("polyhedron"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Polyline &, const G4Transform3D &>(&G4VVisManager::Draw2D),
           py::arg("polyline"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Polymarker &, const G4Transform3D &>(&G4VVisManager::Draw2D),
           py::arg("polymarker"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Square &, const G4Transform3D &>(&G4VVisManager::Draw2D),
           py::arg("square"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw2D", py::overload_cast<const G4Text &, const G4Transform3D &>(&G4VVisManager::Draw2D), py::arg("text"),
           py::arg("objectTransformation") = G4Transform3D())

      .def("Draw", py::overload_cast<const G4VTrajectory &>(&G4VVisManager::Draw))

      .def("Draw", py::overload_cast<const G4VHit &>(&G4VVisManager::Draw))

      .def("Draw", py::overload_cast<const G4VDigi &>(&G4VVisManager::Draw))

      .def("Draw",
           py::overload_cast<const G4LogicalVolume &, const G4VisAttributes &, const G4Transform3D &>(
              &G4VVisManager::Draw),
           py::arg("logVol"), py::arg("visAttr"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw",
           py::overload_cast<const G4VPhysicalVolume &, const G4VisAttributes &, const G4Transform3D &>(
              &G4VVisManager::Draw),
           py::arg("physVol"), py::arg("visAttr"), py::arg("objectTransformation") = G4Transform3D())

      .def("Draw",
           py::overload_cast<const G4VSolid &, const G4VisAttributes &, const G4Transform3D &>(&G4VVisManager::Draw),
           py::arg("solid"), py::arg("visAttr"), py::arg("objectTransformation") = G4Transform3D())

      .def("BeginDraw", &G4VVisManager::BeginDraw, py::arg("objectTransformation") = G4Transform3D())
      .def("EndDraw", &G4VVisManager::EndDraw)
      .def("BeginDraw2D", &G4VVisManager::BeginDraw2D, py::arg("objectTransformation") = G4Transform3D())
      .def("EndDraw2D", &G4VVisManager::EndDraw2D)

      .def("GeometryHasChanged", &G4VVisManager::GeometryHasChanged)
      .def("IgnoreStateChanges", &G4VVisManager::IgnoreStateChanges)
      .def("NotifyHandlers", &G4VVisManager::NotifyHandlers)
      .def("DispatchToModel", &G4VVisManager::DispatchToModel)
      .def("FilterTrajectory", &G4VVisManager::FilterTrajectory)
      .def("FilterHit", &G4VVisManager::FilterHit)
      .def("FilterDigi", &G4VVisManager::FilterDigi);
}
