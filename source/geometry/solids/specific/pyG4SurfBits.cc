#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4SurfBits.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4SurfBits(py::module &m)
{
   py::class_<G4SurfBits>(m, "G4SurfBits")

      .def(py::init<unsigned int>(), py::arg("nbits") = 0)
      .def("__copy__", [](const G4SurfBits &self) { return G4SurfBits(self); })
      .def("__deepcopy__", [](const G4SurfBits &self, py::dict) { return G4SurfBits(self); })
      .def("ResetAllBits", &G4SurfBits::ResetAllBits, py::arg("value") = false)
      .def("ResetBitNumber", &G4SurfBits::ResetBitNumber, py::arg("bitnumber"))
      .def("SetBitNumber", &G4SurfBits::SetBitNumber, py::arg("bitnumber"), py::arg("value") = true)
      .def("TestBitNumber", &G4SurfBits::TestBitNumber, py::arg("bitnumber"))
      .def("__getitem__", &G4SurfBits::operator[], py::is_operator())
      .def("set", py::overload_cast<unsigned int, const char *>(&G4SurfBits::set), py::arg("nbits"), py::arg("array"))
      .def("set", py::overload_cast<unsigned int, const G4int *>(&G4SurfBits::set), py::arg("nbits"), py::arg("array"))
      .def("Get", py::overload_cast<char *>(&G4SurfBits::Get, py::const_), py::arg("array"))
      .def("Get", py::overload_cast<G4int *>(&G4SurfBits::Get, py::const_), py::arg("array"))
      .def("Clear", &G4SurfBits::Clear)
      .def("Compact", &G4SurfBits::Compact)
      .def("GetNbits", &G4SurfBits::GetNbits)
      .def("GetNbytes", &G4SurfBits::GetNbytes)
      .def("Print", &G4SurfBits::Print)
      .def("Output", &G4SurfBits::Output)
      .def_readwrite("fAllBits", &G4SurfBits::fAllBits);
}
