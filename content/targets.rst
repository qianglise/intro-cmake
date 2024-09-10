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



Visibility levels
-----------------


Why it is robust to use targets and properties than using variables? Given a target ``tgtX``, we can invoke one command in the ``target_*`` family as follows.

.. code-block:: cmake

   target_link_libraries(tgtX
     PRIVATE tgt1
     INTERFACE tgt2
     PUBLIC tgt3
     )


.. figure:: img/target_inheritance.svg
   :align: center

   Properties on targets have varied **visibility levels**, which determine how CMake should propagate them between interdependent targets.



.. typealong:: Understanding visibility levels


Visibility levels ``PRIVATE``, ``PUBLIC``, or ``INTERFACE`` are very powerful and herein we will briefly demonstrate their difference.
	
In this demo, we split the source code into 3 libraries and all files are available in the ``content/code/xx_visibility-levels/`` folder.

.. code-block:: bash

   .
   ├── CMakeLists.txt
   ├── greeting
   │   ├── greeting.cpp
   │   └── greeting.hpp
   ├── hello_world
   │   ├── hello_world.cpp
   │   └── hello_world.hpp
   ├── main.cpp
   └── world
       ├── world.cpp
       └── world.hpp


In this source code, the main function links to greeting which links to hello_world which links to world.


.. typealong:: The internal dependency tree

   If you have installed ``Graphviz``, you can visualize the dependencies between these targets:

   .. code-block:: console

      $ cd build
      $ cmake --graphviz=project.dot ..
      $ dot -T svg project.dot -o graphviz-greeting-hello-world.svg

   .. figure:: img/graphviz-greeting-hello-world.svg
      :align: center

      The dependencies between the four targets in the code example.
 


Take a look at the ``CMakeLists.txt``:


.. literalinclude:: code/xx_visibility-levels-CR/CMakeLists.txt
   :language: cmake
   :linenos:
   :emphasize-lines: 17


.. exercise:: Testing the 3 different visibility levels

   1. Browse, configure, build, and run the code.

   2. Uncomment the highlighted line (line 17) with ``target_compile_definitions``, configure into a fresh folder, and build using the commands below. You will see that the definition is used in ``world.cpp`` but nowhere else.

      .. code-block:: console

         $ cmake -S. -Bbuild_private
         $ cmake --build build_private

   3. Change the definition to ``PUBLIC``, configure into a fresh folder, and build. You will see that the definition is used both in ``world.cpp`` and ``hello_world.cpp``.

      .. code-block:: console

         $ cmake -S. -Bbuild_public
         $ cmake --build build_public

   4. Then change the definition to ``INTERFACE``, configure into a fresh folder, and build. You will see that the definition is used only in ``hello_world.cpp`` but not in ``world.cpp``.

      .. code-block:: console

         $ cmake -S. -Bbuild_interface
         $ cmake --build build_interface















Properties
----------


CMake lets you set properties at many different levels of visibility across the project:

- **Global scope**. These are equivalent to variables set in the root ``CMakeLists.txt``. Their use is, however, more powerful as they can be set from *any* leaf ``CMakeLists.txt``.
- **Directory scope**. These are equivalent to variables set in a given leaf ``CMakeLists.txt``.
- **Target**. These are the properties set on targets that we discussed above.
- **Test**.
- **Source files**. For example, compiler flags.
- **Cache entries**.
- **Installed files**.


For a complete list of properties known to CMake:

.. code-block:: bash

   $ cmake --help-properties | less


You can get the current value of any property with ``get_property`` and set the value of any property with ``set_property``.



Multiple folders
----------------






















