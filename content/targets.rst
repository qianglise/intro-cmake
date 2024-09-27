.. _targets:


Target-based build systems with CMake
=====================================


.. questions::

   - How can we handle complex projects with CMake?
   - What exactly are **targets** in the CMake domain-specific language (DSL)?

.. objectives::

   - Learn that the **basic elements** in CMake are not variables, but targets.
   - Learn about properties of targets and how to use them.
   - Learn how to use **visibility levels** to express dependencies between targets.
   - Learn how to handle multiple targets in one project.
   - Learn how to work with projects spanning multiple folders.



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



Visibility levels [#adapt_from_CR]_
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



.. callout:: Understanding visibility levels


	Visibility levels ``PRIVATE``, ``PUBLIC``, or ``INTERFACE`` are very powerful and herein we will briefly demonstrate their difference.
		
	In this demo, we split the source code into 3 libraries and all files are available in the ``content/code/04_visibility-levels/`` folder.

	.. code-block:: bash

	   .
	   ├── CMakeLists.txt
	   ├── greeting
	   │   ├── greeting.cpp
	   │   └── greeting.hpp
	   ├── hello_world
	   │   ├── hello_world.cpp
	   │   └── hello_world.hpp
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


.. literalinclude:: code/04_visibility-levels/CMakeLists.txt
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


In the code example about the visibility levels, we have split a project into three folders and libraries but we kept one ``CMakeLists.txt``. As the project grows, this becomes impractical for humans (the CMake computer overlords will not mind) and maintenance becomes easier if we split the CMake configuration into multiple ``CMakeLists.txt`` with the help of ``add_subdirectory``. Our goal is to have a ``CMakeLists.txt`` as close as possible to the source files.

.. code-block:: text

   project/
   ├── CMakeLists.txt           <--- Root
   ├── external
   │   ├── CMakeLists.txt       <--- Leaf at level 1
   └── src
       ├── CMakeLists.txt       <--- Leaf at level 1
       ├── evolution
       │   ├── CMakeLists.txt   <--- Leaf at level 2
       ├── initial
       │   ├── CMakeLists.txt   <--- Leaf at level 2
       ├── io
       │   ├── CMakeLists.txt   <--- Leaf at level 2
       └── parser
           └── CMakeLists.txt   <--- Leaf at level 2


Each folder in a multi-folder project will contain a ``CMakeLists.txt``: a source tree with one **root** and many **leaves**.

- The root ``CMakeLists.txt`` will contain the invocation of the ``project`` command: variables and targets declared in the root have effectively global scope.
- The ``PROJECT_SOURCE_DIR`` will point to the folder containing the root ``CMakeLists.txt``.
- In order to move between the root and a leaf or between leaves, you will use the ``add_subdirectory`` command.


Typically, you only need to pass the first argument: the folder within the build tree will be automatically computed by CMake. We can declare targets at any level, not necessarily the root: a target is visible at the level at which it is declared and all higher levels.



.. exercise:: Exercise 05: Cellular automata

   Let's work with a project spanning multiple folders. We will implement a relatively simple code to compute and print to screen elementary `cellular automata <https://en.wikipedia.org/wiki/Cellular_automaton#Elementary_cellular_automata>`_. We separate the sources into ``src`` and ``external`` to simulate a nested project which reuses an external project.

   Your goal is to:

   - 1. Build the main executable at ``content/code/05_automata-cxx/`` for C++ and ``content/code/05_automata-f/`` for Fortran.
   - 2. Where are the obtained executables located in the build tree? Remember that CMake generates a build tree mirroring the source tree.
   - 3. The executable will accept 3 arguments: the length, number of steps, and
     automaton rule. You can run it with:

     .. code-block:: bash

        $ automata 40 5 30

     The output will be:

     .. code-block:: text

        length: 40
        number of steps: 5
        rule: 30
                            *
                           ***
                          **  *
                         ** ****
                        **  *   *
                       ** **** ***



.. typealong:: The internal dependency tree

   You can visualize the dependencies between targets in the project with Graphviz:

  .. code-block:: bash

     $ cd build
     $ cmake --graphviz=project.dot ..
     $ dot -T svg project.dot -o project-multiple-folder.svg

  .. figure:: img/graphviz-multiple-folder-project.svg
     :align: center

     The dependencies between targets in the cellular automata project.



.. keypoints::

   - Using **targets**, you can achieve granular control over how artifacts are built and how their dependencies are handled.
   - Compiler flags, definitions, source files, include folders, link libraries, and linker options are **properties** of a target.
   - Avoid using variables to express dependencies between targets: use visibility levels ``PRIVATE``, ``INTERFACE``, ``PUBLIC`` and let CMake figure out the details.
   - To keep the complexity of the build system at a minimum, each folder in a multi-folder project should have its own CMake script.


.. rubric:: Footnotes

.. [#adapt_from_CR] This subsection is adapted, with permission, from the `CodeRefinery CMake lesson <https://coderefinery.github.io/cmake-workshop/targets/>`_.

