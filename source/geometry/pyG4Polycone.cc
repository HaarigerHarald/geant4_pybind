#include <pybind11/pybind11.h>

#include <G4Polycone.hh>

#include <limits>

#include "typecast.hh"

namespace py = pybind11;

void export_G4Polycone(py::module &m)
{
   py::class_<G4Polycone, G4VSolid, std::unique_ptr<G4Polycone, py::nodelete>>(m, "G4Polycone", "Polycone solid class")

      .def(py::init<>([](const G4String &name, G4double phiStart, G4double phiTotal, G4int numZPlanes,
                         const py::list &zPlane, const py::list &rInner, const py::list &rOuter) {
         auto zlist  = std::make_unique<G4double[]>(numZPlanes);
         auto r0list = std::make_unique<G4double[]>(numZPlanes);
         auto r1list = std::make_unique<G4double[]>(numZPlanes);

         for (G4int i = 0; i < numZPlanes; i++) {
            zlist[i]  = zPlane[i].cast<G4double>();
            r0list[i] = rInner[i].cast<G4double>();
            r1list[i] = rOuter[i].cast<G4double>();
         }

         return new G4Polycone(name, phiStart, phiTotal, numZPlanes, zlist.get(), r0list.get(), r1list.get());
      }))

      .def(py::init<>([](const G4String &name, G4double phiStart, G4double phiTotal, G4int numRZ, const py::list &r,
                         const py::list &z) {
         auto zlist = std::make_unique<G4double[]>(numRZ);
         auto rlist = std::make_unique<G4double[]>(numRZ);

         for (G4int i = 0; i < numRZ; i++) {
            rlist[i] = r[i].cast<G4double>();
            zlist[i] = z[i].cast<G4double>();
         }

         return new G4Polycone(name, phiStart, phiTotal, numRZ, rlist.get(), zlist.get());
      }))

      .def("GetStartPhi", &G4Polycone::GetStartPhi)
      .def("GetEndPhi", &G4Polycone::GetEndPhi)
      .def("IsOpen", &G4Polycone::IsOpen)
      .def("GetNumRZCorner", &G4Polycone::GetNumRZCorner)

      .def(
         "__str__",
         [](const G4Polycone &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
