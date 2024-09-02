.. _hello-cmake:


From sources to executables
===========================

.. questions::

   - How do we use CMake to compile source files to executables?

.. objectives::

   - Learn what tools are available in the CMake suite.
   - Learn how to write a simple ``CMakeLists.txt``.
   - Learn the difference between **build systems**, **build tools**, and **build system generator**.
   - Learn to distinguish between *configuration*, *generation*, and **build* time.
 


What is CMake and why should you care?
--------------------------------------

Software is everywhere and so are build systems. Whenever you run a piece of software, anything from calendar apps to computationally-intensive programs, there was a build system involved in transforming the plain-text source code into binary files that could run on the device you are using.

CMake is a **build-system generator**: it provides a family of tools and a *domain-specific language* (DSL) to **describe** what the build system should achieve when the appropriate build tools are invoked. The DSL is platform- *and* compiler-agnostic: you can reuse the same CMake scripts to obtain **native** build systems on any platform.


.. figure:: img/build-systems.svg
   :align: center

   On GNU/Linux, the native build system will be a collection of ``Makefile``-s. The ``make`` build tool uses these ``Makefile``-s to transform sources to executables and libraries.

   CMake abstracts the process of generating the ``Makefile``-s away into a generic DSL.


A CMake-based build system:

- can bring your software closer to being platform- *and* compiler-agnostic.
- has good support within many integrated development environments (IDEs).
- automatically tracks and propagates internal dependencies in your project.
- is built on top of well-maintained functionality for automated dependency detection.


Hello, CMake!
-------------


.. typealong:: Compiling "Hello, world" with CMake

   We will now proceed to compile a single source file to an executable. Choose your favorite language and start typing along!

   .. tabs::

      .. tab:: C++

         You can find the file with the complete source code in the
         ``content/code/00_hello-cxx`` folder.

         .. literalinclude:: code/00_hello-cxx/hello.cpp
            :language: c++

         A working solution is in the ``solution`` subfolder.

      .. tab:: Fortran

         You can find the file with the complete source code in the
         ``content/code/00_hello-f`` folder.

         .. literalinclude:: code/00_hello-f/hello.f90
            :language: fortran

         A working solution is in the ``solution`` subfolder.

   1. The folder contains only the source code. We need to add a file called ``CMakeLists.txt`` to it. CMake reads the contents of these special files when generating the build system.

   2. The first thing we will do is declare the requirement on minimum version of CMake:

      .. code-block:: cmake

         cmake_minimum_required(VERSION 3.18)

   3. Next, we declare our project and its programming language:

      .. code-block:: cmake

         project(Hello LANGUAGES CXX)

   4. We create an *executable target*. CMake will generate rules in the build system to compile and link our source file into an executable:

      .. code-block:: cmake

         add_executable(hello hello.cpp)

   5. We are ready to call CMake and get our build system:

      .. code-block:: bash

         $ cmake -S. -Bbuild

   6. And finally build our executable:

      .. code-block:: bash

         $ cmake --build build








