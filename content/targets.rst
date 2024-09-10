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
	
	In this demo, we want to compile a C++ library and an executable. A complete source code and solution are available in the ``content/code/xx_visibility-levels/`` folder.
	
	* The library code in the ``account`` subfolder consists of one source (account.cpp) and one header file (account.hpp). This header file and the shared library are needed to produce the ``bank`` executable.
	* The compiler flag ``-ffast-math`` will be used to propaged throughout the project.
	* The executable code is in ``bank.cpp``, which includes the header file ``account.hpp``.
	
	More description about the source code:

   1. The ``account`` target declares the ``account.cpp`` source file as ``PRIVATE`` since it is only needed to produce the shared library.

      .. code-block:: cmake

         target_sources(account
           PRIVATE
             account.cpp
           )

   2. The ``-ffast-math`` is instead ``PUBLIC`` as it needs to be propagated to all targets consuming ``account``.

      .. code-block:: cmake

         target_compile_options(account
           PUBLIC
             "-ffast-math"
           )

   3. The ``account`` folder is an include directory with ``INTERFACE`` visibility because only targets consuming ``account`` need to know where ``account.hpp`` is located.

      .. code-block:: cmake

         target_include_directories(account
           INTERFACE
             ${CMAKE_CURRENT_SOURCE_DIR}
           )

   .. callout:: Rule of thumb for visibility settings

	   When working out which visibility settings to use for the properties of your targets you can refer to the following table:

		  ==============  ================ ============
			Who needs?             Others
		  --------------  -----------------------------
		   Target            **YES**           **NO**
		  ==============  ================ ============
			**YES**       ``PUBLIC``       ``PRIVATE``
			**NO**        ``INTERFACE``     N/A
		  ==============  ================ ============


