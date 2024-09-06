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


Real-world projects require more than compiling a few source files into executables and/or libraries. In most cases, you will come to projects comprising hundreds of source files sprawling in a complex source tree. Using modern CMake helps you keep the complexity of the build system in check.



