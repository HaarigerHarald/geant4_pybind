#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4BlockingList.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4BlockingList(py::module &m)
{
   py::class_<G4BlockingList>(m, "G4BlockingList")

      .def(py::init<G4int, G4int>(), py::arg("maxDefault") = kBlockingListMaxDefault,
           py::arg("stride") = kBlockingListStride)

      .def("__copy__", [](const G4BlockingList &self) { return G4BlockingList(self); })
      .def("__deepcopy__", [](const G4BlockingList &self, py::dict) { return G4BlockingList(self); })
      .def("Reset", &G4BlockingList::Reset)
      .def("FullyReset", &G4BlockingList::FullyReset)
      .def("Enlarge", &G4BlockingList::Enlarge, py::arg("nv"))
      .def("Length", &G4BlockingList::Length)
      .def("BlockVolume", &G4BlockingList::BlockVolume, py::arg("v"))
      .def("IsBlocked", &G4BlockingList::IsBlocked, py::arg("v"));
}
