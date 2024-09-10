Setting up your system
======================


In order to follow this workshop, you will need access to compilers, Python and CMake. You can use an HPC cluster if you have access to one, but the instructions here cover how to install the prerequisites on your own computer.

We also show how you can use `Binder
<https://mybinder.org>`_ to run in the cloud.

These instructions are based on installing compilers and CMake via the `Conda package and environment manager <https://docs.conda.io/en/latest/>`_, as it provides a convenient way to install binary packages in an isolated software environment.


For Windows users
-----------------


We strongly recommend to use (and install if necessary) the **Windows Subsystem for Linux (WSL)** as it is a powerful tool which will likely be useful also after the workshop. Inside WSL you will need Python 3 and the conda environment manager.  A useful guide to doing this is found at `HERE <https://github.com/kapsakcj/win10-linux-conda-how-to>`_. The installation of the required dependencies in a WSL terminal is documented below.


For MacOS and Linux users
-------------------------


MacOS and Linux users can simply open a terminal and install 
`Miniconda <https://docs.conda.io/en/latest/miniconda.html>`_:
  
- For MacOS see `HERE <https://docs.conda.io/en/latest/miniconda.html#macosx-installers>`_.
- For Linux see `HERE <https://docs.conda.io/en/latest/miniconda.html#linux-installers>`_.


Creating an environment and installing packages
-----------------------------------------------


Once you have ``conda`` installed (and ``WSL`` if you're using Windows OS) you can use the :download:`environment.yml <../environment.yml>` file to install dependencies.

First save it to your hard drive by clicking the link, and then in a terminal navigate to where you saved the file and type::

  conda env create -f environment.yml

You then need to activate the new environment by::

  conda activate intro-to-cmake

Now you should have CMake, compilers, Python and a few other packages installed!

