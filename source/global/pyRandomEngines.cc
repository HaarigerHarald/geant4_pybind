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
#include <CLHEP/Random/MixMaxRng.h>
#include <CLHEP/Random/DualRand.h>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

using namespace CLHEP;

class PyHepRandomEngine : public HepRandomEngine, public py::trampoline_self_life_support {
public:
   using HepRandomEngine::HepRandomEngine;

   double flat() override { PYBIND11_OVERRIDE_PURE(double, HepRandomEngine, flat); }

   void flatArray(const int size, double *vect) override
   {
      pybind11::gil_scoped_acquire gil;
      py::function flatArray = py::get_override(static_cast<const HepRandomEngine *>(this), "flatArray");

      if (flatArray) {
         py::list pVect(size);
         flatArray(pVect);

         for (size_t i = 0; i < pVect.size(); i++) {
            vect[i] = pVect[i].cast<double>();
         }
      } else {
         py::pybind11_fail("Tried to call pure virtual function \"HepRandomEngine::flatArray\"");
      }
   }

   void setSeed(long seed, int aux) override { PYBIND11_OVERRIDE_PURE(void, HepRandomEngine, setSeed, seed, aux); }

   void setSeeds(const long *seeds, int length) override
   {
      PYBIND11_OVERRIDE_PURE(void, HepRandomEngine, setSeeds, std::vector<long>(seeds, seeds + length));
   }

   void saveStatus(const char filename[] = "Config.conf") const override
   {
      PYBIND11_OVERRIDE_PURE(void, HepRandomEngine, saveStatus, filename);
   };

   void restoreStatus(const char filename[] = "Config.conf") override
   {
      PYBIND11_OVERRIDE_PURE(void, HepRandomEngine, restoreStatus, filename);
   }

   void showStatus() const override { PYBIND11_OVERRIDE_PURE(void, HepRandomEngine, showStatus); };

   std::string name() const override { PYBIND11_OVERRIDE_PURE(std::string, HepRandomEngine, name); }

   // virtual std::ostream &put(std::ostream &os) const;
   // virtual std::istream &get(std::istream &is);

   // virtual std::istream &getState(std::istream &is);

   std::vector<unsigned long> put() const override
   {
      PYBIND11_OVERRIDE(std::vector<unsigned long>, HepRandomEngine, put);
   }

   bool get(const std::vector<unsigned long> &v) override { PYBIND11_OVERRIDE(bool, HepRandomEngine, get, v); }

   bool getState(const std::vector<unsigned long> &v) override
   {
      PYBIND11_OVERRIDE(bool, HepRandomEngine, getState, v);
   }
};

void export_RandomEngines(py::module &m)
{
   py::class_<HepRandomEngine, PyHepRandomEngine>(m, "HepRandomEngine", "base class of random engine")

      .def("flat", &HepRandomEngine::flat)
      .def("flatArray",
           [](HepRandomEngine &self, py::list &vect) {
              std::vector<double> dVect(vect.size());
              self.flatArray(vect.size(), dVect.data());

              for (size_t i = 0; i < vect.size(); i++) {
                 vect[i] = dVect[i];
              }
           })

      .def("setSeed", &HepRandomEngine::setSeed, py::arg("seed"), py::arg("aux"))
      .def("setSeeds",
           [](HepRandomEngine &self, const std::vector<long> &seeds) { self.setSeeds(seeds.data(), seeds.size()); })

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

   py::class_<MixMaxRng, HepRandomEngine>(m, "MixMaxRng").def(py::init<>()).def(py::init<long>());

   py::class_<DualRand, HepRandomEngine>(m, "DualRand")
      .def(py::init<>())
      .def(py::init<long>())
      .def(py::init<int, int>());
}
