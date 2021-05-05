#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4Polyhedra.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4Polyhedra(py::module &m)
{
   py::class_<G4Polyhedra, G4VSolid, std::unique_ptr<G4Polyhedra, py::nodelete>>(m, "G4Polyhedra",
                                                                                 "Polyhedra solid class")

      .def(py::init<>([](const G4String &name, G4double phiStart, G4double phiTotal, G4int numSide, G4int numZPlanes,
                         const py::list &zPlane, const py::list &rInner, const py::list &rOuter) {
         auto zlist  = std::make_unique<G4double[]>(numZPlanes);
         auto r0list = std::make_unique<G4double[]>(numZPlanes);
         auto r1list = std::make_unique<G4double[]>(numZPlanes);

         for (G4int i = 0; i < numZPlanes; i++) {
            zlist[i]  = zPlane[i].cast<G4double>();
            r0list[i] = rInner[i].cast<G4double>();
            r1list[i] = rOuter[i].cast<G4double>();
         }

         return new G4Polyhedra(name, phiStart, phiTotal, numSide, numZPlanes, zlist.get(), r0list.get(), r1list.get());
      }))

      .def(py::init<>([](const G4String &name, G4double phiStart, G4double phiTotal, G4int numSide, G4int numRZ,
                         const py::list &r, const py::list &z) {
         auto zlist = std::make_unique<G4double[]>(numRZ);
         auto rlist = std::make_unique<G4double[]>(numRZ);

         for (G4int i = 0; i < numRZ; i++) {
            zlist[i] = z[i].cast<G4double>();
            rlist[i] = r[i].cast<G4double>();
         }

         return new G4Polyhedra(name, phiStart, phiTotal, numSide, numRZ, rlist.get(), zlist.get());
      }))

      .def("GetStartPhi", &G4Polyhedra::GetStartPhi)
      .def("GetEndPhi", &G4Polyhedra::GetEndPhi)
      .def("GetNumSide", &G4Polyhedra::GetNumSide)
      .def("GetNumRZCorner", &G4Polyhedra::GetNumRZCorner)
      .def("IsOpen", &G4Polyhedra::IsOpen)
      .def("IsGeneric", &G4Polyhedra::IsGeneric)

      .def(
         "__str__",
         [](const G4Polyhedra &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
