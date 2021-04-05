#ifndef HOLDER_HH
#define HOLDER_HH

#include <vector>
#include <mutex>
#include <iterator>

#include <pybind11/pybind11.h>

class HolderStore {

protected:
   static std::vector<void *> store;
   static size_t              maxId;
   static std::mutex          storeMutex;
   static void *              ptrToDelete;

public:
   static void *getPtrToDelete() { return ptrToDelete; };
};

// Smart pointer whose destructor can be runtime deactivated.
// Used to pass pointer ownership.
template <typename T>
class owntrans_ptr : public HolderStore {

private:
   T *    pointer;
   size_t id;

public:
   owntrans_ptr(T *pointer) : pointer(pointer)
   {
      std::lock_guard<std::mutex> lock(storeMutex);
      id = maxId++;
      store.push_back(this);
   }

   owntrans_ptr(const owntrans_ptr<T> &) = delete;

   owntrans_ptr<T> &operator=(const owntrans_ptr<T> &) = delete;

   owntrans_ptr(owntrans_ptr<T> &&other) : pointer(other.pointer) { other.pointer = nullptr; }

   static void remove(T *p)
   {
      std::lock_guard<std::mutex> lock(storeMutex);
      for (auto it = store.end(); it > store.begin(); --it) {
         if (static_cast<owntrans_ptr<T> *>(*(it - 1))->pointer == p) {
            store.erase(it - 1);
            break;
         }
      }
   }

   ~owntrans_ptr()
   {
      std::lock_guard<std::mutex> lock(storeMutex);
      for (auto it = store.begin(); it < store.end(); ++it) {
         if (*it == static_cast<void *>(this) && static_cast<owntrans_ptr<T> *>(*it)->id == this->id) {
            store.erase(it);
            ptrToDelete = pointer;
            delete pointer;
            ptrToDelete = nullptr;
            break;
         }
      }
   }

   T *get() const { return pointer; }
};

// Returns a trampoline class name that works with the reference keeping macros.
#define TRAMPOLINE_NAME(cname) Py##cname

// Checks whether the given pointer is of Trampoline type and increases the reference.
#define TRAMPOLINE_REF_INCREASE(cname, ptr)                                                         \
   bool isPy##cname(cname *);                                                                       \
   if (isPy##cname(ptr)) {                                                                          \
      pybind11::handle _handle =                                                                    \
         pybind11::cast(static_cast<const cname *>(ptr), pybind11::return_value_policy::reference); \
      if (_handle) _handle.inc_ref();                                                               \
   }

// Registers a destructor for the trampoline class that also decreases the reference again for
// ownership transferred pointers. THIS HAS TO BE THE LAST CLASS ENTRY!!
#define TRAMPOLINE_DESTRUCTOR(cname)                                                                    \
   ~Py##cname()                                                                                         \
   {                                                                                                    \
      if (this != HolderStore::getPtrToDelete()) {                                                      \
         pybind11::gil_scoped_acquire gil;                                                              \
         pybind11::handle             pySelf =                                                          \
            pybind11::cast(static_cast<const cname *>(this), pybind11::return_value_policy::reference); \
         if (pySelf) pySelf.dec_ref();                                                                  \
      }                                                                                                 \
   }                                                                                                    \
   }                                                                                                    \
   ;                                                                                                    \
   bool isPy##cname(cname *ptr)                                                                         \
   {                                                                                                    \
      return dynamic_cast<Py##cname *>(ptr) != nullptr;

PYBIND11_DECLARE_HOLDER_TYPE(T, owntrans_ptr<T>);

#endif // HOLDER_HH
