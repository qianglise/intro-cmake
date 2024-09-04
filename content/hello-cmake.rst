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


Important issues for the ``CMakeLists.txt`` file
------------------------------------------------


1. Any CMake build system will invoke the following commands in its **root**
   ``CMakeLists.txt``:

   .. signature:: |cmake_minimum_required|

      .. code-block:: cmake

         cmake_minimum_required(VERSION <min>[...<max>] [FATAL_ERROR])

   .. parameters::

      ``VERSION``: Minimum and, optionally, maximum version of CMake to use.
      ``FATAL_ERROR``: Raise a fatal error if the version constraint is not satisfied. This option is ignored by CMake >=2.6

   .. signature:: |project|

      .. code-block:: cmake

         project(<PROJECT-NAME>
                 [VERSION <major>[.<minor>[.<patch>[.<tweak>]]]]
                 [DESCRIPTION <project-description-string>]
                 [HOMEPAGE_URL <url-string>]
                 [LANGUAGES <language-name>...])

   .. parameters::

      ``<PROJECT-NAME>``: The name of the project.
      ``LANGUAGES``: Languages in the project.


2. The case of CMake commands does not matter: the DSL is case-insensitive. However, the plain-text files that CMake parses **must be called** ``CMakeLists.txt`` and the case matters! The variable names are also case sensitive!


3. The command to add executables to the build system is |add_executable|:

   .. signature:: |add_executable|

      .. code-block:: cmake

         add_executable(<name> [WIN32] [MACOSX_BUNDLE]
                        [EXCLUDE_FROM_ALL]
                        [source1] [source2 ...])


4. Using CMake you can abstract the generation of the build system and also the invocation of the build tools.

.. callout:: Put your ``CMakeLists.txt`` under version control

   All CMake-related files will evolve together with your codebase. It's a good    idea to put them under version control. On the contrary, any of the    *generated* native build-system files, *e.g.* ``Makefile``-s, should not be version-controlled.


.. typealong:: The command-line interface to CMake

   Let us get acquainted with the CMake and especially its command-line interface.

   We can get help at any time with the command 

   .. code-block:: bash

      $ cmake --help

   This will output quite a number of options to your screen. We can analyze the last few lines first:

   .. code-block:: text

      Generators

      The following generators are available on this platform (* marks default):
      * Unix Makefiles                  = Generates standard UNIX makefiles.
        Green Hills MULTI               = Generates Green Hills MULTI files.
        Ninja                           = Generates build.ninja files.
        Ninja Multi-Config              = Generates build-<Config>.ninja files.
        Watcom WMake                    = Generates Watcom WMake makefiles.
        CodeBlocks - Ninja              = Generates CodeBlocks project files.
        CodeBlocks - Unix Makefiles     = Generates CodeBlocks project files.
        CodeLite - Ninja                = Generates CodeLite project files.
        CodeLite - Unix Makefiles       = Generates CodeLite project files.
        Sublime Text 2 - Ninja          = Generates Sublime Text 2 project files.
        Sublime Text 2 - Unix Makefiles = Generates Sublime Text 2 project files.
        Kate - Ninja                    = Generates Kate project files.
        Kate - Unix Makefiles           = Generates Kate project files.
        Eclipse CDT4 - Ninja            = Generates Eclipse CDT 4.0 project files.
        Eclipse CDT4 - Unix Makefiles   = Generates Eclipse CDT 4.0 project files.

   In CMake terminology, the native build scripts and build tools are called **generators**. On any particular platform, the list will show which native build tools can be used through CMake. They can either be "plain", such as ``Makefile``-s or Ninja, or IDE-like projects.

   The ``-S`` switch specifies which source directory CMake should scan: this is the folder containing the *root* ``CMakeLists.txt``, *i.e.*, the one containing the |project| command. By default, CMake will allow *in-source* builds, *i.e.* storing build artifacts alongside source files. This is **not** good practice: you should always keep build artifacts from sources separate. Fortunately, the ``-B`` switch helps with that, as it is used to give where to store build artifacts, including the generated build system. This is the minimal invocation of ``cmake``:

   .. code-block:: bash

      $ cmake -S. -Bbuild

   To switch to another generator, we will use the ``-G`` switch:

   .. code-block:: bash

      $ cmake -S. -Bbuild -GNinja

   Options to be used at build-system generation are passed with the ``-D`` switch. For example, to change compilers:

   .. code-block:: bash

      $ cmake -S. -Bbuild -GNinja -DCMAKE_CXX_COMPILER=clang++

   Finally, you can access to the full CMake manual with:

   .. code-block:: bash

      $ cmake --help-full

   You can also inquire about a specific module, command or variable:

   .. code-block:: bash

      $ cmake --help-variable CMAKE_GENERATOR




