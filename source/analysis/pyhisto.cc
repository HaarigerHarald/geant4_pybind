#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

#include <tools/histo/h1d>
#include <tools/histo/h2d>
#include <tools/histo/h3d>
#include <tools/histo/p1d>
#include <tools/histo/p2d>

#include "typecast.hh"
#include "opaques.hh"

namespace py = pybind11;

void export_histo(py::module &m)
{
   py::class_<tools::histo::h1d>(m, "h1d")
      .def(py::init<>())
      .def(py::init<const std::string &, const std::vector<double> &>(), py::arg("title"), py::arg("edges"))
      .def(py::init<const std::string &, unsigned int, double, double>(), py::arg("title"), py::arg("xnumber"),
           py::arg("xmin"), py::arg("xmax"))

      .def("add", &tools::histo::h1d::add)
      .def("add_annotation", &tools::histo::h1d::add_annotation)
      .def("all_entries", &tools::histo::h1d::all_entries)

      .def("annotation", &tools::histo::h1d::annotation)
      .def("annotations", py::overload_cast<>(&tools::histo::h1d::annotations, py::const_))
      .def("axis", py::overload_cast<>(&tools::histo::h1d::axis, py::const_))

      .def("bin_center", &tools::histo::h1d::bin_center)
      .def("bin_entries", &tools::histo::h1d::bin_entries)
      .def("bin_error", &tools::histo::h1d::bin_error)
      .def("bin_height", &tools::histo::h1d::bin_height)
      .def("bin_mean", &tools::histo::h1d::bin_mean)
      .def("bin_rms", &tools::histo::h1d::bin_rms)
      .def("bin_Sw2", &tools::histo::h1d::bin_Sw2)
      .def("bin_Sw", &tools::histo::h1d::bin_Sw)
      .def("bin_Sx2w", &tools::histo::h1d::bin_Sx2w)
      .def("bin_Sxw", &tools::histo::h1d::bin_Sxw)
      .def("bins_entries", &tools::histo::h1d::bins_entries)
      .def("bins_sum_w2", &tools::histo::h1d::bins_sum_w2)
      .def("bins_sum_w", &tools::histo::h1d::bins_sum_w)
      .def("bins_sum_x2w", &tools::histo::h1d::bins_sum_x2w)
      .def("bins_sum_xw", &tools::histo::h1d::bins_sum_xw)
      .def("configure", py::overload_cast<unsigned int, double, double>(&tools::histo::h1d::configure))
      .def("configure", py::overload_cast<const std::vector<double> &>(&tools::histo::h1d::configure))
      .def("coord_to_index", &tools::histo::h1d::coord_to_index)
      .def("copy_from_data", &tools::histo::h1d::copy_from_data)
      .def("dac", &tools::histo::h1d::dac)
      .def("dimension", &tools::histo::h1d::dimension)
      .def("divide", &tools::histo::h1d::divide)
      .def("entries", &tools::histo::h1d::entries)
      //.def("equals", &tools::histo::h1d::equals)
      //.def("equals_TH", &tools::histo::h1d::equals_TH)
      .def("equivalent_bin_entries", &tools::histo::h1d::equivalent_bin_entries)
      .def("extra_entries", &tools::histo::h1d::extra_entries)
      .def("Fill", &tools::histo::h1d::Fill)
      .def("fill", &tools::histo::h1d::fill)
      .def("gather_bins", &tools::histo::h1d::gather_bins)
      .def("get_all_Sw_Sw2", &tools::histo::h1d::get_all_Sw_Sw2)
      .def("get_axis", &tools::histo::h1d::get_axis)
      .def("get_bin_content", &tools::histo::h1d::get_bin_content)
      .def("get_bins", &tools::histo::h1d::get_bins)
      .def("get_dimension", &tools::histo::h1d::get_dimension)
      .def("get_histo_data", &tools::histo::h1d::get_histo_data)
      .def("get_in_range_Sw2", &tools::histo::h1d::get_in_range_Sw2)
      .def("get_in_range_Sw", &tools::histo::h1d::get_in_range_Sw)
      .def("get_ith_axis_Sx2w", &tools::histo::h1d::get_ith_axis_Sx2w)
      .def("get_ith_axis_Sxw", &tools::histo::h1d::get_ith_axis_Sxw)
      .def("get_Sw_Sw2", &tools::histo::h1d::get_Sw_Sw2)
      .def("get_title", &tools::histo::h1d::get_title)
      .def("has_entries_per_bin", &tools::histo::h1d::has_entries_per_bin)
      .def("hprint", &tools::histo::h1d::hprint)
      .def("hprint_annotations", &tools::histo::h1d::hprint_annotations)
      .def("in_range_planes_xyw", &tools::histo::h1d::in_range_planes_xyw)
      .def("is_valid", &tools::histo::h1d::is_valid)
      .def("max_bin_height", &tools::histo::h1d::max_bin_height)
      .def("max_bin_height_with_entries", &tools::histo::h1d::max_bin_height_with_entries)
      .def("mean", &tools::histo::h1d::mean)
      .def("min_bin_height", &tools::histo::h1d::min_bin_height)
      .def("min_bin_height_with_entries", &tools::histo::h1d::min_bin_height_with_entries)
      .def("multiply", py::overload_cast<double>(&tools::histo::h1d::multiply))
      //.def("multiply", py::overload_cast<const tools::histo::h1d&>(&tools::histo::h1d::multiply))
      .def("not_a_profile", &tools::histo::h1d::not_a_profile)
      .def("number_of_planes", &tools::histo::h1d::number_of_planes)
      .def("reset", &tools::histo::h1d::reset)
      .def("rms", &tools::histo::h1d::rms)
      .def("scale", &tools::histo::h1d::scale)
      .def("set_annotations", &tools::histo::h1d::set_annotations)
      .def("set_bin_content", &tools::histo::h1d::set_bin_content)
      .def("set_title", &tools::histo::h1d::set_title)
      .def("subtract", &tools::histo::h1d::subtract)
      .def("sum_all_bin_heights", &tools::histo::h1d::sum_all_bin_heights)
      .def("sum_bin_heights", &tools::histo::h1d::sum_bin_heights)
      .def("title", &tools::histo::h1d::title);

   // TODO h2d, h3d, p1d, p2d
}
