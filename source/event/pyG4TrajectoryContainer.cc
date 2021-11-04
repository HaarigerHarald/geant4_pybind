#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>
#include <pybind11/stl_bind.h>

#include <G4TrajectoryContainer.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4TrajectoryContainer(py::module &m)
{
   py::bind_vector<TrajectoryVector>(m, "TrajectoryVector");

   py::class_<G4TrajectoryContainer>(m, "G4TrajectoryContainer")
      .def(py::init<>())

      .def(py::self == py::self)
      .def(py::self != py::self)

      .def("size", &G4TrajectoryContainer::size)
      .def(
         "push_back", [](G4TrajectoryContainer &self, py::disown_ptr<G4VTrajectory> p) { self.push_back(p); },
         py::keep_alive<1, 2>())

      .def("entries", &G4TrajectoryContainer::entries)
      .def(
         "insert", [](G4TrajectoryContainer &self, py::disown_ptr<G4VTrajectory> p) { return self.insert(p); },
         py::keep_alive<1, 2>())

      .def("clearAndDestroy", &G4TrajectoryContainer::clearAndDestroy)
      .def("__getitem__", &G4TrajectoryContainer::operator[], py::is_operator(),
           py::return_value_policy::reference_internal)

      .def(
         "GetVector", [](const G4TrajectoryContainer &self) { return self.GetVector(); },
         py::return_value_policy::reference_internal);
}
