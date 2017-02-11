synfig-playground
=================

This is repository for new Synfig modules which are not yet stabilized and/or
standardized.

Modules
=======

Time curve
----------

Valuenode to interpolate numerical values using bezier curves (see
<https://github.com/synfig/synfig/issues/295>)

Skeleton influence
------------------

Valuenode that links curve path to skeleton dynamically.

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

How to write a module
=====================

There is ongoing effort to rewrite some core parts of synfig to make extending
it much easier. However, it also means that existing modules will have to be
rewritten as well.

Documentation on how to write new modules will be available as soon as new core
API gets stabilized.
