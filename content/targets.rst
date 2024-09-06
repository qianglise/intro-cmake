.. _targets:


Target-based build systems with CMake
=====================================


.. questions::

   - How can we handle more complex projects with CMake?
   - What exactly are **targets** in the CMake domain-specific language (DSL)?

.. objectives::

   - Learn that the **basic elements** in CMake are not variables, but targets.
   - Learn about properties of targets and how to use them.
   - Learn how to use *visibility levels* to express dependencies between targets.
   - Learn how to work with projects spanning multiple folders.
   - Learn how to handle multiple targets in one project.


Real-world projects require more than compiling a few source files into executables and/or libraries. In most cases, you will come to projects comprising hundreds of source files sprawling in a complex source tree.


With the advent of CMake 3.0, also known as **Modern CMake**, there has been a significant shift that the CMake domain-specific language (DSL) is structured, which can help you keep the complexity of the build system in check. Rather than relying on **variables** to convey information in a project, all what you need in modern CMake is **targets** and **properties**.



Targets
-------


A target is the basic element in the CMake DSL, which can be declared by either ``add_executable`` or ``add_library``. Any target has a collection of **properties**, which define:

* *how* the build artifact should be produced,
* *how* it should be used by other targets in the project that depend on it.


.. figure:: img/target.svg
   :align: center

    Compile options, definitions, include directories, source files, link libraries, and link options are properties of targets. These properties can be read with ``get_target_property`` and modified with ``set_target_properties``.



In CMake, the five most used commands used to handle targets are:

- ``target_sources``, specifying which source files to use when compiling a target.
- ``target_compile_options``, specifying which compiler flags to use.
- ``target_compile_definitions``, specifying which compiler definitions to use.
- ``target_include_directories``, specifying which directories will contain header (for C/C++) and module (for Fortran) files.
- ``target_link_libraries``, specifying which libraries to link into the current target.


There are additional commands in the ``target_*`` family:

.. code-block:: bash

   $ cmake --help-command-list | grep "^target_"
   
   target_compile_definitions
   target_compile_features
   target_compile_options
   target_include_directories
   target_link_directories
   target_link_libraries
   target_link_options
   target_precompile_headers
   target_sources







