synfig-playground
=================

This is repository for new Synfig modules which are not yet stabilized and/or
standardized.

Dependencies
============

* Synfig **CMake build** for all modules
* [lib2geom](https://github.com/caryoscelus/lib2geom) **dynamic library** for TimeCurve

Building
========

If all deps are satisfied, you only need to run typical CMake build. E.g.:

```
mkdir build && pushd build
cmake -GNinja .. -DCMAKE_BUILD_TYPE=RelWithDebInfo
cmake --build . -- all
sudo cmake --build . -- install
popd
```
