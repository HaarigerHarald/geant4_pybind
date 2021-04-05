#include <pybind11/pybind11.h>

#include "CLHEP/Random/JamesRandom.h"
#include "CLHEP/Random/RandomEngine.h"
#include "CLHEP/Random/RanecuEngine.h"
#include "CLHEP/Random/Ranlux64Engine.h"
#include "CLHEP/Random/RanluxEngine.h"

#include "typecast.hh"

namespace py = pybind11;

using namespace CLHEP;

void export_RandomEngines(py::module &m)
{
   py::class_<HepRandomEngine, std::unique_ptr<HepRandomEngine>>(m, "HepRandomEngine", "base class of random engine");

   py::class_<HepJamesRandom, HepRandomEngine, std::unique_ptr<HepJamesRandom>>(m, "HepJamesRandom",
                                                                                "HepJames random engine")
      .def(py::init<>())
      .def(py::init<long>())
      .def(py::init<int, int>());

   py::class_<RanecuEngine, HepRandomEngine, std::unique_ptr<RanecuEngine>>(m, "RanecuEngine", "Ranecu random engine")
      .def(py::init<>())
      .def(py::init<int>());

   py::class_<RanluxEngine, HepRandomEngine, std::unique_ptr<RanluxEngine>>(m, "RanluxEngine", "Ranlux random engine")
      .def(py::init<>())
      .def(py::init<long>())
      .def(py::init<long, int>())
      .def(py::init<int, int, int>());

   py::class_<Ranlux64Engine, HepRandomEngine, std::unique_ptr<Ranlux64Engine>>(m, "Ranlux64Engine",
                                                                                "Ranlux64 random engine")
      .def(py::init<>())
      .def(py::init<long>())
      .def(py::init<long, int>())
      .def(py::init<int, int, int>());
}
