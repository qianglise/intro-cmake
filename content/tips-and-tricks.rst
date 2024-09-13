.. _tips-and-tricks:


Tips and tricks using CMake
============================


.. objectives::

   - Learn what tools exist to structure projects as they grow.
   - Discuss the value of localizing scope and avoiding side effects.
   - Recognize more maintainable and less maintainable patterns.


As projects grow, code structures get more complicated: more possibilities, more corner cases, more options to users, and more developers who are contributing and may not oversee the entire CMake structure. In this episode we will mention a couple of tools to bring some structure and flow-control into larger projects. [#adapt_from_CR]_



Listing sources or globbing them
--------------------------------


In all our examples we have listed all sources when defining targets.

In CMake, you can glob patters (*e.g.* all files that end with ``*.cpp``) without listing them explicitly. This is tempting, but we advice **against** doing this. The reason is that CMake cannot **guarantee** correct tracking dependency changes when you add files after you have configured. [#glob]_

Listing files explicitly also allows to ``grep`` for them in the CMake code to see where a modification is likely needed. This can help colleagues in our projects who are not familiar with CMake to find out where to change things.



Options and flow control
------------------------


You may want to give users the possibility to decide whether they want to enable an option or not.

.. code-block:: cmake

   # by default this one will be ON
   option(ENABLE_MPI "Configure for MPI parallelization" ON)

   if(ENABLE_MPI)
     find_package(MPI REQUIRED COMPONENTS Fortran)
   else()
     message(STATUS "no problem, building without MPI")
   endif()

Now the users can decide:

.. code-block:: console

   $ cmake -S. -Bbuild -DENABLE_MPI=OFF



Organizing files into modules
-----------------------------


Modules are collections of functions and macros and are either CMake- or user-defined. CMake comes with a rich ecosystem of modules and you will probably write a few of your own to encapsulate frequently used functions or macros in your CMake scripts.

You can collect related CMake-code into a file called ``my_lengthy_code.cmake`` and then include it in another CMake code as shown below. This can help organizing projects that are growing out of hand and separate concerns.

.. code-block:: cmake

   include(my_lengthy_code)



Variables vs. targets
---------------------


In :ref:`targets` we have motivated why targets are preferable over variables.

When you portion your project into modules, then variable declaration impose an order and the risk is high that somebody will not know about the implicit order and reorder modules one day and the behavior will change.

Try to minimize the use of user-defined variables. They can point to a sub-optimal solution and a better, more state-less, declarative, solution may exist.



Functions and macros
--------------------


**Functions** and **macros** are built on top of the basic built-in commands and are either CMake- or user-defined. These prove useful to avoid repetition in your CMake scripts. The difference between a function and a macro is their **scope**:

#. Functions have their own scope: variables defined inside a function are not propagated back to the caller.
#. Macros do not have their own scope: variables from the parent scope can be modified and new variables in the parent scope can be set.

**Prefer functions over macros to minimize side-effects**.


































.. rubric:: Footnotes

.. [#adapt_from_CR] This episode is adapted, with permission, from the `CodeRefinery CMake lesson <https://coderefinery.github.io/cmake-workshop/growing-projects>`_.

.. [#glob] A glob would be done using the ``file`` command. We quote the explanation in the official documentation as to why it is generally not safe to use the ``GLOB`` subcommand: *If no ``CMakeLists.txt`` file changes when a source is added or removed then the generated build system cannot know when to ask CMake to regenerate. The ``CONFIGURE_DEPENDS`` flag may not work reliably on all generators, or if a new generator is added in the future that cannot support it, projects using it will be stuck. Even if ``CONFIGURE_DEPENDS`` works reliably, there is still a cost to perform the check on every rebuild.*

