#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4GeomTools.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4GeomTools(py::module &m)
{
   py::class_<G4GeomTools>(m, "G4GeomTools")

      .def(py::init<>())
      .def("__copy__", [](const G4GeomTools &self) { return G4GeomTools(self); })
      .def("__deepcopy__", [](const G4GeomTools &self, py::dict) { return G4GeomTools(self); })
      .def_static(
         "TriangleArea",
         py::overload_cast<G4double, G4double, G4double, G4double, G4double, G4double>(&G4GeomTools::TriangleArea),
         py::arg("Ax"), py::arg("Ay"), py::arg("Bx"), py::arg("By"), py::arg("Cx"), py::arg("Cy"))

      .def_static(
         "TriangleArea",
         py::overload_cast<G4TwoVector const &, G4TwoVector const &, G4TwoVector const &>(&G4GeomTools::TriangleArea),
         py::arg("A"), py::arg("B"), py::arg("C"))

      .def_static("QuadArea", &G4GeomTools::QuadArea, py::arg("A"), py::arg("B"), py::arg("C"), py::arg("D"))
      .def_static("PolygonArea", &G4GeomTools::PolygonArea, py::arg("polygon"))
      .def_static("PointInTriangle",
                  py::overload_cast<G4double, G4double, G4double, G4double, G4double, G4double, G4double, G4double>(
                     &G4GeomTools::PointInTriangle),
                  py::arg("Px"), py::arg("Py"), py::arg("Ax"), py::arg("Ay"), py::arg("Bx"), py::arg("By"),
                  py::arg("Cx"), py::arg("Cy"))

      .def_static("PointInTriangle",
                  py::overload_cast<G4TwoVector const &, G4TwoVector const &, G4TwoVector const &, G4TwoVector const &>(
                     &G4GeomTools::PointInTriangle),
                  py::arg("P"), py::arg("A"), py::arg("B"), py::arg("C"))

      .def_static("PointInPolygon", &G4GeomTools::PointInPolygon, py::arg("P"), py::arg("Polygon"))
      .def_static("IsConvex", &G4GeomTools::IsConvex, py::arg("polygon"))
      .def_static("TriangulatePolygon",
                  py::overload_cast<G4TwoVectorList const &, G4TwoVectorList &>(&G4GeomTools::TriangulatePolygon),
                  py::arg("polygon"), py::arg("result"))

      .def_static("TriangulatePolygon",
                  py::overload_cast<G4TwoVectorList const &, std::vector<int, std::allocator<int>> &>(
                     &G4GeomTools::TriangulatePolygon),
                  py::arg("polygon"), py::arg("result"))

      .def_static("RemoveRedundantVertices", &G4GeomTools::RemoveRedundantVertices, py::arg("polygon"), py::arg("iout"),
                  py::arg("tolerance") = 0.)

      .def_static("DiskExtent",
                  py::overload_cast<G4double, G4double, G4double, G4double, G4TwoVector &, G4TwoVector &>(
                     &G4GeomTools::DiskExtent),
                  py::arg("rmin"), py::arg("rmax"), py::arg("startPhi"), py::arg("delPhi"), py::arg("pmin"),
                  py::arg("pmax"))

      .def_static(
         "DiskExtent",
         py::overload_cast<G4double, G4double, G4double, G4double, G4double, G4double, G4TwoVector &, G4TwoVector &>(
            &G4GeomTools::DiskExtent),
         py::arg("rmin"), py::arg("rmax"), py::arg("sinPhiStart"), py::arg("cosPhiStart"), py::arg("sinPhiEnd"),
         py::arg("cosPhiEnd"), py::arg("pmin"), py::arg("pmax"))

      .def_static("EllipsePerimeter", &G4GeomTools::EllipsePerimeter, py::arg("a"), py::arg("b"))
      .def_static("EllipticConeLateralArea", &G4GeomTools::EllipticConeLateralArea, py::arg("a"), py::arg("b"),
                  py::arg("h"))

      .def_static("TriangleAreaNormal", &G4GeomTools::TriangleAreaNormal, py::arg("A"), py::arg("B"), py::arg("C"))
      .def_static("QuadAreaNormal", &G4GeomTools::QuadAreaNormal, py::arg("A"), py::arg("B"), py::arg("C"),
                  py::arg("D"))

      .def_static("PolygonAreaNormal", &G4GeomTools::PolygonAreaNormal, py::arg("polygon"))
      .def_static("DistancePointSegment", &G4GeomTools::DistancePointSegment, py::arg("P"), py::arg("A"), py::arg("B"))
      .def_static("ClosestPointOnSegment", &G4GeomTools::ClosestPointOnSegment, py::arg("P"), py::arg("A"),
                  py::arg("B"))

      .def_static("ClosestPointOnTriangle", &G4GeomTools::ClosestPointOnTriangle, py::arg("P"), py::arg("A"),
                  py::arg("B"), py::arg("C"))

      .def_static("SphereExtent", &G4GeomTools::SphereExtent, py::arg("rmin"), py::arg("rmax"), py::arg("startTheta"),
                  py::arg("delTheta"), py::arg("startPhi"), py::arg("delPhi"), py::arg("pmin"), py::arg("pmax"));
}
