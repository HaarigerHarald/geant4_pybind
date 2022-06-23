#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4PhysicsVector.hh>

#include <limits>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

class PyG4PhysicsVector : public G4PhysicsVector, public py::trampoline_self_life_support {
public:
   using G4PhysicsVector::G4PhysicsVector;

   void Initialise() override { PYBIND11_OVERRIDE(void, G4PhysicsVector, Initialise, ); }
};

void export_G4PhysicsVector(py::module &m)
{
   py::class_<G4PhysicsVector, PyG4PhysicsVector>(m, "G4PhysicsVector")

      .def(py::init<G4bool>(), py::arg("spline") = false)
      .def("__copy__", [](const PyG4PhysicsVector &self) { return new PyG4PhysicsVector(self); })
      .def("__deepcopy__", [](const PyG4PhysicsVector &self, py::dict) { return new PyG4PhysicsVector(self); })
      .def("__copy__", [](const G4PhysicsVector &self) { return new G4PhysicsVector(self); })
      .def("__deepcopy__", [](const G4PhysicsVector &self, py::dict) { return new G4PhysicsVector(self); })
      .def("ComputeLogVectorBin", &G4PhysicsVector::ComputeLogVectorBin, py::arg("logenergy"))
      .def("DumpValues", &G4PhysicsVector::DumpValues, py::arg("unitE") = 1., py::arg("unitV") = 1.)
      .def("Energy", &G4PhysicsVector::Energy, py::arg("index"))
      //.def("FillSecondDerivatives", &G4PhysicsVector::FillSecondDerivatives, py::arg("arg0") = Base, py::arg("dir1") =
      //0., py::arg("dir2") = 0.)

      .def("FindBin", &G4PhysicsVector::FindBin, py::arg("energy"), py::arg("idx"))
      .def("FindLinearEnergy", &G4PhysicsVector::FindLinearEnergy, py::arg("rand"))
      .def("GetEnergy", &G4PhysicsVector::GetEnergy, py::arg("value"))
      .def("GetLowEdgeEnergy", &G4PhysicsVector::GetLowEdgeEnergy, py::arg("index"))
      .def("GetMaxEnergy", &G4PhysicsVector::GetMaxEnergy)
      .def("GetMaxValue", &G4PhysicsVector::GetMaxValue)
      .def("GetMinEnergy", &G4PhysicsVector::GetMinEnergy)
      .def("GetMinValue", &G4PhysicsVector::GetMinValue)
      .def("GetSpline", &G4PhysicsVector::GetSpline)
      .def("GetType", &G4PhysicsVector::GetType)
      .def(
         "GetValue",
         [](const G4PhysicsVector &self, const G4double energy, G4bool &isOutRange) {
            return std::make_tuple(self.GetValue(energy, isOutRange), isOutRange);
         },
         py::arg("energy"), py::arg("isOutRange"))

      .def("GetVectorLength", &G4PhysicsVector::GetVectorLength)
      .def("LogVectorValue", &G4PhysicsVector::LogVectorValue, py::arg("energy"), py::arg("theLogEnergy"))
      .def("PutValue", &G4PhysicsVector::PutValue, py::arg("index"), py::arg("value"))
      .def("Retrieve", &G4PhysicsVector::Retrieve, py::arg("fIn"), py::arg("ascii") = false)
      .def("ScaleVector", &G4PhysicsVector::ScaleVector, py::arg("factorE"), py::arg("factorV"))
      .def("SetVerboseLevel", &G4PhysicsVector::SetVerboseLevel, py::arg("value"))
      .def("Store", &G4PhysicsVector::Store, py::arg("fOut"), py::arg("ascii") = false)
      .def(
         "Value",
         [](const G4PhysicsVector &self, const G4double energy, size_t &lastidx) {
            return std::make_tuple(self.Value(energy, lastidx), lastidx);
         },
         py::arg("energy"), py::arg("lastidx"))

      .def("Value", py::overload_cast<const G4double>(&G4PhysicsVector::Value, py::const_), py::arg("energy"))
      .def("__call__", &G4PhysicsVector::operator(), py::arg("index"), py::is_operator())
      .def("__getitem__", &G4PhysicsVector::operator[], py::is_operator())
      .def(
         "__str__",
         [](const G4PhysicsVector &self) {
            std::stringstream ss;
            ss << std::setprecision(std::numeric_limits<G4double>::digits10 + 1) << self;
            return ss.str();
         },
         py::is_operator());
}
