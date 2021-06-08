#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <Randomize.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

using namespace CLHEP;

void export_Randomize(py::module &m)
{
   static long *seedArray = nullptr;

   py::class_<HepRandom>(m, "HepRandom", "generate random number")

      .def(py::init<>())
      .def(py::init<long>())
      .def(py::init<HepRandomEngine &>())
      .def(py::init<HepRandomEngine *>())

      .def_static("setTheSeed", &HepRandom::setTheSeed, py::arg("seed"), py::arg("lux") = 3)
      .def_static("getTheSeed", &HepRandom::getTheSeed)
      .def_static("setTheSeeds",
                  [](const py::list &seedList) {
                     // check size...
                     int idx = 0;
                     while (1) {
                        long val = seedList[idx].cast<long>();
                        if (val == 0) break;
                        idx++;
                     }
                     int nsize = idx + 1;

                     delete[] seedArray;
                     seedArray = new long[nsize];

                     for (int i = 0; i < nsize; i++) {
                        seedArray[i] = seedList[i].cast<long>();
                     }

                     HepRandom::setTheSeeds(seedArray);
                  })

      .def_static("setTheSeeds",
                  [](const py::list &seedList, int aux) {
                     // check size...
                     int idx = 0;
                     while (1) {
                        long val = seedList[idx].cast<long>();
                        if (val == 0) break;
                        idx++;
                     }
                     int nsize = idx + 1;

                     delete[] seedArray;
                     seedArray = new long[nsize];
                     for (int i = 0; i < nsize; i++) {
                        seedArray[i] = seedList[i].cast<long>();
                     }

                     HepRandom::setTheSeeds(seedArray, aux);
                  })

      .def_static("getTheSeeds",
                  []() {
                     py::list    seedList;
                     const long *seeds = HepRandom::getTheSeeds();
                     int         idx   = 0;
                     while (1) {
                        if (seeds[idx] == 0) break;
                        seedList.append(seeds[idx]);
                        idx++;
                     }
                     return seedList;
                  })

      .def_static("getTheTableSeeds",
                  [](int index) {
                     long seedPair[2];
                     HepRandom::getTheTableSeeds(seedPair, index);

                     py::list seedList;
                     seedList.append(seedPair[0]);
                     seedList.append(seedPair[1]);

                     return seedList;
                  })

      .def_static("getTheGenerator", &HepRandom::getTheGenerator, py::return_value_policy::reference)
      .def_static("setTheEngine", [](py::disown_ptr<HepRandomEngine> engine) { HepRandom::setTheEngine(engine); })

      .def_static("getTheEngine", &HepRandom::getTheEngine, py::return_value_policy::reference)
      .def_static("saveEngineStatus", &HepRandom::saveEngineStatus, py::arg("filename") = "Config.conf")
      .def_static("restoreEngineStatus", &HepRandom::restoreEngineStatus, py::arg("filename") = "Config.conf")
      .def_static("showEngineStatus", &HepRandom::showEngineStatus)
      .def_static("createInstance", &HepRandom::createInstance);

   m.attr("G4Random") = m.attr("HepRandom");

   py::class_<RandBit>(m, "RandBit", "generate bit random number")
      .def_static("shootBit", py::overload_cast<>(&RandBit::shootBit));

   py::class_<G4RandGauss>(m, "G4RandGauss", "generate gaussian random number")
      .def_static("shoot", py::overload_cast<>(&RandGaussQ::shoot))
      .def_static("shoot", py::overload_cast<double, double>(&RandGaussQ::shoot));

   m.def("G4UniformRand", [] { return G4UniformRand(); });
}
