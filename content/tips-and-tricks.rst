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
























.. rubric:: Footnotes

.. [#adapt_from_CR] This episode is adapted, with permission, from the `CodeRefinery CMake lesson <https://coderefinery.github.io/cmake-workshop/growing-projects>`_.

.. [#glob] A glob would be done using the ``file`` command. We quote the explanation in the official documentation as to why it is generally not safe to use the ``GLOB`` subcommand: *If no ``CMakeLists.txt`` file changes when a source is added or removed then the generated build system cannot know when to ask CMake to regenerate. The ``CONFIGURE_DEPENDS`` flag may not work reliably on all generators, or if a new generator is added in the future that cannot support it, projects using it will be stuck. Even if ``CONFIGURE_DEPENDS`` works reliably, there is still a cost to perform the check on every rebuild.*

