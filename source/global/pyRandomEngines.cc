#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/operators.h>

#include <CLHEP/Random/JamesRandom.h>
#include <CLHEP/Random/RandomEngine.h>
#include <CLHEP/Random/RanecuEngine.h>
#include <CLHEP/Random/Ranlux64Engine.h>
#include <CLHEP/Random/RanluxEngine.h>
#include <CLHEP/Random/RanshiEngine.h>
#include <CLHEP/Random/MTwistEngine.h>
#include <CLHEP/Random/NonRandomEngine.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

using namespace CLHEP;

void export_RandomEngines(py::module &m)
{
   py::class_<HepRandomEngine>(m, "HepRandomEngine", "base class of random engine")

      .def("flat", &HepRandomEngine::flat)
      .def("flatArray",
           [](HepRandomEngine &self, py::list &vect) {
              for (size_t i = 0; i < vect.size(); i++) {
                 vect[i] = self.flat();
              }
           })

      .def("setSeed", &HepRandomEngine::setSeed, py::arg("seed"), py::arg("aux"))
      .def("setSeeds",
           [](HepRandomEngine &self, const std::vector<long> &seeds, int x) { self.setSeeds(seeds.data(), x); })

      .def("saveStatus", &HepRandomEngine::saveStatus, py::arg("filename") = "Config.conf")
      .def("restoreStatus", &HepRandomEngine::restoreStatus, py::arg("filename") = "Config.conf")
      .def("showStatus", &HepRandomEngine::showStatus)
      .def("name", &HepRandomEngine::name)
      .def("put", py::overload_cast<>(&HepRandomEngine::put, py::const_))
      .def("get", py::overload_cast<const std::vector<unsigned long> &>(&HepRandomEngine::get))
      .def("getState", py::overload_cast<const std::vector<unsigned long> &>(&HepRandomEngine::getState))
      .def("newEngine", py::overload_cast<const std::vector<unsigned long> &>(&HepRandomEngine::newEngine));

   py::class_<HepJamesRandom, HepRandomEngine>(m, "HepJamesRandom", "HepJames random engine")
      .def(py::init<>())
      .def(py::init<long>())
      .def(py::init<int, int>());

   py::class_<RanecuEngine, HepRandomEngine>(m, "RanecuEngine", "Ranecu random engine")
      .def(py::init<>())
      .def(py::init<int>());

   py::class_<RanluxEngine, HepRandomEngine>(m, "RanluxEngine", "Ranlux random engine")
      .def(py::init<>())
      .def(py::init<long>())
      .def(py::init<long, int>())
      .def(py::init<int, int, int>());

   py::class_<Ranlux64Engine, HepRandomEngine>(m, "Ranlux64Engine", "Ranlux64 random engine")
      .def(py::init<>())
      .def(py::init<long>())
      .def(py::init<long, int>())
      .def(py::init<int, int, int>());

   py::class_<MTwistEngine, HepRandomEngine>(m, "MTwistEngine", "MTwistEngine random engine")
      .def(py::init<>())
      .def(py::init<long>())
      .def(py::init<int, int>());

   py::class_<NonRandomEngine, HepRandomEngine>(m, "NonRandomEngine", "NonRandomEngine random engine")
      .def(py::init<>());

   py::class_<RanshiEngine, HepRandomEngine>(m, "RanshiEngine", "RanshiEngine random engine")
      .def(py::init<>())
      .def(py::init<long>())
      .def(py::init<int, int>());
}
