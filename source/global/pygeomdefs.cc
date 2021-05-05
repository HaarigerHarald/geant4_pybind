#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <geomdefs.hh>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_geomdefs(py::module &m)
{
   py::enum_<EAxis>(m, "EAxis")
      .value("kXAxis", kXAxis)
      .value("kYAxis", kYAxis)
      .value("kZAxis", kZAxis)
      .value("kRho", kRho)
      .value("kRadial3D", kRadial3D)
      .value("kPhi", kPhi)
      .value("kUndefined", kUndefined)
      .export_values();

   py::enum_<EInside>(m, "EInside")
      .value("kOutside", kOutside)
      .value("kSurface", kSurface)
      .value("kInside", kInside)
      .export_values();

   py::enum_<EVolume>(m, "EVolume")
      .value("kNormal", kNormal)
      .value("kReplica", kReplica)
      .value("kParameterised", kParameterised)
      .export_values();
}
