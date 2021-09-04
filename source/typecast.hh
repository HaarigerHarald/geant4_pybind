#ifndef TYPE_CAST_HH
#define TYPE_CAST_HH

#include <pybind11/pybind11.h>
#include <pybind11/cast.h>

#include <G4String.hh>

namespace pybind11 {

template <typename T>
struct disown_ptr {
   disown_ptr(T *ptr) : ptr(ptr) {}
   operator T *() const { return ptr; }

private:
   T *ptr;
};

namespace detail {

/** The disown type casters to cast from smart_holder -> to a disowned
 *  pointer encapsulated in a disown_ptr<T>. It is mostly based on pybind11's
 *  std::unique_ptr type caster with the notable difference that the python
 *  object remains accessible after disowning. **/

template <typename T>
struct smart_holder_type_caster_disown_load {
   using holder_type = pybindit::memory::smart_holder;

   bool load(handle src, bool convert)
   {
      static_assert(type_uses_smart_holder_type_caster<T>::value, "Internal consistency error.");
      load_impl = modified_type_caster_generic_load_impl(typeid(T));
      if (!load_impl.load(src, convert)) return false;
      return true;
   }

   disown_ptr<T> loaded_as_disown_ptr()
   {
      if (!have_holder()) {
         return nullptr;
      }

      if (!holder().is_populated) {
         pybind11_fail("Missing value for wrapped C++ type:"
                       " Python instance is uninitialized.");
      }
      if (!holder().has_pointee()) {
         throw value_error("Missing value for wrapped C++ type:"
                           " Python instance was disowned.");
      }

      auto raw_void_ptr = holder().template as_raw_ptr_unowned<void>();

      void *value_void_ptr = load_impl.loaded_v_h.value_ptr();
      if (value_void_ptr != raw_void_ptr) {
         pybind11_fail("smart_holder_type_casters: loaded_as_disown_ptr failure:"
                       " value_void_ptr != raw_void_ptr");
      }

      T *raw_type_ptr = convert_type(raw_void_ptr);

      auto *self_life_support = dynamic_raw_ptr_cast_if_possible<trampoline_self_life_support>(raw_type_ptr);
      if (self_life_support == nullptr && holder().pointee_depends_on_holder_owner) {
         throw value_error("Alias class (also known as trampoline) does not inherit from "
                           "py::trampoline_self_life_support, therefore the ownership of this "
                           "instance cannot safely be transferred to C++.");
      }

      holder().disown();

      if (self_life_support != nullptr) {
         self_life_support->activate_life_support(load_impl.loaded_v_h);
      }

      return raw_type_ptr;
   }

private:
   modified_type_caster_generic_load_impl load_impl;

   bool have_holder() const { return load_impl.loaded_v_h.vh != nullptr && load_impl.loaded_v_h.holder_constructed(); }

   holder_type &holder() const { return load_impl.loaded_v_h.holder<holder_type>(); }

   T *convert_type(void *void_ptr) const
   {
      if (void_ptr != nullptr && load_impl.loaded_v_h_cpptype != nullptr && !load_impl.reinterpret_cast_deemed_ok &&
          load_impl.implicit_cast != nullptr) {
         void_ptr = load_impl.implicit_cast(void_ptr);
      }
      return static_cast<T *>(void_ptr);
   }
};

template <typename T>
struct smart_holder_type_caster<disown_ptr<T>> : smart_holder_type_caster_disown_load<T>,
                                                 smart_holder_type_caster_class_hooks {

   static constexpr auto name = _<T>();

   static handle cast(disown_ptr<T> &&, return_value_policy, handle)
   {
      throw cast_error("Cast from disown_ptr is not allowed.");
   }

   static handle cast(disown_ptr<T> &, return_value_policy, handle)
   {
      throw cast_error("Cast from disown_ptr is not allowed.");
   }

   operator disown_ptr<T>() { return this->loaded_as_disown_ptr(); }

   template <typename>
   using cast_op_type = disown_ptr<T>;
};

template <typename T>
struct smart_holder_type_caster<disown_ptr<T const>> : smart_holder_type_caster_class_hooks {

   static constexpr auto name = _<T>();

   static handle cast(disown_ptr<T const> &&, return_value_policy, handle)
   {
      throw cast_error("Cast from disown_ptr is not allowed.");
   }

   static handle cast(disown_ptr<T const> &, return_value_policy, handle)
   {
      throw cast_error("Cast from disown_ptr is not allowed.");
   }

   operator disown_ptr<T const>() { return this->loaded_as_disown_ptr(); }

   template <typename>
   using cast_op_type = disown_ptr<T const>;
};

#ifdef PYBIND11_USE_SMART_HOLDER_AS_DEFAULT
template <typename T>
class type_caster_for_class_<disown_ptr<T>> : public smart_holder_type_caster<disown_ptr<T>> {
};

template <typename T>
class type_caster_for_class_<disown_ptr<T const>> : public smart_holder_type_caster<disown_ptr<T const>> {
};
#endif

// Typecaster: G4String <-> python string
template <>
struct type_caster<G4String> {
public:
   PYBIND11_TYPE_CASTER(G4String, _(PYBIND11_STRING_NAME));

   bool load(handle src, bool)
   {
      handle load_src = src;
      if (!src) {
         return false;
      } else if (!PyUnicode_Check(load_src.ptr())) {
         if (PYBIND11_BYTES_CHECK(src.ptr())) {

            const char *bytes = PYBIND11_BYTES_AS_STRING(src.ptr());
            if (bytes) {
               value = G4String(bytes, (size_t)PYBIND11_BYTES_SIZE(src.ptr()));
               return true;
            }
         }
         return false;
      }

      auto utfNbytes = reinterpret_steal<object>(PyUnicode_AsEncodedString(load_src.ptr(), "utf-8", nullptr));
      if (!utfNbytes) {
         PyErr_Clear();
         return false;
      }

      const auto *buffer = reinterpret_cast<const char *>(PYBIND11_BYTES_AS_STRING(utfNbytes.ptr()));
      size_t      length = (size_t)PYBIND11_BYTES_SIZE(utfNbytes.ptr()) / sizeof(char);
      value              = G4String(buffer, length);

      return true;
   }

   static handle cast(G4String src, return_value_policy /* policy */, handle /* parent */)
   {
      return PyUnicode_DecodeUTF8(src.c_str(), src.size(), nullptr);
   }
};
} // namespace detail
} // namespace pybind11

#endif // TYPE_CAST_HH
