.. _targets-new-visibility-levels:

Visibility levels (Code from Coderefineary)
-------------------------------------------


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






