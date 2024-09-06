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


A target is declared by either ``add_executable`` or ``add_library``. In broad terms, a target maps to a build artifact in the project. [#custom_targets]_ Any target has a collection of **properties**, which define:

* *how* the build artifact should be produced,
* *how* it should be used by other targets in the project that depend on it.


.. figure:: img/target.svg
   :align: center

   A target is the basic element in the CMake DSL. Each target has *properties*. Herein, compile options, definitions, include directories, source files, link libraries, and link options are properties of targets. These properties can be read with ``get_target_property`` and modified with ``set_target_properties``.







