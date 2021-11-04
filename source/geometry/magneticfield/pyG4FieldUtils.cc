#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <G4FieldUtils.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_G4FieldUtils(py::module &m)
{
   class Scopedfield_utils {
   };

   py::class_<Scopedfield_utils>(m, "field_utils")
      .def_static(
         "absoluteError",
         [](py::list pyY, py::list pyYerr, G4double hstep) {
            G4double *y    = new G4double[pyY.size()];
            G4double *yerr = new G4double[pyYerr.size()];

            for (size_t i = 0; i < pyY.size(); i++) {
               y[i] = pyY[i].cast<G4double>();
            }

            for (size_t i = 0; i < pyYerr.size(); i++) {
               yerr[i] = pyYerr[i].cast<G4double>();
            }

            G4double value = field_utils::absoluteError(y, yerr, hstep);

            delete[] y;
            delete[] yerr;

            return value;
         },
         py::arg("y"), py::arg("yerr"), py::arg("hstep"))

      .def_static(
         "relativeError2",
         [](py::list pyY, py::list pyYerr, G4double hstep, G4double errorTolerance) {
            G4double *y    = new G4double[pyY.size()];
            G4double *yerr = new G4double[pyYerr.size()];

            for (size_t i = 0; i < pyY.size(); i++) {
               y[i] = pyY[i].cast<G4double>();
            }

            for (size_t i = 0; i < pyYerr.size(); i++) {
               yerr[i] = pyYerr[i].cast<G4double>();
            }

            G4double value = field_utils::relativeError2(y, yerr, hstep, errorTolerance);

            delete[] y;
            delete[] yerr;

            return value;
         },
         py::arg("y"), py::arg("yerr"), py::arg("hstep"), py::arg("errorTolerance"))

      .def_static(
         "relativeError",
         [](py::list pyY, py::list pyYerr, G4double hstep, G4double errorTolerance) {
            G4double *y    = new G4double[pyY.size()];
            G4double *yerr = new G4double[pyYerr.size()];

            for (size_t i = 0; i < pyY.size(); i++) {
               y[i] = pyY[i].cast<G4double>();
            }

            for (size_t i = 0; i < pyYerr.size(); i++) {
               yerr[i] = pyYerr[i].cast<G4double>();
            }

            G4double value = field_utils::relativeError(y, yerr, hstep, errorTolerance);

            delete[] y;
            delete[] yerr;

            return value;
         },
         py::arg("y"), py::arg("yerr"), py::arg("hstep"), py::arg("errorTolerance"))

      .def_static("inverseCurvatureRadius", &field_utils::inverseCurvatureRadius, py::arg("particleCharge"),
                  py::arg("momentum"), py::arg("BField"));
}
