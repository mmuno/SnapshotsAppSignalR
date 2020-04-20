Kraft documentation
*************************************

Kraft is the ecosystem used at SKF Magnetic Mechatronic to add cloud
capabilities to magnetic bearings.

This documentation explain how the Kraft's python codebase works.
For any question relative to C++ codebase, refer to: ......


Table of content
===============================

.. toctree::
   :maxdepth: 2
   
   supervisor
   daemons

How Kraft works
================================
- All common tasks are performed in **a daemon**
- A daemon can expose multiple **services**
- A service result is available as a subscription, using ZeroMQ
- The daemons are managed by the **supervisor**

Setup procedure
================
1. Install Python 3.7 using your favorite package manager.
2. Install Pip for Python 3.7.
3. Run **install_dependencies.sh**
4. Run run.py::

    python run.py
